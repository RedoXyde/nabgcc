/*******************************************************************************
	ml674000.h
	JOB60842�T���v���v���O����
	ML674000 ���W�X�^��`�t�@�C��

	Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
	  All rights reserved.

	�X�V����
	Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#ifndef _ML674000_H_
#define _ML674000_H_

#define ML674000

/*----------------------------------------------------------------------------
  ���W�X�^�A�h���X��`
----------------------------------------------------------------------------*/
#define IRQ         0x78000000ul  /* IRQ���W�X�^                                   */
#define IRQS        0x78000004ul  /* IRQ�\�t�g���W�X�^                             */
#define FIQ         0x78000008ul  /* FIQ���W�X�^                                   */
#define FIQRAW      0x7800000Cul  /* FIQRAW���W�X�^                                */
#define FIQEN       0x78000010ul  /* FIQ�C�l�[�u�����W�X�^                         */
#define IRN         0x78000014ul  /* IRQ�ԍ����W�X�^                               */
#define CIL         0x78000018ul  /* ��IRQ���x�����W�X�^                           */
#define ILC0        0x78000020ul  /* IRQ���x�����䃌�W�X�^0                        */
#define ILC1        0x78000024ul  /* IRQ���x�����䃌�W�X�^1                        */
#define CILCL       0x78000028ul  /* ��IRQ���x���N���A���W�X�^                     */
#define CILE        0x7800002Cul  /* ��IRQ���x���G���R�[�h���W�X�^                 */
#define BWC         0x78100000ul  /* �o�X���R���g���[�����W�X�^                    */
#define ROMAC       0x78100004ul  /* �O��ROM�A�N�Z�X�R���g���[�����W�X�^           */
#define RAMAC       0x78100008ul  /* �O��RAM�A�N�Z�X�R���g���[�����W�X�^           */
#define IO0AC       0x7810000Cul  /* �O��IO�o���N0�̃A�N�Z�X�R���g���[�����W�X�^   */
#define IO1AC       0x78100010ul  /* �O��IO�o���N1�̃A�N�Z�X�R���g���[�����W�X�^   */
#define DBWC        0x78180000ul  /* DRAM�o�X���R���g���[�����W�X�^                */
#define DRMC        0x78180004ul  /* DRAM�R���g���[�����W�X�^                      */
#define DRPC        0x78180008ul  /* DRAM�����p�����[�^�R���g���[�����W�X�^        */
#define SDMD        0x7818000Cul  /* SDRAM���[�h���W�X�^                           */
#define DCMD        0x78180010ul  /* DRAM�R�}���h���W�X�^                          */
#define RFSH0       0x78180014ul  /* DRAM���t���b�V���T�C�N���R���g���[�����W�X�^0 */
#define RDWC        0x78180018ul  /* DRAM�p���[�_�E���R���g���[�����W�X�^          */
#define RFSH1       0x7818001Cul  /* DRAM���t���b�V���T�C�N���R���g���[�����W�X�^1 */
#define DMAMOD      0x7BE00000ul  /* DMA���[�h���W�X�^                             */
#define DMASTA      0x7BE00004ul  /* DMA�X�e�[�^�X���W�X�^                         */
#define DMAINT      0x7BE00008ul  /* DMA�I���X�e�[�^�X���W�X�^                     */
#define DMACMSK0    0x7BE00100ul  /* DMA�`���l���}�X�N���W�X�^                     */
#define DMACTMOD0   0x7BE00104ul  /* DMA�]�����[�h���W�X�^                         */
#define DMACSAD0    0x7BE00108ul  /* DMA�]�����A�h���X���W�X�^                     */
#define DMACDAD0    0x7BE0010Cul  /* DMA�]����A�h���X���W�X�^                     */
#define DMACSIZ0    0x7BE00110ul  /* DMA�]���񐔃��W�X�^                           */
#define DMACCINT0   0x7BE00114ul  /* DMA�I���X�e�[�^�X�N���A���W�X�^               */
#define DMACMSK1    0x7BE00200ul  /* DMA�`���l���}�X�N���W�X�^                     */
#define DMACTMOD1   0x7BE00204ul  /* DMA�]�����[�h���W�X�^                         */
#define DMACSAD1    0x7BE00208ul  /* DMA�]�����A�h���X���W�X�^                     */
#define DMACDAD1    0x7BE0020Cul  /* DMA�]����A�h���X���W�X�^                     */
#define DMACSIZ1    0x7BE00210ul  /* DMA�]���񐔃��W�X�^                           */
#define DMACCINT1   0x7BE00214ul  /* DMA�I���X�e�[�^�X�N���A���W�X�^               */
#define IRCL        0x7BF00004ul  /* IRQ�N���A���W�X�^                             */
#define IRQA        0x7BF00010ul  /* IRQA���W�X�^                                  */
#define IDM         0x7BF00014ul  /* IRQ���o���[�h�ݒ背�W�X�^                     */
#define ILC         0x7BF00018ul  /* IRQ���x�����䃌�W�X�^                         */
#define ADCON0      0xB6000000ul  /* A/D�R���g���[��0���W�X�^                      */
#define ADCON1      0xB6000004ul  /* A/D�R���g���[��1���W�X�^                      */
#define ADCON2      0xB6000008ul  /* A/D�R���g���[��2���W�X�^                      */
#define ADINT       0xB600000Cul  /* A/D ���荞�ݐ��䃌�W�X�^                      */
#define ADFINT      0xB6000010ul  /* A/D �������荞�ݔ������W�X�^                  */
#define ADR0        0xB6000014ul  /* A/D���U���g0���W�X�^                          */
#define ADR1        0xB6000018ul  /* A/D���U���g1���W�X�^                          */
#define ADR2        0xB600001Cul  /* A/D���U���g2���W�X�^                          */
#define ADR3        0xB6000020ul  /* A/D���U���g3���W�X�^                          */
#define ADR4        0xB6000024ul  /* A/D���U���g4���W�X�^                          */
#define ADR5        0xB6000028ul  /* A/D���U���g5���W�X�^                          */
#define ADR6        0xB600002Cul  /* A/D���U���g6���W�X�^                          */
#define ADR7        0xB6000030ul  /* A/D���U���g7���W�X�^                          */
#define GPCTL       0xB7000000ul  /* �|�[�g�@�\�I�����W�X�^                        */
#define BCKCTL      0xB7000004ul  /* �@�\�P�ʃN���b�N���䃌�W�X�^                  */
#define GPPOA       0xB7A00000ul  /* �|�[�gA�o�̓��W�X�^                           */
#define GPPIA       0xB7A00004ul  /* �|�[�gA���̓��W�X�^                           */
#define GPPMA       0xB7A00008ul  /* �|�[�gA���[�h���W�X�^                         */
#define GPIEA       0xB7A0000Cul  /* �|�[�gA���荞�݃C�l�[�u�����W�X�^             */
#define GPIPA       0xB7A00010ul  /* �|�[�gA���荞�݋ɐ����W�X�^                   */
#define GPISA       0xB7A00014ul  /* �|�[�gA���荞�݃X�e�[�^�X���W�X�^             */
#define GPPOB       0xB7A00020ul  /* �|�[�gB�o�̓��W�X�^                           */
#define GPPIB       0xB7A00024ul  /* �|�[�gB���̓��W�X�^                           */
#define GPPMB       0xB7A00028ul  /* �|�[�gB���[�h���W�X�^                         */
#define GPIEB       0xB7A0002Cul  /* �|�[�gB���荞�݃C�l�[�u�����W�X�^             */
#define GPIPB       0xB7A00030ul  /* �|�[�gB���荞�݋ɐ����W�X�^                   */
#define GPISB       0xB7A00034ul  /* �|�[�gB���荞�݃X�e�[�^�X���W�X�^             */
#define UARTRBR     0xB7B00000ul  /* Receiver Buffer Register                      */
#define UARTTHR     0xB7B00000ul  /* Transmitter Holding Register                  */
#define UARTDLL     0xB7B00000ul  /* Divisor Latch (LSB)                           */
#define UARTIER     0xB7B00004ul  /* Interrupt Enable Register                     */
#define UARTDLM     0xB7B00004ul  /* Divisor Latch (MSB)                           */
#define UARTIIR     0xB7B00008ul  /* Interrupt Identification Register             */
#define UARTFCR     0xB7B00008ul  /* FIFO Control Register                         */
#define UARTLCR     0xB7B0000Cul  /* Line Control Register                         */
#define UARTMCR     0xB7B00010ul  /* Modem Control Register                        */
#define UARTLSR     0xB7B00014ul  /* Line Status Register                          */
#define UARTMSR     0xB7B00018ul  /* Modem Status Register                         */
#define UARTSCR     0xB7B0001Cul  /* Scratch Register                              */
#define PWR0        0xB7D00000ul  /* PWM���W�X�^0                                  */
#define PWCY0       0xB7D00004ul  /* PWM�������W�X�^0                              */
#define PWC0        0xB7D00008ul  /* PWM�J�E���^0                                  */
#define PWCON0      0xB7D0000Cul  /* PWM�R���g���[�����W�X�^0                      */
#define PWR1        0xB7D00020ul  /* PWM���W�X�^1                                  */
#define PWCY1       0xB7D00024ul  /* PWM�������W�X�^1                              */
#define PWC1        0xB7D00028ul  /* PWM�J�E���^1                                  */
#define PWCON1      0xB7D0002Cul  /* PWM�R���g���[�����W�X�^1                      */
#define PWINTSTS    0xB7D0003Cul  /* �o�v�l���荞�݃X�e�[�^�X���W�X�^              */
#define WDTCON      0xB7E00000ul  /* �E�H�b�`�h�b�O�^�C�}���䃌�W�X�^              */
#define WDTBCON     0xB7E00004ul  /* �^�C���x�[�X�J�E���^���䃌�W�X�^              */
#define WDSTAT      0xB7E00014ul  /* �X�e�[�^�X���W�X�^                            */
#define TIMECNTL0   0xB7F00000ul  /* �^�C�}0���䃌�W�X�^                           */
#define TIMEBASE0   0xB7F00004ul  /* �^�C�}0�x�[�X���W�X�^                         */
#define TIMECNT0    0xB7F00008ul  /* �^�C�}0�J�E���^���W�X�^                       */
#define TIMECMP0    0xB7F0000Cul  /* �^�C�}0�R���y�A���W�X�^                       */
#define TIMESTAT0   0xB7F00010ul  /* �^�C�}0�X�e�[�^�X���W�X�^                     */
#define TIMECNTL1   0xB7F00020ul  /* �^�C�}1���䃌�W�X�^                           */
#define TIMEBASE1   0xB7F00024ul  /* �^�C�}1�x�[�X���W�X�^                         */
#define TIMECNT1    0xB7F00028ul  /* �^�C�}1�J�E���^���W�X�^                       */
#define TIMECMP1    0xB7F0002Cul  /* �^�C�}1�R���y�A���W�X�^                       */
#define TIMESTAT1   0xB7F00030ul  /* �^�C�}1�X�e�[�^�X���W�X�^                     */
#define TIMECNTL2   0xB7F00040ul  /* �^�C�}2���䃌�W�X�^                           */
#define TIMEBASE2   0xB7F00044ul  /* �^�C�}2�x�[�X���W�X�^                         */
#define TIMECNT2    0xB7F00048ul  /* �^�C�}2�J�E���^���W�X�^                       */
#define TIMECMP2    0xB7F0004Cul  /* �^�C�}2�R���y�A���W�X�^                       */
#define TIMESTAT2   0xB7F00050ul  /* �^�C�}2�X�e�[�^�X���W�X�^                     */
#define TIMECNTL3   0xB7F00060ul  /* �^�C�}3���䃌�W�X�^                           */
#define TIMEBASE3   0xB7F00064ul  /* �^�C�}3�x�[�X���W�X�^                         */
#define TIMECNT3    0xB7F00068ul  /* �^�C�}3�J�E���^���W�X�^                       */
#define TIMECMP3    0xB7F0006Cul  /* �^�C�}3�R���y�A���W�X�^                       */
#define TIMESTAT3   0xB7F00070ul  /* �^�C�}3�X�e�[�^�X���W�X�^                     */
#define TIMECNTL4   0xB7F00080ul  /* �^�C�}4���䃌�W�X�^                           */
#define TIMEBASE4   0xB7F00084ul  /* �^�C�}4�x�[�X���W�X�^                         */
#define TIMECNT4    0xB7F00088ul  /* �^�C�}4�J�E���^���W�X�^                       */
#define TIMECMP4    0xB7F0008Cul  /* �^�C�}4�R���y�A���W�X�^                       */
#define TIMESTAT4   0xB7F00090ul  /* �^�C�}4�X�e�[�^�X���W�X�^                     */
#define TIMECNTL5   0xB7F000A0ul  /* �^�C�}5���䃌�W�X�^                           */
#define TIMEBASE5   0xB7F000A4ul  /* �^�C�}5�x�[�X���W�X�^                         */
#define TIMECNT5    0xB7F000A8ul  /* �^�C�}5�J�E���^���W�X�^                       */
#define TIMECMP5    0xB7F000ACul  /* �^�C�}5�R���y�A���W�X�^                       */
#define TIMESTAT5   0xB7F000B0ul  /* �^�C�}5�X�e�[�^�X���W�X�^                     */
#define CLKSTP      0xB8000004ul  /* CLK ��~���W�X�^                              */
#define CGBCNT0     0xB8000008ul  /* �N���b�N�I�����W�X�^                          */
#define CKWT        0xB800000Cul  /* �N���b�N�����҂����W�X�^                      */
#define RMPCON      0xB8000010ul  /* ���}�b�v���䃌�W�X�^                          */
#define TMEN        0xB8001004ul  /* �V�X�e���^�C�}�C�l�[�u�����W�X�^              */
#define TMRLR       0xB8001008ul  /* �V�X�e���^�C�}�����[�h���W�X�^                */
#define TMOVFR      0xB8001010ul  /* �V�X�e���^�C�}�I�[�o�[�t���[���W�X�^          */
#define SIOBUF      0xB8002000ul  /* ����M�o�b�t�@���W�X�^                        */
#define SIOSTA      0xB8002004ul  /* SIO �X�e�[�^�X���W�X�^                        */
#define SIOCON      0xB8002008ul  /* SIO�R���g���[�����W�X�^                       */
#define SIOBCN      0xB800200Cul  /* �{�[���[�g�R���g���[�����W�X�^                */
#define SIOBT       0xB8002014ul  /* �{�[���[�g�^�C�}���W�X�^                      */
#define SIOTCN      0xB8002018ul  /* SIO���[�v�o�b�N�@�\���W�X�^                   */


/*----------------------------------------------------------------------------
  ���̑��̒�`
----------------------------------------------------------------------------*/
/* IRQ�v���ԍ� */
#define STMIRQ      0   /* �V�X�e���E�^�C�} */
#define WDTIRQ      1   /* �E�H�b�`�h�b�O�^�C�} */
#define WDTITVIRQ   2   /* �E�H�b�`�h�b�O�^�C�}�̃C���^�[�o���^�C�}���[�h */
#define GPIOAIRQ    4   /* GPIOA */
#define GPIOBIRQ    5   /* GPIOB */
#define SOFTIRQ     8   /* �\�t�gIRQ */
#define UARTIRQ     9   /* UART */
#define SIOIRQ      10  /* SIO */
#define ADIRQ       11  /* AD */
#define PWM0IRQ     12  /* PWM�`���l��0 */
#define PWM1IRQ     13  /* PWM�`���l��1 */
#define TMRIRQ0     16  /* �^�C�}0 */
#define TMRIRQ1     17  /* �^�C�}1 */
#define TMRIRQ2     18  /* �^�C�}2 */
#define TMRIRQ3     19  /* �^�C�}3 */
#define TMRIRQ4     20  /* �^�C�}4 */
#define TMRIRQ5     21  /* �^�C�}5 */
#define DMAIRQ0     24  /* DMA�`���l��0 */
#define DMAIRQ1     25  /* DMA�`���l��1 */
#define EIRQ0       28  /* �O�����荞��0 */
#define EIRQ1       29  /* �O�����荞��1 */
#define EIRQ2       30  /* �O�����荞��2 */
#define EIRQ3       31  /* �O�����荞��3 */

#endif /* _ML674000_H_ */
