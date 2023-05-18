#include <citro2d.h>
#include <3ds.h>
#include <stdbool.h>

typedef struct {
    C3D_RenderTarget* top;
    C3D_RenderTarget* bottom;
    u32 clrBlack;
    u32 clrWhite;
    u32 clrRed;
    u32 clrBlue;
    u32 clrGreen;
    u32 clrYellow;
    u32 clrPink;
} DrawContext;

void InitC2D();
void InitContext(DrawContext* ctx);
void InitColors(DrawContext* ctx);
void ExitC2D();
void DrawText(float x, float y, float scale, char* string, u32 color);