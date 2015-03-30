;@********************************************************************************
;@*                                                                              *
;@*    Copyright (C) 2002 Oki Electric Industry Co., LTD.                        *
;@*                                                                              *
;@*    System Name    :  ML67405x                                                *
;@*    Module Name    :  Reentrant irq handler routine                           *
;@*    File   Name    :  reentrant_irq_handler.s                                 *
;@*    Revision       :  01.00                                                   *
;@*    Date           :  2005/04/20 initial version                              *
;@*                                                                              *
;@********************************************************************************

        ;@rseg ICODE:CODE(2)
        .arm

;@   <<< bit field of status registers (CPSR, SPSR) >>>
;@   31  30  29  28        7   6   5   4   3   2   1   0
;@ +---+---+---+---+-----+---+---+---+---+---+---+---+---+
;@ | N | Z | C | V | - - | I | F | T | M4| M3| M2| M1| M0|
;@ +---+---+---+---+-----+---+---+---+---+---+---+---+---+
;@ M0-M4 10010 : IRQ mode
;@       11111 : SYSTEM mode
;@   T       0 : ARM mode
;@           1 : THUMB mode
;@   F       0 : FIQ is allowed
;@           1 : FIQ is not allowed
;@   I       0 : IRQ is allowed
;@           1 : IRQ is not allowed
;@ N,Z,C,V     : condition flags. flags change with the results of ALU.
;@
;@
;@   <<< use situation of registers >>>
;@        IRQ         change to       handler   change to  IRQ
;@       start         SYS mode     start  end  IRQ mode   end
;@       --|--------------|-----------|-----|-----|--------|-->
;@      r0 +--+--+--@========@========@--X--+--+--+--+--+--+ r0
;@      r1 +--+--+--+--+--+--+--@=====@--X--+--+--+--+--+--+ r1
;@      r2 +--+--+--+--+--+--+--+--+--@--X--+--+--+--+--@--+ r2
;@      r3 +--+--+--+--+--@--+--+--+--+--X--+--+--@--+--+--+ r3
;@      r4 +--@========@=================O=====@=====@--+--+ r4
;@      r5 +--+--@=======================O==============@--+ r5
;@  r6-r11 +--+--+--+--+--+--+--+--+--+--O--+--+--+--+--+--+ r6-r11
;@     r12 +--+--+--+--+--+--+--+--+--+--X--+--+--+--+--+--+ r12
;@  lr_IRQ @=============== = = = = = = = = = = = =========@ lr_IRQ
;@  lr_USR - - - - - - - - --+--+--@=====O==@--+-- - - - - - lr_USR
;@spsr_IRQ @=============== = = = = = = = = = = = =========@ spsr_IRQ
;@         |<------------>|<--------------------->|<------>|
;@             IRQ mode           SYS mode         IRQ mode
;@
;@ now some standard definitions...
.equ Mode_USR, 0x10
.equ Mode_IRQ, 0x12
.equ Mode_SVC, 0x13
.equ Mode_SYS, 0x1F

.equ I_Bit   , 0x80
.equ F_Bit   , 0x40

.equ GPCTL   , 0xb7000000  ;@ address of GPCTL

.equ IRQSIZE , 64          ;@ number of IRQ interrupt factor.
.equ IRQ_BASE, 0x78000000  ;@ base address of registers about IRQ.
.equ FIQ 	, 0x78000008

;@;@ definition of alias of registers
;@sp_IRQ               RN      sp ;@ r13
;@lr_IRQ               RN      lr ;@ r14
;@sp_USR               RN      sp ;@ r13
;@lr_USR               RN      lr ;@ r14
;@irq_handler_table    RN      r1 ;@ address of irq_handler_table is saved.
;@cil_clear            RN      r2 ;@ value of this is set to CILCL register.
;@address_of_handler   RN      r2 ;@ address of handler corresponding to
                                ;@ intrrupt factor is sabed.
;@cpsr_tmp             RN      r3 ;@
;@saved_spsr_irq       RN      r4 ;@ value of spsr_irq is saved.
;@irq_base             RN      r5 ;@ base address of registers about IRQ is saved.
;@irn                  RN      r6 ;@ value of IRN register is saved.

        .global  IRQ_HANDLER_TABLE
        .global  count_interval
        .global  FIQ_handler

        .global  fiq_handler
        .global  irq_handler

;@**********************************************************************
;@*  IRQ Handler                                                       *
;@*  Function : void IRQ_Handler(void)                                 *
;@*      Parameters                                                    *
;@*          input  : nothing                                          *
;@*          output : nothing                                          *
;@**********************************************************************
irq_handler:
        SUB     lr, lr, #4;@ construct the return address

        ;@;@ registers which may be overwritten are saved.(IRQ mode)
        ;@;@ r0-r5 : these are used in this handler.
        ;@;@ lr_IRQ(r14) : if IRQ handler is reentered, this is overwritten.
        ;@;@ registers which may be overwritten are r1-r6,lr_IRQ(r14).
        STMFD   sp!, {r1-r6, lr}

        ;@;@ spsr_IRQ is saved to saved_spsr_irq(r4).
        ;@;@ if IRQ handler is reentered, spsr_IRQ is overwritten.
        MRS     r4, spsr

        ;@;@ check 'I' bit of spsr
        ;@;@ please refer to the following section of FAQ at the ARM website for details.
        ;@;@   FAQ - ARM Cores
        ;@;@     4. Interrupt behaviour:
        ;@;@       - What happens if an interrupt occurs as it is being disabled?
        TST     r4, #I_Bit
        LDMNEFD sp!, {r0-r5, pc}^

        ;@;@ IRQ number is got from IRN register. IRQ number is saved to irn(r6).
        ;@;@ after the value of IRN register is read,
        ;@;@ the bit of CIL register corresponding to interrupt level is set.
        MOV     r5, #IRQ_BASE     ;@ IRQ_BASE(0x78000000) is saved to irq_base(r5).
        LDR     r6, [r5, #0x14]   ;@ IRQ number is saved to irn(r6).

        ;@;@ mode is changed into SYS mode. and IRQ is enabled.
        ;@;@ if IRQ is enabled before a CIL register is set,
        ;@;@ this program does not operate appropriately.
        ;@;@ in SYS mode, USR mode registers are used.
        TST     r4, #F_Bit              ;@ FIQ is available ?
        MOVEQ   r3, #Mode_SVC     ;@ available
        MOVNE   r3, #Mode_SVC|F_Bit;@ not abailable
        MSR     cpsr_c, r3        ;@ change to SYS mode and enable IRQ

        ;@;@ check IRQ number
        ;@;@ if IRQ number is invalid(irn > IRQSIZE),
        ;@;@ this routine doesn't branch to handler corresponding to interrupt's factor.
        CMP     r6, #IRQSIZE
        BCS     LABEL

        ;@;@ USR mode registers which may be overwritten
        ;@;@ and registers which are not saved by callee are saved.
        ;@;@ -- USR mode registers which may be overwritten --
        ;@;@ lr_USR(r14) : this is overwritten.
        ;@;@ -- registers which is not saved by callee --
        ;@;@ r0-r3,r12 : these aren't saved by callee.
        ;@;@             but there is no influence even if values of r1-r3 change.
        ;@;@ registers which need to be saved are r0, r12 and lr_USR.
        STMFD   sp!, {r0, r12, lr};@ R0, R12 and lr_USR(r14) are saved.

        ;@;@ address of IRQ_HANDLER_TABLE is got.
        ;@;@ address of IRQ_HANDLER_TABLE is saved to irq_handler_table(r1).
        LDR     r1, =IRQ_HANDLER_TABLE

        ;@;@ branch to handler corresponding to interrupt's factor
        BL      BRANCH_TO_HANDLER

        LDMFD   sp!, {r0, r12, lr};@ R0, R12 and link register is restored.
LABEL:

        ;@;@ mode is changed to IRQ mode. and IRQ is disabled.
        ;@;@ if IRQ is still being allowed after CIL register is cleared,
        ;@;@ this program does not operate appropriately.
        TST     r4, #F_Bit;@ FIQ is available ?
        MOVEQ   r3, #Mode_IRQ|I_Bit;@ available
        MOVNE   r3, #Mode_IRQ|I_Bit|F_Bit;@ not abailable
        MSR     cpsr_c, r3        ;@ change to IRQ mode and disable IRQ
        MSR     spsr_cf, r4       ;@ spsr_IRQ is restored.

        ;@;@ the most significant '1' bit of CIL register is cleared.
        ;@;@ if arbitrary value is written in CILCL register,
        ;@;@ the most significant '1' bit of CIL register will be cleared.
        STR     r2, [r5, #0x28];@ arbitrary value is written to
                                            ;@ CILCL register.

        ;@;@ saved registers are restored, and control is returned from IRQ.
        LDMFD   sp!, {r1-r6, pc}^
;@ end of IRQ_Handler

;@**********************************************************************
;@*  Branch to handler corresponding to interrupt's factor.            *
;@*  Handler doesn't return to this function.                          *
;@*  Handler directry returns to IRQ_Handler.                          *
;@*  Function : void BRANCH_TO_HANDLER(void)                           *
;@*      Parameters                                                    *
;@*          input  : nothing                                          *
;@*          output : nothing(This function doesn't return.)           *
;@**********************************************************************
BRANCH_TO_HANDLER:
        ;@;@ address of handler and information that handler is ARM or THUMB
        ;@;@ is saved at irq_handler_table + irn*4.
        LDR     r2, [r1, r6, lsl #2];@
        BX      r2      ;@ branch to handler corresponding to
                        ;@ interrupt's factor
;@ end of BRANCH_TO_HANDLER

;@**********************************************************************
;@*  fir_handler                                                       *
;@*  the count_interval is taken from FIQ sample                       *
;@*  fiq_handler handles FIQ interrupt.                                *
;@*  Function : void fiq_handler(void)                                 *
;@*      Parameters                                                    *
;@*          input  : nothing                                          *
;@*          output : nothing                                          *
;@**********************************************************************
;@ --- The FIQ handler starts here
fiq_handler:
        SUB     lr, lr, #4              ;@ construct the return address
        STMFD   sp!, {r0-r3, lr}        ;@ store low registers to FIQ stack

        BL      BRANCH_TO_FIQ_HANDLER

        LDMFD   sp!, {r0-r3, pc}^  ;@ restore registers & return from FIQ

BRANCH_TO_FIQ_HANDLER:
        LDR     r2, =FIQ_handler
        BX      r2
;@ end of BRANCH_TO_FIQ_HANDLER

        .END
