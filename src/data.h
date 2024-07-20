#ifndef DATA_H
#define DATA_H

#include "game/game.h"
#include "camera/camera.h"
#include "renderer/renderer.h"
#include "gui/gui.h"
#include "util/framedata.h"
#include "util/indices.h"

typedef struct {
    f32 *buffer;
    FrameData ***frame_data;
} Data;

extern Data data;

void data_init(void);
void data_update(void);
void data_update_tiles(void);
void data_update_walls(void);
void data_update_entities(void);
void data_update_projectiles(void);
void data_update_parjicles(void);
void data_update_particles(void);
void data_update_parstacles(void);
void data_update_obstacles(void);
void data_destroy(void);

#endif