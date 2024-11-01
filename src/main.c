#include "display.h"
#include "vector.h"
#include <SDL2/SDL_keycode.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define N_POINTS 9 * 9 * 9

vec3_t cube_points[N_POINTS];
vec2_t projected_points[N_POINTS];
float fov_factor = 128;
vec3_t camera_position = { .x = 0, .y = 0, .z = 5 };
vec3_t rotation_point = { .x = 0, .y = 0, .z = 0 };

void
setup (void)
{
  color_buffer
      = (uint32_t *)malloc (sizeof (uint32_t) * window_width * window_height);
  color_buffer_texture = SDL_CreateTexture (renderer, SDL_PIXELFORMAT_ARGB8888,
                                            SDL_TEXTUREACCESS_STREAMING,
                                            window_width, window_height);
  /**
   * Because paint pixels from -1 on coordinate axis to +1
   */
  int point_counter = 0;
  for (float x = -1.0; x <= 1.0; x += 0.25)
    {
      for (float y = -1.0; y <= 1.0; y += 0.25)
        {
          for (float z = -1.0; z <= 1.0; z += 0.25)
            {
              vec3_t point = { .x = x, .y = y, .z = z };
              cube_points[point_counter++] = point;
            };
        }
    }
}

vec2_t
project (vec3_t point)
{
  vec2_t projected_point = { .x = fov_factor * point.x / point.z,
                             .y = fov_factor * point.y / point.z };
  return projected_point;
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
      if (event.key.keysym.sym == SDLK_UP)
        {
          camera_position.z--;
        }
      if (event.key.keysym.sym == SDLK_DOWN)
        {
          camera_position.z++;
        }
      if (event.key.keysym.sym == SDLK_LEFT)
        {
          fov_factor -= 10;
        }
      if (event.key.keysym.sym == SDLK_RIGHT)
        {
          fov_factor += 10;
        }
      break;
    }
}
void
update (void)
{
  for (int i = 0; i < N_POINTS; i++)
    {
      vec3_t cube_point = cube_points[i];
      rotation_point.x += 0.00001;
      rotation_point.y += 0.00001;
      rotation_point.z += 0.00001;

      vec3_t transformed_point = rotate_by_x (cube_point, rotation_point.x);
      transformed_point = rotate_by_y (transformed_point, rotation_point.y);
      transformed_point = rotate_by_z (transformed_point, rotation_point.z);

      transformed_point.z -= camera_position.z;
      projected_points[i] = project (transformed_point);
    }
}
void
render (void)
{

  draw_grid (10, 10, 0xFF222222);

  for (int i = 0; i < N_POINTS; i++)
    {
      draw_rectangle (projected_points[i].x + window_width / 2,
                      projected_points[i].y + window_height / 2, 4, 4,
                      0xFFFFF00);
    }

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
