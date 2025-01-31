#include "resource.h"
#include "fw/pixels.h"
#include "fw/draw.h"
#include "dat/fonts/font_pixels.h"
#include "dat/fonts/font_meta.h"
#include "dat/images/bayer_vertical_pixels.h"
#include "dat/images/spritesheet_pixels.h"
#include "dat/images/gradient_pixels.h"

static fw_image _images[IMAGES_ENUM_SIZE];
static fw_sprite_image _spriteImages[SPRITE_IMAGES_ENUM_SIZE];

static void generateImages(void) {
    fw_vec4i color = {255,255,255,255};
    int w, h, bpp=4;
    unsigned char *buffer;

    w = 2, h = 2, buffer = calloc(w*h*4, sizeof(unsigned char));
    fw_draw_pixel(0,0,  &color, buffer, w, h, bpp);
    fw_draw_pixel(1,1,  &color, buffer, w, h, bpp);
    fw_image_initRGBA(&_images[RES_IMG_DITHER], w, h, buffer);

    // Scroller gradient.
    w = 16, h = 16, buffer = calloc(w*h*4, sizeof(unsigned char));
    for (int i=0; i<h/2; i++) {
        int v = 255-i*255/h;
        fw_vec4i c = {v,v,v,255};
        fw_draw_line(0,i,16,i,&c, buffer, w, h, bpp);
    }
    for (int i=h/2; i<h; i++) {
        int v = i*255/h;
        fw_vec4i c = {v,v,v,255};
        fw_draw_line(0,i,16,i,&c, buffer, w, h, bpp);
    }
    fw_image_initRGBA(&_images[RES_IMG_SCROLLER_GRADIENT], w, h, buffer);
}

static void initImages(void) {
    fw_image_setTextureWrapParamClamp();

    fw_image_initRGBA(&_images[RES_IMG_SPRITE_SHEET], SPRITESHEET_PIXELS_WIDTH, SPRITESHEET_PIXELS_HEIGHT, _spritesheetPixels);
    _images[RES_IMG_SPRITE_SHEET].sprites = _spriteImages;
    _images[RES_IMG_SPRITE_SHEET].numSprites = LEN(_spriteImages);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_S_0, 0,0,  16,2);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_S_1, 0,3,  16,11);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_S_2, 0,15, 16,2);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_S_3, 0,18, 16,13);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_S_4, 0,32, 16,4);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_S_5, 0,37, 16,10);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_S_6, 0,48, 16,5);

    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_P_0, 16,0,  18,2);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_P_1, 16,3,  18,11);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_P_2, 16,15, 18,2);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_P_3, 16,18, 18,20);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_P_4, 16,39, 18,7);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_P_5, 16,47, 18,8);

    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_E_0, 36,0,  16,2);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_E_1, 36,3,  16,11);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_E_2, 36,15, 16,2);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_E_3, 36,18, 16,20);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_E_4, 36,39, 16,6);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_E_5, 36,46, 16,11);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_E_6, 36,58, 16,5);

    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_C_0, 54,0,  16,2);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_C_1, 54,3,  16,22);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_C_2, 54,26, 16,2);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_C_3, 54,29, 16,2);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_C_4, 54,32, 16,20);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_C_5, 54,53, 16,5);

    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_T_0, 72,0,  16,2);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_T_1, 72,3,  16,8);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_T_2, 72,12, 16,2);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_T_3, 72,15, 16,17);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_T_4, 72,33, 16,20);

    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_R_0, 88,0,  18,2);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_R_1, 88,3,  18,10);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_R_2, 88,14, 18,2);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_R_3, 88,17, 18,20);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_R_4, 88,38, 18,7);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_R_5, 88,46, 18,7);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_R_6, 88,54, 18,8);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_R_7, 88,63, 18,8);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_R_8, 88,72, 18,13);

    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_O_0, 108,0,  16,2);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_O_1, 108,3,  16,22);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_O_2, 108,26, 16,2);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_O_3, 108,29, 16,11);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_O_4, 108,41, 16,20);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_O_5, 108,62, 16,5);

    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_X_0, 126,0,  16,2);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_X_1, 126,3,  16,5);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_X_2, 126,9,  16,8);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_X_3, 126,18, 16,2);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_X_4, 126,21, 16,4);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_X_5, 126,26, 16,3);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_X_6, 126,30, 16,11);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_X_7, 126,42, 16,10);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_X_8, 126,53, 16,5);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_X_9, 126,59, 16,6);
    fw_image_initSpriteImage(&_images[RES_IMG_SPRITE_SHEET], RES_SPRITE_ISO_X_10,126,66, 16,7);

    fw_image_setTextureWrapParamRepeat();

    fw_image_initRGBA(&_images[RES_IMG_GRADIENT], GRADIENT_PIXELS_WIDTH, GRADIENT_PIXELS_HEIGHT, _gradientPixels);
}

static void initBayer(void) {
    fw_image_initRGBA(&_images[RES_IMG_BAYER_VERTICAL], BAYER_VERTICAL_PIXELS_WIDTH, BAYER_VERTICAL_PIXELS_HEIGHT, _bayerVerticalPixels);
    // Clamp currently active texture horizontally to avoid repeat artifacts when translating to non-integer positions.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
}

static void initFonts(void) {
    fw_image_initRGBA(&_images[RES_IMG_FONT], FONT_PIXELS_WIDTH, FONT_PIXELS_HEIGHT, _fontPixels);
    fw_font_initFontFace(&_fontFace, &_images[RES_IMG_FONT]);
}

void fw_resource_init() {
    // Images.
    initImages();
    initBayer();
    initFonts();
    generateImages();
}

fw_image *getImages() {
    return _images;
}

fw_font_face *getFontFace() {
    return &_fontFace;
}
