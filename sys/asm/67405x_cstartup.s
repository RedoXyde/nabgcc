;@**************************************************************************************************
;@*                                                                                                *
;@*    Copyright (C) 2004 Oki Electric Industry Co., LTD.                                          *
;@*                                                                                                *
;@*    System Name    :  ML67Q405x                                                                 *
;@*    Module Name    :  Startup routine                                                           *
;@*    File   Name    :  67405x_cstartup.s                                                         *
;@*    Revision       :  01.00                                                                     *
;@*    Date           :  2004/10/19                                                                *
;@*                                                                                                *
;@**************************************************************************************************
;@
;@ Naming covention of labels in this file:
;@
;@  ?xxx    - External labels only accessed from assembler.
;@  __xxx  - External labels accessed from or defined in C.
;@  xxx    - Labels local to one module (note: this file contains
;@           several modules).
;@  main    - The starting point of the user program.
;@

;@---------------------------------------------------------------
;@ Macros and definitions for the whole file
;@---------------------------------------------------------------

;@ Mode, corresponds to bits 0-5 in CPSR
.equ MODE_BITS,         0x1F    ;@ Bit mask for mode bits in CPSR
.equ USR_MODE,          0x10    ;@ User mode
.equ FIQ_MODE,          0x11    ;@ Fast Interrupt Request mode
.equ IRQ_MODE,          0x12    ;@ Interrupt Request mode
.equ SVC_MODE,          0x13    ;@ Supervisor mode
.equ ABT_MODE,          0x17    ;@ Abort mode
.equ UND_MODE,          0x1B    ;@ Undefined Instruction mode
.equ SYS_MODE,          0x1F    ;@ System mode

;@clock control register
.equ CLKCNT,            0xb7000010

;@system timer setting
.equ TMEN,              0xb8001004
.equ TMOVF,             0xb8001010
.equ TMRLR,             0xb8001008
.equ TMRCYC,            10
.equ RINGOSC,           16
.equ VALUE_OF_TMRLR,    65536 - (TMRCYC * RINGOSC * 1000) /16
.equ CHANGE_CLK_VALUE,  0xfffffcff

;@external memory controller
.equ BWC,               0x78100000
.equ RAMAC,             0x78100008
.equ IO0AC,             0x7810000C
.equ BWC_VALUE,         0xA0
.equ RAMAC_VALUE,       0x2
.equ IO0AC_VALUE,       0x1

;@---------------------------------------------------------------
;@ ?RESET
;@ Reset Vector.
;@ Normally, segment INTVEC is linked at address 0.
;@ For debugging purposes, INTVEC may be placed at other
;@ addresses.
;@ A debugger that honors the entry point will start the
;@ program in a normal way even if INTVEC is not at address 0.
;@---------------------------------------------------------------
.section .intvec
    .global  __program_start
    .global  undef_handler, swi_handler, prefetch_handler, \
             data_handler, irq_handler, fiq_handler
    .arm  ;@ Always ARM mode after reset
__program_start:
    .org  0x00
    .ifdef FLASHCODE
      b  boot ;@ Relative branch allows remap
    .else
      ldr  pc,=boot ;@ Absolute jump can reach above 0x2000000
    .endif
    .org  0x04
      ;@ b       0x04
      ldr  pc,=undef_handler
    .org  0x08
      ldr  pc,=swi_handler
    .org  0x0c
      ;@b       0x0c
      ldr  pc,=prefetch_handler
    .org  0x10
      ;@b       0x10
      ldr  pc,=data_handler
    .org     0x14
      nop
    .org  0x18
      ldr  pc,=irq_handler
    .org  0x1c
      ldr  pc,=fiq_handler

    ;@ Constant table entries (for ldr pc) will be placed at 0x20
    .org  0x20
;@    ENDMOD  __program_start
                ;@ENDMOD


;@---------------------------------------------------------------
;@ ?BOOT
;@---------------------------------------------------------------
    .section .startup.boot
    .arm
    .global boot
boot:
  b           cstartup

;@---------------------------------------------------------------
;@ ?CSTARTUP
;@---------------------------------------------------------------
    .section .startup.cstartup
    .global .main
    .arm
cstartup:

;@ Add initialization nedded before setup of stackpointers here
;@ --- ring oscillator is srcsel?
    LDR  R0,=CLKCNT
    LDR  R1,[R0]
    AND  R1,R1,#0x300
    CMP  R1,#0x100
    BNE  _not_ringosc1

;@ --- set system timer
    MOV  R0,#0x0
    LDR  R1,=TMEN
    STR  R0,[R1]
    MOV  R0,#0x1
    LDR  R1,=TMOVF
    STR  R0,[R1]
    ;@ set 10msec cycle
    LDR  R0,=VALUE_OF_TMRLR
    LDR  R1,=TMRLR
    STR  R0,[R1]
    ;@ start system timer
    MOV  R0,#0x1
    LDR  R1,=TMEN
    STR  R0,[R1]

_not_ringosc1:

;@ Initialize the stack pointers.
;@ The pattern below can be used for any of the exception stacks:
;@ FIQ, IRQ, SVC, ABT, UND, SYS.
;@ The USR mode uses the same stack as SYS.
;@ The stack segments must be defined in the linker command file,
;@ and be declared above.

                mrs     r0,cpsr                             ;@ Original PSR value
                bic     r0,r0,#MODE_BITS                    ;@ Clear the mode bits
                orr     r0,r0,#IRQ_MODE                     ;@ Set IRQ mode bits
                msr     cpsr_c,r0                           ;@ Change the mode
                @ldr     sp,=SFE(IRQ_STACK) & 0xFFFFFFF8     ;@ End of IRQ_STACK

                bic     r0,r0,#MODE_BITS                    ;@ Clear the mode bits
                orr     r0,r0,#FIQ_MODE                     ;@ Set System mode bits
                msr     cpsr_c,r0                           ;@ Change the mode
                @ldr     sp,=SFE(FIQ_STACK) & 0xFFFFFFF8     ;@ End of FIQ_STACK

                bic     r0,r0,#MODE_BITS                    ;@ Clear the mode bits
                orr     r0,r0,#SVC_MODE                     ;@ Set System mode bits
                msr     cpsr_c,r0                           ;@ Change the mode
                @ldr     sp,=SFE(SVC_STACK) & 0xFFFFFFF8        ;@ End of SVC_STACK

;@ --- ring oscillator is srcsel?
    LDR  R0,=CLKCNT
    LDR  R1,[R0]
    AND  R1,R1,#0x300
    CMP  R1,#0x100
    BNE  _not_ringosc2

;@ --- timer overflow wait
_wait_ovf:
    LDR  R1,=TMOVF
    LDR  R0,[R1]
    CMP  R0,#0x1
    BNE  _wait_ovf

;@ --- change to main clk from ring oscillator
    LDR  R1,=CLKCNT
    LDR  R0,[R1]
    LDR  R1,=CHANGE_CLK_VALUE
    AND  R0,R0, R1
    LDR  R1,=CLKCNT
    STR  R0,[R1]
_not_ringosc2:
;@ init external memory controller
    ;@ set BWC
    LDR  R0,=BWC_VALUE
    LDR  R1,=BWC
    STR  R0,[R1]
    ;@ set RAMAC
    LDR  R0,=RAMAC_VALUE
    LDR  R1,=RAMAC
    STR  R0,[R1]
    ;@ set IO0AC
    LDR  R0,=IO0AC_VALUE
    LDR  R1,=IO0AC
    STR  R0,[R1]

;@ Continue to ?main for more IAR specific system startup
    ldr     r0,=main
    bx      r0

undef_handler:
  b undef_handler

prefetch_handler:
  b prefetch_handler

data_handler:
  b data_handler

  .end
