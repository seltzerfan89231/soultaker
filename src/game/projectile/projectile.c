#include "projectile.h"

Projectile* projectile_create(projtype type)
{
    Projectile* projectile = malloc(sizeof(Projectile));
    projectile->type = type;
    projectile->scale = 1;
    projectile->speed = 1;
    projectile->lifetime = 5;
    projectile->rotation = 0;
    projectile->direction = vec3f_create(0, 0, 0);
    return projectile;
}

void projectile_push_data(Projectile* projectile, f32* buffer, u32* length)
{
    buffer[(*length)++] = projectile->position.x;
    buffer[(*length)++] = projectile->position.y;
    buffer[(*length)++] = projectile->position.z;
    buffer[(*length)++] = projectile->rotation;
    buffer[(*length)++] = projectile->camera_rotation;
}

void projectile_update_data(Projectile* projectile, f32* buffer, u32 offset)
{
    projectile_push_data(projectile, buffer, &offset);
}

void projectile_update_position(Projectile* projectile, f32 dt)
{
    projectile->position = vec3f_add(projectile->position, vec3f_scale(projectile->speed * dt, projectile->direction));
}

void projectile_destroy(Projectile* projectile)
{
    free(projectile);
}