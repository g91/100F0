#include "stdafx.h"
#pragma once


#define SOC_MMIO_BASE 0x8000020000000000
#define SOC_SRAM SOC_MMIO_BASE + 0x10000


#define __REG_20000 SOC_MMIO_BASE + 0x20000 // FUSESET_00
#define __REG_20200 SOC_MMIO_BASE + 0x20200 // FUSESET_01
#define __REG_20400 SOC_MMIO_BASE + 0x20400 // FUSESET_02
#define __REG_20600 SOC_MMIO_BASE + 0x20600 // FUSESET_03
#define __REG_20800 SOC_MMIO_BASE + 0x20800 // FUSESET_04
#define __REG_20A00 SOC_MMIO_BASE + 0x20A00 // FUSESET_05
#define __REG_20C00 SOC_MMIO_BASE + 0x20C00 // FUSESET_06
#define __REG_20E00 SOC_MMIO_BASE + 0x20E00 // FUSESET_07
#define __REG_21000 SOC_MMIO_BASE + 0x21000 // FUSESET_08
#define __REG_21200 SOC_MMIO_BASE + 0x21200 // FUSESET_09
#define __REG_21400 SOC_MMIO_BASE + 0x21400 // FUSESET_10
#define __REG_21600 SOC_MMIO_BASE + 0x21600 // FUSESET_11
#define __REG_22000 SOC_MMIO_BASE + 0x22000 // FUSE_DEVICE
#define __REG_22008 SOC_MMIO_BASE + 0x22008 // FUSE_DEVICE
#define __REG_24000 SOC_MMIO_BASE + 0x24000 // SOCSECENG_BLOCK
#define __REG_24008 SOC_MMIO_BASE + 0x24008 // SOCSECENG_BLOCK
#define __REG_24040 SOC_MMIO_BASE + 0x24040 // SOCSECENG_BLOCK
#define __REG_24048 SOC_MMIO_BASE + 0x24048 // SOCSECENG_BLOCK
#define __REG_24080 SOC_MMIO_BASE + 0x24080 // SOCSECENG_BLOCK
#define __REG_24088 SOC_MMIO_BASE + 0x24088 // SOCSECENG_BLOCK
#define __REG_25000 SOC_MMIO_BASE + 0x25000 // SOCSECENG_BLOCK
#define __REG_25008 SOC_MMIO_BASE + 0x25008 // SOCSECENG_BLOCK
#define __REG_25040 SOC_MMIO_BASE + 0x25040 // SOCSECENG_BLOCK
#define __REG_25048 SOC_MMIO_BASE + 0x25048 // SOCSECENG_BLOCK
#define __REG_25080 SOC_MMIO_BASE + 0x25080 // SOCSECENG_BLOCK
#define __REG_25088 SOC_MMIO_BASE + 0x25088 // SOCSECENG_BLOCK
#define __REG_26000 SOC_MMIO_BASE + 0x26000 // RNG device
#define __REG_26008 SOC_MMIO_BASE + 0x26008 // RNG device
#define __REG_28000 SOC_MMIO_BASE + 0x28000
#define __REG_28028 SOC_MMIO_BASE + 0x28028 // set in cbb InitSoC
#define __REG_28048 SOC_MMIO_BASE + 0x28048 // set in cbb InitSoC
#define __REG_30000 SOC_MMIO_BASE + 0x30000
#define __REG_30010 SOC_MMIO_BASE + 0x30010 // used in HvxBlowFuses
#define __REG_30020 SOC_MMIO_BASE + 0x30020 // used in HvxBlowFuses
#define __REG_33000 SOC_MMIO_BASE + 0x33000 // set in cbb InitSoC
#define __REG_33100 SOC_MMIO_BASE + 0x33100 // set in cbb InitSoC
#define __REG_33200 SOC_MMIO_BASE + 0x33200 // set in cbb InitSoC
#define __REG_33300 SOC_MMIO_BASE + 0x33300 // set in cbb InitSoC
#define __REG_37000 SOC_MMIO_BASE + 0x37000 // used in HvxBlowFuses
#define __REG_40000 SOC_MMIO_BASE + 0x40000
#define __REG_43000 SOC_MMIO_BASE + 0x43000 // set in cbb InitSoC
#define __REG_43100 SOC_MMIO_BASE + 0x43100 // set in cbb InitSoC
#define __REG_43200 SOC_MMIO_BASE + 0x43200 // set in cbb InitSoC
#define __REG_43300 SOC_MMIO_BASE + 0x43300 // set in cbb InitSoC
#define __REG_46200 SOC_MMIO_BASE + 0x46200 // VdpClockRegisterConfig
#define __REG_48000 SOC_MMIO_BASE + 0x48000 // used in HvxBlowFuses
#define __REG_50000 SOC_MMIO_BASE + 0x50000 // irq
#define __REG_50008 SOC_MMIO_BASE + 0x50008 // irq, used in HvxBlowFuses
#define __REG_50010 SOC_MMIO_BASE + 0x50010 // irq, used to wake up cpus
#define __REG_50050 SOC_MMIO_BASE + 0x50050 // irq, used in HvxBlowFuses
#define __REG_50060 SOC_MMIO_BASE + 0x50060 // irq, used in HvxBlowFuses
#define __REG_52000 SOC_MMIO_BASE + 0x52000 // irq, used to wake up cpus
#define __REG_52008 SOC_MMIO_BASE + 0x52008 // irq, used to wake up cpus
#define __REG_52070 SOC_MMIO_BASE + 0x52070 // irq, used to wake up cpus
#define __REG_54000 SOC_MMIO_BASE + 0x54000 // irq, used to wake up cpus
#define __REG_54008 SOC_MMIO_BASE + 0x54008 // irq, used to wake up cpus
#define __REG_54070 SOC_MMIO_BASE + 0x54070 // irq, used to wake up cpus
#define __REG_56000 SOC_MMIO_BASE + 0x56000 // irq - used to boost cpu voltage
#define __REG_56010 SOC_MMIO_BASE + 0x56010 // irq - used to boost cpu voltage
#define __REG_56020 SOC_MMIO_BASE + 0x56020 // PFM Inturrupt Enable - used to boost cpu voltage, used in HvxBlowFuses
#define __REG_56030 SOC_MMIO_BASE + 0x56030 // irq - used to boost cpu voltage
#define __REG_56040 SOC_MMIO_BASE + 0x56040 // irq - used to boost cpu voltage
#define __REG_60000 SOC_MMIO_BASE + 0x60000
#define __REG_60430 SOC_MMIO_BASE + 0x60430 // set in cbb InitSoC
#define __REG_60530 SOC_MMIO_BASE + 0x60530 // set in cbb InitSoC
#define __REG_60630 SOC_MMIO_BASE + 0x60630 // set in cbb InitSoC
#define __REG_60808 SOC_MMIO_BASE + 0x60808 // set in cbb InitSoC
#define __REG_60820 SOC_MMIO_BASE + 0x60820 // set in cbb InitSoC
#define __REG_60830 SOC_MMIO_BASE + 0x60830 // set in cbb InitSoC
#define __REG_60B30 SOC_MMIO_BASE + 0x60B30 // set in cbb InitSoC
#define __REG_60B58 SOC_MMIO_BASE + 0x60B58 // used in HvxBlowFuses
#define __REG_61000 SOC_MMIO_BASE + 0x61000 // PRV Base - used in HvxBlowFuses
#define __REG_61010 SOC_MMIO_BASE + 0x61010 // POST
#define __REG_61030 SOC_MMIO_BASE + 0x61030 // used in HvxBlowFuses
#define __REG_61050 SOC_MMIO_BASE + 0x61050 // used in HvxBlowFuses
#define __REG_61060 SOC_MMIO_BASE + 0x61060 // used in HvxBlowFuses, set in cbb InitSoC
#define __REG_61188 SOC_MMIO_BASE + 0x61188 // seems config reg, used to boost cpu voltage, used in HvxBlowFuses
#define __REG_0E102_0000 SOC_MMIO_BASE + 0xE1020000 // used in HvxBlowFuses
#define __REG_0E102_0004 SOC_MMIO_BASE + 0xE1020004 // used in HvxBlowFuses
#define __REG_0E100_0000 SOC_MMIO_BASE + 0xE1000000 // used in HvxBlowFuses
#define __REG_0E100_7000 SOC_MMIO_BASE + 0xE1007000 // used in HvxBlowFuses

#define _REG_20000 (*((volatile QWORD *)__REG_20000))
#define _REG_20200 (*((volatile QWORD *)__REG_20200))
#define _REG_20400 (*((volatile QWORD *)__REG_20400))
#define _REG_20600 (*((volatile QWORD *)__REG_20600))
#define _REG_20800 (*((volatile QWORD *)__REG_20800))
#define _REG_20A00 (*((volatile QWORD *)__REG_20A00))
#define _REG_20C00 (*((volatile QWORD *)__REG_20C00))
#define _REG_20E00 (*((volatile QWORD *)__REG_20E00))
#define _REG_21000 (*((volatile QWORD *)__REG_21000))
#define _REG_21200 (*((volatile QWORD *)__REG_21200))
#define _REG_21400 (*((volatile QWORD *)__REG_21400))
#define _REG_21600 (*((volatile QWORD *)__REG_21600))
#define _REG_22000 (*((volatile QWORD *)__REG_22000))
#define _REG_22008 (*((volatile QWORD *)__REG_22008))
#define _REG_24000 (*((volatile QWORD *)__REG_24000))
#define _REG_24008 (*((volatile QWORD *)__REG_24008))
#define _REG_24040 (*((volatile QWORD *)__REG_24040))
#define _REG_24048 (*((volatile QWORD *)__REG_24048))
#define _REG_24080 (*((volatile QWORD *)__REG_24080))
#define _REG_24088 (*((volatile QWORD *)__REG_24088))
#define _REG_25000 (*((volatile QWORD *)__REG_25000))
#define _REG_25008 (*((volatile QWORD *)__REG_25008))
#define _REG_25040 (*((volatile QWORD *)__REG_25040))
#define _REG_25048 (*((volatile QWORD *)__REG_25048))
#define _REG_25080 (*((volatile QWORD *)__REG_25080))
#define _REG_25088 (*((volatile QWORD *)__REG_25088))
#define _REG_26000 (*((volatile QWORD *)__REG_26000))
#define _REG_26008 (*((volatile QWORD *)__REG_26008))
#define _REG_28000 (*((volatile QWORD *)__REG_28000))
#define _REG_28028 (*((volatile QWORD *)__REG_28028))
#define _REG_28048 (*((volatile QWORD *)__REG_28048))
#define _REG_30000 (*((volatile QWORD *)__REG_30000))
#define _REG_30010 (*((volatile QWORD *)__REG_30010))
#define _REG_30020 (*((volatile QWORD *)__REG_30020))
#define _REG_33000 (*((volatile QWORD *)__REG_33000))
#define _REG_33100 (*((volatile QWORD *)__REG_33100))
#define _REG_33200 (*((volatile QWORD *)__REG_33200))
#define _REG_33300 (*((volatile QWORD *)__REG_33300))
#define _REG_37000 (*((volatile QWORD *)__REG_37000))
#define _REG_40000 (*((volatile QWORD *)__REG_40000))
#define _REG_43000 (*((volatile QWORD *)__REG_43000))
#define _REG_43100 (*((volatile QWORD *)__REG_43100))
#define _REG_43200 (*((volatile QWORD *)__REG_43200))
#define _REG_43300 (*((volatile QWORD *)__REG_43300))
#define _REG_46200 (*((volatile QWORD *)__REG_46200))
#define _REG_48000 (*((volatile QWORD *)__REG_48000))
#define _REG_50000 (*((volatile QWORD *)__REG_50000))
#define _REG_50008 (*((volatile QWORD *)__REG_50008))
#define _REG_50010 (*((volatile QWORD *)__REG_50010))
#define _REG_50050 (*((volatile QWORD *)__REG_50050))
#define _REG_50060 (*((volatile QWORD *)__REG_50060))
#define _REG_52000 (*((volatile QWORD *)__REG_52000))
#define _REG_52008 (*((volatile QWORD *)__REG_52008))
#define _REG_52070 (*((volatile QWORD *)__REG_52070))
#define _REG_54000 (*((volatile QWORD *)__REG_54000))
#define _REG_54008 (*((volatile QWORD *)__REG_54008))
#define _REG_54070 (*((volatile QWORD *)__REG_54070))
#define _REG_56000 (*((volatile QWORD *)__REG_56000))
#define _REG_56010 (*((volatile QWORD *)__REG_56010))
#define _REG_56020 (*((volatile QWORD *)__REG_56020))
#define _REG_56030 (*((volatile QWORD *)__REG_56030))
#define _REG_56040 (*((volatile QWORD *)__REG_56040))
#define _REG_60000 (*((volatile QWORD *)__REG_60000))
#define _REG_60430 (*((volatile QWORD *)__REG_60430))
#define _REG_60530 (*((volatile QWORD *)__REG_60530))
#define _REG_60630 (*((volatile QWORD *)__REG_60630))
#define _REG_60808 (*((volatile QWORD *)__REG_60808))
#define _REG_60820 (*((volatile QWORD *)__REG_60820))
#define _REG_60830 (*((volatile QWORD *)__REG_60830))
#define _REG_60B30 (*((volatile QWORD *)__REG_60B30))
#define _REG_60B58 (*((volatile QWORD *)__REG_60B58))
#define _REG_61000 (*((volatile QWORD *)__REG_61000))
#define _REG_61010 (*((volatile QWORD *)__REG_61010))
#define _REG_61030 (*((volatile QWORD *)__REG_61030))
#define _REG_61050 (*((volatile QWORD *)__REG_61050))
#define _REG_61060 (*((volatile QWORD *)__REG_61060))
#define _REG_61188 (*((volatile QWORD *)__REG_61188))
#define _REG_0E102_0000 (*((volatile DWORD *)__REG_0E102_0000)) // DWORD
#define _REG_0E102_0004 (*((volatile DWORD *)__REG_0E102_0004)) // DWORD
#define _REG_0E100_0000 (*((volatile QWORD *)__REG_0E100_0000))
#define _REG_0E100_7000 (*((volatile QWORD *)__REG_0E100_7000))

#define SOC_FUSESET_BASE __REG_20000
#define SOC_FUSESET_00_P __REG_20000
#define SOC_FUSESET_01_P __REG_20200
#define SOC_FUSESET_02_P __REG_20400
#define SOC_FUSESET_03_P __REG_20600
#define SOC_FUSESET_04_P __REG_20800
#define SOC_FUSESET_05_P __REG_20A00
#define SOC_FUSESET_06_P __REG_20C00
#define SOC_FUSESET_07_P __REG_20E00
#define SOC_FUSESET_08_P __REG_21000
#define SOC_FUSESET_09_P __REG_21200
#define SOC_FUSESET_10_P __REG_21400
#define SOC_FUSESET_11_P __REG_21600
#define SOC_FUSESET_00_V _REG_20000
#define SOC_FUSESET_01_V _REG_20200
#define SOC_FUSESET_02_V _REG_20400
#define SOC_FUSESET_03_V _REG_20600
#define SOC_FUSESET_04_V _REG_20800
#define SOC_FUSESET_05_V _REG_20A00
#define SOC_FUSESET_06_V _REG_20C00
#define SOC_FUSESET_07_V _REG_20E00
#define SOC_FUSESET_08_V _REG_21000
#define SOC_FUSESET_09_V _REG_21200
#define SOC_FUSESET_10_V _REG_21400
#define SOC_FUSESET_11_V _REG_21600

// mapped to __REG_26000
typedef struct _SOC_RNG {
	QWORD Flags;
	QWORD Random;
} SOC_RNG, *PSOC_RNG;
