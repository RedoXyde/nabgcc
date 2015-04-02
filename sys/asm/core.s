
.set    MODE_USR, 0x10
.set    MODE_FIQ, 0x11
.set    MODE_IRQ, 0x12
.set    MODE_SVC, 0x13
.set    MODE_ABT, 0x17
.set    MODE_UND, 0x1B
.set    MODE_SYS, 0x1F

.equ    I_BIT, 0x80
.equ    F_BIT, 0x40

.text

.balign 16
.thumb
.thumb_func
.global _port_disable_thumb
_port_disable_thumb:
  mov     r3, pc
  bx      r3
  .arm
  mrs     r3, CPSR
  orr     r3, #0xC0
  msr     CPSR_c, r3
  bx      lr

.balign 16
.thumb
.thumb_func
.global _port_enable_thumb
_port_enable_thumb:
  mov     r3, pc
  bx      r3
  .arm
  mrs     r3, CPSR
  bic     r3, #0xC0
  msr     CPSR_c, r3
  bx      lr
