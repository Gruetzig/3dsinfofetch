#include "stats.h"

void updateStats(StatsContext* stx) {
    stx->batterylevel = getBatteryLevel();
    stx->charging = isCharging();
    stx->clockratemode = getClockRateMode();
    if (stx->clockratemode == 0) { //gbatek stuff http://www.problemkaputt.de/gbatek.htm
        sprintf(stx->cpu, "Dual-core ARM11 MPCore @ 268 MHz");
    }
    else if (stx->clockratemode == 1) {
        sprintf(stx->cpu, "Quad-core ARM11 MPCore @ 268 MHz");
    }
    else if (stx->clockratemode == 3) {
        sprintf(stx->cpu, "Quad-core ARM11 MPCore @ 536 MHz");
    }
    else if (stx->clockratemode == 5 || stx->clockratemode == 7) {
        sprintf(stx->cpu, "Quad-core ARM11 MPCore @ 804 MHz");
    }
    else {
        sprintf(stx->cpu, "Dual-core ARM11 MPCore @ 268 MHz");
    }
    getVersion(stx->version);
    u8 model;
    model = getModel(stx->model);
    stx->modelnumber = model;
    if (!(model == CFG_MODEL_2DS || model == CFG_MODEL_N2DSXL)) {
        sprintf(stx->resolution, "800x240, 320x240");
    }
    else {
       sprintf(stx->resolution, "400x240, 320x240"); 
    }
    getSDFreeSize(stx->freesdsize);
    getRunTime(stx->runtime);
    getTime(stx->time);
    getKernelVersion(stx->kernelversion);
    getUsernameFromCfgSavegame(stx->username);
    getSystemLanguage(stx->language);
}