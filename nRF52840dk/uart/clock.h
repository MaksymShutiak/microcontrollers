struct clock {
  volatile uint32_t TASKS_HFCLKSTART, // 0x000 = 0
                    TASKS_HFCLKSTOP, // 0x004 = 4
                    TASKS_LFCLKSTART, // 0x008 = 8
                    TASKS_LFCLKSTOP, // 0x00C = 12
                    TASKS_CAL, // 0x010 = 16
                    TASKS_CTSTART, // 0x014 = 20
                    TASKS_CTSTOP, // 0x018 = 24
                    RESERVED[57], // 0x01C = 28
                    EVENTS_HFCLKSTARTED, // 0x100 = 256 
                    EVENTS_LFCLKSTARTED, // 0x104 = 260
                    RESERVED1[1], 
                    EVENTS_DONE, // 0x10C = 268
                    EVENTS_CTTO, // 0x110 = 272
                    RESERVED2[5],
                    EVENTS_CTSTARTED, // 0x128 = 296
                    EVENTS_CTSTOPPED, // 0x12C = 300
                    RESERVED3[117],
                    INTENSET, // 0x304 = 772
                    INTENCLR, // 0x308 = 776
                    RESERVED4[63],
                    HFCLKRUN, // 0x408 = 1032
                    HFCLKSTAT, // 0x40C = 1036
                    RESERVED5[1],
                    LFCLKRUN, //0x414 = 1044
                    LFCLKSTAT, // 0x418 = 1048
                    LFCLKSRCCOPY, // 0x41C = 1052
                    RESERVED6[62],
                    LFCLKSRC, // 0x518 = 1304
                    RESERVED7[3],
                    HFXODEBOUNCE, // 0x528 = 1320
                    RESERVED8[3],
                    CTIV, // 0x538 = 1336
                    RESERVED9[8],
                    TRACECONFIG, // 0x55C = 1372
                    RESERVED10[20],
                    LFRCMODE; // 0x5B4 = 1460
};
