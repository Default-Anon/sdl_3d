#include "display.h"
#include "vector.h"
#include <errno.h>

bool is_running = false;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *color_buffer_texture = NULL;
uint32_t *color_buffer = NULL;
int window_height = 600;
int window_width = 800;

bool
initialize_window (void)
{
  if (SDL_Init (SDL_INIT_EVERYTHING) != 0)
    {
      fprintf (stderr, "SDL_Init() error, %s\n", strerror (errno));
      return false;
    }

  // FULLSCREEN MODE
  SDL_DisplayMode display_mode;
  SDL_GetCurrentDisplayMode (0, &display_mode);

  window_width = display_mode.w;
  window_height = display_mode.h;

  window
      = SDL_CreateWindow (NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                          window_width, window_height, SDL_WINDOW_BORDERLESS);
  if (!window)
    {
      fprintf (stderr, "SDL_CreateWindow() error, %s\n", strerror (errno));
      return false;
    }
  SDL_SetWindowFullscreen (window, SDL_WINDOW_FULLSCREEN);
  renderer = SDL_CreateRenderer (window, -1, 0);

  if (!renderer)
    {
      fprintf (stderr, "SDL_CreateRenderer() error, %s\n", strerror (errno));
      return false;
    }
  return true;
}

void
clear_color_buffer (uint32_t color)
{
  for (int y = 0; y < window_height; y++)
    {
      for (int x = 0; x < window_width; x++)
        {
          color_buffer[window_width * y + x] = color;
        }
    }
}
void
render_color_buffer ()
{
  SDL_UpdateTexture (color_buffer_texture, NULL, color_buffer,
                     window_width * sizeof (uint32_t));
  SDL_RenderCopy (renderer, color_buffer_texture, NULL, NULL);
}
void
draw_grid (int sizeX, int sizeY, uint32_t grid_color)
{
  for (int y = 0; y < window_height; y++)
    {
      for (int x = 0; x < window_width; x++)
        {
          if (y % sizeY == 0 || x % sizeX == 0)
            {
              color_buffer[window_width * y + x] = grid_color;
            }
        }
    }
}
void
draw_rectangle (int marginX, int marginY, int width, int height,
                uint32_t color)
{
  for (int y = marginY; y < height + marginY; y++)
    {
      for (int x = marginX; x < width + marginX; x++)
        {
          draw_pixel (x, y, color);
        }
    }
}
void
draw_pixel (int x, int y, uint32_t pixel_color)
{
  if (x >= 0 && x < window_width && y >= 0 && y < window_height)
    color_buffer[window_width * y + x] = pixel_color;
}

void
destroy_window (void)
{
  free (color_buffer);
  SDL_DestroyRenderer (renderer);
  SDL_DestroyWindow (window);
  SDL_Quit ();
}
