#include <3ds.h>
#include "graphics.h"
#include "utils.h"
#include "stats.h"

DrawContext ctx;
StatsContext stx;
void init() {
    gfxInitDefault();
    cfguInit();
    fsInit();
    ptmuInit();
    mcuHwcInit();
    InitC2D();
    InitContext(&ctx);
    InitColors(&ctx);
}

void deinit() {
    gfxExit();
    cfguExit();
    fsExit();
    ptmuExit();
    mcuHwcExit();
    ExitC2D();
}


int main() {
    init();
    while (aptMainLoop()) {
        hidScanInput();
        u32 kDown = hidKeysDown();
        if (kDown & KEY_START) break;
        updateStats(&stx);
        char line1[50], line2[50], line3[50], line4[50],line5[50], line6[50],line7[50], line8[50],line9[50], line10[50],line11[50], line12[50], line13[50], line14[50];
        char shortmodel[10];
        getShortNameFromModel(stx.modelnumber, shortmodel);
        sprintf(line1, "%s@%s", stx.username, shortmodel);
        sprintf(line2, "------------------------------");
        sprintf(line3, "%s", stx.version);
        sprintf(line4, "%s", stx.kernelversion);
        sprintf(line5, "%s", stx.lumaversion);
        sprintf(line6, "%s", stx.model);
        sprintf(line7, "%s", stx.cpu);
        sprintf(line8, "%s", stx.resolution);
        sprintf(line9, stx.charging ? "charging @ %d%%" : "discharging @ %d%%", stx.batterylevel);
        sprintf(line10, "%s", stx.freesdsize);
        sprintf(line11, " ");
        sprintf(line12, "%s", stx.language);
        sprintf(line13, "%s", stx.time);
        sprintf(line14, "%s", stx.runtime);
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_TargetClear(ctx.top, ctx.clrBlack);
        C2D_SceneBegin(ctx.top);
        DrawText(1, 1, 0.6f, line1, ctx.clrWhite);
        DrawText(1, 1+15*1, 0.6f, line2, ctx.clrWhite);

        DrawText(  1, 1+15*2, 0.5f, "Firmware:", ctx.clrPink);
        DrawText(  1, 1+15*3, 0.5f, "Kernel:", ctx.clrPink);
        DrawText(  1, 1+15*4, 0.5f, "Luma3DS version:", ctx.clrPink);
        DrawText(  1, 1+15*5, 0.5f, "Model:", ctx.clrPink);
        DrawText(  1, 1+15*6, 0.5f, "CPU:", ctx.clrPink);
        DrawText(  1, 1+15*7, 0.5f, "Resolution:", ctx.clrPink);
        DrawText(  1, 1+15*8, 0.5f, "Battery:", ctx.clrPink);
        DrawText(  1, 1+15*9, 0.5f, "Free SD space:", ctx.clrPink);
        DrawText(  1, 1+15*11, 0.5f, "Language:", ctx.clrPink);
        DrawText(  1, 1+15*12, 0.5f, "Time:", ctx.clrPink);
        DrawText(  1, 1+15*13, 0.5f, "Uptime:", ctx.clrPink);

        DrawText(120, 1+15*2, 0.5f, line3, ctx.clrWhite);
        DrawText(120, 1+15*3, 0.5f, line4, ctx.clrWhite);
        DrawText(120, 1+15*4, 0.5f, line5, ctx.clrWhite);
        DrawText(120, 1+15*5, 0.5f, line6, ctx.clrWhite);
        DrawText(120, 1+15*6, 0.5f, line7, ctx.clrWhite);
        DrawText(120, 1+15*7, 0.5f, line8, ctx.clrWhite);
        DrawText(120, 1+15*8, 0.5f, line9, ctx.clrWhite);
        DrawText(120, 1+15*9, 0.5f, line10, ctx.clrWhite);
        DrawText(120, 1+15*11, 0.5f, line12, ctx.clrWhite);
        DrawText(120, 1+15*12, 0.5f, line13, ctx.clrWhite);
        DrawText(120, 1+15*13, 0.5f, line14, ctx.clrWhite);
        C3D_FrameEnd(0);
    }
    deinit();
    
}