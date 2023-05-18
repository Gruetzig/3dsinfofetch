#include <3ds.h>
#include <stdio.h>
#include <string.h>

void getVersion(char* version);
u8 getModel(char* models);
void getSDFreeSize(char* outputstring);
void getRunTime(char* runtime);
void getTime(char* outputstring);
int getBatteryLevel();
bool isCharging();
void getKernelVersion(char* out);
int getClockRateMode();
void getUsernameFromCfgSavegame(char* out);
void getSystemLanguage(char* out);
void getShortNameFromModel(u8 model, char* out);
