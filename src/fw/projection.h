#ifndef FW_PROJECTION_H
#define FW_PROJECTION_H

void fw_projection_perspective();
void fw_projection_ortho();
float fw_projection_getAspect();

void fw_projection_initPixelPerfectZ(void);
float fw_projection_getPixelPerfectZ(void);

#endif
