#include "display.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
void
setup (void)
{
  color_buffer
      = (uint32_t *)malloc (sizeof (uint32_t) * window_width * window_height);
  color_buffer_texture = SDL_CreateTexture (renderer, SDL_PIXELFORMAT_ARGB8888,
                                            SDL_TEXTUREACCESS_STREAMING,
                                            window_width, window_height);
}
void
process_input (void)
{
  SDL_Event event;
  SDL_PollEvent (&event);

  switch (event.type)
    {
    case SDL_QUIT:
      is_running = false;
      break;
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE)
        {
          is_running = false;
          break;
        }
      break;
    }
}
void
update (void)
{
}
void
render (void)
{
  SDL_SetRenderDrawColor (renderer, 255, 0, 0, 255);
  SDL_RenderClear (renderer);

  draw_grid (10, 10, 0xFF00FFFF);
  draw_rectangle (1000, 500, 400, 500, 0xFFFFFF00);

  render_color_buffer ();
  clear_color_buffer (0xFF000000);

  SDL_RenderPresent (renderer);
}

int
main (void)
{
  is_running = initialize_window ();

  setup ();

  while (is_running)
    {
      process_input ();
      update ();
      render ();
    }
  destroy_window ();
  return 0;
}