#include "Data_Deal.h"

CDeal::CDeal()
{
	pOrder = NULL;
	business_id = "";  //	C32	�ɽ����
	exchange_type = "";//	C4	�������
	stock_code = "";   //	C6	֤ȯ����
	stock_name = "";   //   C32 ֤ȯ����
	entrust_bs = _Buy;//	C1	��������
	business_price = 0; //	N11.4	�ɽ��۸�
	business_amount = 0;//	N10	�ɽ�����
	business_balance = 0;//	N16.2	�ɽ����
	business_time = 0;  //	N8	�ɽ�ʱ��
	business_times = 0; //	N5	�ֱʳɽ�����
	real_type = BuySell;//	C1	�ɽ�����
	real_status = Deal;//	C1	�����־
	entrust_no = 0; //	N10	ί�б��
	entrust_prop = _Limit;//	C3	ί������
	date = 0;  //	N8	����
	report_no = 0;  // N8 ������
}

CDeal::CDeal(COrder *lpOrder, CDeal &Deal)
{
	pOrder = lpOrder;
	business_id = Deal.business_id;
	exchange_type = Deal.exchange_type;
	stock_code = Deal.stock_code;
	stock_name = Deal.stock_name;
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
}

CDeal::~CDeal()
{
	pOrder = NULL;
}