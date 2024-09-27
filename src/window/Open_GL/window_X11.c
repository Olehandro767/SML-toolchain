#include "../sml_window.h"
#include <GL/glx.h>
#include <SDL2/SDL_image.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  Window window;
  Display *display;
  GLXContext glcontext;
} sml_X11_GL_window_context;

void set_window_icon(Display *display, Window window, const_string icon_path) {
  if (IMG_Init(IMG_INIT_PNG) == 0) {
    fprintf(stderr, "Failed to initialize SDL_image: %s\n", IMG_GetError());
    return;
  }

  SDL_Surface *image = IMG_Load(icon_path);
  if (!image) {
    fprintf(stderr, "Failed to load icon image: %s\n", IMG_GetError());
    IMG_Quit();
    return;
  }

  int icon_width = image->w;
  int icon_height = image->h;
  int pixel_count = icon_width * icon_height;

  long *icon_data = (long *)malloc((2 + pixel_count) * sizeof(long));
  icon_data[0] = icon_width;
  icon_data[1] = icon_height;

  Uint32 *pixels = (Uint32 *)image->pixels;
  for (int i = 0; i < pixel_count; i++) {
    Uint32 pixel = pixels[i];
    Uint8 r, g, b, a;
    SDL_GetRGBA(pixel, image->format, &r, &g, &b, &a);
    icon_data[2 + i] = (a << 24) | (r << 16) | (g << 8) | b;
  }

  Atom _NET_WM_ICON = XInternAtom(display, "_NET_WM_ICON", False);
  XChangeProperty(display, window, _NET_WM_ICON, XA_CARDINAL, 32,
                  PropModeReplace, (unsigned char *)icon_data, 2 + pixel_count);

  free(icon_data);
  SDL_FreeSurface(image);
  IMG_Quit();
}

void *sml_open_window(sml_window_properties properties) {
  Display *display = XOpenDisplay(NULL);
  if (display == NULL) {
    printf("Cannot connect to X server\n");
    exit(1);
  }

  GLint attrib_list[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};
  XVisualInfo *visual_info = glXChooseVisual(display, 0, attrib_list);

  if (visual_info == NULL) {
    printf("No appropriate visual found\n");
    exit(1);
  }

  Window root_window = DefaultRootWindow(display);
  Colormap colormap =
      XCreateColormap(display, root_window, visual_info->visual, AllocNone);
  XSetWindowAttributes window_attributes;
  window_attributes.colormap = colormap;
  window_attributes.event_mask = ExposureMask | KeyPressMask;
  window_attributes.override_redirect = properties.borderless;

  Window window = XCreateWindow(display, root_window, 0, 0, properties.width,
                                properties.height, 0, visual_info->depth,
                                InputOutput, visual_info->visual,
                                CWColormap | CWEventMask, &window_attributes);
  XMapWindow(display, window);
  XStoreName(display, window, properties.title);
  GLXContext glcontext = glXCreateContext(display, visual_info, NULL, GL_TRUE);
  glXMakeCurrent(display, window, glcontext);

  if (smp_string_is_not_empty(properties.icon_path)) {
    set_window_icon(display, window, properties.icon_path);
  }

  void *context_ptr = malloc(sizeof(sml_X11_GL_window_context));
  sml_X11_GL_window_context context =
      *((sml_X11_GL_window_context *)context_ptr);
  context.window = window;
  context.display = display;
  context.glcontext = glcontext;
  return context_ptr;
}

int sml_close_window(void *sml_context_ptr) {
  // FIXME Segmentation fault
  sml_X11_GL_window_context context =
      *((sml_X11_GL_window_context *)sml_context_ptr);
  glXMakeCurrent(context.display, None, NULL);
  glXDestroyContext(context.display, context.glcontext);
  XDestroyWindow(context.display, context.window);
  XCloseDisplay(context.display);
  free(sml_context_ptr);
  return 0;
}
