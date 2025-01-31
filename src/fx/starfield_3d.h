#ifndef FX_STARFIELD_3D_H
#define FX_STARFIELD_3D_H

#include "../fw/types.h"

typedef struct {
    fw_vec3f pos;
} fx_star_3d;

typedef struct {
    int numStars;
    fx_star_3d *stars;
} fx_starfield_3d;

void fx_starfield_3d_init(int numStars, fx_starfield_3d *starfield);
void fx_starfield_3d_update(fx_starfield_3d *starfield, fw_timer_data *time);
void fx_starfield_3d_render(fx_starfield_3d *starfield, fw_timer_data *time);

#endif
