#include <3ds.h>
#include "utils.h"

typedef struct {
    char version[20];
    char model[20];
    char freesdsize[10];
    char runtime[20];
    char time[20];
    int batterylevel;
    bool charging;
    char kernelversion[10];
    int clockratemode;
    char username[0x1C];
    char language[20];
    char cpu[40];
    char resolution[20];
    char lumaversion[10];
    u8 modelnumber;
} StatsContext;

void updateStats(StatsContext* stx);