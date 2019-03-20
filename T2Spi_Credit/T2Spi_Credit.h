#pragma once
#include "stdafx.h"
#include "../tool/T2Spi.h"

class CT2Spi_Credit:public CT2Spi
{
public:
	char *pRsp;
public:
	CT2Spi_Credit();
	~CT2Spi_Credit();
	void OnRecvJsonMsg(char* pRespdata);
	void OnClose();
	void OnDisConnect();
	void OnConnected();

	/*У��˱���Ԫ���Ƿ���ȷ*/
	bool OnLogin(const Value &root);
	bool OnQueryStockAccount(const Value &root);
	bool OnRevoke(const Value &root);

	/*fund*/
	bool OnQueryFund(const Value &root);
	bool QueryFund();
	bool QueryCreditAsset();
	bool OnQueryCreditAsset(const Value &root);

	/*Position*/
	bool QuerySinglePosition(const string &stock_code);
	bool GainQuerySinglePosition(string &s_str,const string &stock_code);
	bool OnQuerySinglePosition(const Value &root);
	void InitVCreditAsset(VecCreditAsset &VCreditAsset);
	string GainPer_assurescale_value(const Value &root,const int i);
	bool GainFetch_balance(string &fetch_balance);
	void FillVCreditAsset(VecCreditAsset &VCreditAsset, const Value &root,const int i);
	string Modifystring(string s_str);
	
	/*order*/
	bool OnSendOrder(const Value &root);

	void updateEntrust_status(COrder &obj_COrder,const string &entrust_status,string cancel_info);
	void updateEntrust_bs(COrder &obj_COrder, const string &entrust_bs);
	void updateEntrust_bs(CDeal &obj_CDeal, const string &entrust_bs);
	void updateEntrust_type(COrder &obj_COrder, const string &entrust_type);
	
	/*���deal set�󣬸��´˵�ί��*/
	/*DealPush.Cpp*/

	bool On620001(const Value &root);
	/*Subscribe*/
	bool OnSubscribe(const Value &root);
	/*����ί������*/
	bool Deal_Entrust(const Value &root);
	/*����ί������Ϊ������ί������*/
	bool Deal_Entrust_Revoke(const Value &root, const int i, const int count);
	/*����ί������Ϊ�������ʡ����ý��׵�ί������*/
	bool Deal_Entrust_Entrust(const Value &root, const int i, const int count);

	/*����ɽ�����*/
	bool Deal_Deal(const Value &root);
	/*����δ�������ĳɽ�����*/
	bool Deal_Deal_WeiBaoRevoke(const Value &root, const int i, const int count);
	/*����ί������Ϊ���������ʡ����ý��׵ĳɽ�����*/
	bool Deal_Deal_Entrust(const Value &root, const int i, const int count);
	/*����ί������Ϊ�������ʡ����ý��� �ɽ�����Ϊ�����ĳɽ�����*/
	bool Deal_Deal_Entrust_BS(const Value &root, const int i, const int count);
	/*����ί������Ϊ�������ʡ����ý��� �ɽ�����Ϊ�����ĳɽ�����*/
	bool Deal_Deal_Entrust_Revoke(const Value &root, const int i, const int count);
	/*tools*/
	bool UpdateFund_Position(const string SecCode);
};

