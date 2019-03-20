#pragma once
#include "Data_Gobal.h"

class CFund
{
public:
	CFund();
	CFund(CData *lpData, CString strFundID);
	CFund(CData *lpData, CFund &Fund);
	~CFund();
	CFund& operator = (CFund &Fund)
	{
		fund_account = Fund.fund_account;
		money_type = Fund.money_type;
		current_balance = Fund.current_balance;
		begin_balance = Fund.begin_balance;
		enable_balance = Fund.enable_balance;
		foregift_balance = Fund.foregift_balance;
		mortgage_balance = Fund.mortgage_balance;
		frozen_balance = Fund.frozen_balance;
		unfrozen_balance = Fund.unfrozen_balance;
		fetch_balance = Fund.fetch_balance;
		fetch_cash = Fund.fetch_cash;
		entrust_buy_balance = Fund.entrust_buy_balance;
		market_value = Fund.market_value;
		asset_balance = Fund.asset_balance;
		interest = Fund.interest;
		integral_balance = Fund.integral_balance;
		fine_integral = Fund.fine_integral;
		pre_interest = Fund.pre_interest;
		pre_fine = Fund.pre_fine;
		pre_interest_tax = Fund.pre_interest_tax;
		correct_balance = Fund.correct_balance;
		fund_balance = Fund.fund_balance;
		opfund_market_value = Fund.opfund_market_value;
		rate_kind = Fund.rate_kind;
		real_buy_balance = Fund.real_buy_balance;
		real_sell_balance = Fund.real_sell_balance;
		net_asset = Fund.net_asset;
		prod_market_value = Fund.prod_market_value;
		return *this;
	}
	void initVec_CreditAsset();
public:
	CString        fund_account;       //�ʽ��˻�
	CString        money_type;       //	C3	�������  ͳһ��Ϊ����ֱ����ʾ��
	double         current_balance;  //	N16.2	��ǰ���
	double   	   begin_balance;    //	N16.2	�ڳ����
	double         enable_balance;   //	N16.2	�����ʽ�
	double         foregift_balance; //	N16.2	��ȡ�ʽ�
	double         mortgage_balance; //	N16.2	��ȡ�ʲ�
	double         frozen_balance;   //	N16.2	�����ʽ�
	double         unfrozen_balance; //	N16.2	�ⶳ�ʽ�
	double         fetch_balance;    //	N16.2	��ȡ���
	double         fetch_cash;       //	N16.2	��ȡ�ֽ�
	double         entrust_buy_balance; //	N16.2	ί��������
	double         market_value;     //	N16.2	֤ȯ��ֵ
	double         asset_balance;    //	N16.2	�ʲ�ֵ
	double         interest;         //	N16.2	��������Ϣ
	double   	   integral_balance; //	N16.2	��Ϣ����
	double         fine_integral;    //	N16.2	��Ϣ����
	double         pre_interest;     //	N16.2	Ԥ����Ϣ
	double         pre_fine;         //	N16.2	Ԥ�Ʒ�Ϣ
	double         pre_interest_tax; //	N16.2	Ԥ����Ϣ˰
	double         correct_balance;  //	N16.2	�ʲ��������
	double         fund_balance;     //	N16.2	���ʽ����
	double         opfund_market_value; //	N16.2	������ֵ
	char           rate_kind;        //	C1	�������
	double         real_buy_balance; // N16.2	�ر�������
	double         real_sell_balance;//	N16.2	�ر��������
	double         net_asset;        //	N16.2	���ʲ�
	double         prod_market_value;//	N16.2	����ڲ�Ʒ��ֵ

	VecCreditAsset VCreditAsset;
	/*{
	{per_assurescale_value ά�ֵ������� ,fin_enable_quota ���ʿ��ö��, slo_enable_quota ��ȯ���ö��},
	{ enable_bail_balance ���ñ�֤�� ,fin_used_quota �������ö��,slo_used_quota ��ȯ���ö�� },
	{ per_assurescale_value"fin_income+slo_income" ��ծ�ܸ�ӯ ,fin_compact_balance ���ʺ�Լ��� ,slo_compact_balance ��ȯ��Լ��� },
	{ used_bail_balance ���ñ�֤�� ,fin_compact_fare ���ʺ�Լ���� ,slo_compact_fare ��ȯ��Լ���� },
	{ assure_enbuy_balance �򵣱�Ʒ�����ʽ� ,fin_compact_interest ���ʺ�Լ��Ϣ ,slo_compact_interest ��ȯ��Լ��Ϣ },

	{ fin_enrepaid_balance �ֽ𻹿�����ʽ� ,fin_market_value ������ֵ ,slo_market_value ��ȯ��ֵ },
	{ fin_enbuy_balance �����ʱ�Ŀ����ʽ� ,fin_income ���ʺ�Լӯ�� ,slo_income ��ȯ��Լӯ�� },
	{ market_value ֤ȯ��ֵ ,fin_used_bail �������ñ�֤�� ,slo_used_bail ��ȯ���ñ�֤�� },
	{ "fetch_balance" ��ȡ��� ,cash_asset �ֽ��ʲ� ,slo_sell_balance ��ȯ���������ܶ� },
	{ slo_max_quota ��ȯ������� ,assure_asset  �����ʲ� ,total_debit ��ծ�ܶ� },

	{ "" ,other_fare �������� ,fin_max_quota ���ʶ������ },
	{ "" ,net_asset ���ʲ� ,slo_enrepaid_balance ��ȯ��ȯ�����ʽ� },
	}*/
	boost::shared_mutex DataMutex_VCreditAsset;

public:
	bool           ClearMPosition();
	bool           ClearMOrder();
	
	bool           SetAccount(CAccount& Account);
	bool           SetPosition(CString strAccountID, CPosition& Position);
	bool           SetOrder(CString strAccountID, COrder& Order);
	bool           SetDeal(CString strAccountID, UInt_64 entrust_no, CDeal& Deal);
	bool           SetSecurity(CString strAccountID, CSecurity &Security);

	bool           SetSecurity_BiaoDi(CString strAccountID, CSecurity &Security);
	bool           SetSecurity_DanBao(CString strAccountID, CSecurity &Security);

	bool           SetVCreditAsset(VecCreditAsset &VCreditAssetTmp);

	bool           GetSecurity(CString strAccountID, CString strSecCode, CSecurity &Security);
	bool           GetVCreditAsset(VecCreditAsset &VCreditAssetTmp);
	bool           GetSecurity_BiaoDi(CString strAccountID, CString strSecCode, CSecurity &Security);
	bool           GetSecurity_DanBao(CString strAccountID, CString strSecCode, CSecurity &Security);

	bool           GetMSecurity(CString strAccountID, _Security& Security);
	bool           GetMSecurity_BiaoDi(CString strAccountID, _Security& Security);
	bool           GetMSecurity_DanBao(CString strAccountID, _Security& Security);

	bool           GetAccount(CString strAccountID, CAccount& Account);
	bool           GetPosition(CString strAccountID, CString strSecCode, CPosition& Position);
	bool           GetOrder(CString strAccountID, UInt_64 entrust_no, COrder& Order);
	bool           GetDeal(CString strAccountID, UInt_64 entrust_no, CString business_id, CDeal& Deal);
	bool           GetMAccount(_Account& Account);
	bool           GetMPosition(CString strAccountID, _Position& Position);
	bool           GetMOrder(CString strAccountID, _Order& Order);
	bool           GetMDeal(CString strAccountID, UInt_64 entrust_no, _Deal& Deal);
protected:
	bool           SetAccount(CString strAccountID);
	_Account       MAccount;      //  �ɶ��˻�
	boost::shared_mutex DataMutex_MAccount;
public:
	boost::shared_mutex DataMutex_CFund;
	CData* pData;
};

