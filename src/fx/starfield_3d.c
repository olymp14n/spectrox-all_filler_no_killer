#include "starfield_3d.h"
#include <stdlib.h>
#include <GL/gl.h>
#include <math.h>
#include "../fw/math.h"
#include "../fw/projection.h"
#include "../fw/render.h"

static const float _rangeX = 2;
static const float _rangeY = 2;
static const float _rangeZ = 10;

void fx_starfield_3d_init(int numStars, fx_starfield_3d *starfield) {
    starfield->numStars = numStars;
    starfield->stars = calloc(numStars, sizeof(fw_vec3f));

    srand(123);

    for (int i=0; i<numStars; i++) {
        starfield->stars[i].pos.x = fw_math_randf(-_rangeX,_rangeX);
        starfield->stars[i].pos.y = fw_math_randf(-_rangeY,_rangeY);
        starfield->stars[i].pos.z = fw_math_randf(-_rangeZ,0);
    }
}

void fx_starfield_3d_update(fx_starfield_3d *starfield, fw_timer_data *time) {
    for (int i=0; i < starfield->numStars; i++) {
        starfield->stars[i].pos.z += 3*time->delta;

        if (starfield->stars[i].pos.z > 0) {
            starfield->stars[i].pos.x = fw_math_randf(-_rangeX,_rangeX);
            starfield->stars[i].pos.y = fw_math_randf(-_rangeY,_rangeY);
            starfield->stars[i].pos.z = -_rangeZ;
        }
    }
}

static void renderLine(float minRange, float maxRange, float trailLength, float offX, float offY, float offZ, fx_starfield_3d *starfield) {
    for (int i=0; i<starfield->numStars; i++) {
        const float z = starfield->stars[i].pos.z;
        if (!(z >= minRange && z < maxRange)) {
            continue;
        }
        const float x = starfield->stars[i].pos.x;
        const float y = starfield->stars[i].pos.y;

        glVertex3f(offX+x, offY+y, offZ+z);
        glVertex3f(offX+x, offY+y, offZ+z-trailLength);
    }
}

void fx_starfield_3d_render(fx_starfield_3d *starfield, fw_timer_data *time) {
    fw_projection_perspective();

    glEnable(GL_DEPTH_TEST);

    const float trailLength = .4f;

    const float a = .04f*.2f;
    const float s1 = 2.f;
    const float s2 = 1.f;

    const float add1 = a*sinf(time->elapsed*s1);
    const float add2 = a*cosf(time->elapsed*s2);
    const float add3 = a*sinf(1.1f+time->elapsed*s2);
    const float add4 = a*cosf(1.1f+time->elapsed*s1);

    glLineWidth(4);

    glBegin(GL_LINES);
    {
        glColor3ub(32,46,55);
        renderLine(-11, -8, trailLength, 0,0,0, starfield);

        glColor3ub(57,74,80);
        renderLine(-8, -6, trailLength, 0,0,0, starfield);

        glColor3ub(122,54,123);
        renderLine(-6, -2, trailLength, 0,0,0, starfield);
    }
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    {
        glColor3ub(198,181,151);
        renderLine(-2, 1, trailLength, 0,0,0, starfield);
    }
    glEnd();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glLineWidth(4);
    glBegin(GL_LINES);
    {
        glColor3ub(255,0,0);
        renderLine(-5,-2, trailLength, add1, add2, add3, starfield);

        glColor3ub(0,0,255);
        renderLine(-5,-2, trailLength, add3, add4, add1, starfield);
    }
    glEnd();


    glLineWidth(2);
    glBegin(GL_LINES);
    {
        glColor3ub(255,0,0);
        renderLine(-2,1, trailLength, add1, add2, add3, starfield);

        glColor3ub(0,0,255);
        renderLine(-2,1, trailLength, add3, add4, add1, starfield);
    }
    glEnd();

    fw_render_defaultBlendMode();
    glDisable(GL_DEPTH_TEST);
}
