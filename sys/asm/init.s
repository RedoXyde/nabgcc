;*******************************************************************************
;   Init.s
;   JOB60842サンプルプログラム
;   ARM7TDMI スタートアップルーチン
;
;   Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
;     All rights reserved.
;
;   更新履歴
;   Mar.31,2003 rev1.00:新規作成
;*******************************************************************************

			AREA	Init, CODE, READONLY

;-----------------------------------------------------------------------------
; Now some standard definitions...

Mode_USR	EQU		0x10
Mode_FIQ	EQU		0x11
Mode_IRQ	EQU		0x12
Mode_SVC	EQU		0x13
Mode_SYS	EQU		0x1F

I_Bit		EQU		0x80
F_Bit		EQU		0x40

;-----------------------------------------------------------------------------
; Locations of various things in our memory system

RAM_Base	EQU		0x10000000				; for ML674000
RAM_Size	EQU		0x00002000				; 8KByte

RAM_Limit	EQU		RAM_Base+RAM_Size		;

SVC_SSize	EQU		128
FIQ_SSize	EQU		128
IRQ_SSize	EQU		1024
USR_SSize	EQU		RAM_Size-SVC_SSize-FIQ_SSize-IRQ_SSize

IRQ_Stack	EQU		RAM_Limit				; followed by IRQ stack
FIQ_Stack	EQU		IRQ_Stack-IRQ_SSize		; followed by FIQ stack
SVC_Stack	EQU		FIQ_Stack-FIQ_SSize		; followed by SVC stack
USR_Stack	EQU		SVC_Stack-SVC_SSize		; followed by USR stack

;-----------------------------------------------------------------------------
			IMPORT	IRQ_Handler
;			IMPORT	FIQ_Handler

;-----------------------------------------------------------------------------
; --- Define entry point
			EXPORT	__main	; defined to ensure that C runtime system
__main						; is not linked in
			ENTRY

; --- Setup interrupt / exception vectors
			B		Reset_Handler
			NOP		;Undefined_Handler
			NOP		;SWI_Handler
			NOP		;Prefetch_Handler
			NOP		;Abort_Handler
			B		Error_Handler 	;Reserved vector
			B		IRQ_Handler
			NOP		;FIQ_Handler

;-----------------------------------------------------------------------------
; The RESET entry point
			EXPORT	Reset_Handler	;
Reset_Handler
; --- Initialise stack pointer registers
; Enter IRQ mode and set up the IRQ stack pointer
			MOV		R0, #Mode_IRQ:OR:I_Bit			 ; FIQ enable
			MSR		CPSR_c, R0
			LDR		R13, =IRQ_Stack

;-----------------------------------------------------------------------------
; Enter FIQ mode and set up the FIQ stack pointer
			MOV		R0, #Mode_FIQ:OR:I_Bit:OR:F_Bit ; No interrupts
			MSR		CPSR_c, R0
			LDR		R13, =FIQ_Stack

;-----------------------------------------------------------------------------
; Set up the SVC stack pointer last and return to SVC mode
			MOV		R0, #Mode_SVC:OR:I_Bit:OR:F_Bit ; No interrupts
			MSR		CPSR_c, R0
			LDR		R13, =SVC_Stack

;-----------------------------------------------------------------------------
; Set up other stack pointers if necessary
			; ...

;-----------------------------------------------------------------------------
; --- Initialise memory system
			; ...

;-----------------------------------------------------------------------------
; スタック使用量をチェックするために領域の初期化
;	IRQスタック領域の初期化
			LDR		r1, =IRQ_Stack
			LDR		r3, =FIQ_Stack
			MOV		r2, #0xAA			; 0x000000AAで埋める
irqSTK		CMP		r3, r1
			STRCC	r2, [r3], #4
			BCC		irqSTK
;	IRQスタック領域の初期化
			LDR		r1, =FIQ_Stack
			LDR		r3, =SVC_Stack
			MOV		r2, #0xBB			; 0x000000BBで埋める
fiqSTK		CMP		r3, r1
			STRCC	r2, [r3], #4
			BCC		fiqSTK
;	SVCスタック領域の初期化
			LDR		r1, =SVC_Stack
			LDR		r3, =USR_Stack
			MOV		r2, #0xCC			; 0x000000CCで埋める
svcSTK		CMP		r3, r1
			STRCC	r2, [r3], #4
			BCC		svcSTK
;	USRスタック領域の初期化
			LDR		r1, =USR_Stack
			LDR		r3, =RAM_Base
			MOV		r2, #0xDD			; 0x000000DDで埋める
usrSTK		CMP		r3, r1
			STRCC	r2, [r3], #4
			BCC		usrSTK

;-----------------------------------------------------------------------------
; --- Initialise critical IO devices
			; ...

;-----------------------------------------------------------------------------
; --- Initialise interrupt system variables here

			MOV		r0,	#0xB7000000			; for ML674000
			MOV		r1, #0x04				; Write data GPCTL register 
			STRB	r1, [r0, #0]			; to make XA[23:19] effective.

			MOV		r0,	#0x00100000			;
			ADD		r0,	r0, #0x78000000		; for ML674000
			MOV		r1, #0x28				; Write data in BWC register 
			STRB	r1, [r0, #0]			; to make the external RAM access effective.

;-----------------------------------------------------------------------------
; --- Initialise memory required by C code
			IMPORT	|Image$$RO$$Base|		; start of ROM code
			IMPORT	|Image$$RO$$Limit|		; End of ROM code (=start of ROM data)
			IMPORT	|Image$$RW$$Base|		; Base of RAM to initialise
			IMPORT	|Image$$ZI$$Base|		; Base and limit of area
			IMPORT	|Image$$ZI$$Limit|		; to zero initialise
			IMPORT	__rt_lib_init
			IMPORT	|__c_initialise|, WEAK
			IMPORT	|__c_finalise|, WEAK

			LDR		r0, =|Image$$RO$$Limit| ; Get pointer to ROM data
			LDR		r1, =|Image$$RW$$Base|	; and RAM copy
			LDR		r3, =|Image$$ZI$$Base|	; Zero init base => top of initialised data
			CMP		r0, r1					; Check that they are different
			BEQ		%1
0			CMP		r1, r3					; Copy init data
			LDRCC	r2, [r0], #4
			STRCC	r2, [r1], #4
			BCC		%0
1			LDR		r1, =|Image$$ZI$$Limit| ; Top of zero init segment
			MOV		r2, #0
2			CMP		r3, r1					; Zero init
			STRCC	r2, [r3], #4
			BCC		%2

;-----------------------------------------------------------------------------
; --- Now change to user mode and set up user mode stack.
			MOV		R0, #Mode_USR			; IRQ and FIQ enabled
			MSR		CPSR_c, R0
			LDR		sp, =USR_Stack

;-----------------------------------------------------------------------------
; --- Now we enter the C code

			IMPORT	main
		[ :DEF:THUMB
			ORR		lr, pc, #1
			BX		lr
			CODE16					; Next instruction will be Thumb
		]
			BL		main

; In a real application we wouldn't normally expect to return, however
; in case we do the debug monitor swi is used to halt the application.
			MOV		r0, #0x18		; angel_SWIreason_ReportException
			LDR		r1, =0x20026	; ADP_Stopped_ApplicationExit
		[ :DEF: THUMB
			SWI 0xAB				; Angel semihosting Thumb SWI
			NOP						; If we are in Thumb state here,
			NOP						; need to pad end of code so that
									; literal pool is greater than
									; 8 bytes away.
			|
			SWI		0x123456		; Angel semihosting ARM SWI
		]

;-----------------------------------------------------------------------------
			EXPORT	sti
sti
			MRS 	a1, CPSR
			BIC 	a1, a1, #0x80
			MSR 	CPSR_c, a1
			BX		LR

;-----------------------------------------------------------------------------
			EXPORT	cli
cli
			MRS 	a1, CPSR
			ORR 	a1, a1, #0x80
			MSR 	CPSR_c, a1
			BX		LR
	
;-----------------------------------------------------------------------------
Error_Handler
			B	Error_Handler		; This is a dead loop.
			
			END						; End of file
