#pragma once
#include "../tool/baseView/ViewManager.h"

class CViewManager_credit;
#define SingleViewManager Singleton<CViewManager_credit>::Instance()

enum
{
	ID_base_view = ID_BASE_VIEW,
	ID_viw_creditTrade,//������ȯ
	ID_view_order,//ί��
	ID_view_position,//�ֲ�
	ID_view_fund,//�ʽ�
	ID_view_alert,//Ԥ��
	ID_view_orderQueue,//ί�ж���
	ID_view_orderEach,//���ί��
	ID_view_orderDealDetail,//ί�е��ɽ���ϸ
	ID_view_dealSummary,//�ɽ�����
	ID_view_customPool,//��ѡ��
	ID_View_BiaoDiQuan,//���ȯ
	ID_View_DanBaoQuan,//����֤ȯ
	ID_View_CreditAsset,//�����ʲ�
	ID_MAX_VIEW,
	ID_view_nil = ID_VIEW_NIL,
};

class CViewManager_credit :public CViewManager
{
public:
	CViewManager_credit();
	~CViewManager_credit();
};

