#ifndef FW_RESOURCE_H
#define FW_RESOURCE_H

#include "fw/font.h"
#include "fw/image.h"

enum ImagesEnum {
    RES_IMG_FONT,
    RES_IMG_SPRITE_SHEET,
    RES_IMG_BAYER_VERTICAL,
    RES_IMG_DITHER,
    RES_IMG_GRADIENT,
    RES_IMG_SCROLLER_GRADIENT,

    // See https://stackoverflow.com/a/11090007/891846
    IMAGES_ENUM_SIZE
};

enum SpriteImagesEnum {
    RES_SPRITE_ISO_S_0,
    RES_SPRITE_ISO_S_1,
    RES_SPRITE_ISO_S_2,
    RES_SPRITE_ISO_S_3,
    RES_SPRITE_ISO_S_4,
    RES_SPRITE_ISO_S_5,
    RES_SPRITE_ISO_S_6,

    RES_SPRITE_ISO_P_0,
    RES_SPRITE_ISO_P_1,
    RES_SPRITE_ISO_P_2,
    RES_SPRITE_ISO_P_3,
    RES_SPRITE_ISO_P_4,
    RES_SPRITE_ISO_P_5,

    RES_SPRITE_ISO_E_0,
    RES_SPRITE_ISO_E_1,
    RES_SPRITE_ISO_E_2,
    RES_SPRITE_ISO_E_3,
    RES_SPRITE_ISO_E_4,
    RES_SPRITE_ISO_E_5,
    RES_SPRITE_ISO_E_6,

    RES_SPRITE_ISO_C_0,
    RES_SPRITE_ISO_C_1,
    RES_SPRITE_ISO_C_2,
    RES_SPRITE_ISO_C_3,
    RES_SPRITE_ISO_C_4,
    RES_SPRITE_ISO_C_5,

    RES_SPRITE_ISO_T_0,
    RES_SPRITE_ISO_T_1,
    RES_SPRITE_ISO_T_2,
    RES_SPRITE_ISO_T_3,
    RES_SPRITE_ISO_T_4,

    RES_SPRITE_ISO_R_0,
    RES_SPRITE_ISO_R_1,
    RES_SPRITE_ISO_R_2,
    RES_SPRITE_ISO_R_3,
    RES_SPRITE_ISO_R_4,
    RES_SPRITE_ISO_R_5,
    RES_SPRITE_ISO_R_6,
    RES_SPRITE_ISO_R_7,
    RES_SPRITE_ISO_R_8,

    RES_SPRITE_ISO_O_0,
    RES_SPRITE_ISO_O_1,
    RES_SPRITE_ISO_O_2,
    RES_SPRITE_ISO_O_3,
    RES_SPRITE_ISO_O_4,
    RES_SPRITE_ISO_O_5,

    RES_SPRITE_ISO_X_0,
    RES_SPRITE_ISO_X_1,
    RES_SPRITE_ISO_X_2,
    RES_SPRITE_ISO_X_3,
    RES_SPRITE_ISO_X_4,
    RES_SPRITE_ISO_X_5,
    RES_SPRITE_ISO_X_6,
    RES_SPRITE_ISO_X_7,
    RES_SPRITE_ISO_X_8,
    RES_SPRITE_ISO_X_9,
    RES_SPRITE_ISO_X_10,

    SPRITE_IMAGES_ENUM_SIZE
};

void fw_resource_init();

fw_image *getImages();
fw_font_face *getFontFace();

#endif
