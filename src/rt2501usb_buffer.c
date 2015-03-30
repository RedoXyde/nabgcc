/*
	Ralink RT2501 driver for Violet embedded platforms
	(c) 2006 Sebastien Bourdeauducq
*/

#include <intrinsics.h>
#include <stdio.h>
#include <string.h>
#include "mem.h"
#include "hcdmem.h"
#include "hcd.h"
#include "debug.h"
#include "delay.h"

#include "rt2501usb.h"
#include "rt2501usb_internal.h"
#include "ieee80211.h"

static struct rt2501buffer *head, *queue;

void rt2501buffer_init(void)
{
	disable_ohci_irq();
	head = queue = NULL;
	enable_ohci_irq();
}

void rt2501buffer_free(void)
{
	disable_ohci_irq();
	while(rt2501_receive() != NULL);
	enable_ohci_irq();
}

int rt2501buffer_new(const char *data, unsigned int length,
                     const unsigned char *source_mac,
		     const unsigned char *dest_mac)
{
	struct rt2501buffer *newbuffer;

	disable_ohci_irq();
	newbuffer = (struct rt2501buffer *)hcd_malloc(sizeof(struct rt2501buffer)+length, EXTRAM,19);
	if(newbuffer == NULL) {
		enable_ohci_irq();
		return 0;
	}
	newbuffer->next = NULL;
	newbuffer->length = length;
	memcpy(newbuffer->source_mac, source_mac, IEEE80211_ADDR_LEN);
	memcpy(newbuffer->dest_mac, dest_mac, IEEE80211_ADDR_LEN);
	memcpy(newbuffer->data, data, length);

	if(queue == NULL) {
		/* This is the first buffer */
		head = queue = newbuffer;
	} else {
		queue->next = newbuffer;
		queue = newbuffer;
	}
	enable_ohci_irq();
	return 1;
}

struct rt2501buffer *rt2501_receive(void)
{
	struct rt2501buffer *r;

	while(1) {
		disable_ohci_irq();
		if(head == NULL) {
			enable_ohci_irq();
			return NULL;
		}
		r = head;
		head = head->next;
		if(head == NULL) queue = NULL;
		enable_ohci_irq();
/*		
        sprintf(dbg_buffer,"rt2501_receive: %x\r\n", r);
        DBG(dbg_buffer);
*/
		if((r->length < LLC_LENGTH)
		   || (memcmp(r->data, eapol_llc, LLC_LENGTH) != 0))
	  		/* Not an EAPOL frame. Return it to the application. */
			return r;
		
		/* EAPOL frame, process it. */
		eapol_input(r->data, r->length);
		disable_ohci_irq();
		hcd_free(r);
		enable_ohci_irq();
	}
}
