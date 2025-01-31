#include "scene_0.h"
#include <GL/glu.h>
#include <math.h>
#include "config/config.h"
#include "resource.h"
#include "fw/types.h"
#include "fw/render.h"
#include "fw/lut.h"
#include "fw/easing.h"
#include "fw/animation.h"
#include "fw/font.h"
#include "fw/projection.h"
#include "fw/sync.h"
#include "fw/math.h"
#include "fw/quad.h"
#include "fw/stencil.h"
#include "fw/sync.h"
#include "fw/broadcast.h"
#include "fx/logo_parts.h"
#include "fx/lines.h"
#include "fx/starfield_3d.h"

static fw_sync_data _syncData;

static fx_lines _lines;
static fx_lines _lines2;

static fx_starfield_3d _starfield;

enum anim_names_enum {
    ANIM_START,
    ANIM_LOGO_IN,
    ANIM_LOGO_OUT,
    ANIM_STARFIELD,
    ANIM_END,
};

///////////////////////////////////////////////////////////////////////////////
// STRINGS
///////////////////////////////////////////////////////////////////////////////
const char _titleText[] = "ALL FILLER - NO KILLER";

const char _scrollText[] =
    "ALL FILLER - NO KILLER                                    "
    "SPECTROX IS BACK AT MOUNTAINBYTES 2025 WITH A LITTLE COMPOFILLER ! ! ! "
    "            "
    "               "
    "CODE, GRAPHICS, AND MUSIC BY OLYMPIAN "
    ". . .       "
    "               "
    "EVEN THOUGH I CAN\'T BE THERE IN PERSON FOR THE SWISS SCENE MADNESS, "
    "HERE\'S A TINY REMOTE ENTRY TO SAY HI :)    "
    "SENDING HUGS FROM BERN !  HAVE A GREAT PARTY ! ! !"
    "               "
    "GREETINGS FLY OUT TO "
    ". . .          "
    "ABYSS - AGIMA - ALCATRAZ - ANDROMEDA - ARTSTATE - ASD - CALODOX - COMPLEX - CONSPIRACY - DESIRE - "
    "ECHTZEIT - FAIRLIGHT - FARBRAUSCH - FROZAK - GASPODE - HAUJOBB - ISTARI - LEMON. - "
    "LOGICOMA - MELON - MFX - MOODS PLATEAU - OXYGENE - RAZOR 1911 - REBELS - SCA - SCOOPEX - "
    "SMFX - SPACEBALLS - SPREADPOINT - TEADRINKER - TEK - TITAN - TPOLM - TRBL - TRSI - VANTAGE "
    ". . .       "
    "               "
    "THANKS FOR WATCHING AND SEE YOU IN THE NEXT ONE ! "
    ". . ."
    ;

///////////////////////////////////////////////////////////////////////////////
// INITIAL KEYFRAME VARIABLES
///////////////////////////////////////////////////////////////////////////////
static const fw_vec4f _linesMaskTopPosInit = {0};
static const fw_vec4f _linesMaskBottomPosInit = {FW_RENDER_HEIGHT*.5f};

static const fw_vec4f _logoTopSineAmpSpeedInit = {20,2};
static const fw_vec4f _logoTopOffsetInit = {0,13};

static const fw_vec4f _titleTextAlphaInit = {0};
static const fw_vec4f _logoBoxLinesOffInit = {FW_RENDER_WIDTH,-FW_RENDER_WIDTH};

static const fw_vec4f _logoTopMaskPosInit = {0};
static const fw_vec4f _logoTopMaskPosFinal = {160};

static const fw_vec4f _logoBoxBGAlphaInit = {0};
static const fw_vec4f _logoBoxBGDimInit = {0,104,FW_RENDER_WIDTH,64};

static const fw_vec4f _flashFadeAlphaInit = {255};
static const fw_vec4f _starfieldLogoBoxBGOffsetInit = {0};

static const fw_vec4f _logoLeftMaskPosInit = {-28};
static const fw_vec4f _logoLeftMaskPosFinal = {-105};

static const fw_vec4f _logoRightMaskPosInit = {28+FW_RENDER_WIDTH-101};
static const fw_vec4f _logoRightMaskPosFinal = {FW_RENDER_WIDTH + 5};

static const fw_vec4f _scrollerOffsetInit = {117};

///////////////////////////////////////////////////////////////////////////////
// KEY FRAME VARIABLES
///////////////////////////////////////////////////////////////////////////////
static fw_vec4f _bgClearColor = {9/255.f,10/255.f,20/255.f,1};

static fw_vec4f _linesMaskTopPos = _linesMaskTopPosInit;
static fw_vec4f _linesMaskBottomPos = _linesMaskBottomPosInit;

static fw_vec4f _linesMaskLeftPos = _logoLeftMaskPosInit;
static fw_vec4f _linesMaskRightPos = _logoRightMaskPosInit;

static fw_vec4f _logoTopSineAmpSpeed = _logoTopSineAmpSpeedInit;
static fw_vec4f _logoTopOffset = _logoTopOffsetInit;

static fw_vec4f _titleTextAlpha = _titleTextAlphaInit;
static fw_vec4f _logoBoxLinesOff = _logoBoxLinesOffInit;

static fw_vec4f _logoTopMaskPos = _logoTopMaskPosInit;

static fw_vec4f _logoBoxBGAlpha = _logoBoxBGAlphaInit;
static fw_vec4f _logoBoxBGDim = _logoBoxBGDimInit;

static fw_vec4f _flashFadeAlpha = _flashFadeAlphaInit;
static fw_vec4f _starfieldLogoBoxBGOffset = _starfieldLogoBoxBGOffsetInit;

static fw_vec4f _scrollerOffset = _scrollerOffsetInit;

///////////////////////////////////////////////////////////////////////////////
// ANIM START / STOP DECLARATIONS
///////////////////////////////////////////////////////////////////////////////
static void animStartedStart(fw_animation *anim, fw_timer_data *time);
static void animCompletedStart(fw_animation *anim, fw_timer_data *time);

static void animStartedStarfield(fw_animation *anim, fw_timer_data *time);
static void animCompletedStarfield(fw_animation *anim, fw_timer_data *time);

static void animStartedLogoIn(fw_animation *anim, fw_timer_data *time);
static void animCompletedLogoIn(fw_animation *anim, fw_timer_data *time);

static void animStartedEnd(fw_animation *anim, fw_timer_data *time);
static void animCompletedEnd(fw_animation *anim, fw_timer_data *time);

///////////////////////////////////////////////////////////////////////////////
// KEY FRAME CALLBACKS
///////////////////////////////////////////////////////////////////////////////
static void startLogoInAnim(fw_timer_data *time);

///////////////////////////////////////////////////////////////////////////////
// KEY FRAMES
///////////////////////////////////////////////////////////////////////////////

const float __kst = 2;
const float __kso = -.5;
static fw_keyframe _keysStart[] = {

    {.25f, 1.75f, _logoTopMaskPosInit, _logoTopMaskPosFinal, LinearInterpolation, &_logoTopMaskPos},

    {-.4f+3*3.84, -.4f+4*3.84, _linesMaskBottomPosInit, {-37+FW_RENDER_HEIGHT}, LinearInterpolation, &_linesMaskBottomPos},
    {-.4f+4*3.84, -.4f+5*3.84, _linesMaskTopPosInit, {37-FW_RENDER_HEIGHT*.5f}, LinearInterpolation, &_linesMaskTopPos},

    {6*3.84, 6*3.84+3, {-37+FW_RENDER_HEIGHT}, {FW_RENDER_HEIGHT}, LinearInterpolation, &_linesMaskBottomPos},
    {6*3.84, 6*3.84+3, {37-FW_RENDER_HEIGHT*.5f}, {-FW_RENDER_HEIGHT*.5f}, LinearInterpolation, &_linesMaskTopPos},

    {6*3.84, 6*3.84+3, _logoLeftMaskPosInit, _logoLeftMaskPosFinal, LinearInterpolation, &_linesMaskLeftPos},
    {6*3.84, 6*3.84+3, _logoRightMaskPosInit, _logoRightMaskPosFinal, LinearInterpolation, &_linesMaskRightPos},


    {1*3.84, 1*3.84, _logoTopSineAmpSpeedInit, {3,60}, LinearInterpolation, &_logoTopSineAmpSpeed},
    {1*3.84, 1*3.84+.5, _logoTopOffsetInit, {0,33}, ElasticEaseOut, &_logoTopOffset},

    {2*3.84, 2*3.84, {3,60}, _logoTopSineAmpSpeedInit, LinearInterpolation, &_logoTopSineAmpSpeed},
    {2*3.84, 2*3.84+.5, {0,33}, _logoTopOffsetInit, ElasticEaseOut, &_logoTopOffset},

    {3*3.84, 3*3.84, _logoTopSineAmpSpeedInit, {3,60}, LinearInterpolation, &_logoTopSineAmpSpeed},
    {3*3.84, 3*3.84+.5, _logoTopOffsetInit, {0,33}, ElasticEaseOut, &_logoTopOffset},

    {4*3.84, 4*3.84, {3,60}, {10,10}, LinearInterpolation, &_logoTopSineAmpSpeed},
    {4*3.84, 4*3.84+.5, {0,33}, {0,-25}, ElasticEaseOut, &_logoTopOffset},

    {5*3.84, 5*3.84, {10,10}, {3,60}, LinearInterpolation, &_logoTopSineAmpSpeed},
    {5*3.84, 5*3.84, {0,-25}, _logoTopOffsetInit, LinearInterpolation, &_logoTopOffset},

    {5*3.84 + 3.84*.5, 5*3.84 + 3.84*.5, {3,60}, {15,5}, LinearInterpolation, &_logoTopSineAmpSpeed},
    {5*3.84 + 3.84*.5, 5*3.84 + 3.84*.5 + .5, {0,0}, {0,-20}, ElasticEaseOut, &_logoTopOffset},

    {5*3.84 + 3.84*.5 + 1.44, 5*3.84 + 3.84*.5 + 1.44, {15,5}, {5,60}, LinearInterpolation, &_logoTopSineAmpSpeed},
    {5*3.84 + 3.84*.5 + 1.44, 5*3.84 + 3.84*.5  + 1.44 + .5, {0,10}, {0,33}, ElasticEaseOut, &_logoTopOffset},

    {6*3.84, 6*3.84, {5,60}, _logoTopSineAmpSpeedInit, LinearInterpolation, &_logoTopSineAmpSpeed},
    {6*3.84, 6*3.84+.5, {0,10}, _logoTopOffsetInit, ElasticEaseOut, &_logoTopOffset},


    {__kst+__kso+6*3.84-1, __kst+__kso+6*3.84 + 3-1, _logoTopSineAmpSpeedInit, {0,2}, QuadraticEaseInOut, &_logoTopSineAmpSpeed},
    {__kst+__kso+6*3.84, __kst+__kso+6*3.84 + 2, _logoTopOffsetInit, {0,-8}, QuadraticEaseInOut, &_logoTopOffset},

    {__kso+6*3.84, 0, {0}, {0}, NULL, NULL, startLogoInAnim},


    {10*3.84, 10*3.84+2, _titleTextAlphaInit, {255}, QuadraticEaseOut, &_titleTextAlpha},
    {41, 43, _logoBoxLinesOffInit, {0,0}, QuadraticEaseOut, &_logoBoxLinesOff},
    {41, 43, _logoBoxBGAlphaInit, {255}, LinearInterpolation, &_logoBoxBGAlpha},

    // Artificial wait.
    {12*3.84, 12*3.84, {0}, {0}},
};

static fw_keyframe _keysStarfield[] = {
    {0, 0, {0}, {0}, LinearInterpolation, &_logoBoxBGAlpha},
    {0, 1, _flashFadeAlphaInit, {0}, LinearInterpolation, &_flashFadeAlpha},

    {135.84-2-(12*3.84), 135.84-(12*3.84), {0}, {255}, LinearInterpolation, &_logoBoxBGAlpha},
    {135.84-(12*3.84),   135.84+2.5-(12*3.84), _starfieldLogoBoxBGOffsetInit, {104}, QuadraticEaseOut, &_starfieldLogoBoxBGOffset},
    {135.84-(12*3.84),   135.84+2.5-(12*3.84), _logoBoxBGDimInit, {0,0,FW_RENDER_WIDTH,FW_RENDER_HEIGHT}, QuadraticEaseOut, &_logoBoxBGDim},

    {4, 135.84-(12*3.84), _scrollerOffsetInit, {-4250}, LinearInterpolation, &_scrollerOffset},
};

static fw_keyframe _keysEnd[] = {
    {0,0, _logoTopMaskPosInit, _logoTopMaskPosFinal, LinearInterpolation, &_logoTopMaskPos},
    {0,0, _logoTopSineAmpSpeedInit, {0,2}, QuadraticEaseInOut, &_logoTopSineAmpSpeed},
    {0,0, _logoTopOffsetInit, {0,-8}, QuadraticEaseInOut, &_logoTopOffset},

    {7.5,7.5, _logoTopSineAmpSpeedInit, _logoTopSineAmpSpeedInit, QuadraticEaseInOut, &_logoTopSineAmpSpeed},
    {7.5,7.75, {0,-8}, _logoTopOffsetInit, ElasticEaseOut, &_logoTopOffset},


    {11, 12.5, _logoTopMaskPosFinal, _logoTopMaskPosInit, LinearInterpolation, &_logoTopMaskPos},

    // Artificial wait.
    {15, 15, {0}, {0}},
};

///////////////////////////////////////////////////////////////////////////////
// ANIMS
///////////////////////////////////////////////////////////////////////////////

static fw_animation _anims[] = {
    [ANIM_START] = {
        .isAutostart = 1,
        .keyframes = _keysStart,
        .numKeyframes = LEN(_keysStart),
        .started_proc = animStartedStart,
        .completed_proc = animCompletedStart,
    },
    [ANIM_STARFIELD] = {
        .isAutostart = 0,
        .keyframes = _keysStarfield,
        .numKeyframes = LEN(_keysStarfield),
        .started_proc = animStartedStarfield,
        .completed_proc = animCompletedStarfield,
    },
    [ANIM_LOGO_IN] = {
        .isAutostart = 0,
        .started_proc = animStartedLogoIn,
        .completed_proc = animCompletedLogoIn,
    },
    [ANIM_LOGO_OUT] = {
        .isAutostart = 0,
    },
    [ANIM_END] = {
        .isAutostart = 0,
        .keyframes = _keysEnd,
        .numKeyframes = LEN(_keysEnd),
        .started_proc = animStartedEnd,
        .completed_proc = animCompletedEnd,
    },
};

static fw_animation_schedule _animSchedule = {
    _anims,
    LEN(_anims)
};

static BOOL isRunning(enum anim_names_enum animNameEnum) {
    return _animSchedule.animations[animNameEnum].state == RUNNING;
}


static void startLogoInAnim(fw_timer_data *time) {
    fw_animation_start(&_anims[ANIM_LOGO_IN], time);
}

///////////////////////////////////////////////////////////////////////////////
// ANIM START / STOP IMPLEMENTATIONS
///////////////////////////////////////////////////////////////////////////////
static void animStartedStart(fw_animation *anim, fw_timer_data *time) {
}

static void animCompletedStart(fw_animation *anim, fw_timer_data *time) {
    fw_animation_start(&_anims[ANIM_STARFIELD], time);
}

static void animStartedStarfield(fw_animation *anim, fw_timer_data *time) {
}

static void animCompletedStarfield(fw_animation *anim, fw_timer_data *time) {
    fw_animation_start(&_anims[ANIM_END], time);
}

static void animStartedLogoIn(fw_animation *anim, fw_timer_data *time) {
}

static void animCompletedLogoIn(fw_animation *anim, fw_timer_data *time) {
}

static void animStartedEnd(fw_animation *anim, fw_timer_data *time) {
    _bgClearColor = (fw_vec4f) {
        0,0,0,1
    };
    fw_animation_start(&_anims[ANIM_LOGO_OUT], time);
}

static void animCompletedEnd(fw_animation *anim, fw_timer_data *time) {
    fw_broadcast_exit();
}

///////////////////////////////////////////////////////////////////////////////
// MUSIC SYNC
///////////////////////////////////////////////////////////////////////////////

static float _syncLogoHighlightAlpha = 0;

static void triggerSyncKick(int beatNumber, fw_timer_data *time) {
}

static void triggerSyncSnare(int beatNumber, fw_timer_data *time) {
    if (beatNumber >= 384) {
        _syncLogoHighlightAlpha = 128;
    }
}

static void triggerSyncKickOrSnare(int beatNumber, fw_timer_data *time) {
}

static void triggerSync(int beatNumber, fw_timer_data *time) {
    int isKick = beatNumber % 8 == 0;
    int isSnare = (beatNumber+4) % 8 == 0;

    if (beatNumber < 384
            && (beatNumber == 5*64 + 56
                || beatNumber == 5*64 + 58
                || beatNumber == 5*64 + 59
                || beatNumber == 5*64 + 61
                || beatNumber == 5*64 + 62
                || beatNumber == 5*64 + 63)
       ) {
        _syncLogoHighlightAlpha = 200;
    }

    if (isKick) {
        triggerSyncKick(beatNumber, time);
    }

    if (isSnare) {
        triggerSyncSnare(beatNumber, time);
    }

    if (isKick || isSnare) {
        triggerSyncKickOrSnare(beatNumber, time);
    }
}

///////////////////////////////////////////////////////////////////////////////
// COMMON
///////////////////////////////////////////////////////////////////////////////

static fw_timer_data animTime(enum anim_names_enum animNameEnum, fw_timer_data *time) {
    fw_timer_data animTime = *time;
    animTime.elapsed = time->elapsed - _animSchedule.animations[animNameEnum].timeStartedAt;
    return animTime;
}

///////////////////////////////////////////////////////////////////////////////
// INIT
///////////////////////////////////////////////////////////////////////////////

void scene_0_init() {
    fw_animation_resetAnimationSchedule(&_animSchedule);

    fw_projection_initPixelPerfectZ();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_COLOR_MATERIAL);

    // Set up music sync: 125 BPM, 6 SPEED. Trigger every row.
    fw_sync_init2(&_syncData, 125, 6, 1, triggerSync);

    fx_logo_parts_init(&_anims[ANIM_LOGO_IN]);
    fx_logo_parts_initEndAnim(&_anims[ANIM_LOGO_OUT]);

    fx_lines_init(10, &_lines);
    fx_lines_init(10, &_lines2);

    fx_starfield_3d_init(1500, &_starfield);
}

///////////////////////////////////////////////////////////////////////////////
// EXECUTE
///////////////////////////////////////////////////////////////////////////////

// ++++++++++++ //
// SCENE: LINES
// ++++++++++++ //

static void renderLinesBG(void) {
    fw_projection_ortho();

    glColor3ub(0,0,0);
    fw_quad_put(0,100, FW_RENDER_WIDTH, 70);

    fw_image_renderBegin(&getImages()[RES_IMG_GRADIENT], 1);

    glPushMatrix();
    glTranslatef(0,0,0);
    glScalef(350,1.85,1);
    fw_image_putImage(&getImages()[RES_IMG_GRADIENT]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,270,0);
    glScalef(350,-1.85,1);
    fw_image_putImage(&getImages()[RES_IMG_GRADIENT]);
    glPopMatrix();

    fw_image_renderEnd();

    fw_image_renderBegin(&getImages()[RES_IMG_DITHER], 1);
    glColor4f(0,0,0,1);
    glTranslatef(0,0,0);
    fw_image_putImageExt(&getImages()[RES_IMG_DITHER], 175,0, 135,0);
    fw_image_renderEnd();
}

static void renderLines(fw_timer_data *time) {
    fx_lines_update(2, &_lines, time);
    fx_lines_update(2, &_lines2, time);

    fw_projection_perspective();

    glColor3ub(0,0,0);
    glPushMatrix();
    glTranslatef(0,1,0);
    fx_lines_render(&_lines);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,-1,0);
    fx_lines_render(&_lines2);
    glPopMatrix();

    glColor3f(0,0,0);
    glLineWidth(2);
    glPushMatrix();
    glTranslatef(0,-1,0);
    glBegin(GL_LINES);
    for (float i=-5; i<5; i+=1) {
        glVertex3f(i,0,0);
        glVertex3f(i,0,-10);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,1,0);
    glBegin(GL_LINES);
    for (float i=-5; i<5; i+=1)  {
        glVertex3f(i,0,0);
        glVertex3f(i,0,-10);
    }
    glEnd();
    glPopMatrix();
}

static void renderLinesMask(void) {
    fw_projection_ortho();

    float h = FW_RENDER_HEIGHT*.5f;

    glColor3ub(0,0,0);
    fw_quad_put(0, _linesMaskTopPos.x, FW_RENDER_WIDTH, h);
    fw_quad_put(0, _linesMaskBottomPos.x, FW_RENDER_WIDTH, h);
    fw_quad_put(_linesMaskLeftPos.x, 0, 100, FW_RENDER_HEIGHT);
    fw_quad_put(_linesMaskRightPos.x, 0, 120, FW_RENDER_HEIGHT);
}

static void renderLogoTop(fw_timer_data *time) {
    const int *topPartIndexes = fx_logo_parts_getTopPartIndexes();
    const int topPartXPositions[] = {
        0,16,36,54,72,88,108,126
    };

    fw_image *img = &getImages()[RES_IMG_SPRITE_SHEET];
    fw_image_renderBegin(&getImages()[RES_IMG_SPRITE_SHEET],1);

    glTranslatef(-71+FW_RENDER_WIDTH*.5f + _logoTopOffset.x, -13+FW_RENDER_HEIGHT*.5f + _logoTopOffset.y, 0);
    for (int i=0; i<8; i++) {
        int spriteIdx = topPartIndexes[i];
        glPushMatrix();
        glTranslatef(0,_logoTopSineAmpSpeed.x*sinf(i + _logoTopSineAmpSpeed.y*time->elapsed),0);
        glTranslatef(topPartXPositions[i],0,0);
        fw_image_putSpriteImage(&img->sprites[spriteIdx]);
        fx_logo_parts_renderAccent(i,0,img,spriteIdx,time);
        glPopMatrix();
    }

    fw_image_renderEnd();
}

static void renderLogoTopMask(void) {
    if (_logoTopMaskPos.x < _logoTopMaskPosFinal.x) {
        glColor4ub(0,0,0,255);
        fw_quad_put(90 + _logoTopMaskPos.x,100,160,70);
    }
}

static void renderTitleText(void) {
    if (_titleTextAlpha.x <= 0) {
        return;
    }

    fw_font_renderTextBegin(getFontFace());
    {
        glPushMatrix();
        glTranslatef(117,149,0);
        glColor4ub(170,170,170,_titleTextAlpha.x);
        fw_font_renderSingleTextLine(_titleText, getFontFace(), 0,0);
        glPopMatrix();
    }
    fw_font_renderTextEnd();

}

static void renderLogoBoxLines(float topOffX, float bottomOffX, float offY) {
    // Top line. Light Gray.
    glColor4ub(120,120,120,255);
    glPushMatrix();
    glTranslatef(topOffX,82-offY,0);
    fw_quad_put(0,20,FW_RENDER_WIDTH,1);
    glPopMatrix();

    // Bottom line. Light Gray.
    glPushMatrix();
    glTranslatef(bottomOffX,146+offY,0);
    fw_quad_put(0,20,FW_RENDER_WIDTH,1);
    glPopMatrix();

    // Top line. Dark Gray.
    glColor4ub(80,80,80,255);
    glPushMatrix();
    glTranslatef(topOffX,83-offY,0);
    fw_quad_put(0,20,FW_RENDER_WIDTH,1);
    glPopMatrix();

    // Bottom line. Dark Gray.
    glPushMatrix();
    glTranslatef(bottomOffX,147+offY,0);
    fw_quad_put(0,20,FW_RENDER_WIDTH,1);
    glPopMatrix();
}

static void renderLogoBoxBG(void) {
    if (_logoBoxBGAlpha.x <= 0) {
        return;
    }
    fw_projection_ortho();
    glColor4ub(0,0,0,_logoBoxBGAlpha.x);
    fw_quad_put(_logoBoxBGDim.x,_logoBoxBGDim.y,_logoBoxBGDim.z,_logoBoxBGDim.w);
}

static void renderLogoIn(fw_timer_data *time) {
    fw_stencil_begin();
    fw_stencil_activateStencilBuffer();

    fw_projection_ortho();
    glColor3ub(0,0,0);
    glPushMatrix();
    fw_quad_put(0,183,FW_RENDER_WIDTH, 100);
    glPopMatrix();

    fw_stencil_activateColorBuffer(1);

    fx_logo_parts_render(FALSE,FALSE, (fw_vec4f) {
        255,255,255,255
    }, time);

    fw_stencil_end();
}

static void updateLogoHighlightsSync(fw_timer_data *time) {
    _syncLogoHighlightAlpha = fw_math_lerp(_syncLogoHighlightAlpha, 0.0f, time->delta*4);
}

static void renderLogoHighlights(fw_timer_data *time) {
    if (_syncLogoHighlightAlpha <= 0) {
        return;
    }

    updateLogoHighlightsSync(time);

    fw_vec4f color = {255,255,255, _syncLogoHighlightAlpha};
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    fx_logo_parts_render(TRUE,TRUE, color, time);
    fw_render_defaultBlendMode();
}

static void renderLinesScene(fw_timer_data *time) {
    renderLinesBG();
    renderLines(time);
    renderLinesMask();
    renderLogoBoxBG();
    renderLogoBoxLines(_logoBoxLinesOff.x,_logoBoxLinesOff.y,0);
    renderLogoTop(time);
    renderLogoTopMask();
    renderTitleText();
    renderLogoIn(time);
    renderLogoHighlights(time);
}

// ++++++++++++++++ //
// SCENE: STARFIELD
// ++++++++++++++++ //

static void renderStarfield(fw_timer_data *time) {
    fw_stencil_begin();

    fw_stencil_activateStencilBuffer();

    fw_image_renderBegin(&getImages()[RES_IMG_DITHER], 1);
    glColor4f(0,0,0,1);
    fw_image_putImageExt(&getImages()[RES_IMG_DITHER], 175,0, 135,0);
    fw_image_renderEnd();

    fw_stencil_activateColorBuffer(1);

    fx_starfield_3d_update(&_starfield, time);
    fx_starfield_3d_render(&_starfield, time);

    fw_stencil_end();
}

static void renderStarfieldLogoBox(void) {
    fw_image_renderBegin(&getImages()[RES_IMG_DITHER], 1);
    glColor4f(0,0,0,.8f);
    glTranslatef(-1,102,0);
    fw_image_putImageExt(&getImages()[RES_IMG_DITHER], 176,0, 32,0);
    fw_image_renderEnd();

    renderLogoBoxBG();

    renderLogoBoxLines(0,0,_starfieldLogoBoxBGOffset.x);
}


static void renderFlashFade(void) {
    if (_flashFadeAlpha.x <= 0) {
        return;
    }
    glColor4ub(255,255,255, _flashFadeAlpha.x);
    fw_quad_put(0,0,FW_RENDER_WIDTH, FW_RENDER_HEIGHT);
}

static void renderStarfieldScene(fw_timer_data *time) {
    renderStarfield(time);
    renderStarfieldLogoBox();
    fx_logo_parts_render(TRUE,FALSE, (fw_vec4f) {
        255,255,255,255
    }, time);
    renderLogoHighlights(time);
}

// +++++++++++++++ //
// SCENE: SCROLLER
// +++++++++++++++ //

static void renderScrollerBayerMask(int width) {
    fw_image_renderBegin(&getImages()[RES_IMG_BAYER_VERTICAL], 1);
    glTranslatef(5+width,142,0);
    fw_image_putImageExt(&getImages()[RES_IMG_BAYER_VERTICAL], 1,0, 2,0);
    fw_image_renderEnd();

    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(0,142,0);
    fw_quad_put(0,0,5+width,20);
    glPopMatrix();

    fw_image_renderBegin(&getImages()[RES_IMG_BAYER_VERTICAL], 1);
    glTranslatef(340-width,142,0);
    glScalef(-1,1,1);
    fw_image_putImageExt(&getImages()[RES_IMG_BAYER_VERTICAL], 1,0, 2,0);
    fw_image_renderEnd();

    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(340-width,142,0);
    fw_quad_put(0,0,90,20);
    glPopMatrix();
}

static void renderScrollerGradientShadow(fw_timer_data *time) {
    fw_stencil_begin();
    fw_stencil_activateStencilBuffer();

    fw_font_renderTextBegin(getFontFace());
    {
        glPushMatrix();
        glTranslatef(_scrollerOffset.x,149,0);
        glColor4ub(240,62,200,255);
        fw_font_renderSingleTextLine(_scrollText, getFontFace(), 0,0);
        glPopMatrix();
    }
    fw_font_renderTextEnd();

    glStencilOp(GL_ZERO, GL_ZERO, GL_ZERO);
    renderScrollerBayerMask(0);

    fw_stencil_activateColorBuffer(0);

    fw_image_renderBegin(&getImages()[RES_IMG_SCROLLER_GRADIENT], 1);
    glColor4ub(175,13,140,255);
    glTranslatef(0,145,0);
    fw_image_putImageExt(&getImages()[RES_IMG_SCROLLER_GRADIENT], 23,0, 1, fx_math_triwf(time->elapsed*.2f));
    fw_image_renderEnd();

    fw_stencil_end();
}

static void renderScroller(fw_timer_data *time) {
    fw_stencil_begin();
    fw_stencil_activateStencilBuffer();
    renderScrollerBayerMask(5);
    fw_stencil_activateColorBuffer(1);

    fw_font_renderTextBegin(getFontFace());
    {
        glPushMatrix();
        glTranslatef(_scrollerOffset.x,149,0);
        glTranslatef(0,-1,0);
        glColor4ub(210,210,210,255);
        fw_font_renderSingleTextLine(_scrollText, getFontFace(), 0,0);
        glPopMatrix();
    }
    fw_font_renderTextEnd();

    fw_stencil_end();
}

static void renderScrollerScene(fw_timer_data *time) {
    renderScrollerGradientShadow(time);
    renderScroller(time);
    renderFlashFade();
}

// ++++++++++ //
// SCENE: END
// ++++++++++ //
static void renderEndScene(fw_timer_data *time) {

    if (_logoTopSineAmpSpeed.x == 0) {
        fx_logo_parts_render(TRUE,FALSE, (fw_vec4f) {
            255,255,255,255
        }, time);
    } else {
        renderLogoTop(time);
    }

    renderLogoTopMask();
}

#if FW_SCANLINES_ENABLED
static void renderScanlines(void) {
    fw_render_viewportHiRes(0,0);
    fw_projection_ortho();
    glColor4f(0,0,0,FW_SCANLINES_ALPHA);
    glPushMatrix();
    glLoadIdentity();
    glBegin(GL_LINES);
    for (float i=0; i<FW_WINDOW_HEIGHT/2; i+=1) {
        glVertex2f(0, i);
        glVertex2f(FW_WINDOW_WIDTH, i);
    }
    glEnd();
    glPopMatrix();
}
#endif

void scene_0_execute(fw_timer_data *time) {
    fw_sync_process(&_syncData, time);
    fw_animation_processAnimationSchedule(&_animSchedule, time);

    // Scene time.
    fw_timer_data at;

    // Low-res.
    fw_render_bindTextureBufferBegin();
    {
        //fw_render_viewportLowRes(0,0);

        if (isRunning(ANIM_START)) {
            at = animTime(ANIM_START, time);
            renderLinesScene(&at);
        }

        if (isRunning(ANIM_STARFIELD)) {
            at = animTime(ANIM_STARFIELD, time);
            renderStarfieldScene(&at);
        }

        if (isRunning(ANIM_END)) {
            at = animTime(ANIM_END, time);
            renderEndScene(&at);
        }

    }
    fw_render_bindTextureBufferEnd();

    // High-res.
    fw_render_viewportHiRes(0,0);
    {
        fw_render_clearHiRes(_bgClearColor.x, _bgClearColor.y, _bgClearColor.z, _bgClearColor.w);
    }

    // Render low-res content from texture.
    fw_render_renderTextureBuffer();

    // Render additional hi-res content.
    fw_render_viewportHiRes(0,0);

    if (isRunning(ANIM_STARFIELD)) {
        at = animTime(ANIM_STARFIELD, time);
        renderScrollerScene(&at);
    }

    // ...

#if FW_SCANLINES_ENABLED
    renderScanlines();
#endif

}
