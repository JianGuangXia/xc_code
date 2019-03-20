#pragma once
#include "Data_Gobal.h"


class CDepth
{
public:
	CDepth();
	CDepth(CDynaQuote *lpDyna, CDepth &Depth);
	~CDepth();
	CDepth&	operator = (CDepth &Depth)
	{
		Grade = Depth.Grade;
		Price = Depth.Price;
		Quantity = Depth.Quantity;
		NumOrders = Depth.NumOrders;
		return *this;
	}
public:
	int             Grade;      // ��λ
	double			Price;		// ��Ʒ��С��λ������
	UInt_64			Quantity;	// ί�������ڻ�Ϊ�֣���ƱΪ��
	UInt_64         NumOrders = 0;//��ί�б���
public:
	boost::shared_mutex DataMutex_CDepth;
	CDynaQuote*     pDyna;
};

