#pragma once

#include "Data_Gobal.h"


class CDynaQuote
{
public:
	CDynaQuote();
	CDynaQuote(CSecurity *lpSec);
	CDynaQuote(CSecurity *lpSec, CDynaQuote &Dyna);
	~CDynaQuote();
	CDynaQuote&	operator =(CDynaQuote &Dyna)
	{
		Time = Dyna.Time;
		Open = Dyna.Open;
		High = Dyna.High;
		Low = Dyna.Low;
		Close = Dyna.Close;
		New = Dyna.New;
		Volume = Dyna.Volume;
		return *this;
	}
public:
	bool        SetDepth(CDepth &Depth);                    // д��Depth
	bool        GetDepth(int iGrade, CDepth &Depth);        // ����Depth
public:
	UInt_32			Time;			// ��0�㿪ʼ�Ķ��ٺ���
	double			Open;			// ���̼ۣ�3λС��
	double			High;			// ��߼ۣ��洢����ͬ��
	double			Low;			// ��ͼۣ��洢����ͬ��
	double          Close;          // �����̼ۣ��洢����ͬ��
	double			New;			// ���¼ۣ��洢����ͬ��
	UInt_64           Volume  = 0;//�ɽ���
protected:
	_Depth          MDepth;         // ��ȶ���
	boost::shared_mutex DataMutex_MDepth;
public:
	boost::shared_mutex DataMutex_CDynaQuote;
	CSecurity*      pSec;
};

