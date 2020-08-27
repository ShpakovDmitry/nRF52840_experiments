#include <stdint.h>
#include <stdbool.h>
#include <clock.h>

typedef volatile struct __attribute__ ((packed)) {
    uint32_t TASKS_HFCLKSTART;      /* 0x000 start HFXO crystal oscillator */
    uint32_t TASKS_HFCLKSTOP;       /* 0x004 stop HFXO crystal oscillator */
    uint32_t TASKS_LFCLKSTART;      /* 0x008 start LFCLK */
    uint32_t TASKS_LFCLKSTOP;       /* 0x00C stop LFCLK */
    uint32_t TASKS_CAL;             /* 0x010 start calibration of LFRC */
    uint32_t TASKS_CTSTART;         /* 0x014 start calibration timer */
    uint32_t TASKS_CTSTOP;          /* 0x018 stop calibration timer */
    uint32_t reserved0[57];         /* 0x01C - 0x0FC reserved */
    uint32_t EVENTS_HFCLKSTARTED;   /* 0x100 HFXO crystal osc. started */
    uint32_t EVENTS_LFCLKSTARTED;   /* 0x104 LFCLK started */
    uint32_t reserved1[1];          /* 0x108 reserved */
    uint32_t EVENTS_DONE;           /* 0x10C calibration of LFRC completed */
    uint32_t EVENTS_CTTO;           /* 0x110 calibration timer timeout */
    uint32_t reserved2[5];          /* 0x114 - 0x124 reserved */
    uint32_t EVENTS_CTSTARTED;      /* 0x128 calibration timer started */
    uint32_t EVENTS_CTSTOPPED;      /* 0x12C calibration timer stopped */
    uint32_t reserved3[117];        /* 0x130 - 0x300 reserved */
    uint32_t INTENSET;              /* 0x304 enable interrupt */
    uint32_t INTENCLR;              /* 0x308 disable interrupt */
    uint32_t reserved4[63];         /* 0x30C - 0x404 reserved */
    uint32_t HFCLKRUN;              /* 0x408 HFCLKSTART task triggered */
    uint32_t HFCLKSTAT;             /* 0x40C HFCLK status */
    uint32_t reserved5[1];          /* 0x410 reserved */
    uint32_t LFCLKRUN;              /* 0x414 LFCLKSTART task triggered */
    uint32_t LFCLKSTAT;             /* 0x418 LFCLK status */
    uint32_t LFCLKSRCCOPY;          /* 0x41C copy of LFCLKSRCCOPY register */
    uint32_t reserved6[62];         /* 0x420 - 0x514 reserved */
    uint32_t LFCLKSRC;              /* 0x518 clock source for LFCLK */
    uint32_t reserved7[3];          /* 0x51C - 0x524 reserved */
    uint32_t HFXODEBOUNCE;          /* 0x528 HFXO debounce time */
    uint32_t reserved8[3];          /* 0x52C - 0x534 reserved */
    uint32_t CTIV;                  /* 0x538 calibration timer interval */
    uint32_t reserved9[8];          /* 0x53C - 0x558 reserved */
    uint32_t TRACECONFIG;           /* 0x55C clocking options for TPDI */
    uint32_t reserved10[21];        /* 0x560 - 0x5B0 reserved */
    uint32_t LFRCMODE;              /* 0x5B4 LFRC mode configuration */
} ClockRegisters;

static ClockRegisters* clock = (ClockRegisters *)0x40000000u;

#define TASKS_HFCLKSTART_BIT 0
#define EVENTS_HFCLKSTARTED_BIT 0

#define TASKS_HFCLKSTOP_BIT 0

#define SET_BIT_HI(reg, bit) ( (reg) |=  (1 << (bit)) )
#define SET_BIT_LO(reg, bit) ( (reg) &= ~(1 << (bit)) )
#define GET_BIT(reg, bit) ( (reg) & (1 << (bit)) )

static bool HfxoClkStarted(void) {
    bool res;
    if ( GET_BIT(clock->EVENTS_HFCLKSTARTED, EVENTS_HFCLKSTARTED_BIT) ) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

void startHfxoClock(void) {
    SET_BIT_HI(clock->TASKS_HFCLKSTART, TASKS_HFCLKSTART_BIT);

    while ( HfxoClkStarted() == false ) {
        ;
    }
}

void stopHfxoClock(void) {
    SET_BIT_HI(clock->TASKS_HFCLKSTOP, TASKS_HFCLKSTOP_BIT);
}

void setHfxoDebounce(HfxoDebounceTime debounceTime) {
    switch (debounceTime) {
        case HFXO_DEBOUNCE_16US:
        case HFXO_DEBOUNCE_32US:
        case HFXO_DEBOUNCE_64US:
        case HFXO_DEBOUNCE_128US:
        case HFXO_DEBOUNCE_256US:
        case HFXO_DEBOUNCE_512US:
        case HFXO_DEBOUNCE_1024US:
        case HFXO_DEBOUNCE_2048US:
            SET_BIT_HI(clock->HFXODEBOUNCE, debounceTime);
            break;
        default:
            // set max debounce for sure
            SET_BIT_HI(clock->HFXODEBOUNCE, HFXO_DEBOUNCE_2048US);
            break;
    }
}
