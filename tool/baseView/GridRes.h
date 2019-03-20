#ifndef __GRIDRESOURCE__
#define __GRIDRESOURCE__

#include "GridCtrlEx.h"
#define ColId_TotalBuyVolume COLID_INT_MIN + 205// 
#define ColId_TotalSellVolume COLID_INT_MIN + 206// 
#define ColId_CurrentAmount COLID_INT_MIN + 143  // ��Ʊ���
#define ColId_EnableAmount COLID_INT_MIN + 132  // ��������



// END INT (ע�⣺��Ӻ��ֵ���ܳ��� 30000)

// BEGIN DOUBLE
#define ColId_EntrustPrice COLID_DOUBLE_MIN + 1001 // ί�м۸�
#define ColId_EntrstAmount COLID_DOUBLE_MIN + 1002 // ί������
#define ColId_BusinessAmount COLID_DOUBLE_MIN + 1003 // �ɽ�����
#define ColId_EntrustNo COLID_DOUBLE_MIN + 1004 // ί�к�
#define ColId_CostPrice COLID_DOUBLE_MIN + 1005 // �ɱ���
#define ColId_LastPrice COLID_DOUBLE_MIN + 1006 // ���¼�
#define ColId_marketValue COLID_DOUBLE_MIN + 1007 // ��ֵ
#define ColId_balance COLID_DOUBLE_MIN + 1008 // ӯ��
#define ColId_balanceRate COLID_DOUBLE_MIN + 1009 // ӯ����
#define ColId_AssetBalance COLID_DOUBLE_MIN + 1010 // �ʲ�ֵ
#define ColId_MarketValue COLID_DOUBLE_MIN + 1011 // ֤ȯ��ֵ
#define ColId_CurrentBalance COLID_DOUBLE_MIN + 1012 // ��ǰ���
#define ColId_EnableBalance COLID_DOUBLE_MIN + 1013 // �����ʽ�
#define ColId_FetchBalance COLID_DOUBLE_MIN + 1014 // ��ȡ���
#define ColId_RealBuyBalance COLID_DOUBLE_MIN + 1015 // �ر�������
#define ColId_RealSellBalance COLID_DOUBLE_MIN + 1016 // �ر��������
#define ColId_AppearPrice COLID_DOUBLE_MIN + 1017 // �����۸�
#define ColId_DealPrice COLID_DOUBLE_MIN + 1018 // 
#define ColId_BuyAveragePrice COLID_DOUBLE_MIN + 1019 // 
#define ColId_SellAveragePrice COLID_DOUBLE_MIN + 1020 // 
#define ColId_TotalBuyMoney COLID_DOUBLE_MIN + 1021 // 
#define ColId_TotalSellMoney COLID_DOUBLE_MIN + 1022 // 
#define ColId_FrozenBalance COLID_DOUBLE_MIN + 1023 // 
#define ColId_UnfrozenBalance COLID_DOUBLE_MIN + 1024 // 
#define ColId_FinRatio COLID_DOUBLE_MIN + 1025 // 
#define ColId_AssureRatio COLID_DOUBLE_MIN + 1026 // 
#define ColId_Value1 COLID_DOUBLE_MIN + 1027 // 
#define ColId_Value2 COLID_DOUBLE_MIN + 1028 // 
#define ColId_Value3 COLID_DOUBLE_MIN + 1029 // 



// END DOUBLE (ע�⣺��Ӻ��ֵ���ܳ��� 50000)

// BEGIN STRING
#define ColId_stockName COLID_STRING_MIN + 1001 // ��Ʊ����
#define COLID_stockCode COLID_STRING_MIN + 1002 // ��Ʊ����
#define COLID_direction COLID_STRING_MIN + 1003 // ��������
#define COLID_entrustStatus COLID_STRING_MIN + 1004 // ί��״̬
#define COLID_reportTime COLID_STRING_MIN + 1005 // �걨ʱ��
#define ColId_MoneyType COLID_STRING_MIN + 1006 // ��������
#define ColId_Check COLID_STRING_MIN + 1007 // ��ѡ
#define ColId_RiseRate COLID_STRING_MIN + 1008 // �ǵ���%
#define ColId_AppearTime COLID_STRING_MIN + 1009 // ����ʱ��
#define ColId_BuySell1 COLID_STRING_MIN + 1010
#define ColId_Price COLID_STRING_MIN + 1011
#define ColId_Amout COLID_STRING_MIN + 1012
#define ColId_Null1 COLID_STRING_MIN + 1013
#define ColId_Null2 COLID_STRING_MIN + 1014
#define ColId_Null3 COLID_STRING_MIN + 1015
#define ColId_Hand COLID_STRING_MIN + 1016
#define ColId_Time COLID_STRING_MIN + 1017
#define ColId_Volume COLID_STRING_MIN + 1018
#define ColId_Money COLID_STRING_MIN + 1019
#define ColId_DealTime COLID_STRING_MIN + 1020 // 
#define ColId_DealNO COLID_STRING_MIN + 1021 // 
#define ColId_Market COLID_STRING_MIN + 1022 // 
#define ColId_FinStatus COLID_STRING_MIN + 1023 // 
#define ColId_AssureStatus COLID_STRING_MIN + 1024 // 
#define ColId_CreditAssetBalance COLID_STRING_MIN + 1025 // 
#define ColId_RongZiMsg COLID_STRING_MIN + 1026 // 
#define ColId_RongQuanMsg COLID_STRING_MIN + 1027 // 
#define ColId_EntrustType COLID_STRING_MIN + 1028 // 
#define ColId_whetherBiaoDi COLID_STRING_MIN + 1029 // ��Ʊ����

/*AlertRecord*/
#define ColID_time COLID_STRING_MIN + 1050
#define ColID_secCode COLID_STRING_MIN + 1051
#define ColID_secName COLID_STRING_MIN + 1052
#define ColID_triggerName COLID_STRING_MIN + 1053
#define ColID_entrustNo COLID_STRING_MIN + 1054
#define ColID_entrustPrice COLID_STRING_MIN + 1055
#define ColID_entrustAmount COLID_STRING_MIN + 1056
#define ColID_note COLID_STRING_MIN + 1057

// END STRING  (ע�⣺��Ӻ��ֵ���ܳ��� 70000)
void SetDefaultFormat(const int ID, int &format);
void GetViewGridCol(tagColumn **ppCols, int *pCnt,vector<tagColumn> &vec);

//void InitPositonViewGridCol();
void GetPositonViewGridCol(tagColumn **ppCols, int *pCnt);

//void InitQueueBuy1GridCol();
void GetQueueBuy1GridCol(tagColumn **ppCols, int *pCnt);

//void InitQueueSell1GridCol();
void GetQueueSell1GridCol(tagColumn **ppCols, int *pCnt);

//void InitOrderEachGridCol();
void GetOrderEachViewGridCol(tagColumn **ppCols, int *pCnt);

//void InitDealDealSummaryGridCol();
void GetDealDealSummaryGridCol(tagColumn **ppCols, int *pCnt);

//void InitCustomPoolGridCol();
void GetCustomPoolGridCol(tagColumn **ppCols, int *pCnt);

//void InitGridCol_OrderDealDetail();
void GetGridCol_OrderDealDetail(tagColumn **ppCols, int *pCnt);

#endif