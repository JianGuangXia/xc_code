#define dllExport __declspec(dllexport)


#define DllId_Fast 1
#define DllId_Credit 2
#define DllId_Auto 3

#define AlertType_SSE 4
#define AlertType_SZSE 5
#define AlertType_Auto 6
#define UF2 20
#define MyINFO 0
#define MyWARNING 1
#define MyERROR 2
#define MyFATAL 3
#define MaintenanceGuaranteeRatio "ά�ֵ�������"
#define LimitPrice "0 �޼۵�"
#define MarketPrice "1 �м۵�"
#define CollateralBuy "����Ʒ����"
#define CollateralSell "����Ʒ����"
#define FinancingBuy "��������"
#define FinancingSell "��ȯ����"
#define BidLimit "�����޼���"
#define EnhancedLimit "��ǿ�޼���"
#define Revoke_Interval 10
#define Alert_FluctuateRatio "DYNA_ALERT1"
#define SSE "SSE"
#define SZSE "SZSE"
#define Auto "Auto"
#define HGT "HGT"
#define SGT "SGT"
#define index_Reply 0
#define index_EntrustPush 1
#define index_DealPush 2
#define Ratio_poundage 0.003 //�����ǧ���������֣���û��ӡ��˰��������̫�Ͳ�����

#define Len_SingleOrderNum 4
#define MaxSecCodeLen_A 6
#define MaxSecCodeLen_G 5 
#define MaxBaseQuantity 2
#define SingleQuerySize 100//��Ϊ100����õģ�50���ܻή�ܶ࣬�ٴ��Ӱ������������ˣ����һή���ٶ�
#define TimingQueryFund 300000
#define TimeShortest 2000
#define ShortTime 5000
#define MediumTime 10000
#define LongestTime 100000

#define Max_Monitor 2000
#define Unit_BaseQuantiry 10000
#define Max_EntrustAmount 1000000


#define Threshold_Discoloration 500

#define RedrawSum_EntrustEach 20

#define Toplimit_Dismantling 60

#define AllMarket 0
#define CustomizePool 1
#define Interval_Display 3000

#define ConfigPath  "..\\share\\config.xml"
#define FontStandard  "��׼"
#define FontMedium  "�е�"
#define FontBig          "���"

/*��ֹΪ0*/
//#define DllId_Fast 60
//#define DllId_Credit 61
#define DllId_Fast 1
#define DllId_Credit 2

/*0 < RefType < 99*/
#define RefType_331100 1//��¼
#define RefType_331300 2//�ɶ��˻���ѯ
#define RefType_620001_12 3//���ĳɽ�
#define RefType_620001_23 4//����ί��
#define RefType_332255_InitFund 5//�ʽ��ѯ
#define RefType_332255_NoFirstQueryFund 6//�ʽ��ѯ
#define RefType_333104_SingleBatchPosition 7//�ֲֲ�ѯ
#define RefType_333104_SinglePosition 8//�ֲֲ�ѯ

#define RefType_333101_SingleBatchOrder 9
#define RefType_333101_OrderForRevoke 11//����ί�е�ί�����͵���ʱΪ�˸���ԭί��״̬�����Ĳ�ѯ

#define RefType_333102_SingleBatchDeal 12

/*������ȯ*/
#define RefType_335501_SingleBatchDanBaoSecurity 40//����ȯ��ѯ
#define RefType_335502_SingleBatchBiaoDiQuan 50//���ȯ��ѯ
#define RefType_335101_InitFund 52//�ʽ��ѯ
#define RefType_335101_NoFirstQueryFund  53//�ʽ��ѯ
#define RefType_335102_SingleBatchPosition 54//�ֲֲ�ѯ
#define RefType_335102_SinglePosition 55//�ֲֲ�ѯ

#define RefType_335103_SingleBatchOrder 56 //ί�в�ѯ
#define RefType_335104_SingleBatchDeal 58 //�ɽ���ѯ

/*windows��Ϣ*/

/*�Զ�����Ϣ*/
#define WM_ReDrawPosition WM_USER + 0 //��ѯ�ֲַ���
#define WM_RedrawFund WM_USER + 1 //��ѯ�ʽ𷵻�
#define WM_RedrawMarket WM_USER + 2 //��������
#define WM_RedrawOrder WM_USER + 3 //�ػ�ί��
#define WM_RedrawSubDeal WM_USER + 4 //�ػ�ֱʳɽ�
#define WM_RedrawAlert WM_USER + 5 //�ػ�Ԥ����
#define WM_ClearAlert WM_USER + 6 //���Ԥ����
#define WM_EndScrollAlert WM_USER + 7 //�����϶�Ԥ���ع�����
#define WM_RedrawAlertRecord WM_USER + 8 //�ػ�Ԥ����

#define WM_RedrawBiaoDiQuan WM_USER + 10 //�ػ���ȯ
#define WM_RedrawDanBaoQuan WM_USER + 11 //�ػ浣��ȯ

#define WM_RedrawEntrustQueue_B1 WM_USER + 12 
#define WM_RedrawEntrustQueue_S1 WM_USER + 13 
#define WM_RedrawEntrustEach WM_USER + 14 
#define WM_RedrawCreditAsset WM_USER + 15 //�ػ������ʲ� 

#define WM_F3 WM_USER + 20 //����
#define WM_F4 WM_USER + 21 //������
#define WM_F5 WM_USER + 22 //����ѡ
#define WM_F6 WM_USER + 23 //��ȫ��
#define WM_RETURN WM_USER + 24

#define WM_AbnormalExit WM_USER + 50 //�쳣�˳�

#define WM_DisConnect_T2 WM_USER + 60
#define WM_Connected_T2 WM_USER + 61

#define WM_DisConnect_alert WM_USER + 62
#define WM_Connected_alert WM_USER + 63
#define WM_stopTrade_alert  WM_USER + 64

#define MainPage_SC_RESTORE WM_USER + 70 //MainPage  SC_RESTORE
#define MainPage_SC_MINIMIZE WM_USER + 71 
#define RetryLogin_MainDlg_Fast 72
#define RetryLogin_MainDlg_Credit 74
#define RetryLogin_MainDlg_HGT 75
#define RetryLogin_MainDlg_SGT 76

#define WM_FastTrade_FundList WM_USER + 80
#define WM_CreditTrade_FundList WM_USER + 81
#define WM_VK_RETURN WM_USER + 100//enter��

#define WM_MainPage_HighlightedItem WM_USER+101
#define WM_RedrawTrade 102

#define  WM_SETDELLHWND        WM_USER + 103
#define  WM_CLOSEMAINFRM       WM_USER + 104

#define  WM_DealTrade       WM_USER + 105

/*market �������б�*/
#define IDMarket_QueryStockMap 1000001
#define IDMarket_SubscribeSingle 1000002
#define IDMarket_SubscribePrevious 1000003
#define IDMarket_SubscribePosition 1000004
#define IDMarket_UnSubscribe 1000005

/*Alert*/
#define Id_RequireIncreaseMonitor 2000001
#define Id_RequireDeclineMonitor 2000002
#define ID_CancelMonitor_SSE 2000003
#define ID_CancelMonitor_SZSE 2000004

/*��������ҵ���ֶα���*/
#define AssetProp_��ͨ�˻� "0"
#define AssetProp_�����˻� "7"
#define password_type_�������� "2"
#define op_entrust_way_����ί�� "7"
#define op_station_My "Test"
#define issue_type_�ɽ����� "12"
#define issue_type_ί������ "23"
#define money_type_����� "0"
#define exchange_type_SSE "1"
#define exchange_type_SZSE "2"
#define entrust_bs_���� "1"
#define entrust_bs_���� "2"
#define entrust_prop_���� "0"

#define Name_SecCode "��Ʊ����"
#define Name_EntrustBs "��������"
#define Name_EntrustNo "ί�к�"
#define Name_EntrustStatus "ί��״̬"
#define MsgType_ConnectPartition 0
#define MsgType_Publish 1
#define MsgType_Heart 2
#define MsgType_Login 10
#define MsgType_Reset 11
#define MsgType_LogOut 12
#define MsgType_SubScribe 13
#define MsgType_reconnecting 90
#define MsgType_reconned 91

#define Magnification_Alert 10000

#define warnningId_Deal "1"
#define warnningId_Revoke "2"
#define warnningId_Entrust "3"
#define warnningId_N_Increase "4"
#define warnningId_Low_Rise "5"
#define warnningId_Increase "6"
#define warnningId_N_Decline "7"
#define warnningId_Decline "8"

#define warnningId_EntrustEach "101"

#define Api_Asy 0
#define Api_Syn 1
#define Api_Syn_SSE 2
#define Api_Syn_SZSE 3

#include <math.h>
#define MIN_VALUE (1e-9) 
#define IS_DOUBLE_ZERO(d) (fabs((double)d) < MIN_VALUE)
#define IS_DOUBLE_EQUAL(d1, d2) (IS_DOUBLE_ZERO(d1 - d2))

#define IS_DOUBLE_GREAT(d1, d2) ( !IS_DOUBLE_EQUAL(d1, d2) && ((double)d1 > (double)d2) )
#define IS_DOUBLE_LESS(d1, d2) ( !IS_DOUBLE_EQUAL(d1, d2) && ((double)d1 < (double)d2) )
#define warnningId_EntrustEach "101"
#define DllId_Fast 1
#define DllId_Credit 2

#define paramsIndex_101_EntrustAmount 0u
#define paramsIndex_101_EntrustBalance 1
#define paramsIndex_101_bBuy 2
#define paramsIndex_101_bSell 3
#define paramsIndex_101_bWithdarwBuy 4
#define paramsIndex_101_bWithdrawSell 5
#define paramsIndex_101_kkkkkk 6
#define paramsIndex_101_DeviateRatio 7

#define paramsIndex_101_bFilterRatio 9
#define paramsIndex_101_increaseRatio 10

#define PercentageIncrease "+(%)"
#define IncreaseByYuan "+(Ԫ)"
#define AlertPrice "ί�м�"
#define latestPrice "�ּ�"

/*timerId*/
#define timerID_queryFund 1

#define EventId_SetTimer_Invalidate 10
#define Time_Invalidate 1500
