#if !defined(CHUNK_H)
#define CHUNK_H
#include "camera.h"
#include <glad/glad.h>
#include <cglm/cglm.h>

typedef enum {
  BLOCK_AIR, // BLOCK_AIR SHOULD ALWAYS BE FIRST

  BLOCK_WHITE,

  BLOCK_COUNT // BLOCK_COUNT SHOULD ALWAYS BE LAST
} Block;

#define CHUNK_WIDTH  16
#define CHUNK_HEIGHT 128
#define CHUNK_SIZE   CHUNK_WIDTH*CHUNK_WIDTH*CHUNK_HEIGHT

typedef struct {
  vec2 offset;
  Block blocks[CHUNK_SIZE];
} Chunk;

void
init_chunk_arrays();

void
init_chunk(Chunk* chunk);

void
render_chunk(Chunk* chunk, Camera* camera);

#endif // CHUNK_H