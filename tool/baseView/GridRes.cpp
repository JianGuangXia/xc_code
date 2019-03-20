#include "stdafx.h"
#include "GridRes.h"
// #include "global.h"
// #include "util.h"

void SetDefaultFormat(const int ID, int &format)
{
	format = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
	return;
}

void GetViewGridCol(tagColumn **ppCols, int *pCnt, vector<tagColumn> &vec)
{
	if (ppCols != nullptr)
	{
		*ppCols = &vec[0];
	}
	if (pCnt != nullptr)
	{
		*pCnt = vec.size();
	}

	for (int i = 0; i < *pCnt; i++)
	{
		SetDefaultFormat((*ppCols)[i].nColID, (*ppCols)[i].nFormat);
	}
}

void GetPositonViewGridCol(tagColumn **ppCols, int *pCnt)
{
	static vector<tagColumn> vec_ViewCol
	{
		{ ColId_stockName, "��Ʊ����", 90, COLTYPE_FIX, TRUE }
		,{ COLID_stockCode, "��Ʊ����", 100, COLTYPE_FIX, TRUE }
		,{ ColId_CurrentAmount, "��Ʊ���", 90, COLTYPE_FIX, TRUE }
		,{ ColId_EnableAmount, "��������", 90, COLTYPE_FIX, TRUE }
		,{ ColId_CostPrice, "�ɱ���", 90, COLTYPE_FIX, TRUE }
		,{ ColId_LastPrice, "���¼�", 90, COLTYPE_FIX, TRUE }
		,{ ColId_marketValue, "��ֵ", 110, COLTYPE_FIX, TRUE }
		,{ ColId_balance, "ӯ��", 110, COLTYPE_FIX, TRUE }
		,{ ColId_balanceRate, "ӯ����", 90, COLTYPE_FIX, TRUE }
	};
	if (ppCols != nullptr)
	{
		*ppCols = &vec_ViewCol[0];
	}
	if (pCnt != nullptr)
	{
		*pCnt = vec_ViewCol.size();
	}

	for (int i = 0; i < *pCnt; i++)
	{
		SetDefaultFormat((*ppCols)[i].nColID, (*ppCols)[i].nFormat);
	}
}

//ί�ж�����һ
void GetQueueBuy1GridCol(tagColumn **ppCols, int *pCnt)
{
	static vector<tagColumn> vec_ViewCol
	{
		{ ColId_BuySell1, "��һ", 60, COLTYPE_FIX, FALSE }
		,{ ColId_Price, "", 60, COLTYPE_FIX, FALSE }
		,{ ColId_Amout, "", 60, COLTYPE_FIX, FALSE }
		,{ ColId_Null1, "", 60, COLTYPE_FIX, FALSE }
		,{ ColId_Null2, "", 60, COLTYPE_FIX, FALSE }
		,{ ColId_Null3, "", 60, COLTYPE_FIX, FALSE }
		,{ ColId_Hand, "����", 60, COLTYPE_FIX, FALSE }
	};
	if (ppCols != nullptr)
	{
		*ppCols = &vec_ViewCol[0];
	}
	if (pCnt != nullptr)
	{
		*pCnt = vec_ViewCol.size();
	}

	for (int i = 0; i < *pCnt; i++)
	{
		SetDefaultFormat((*ppCols)[i].nColID, (*ppCols)[i].nFormat);
	}
}

//ί�ж�����һ
void GetQueueSell1GridCol(tagColumn **ppCols, int *pCnt)
{
	static vector<tagColumn> vec_ViewCol
	{
		{ ColId_BuySell1, "��һ", 60, COLTYPE_FIX, FALSE }
		,{ ColId_Price, "", 60, COLTYPE_FIX, FALSE }
		,{ ColId_Amout, "", 60, COLTYPE_FIX, FALSE }
		,{ ColId_Null1, "", 60, COLTYPE_FIX, FALSE }
		,{ ColId_Null2, "", 60, COLTYPE_FIX, FALSE }
		,{ ColId_Null3, "", 60, COLTYPE_FIX, FALSE }
		,{ ColId_Hand, "����", 60, COLTYPE_FIX, FALSE }
	};
	if (ppCols != nullptr)
	{
		*ppCols = &vec_ViewCol[0];
	}
	if (pCnt != nullptr)
	{
		*pCnt = vec_ViewCol.size();
	}

	for (int i = 0; i < *pCnt; i++)
	{
		SetDefaultFormat((*ppCols)[i].nColID, (*ppCols)[i].nFormat);
	}
}

//���ί��
void GetOrderEachViewGridCol(tagColumn **ppCols, int *pCnt)
{
	static vector<tagColumn> vec_ViewCol
	{
		{ ColId_Time, "ʱ��", 120, COLTYPE_FIX, FALSE }
		,{ ColId_EntrustNo, "ί�к�", 120, COLTYPE_FIX, TRUE }
		,{ ColId_Price, "�۸�", 120, COLTYPE_FIX, TRUE }
		,{ ColId_Volume, "����", 120, COLTYPE_FIX, TRUE }
		,{ ColId_Money, "���", 130, COLTYPE_FIX, TRUE }
		,{ COLID_direction, "��������", 120, COLTYPE_FIX, TRUE, TRUE }
	};
	if (ppCols != nullptr)
	{
		*ppCols = &vec_ViewCol[0];
	}
	if (pCnt != nullptr)
	{
		*pCnt = vec_ViewCol.size();
	}

	for (int i = 0; i < *pCnt; i++)
	{
		SetDefaultFormat((*ppCols)[i].nColID, (*ppCols)[i].nFormat);
	}
}

//�ֱʳɽ�
void GetGridCol_OrderDealDetail(tagColumn **ppCols, int *pCnt)
{
	static vector<tagColumn> vec_ViewCol
	{
		{ ColId_stockName, "��Ʊ����", 90, COLTYPE_FIX, FALSE }
		,{ COLID_stockCode, "��Ʊ����", 90, COLTYPE_FIX, FALSE }
		,{ COLID_direction, "��������", 90, COLTYPE_FIX, FALSE }
		,{ ColId_BusinessAmount, "�ɽ�����", 90, COLTYPE_FIX, FALSE }
		,{ ColId_DealPrice, "�ɽ��۸�", 90, COLTYPE_FIX, FALSE }
		,{ ColId_DealTime, "�ɽ�ʱ��", 90, COLTYPE_FIX, FALSE }
		,{ ColId_DealNO, "�ɽ����", 195, COLTYPE_FIX, FALSE }
		,{ ColId_EntrustNo, "ί�к�", 100, COLTYPE_FIX, FALSE }
	};
	if (ppCols != nullptr)
	{
		*ppCols = &vec_ViewCol[0];
	}
	if (pCnt != nullptr)
	{
		*pCnt = vec_ViewCol.size();
	}

	for (int i = 0; i < *pCnt; i++)
	{
		SetDefaultFormat((*ppCols)[i].nColID, (*ppCols)[i].nFormat);
	}
}

//�ɽ�����
void GetDealDealSummaryGridCol(tagColumn **ppCols, int *pCnt)
{
	static vector<tagColumn> vec_ViewCol
	{
		{ ColId_stockName, "��Ʊ����", 90, COLTYPE_FIX, FALSE }
		,{ COLID_stockCode, "��Ʊ����", 90, COLTYPE_FIX, FALSE }
		,{ ColId_TotalBuyVolume, "��������", 90, COLTYPE_FIX, FALSE }
		,{ ColId_TotalSellVolume, "��������", 100, COLTYPE_FIX, FALSE }
		,{ ColId_BuyAveragePrice, "�������", 90, COLTYPE_FIX, FALSE }
		,{ ColId_SellAveragePrice, "��������", 90, COLTYPE_FIX, FALSE }
		,{ ColId_TotalBuyMoney, "������", 110, COLTYPE_FIX, FALSE }
		,{ ColId_TotalSellMoney, "�������", 110, COLTYPE_FIX, FALSE }
	};
	if (ppCols != nullptr)
	{
		*ppCols = &vec_ViewCol[0];
	}
	if (pCnt != nullptr)
	{
		*pCnt = vec_ViewCol.size();
	}

	for (int i = 0; i < *pCnt; i++)
	{
		SetDefaultFormat((*ppCols)[i].nColID, (*ppCols)[i].nFormat);
	}
}

//��ѡ��
void GetCustomPoolGridCol(tagColumn **ppCols, int *pCnt)
{
	static vector<tagColumn> vec_ViewCol
	{
		{ ColId_Market, "�г�", 200, COLTYPE_FIX, TRUE }
		,{ ColId_stockName, "��Ʊ����", 200, COLTYPE_FIX, TRUE }
		,{ COLID_stockCode, "��Ʊ����", 200, COLTYPE_FIX, TRUE }
	};
	if (ppCols != nullptr)
	{
		*ppCols = &vec_ViewCol[0];
	}
	if (pCnt != nullptr)
	{
		*pCnt = vec_ViewCol.size();
	}

	for (int i = 0; i < *pCnt; i++)
	{
		SetDefaultFormat((*ppCols)[i].nColID, (*ppCols)[i].nFormat);
	}
}






