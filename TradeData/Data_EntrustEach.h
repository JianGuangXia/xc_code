#pragma once
#include "Data_Gobal.h"

class CEntrustEach
{
public:
	CEntrustEach();
	CEntrustEach(CSecurity *lpSec);
	CEntrustEach(CSecurity *lpSec, CEntrustEach &obj_CEntrustEach);
	~CEntrustEach();
	CEntrustEach& operator =(CEntrustEach &obj_CEntrustEach)
	{
		pSec = obj_CEntrustEach.pSec;
		Price = obj_CEntrustEach.Price;
		Volume = obj_CEntrustEach.Volume;
		Amount = obj_CEntrustEach.Amount;
		OrderNo = obj_CEntrustEach.OrderNo;
		Side = obj_CEntrustEach.Side;
		Time = obj_CEntrustEach.Time;
		return *this;
	}
public:
	double Price  = 0;          // �۸�,3λС��
	UInt_64 Volume = 0;         // ����
	double Amount = 0;         // ��3λС��
	UInt_64 OrderNo = 0;        // ί�к�
	char Side = ' ';           // �������� 1����  2����
	UInt_32 Time = 0;			  // ʱ��
public:
	boost::shared_mutex DataMutex_CEntrustEach;
	CSecurity*      pSec;
};


