/*******************************************************************************
    usbhcfg.h
    JOB60842サンプルプログラム
    USBホストクラスドライバ構成定義ファイル

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    更新履歴
    Mar.31,2003 rev1.00:新規作成
*******************************************************************************/
#ifndef _USBHCFG_H_
#define _USBHCFG_H_

/*--------------------------------------------------------------------------*/
#define CONFIG_HUB
#define CONFIG_OKIJOB
#define CONFIG_MOUSE

/*--------------------------------------------------------------------------*/
#ifdef CONFIG_HUB
extern int usb_hub_init(void);
extern int usb_hub_exit(void);
extern void usb_hub_events(void);
#else
__inline void usb_hub_events(void) { ; }
#endif

/*--------------------------------------------------------------------------*/
#ifdef CONFIG_MOUSE
extern int usb_mouse_init(void);
extern void usb_mouse_exit(void);
#endif

/*--------------------------------------------------------------------------*/
#ifdef CONFIG_OKIJOB
extern int usb_okijob_init(void);
extern void usb_okijob_exit(void);
extern void okijob_test(void);
#endif

int usb_okijob_init(void);
void usb_okijob_exit(void);
void okijob_test(void);
int test_bug(void);

/*--------------------------------------------------------------------------*/
/*__inline int usbhdriver_init(void)
{
	int ret;

#ifdef CONFIG_HUB
	ret = usb_hub_init();
	if(ret!=OK) return ret;
#endif

#ifdef CONFIG_OKIJOB
	ret = usb_okijob_init();
	if(ret!=OK) return ret;
#endif

#ifdef CONFIG_MOUSE
	ret = usb_mouse_init();
	if(ret!=OK) return ret;
#endif

	return 0;
}
*/
/*--------------------------------------------------------------------------*/
/*__inline void usbhdriver_exit(void)
{

#ifdef CONFIG_OKIJOB
	usb_okijob_exit();
#endif

#ifdef CONFIG_MOUSE
	usb_mouse_exit();
#endif

#ifdef CONFIG_HUB
	usb_hub_exit();
#endif

}
*/
#endif /* _USBHCFG_H_ */
