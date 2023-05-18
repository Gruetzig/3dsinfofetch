#include "graphics.h"

void InitC2D() {
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
}

void InitContext(DrawContext* ctx)
{
    ctx->top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    ctx->bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
}

void InitColors(DrawContext* ctx)
{
    ctx->clrBlack = C2D_Color32(0x00, 0x00, 0x00, 0xFF);
    ctx->clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
    ctx->clrRed = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
    ctx->clrBlue = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);
    ctx->clrGreen = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
    ctx->clrYellow = C2D_Color32(0xFF, 0xFF, 0x00, 0xFF);
    ctx->clrPink = C2D_Color32(0xFC, 0x46, 0xAA, 0xFF);
}

void ExitC2D() {
    C2D_Fini();
    C3D_Fini();
}

void DrawText(float x, float y, float scale, char* string, u32 color) {
    C2D_TextBuf buf=C2D_TextBufNew(4096);
    C2D_Text text;
    C2D_TextParse(&text, buf, string);
    C2D_TextOptimize(&text);
    C2D_DrawText(&text, C2D_WithColor /*| C2D_AlignCenter*/, x, y, 0, scale, scale, color);
    C2D_TextBufDelete(buf);
}
