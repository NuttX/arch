/****************************************************************************
 * arch/arm/src/armv7-a/gic.h
 * Generic Interrupt Controller Definitions
 *
 *   Copyright (C) 2016 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Reference:
 *   Cortex™-A9 MPCore, Revision: r4p1, Technical Reference Manual, ARM DDI
 *   0407I (ID091612).
 *
 *   Includes some removed registers from the r2p2 version as well. ARM DDI
 *   0407F (ID050110)
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#ifndef __ARCH_ARM_SRC_ARMV7_A_GIC_H
#define __ARCH_ARM_SRC_ARMV7_A_GIC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include "mpcore.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
/* Generic indexing helpers *************************************************/
/* 1x32 bit field per register */

#define GIC_INDEX1(n)              (n)                       /* 1 field per word */
#define GIC_OFFSET1(n)             (GIC_INDEX1(n) << 2)      /* 32-bit word offset */
#define GIC_SHIFT1(n)              (0)                       /* No shift */
#define GIC_MASK1(n)               (0xffffffff)              /* Whole word */

/* 2x16 bit field per register */

#define GIC_INDEX2(n)              (n >> 1)                  /* 2 fields per word */
#define GIC_OFFSET2(n)             (GIC_INDEX2(n) << 2)      /* 32-bit word offset */
#define GIC_SHIFT2(n)              (((n) & 1) << 4)          /* Shift 16-bits per field */
#define GIC_MASK2(n)               (0xffff << GIC_SHIFT2(n)) /* 16-bit mask */

/* 4x8 bit field per register */

#define GIC_INDEX4(n)              (n >> 2)                  /* 4 fields per word */
#define GIC_OFFSET4(n)             (GIC_INDEX4(n) << 2)      /* 32-bit word offset */
#define GIC_SHIFT4(n)              (((n) & 3) << 3)          /* Shift 8-bits per field */
#define GIC_MASK4(n)               (0xff << GIC_SHIFT4(n))   /* 8-bit mask */

/* 8x4 bit field per register */

#define GIC_INDEX8(n)              (n >> 3)                  /* 8 fields per word */
#define GIC_OFFSET8(n)             (GIC_INDEX8(n) << 2)      /* 32-bit word offset */
#define GIC_SHIFT8(n)              (((n) & 7) << 2)          /* Shift 4-bits per field */
#define GIC_MASK8(n)               (15 << GIC_SHIFT8(n))     /* 4-bit mask */

/* 16x2 bit field per register */

#define GIC_INDEX16(n)             (n >> 4)                  /* 16 fields per word */
#define GIC_OFFSET16(n)            (GIC_INDEX16(n) << 2)     /* 32-bit word offset */
#define GIC_SHIFT16(n)             (((n) & 15) << 1)         /* Shift 2-bits per field */
#define GIC_MASK16(n)              (3 << GIC_SHIFT16(n))     /* 2-bit mask */

/* 32x1 bit field per register */

#define GIC_INDEX32(n)             (n >> 5)                  /* 32 fields per word */
#define GIC_OFFSET32(n)            (GIC_INDEX32(n) << 2)     /* 32-bit word offset */
#define GIC_SHIFT32(n)             ((n) & 31)                /* Shift 1-bit per field */
#define GIC_MASK32(n)              (1 << GIC_SHIFT32(n))     /* 1-bit mask */

/* GIC Register Offsets *****************************************************/
/* Interrupt Interface registers */

#define GIC_ICCICR_OFFSET          0x0000    /* CPU Interface Control Register */
#define GIC_ICCPMR_OFFSET          0x0004    /* Interrupt Priority Mask Register */
#define GIC_ICCBPR_OFFSET          0x0008    /* Binary point Register */
#define GIC_ICCIAR_OFFSET          0x000c    /* Interrupt Acknowledge */
#define GIC_ICCEOIR_OFFSET         0x0010    /* End of interrupt */
#define GIC_ICCRPR_OFFSET          0x0014    /* Running interrupt */
#define GIC_ICCHPIR_OFFSET         0x0018    /* Highest pending interrupt */
#define GIC_ICCABPR_OFFSET         0x001c    /* Aliased Non-secure Binary Point Register */
#define GIC_ICCIDR_OFFSET          0x00fc    /* CPU Interface Implementer ID Register */

/* Distributor Registers */

#define GIC_ICDDCR_OFFSET          0x0000    /* Distributor Control Register */
#define GIC_ICDICTR_OFFSET         0x0004    /* Interrupt Controller Type Register */
#define GIC_ICDIIDR_OFFSET         0x0008    /* Distributor Implementer ID Register */

/* 0x000c-0x007c: Reserved */
/* Interrupt Security Registers: 0x0080-0x009c */

#define GIC_ICDISR_OFFSET(n)       (0x0080 + GIC_OFFSET32(n))

/* Interrupt Set-Enable Registers: 0x0100-0x011c */

#define GIC_ICDISER_OFFSET(n)      (0x0100 + GIC_OFFSET32(n))

/* Interrupt Clear-Enable Registers: 0x0180-0x019c */

#define GIC_ICDICER_OFFSET(n)      (0x0180 + GIC_OFFSET32(n))

/* Interrupt Set-Pending Registers: 0x0200-0x027c */

#define GIC_ICDISPR_OFFSET(n)      (0x0200 + GIC_OFFSET32(n))

/* Interrupt Clear-Pending Registers: 0x0280-0x02fc */

#define GIC_ICDICPR_OFFSET(n)      (0x0280 + GIC_OFFSET32(n))

/* Interrupt Active Bit Registers: 0x0300-0x31c */

#define GIC_ICDABR_OFFSET(n)       (0x0300 + GIC_OFFSET32(n))

/* 0x0380-0x03fc: Reserved */
/* Interrupt Priority Registers: 0x0400-0x04fc */

#define GIC_ICDIPR_OFFSET(n)       (0x0400 + GIC_OFFSET4(n))

/* 0x0500-0x07fc: Reserved */
/* Interrupt Processor Target Registers: 0x0800-0x08fc */

#define GIC_ICDIPTR_OFFSET(n)      (0x0800 + GIC_OFFSET4(n))

/* 0x0900-0x0bfc: Reserved */
/* Interrupt Configuration Registers: 0x0c00-0x0c3c */

#define GIC_ICDICFR_OFFSET(n)      (0x0c00 + GIC_OFFSET16(n))

/* PPI Status Register: 0x0d00 */

#define GIC_ICPPISR_OFFSET         0x0d00    /* PPI Status Register */

/* SPI Status Registers: 0x0d04-0x0d1c */

#define GIC_ICSPISR_OFFSET(n)      (0x0d04 + GIC_OFFSET32(n))

/* 0x0d80-0x0efc: Reserved */
/* Software Generated Interrupt Register: 0x0f00 */

#define GIC_ICDSGIR_OFFSET         0x0f00    /* Software Generated Interrupt Register */

/* 0x0f0c-0x0fcc: Reserved */
/* Peripheral Identification Registers: 0x0fd0-0xfe8 */

#define GIC_ICPIDR_OFFSET(n)       (0x0fd0 + ((n) << 2))

/* Component Identification Registers: 0x0ff0-0x0ffc */

#define GIC_ICCIDR_OFFSET(n)       (0x0ff0 + ((n) << 2))

/* 0x0f04-0x0ffc: Reserved */

/* GIC Register Addresses ***************************************************/
/* The Interrupt Controller is a single functional unit that is located in a
 * Cortex-A9 MPCore design. There is one interrupt interface per Cortex-A9
 * processor.  Registers are memory mapped and accessed through a chip-
 * specific private memory spaced (see mpcore.h).
 */

/* Interrupt Interface registers */

#define GIC_ICCICR                 (MPCORE_ICC_VBASE+GIC_ICCICR_OFFSET)
#define GIC_ICCPMR                 (MPCORE_ICC_VBASE+GIC_ICCPMR_OFFSET)
#define GIC_ICCBPR                 (MPCORE_ICC_VBASE+GIC_ICCBPR_OFFSET)
#define GIC_ICCIAR                 (MPCORE_ICC_VBASE+GIC_ICCIAR_OFFSET)
#define GIC_ICCEOIR                (MPCORE_ICC_VBASE+GIC_ICCEOIR_OFFSET)
#define GIC_ICCRPR                 (MPCORE_ICC_VBASE+GIC_ICCRPR_OFFSET)
#define GIC_ICCHPIR                (MPCORE_ICC_VBASE+GIC_ICCHPIR_OFFSET)
#define GIC_ICCABPR                (MPCORE_ICC_VBASE+GIC_ICCABPR_OFFSET)
#define GIC_ICCIDR                 (MPCORE_ICC_VBASE+GIC_ICCIDR_OFFSET_

/* Distributor Registers */

#define GIC_ICDDCR                 (MPCORE_ICD_VBASE+GIC_ICDDCR_OFFSET)
#define GIC_ICDICTR                (MPCORE_ICD_VBASE+GIC_ICDICTR_OFFSET)
#define GIC_ICDIIDR                (MPCORE_ICD_VBASE+GIC_ICDIIDR_OFFSET)
#define GIC_ICDISER(n)             (MPCORE_ICD_VBASE+GIC_ICDISER_OFFSET(n))
#define GIC_ICDICER(n)             (MPCORE_ICD_VBASE+GIC_ICDICER_OFFSET(n))
#define GIC_ICDISPR(n)             (MPCORE_ICD_VBASE+GIC_ICDISPR_OFFSET(n))
#define GIC_ICDICPR(n)             (MPCORE_ICD_VBASE+GIC_ICDICPR_OFFSET(n))
#define GIC_ICDABR(n)              (MPCORE_ICD_VBASE+GIC_ICDABR_OFFSET(n))
#define GIC_ICDIPR(n)              (MPCORE_ICD_VBASE+GIC_ICDIPR_OFFSET(n))
#define GIC_ICDIPTR(n)             (MPCORE_ICD_VBASE+GIC_ICDIPTR_OFFSET(n))
#define GIC_ICDICFR(n)             (MPCORE_ICD_VBASE+GIC_ICDICFR_OFFSET(n))
#define GIC_ICPPISR                (MPCORE_ICD_VBASE+GIC_ICPPISR_OFFSET)
#define GIC_ICSPISR(n)             (MPCORE_ICD_VBASE+GIC_ICSPISR_OFFSET(n))
#define GIC_ICDSGIR                (MPCORE_ICD_VBASE+GIC_ICDSGIR_OFFSET)
#define GIC_ICPIDR(n)              (MPCORE_ICD_VBASE+GIC_ICPIDR_OFFSET(n))
#define GIC_ICCIDR(n)              (MPCORE_ICD_VBASE+GIC_ICCIDR_OFFSET(n))

/* PrimeCell Identification Registers: 0x0ff0-0x0ffc */

#define        (0x0ff0 + GIC_OFFSET32(n))

/* GIC Register Bit Definitions *********************************************/

/* Interrupt Interface registers */
/*  CPU Interface Control Register */

#define GIC_ICCICR_ENABLE          (1 << 0)  /* Bit 0: Enable the CPU interface for this GIC */
                                             /* Bits 1-31: Reserved */
/* Interrupt Priority Mask Register */
                                             /* Bits 0-3: Reserved */
#define GIC_ICCPMR_SHIFT           (4)       /* Bits 4-7: Priority mask */
#define GIC_ICCPMR_MASK            (15 << GIC_ICCPMR_SHIFT)
#  define GIC_ICCPMR_VALUE(n)      ((uint32_t)(n) << GIC_ICCPMR_SHIFT)
                                             /* Bits 8-31: Reserved */
/* Binary point Register and liased Non-secure Binary Point Register */

#define GIC_ICCBPR_SHIFT           (0)       /* Bits 0-2: Binary point */
#define GIC_ICCBPR_MASK            (7 << GIC_ICCBPR_SHIFT)
#  define GIC_ICCBPR_ALL           (3 << GIC_ICCBPR_SHIFT) /* All priority bits are compared for pre-emption */
#  define GIC_ICCBPR_5_7           (4 << GIC_ICCBPR_SHIFT) /* Priority bits [7:5] compared for pre-emption */
#  define GIC_ICCBPR_6_7           (5 << GIC_ICCBPR_SHIFT) /* Priority bits [7:6] compared for pre-emption */
#  define GIC_ICCBPR_7             (6 << GIC_ICCBPR_SHIFT) /* Priority bit [7] compared for pre-emption */
#  define GIC_ICCBPR_NOPREMPT      (7 << GIC_ICCBPR_SHIFT) /* No pre-emption is performed */
                                             /* Bits 3-31: Reserved */
/* Interrupt Acknowledge Register */

#define GIC_ICCIAR_INTID_SHIFT     (0)       /* Bits 0-9: Interrupt ID */
#define GIC_ICCIAR_INTID_MASK      (0x3ff << GIC_ICCIAR_INTID_SHIFT)
#  define GIC_ICCIAR_INTID(n)      ((uint32_t)(n) << GIC_ICCIAR_INTID_SHIFT)
#define GIC_ICCIAR_CPUSRC_SHIFT    (10)      /* Bits 10-12: CPU source ID */
#define GIC_ICCIAR_CPUSRC_MASK     (7 << GIC_ICCIAR_CPUSRC_SHIFT)
#  define GIC_ICCIAR_CPUSRC(n)     ((uint32_t)(n) << GIC_ICCIAR_CPUSRC_SHIFT)
                                             /* Bits 13-31: Reserved */
/* End of Interrupt Register */

#define GIC_ICCEOIR_INTID_SHIFT    (0)       /* Bits 0-9: Interrupt ID */
#define GIC_ICCEOIR_INTID_MASK     (0x3ff << GIC_ICCEOIR_INTID_SHIFT)
#  define GIC_ICCEOIR_INTID(n)     ((uint32_t)(n) << GIC_ICCEOIR_INTID_SHIFT)
#define GIC_ICCEOIR_CPUSRC_SHIFT   (10)      /* Bits 10-12: CPU source ID */
#define GIC_ICCEOIR_CPUSRC_MASK    (7 << GIC_ICCEOIR_CPUSRC_SHIFT)
#  define GIC_ICCEOIR_CPUSRC(n)    ((uint32_t)(n) << GIC_ICCEOIR_CPUSRC_SHIFT)
                                             /* Bits 13-31: Reserved */
/* Running Interrupt Register */

                                             /* Bits 0-3: Reserved */
#define GIC_ICCRPR_PRIO_SHIFT      (4)       /* Bits 4-7: Priority mask */
#define GIC_ICCRPR_PRIO_MASK       (15 << GIC_ICCRPR_PRIO_SHIFT)
#  define GIC_ICCRPR_PRIO_VALUE(n) ((uint32_t)(n) << GIC_ICCRPR_PRIO_SHIFT)
                                             /* Bits 8-31: Reserved */
/* Highest Pending Interrupt Register */

#define GIC_ICCHPIR_INTID_SHIFT    (0)       /* Bits 0-9: Interrupt ID */
#define GIC_ICCHPIR_INTID_MASK     (0x3ff << GIC_ICCHPIR_INTID_SHIFT)
#  define GIC_ICCHPIR_INTID(n)     ((uint32_t)(n) << GIC_ICCHPIR_INTID_SHIFT)
#define GIC_ICCHPIR_CPUSRC_SHIFT   (10)      /* Bits 10-12: CPU source ID */
#define GIC_ICCHPIR_CPUSRC_MASK    (7 << GIC_ICCHPIR_CPUSRC_SHIFT)
#  define GIC_ICCHPIR_CPUSRC(n)    ((uint32_t)(n) << GIC_ICCHPIR_CPUSRC_SHIFT)
                                             /* Bits 13-31: Reserved */

/* CPU Interface Implementer ID Register */

#define GIC_ICCIDR_IMPL_SHIFT      (0)       /* Bits 0-11:  Implementer */
#define GIC_ICCIDR_IMPL_MASK       (0xfff << GIC_ICCIDR_IMPL_SHIFT)
#define GIC_ICCIDR_REVISION_SHIFT  (12)      /* Bits 12-15: Revision number */
#define GIC_ICCIDR_REVISION_MASK   (15 << GIC_ICCIDR_REVISION_SHIFT)
#define GIC_ICCIDR_ARCHNO_SHIFT    (16)      /* Bits 16-19: Architecture number */
#define GIC_ICCIDR_ARCHNO_MASK     (15 << GIC_ICCIDR_ARCHNO_SHIFT)
#define GIC_ICCIDR_PARTNO_SHIFT    (20)      /* Bits 20-31: Part number */
#define GIC_ICCIDR_PARTNO_MASK     (0xfff << GIC_ICCIDR_PARTNO_SHIFT)

/* Distributor Registers */
/* Distributor Control Register */

#define GIC_ICDDCR_NONSECENAB      (1 << 0)  /* Bit 0: Enable distributor for Non-secure interrupts */
#define GIC_ICDDCR_SECENABLE       (1 << 1)  /* Bit 1: Enable distributor for Secure interrupts */
                                             /* Bits 2-31: Reserved */
/* Interrupt Controller Type Register */

#define GIC_ICDICTR_ITLINES_SHIFT  (0)       /* Bits 0-4: It lines number */
#define GIC_ICDICTR_ITLINES_MASK   (0x1f << GIC_ICDICTR_ITLINES_SHIFT)
#define GIC_ICDICTR_CPUNO_SHIFT    (5)       /* Bits 5-7: CPU number */
#define GIC_ICDICTR_CPUNO_MASK     (7 << GIC_ICDICTR_CPUNO_SHIFT)
                                             /* Bits 8-9: Reserved */
#define GIC_ICDICTR_SECEXTNS       (1 << 10) /* Bit 10: Number of security domains */
#define GIC_ICDICTR_LSPI_SHIFT     (11)      /* Bits 11-15: Number of Lockable Shared Peripheral Interrupts */
#define GIC_ICDICTR_LSPI_MASK      (0x1f << GIC_ICDICTR_LSPI_SHIFT)
                                             /* Bits 16-31: Reserved */
/* Distributor Implementer ID Register */

#define GIC_ICDIIDR_IMPL_SHIFT      (0)      /* Bits 0-11: Implementer */
#define GIC_ICDIIDR_IMPL_MASK       (0xfff << GIC_ICDIIDR_IMPL_SHIFT)
#define GIC_ICDIIDR_REVISION_SHIFT  (12)     /* Bits 12-23: Revision number */
#define GIC_ICDIIDR_REVISION_MASK   (0xfff << GIC_ICDIIDR_REVISION_SHIFT)
#define GIC_ICDIIDR_VERSION_SHIFT   (24)     /* Bits 24-31: Iimplementer version */
#define GIC_ICDIIDR_VERSION_MASK    (0xff << GIC_ICDIIDR_VERSION_SHIFT)

/* Interrupt Set-Enable.
 *
 * NOTE: In the Cortex-A9 MPCore, SGIs are always enabled. The corresponding bits
 * in the ICDISERn are read as one, write ignored
 */

#define GIC_ICDISER_INT(n)         GIC_MASK32(n)

/* Interrupt Clear-Enable.
 *
 * NOTE: In the Cortex-A9 MPCore, SGIs are always enabled. The corresponding bits
 * in the ICDICERn are read as one, write ignored
 */

#define GIC_ICDICER_INT(n)         GIC_MASK32(n)

/* Interrupt Set-Pending */

#define GIC_ICDISPR_INT(n)         GIC_MASK32(n)

/* Interrupt Clear-Pending */

#define GIC_ICDICPR_INT(n)         GIC_MASK32(n)

/* Interrupt Active Bit */

#define GIC_ICDABR_INT(n)          GIC_MASK32(n)

/* Interrupt Priority Registers */

#define GIC_ICDIPR_ID_SHIFT(n)     GIC_SHIFT4(n)
#define GIC_ICDIPR_ID_MASK(n)      GIC_MASK4(n)
#  define GIC_ICDIPR_ID(n,p)       ((uint32_t)(p) << GIC_SHIFT4(n))

/* Interrupt Processor Target Registers */

#define CPU0_TARGET                (1 << 0)
#define CPU1_TARGET                (1 << 1)
#define CPU2_TARGET                (1 << 2)
#define CPU3_TARGET                (1 << 3)

#define GIC_ICDIPTR_ID_SHIFT(n)    GIC_SHIFT4(n)
#define GIC_ICDIPTR_ID_MASK(n)     GIC_MASK4(n)
#  define GIC_ICDIPTR_ID(n,t)      ((uint32_t)(t) <<GIC_SHIFT4(n))

/* Interrupt Configuration Register */

#define INT_ICDICFR_NN             0         /* Bit n: 0= N-N Model */
#define INT_ICDICFR_1N             1         /* Bit n: 1= 1-N Model */
#define INT_ICDICFR_LEVEL          0         /* Bit n+1: 0=Level sensitive */
#define INT_ICDICFR_EDGE           2         /* Bit n+2: 1=Edge sensitive */

#define GIC_ICDICFR_ID_SHIFT(n)    GIC_SHIFT16(n)
#define GIC_ICDICFR_ID_MASK(n)     GIC_MASK16(n
#  define GIC_ICDICFR_ID(n,c)      ((uint32_t)(c) << GIC_SHIFT16(n))

/* PPI Status Register */

#define GIC_ICPPISR(n)             (1 << ((n) + 11)) /* Bits 11-15:  PPI(n) status, n=0-4 */
#  define GIC_ICPPISR_GTM          (1 << 11) /* Bit 11:  PPI[0], Global Timer */
#  define GIC_ICPPISR_NFIQ         (1 << 12) /* Bit 12:  PPI[1], FIQ, active low */
#  define GIC_ICPPISR_PTM          (1 << 13) /* Bit 13:  PPI[2], Private Timer */
#  define GIC_ICPPISR_PWDT         (1 << 14) /* Bit 14:  PPI[3], Private Watchdog */
#  define GIC_ICPPISR_NIRQ         (1 << 15) /* Bit 15:  PPI[3], IRQ, active low */

/* SPI Status Registers */

#define GIC_ICSPISR_INT(n)         GIC_MASK32(n)

/* Software Generated Interrupt Register */

#define GIC_ICDSGIR_INTID_SHIFT       (0)    /* Bits 0-9: Interrupt ID */
#define GIC_ICDSGIR_INTID_MASK        (0x3ff << GIC_ICDSGIR_INTID_SHIFT)
#  define GIC_ICDSGIR_INTID(n)        ((uint32_t)(n) << GIC_ICDSGIR_INTID_SHIFT)
                                             /* Bits 10-15: Reserved */
#define GIC_ICDSGIR_CPUTARGET_SHIFT   (16)   /* Bits 16-23: CPU target */
#define GIC_ICDSGIR_CPUTARGET_MASK    (0xff << GIC_ICDSGIR_CPUTARGET_SHIFT)
#  define GIC_ICDSGIR_CPUTARGET(n)    ((uint32_t)(n) << GIC_ICDSGIR_CPUTARGET_SHIFT)
                                             /* Bits 26-31: Reserved */
#define GIC_ICDSGIR_TGTFILTER_SHIFT   (24)   /* Bits 24-25: Target filter */
#define GIC_ICDSGIR_TGTFILTER_MASK    (3 << GIC_ICDSGIR_TGTFILTER_SHIFT)
#  define GIC_ICDSGIR_TGTFILTER_LIST  (0 << GIC_ICDSGIR_TGTFILTER_SHIFT) /* Interrupt sent to CPUs CPU target list */
#  define GIC_ICDSGIR_TGTFILTER_OTHER (1 << GIC_ICDSGIR_TGTFILTER_SHIFT) /* Interrupt is sent to all but requesting CPU */
#  define GIC_ICDSGIR_TGTFILTER_THIS  (2 << GIC_ICDSGIR_TGTFILTER_SHIFT) /* Interrupt is sent to requesting CPU only */

#endif /* __ARCH_ARM_SRC_ARMV7_A_GIC_H */