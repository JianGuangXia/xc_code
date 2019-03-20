#include "stdafx.h"
#include "GridRes.h"
// #include "global.h"
// #include "util.h"

void SetDefaultFormat(const int ID, int &format)
{
	format = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
	return;
}

void InitAllGridCol()
{
	InitOrderViewGridCol();
	InitPositonViewGridCol();
	InitFundViewGridCol();
	InitAlertViewGridCol();
	InitQueueBuy1GridCol();
	InitQueueSell1GridCol();
	InitOrderEachGridCol();
	InitDealEachGridCol();
	InitDealDealSummaryGridCol();
	InitCustomPoolGridCol();
	InitBiaoDiQuanGridCol();
	InitDanBaoQuanGridCol();
	InitCreditAssetGridCol();
}

//ί��
#define ORDERVIEWCOL_COUNT 9
tagColumn g_arrOrderViewCol[ORDERVIEWCOL_COUNT];
void InitOrderViewGridCol()
{
	tagColumn tempCol[] =
	{
		//{ ColId_Check, "��ѡ", 39, COLTYPE_FIX, FALSE }
	{ COLID_STOCKNAME, "��Ʊ����", 130, COLTYPE_FIX, TRUE }
		,{ COLID_STOCKCODE, "��Ʊ����", 90, COLTYPE_FIX, TRUE }
		,{ COLID_DIRECTION, "��������", 90, COLTYPE_FIX, TRUE }
		,{ ColId_EntrustType, "ί������", 90, COLTYPE_FIX, TRUE }
		,{ COLID_ORDERPRICE, "ί�м۸�", 90, COLTYPE_FIX, TRUE, TRUE }
		,{ COLID_ORDERVOLUME, "ί������", 90, COLTYPE_FIX, TRUE }
		,{ COLID_DEALVOLUME, "�ɽ�����", 90, COLTYPE_FIX, TRUE }
		,{ COLID_ORDERSTATUS, "ί��״̬", 90, COLTYPE_FIX, TRUE }
		,{ COLID_ORDERNO, "ί�к�", 90, COLTYPE_FIX, TRUE }

	};

	for (int i = 0; i < ORDERVIEWCOL_COUNT; i++)
	{
		g_arrOrderViewCol[i] = tempCol[i];
	}
}
void GetOrderViewGridCol(tagColumn **ppCols, int *pCnt)
{
	if (ppCols != nullptr)
	{
		*ppCols = g_arrOrderViewCol;
	}
	if (pCnt != nullptr)
	{
		*pCnt = ORDERVIEWCOL_COUNT;
	}

	for (int i = 0; i < *pCnt; i++)
	{
		SetDefaultFormat((*ppCols)[i].nColID, (*ppCols)[i].nFormat);
	}
}

//�ֲ�
#define POSITONVIEWCOL_COUNT 9
tagColumn g_arrPositionViewCol[POSITONVIEWCOL_COUNT];
void InitPositonViewGridCol()
{
	tagColumn tempCol[] =
	{
		{ COLID_STOCKNAME, "��Ʊ����", 90, COLTYPE_FIX, TRUE }
		,{ COLID_STOCKCODE, "��Ʊ����", 100, COLTYPE_FIX, TRUE }
		,{ COLID_STOCKBALANCE, "��Ʊ���", 90, COLTYPE_FIX, TRUE }
		,{ COLID_AVLIABLEVOLUME, "��������", 90, COLTYPE_FIX, TRUE }
		,{ COLID_COSTPRICE, "�ɱ���", 90, COLTYPE_FIX, TRUE }
		,{ ColId_LastPrice, "���¼�", 90, COLTYPE_FIX, TRUE }
		,{ COLID_MARKETVALUE, "��ֵ", 110, COLTYPE_FIX, TRUE }
		,{ COLID_BALANCE, "ӯ��", 110, COLTYPE_FIX, TRUE }
		,{ COLID_BALANCERATE, "ӯ����", 90, COLTYPE_FIX, TRUE }
	};

	for (int i = 0; i < POSITONVIEWCOL_COUNT; i++)
	{
		g_arrPositionViewCol[i] = tempCol[i];
	}
}
void GetPositonViewGridCol(tagColumn **ppCols, int *pCnt)
{
	if (ppCols != nullptr)
	{
		*ppCols = g_arrPositionViewCol;
	}
	if (pCnt != nullptr)
	{
		*pCnt = POSITONVIEWCOL_COUNT;
	}

	for (int i = 0; i < *pCnt; i++)
	{
		SetDefaultFormat((*ppCols)[i].nColID, (*ppCols)[i].nFormat);
	}
}

//�ʽ�
#define FUNDVIEWCOL_COUNT 6
tagColumn g_arrFundViewCol[FUNDVIEWCOL_COUNT];
void InitFundViewGridCol()
{
	tagColumn tempCol[] =
	{
		{ ColId_CurrentBalance, "��ǰ���", 140, COLTYPE_FIX, FALSE }
		,{ ColId_EnableBalance, "�����ʽ�", 140, COLTYPE_FIX, FALSE }
		,{ ColId_FrozenBalance, "�����ʽ�", 140, COLTYPE_FIX, FALSE }
		,{ ColId_UnfrozenBalance, "�ⶳ�ʽ�", 140, COLTYPE_FIX, FALSE }
		,{ ColId_RealBuyBalance, "�ر�������", 140, COLTYPE_FIX, FALSE }
		,{ ColId_RealSellBalance, "�ر��������", 140, COLTYPE_FIX, FALSE }
	};

	for (int i = 0; i < FUNDVIEWCOL_COUNT; i++)
	{
		g_arrFundViewCol[i] = tempCol[i];
	}
}
void GetFundViewGridCol(tagColumn **ppCols, int *pCnt)
{
	if (ppCols != nullptr)
	{
		*ppCols = g_arrFundViewCol;
	}
	if (pCnt != nullptr)
	{
		*pCnt = FUNDVIEWCOL_COUNT;
	}

	for (int i = 0; i < *pCnt; i++)
	{
		SetDefaultFormat((*ppCols)[i].nColID, (*ppCols)[i].nFormat);
	}
}

//Ԥ��
#define AlertCol_Count 6
tagColumn g_arrAlertViewCol[AlertCol_Count];
void InitAlertViewGridCol()
{
	tagColumn tempCol[] =
	{
		{ COLID_STOCKNAME, "��Ʊ����", 120, COLTYPE_FIX, FALSE }
		,{ COLID_STOCKCODE, "��Ʊ����", 120, COLTYPE_FIX, FALSE }
		,{ ColId_RiseRate, "�ǵ���%", 120, COLTYPE_FIX, FALSE }
		,{ ColId_LastPrice, "���¼�", 120, COLTYPE_FIX, FALSE }
		,{ ColId_AppearPrice, "�����۸�", 120, COLTYPE_FIX, FALSE }
		,{ ColId_AppearTime, "����ʱ��", 120, COLTYPE_FIX, FALSE }

	};

	for (int i = 0; i < AlertCol_Count; i++)
	{
		g_arrAlertViewCol[i] = tempCol[i];
	}
}
void GetAlertViewGridCol(tagColumn **ppCols, int *pCnt)
{
	if (ppCols != nullptr)
	{
		*ppCols = g_arrAlertViewCol;
	}
	if (pCnt != nullptr)
	{
		*pCnt = AlertCol_Count;
	}

	for (int i = 0; i < *pCnt; i++)
	{
		SetDefaultFormat((*ppCols)[i].nColID, (*ppCols)[i].nFormat);
	}
}

//ί�ж�����һ
#define QueueBuy1Col_Count 7
tagColumn g_arrQueueBuy1ViewCol[QueueBuy1Col_Count];
void InitQueueBuy1GridCol()
{
	tagColumn tempCol[] =
	{
		{ ColId_BuySell1, "��һ", 60, COLTYPE_FIX, FALSE }
		,{ ColId_Price, "", 60, COLTYPE_FIX, FALSE }
		,{ ColId_Amout, "", 60, COLTYPE_FIX, FALSE }
		,{ ColId_Null1, "", 60, COLTYPE_FIX, FALSE }
		,{ ColId_Null2, "", 60, COLTYPE_FIX, FALSE }
		,{ ColId_Null3, "", 60, COLTYPE_FIX, FALSE }
		,{ ColId_Hand, "����", 60, COLTYPE_FIX, FALSE }
	};

	for (int i = 0; i < QueueBuy1Col_Count; i++)
	{
		g_arrQueueBuy1ViewCol[i] = tempCol[i];
	}
}
void GetQueueBuy1GridCol(tagColumn **ppCols, int *pCnt)
{
	if (ppCols != nullptr)
	{
		*ppCols = g_arrQueueBuy1ViewCol;
	}
	if (pCnt != nullptr)
	{
		*pCnt = QueueBuy1Col_Count;
	}

	for (int i = 0; i < *pCnt; i++)
	{
		SetDefaultFormat((*ppCols)[i].nColID, (*ppCols)[i].nFormat);
	}
}

//ί�ж�����һ
#define QueueSell1Col_Count 7
tagColumn g_arrQueueSell1ViewCol[QueueSell1Col_Count];
void InitQueueSell1GridCol()
{
	tagColumn tempCol[] =
	{
		{ ColId_BuySell1, "��һ", 60, COLTYPE_FIX, FALSE }
		,{ ColId_Price, "", 60, COLTYPE_FIX, FALSE }
		,{ ColId_Amout, "", 60, COLTYPE_FIX, FALSE }
		,{ ColId_Null1, "", 60, COLTYPE_FIX, FALSE }
		,{ ColId_Null2, "", 60, COLTYPE_FIX, FALSE }
		,{ ColId_Null3, "", 60, COLTYPE_FIX, FALSE }
		,{ ColId_Hand, "����", 60, COLTYPE_FIX, FALSE }
	};

	for (int i = 0; i < QueueSell1Col_Count; i++)
	{
		g_arrQueueSell1ViewCol[i] = tempCol[i];
	}
}
void GetQueueSell1GridCol(tagColumn **ppCols, int *pCnt)
{
	if (ppCols != nullptr)
	{
		*ppCols = g_arrQueueSell1ViewCol;
	}
	if (pCnt != nullptr)
	{
		*pCnt = QueueSell1Col_Count;
	}

	for (int i = 0; i < *pCnt; i++)
	{
		SetDefaultFormat((*ppCols)[i].nColID, (*ppCols)[i].nFormat);
	}
}

//���ί��
#define OrderEachViewCol_Count 6
tagColumn g_arrOrderEachViewCol[OrderEachViewCol_Count];
void InitOrderEachGridCol()
{
	tagColumn tempCol[] =
	{
		{ ColId_Time, "ʱ��", 120, COLTYPE_FIX, FALSE }
		,{ COLID_ORDERNO, "ί�к�", 120, COLTYPE_FIX, TRUE }
		,{ ColId_Price, "�۸�", 120, COLTYPE_FIX, TRUE }
		,{ ColId_Volume, "����", 120, COLTYPE_FIX, TRUE }
		,{ ColId_Money, "���", 130, COLTYPE_FIX, TRUE }
		,{ COLID_DIRECTION, "��������", 120, COLTYPE_FIX, TRUE, TRUE }

	};

	for (int i = 0; i < OrderEachViewCol_Count; i++)
	{
		g_arrOrderEachViewCol[i] = tempCol[i];
	}
}
void GetOrderEachViewGridCol(tagColumn **ppCols, int *pCnt)
{
	if (ppCols != nullptr)
	{
		*ppCols = g_arrOrderEachViewCol;
	}
	if (pCnt != nullptr)
	{
		*pCnt = OrderEachViewCol_Count;
	}

	for (int i = 0; i < *pCnt; i++)
	{
		SetDefaultFormat((*ppCols)[i].nColID, (*ppCols)[i].nFormat);
	}
}

//�ֱʳɽ�
#define DealEachViewCol_Count 8
tagColumn g_arrDealEachViewCol[DealEachViewCol_Count];
void InitDealEachGridCol()
{
	tagColumn tempCol[] =
	{
		{ COLID_STOCKNAME, "��Ʊ����", 90, COLTYPE_FIX, FALSE }
		,{ COLID_STOCKCODE, "��Ʊ����", 90, COLTYPE_FIX, FALSE }
		,{ COLID_DIRECTION, "��������", 90, COLTYPE_FIX, FALSE }
		,{ COLID_DEALVOLUME, "�ɽ�����", 90, COLTYPE_FIX, FALSE }
		,{ ColId_DealPrice, "�ɽ��۸�", 90, COLTYPE_FIX, FALSE }
		,{ ColId_DealTime, "�ɽ�ʱ��", 90, COLTYPE_FIX, FALSE }
		,{ ColId_DealNO, "�ɽ����", 195, COLTYPE_FIX, FALSE }
		,{ COLID_ORDERNO, "ί�к�", 100, COLTYPE_FIX, FALSE }

	};

	for (int i = 0; i < DealEachViewCol_Count; i++)
	{
		g_arrDealEachViewCol[i] = tempCol[i];
	}
}
void GetDealEachViewGridCol(tagColumn **ppCols, int *pCnt)
{
	if (ppCols != nullptr)
	{
		*ppCols = g_arrDealEachViewCol;
	}
	if (pCnt != nullptr)
	{
		*pCnt = DealEachViewCol_Count;
	}

	for (int i = 0; i < *pCnt; i++)
	{
		SetDefaultFormat((*ppCols)[i].nColID, (*ppCols)[i].nFormat);
	}
}

//�ɽ�����
#define DealSummaryViewCol_Count 8
tagColumn g_arrDealSummaryViewCol[DealSummaryViewCol_Count];
void InitDealDealSummaryGridCol()
{
	tagColumn tempCol[] =
	{
		{ COLID_STOCKNAME, "��Ʊ����", 90, COLTYPE_FIX, FALSE }
		,{ COLID_STOCKCODE, "��Ʊ����", 90, COLTYPE_FIX, FALSE }
		,{ ColId_TotalBuyVolume, "��������", 90, COLTYPE_FIX, FALSE }
		,{ ColId_TotalSellVolume, "��������", 100, COLTYPE_FIX, FALSE }
		,{ ColId_BuyAveragePrice, "�������", 90, COLTYPE_FIX, FALSE }
		,{ ColId_SellAveragePrice, "��������", 90, COLTYPE_FIX, FALSE }
		,{ ColId_TotalBuyMoney, "������", 110, COLTYPE_FIX, FALSE }
		,{ ColId_TotalSellMoney, "�������", 110, COLTYPE_FIX, FALSE }
	};

	for (int i = 0; i < DealSummaryViewCol_Count; i++)
	{
		g_arrDealSummaryViewCol[i] = tempCol[i];
	}
}
void GetDealDealSummaryGridCol(tagColumn **ppCols, int *pCnt)
{
	if (ppCols != nullptr)
	{
		*ppCols = g_arrDealSummaryViewCol;
	}
	if (pCnt != nullptr)
	{
		*pCnt = DealSummaryViewCol_Count;
	}

	for (int i = 0; i < *pCnt; i++)
	{
		SetDefaultFormat((*ppCols)[i].nColID, (*ppCols)[i].nFormat);
	}
}

//��ѡ��
#define CustomPoolViewCol_Count 3
tagColumn g_arrCustomPoolViewCol[CustomPoolViewCol_Count];
void InitCustomPoolGridCol()
{
	tagColumn tempCol[] =
	{
		//{ ColId_Check, "��ѡ", 39, COLTYPE_FIX, FALSE }
		{ ColId_Market, "�г�", 200, COLTYPE_FIX, TRUE }
		,{ COLID_STOCKNAME, "��Ʊ����", 200, COLTYPE_FIX, TRUE }
		,{ COLID_STOCKCODE, "��Ʊ����", 200, COLTYPE_FIX, TRUE }
	};

	for (int i = 0; i < CustomPoolViewCol_Count; i++)
	{
		g_arrCustomPoolViewCol[i] = tempCol[i];
	}
}
void GetCustomPoolGridCol(tagColumn **ppCols, int *pCnt)
{
	if (ppCols != nullptr)
	{
		*ppCols = g_arrCustomPoolViewCol;
	}
	if (pCnt != nullptr)
	{
		*pCnt = CustomPoolViewCol_Count;
	}

	for (int i = 0; i < *pCnt; i++)
	{
		SetDefaultFormat((*ppCols)[i].nColID, (*ppCols)[i].nFormat);
	}
}

//���ȯ
#define BiaoDiQuanViewCol_Count 5
tagColumn g_arrBiaoDiQuanViewCol[BiaoDiQuanViewCol_Count];
void InitBiaoDiQuanGridCol()
{
	tagColumn tempCol[] =
	{
		{ COLID_STOCKNAME, "��Ʊ����", 120, COLTYPE_FIX, FALSE }
		,{ COLID_STOCKCODE, "��Ʊ����", 120, COLTYPE_FIX, FALSE }
		,{ ColId_FinRatio, "���ʱ�֤�����", 138, COLTYPE_FIX, FALSE }
		,{ ColId_FinStatus, "����״̬", 120, COLTYPE_FIX, FALSE }
		,{ ColId_AssureRatio, "����������", 120, COLTYPE_FIX, FALSE }

	};

	for (int i = 0; i < BiaoDiQuanViewCol_Count; i++)
	{
		g_arrBiaoDiQuanViewCol[i] = tempCol[i];
	}
}
void GetBiaoDiQuanGridCol(tagColumn **ppCols, int *pCnt)
{
	if (ppCols != nullptr)
	{
		*ppCols = g_arrBiaoDiQuanViewCol;
	}
	if (pCnt != nullptr)
	{
		*pCnt = BiaoDiQuanViewCol_Count;
	}

	for (int i = 0; i < *pCnt; i++)
	{
		SetDefaultFormat((*ppCols)[i].nColID, (*ppCols)[i].nFormat);
	}
}

//����֤ȯ
#define DanBaoQuanViewCol_Count 4
tagColumn g_arrDanBaoQuanViewCol[DanBaoQuanViewCol_Count];
void InitDanBaoQuanGridCol()
{
	tagColumn tempCol[] =
	{
		{ COLID_STOCKNAME, "��Ʊ����", 120, COLTYPE_FIX, FALSE }
		,{ COLID_STOCKCODE, "��Ʊ����", 120, COLTYPE_FIX, FALSE }
		,{ ColId_AssureRatio, "����������", 120, COLTYPE_FIX, FALSE }
		,{ ColId_AssureStatus, "����״̬", 120, COLTYPE_FIX, FALSE }

	};

	for (int i = 0; i < DanBaoQuanViewCol_Count; i++)
	{
		g_arrDanBaoQuanViewCol[i] = tempCol[i];
	}
}
void GetDanBaoQuanGridCol(tagColumn **ppCols, int *pCnt)
{
	if (ppCols != nullptr)
	{
		*ppCols = g_arrDanBaoQuanViewCol;
	}
	if (pCnt != nullptr)
	{
		*pCnt = DanBaoQuanViewCol_Count;
	}

	for (int i = 0; i < *pCnt; i++)
	{
		SetDefaultFormat((*ppCols)[i].nColID, (*ppCols)[i].nFormat);
	}
}

//�����ʲ�
#define CreditAssetViewCol_Count 6
tagColumn g_arrCreditAssetViewCol[CreditAssetViewCol_Count];
void InitCreditAssetGridCol()
{
	tagColumn tempCol[] =
	{
		{ ColId_CreditAssetBalance, "�����ʽ���", /*150*/175, COLTYPE_FIX, FALSE }
		,{ ColId_Value1, "��ֵ", /*120*/130, COLTYPE_FIX, FALSE }
		,{ ColId_RongZiMsg, "������Ϣ", 150, COLTYPE_FIX, FALSE }
		,{ ColId_Value2, "��ֵ", /*120*/135, COLTYPE_FIX, FALSE }
		,{ ColId_RongQuanMsg, "��ȯ��Ϣ", /*150*/160, COLTYPE_FIX, FALSE }
		,{ ColId_Value3, "��ֵ", /*120*/185, COLTYPE_FIX, FALSE }

	};

	for (int i = 0; i < CreditAssetViewCol_Count; i++)
	{
		g_arrCreditAssetViewCol[i] = tempCol[i];
	}
}
void GetCreditAssetGridCol(tagColumn **ppCols, int *pCnt)
{
	if (ppCols != nullptr)
	{
		*ppCols = g_arrCreditAssetViewCol;
	}
	if (pCnt != nullptr)
	{
		*pCnt = CreditAssetViewCol_Count;
	}

	for (int i = 0; i < *pCnt; i++)
	{
		SetDefaultFormat((*ppCols)[i].nColID, (*ppCols)[i].nFormat);
	}
}






