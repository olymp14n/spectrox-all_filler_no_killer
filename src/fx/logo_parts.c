#include "logo_parts.h"
#include <math.h>
#include "../config/config.h"
#include "../fw/easing.h"
#include "../fw/math.h"
#include "../fw/render.h"
#include "../resource.h"

typedef struct {
    int isAccentColor;
    fw_vec4f initialPosition;
    fw_vec4f finalPosition;
    fw_vec4f currentPosition;
    fw_vec4f isHidden;
    int spriteIdx;
} letter_part;

typedef struct {
    fw_vec3f positionOffset;
    int numParts;
    letter_part *letterParts;
} letter;

static letter _letters[8];
static int _numLetters = LEN(_letters);

int _topPartIndexes[] = {
    RES_SPRITE_ISO_S_0,
    RES_SPRITE_ISO_P_0,
    RES_SPRITE_ISO_E_0,
    RES_SPRITE_ISO_C_0,
    RES_SPRITE_ISO_T_0,
    RES_SPRITE_ISO_R_0,
    RES_SPRITE_ISO_O_0,
    RES_SPRITE_ISO_X_0,
};
const int _numTopParts = LEN(_topPartIndexes);

static void fx_logo_parts_initPositions(void) {
    int numParts = 0;
    int letterIdx = 0;
    int partIdx = 0;
    int spriteIdx = 0;

    // S
    spriteIdx = RES_SPRITE_ISO_S_0;
    numParts = 7;
    _letters[letterIdx].numParts = numParts;
    _letters[letterIdx].letterParts = calloc(numParts, sizeof(letter_part));

    _letters[letterIdx].letterParts[partIdx].isAccentColor = 1;
    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        0,0
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        0,0
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        0,3
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        0,6
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        0,17
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        0,16
    };

    _letters[letterIdx].letterParts[partIdx].isAccentColor = 1;
    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        0,21
    };

    // P
    spriteIdx = RES_SPRITE_ISO_P_0;
    numParts = 6;
    letterIdx++;
    partIdx = 0;

    _letters[letterIdx].numParts = numParts;
    _letters[letterIdx].letterParts = calloc(numParts, sizeof(letter_part));

    _letters[letterIdx].letterParts[partIdx].isAccentColor = 1;
    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        16,0
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        16,0
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        16,3
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        16,6
    };

    _letters[letterIdx].letterParts[partIdx].isAccentColor = 1;
    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        16,10
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        16,18
    };

    // E
    spriteIdx = RES_SPRITE_ISO_E_0;
    numParts = 7;
    letterIdx++;
    partIdx = 0;

    _letters[letterIdx].numParts = numParts;
    _letters[letterIdx].letterParts = calloc(numParts, sizeof(letter_part));

    _letters[letterIdx].letterParts[partIdx].isAccentColor = 1;
    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        36,0
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        36,0
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        36,3
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        36,6
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        36,16
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        36,15
    };

    _letters[letterIdx].letterParts[partIdx].isAccentColor = 1;
    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        36,21
    };

    // C
    spriteIdx = RES_SPRITE_ISO_C_0;
    numParts = 6;
    letterIdx++;
    partIdx = 0;

    _letters[letterIdx].numParts = numParts;
    _letters[letterIdx].letterParts = calloc(numParts, sizeof(letter_part));

    _letters[letterIdx].letterParts[partIdx].isAccentColor = 1;
    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        54,0
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        54,0
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        54,3
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        54,6
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        54,6
    };

    _letters[letterIdx].letterParts[partIdx].isAccentColor = 1;
    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        54,21
    };

    // T
    spriteIdx = RES_SPRITE_ISO_T_0;
    numParts = 5;
    letterIdx++;
    partIdx = 0;

    _letters[letterIdx].numParts = numParts;
    _letters[letterIdx].letterParts = calloc(numParts, sizeof(letter_part));

    _letters[letterIdx].letterParts[partIdx].isAccentColor = 1;
    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        72,0
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        72,0
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        72,6
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        72,6
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        72,6
    };

    // R
    spriteIdx = RES_SPRITE_ISO_R_0;
    numParts = 9;
    letterIdx++;
    partIdx = 0;

    _letters[letterIdx].numParts = numParts;
    _letters[letterIdx].letterParts = calloc(numParts, sizeof(letter_part));

    _letters[letterIdx].letterParts[partIdx].isAccentColor = 1;
    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        88,0
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        88,0
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        88,3
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        88,6
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        88,6
    };

    _letters[letterIdx].letterParts[partIdx].isAccentColor = 1;
    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        88,10
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        88,18
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        88,15
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        88,13
    };

    // O
    spriteIdx = RES_SPRITE_ISO_O_0;
    numParts = 6;
    letterIdx++;
    partIdx = 0;

    _letters[letterIdx].numParts = numParts;
    _letters[letterIdx].letterParts = calloc(numParts, sizeof(letter_part));

    _letters[letterIdx].letterParts[partIdx].isAccentColor = 1;
    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        108,0
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        108,0
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        108,3
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        108,6
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        108,6
    };

    _letters[letterIdx].letterParts[partIdx].isAccentColor = 1;
    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        108,21
    };

    // X
    spriteIdx = RES_SPRITE_ISO_X_0;
    numParts = 11;
    letterIdx++;
    partIdx = 0;

    _letters[letterIdx].numParts = numParts;
    _letters[letterIdx].letterParts = calloc(numParts, sizeof(letter_part));

    _letters[letterIdx].letterParts[partIdx].isAccentColor = 1;
    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        126,0
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        126,0
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        126,3
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        126,6
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        126,6
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        126,11
    };

    _letters[letterIdx].letterParts[partIdx].isAccentColor = 1;
    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        126,9
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        126,16
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        126,21
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        126,20
    };

    _letters[letterIdx].letterParts[partIdx].spriteIdx = spriteIdx++;
    _letters[letterIdx].letterParts[partIdx++].finalPosition = (fw_vec4f) {
        126,19
    };
}

static void fx_logo_parts_initAnim(fw_animation *anim) {
    anim->numKeyframes = SPRITE_IMAGES_ENUM_SIZE;
    anim->keyframes = calloc(anim->numKeyframes, sizeof(fw_keyframe));
    fw_keyframe *keys = anim->keyframes;

    int letterOrderMap[] = {7,5,1,4,3,2,0,6};

    // Create anim keysframes.
    srand(3);
    int keyIdx = 0;
    for (int j=0; j<_numLetters; j++) {
        float r =  fw_math_randf(0,1);
        int letterIdx = letterOrderMap[j];
        for (int i=0; i<_letters[letterIdx].numParts; i++) {
            letter_part *letterPart = &_letters[letterIdx].letterParts[i];
            letterPart->initialPosition = letterPart->finalPosition;
            letterPart->initialPosition.y += 70;

            letterPart->currentPosition = letterPart->initialPosition;

            keys[keyIdx].timeStart = j*.6 + (i*1.15);
            keys[keyIdx].timeEnd =   j*.6 + (i*1.15) + 2.5 + r;
            keys[keyIdx].from = letterPart->initialPosition;
            keys[keyIdx].to = letterPart->finalPosition;
            keys[keyIdx].easing_func = ExponentialEaseIn;
            keys[keyIdx].value = &letterPart->currentPosition;
            keyIdx++;
        }
    }
}

static void flicker(float startTime, float duration, int isHidden, letter_part *letterPart, fw_keyframe *keys, int keyIdx) {
    keys[keyIdx].timeStart = startTime;
    keys[keyIdx].timeEnd =   startTime+duration;
    keys[keyIdx].from = (fw_vec4f) {isHidden};
    keys[keyIdx].to = (fw_vec4f) {isHidden};
    keys[keyIdx].easing_func = LinearInterpolation;
    keys[keyIdx].value = &letterPart->isHidden;
}

void fx_logo_parts_initEndAnim(fw_animation *anim) {
    const int numKeyFramesPerPart = 15;
    anim->numKeyframes = SPRITE_IMAGES_ENUM_SIZE * numKeyFramesPerPart;
    anim->keyframes = calloc(anim->numKeyframes, sizeof(fw_keyframe));
    fw_keyframe *keys = anim->keyframes;

    srand(123);

    int keyIdx = 0;
    for (int j=0; j<_numLetters; j++) {
        for (int i=0; i<_letters[j].numParts; i++) {
            letter_part *letterPart = &_letters[j].letterParts[i];

            float r = fw_math_randf(0, 1) + fw_math_randf(0, 1);
            r += 1.5;
            flicker(r+1.0, .1, 1, letterPart, keys, keyIdx++);
            flicker(r+1.2, .1, 0, letterPart, keys, keyIdx++);
            flicker(r+1.4, .1, 1, letterPart, keys, keyIdx++);
            flicker(r+1.6, .1, 0, letterPart, keys, keyIdx++);
            flicker(r+1.8, .1, 1, letterPart, keys, keyIdx++);
            flicker(r+2.0, .1, 0, letterPart, keys, keyIdx++);

            flicker(r+2.2, .05, 1, letterPart, keys, keyIdx++);
            flicker(r+2.3, .05, 0, letterPart, keys, keyIdx++);
            flicker(r+2.4, .05, 1, letterPart, keys, keyIdx++);
            flicker(r+2.5, .05, 0, letterPart, keys, keyIdx++);

            flicker(r+2.6, .05, 1, letterPart, keys, keyIdx++);
            flicker(r+2.7, .05, 0, letterPart, keys, keyIdx++);
            flicker(r+2.8, .05, 1, letterPart, keys, keyIdx++);
            flicker(r+2.9, .05, 0, letterPart, keys, keyIdx++);

            flicker(r+3.0, .05, 1, letterPart, keys, keyIdx++);
        }
    }
}

void fx_logo_parts_init(fw_animation *anim) {
    fx_logo_parts_initPositions();
    fx_logo_parts_initAnim(anim);
}

static int isTopPart(int spriteIdx) {
    for (int i=0; i<_numTopParts; i++) {
        if (spriteIdx == _topPartIndexes[i]) {
            return 1;
        }
    }
    return 0;
}

void fx_logo_parts_render(int isRenderTopPart, int isRenderOnlyNonAccentParts, fw_vec4f color, fw_timer_data *time) {
    fw_image *img = &getImages()[RES_IMG_SPRITE_SHEET];
    fw_image_renderBegin(img, 1);
    glColor4ub(color.x, color.y, color.z, color.w);

    //Center logo. Logo is 142x26 when assembled.
    glTranslatef(-71 + FW_RENDER_WIDTH*.5f, -21 + FW_RENDER_HEIGHT*.5f,0);

    for (int j=0; j<_numLetters; j++) {
        for (int i=0; i<_letters[j].numParts; i++) {
            letter_part *letterPart = &_letters[j].letterParts[i];

            if (letterPart->isHidden.x && !isTopPart(letterPart->spriteIdx)) {
                continue;
            }

            if (isRenderOnlyNonAccentParts && letterPart->isAccentColor) {
                continue;
            }

            if (!isRenderTopPart && isTopPart(letterPart->spriteIdx)) {
                continue;
            }

            glPushMatrix();
            glTranslatef(letterPart->currentPosition.x,letterPart->currentPosition.y,0);
            fw_image_putSpriteImage(&img->sprites[ letterPart->spriteIdx ]);

            if (letterPart->isAccentColor) {
                fx_logo_parts_renderAccent(i,j, img, letterPart->spriteIdx, time);
            }
            glPopMatrix();
        }
    }
    fw_image_renderEnd();
}

void fx_logo_parts_renderAccent(int i, int j, fw_image *img, int spriteIdx, fw_timer_data *time) {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    float jadd = j * 2.3f;
    float iadd = i * 2.3f;

    glColor4f(1,0,0,1);
    glPushMatrix();
    glTranslatef(sinf(jadd+iadd+time->elapsed*8)*1,cosf(jadd+iadd+time->elapsed*4)*1,0);
    fw_image_putSpriteImage(&img->sprites[ spriteIdx ]);
    glPopMatrix();

    glPushMatrix();
    glColor4f(0,0,1,1);
    glTranslatef(sinf(jadd+iadd+1.1+time->elapsed*4)*1,cosf(jadd+iadd+1.1+time->elapsed*8)*1,0);
    fw_image_putSpriteImage(&img->sprites[ spriteIdx ]);
    glPopMatrix();

    fw_render_defaultBlendMode();
    glColor4f(1,1,1,1);
}

int *fx_logo_parts_getTopPartIndexes(void) {
    return _topPartIndexes;
}

