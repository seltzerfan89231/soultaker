#ifndef UBO_H
#define UBO_H

#include <glad.h>
#include <glfw.h>
#include "../../util/type.h"

#define NUM_UBOS         9
#define MATRICES_UBO     0
#define ZOOM_UBO         1
#define ASPECT_RATIO_UBO 2
#define ROTATION_UBO     3
#define TILT_UBO         4
#define CONSTANTS_UBO    5
#define OUTLINE_UBO      6
#define GAME_TIME_UBO    7
#define MINIMAP_UBO      8

typedef struct {
    u32 id;
} UBO;

UBO ubo_create(size_t size);
void ubo_bind_buffer_base(UBO ubo, u32 index);
void ubo_update(UBO ubo, size_t offset, size_t size, void *data);
void ubo_destroy(UBO ubo);

#endif