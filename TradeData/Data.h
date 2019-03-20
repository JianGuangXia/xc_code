#pragma once
#include "Data_Gobal.h"
#include "../share/define.h"

class CAertRecord;
class CEntrustEachConfig;
class CAutoTradeConfig;
class CAertRecord
{
public:
	CAertRecord()
	{

	}
	~CAertRecord()
	{
		int i = 0;
	}
	CString s_alertTime;
	CString stock_code;
	CString stock_name;
	CString cause;
	CString entrust_no;
	CString entrust_price;
	CString entrust_amount;
	CString note;
public:
	void changeIntoJson(Json::Value &val)
	{
		val["s_alertTime"] = string(s_alertTime);
		val["stock_code"] = string(stock_code);
		val["stock_name"] = string(stock_name);
		val["cause"] = string(cause);
		val["entrust_no"] = string(entrust_no);

		val["entrust_price"] = string(entrust_price);
		val["entrust_amount"] = string(entrust_amount);
		val["note"] = string(note);
	}
};
class CAlertConfig
{
public:
	size_t Template_Stock = AllMarket;
	size_t Template_Alert = enum_Increase;
	double IncreaseRatio = 7;
	bool bRemove_Increase = false;
	unsigned int Period_Increase_day = 30;
	size_t Period_Increase_second = 0;

	size_t Minute_N_Rise = 5;
	double IncreaseRatio_N_Rise = 3;

	size_t Minute_Low_Rise = 5;
	double BeginRatio_Low_Rise = 3;
	double EndRatio_Low_Rise = 3;
};


class CAlertNeed
{
public:
	CAlertNeed();
	CAlertNeed(CAlertNeed &obj_CAlertNeed);
	~CAlertNeed() {};
	CAlertNeed& operator = (CAlertNeed &obj_CAlertNeed)
	{
		SecName = obj_CAlertNeed.SecName;
		SecCode = obj_CAlertNeed.SecCode;
		MarketCode = obj_CAlertNeed.MarketCode;
		FluctuateRatio = obj_CAlertNeed.FluctuateRatio;
		PrevClosePx = obj_CAlertNeed.PrevClosePx;
		NewPrice = obj_CAlertNeed.NewPrice;
		Price_Jump = obj_CAlertNeed.Price_Jump;
		Time_Jump = obj_CAlertNeed.Time_Jump;
		s_bBiaoDiQuan = obj_CAlertNeed.s_bBiaoDiQuan;
		return *this;
	}
public:
	CString SecName;//֤ȯ����
	CString SecCode;//֤ȯ����
	CString MarketCode = "";
	double FluctuateRatio;//�ǵ���
	double PrevClosePx;//������
	double NewPrice;//���¼�
	double Price_Jump;//�����۸�
	CString Time_Jump;//����ʱ��
	CString s_bBiaoDiQuan = "";
};

class CEntrustEachConfig
{
public:
	size_t entrustAmount = 100;
	double entrustBalance = 0;//��Ԫ
	bool bBuy = true;
	bool bSell = false;
	bool bWithdrawBuy = false;

	bool bWithdrawSell = false;
	double DeviateRatio = 2;
	bool bFilterRatio = false;
	double increaseRatio = 0;
	size_t Template_stock = AllMarket;
	bool bSound = false;
};

class CAutoTradeConfig
{
public:
	CString s_bPercentageIncrease = "";
	double IncreaseValue = 0;
	CString priceType = "";
	bool bDefaultAmount = true;
	size_t DefaultAmount = 100;
	double DefaultBalance = 100;

	bool bManualConfirm = true;
	double limit_entrustBalance = 100;
	bool bTimingTrading = false;
	CString beginTime = "";
	CString endTime = "";
};
typedef std::tr1::shared_ptr<CAlertNeed> PtrAlert;
typedef map<CString, PtrAlert> _MAlert; // map<SecCode,PtrAlert>
typedef map<string, _MAlert> _MALLAlert;    // map<warningId_market,map<SecCode,PtrAlert>>

typedef multimap<double, PtrAlert> _MSpecialAlert;//map<FluctuateRatio,PtrAlert>;������ʾ��
typedef map<string, UInt_64> Type_CheckList;
typedef map<CString, int> Type_M_blackList;

#include "Data_Order.h"
typedef map<int, COrder> Type_OrderList; //map<ref_id,COrder> 

typedef vector<CAertRecord> Type_VCAertRecord;
typedef map<string, UInt_64> Type_MAlertId;//map<warningId,version>version Ϊ�汾�ţ�ÿ�η���Ԥ������һ��version

class CData
{
public:
	CData();
	~CData();

public:
	/*��½ʱ����ѯһ�Σ��������йɶ��˻��µ�����֤ȯ���룬���ںϷ���У�飬�Լ��������鶩�ĵ�ʱ���ȡ��Ӧ��MarketCode*/
	bool         	SetMarket(CMarket &Market);   // CMarket�г��������     
	bool 		    SetSecurity(CString strMarketCode, CSecurity &Security);  //CSecurity֤ȯ�������                                       
	bool  		    SetDyna(CString strMarketCode, CString strSecCode, CDynaQuote &Dyna);
	bool		    SetDepth(CString strMarketCode, CString strSecCode, CDepth &Depth);//CDepth��λ����
	bool		    SetEntrustQueue(CString strMarketCode, CString strSecCode, CEntrustQueue &obj_CEntrustQueue);
	bool		    SetEntrustEach(CString strMarketCode, CString strSecCode, CEntrustEach &obj_CEntrustEach);
	bool            ClearEntrustEach(CString strMarketCode, CString strSecCode);
	bool            ClearMPosition(CString strFundID);
	bool            ClearMOrder(CString strFundID);


	bool            SetFund(CFund &Fund);//CFund�ʽ��˻�������
	bool            SetAccount(CString strFundID, CAccount& Account);//CAccount�ɶ��˻�����
	bool            SetPosition(CString strFundID, CString strAccountID, CPosition& Position);//CPosition ֤ȯ�������
	bool            SetOrder(CString strFundID, CString strAccountID, COrder& Order);//COrder ί��id����
	bool            SetDeal(CString strFundID, CString strAccountID, UInt_64 entrust_no, CDeal& Deal); //CDeal �ɽ���ű���
																										/*�������еĶ��ĵ�֤ȯ����*/
	bool 		    SetSecurity(CString strFundID, CString strAccountID, CSecurity &Security);//CSecurity֤ȯ������� 
																							
	bool 		    SetSecurity_BiaoDi(CString strFundID, CString strAccountID, CSecurity &Security);
	/*set����֤ȯ*/
	bool 		    SetSecurity_DanBao(CString strFundID, CString strAccountID, CSecurity &Security);
	
	bool            SetVCreditAsset(CString strFundID, VecCreditAsset &VCreditAsset);

	/*��ȫ�������л�ȡָ����Ϣ���Ϸ��Լ���ã�*/
	bool         	GetMarket(CString strMarketCode, CMarket &Market);
	bool 		    GetSecurity(CString strMarketCode, CString strSecCode, CSecurity &Security);
	bool  		    GetDyna(CString strMarketCode, CString strSecCode, CDynaQuote &Dyna);
	bool		    GetDepth(CString strMarketCode, CString strSecCode, int iGrade, CDepth &Depth);
	bool		    GetMEntrustQueue(CString strMarketCode, CString strSecCode, int Grade, VecEntrustQueue &VEntrustQueue);
	bool		    GetVEntrustEach(CString strMarketCode, CString strSecCode, VecEntrustEach &VCEntrustEach,int RedrawSum);
	/*��ȡ��������*/
	bool            GetFund(CString strFundID, CFund &Fund);
	/*���е�get Account��Ĳ����ǻ�ȡһ��Account�µ����ж���,�������¹ҵ�map֮��ģ�����get AccountMap���ͳͳ��ֻ��ȡAccount�³���map֮���
	�������ݵĽṹ�����ĳ�Ա������������������޶ȵļ����ڴ濽������߳����ٶȣ�����ʹ�������鷳�ܶ࣬����get account mapֻ�Ǳ�֤map���value
	��account�ĳ�Ա���������¼����mapû�������Ҫʹ��position map��ֻ��ʹ��get position map����ʹ��get account map������get acoount��=�������ˣ�*/
	bool            GetAccount(CString strFundID, CString strAccountID, CAccount& Account);
	bool            GetPosition(CString strFundID, CString strAccountID, CString strSecCode, CPosition& Position);
	bool            GetOrder(CString strFundID, CString strAccountID, UInt_64 entrust_no, COrder& Order);
	bool            GetDeal(CString strFundID, CString strAccountID, UInt_64 entrust_no, CString business_id, CDeal& Deal);

	bool 		    GetSecurity_BiaoDi(CString strFundID, CString strAccountID, CString strSecCode, CSecurity &Security);
	bool 		    GetSecurity_DanBao(CString strFundID, CString strAccountID, CString strSecCode, CSecurity &Security);
	bool            GetMSecurity_BiaoDi(CString strFundID, CString strAccountID, _Security& Security);
	bool            GetMSecurity_DanBao(CString strFundID, CString strAccountID, _Security& Security);
	
	bool            GetMAccount(CString strFundID, _Account& Account);
	bool            GetMPosition(CString strFundID, CString strAccountID, _Position& Position);
	bool            GetMOrder(CString strFundID, CString strAccountID, _Order& Order);
	bool            GetMDeal(CString strFundID, CString strAccountID, UInt_64 entrust_no, _Deal& Deal);
	bool            GetMSecurity(CString strFundID, CString strAccountID, _Security& Security);
	bool            GetMSecurity(CString strMarketCode, _Security& Security);

	/*��ȡ������Ϣ*/
	bool 		    GetSecurity(CString strFundID, CString strAccountID, CString strSecCode, CSecurity &Security);
	bool            GetVCreditAsset(CString strFundID, VecCreditAsset &VCreditAsset);
	


	/*Ԥ����*/
	string           GetKey(string warnningId, CString marketId);
	bool            GetAlert(string warnningId, CString marketId,const CString &SecCode,CAlertNeed &obj_Alert);
	bool            SetAlert(string warnningId, CString marketId,CAlertNeed &obj_Alert);
	bool            GetMAlert_All(_MALLAlert& Alert);
	bool            GetMAlert_Special(string warnningId,_MSpecialAlert &MSpecialAlert);
	bool            ClearMAlert_ALL();
	bool            deleteElement_MAlert(string warnningId, CString marketId, const CString &stock_code);
	bool            ClearPreviousRedrawList();
	bool            insertPreviousRedrawList(const CString &SecCode);
	bool            VerifybJump(const CString &SecCode);
	/*AlertRecord*/
	bool            GetVAlertRecord(Type_VCAertRecord &vec_CAertRecordTmp);
	bool            SetAlertRecord(CAertRecord &obj_CAertRecord);
	
	/*���߷���*/
	bool            Market2Account(const CString &strFundID, const CString &strMarketCode, CString& strAccountID);
	bool            Account2Market(CString strFundID, CString strAccountID, CString& strMarketCode);
	bool            SecCode2StockAccount(const CString &SecCode, CString &StockAccount);
	bool            SecCode2MarketCode(const CString &SecCode, CString &MarketCode);
	bool            SecCode2ExchangeType(const CString &SecCode, string &ExchangeType);
	bool            SecCode2SecName(const CString &SecCdoe, CString &SecName);

	bool            Account2ExchangeType(const CString &stock_account, string &exchange_type);
	bool            initM_AlertSecCode();
	bool            inspect_bAlert(CString stock_code);
	bool            inspectbStock(const CString strMarketCode, const CString &stock_code);
	/*ref_id*/
	bool SetRefId_T2(int RefID_HS, int MyRefId);
	bool GetEraseRefId_T2(int RefID_HS,int &MyRefId);
protected:
	bool            SetMarket(CString strMarketCode);
	bool            SetFund(CString strFundID);
public:
	_MALLAlert              MALLAlert;
	boost::shared_mutex       MALLAlert_Lock;
	map<CString, int> M_PreviousRedrawList;
	boost::shared_mutex M_PreviousRedrawList_Lock;

	Type_CheckList M_CheckList;//key report_no+ "_" +stock_account ,entrust_no  ��ί�лر���ʱ��insert��map���ڳ�����ʱ��ʹ��
	Type_OrderList M_OrderList;//key ref_id ���������¼�������������һ��Ҫ���

	_Longlong                 ref_id;
	boost::shared_mutex       ref_Lock;
	_Fund   MFund;//�ʽ��˻�����
	boost::shared_mutex      MFund_Lock;
	/*��һ�ε�½ʱ���£���������֤ȯ�б����ںϷ���У�飬֮������������T2��ѯ�������market server���͵�����*/
	_Market MMarket;
	boost::shared_mutex      MMarket_Lock;

	CAlertConfig obj_CAlertConfig;
	volatile bool bBeginRelease = false;//��release��Դ��ʱ��Ҫ��Ӧonclose
	bool bRun_MainPageDlg;
	bool bEndQueryDanBaoQuan_SSE;
	bool bEndQueryDanBaoQuan_SZSE;
	bool bT2SupportMarket;//���������T2��ѯ��֤ȯ�˺ŵ������Ƿ�֧�� trueΪ֧��
	bool bActivity_TradeData;
	bool bQuit_ErrorInfo = false;
	bool bRuning_ErrorInfo = false;
	bool bLog_MarketAlert = true;

	int OrderInterval = 0;//����
	int Frequency = 0;//ÿ���µ�����

	CString fund_account;//�ʽ��˻�
	CString TradingSecCode;

	HANDLE  LoginT2_Event;//��½T2����
	HANDLE  LoginSSEMarket_Event;//��½Market����
	HANDLE  LoginSZSEMarket_Event;//��½Market����

	HANDLE  QueryStockAccount_Event; //  ��½��ʱ��������ѯһ���ʽ��˻��µ����йɶ��˻�  
	HANDLE  QuerySSEStockMap_Event;     //  ��½��ʱ��������ѯ��֧�����鶩�ĵĹ�Ʊmap
	HANDLE  QuerySZSEStockMap_Event;
	HANDLE  InitFund_Event;

	HANDLE  QueryDeal_Event;//��½��ʱ��������ʼ��deal demo
	HANDLE  QueryDanBaoQuanMap_Event; //��¼��ʱ��������ѯһ���ʽ��˻��µĵ���֤ȯ

	HANDLE  UnSubscribe_Event;
	HANDLE  Subscribe_Event;

	HANDLE  Event_ConnectPartition_SSE = CreateEvent(NULL, FALSE, FALSE, NULL);
	HANDLE  Event_ConnectPartition_SZSE = CreateEvent(NULL, FALSE, FALSE, NULL);
	HANDLE  Event_loginSSEAlert = CreateEvent(NULL, FALSE, FALSE, NULL);
	HANDLE  Event_loginSZSEAlert = CreateEvent(NULL, FALSE, FALSE, NULL);
	HANDLE  Event_ResetAlert_SSE = CreateEvent(NULL, FALSE, FALSE, NULL);
	HANDLE  Event_ResetAlert_SZSE = CreateEvent(NULL, FALSE, FALSE, NULL);


	HANDLE Event_SendOrder = CreateEvent(NULL, FALSE, TRUE, NULL);//2 �Զ���Ϊ���ź�,3��ʼ���ź�
	HANDLE Event_SendAllOrder = CreateEvent(NULL, FALSE, TRUE, NULL);
	/*����ָ�룬Ϊ���Զ�����Ϣ*/
	intptr_t intptr_CFastTradeDlg{};

	string branch_no;
	string sysnode_id;
	string s_user;
	string s_pass;
	HWND hwnd_MainPageDlg;
	HWND hwnd_TradeDlg;

	SYSTEMTIME systime_SendOrder;
	SYSTEMTIME systime_OnSendOrder;
	SYSTEMTIME systime_BeginQueryOrder;
	SYSTEMTIME systime_RecvQueryOrder;
	SYSTEMTIME systime_FinishQueryOrder;
	int TestSpeed;
	bool bFullLog = false;
	queue<string> Queue_T2ErrorInfo;
	queue<string> Queue_MarketErrorInfo;
	queue<unsigned int> Queue_WmMessage;//�ڽ��״���û�г�ʼ��֮ǰ�ݴ��ػ���Ϣ	
	map<CString, int> M_AlertSecCode;
	map<int, int> MRefId_T2;//key ����Refid, value �Զ���Id
	boost::shared_mutex Lock_MRefId_T2;
	string S_StockPath_Fast = "../share/StockList_Alert_Fast.json";
	string S_StockPath_Credit = "../share/StockList_Alert_Credit.json";
	string S_StockPath_Auto = "../share/StockList_Alert_Auto.json";
	
	string partitionId = "";
	string user_alert = "";
	CAutoTradeConfig obj_CAutoTradeConfig;

	Type_VCAertRecord vec_CAertRecord;
	boost::shared_mutex lock_VAlertRecord;

	CEntrustEachConfig obj_CEntrustEachConfig;
	Type_M_blackList M_blackList;
	Type_MAlertId M_alertId;
};