#pragma once
#include "stdafx.h"
#include "../tool/T2Spi.h"

/*�ع�T2 Spi*/
class CT2Spi_Fast:public CT2Spi
{
public:
	char *pRsp;
public:
	CT2Spi_Fast();
	~CT2Spi_Fast();
	void OnRecvJsonMsg(char* pRespdata);
	void OnClose();
	void OnDisConnect();
	void OnConnected();

	/*У��˱���Ԫ���Ƿ���ȷ*/
	bool OnLogin(const Value &root);
	bool OnQueryStockAccount(const Value &root);
	bool OnRevoke(const Value &root);

	/*Position*/
	bool QuerySinglePosition(const string &stock_code);
	bool GainQuerySinglePosition(string &s_str, const string &stock_code);
	bool OnQuerySinglePosition(const Value &root);

	/*fund*/
	bool OnQueryFund(const Value &root);
	bool QueryFund();

	void updateEntrust_status(COrder &obj_COrder, const string &entrust_status,const string &cancel_info);
	void updateEntrust_bs(COrder &obj_COrder, const string &entrust_bs);
	void updateEntrust_bs(CDeal &obj_CDeal, const string &entrust_bs);

	/*order*/
	bool OnSendOrder(const Value &root);

	/*deal*/
	/*���deal set�󣬸��´˵�ί��*/

	/*DealPush.Cpp*/

	/*Subscribe*/
	bool On620001(const Value &root);
	bool OnSubscribe(const Value &root);
	/*���������������Deal_PushType_EntrustType_RealType ���ǵ������ԣ�ί�����������еķǳ�����дΪentrust*/
	/*����ί������*/
	bool Deal_Entrust(const Value &root);
	/*����ί������Ϊί�е�ί������*/
	bool Deal_Entrust_Entrust(const Value &root, const int i, const int count);
	/*����ί������Ϊ������ί������*/
	bool Deal_Entrust_Revoke(const Value &root, const int i, const int count);

	/*����ɽ�����*/
	bool Deal_Deal(const Value &root);
	/*����ί������Ϊί�еĳɽ�����*/
	bool Deal_Deal_Entrust(const Value &root, const int i, const int count);
	/*����ί������Ϊί�гɽ�����Ϊ�����ĳɽ�����*/
	bool Deal_Deal_Entrust_BS(const Value &root, const int i, const int count);
	/*����ί������Ϊί�гɽ�����Ϊ�����ĳɽ�����*/
	bool Deal_Deal_Entrust_Revoke(const Value &root, const int i, const int count);

	/*tools*/
	bool UpdateFund_Position(const string SecCode);
};
