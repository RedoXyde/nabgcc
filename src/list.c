/*******************************************************************************
    list.h

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    Mar.31,2003 rev1.00
*******************************************************************************/

#include "ML674061.h"
#include "common.h"
#include "list.h"

void __list_add(pLIST_ENTRY entry, pLIST_ENTRY Blink, pLIST_ENTRY Flink)
{
	entry->Blink = Blink;	
	entry->Flink = Flink;
	Blink->Flink = entry;
	Flink->Blink = entry;	
}

/* リストから削除する */
void __list_del(pLIST_ENTRY Blink, pLIST_ENTRY Flink)
{
	Flink->Blink = Blink;
	Blink->Flink = Flink;
}

/* エントリをリストに先頭に追加する */
void list_add_top(pLIST_ENTRY entry, pLIST_ENTRY head)
{
	__list_add(entry, head, head->Flink);
}

/* エントリをリストの最後に追加する */
void list_add(pLIST_ENTRY entry, pLIST_ENTRY head)
{
	__list_add(entry, head->Blink, head);
}

/* エントリをリストから削除する */
void list_del(pLIST_ENTRY entry)
{
	__list_del(entry->Blink, entry->Flink);
}

/* リストが空かチェックする */
int list_empty(pLIST_ENTRY head)
{
	return (head->Flink == head);
}

