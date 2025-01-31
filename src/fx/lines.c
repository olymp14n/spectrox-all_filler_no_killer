#include "lines.h"

#include <stdlib.h>
#include <GL/gl.h>

void fx_lines_init(int numLines, fx_lines *lines) {
    lines->numLines = numLines;
    lines->lineCenters = calloc(numLines, sizeof(fw_vec3f));

    for (int i=0; i<numLines; i++) {
        lines->lineCenters[i].z = -i;
    }
}

void fx_lines_update(float speed, fx_lines *lines, fw_timer_data *time) {

    for (int i=0; i < lines->numLines; i++) {
        lines->lineCenters[i].z += speed*time->delta;

        if (lines->lineCenters[i].z > 0) {
            lines->lineCenters[i].z = -lines->numLines;
        }
        if (lines->lineCenters[i].z < -lines->numLines) {
            lines->lineCenters[i].z = 0;
        }
    }
}

void fx_lines_render(fx_lines *lines) {
    for (int i=0; i<lines->numLines; i++) {
        if (lines->lineCenters[i].z > -4) {
            glLineWidth(3);
        } else {
            glLineWidth(2);
        }
        glBegin(GL_LINES);
        glVertex3f(-30,0,lines->lineCenters[i].z);
        glVertex3f(30,0,lines->lineCenters[i].z);
        glEnd();
    }
}
