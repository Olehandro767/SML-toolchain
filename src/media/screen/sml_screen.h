#ifndef SML_MEDIA_SCREEN_H
#define SML_MEDIA_SCREEN_H

typedef struct {
  unsigned int width;
  unsigned int height;
} sml_screen_resolution;

sml_screen_resolution sml_get_screen_resilution();

#endif /* SML_MEDIA_SCREEN_H */
