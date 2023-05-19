#include "utils.h"

#define CFG11_MPCORE_CLKCNT (0x10141300 | (1<<31))

void getVersion(char* version) {
    osGetSystemVersionDataString(NULL, NULL, version, 20);
}

u8 getModel(char* models) {
    u8 model;
    int stringsize = 20;
    CFGU_GetSystemModel(&model);
    if (model == CFG_MODEL_3DS) {
        snprintf(models, stringsize, "3DS(CTR)");
    }
    else if (model == CFG_MODEL_3DSXL) {
        snprintf(models, stringsize, "3DS XL(SPR)");
    }
    else if (model == CFG_MODEL_N3DS) {
        snprintf(models, stringsize, "New 3DS(KTR)");
    }
    else if (model == CFG_MODEL_2DS) {
        snprintf(models, stringsize, "2DS(FTR)");
    }
    else if (model == CFG_MODEL_N3DSXL) {
        snprintf(models, stringsize, "New 3DS XL(RED)");
    }
    else if (model == CFG_MODEL_N2DSXL) {
        snprintf(models, stringsize, "New 2DS XL(JAN)");
    }
    else {
        snprintf(models, stringsize, "unknown");
    }
    return model;
}

void getSizeString(char *string, uint64_t size) //Thanks TheOfficialFloW //thanks 3dsident https://github.com/joel16/3DSident/blob/master/common/utils.c#L7-L21
{
	double double_size = (double)size;

	int i = 0;
	static char *units[] = { "B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB" };

	while (double_size >= 1024.0f)
	{
		double_size /= 1024.0f;
		i++;
	}

	sprintf(string, "%.*f %s", (i == 0) ? 0 : 2, double_size, units[i]);
}

void getSDFreeSize(char* outputstring) {
    FS_ArchiveResource resource;
    FSUSER_GetArchiveResource(&resource, SYSTEM_MEDIATYPE_SD);
    u64 size = (u64) resource.freeClusters * (u64) resource.clusterSize;
    getSizeString(outputstring, size);
}

int dateTimeToString(char *out, u64 msSince1900, bool date) //thanks luma3ds
{
    // Conversion code adapted from https://stackoverflow.com/questions/21593692/convert-unix-timestamp-to-date-without-system-libs
    // (original author @gnif under CC-BY-SA 4.0)
    u32 seconds, minutes, hours, days, year, month;
    u64 milliseconds = msSince1900;
    seconds = milliseconds/1000;
    milliseconds %= 1000;
    minutes = seconds / 60;
    seconds %= 60;
    hours = minutes / 60;
    minutes %= 60;
    days = hours / 24;
    hours %= 24;
    if (date) {
    year = 1900; // osGetTime starts in 1900

    while(true)
    {
        bool leapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        u16 daysInYear = leapYear ? 366 : 365;
        if(days >= daysInYear)
        {
            days -= daysInYear;
            ++year;
        }
        else
        {
            static const u8 daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            for(month = 0; month < 12; ++month)
            {
                u8 dim = daysInMonth[month];

                if (month == 1 && leapYear)
                    ++dim;

                if (days >= dim)
                    days -= dim;
                else
                    break;
            }
            break;
        }
    }
    days++;
    month++;
    return sprintf(out, "%04lu-%02lu-%02lu %02lu:%02lu:%02lu", year, month, days, hours, minutes, seconds);
    }
    else {
        return sprintf(out, "%02lu:%02lu:%02lu", hours, minutes, seconds);
    }
}

void getTime(char* outputstring) {
    u64 timeNow = osGetTime();
    dateTimeToString(outputstring, timeNow, true);
}

void getRunTime(char* runtime) {
    u64 timeNow = osGetTime();
    u64 timeAtBoot = timeNow - (1000 * svcGetSystemTick() / SYSCLOCK_ARM11);
    u64 runtimems = timeNow - timeAtBoot;
    dateTimeToString(runtime, runtimems, false);
}

int getBatteryLevel() {
    u8 level;
    MCUHWC_GetBatteryLevel(&level);
    return level;
}

bool isCharging() {
    u8 charging;
    PTMU_GetBatteryChargeState(&charging);
    return charging;
}

void getKernelVersion(char* out) {
    u32 kernel = osGetKernelVersion();
    int ma = GET_VERSION_MAJOR(kernel);
    int mi = GET_VERSION_MINOR(kernel);
    int rev = GET_VERSION_REVISION(kernel);
    sprintf(out, "%d.%d.%d", ma, mi, rev);
}

int getClockRateMode() {
    return (((*(vu32*)CFG11_MPCORE_CLKCNT)>>16)&7);
}

void getUsernameFromCfgSavegame(char* out) {
    /*u8 username[0x1C+1];
    u16 _username[0x1C];
    CFGU_GetConfigInfoBlk2(0x1C, 0x000A0000, _username);
	utf16_to_utf8(username, _username, 0x1C);
    username[0x1C] = '\0';
    sprintf(out, "%x", username[5]);*/

    char username_tmp[0x1C];
	CFGU_GetConfigInfoBlk2(0x1C, 0xA0000, (u8*)&username_tmp);
    int i;
	for (i = 0; i < 0x0E; i++){
		out[i] = username_tmp[i<<1];
	}
    out[i] = '\0';
}

void getSystemLanguage(char* out) {
    u8 language;
    CFGU_GetSystemLanguage(&language);
    if (language == CFG_LANGUAGE_DE) {
        sprintf(out, "German");
    }
    else if (language == CFG_LANGUAGE_EN) {
        sprintf(out, "English");
    }
    else if (language == CFG_LANGUAGE_JP) {
        sprintf(out, "Japanese");
    }
    else if (language == CFG_LANGUAGE_FR) {
        sprintf(out, "French");
    }
    else if (language == CFG_LANGUAGE_IT) {
        sprintf(out, "Italian");
    }
    else if (language == CFG_LANGUAGE_ES) {
        sprintf(out, "Spanish");
    }
    else if (language == CFG_LANGUAGE_ZH) {
        sprintf(out, "Simplified Chinese");
    }
    else if (language == CFG_LANGUAGE_KO) {
        sprintf(out, "Korean");
    }
    else if (language == CFG_LANGUAGE_NL) {
        sprintf(out, "Dutch");
    }
    else if (language == CFG_LANGUAGE_PT) {
        sprintf(out, "Portugese");
    }
    else if (language == CFG_LANGUAGE_RU) {
        sprintf(out, "Russian");
    }
    else if (language == CFG_LANGUAGE_TW) {
        sprintf(out, "Traditional Chinese");
    }
    else {
        sprintf(out, "unknown");
    }
    
}

void getShortNameFromModel(u8 model, char* out) {
    if (model == CFG_MODEL_3DS) {
        sprintf(out, "3ds");
    }
    else if (model == CFG_MODEL_3DSXL) {
        sprintf(out, "3dsxl");
    }
    else if (model == CFG_MODEL_N3DS) {
        sprintf(out, "new3ds");
    }
    else if (model == CFG_MODEL_2DS) {
        sprintf(out, "2ds");
    }
    else if (model == CFG_MODEL_N3DSXL) {
        sprintf(out, "new3dsxl");
    }
    else if (model == CFG_MODEL_N2DSXL) {
        sprintf(out, "new2dsxl");
    }
    else {
        sprintf(out, "unknown");
    }
}

void getLumaVersion(char* out) {
    s64 outInfo;
    svcGetSystemInfo(&outInfo, 0x10000, 0);
    u32 lumaversion = (u32)outInfo;
    int ma = GET_VERSION_MAJOR(lumaversion);
    int mi = GET_VERSION_MINOR(lumaversion);
    int rev = GET_VERSION_REVISION(lumaversion);
    sprintf(out, "%d.%d.%d", ma, mi, rev);
}

