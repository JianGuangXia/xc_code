#include "Data_Depth.h"

CDepth::CDepth()
{
	pDyna = NULL;
	Grade = 0;      // ��λ
	Price = 0;		// ��Ʒ��С��λ������
	Quantity = 0;	// ί�������ڻ�Ϊ�֣���ƱΪ��
	NumOrders = 0;
}

CDepth::CDepth(CDynaQuote *lpDyna, CDepth &Depth)
{
	pDyna = lpDyna;
	Grade = Depth.Grade;
	Price = Depth.Price;
	Quantity = Depth.Quantity;
	NumOrders = Depth.NumOrders;
}

CDepth::~CDepth()
{
	pDyna = NULL;
}