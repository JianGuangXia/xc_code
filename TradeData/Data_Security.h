#pragma once
#include "Data_Gobal.h"

class CSecurity
{
public:
	CSecurity();
	CSecurity(CAccount *lpAccount, CString strSecCode);
	CSecurity(CAccount *lpAccount, CSecurity &Security);
	CSecurity(CMarket *lpMarket, CString strSecCode);
	CSecurity(CMarket *lpMarket, CSecurity &Security);
	~CSecurity();
	CSecurity&	operator = (CSecurity &Security)
	{
		VEntrustQueue_B1.resize(EntrustQueueSize);
		VEntrustQueue_S1.resize(EntrustQueueSize);
		stock_code = Security.stock_code;
		stock_type = Security.stock_type;
		stock_name = Security.stock_name;
		PinYin = Security.PinYin;
		StartDate = Security.StartDate;
		UpLimitPrice = Security.UpLimitPrice;
		DownLimitPrice = Security.DownLimitPrice;
		PrevClosePx = Security.PrevClosePx;
		fin_ratio = Security.fin_ratio;
		assure_ratio = Security.assure_ratio;
		fin_status = Security.fin_status;
		assure_status = Security.assure_status;

		buy_unit = Security.buy_unit;
		sell_unit = Security.sell_unit;
		up_price = Security.up_price;
		down_price = Security.down_price;
		enable_amount = Security.enable_amount;
		s_bBiaoDiQuan = Security.s_bBiaoDiQuan;
		return *this;
	}

public:
	bool		SetDepth(CDepth& Depth);
	bool		SetDyna(CDynaQuote& Dyna);
	bool		SetEntrustQueue(CEntrustQueue& obj_CEntrustQueue);
	bool        SetEntrustQueue(CEntrustQueue& obj_CEntrustQueue, VecEntrustQueue &VEntrustQueue, boost::shared_mutex &DataMutex_MEntrustQueue);
	bool		SetEntrustEach(CEntrustEach& obj_CEntrustEach);
	bool        ClearEntrustEach();

	bool		GetDepth(int iGrade, CDepth& Depth);
	bool		GetMEntrustQueue(int Grade, VecEntrustQueue &VEntrustQueue);
	bool		GetVEntrustEach(VecEntrustEach &VCEntrustEach, int RedrawSum);

	bool		GetDyna(CDynaQuote& Dyna);
public:
	CString	    stock_code;			// ֤ȯ����
	CString	    stock_type;			// ����  0 ��������֧�ֵĹ�Ʊ �Ϻ���ES�����ڵ�1(����A��) 2(��С���Ʊ002��ͷ���ں������0��Ʊ��) 3(��ҵ���Ʊ)
	CString  	stock_name;		    // ��Ʊ����
	CString	    PinYin;				// ƴ�������ã�
	CString     StartDate;          // ��������
	CString     buy_unit;			//���뵥λ
	CString		sell_unit;			//������λ
	double	    UpLimitPrice;		// ������ͣ��
	double	    DownLimitPrice;		// ���յ�ͣ��
	double      PrevClosePx;        // �����̼� 
	double      fin_ratio;          //���ʱ�֤�����
	double      assure_ratio;       //����������

	double		up_price;			//���޼�
	double		down_price;			//���޼�
	UInt_64		enable_amount;		//��������

	char        fin_status;         //����״̬
	char        assure_status;      //����״̬
	CString     s_bBiaoDiQuan;        //�Ƿ��Ǳ��ȯ���ǵĻ����Ϊ���ȯ


protected:
	bool        SetDyna();
	PtrDynaQuote	pDyna;          // ��������
	VecEntrustQueue VEntrustQueue_B1;
	VecEntrustQueue VEntrustQueue_S1;
	_EntrustEach MEntrustEach;
public:
	boost::shared_mutex DataMutex_CDyna;
	boost::shared_mutex DataMutex_MEntrustQueue_B1;
	boost::shared_mutex DataMutex_MEntrustQueue_S1;
	boost::shared_mutex DataMutex_MEntrustEach;
	boost::shared_mutex DataMutex_CSecurity;
	CMarket*        pMarket;
	CAccount*       pAccount;
};

