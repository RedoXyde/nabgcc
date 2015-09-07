/*******************************************************************************
    list.h

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    Mar.31,2003 rev1.00
*******************************************************************************/

#include "ml674061.h"
#include "common.h"
#include "list.h"

void __list_add(pLIST_ENTRY entry, pLIST_ENTRY Blink, pLIST_ENTRY Flink)
{
	entry->Blink = Blink;
	entry->Flink = Flink;
	Blink->Flink = entry;
	Flink->Blink = entry;
}

/* Xg©çí·é */
void __list_del(pLIST_ENTRY Blink, pLIST_ENTRY Flink)
{
	Flink->Blink = Blink;
	Blink->Flink = Flink;
}

/* GgðXgÉæªÉÇÁ·é */
void list_add_top(pLIST_ENTRY entry, pLIST_ENTRY head)
{
	__list_add(entry, head, head->Flink);
}

/* GgðXgÌÅãÉÇÁ·é */
void list_add(pLIST_ENTRY entry, pLIST_ENTRY head)
{
	__list_add(entry, head->Blink, head);
}

/* GgðXg©çí·é */
void list_del(pLIST_ENTRY entry)
{
	__list_del(entry->Blink, entry->Flink);
}

/* Xgªó©`FbN·é */
int list_empty(pLIST_ENTRY head)
{
	return (head->Flink == head);
}

