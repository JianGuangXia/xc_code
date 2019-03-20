#pragma once

#include "Data_Gobal.h"
class COrder
{
public:
	COrder();
	COrder(CAccount *lpAccount, COrder &Order);
	COrder(CAccount *lpAccount, UInt_64 qentrust_no);
	~COrder();
	COrder& operator = (COrder &Order)
	{
		entrust_no = Order.entrust_no;
		batch_no = Order.batch_no;
		exchange_type = Order.exchange_type;
		stock_code = Order.stock_code;
		stock_name = Order.stock_name;
		compact_id = Order.compact_id;
		entrust_amount = Order.entrust_amount;
		entrust_price = Order.entrust_price;
		business_amount = Order.business_amount;
		business_price = Order.business_price;
		entrust_type = Order.entrust_type;
		withdraw_amount = Order.withdraw_amount;
		entrust_bs = Order.entrust_bs;
		entrust_prop = Order.entrust_prop;
		entrust_status = Order.entrust_status;
		entrust_time = Order.entrust_time;
		entrust_date = Order.entrust_date;
		op_branch_no = Order.op_branch_no;
		op_entrust_way = Order.op_entrust_way;
		op_station = Order.op_station;
		branch_no = Order.branch_no;
		client_id = Order.client_id;
		user_token = Order.user_token;
		cancel_info = Order.cancel_info;
		report_no = Order.report_no;
		report_time = Order.report_time;
		trade_name = Order.trade_name;
		ArrivalSequence_PlaceOrder = Order.ArrivalSequence_PlaceOrder;
		ArrivalSequence_WithdrawOrder = Order.ArrivalSequence_WithdrawOrder;
		return *this;
	}
public:
	UInt_64   entrust_no;    // N10	ί�б��
	UInt_32   batch_no;      //	N8	ί������
	CString	exchange_type; //	C4	�������
	CString	stock_code;    //	C6	֤ȯ����
	CString stock_name;    //   C32 ֤ȯ����
	CString compact_id;//   C32 ��Լ���
	UInt_64	entrust_amount;//	N10	ί������
	double	entrust_price; //	N11.3	ί�м۸�
	UInt_64	business_amount;//	N10	�ɽ�����
	double	business_price; //	N11.4	�ɽ��۸�
	UInt_64   withdraw_amount;//	N10	��������
	_EnumDirection	entrust_bs;//	C1	��������
	_EnumEntrustProp	entrust_prop;//	C3	ί������
	enumEntrustStatus 	entrust_status;  //	C1	ί��״̬
	enumEntrustType    entrust_type;
	UInt_32	entrust_time;   //	N8	ί��ʱ��
	UInt_32	entrust_date;   //	N8	ί������
	UInt_32	op_branch_no;   //	N5	������֧����
	char	op_entrust_way; //	C1	ί�з�ʽ
	CString	op_station;     //	C255	վ���ַ
	UInt_32	branch_no;      //	N5	��֧����
	CString	client_id;      //	C18	�ͻ����
	CString	user_token;     //	C512	�û�����
	CString	cancel_info;    //	C20	�ϵ�ԭ��
	UInt_32   report_no;      //	N8	������
	CString   report_time;    //  N8 �걨ʱ��
	CString trade_name;     //��������
	string ArrivalSequence_PlaceOrder = "000";//����˳�� 0 Ӧ��1 ί������ 2���ɽ�����
	string ArrivalSequence_WithdrawOrder = "000";
public:
	bool           SetDeal(CDeal& Deal);
	bool           GetDeal(CString business_id, CDeal& Deal);
	bool           GetMDeal(_Deal& Deal);

public:
	boost::shared_mutex DataMutex_COrder;
	boost::shared_mutex DataMutex_MDeal;
	_Deal          MDeal;          //  �ɽ��б�
	CAccount*      pAccount;
};
