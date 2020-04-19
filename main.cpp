/*
 * File:   main.cpp
 * Author: Nikita
 *
 * Created on March 4 2011, 15:59
 */
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <inttypes.h>

struct VersionInfo
{
    uint8_t stepping;
    uint8_t model;
    uint8_t family;
    uint8_t type;
    uint8_t exmodel;
    uint8_t exfamily;
};

uint64_t getFreq()
{
    unsigned int ts_hi1, ts_lo1, ts_hi2, ts_lo2;

    uint64_t countStart;
    uint64_t countEnd;

    timeval* tp = new timeval;

    uint64_t startMsec;
    uint64_t endMsec;


    asm __volatile__("rdtsc" : "=a"(ts_lo1), "=d"(ts_hi1) :);

    gettimeofday(tp, NULL);
    startMsec = (tp->tv_sec * 1E6) + tp->tv_usec;

    do
    {
        gettimeofday(tp, NULL);
        endMsec = (tp->tv_sec * 1E6) + tp->tv_usec;
    }
    while ((startMsec + 1E6) >= endMsec);

    asm __volatile__("rdtsc" : "=a"(ts_lo2), "=d"(ts_hi2) :);

    countStart = ts_hi1;
    countStart = countStart << 32;
    countStart = countStart | ts_lo1;

    countEnd = ts_hi2;
    countEnd = countEnd << 32;
    countEnd = countEnd | ts_lo2;

    delete tp;

    return countEnd - countStart;
};

void getBrand(char *outStr)
{
    uint32_t num;
    uint32_t cpuidStr[4];

    for (num = 0x80000002; num < 0x80000005; ++num)
    {
        asm __volatile__("cpuid"
                                : "=a"(cpuidStr[0]),
                                  "=b"(cpuidStr[1]),
                                  "=c"(cpuidStr[2]),
                                  "=d"(cpuidStr[3])
                                :  "a"(num));

        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                outStr[(num - 0x80000002)*16 + i * 4 + j] = (cpuidStr[i] >> j * 8) & 0xFF;
            }
        }

    }
};

void getVersion(VersionInfo *outStruct)
{
    uint32_t cpuidNum;

    asm __volatile__("movl $1, %%eax\n"
                     "cpuid"
                            : "=a"(cpuidNum) :);

    outStruct->stepping = cpuidNum & 0xF;
    outStruct->model = (cpuidNum >> 4) & 0xF;
    outStruct->family = (cpuidNum >> 8) & 0xF;
    outStruct->type = (cpuidNum >> 12) & 0x3;
    outStruct->exmodel = (cpuidNum >> 16) & 0xF;
    outStruct->exfamily = (cpuidNum >> 20) & 0xFF;

};

int main()
{
    char brandStr[49];
    memset(brandStr, 0, sizeof (brandStr));

    getBrand(brandStr);
    printf("Processor brand string: %s\n\n", brandStr);


    VersionInfo* version = new VersionInfo;

    getVersion(version);
    printf("Stepping: %X "  " Model: %X "   " Family: %X "   " Type: %X "   " Extended Model: %X " " Extended Family: %X\n\n\n",
           version->stepping, version->model, version->family, version->type, version->exmodel,      version->exfamily);

    delete version;

    printf("Press \"q\" to exit or \"Enter\" to detect CPU clock frequency again\n\n");

    uint64_t freq;
    double freqMhz;

    char ch = getchar();

    while (ch != 'q')
    {
        freq = getFreq();
        freqMhz = freq / 1E6;

        printf("Frequency = %llu Hz (%.2f MHz)\n", freq, freqMhz);

        ch = getchar();
    }

    return 0;
}
