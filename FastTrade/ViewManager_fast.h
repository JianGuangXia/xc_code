#pragma once
#include "../tool/baseView/ViewManager.h"

class CViewManager_fast;
#define SingleViewManager Singleton<CViewManager_fast>::Instance()

enum
{
	ID_base_view = ID_BASE_VIEW,
	ID_view_fastTrade,//���ٽ���
	ID_view_order,//ί��
	ID_view_position,//�ֲ�
	ID_view_fund,//�ʽ�
	ID_view_alert,//Ԥ��
	ID_view_orderQueue,//ί�ж���
	ID_view_orderEach,//���ί��
	ID_view_orderDealDetail,//ί�е��ɽ���ϸ ID_view_orderDealDetail
	ID_view_dealSummary,//�ɽ�����
	ID_view_customPool,//��ѡ��
	ID_MAX_VIEW,
	ID_view_nil = ID_VIEW_NIL,
};

class CViewManager_fast :public CViewManager
{
public:
	CViewManager_fast();
	~CViewManager_fast();
};

