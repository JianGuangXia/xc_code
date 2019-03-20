#pragma once

#include "Data_Gobal.h"
enum _EnumRealType
{
	BuySell = 0, //	����
	Query,     //	��ѯ
	Withdraw,     //	����
	BuyerTransferIn,     //	Buyer Transfer in
	ModifyOrder,     //	Modify Order
	ModifyMatchType,     //	Modify Match Type
	RongZi,     //	����
	RongQuan,     //	��ȯ
	CLosePosition,     //	ƽ��
	XinYong,     //	����
	_EnumRealTypeCount
};

enum _EnumRealSts
{
	Deal = 0,  //	�ɽ�
	UselessOrder,      //	�ϵ�
	_RSts3,      //	����ʱ�ɽ���ϵ�
	Confirm,      //	ȷ��
	_EnumRealStsCount
};

class CDeal
{
public:
	CDeal();
	CDeal(COrder *lpOrder, CDeal &Deal);
	~CDeal();
	CDeal& operator = (CDeal &Deal)
	{
		business_id = Deal.business_id;
		exchange_type = Deal.exchange_type;
		stock_code = Deal.stock_code;
		entrust_bs = Deal.entrust_bs;
		business_price = Deal.business_price;
		business_amount = Deal.business_amount;
		business_balance = Deal.business_balance;
		business_time = Deal.business_time;
		business_times = Deal.business_times;
		real_type = Deal.real_type;
		real_status = Deal.real_status;
		entrust_no = Deal.entrust_no;
		entrust_prop = Deal.entrust_prop;
		date = Deal.date;
		report_no = Deal.report_no;
		return *this;
	}
public:
	CString business_id;  //	C32	�ɽ���� 
	CString	exchange_type;//	C4	�������
	CString	stock_code;   //	C6	֤ȯ����
	CString stock_name;   //    C32 ֤ȯ����
	_EnumDirection	entrust_bs;//	C1	��������
	double	business_price; //	N11.4	�ɽ��۸�
	UInt_64	business_amount;//	N10	�ɽ�����
	double	business_balance;//	N16.2	�ɽ����
	UInt_32	business_time;  //	N8	�ɽ�ʱ��
	UInt_32	business_times; //	N5	�ֱʳɽ�����
	_EnumRealType real_type;//	C1	�ɽ�����
	_EnumRealSts real_status;//	C1	�����־
	UInt_64	entrust_no; //	N10	ί�б��
	_EnumEntrustProp	entrust_prop;//	C3	ί������
	UInt_32	date;  //	N8	����
	UInt_32   report_no; //	N8	������
public:
	boost::shared_mutex DataMutex_CDeal;
	COrder*        pOrder;
};

