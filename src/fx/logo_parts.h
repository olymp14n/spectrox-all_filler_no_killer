#ifndef FX_LOGO_PARTS_H
#define FX_LOGO_PARTS_H

#include "../fw/types.h"
#include "../fw/animation.h"
#include "../fw/image.h"

void fx_logo_parts_init(fw_animation *anim);
void fx_logo_parts_initEndAnim(fw_animation *anim);
void fx_logo_parts_render(int isRenderTopPart, int isRenderOnlyNonAccentParts, fw_vec4f color, fw_timer_data *time);
void fx_logo_parts_renderAccent(int i, int j, fw_image *img, int spriteIdx, fw_timer_data *time);

int *fx_logo_parts_getTopPartIndexes(void);

#endif
