#include "projection.h"
#include <GL/glu.h>
#include <math.h>
#include "../config/config.h"

static const float _aspect = FW_RENDER_WIDTH/(float)FW_RENDER_HEIGHT;
static const float _zFar = FW_RENDER_HEIGHT*2.f;
static const float _fov = 45.f;
static float _pixelPerfectZ;

void fw_projection_perspective() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(_fov, _aspect, 0.01f, _zFar);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void fw_projection_ortho() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, FW_RENDER_WIDTH, FW_RENDER_HEIGHT, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

float fw_projection_getAspect() {
    return _aspect;
}

void fw_projection_initPixelPerfectZ(void) {
    // https://stackoverflow.com/a/46285620/891846
    float angRad = _fov * M_PI / 180.f;
    _pixelPerfectZ = -FW_RENDER_HEIGHT / (2.f * tanf(angRad * .5f));
}

/**
 * Get Z plane at which images are displayed pixel perfect with perspective projection.
 */
float fw_projection_getPixelPerfectZ(void) {
    return _pixelPerfectZ;
}
