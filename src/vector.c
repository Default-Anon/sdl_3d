#include "vector.h"
#include <math.h>

vec3_t
rotate_by_x (vec3_t point, float angle)
{
  vec3_t rotated_point
      = { .x = point.x,
          .y = point.y * cos (angle) - point.z * sin (angle),
          .z = point.y * sin (angle) + point.z * cos (angle) };
  return rotated_point;
}

vec3_t
rotate_by_y (vec3_t point, float angle)
{
  vec3_t rotated_point
      = { .y = point.y,
          .x = point.x * cos (angle) - point.z * sin (angle),
          .z = point.x * sin (angle) + point.z * cos (angle) };
  return rotated_point;
}

vec3_t
rotate_by_z (vec3_t point, float angle)
{
  vec3_t rotated_point
      = { .z = point.z,
          .x = point.x * cos (angle) - point.y * sin (angle),
          .y = point.x * sin (angle) + point.y * cos (angle) };
  return rotated_point;
}
