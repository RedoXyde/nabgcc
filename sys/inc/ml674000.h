/*******************************************************************************
	ml674000.h
	JOB60842サンプルプログラム
	ML674000 レジスタ定義ファイル

	Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
	  All rights reserved.

	更新履歴
	Mar.31,2003 rev1.00:新規作成
*******************************************************************************/
#ifndef _ML674000_H_
#define _ML674000_H_

#define ML674000

/*----------------------------------------------------------------------------
  レジスタアドレス定義
----------------------------------------------------------------------------*/
#define IRQ         0x78000000ul  /* IRQレジスタ                                   */
#define IRQS        0x78000004ul  /* IRQソフトレジスタ                             */
#define FIQ         0x78000008ul  /* FIQレジスタ                                   */
#define FIQRAW      0x7800000Cul  /* FIQRAWレジスタ                                */
#define FIQEN       0x78000010ul  /* FIQイネーブルレジスタ                         */
#define IRN         0x78000014ul  /* IRQ番号レジスタ                               */
#define CIL         0x78000018ul  /* 現IRQレベルレジスタ                           */
#define ILC0        0x78000020ul  /* IRQレベル制御レジスタ0                        */
#define ILC1        0x78000024ul  /* IRQレベル制御レジスタ1                        */
#define CILCL       0x78000028ul  /* 現IRQレベルクリアレジスタ                     */
#define CILE        0x7800002Cul  /* 現IRQレベルエンコードレジスタ                 */
#define BWC         0x78100000ul  /* バス幅コントロールレジスタ                    */
#define ROMAC       0x78100004ul  /* 外部ROMアクセスコントロールレジスタ           */
#define RAMAC       0x78100008ul  /* 外部RAMアクセスコントロールレジスタ           */
#define IO0AC       0x7810000Cul  /* 外部IOバンク0のアクセスコントロールレジスタ   */
#define IO1AC       0x78100010ul  /* 外部IOバンク1のアクセスコントロールレジスタ   */
#define DBWC        0x78180000ul  /* DRAMバス幅コントロールレジスタ                */
#define DRMC        0x78180004ul  /* DRAMコントロールレジスタ                      */
#define DRPC        0x78180008ul  /* DRAM特性パラメータコントロールレジスタ        */
#define SDMD        0x7818000Cul  /* SDRAMモードレジスタ                           */
#define DCMD        0x78180010ul  /* DRAMコマンドレジスタ                          */
#define RFSH0       0x78180014ul  /* DRAMリフレッシュサイクルコントロールレジスタ0 */
#define RDWC        0x78180018ul  /* DRAMパワーダウンコントロールレジスタ          */
#define RFSH1       0x7818001Cul  /* DRAMリフレッシュサイクルコントロールレジスタ1 */
#define DMAMOD      0x7BE00000ul  /* DMAモードレジスタ                             */
#define DMASTA      0x7BE00004ul  /* DMAステータスレジスタ                         */
#define DMAINT      0x7BE00008ul  /* DMA終了ステータスレジスタ                     */
#define DMACMSK0    0x7BE00100ul  /* DMAチャネルマスクレジスタ                     */
#define DMACTMOD0   0x7BE00104ul  /* DMA転送モードレジスタ                         */
#define DMACSAD0    0x7BE00108ul  /* DMA転送元アドレスレジスタ                     */
#define DMACDAD0    0x7BE0010Cul  /* DMA転送先アドレスレジスタ                     */
#define DMACSIZ0    0x7BE00110ul  /* DMA転送回数レジスタ                           */
#define DMACCINT0   0x7BE00114ul  /* DMA終了ステータスクリアレジスタ               */
#define DMACMSK1    0x7BE00200ul  /* DMAチャネルマスクレジスタ                     */
#define DMACTMOD1   0x7BE00204ul  /* DMA転送モードレジスタ                         */
#define DMACSAD1    0x7BE00208ul  /* DMA転送元アドレスレジスタ                     */
#define DMACDAD1    0x7BE0020Cul  /* DMA転送先アドレスレジスタ                     */
#define DMACSIZ1    0x7BE00210ul  /* DMA転送回数レジスタ                           */
#define DMACCINT1   0x7BE00214ul  /* DMA終了ステータスクリアレジスタ               */
#define IRCL        0x7BF00004ul  /* IRQクリアレジスタ                             */
#define IRQA        0x7BF00010ul  /* IRQAレジスタ                                  */
#define IDM         0x7BF00014ul  /* IRQ検出モード設定レジスタ                     */
#define ILC         0x7BF00018ul  /* IRQレベル制御レジスタ                         */
#define ADCON0      0xB6000000ul  /* A/Dコントロール0レジスタ                      */
#define ADCON1      0xB6000004ul  /* A/Dコントロール1レジスタ                      */
#define ADCON2      0xB6000008ul  /* A/Dコントロール2レジスタ                      */
#define ADINT       0xB600000Cul  /* A/D 割り込み制御レジスタ                      */
#define ADFINT      0xB6000010ul  /* A/D 強制割り込み発生レジスタ                  */
#define ADR0        0xB6000014ul  /* A/Dリザルト0レジスタ                          */
#define ADR1        0xB6000018ul  /* A/Dリザルト1レジスタ                          */
#define ADR2        0xB600001Cul  /* A/Dリザルト2レジスタ                          */
#define ADR3        0xB6000020ul  /* A/Dリザルト3レジスタ                          */
#define ADR4        0xB6000024ul  /* A/Dリザルト4レジスタ                          */
#define ADR5        0xB6000028ul  /* A/Dリザルト5レジスタ                          */
#define ADR6        0xB600002Cul  /* A/Dリザルト6レジスタ                          */
#define ADR7        0xB6000030ul  /* A/Dリザルト7レジスタ                          */
#define GPCTL       0xB7000000ul  /* ポート機能選択レジスタ                        */
#define BCKCTL      0xB7000004ul  /* 機能単位クロック制御レジスタ                  */
#define GPPOA       0xB7A00000ul  /* ポートA出力レジスタ                           */
#define GPPIA       0xB7A00004ul  /* ポートA入力レジスタ                           */
#define GPPMA       0xB7A00008ul  /* ポートAモードレジスタ                         */
#define GPIEA       0xB7A0000Cul  /* ポートA割り込みイネーブルレジスタ             */
#define GPIPA       0xB7A00010ul  /* ポートA割り込み極性レジスタ                   */
#define GPISA       0xB7A00014ul  /* ポートA割り込みステータスレジスタ             */
#define GPPOB       0xB7A00020ul  /* ポートB出力レジスタ                           */
#define GPPIB       0xB7A00024ul  /* ポートB入力レジスタ                           */
#define GPPMB       0xB7A00028ul  /* ポートBモードレジスタ                         */
#define GPIEB       0xB7A0002Cul  /* ポートB割り込みイネーブルレジスタ             */
#define GPIPB       0xB7A00030ul  /* ポートB割り込み極性レジスタ                   */
#define GPISB       0xB7A00034ul  /* ポートB割り込みステータスレジスタ             */
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
#define PWR0        0xB7D00000ul  /* PWMレジスタ0                                  */
#define PWCY0       0xB7D00004ul  /* PWM周期レジスタ0                              */
#define PWC0        0xB7D00008ul  /* PWMカウンタ0                                  */
#define PWCON0      0xB7D0000Cul  /* PWMコントロールレジスタ0                      */
#define PWR1        0xB7D00020ul  /* PWMレジスタ1                                  */
#define PWCY1       0xB7D00024ul  /* PWM周期レジスタ1                              */
#define PWC1        0xB7D00028ul  /* PWMカウンタ1                                  */
#define PWCON1      0xB7D0002Cul  /* PWMコントロールレジスタ1                      */
#define PWINTSTS    0xB7D0003Cul  /* ＰＷＭ割り込みステータスレジスタ              */
#define WDTCON      0xB7E00000ul  /* ウォッチドッグタイマ制御レジスタ              */
#define WDTBCON     0xB7E00004ul  /* タイムベースカウンタ制御レジスタ              */
#define WDSTAT      0xB7E00014ul  /* ステータスレジスタ                            */
#define TIMECNTL0   0xB7F00000ul  /* タイマ0制御レジスタ                           */
#define TIMEBASE0   0xB7F00004ul  /* タイマ0ベースレジスタ                         */
#define TIMECNT0    0xB7F00008ul  /* タイマ0カウンタレジスタ                       */
#define TIMECMP0    0xB7F0000Cul  /* タイマ0コンペアレジスタ                       */
#define TIMESTAT0   0xB7F00010ul  /* タイマ0ステータスレジスタ                     */
#define TIMECNTL1   0xB7F00020ul  /* タイマ1制御レジスタ                           */
#define TIMEBASE1   0xB7F00024ul  /* タイマ1ベースレジスタ                         */
#define TIMECNT1    0xB7F00028ul  /* タイマ1カウンタレジスタ                       */
#define TIMECMP1    0xB7F0002Cul  /* タイマ1コンペアレジスタ                       */
#define TIMESTAT1   0xB7F00030ul  /* タイマ1ステータスレジスタ                     */
#define TIMECNTL2   0xB7F00040ul  /* タイマ2制御レジスタ                           */
#define TIMEBASE2   0xB7F00044ul  /* タイマ2ベースレジスタ                         */
#define TIMECNT2    0xB7F00048ul  /* タイマ2カウンタレジスタ                       */
#define TIMECMP2    0xB7F0004Cul  /* タイマ2コンペアレジスタ                       */
#define TIMESTAT2   0xB7F00050ul  /* タイマ2ステータスレジスタ                     */
#define TIMECNTL3   0xB7F00060ul  /* タイマ3制御レジスタ                           */
#define TIMEBASE3   0xB7F00064ul  /* タイマ3ベースレジスタ                         */
#define TIMECNT3    0xB7F00068ul  /* タイマ3カウンタレジスタ                       */
#define TIMECMP3    0xB7F0006Cul  /* タイマ3コンペアレジスタ                       */
#define TIMESTAT3   0xB7F00070ul  /* タイマ3ステータスレジスタ                     */
#define TIMECNTL4   0xB7F00080ul  /* タイマ4制御レジスタ                           */
#define TIMEBASE4   0xB7F00084ul  /* タイマ4ベースレジスタ                         */
#define TIMECNT4    0xB7F00088ul  /* タイマ4カウンタレジスタ                       */
#define TIMECMP4    0xB7F0008Cul  /* タイマ4コンペアレジスタ                       */
#define TIMESTAT4   0xB7F00090ul  /* タイマ4ステータスレジスタ                     */
#define TIMECNTL5   0xB7F000A0ul  /* タイマ5制御レジスタ                           */
#define TIMEBASE5   0xB7F000A4ul  /* タイマ5ベースレジスタ                         */
#define TIMECNT5    0xB7F000A8ul  /* タイマ5カウンタレジスタ                       */
#define TIMECMP5    0xB7F000ACul  /* タイマ5コンペアレジスタ                       */
#define TIMESTAT5   0xB7F000B0ul  /* タイマ5ステータスレジスタ                     */
#define CLKSTP      0xB8000004ul  /* CLK 停止レジスタ                              */
#define CGBCNT0     0xB8000008ul  /* クロック選択レジスタ                          */
#define CKWT        0xB800000Cul  /* クロック供給待ちレジスタ                      */
#define RMPCON      0xB8000010ul  /* リマップ制御レジスタ                          */
#define TMEN        0xB8001004ul  /* システムタイマイネーブルレジスタ              */
#define TMRLR       0xB8001008ul  /* システムタイマリロードレジスタ                */
#define TMOVFR      0xB8001010ul  /* システムタイマオーバーフローレジスタ          */
#define SIOBUF      0xB8002000ul  /* 送受信バッファレジスタ                        */
#define SIOSTA      0xB8002004ul  /* SIO ステータスレジスタ                        */
#define SIOCON      0xB8002008ul  /* SIOコントロールレジスタ                       */
#define SIOBCN      0xB800200Cul  /* ボーレートコントロールレジスタ                */
#define SIOBT       0xB8002014ul  /* ボーレートタイマレジスタ                      */
#define SIOTCN      0xB8002018ul  /* SIOループバック機能レジスタ                   */


/*----------------------------------------------------------------------------
  その他の定義
----------------------------------------------------------------------------*/
/* IRQ要因番号 */
#define STMIRQ      0   /* システム・タイマ */
#define WDTIRQ      1   /* ウォッチドッグタイマ */
#define WDTITVIRQ   2   /* ウォッチドッグタイマのインターバルタイマモード */
#define GPIOAIRQ    4   /* GPIOA */
#define GPIOBIRQ    5   /* GPIOB */
#define SOFTIRQ     8   /* ソフトIRQ */
#define UARTIRQ     9   /* UART */
#define SIOIRQ      10  /* SIO */
#define ADIRQ       11  /* AD */
#define PWM0IRQ     12  /* PWMチャネル0 */
#define PWM1IRQ     13  /* PWMチャネル1 */
#define TMRIRQ0     16  /* タイマ0 */
#define TMRIRQ1     17  /* タイマ1 */
#define TMRIRQ2     18  /* タイマ2 */
#define TMRIRQ3     19  /* タイマ3 */
#define TMRIRQ4     20  /* タイマ4 */
#define TMRIRQ5     21  /* タイマ5 */
#define DMAIRQ0     24  /* DMAチャネル0 */
#define DMAIRQ1     25  /* DMAチャネル1 */
#define EIRQ0       28  /* 外部割り込み0 */
#define EIRQ1       29  /* 外部割り込み1 */
#define EIRQ2       30  /* 外部割り込み2 */
#define EIRQ3       31  /* 外部割り込み3 */

#endif /* _ML674000_H_ */
