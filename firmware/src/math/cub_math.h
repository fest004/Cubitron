#ifndef VEC_H
#define VEC_H


#define MAX_ROWS 10
#define MAX_COLS 10

#include <stdint.h>
#include <stdlib.h>
#include "../core.h"


#ifdef __cplusplus
extern "C" {
#endif

/******************/
/* MATRIX STRUCTS */
/******************/


typedef struct
{
  uint8_t rows;
  uint8_t cols;
  double data[MAX_ROWS][MAX_COLS];
} cub_mat;



/******************/
/* VECTOR STRUCTS */
/******************/

/* vec2 */
typedef struct
{
  float x;
  float y;
} vec2f;

typedef struct
{
  int x;
  int y;
} vec2i;

/* vec3 */
typedef struct
{
  float x;
  float y;
  float z;
} vec3f;

typedef struct
{
  int x;
  int y;
  int z;
} vec3i;

/* vec4 */
typedef struct
{
  float x;
  float y;
  float z;
  float w;
} vec4f;

typedef struct
{
  int x;
  int y;
  int z;
  int w;
} vec4i;


/*********************/
/* MATRIX OPERATIONS */
/*********************/

int create_mat(uint8_t rows, uint8_t cols, cub_mat* res);
int free_mat(cub_mat* res);

int mat_print(cub_mat* A);
int mat_printf(cub_mat* A, const char* f_dmt);


/*********************/
/* VECTOR OPERATIONS */
/*********************/

/* Add */

int vec2i_add(vec2i a, vec2i b, vec2i* res);
int vec2f_add(vec2f a, vec2f b, vec2f* res);

int vec3i_add(vec3i a, vec3i b, vec3i* res);
int vec3f_add(vec3f a, vec3f b, vec3f* res);

int vec4i_add(vec4i a, vec4i b, vec4i* res);
int vec4f_add(vec4f a, vec4f b, vec4f* res);

/* Subtract */

int vec2i_sub(vec2i a, vec2i b, vec2i* res);
int vec2f_sub(vec2f a, vec2f b, vec2f* res);

int vec3i_sub(vec3i a, vec3i b, vec3i* res);
int vec3f_sub(vec3f a, vec3f b, vec3f* res);

int vec4i_sub(vec4i a, vec4i b, vec4i* res);
int vec4f_sub(vec4f a, vec4f b, vec4f* res);

/* Dot Product */

int vec2i_dot(vec2i a, vec2i b, int* res);
int vec2f_dot(vec2f a, vec2f b, float* res);

int vec3i_dot(vec3i a, vec3i b, int* res);
int vec3f_dot(vec3f a, vec3f b, float* res);

int vec4i_dot(vec4i a, vec4i b, int* res);
int vec4f_dot(vec4f a, vec4f b, float* res);

/* Cross Product */
int vec3i_cross(vec3i a, vec3i b, int* res);
int vec3f_cross(vec3f a, vec3f b, float* res);


#ifdef __cplusplus
}
#endif


#endif

