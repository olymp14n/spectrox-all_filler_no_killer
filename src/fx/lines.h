#ifndef FX_LINES_H
#define FX_LINES_H

#include "../fw/types.h"

typedef struct {
    int numLines;
    fw_vec3f *lineCenters;
} fx_lines;


void fx_lines_init(int numLines, fx_lines *lines);
void fx_lines_update(float speed, fx_lines *lines, fw_timer_data *time);
void fx_lines_render(fx_lines *lines);

#endif
