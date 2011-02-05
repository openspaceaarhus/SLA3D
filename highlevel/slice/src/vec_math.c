#include <math.h>
#include <stdlib.h>
#include "vec_math.h"

vec3d vec3d_create(float x, float y, float z) {
  vec3d tmp;
  tmp.x = x;
  tmp.y = y;
  tmp.z = z;
  return tmp;
}

vec3d vec3d_sub(vec3d v, vec3d u) {
  vec3d tmp;
  tmp.x = v.x - u.x;
  tmp.y = v.y - u.y;
  tmp.z = v.z - u.z;
  return tmp;
}


vec3d vec3d_add(vec3d v, vec3d u) {
  vec3d tmp;
  tmp.x = v.x + u.x;
  tmp.y = v.y + u.y;
  tmp.z = v.z + u.z;
  return tmp;
}

vec3d vec3d_cross(vec3d v, vec3d u) {
  vec3d tmp;
  tmp.x = v.y * u.z - u.y * v.z;
  tmp.y = v.z * u.x - u.z * v.x;
  tmp.z = v.x * u.y - u.x * v.y;
  return tmp;
}


vec3d vec3d_cross_y(vec3d u) {
  vec3d tmp;
  tmp.x = u.z;
  tmp.y = 0;
  tmp.z = -u.x;
  return tmp;
}


float vec3d_dot(vec3d v, vec3d u) {
  float tmp;
  tmp = v.x * u.x;
  tmp += v.y * u.y;
  tmp += v.z * u.z;
  return tmp;
}


vec3d vec3d_mul(vec3d v, float s) {
  vec3d tmp;
  tmp.x = v.x*s;
  tmp.y = v.y*s;
  tmp.z = v.z*s;
  return tmp;
}

vec3d vec3d_div(vec3d v, float s) {
  return vec3d_mul(v, 1.0f/s);
}

inline float vec3d_len(vec3d v) {
  return sqrt( vec3d_dot (v, v));
}

vec3d vec3d_normalize(vec3d v) {
  return vec3d_div(v, vec3d_len(v));
}

char vec3d_zero(vec3d v) {
  return fabs(v.x)<EPISILON &&
    fabs(v.y)<EPISILON &&
    fabs(v.z)<EPISILON;
}

char vec3d_compare(vec3d v, vec3d u) {
  return vec3d_zero(vec3d_sub(v, u));
}
