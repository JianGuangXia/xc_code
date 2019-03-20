#include "stdafx.h"
#include "ViewManager_auto.h"



vector<VIEWNODE> view_entry2
{
	{ ID_View_EntrustEach, "AutoTrade_EntrustEach", "���ί�й���", CView_EntrustEach::CreateView },
	{ ID_View_TradeConig, "AutoTrade_TradeConfig", "���ײ�������", CView_TradeConfig::CreateView },
	{ ID_View_AlertRecord, "AutoTrade_AlertRecord", "Ԥ����¼", CView_AlertRecord::CreateView },
	{ ID_View_CustomPool, "AutoTrade_CustomPool", "��ѡ��", CCustomPoolView::CreateView },
	{ ID_View_blackList, "AutoTrade_blackList", "������", CBlackListView::CreateView },
};

CViewManager_auto::CViewManager_auto()
	: CViewManager(view_entry2)
{
}

CViewManager_auto::~CViewManager_auto(void)
{
}
