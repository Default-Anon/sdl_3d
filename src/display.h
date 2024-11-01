#ifndef DISPLAY_H
#define DISPLAY_H

#include "vector.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

extern bool is_running;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *color_buffer_texture;
extern uint32_t *color_buffer;
extern int window_height;
extern int window_width;

void destroy_window (void);
bool initialize_window (void);
void clear_color_buffer (uint32_t color);
void render_color_buffer ();
void draw_pixel (int X, int Y, uint32_t pixel_color);
void draw_grid (int sizeX, int sizeY, uint32_t grid_color);
void draw_rectangle (int marginX, int marginY, int width, int height,
                     uint32_t color);

#endif
