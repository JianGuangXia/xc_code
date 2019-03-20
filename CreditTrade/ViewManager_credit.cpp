#include "stdafx.h"
#include "ViewManager_credit.h"

#include "CreditTradeView_001.h"
#include "OrderView_002.h"
#include "PositionView.h"
#include "Fundview_004.h"
#include "AlertView_005.h"
#include "OrderQueueView.h"
#include "OrderEachView.h"
#include "OrderDealDetailView.h"
#include "DealSummaryView.h"
#include "CustomPoolView.h"
#include "BiaoDiQuanView_011.h"
#include "DanBaoQuanView_012.h"
#include "CreditAssetView_013.h"

vector<VIEWNODE> view_entry2
{
	{ ID_viw_creditTrade, "001", "������ȯ", CCreditTradeView::CreateView },
	{ ID_view_order, "002", "ί��", COrderView::CreateView },
	{ ID_view_position, "003", "�ֲ�", CPositionView::CreateView },
	{ ID_view_fund, "004", "�ʽ�", CFundView::CreateView },
	{ ID_view_alert, "005", "Ԥ��", CAlertView::CreateView },
	{ ID_view_orderQueue, "006", "ί�ж���", COrderQueueView::CreateView },
	{ ID_view_orderEach, "007", "���ί��", COrderEachView::CreateView },
	{ ID_view_orderDealDetail, "008", "ί�е��ɽ���ϸ", COrderDealDetailView::CreateView },
	{ ID_view_dealSummary, "009", "�ɽ�����", CDealSummaryView::CreateView },
	{ ID_view_customPool, "010", "��ѡ��", CCustomPoolView::CreateView },
	{ ID_View_BiaoDiQuan, "011", "���ȯ", CBiaoDiQuanView::CreateView },
	{ ID_View_DanBaoQuan, "012", "����֤ȯ", CDanBaoQuanView::CreateView },
	{ ID_View_CreditAsset, "013", "�����ʲ�", CCreditAssetView::CreateView },

};

CViewManager_credit::CViewManager_credit()
	: CViewManager(view_entry2)
{
}

CViewManager_credit::~CViewManager_credit(void)
{
}
