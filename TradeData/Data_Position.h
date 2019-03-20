#pragma once

#include "Data_Gobal.h"

class CPosition
{
public:
	CPosition();
	CPosition(CAccount *lpAccount, CPosition &Position);
	~CPosition();
	CPosition& operator = (CPosition  &Position)
	{
		stock_code = Position.stock_code;
		stock_name = Position.stock_name;
		stock_type = Position.stock_type;
		hold_amount = Position.hold_amount;
		current_amount = Position.current_amount;
		enable_amount = Position.enable_amount;
		frozen_amount = Position.frozen_amount;
		last_price = Position.last_price;
		cost_price = Position.cost_price;
		keep_cost_price = Position.keep_cost_price;
		income_balance = Position.income_balance;
		market_value = Position.market_value;
		av_buy_price = Position.av_buy_price;
		av_income_balance = Position.av_income_balance;
		cost_balance = Position.cost_balance;
		profit_ratio = Position.profit_ratio;
		return *this;
	}
public:
	CString     stock_code;   //	C6	֤ȯ����
	CString     stock_name;   //    C32 ֤ȯ����
	CString	    stock_type;
	UInt_64		hold_amount;  //	N10	��������
	UInt_64  	current_amount; //	N10	��ǰ����
	UInt_64  	enable_amount;  //	N10	��������
	UInt_64   	frozen_amount;  //	N10	��������
	double  	last_price;   //	N16.3	���¼�
	double  	cost_price;   //	N11.3	�ɱ���
	double   	keep_cost_price;//	N11.3	������
	double  	income_balance; //	N16.2	ӯ�����
	double  	market_value; //	N16.2	֤ȯ��ֵ
	double  	av_buy_price; //	N11.4	�������
	double  	av_income_balance;//	N16.2	ʵ��ӯ��
	double   	cost_balance; //	N16.2	�ֲֳɱ�
	double      profit_ratio; //    N16.2	ӯ������(%)

public:
	boost::shared_mutex DataMutex_CPosition;
	CAccount*        pAccount;
};


