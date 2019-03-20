#include "Data_DynaQuote.h"
#include "Data_Depth.h"

CDynaQuote::CDynaQuote()
{
	pSec = NULL;
	Time = 0;			// ��0�㿪ʼ�Ķ��ٺ���
	Open = 0;			// ���̼ۣ���Ʒ��С��λ��������2λС����Open=1234�ʹ���12.34
	High = 0;			// ��߼ۣ��洢����ͬ��
	Low = 0;			// ��ͼۣ��洢����ͬ��
	Close = 0;          // �����̼ۣ��洢����ͬ��
	New = 0;			// ���¼ۣ��洢����ͬ��
	Volume = 0;
}

CDynaQuote::CDynaQuote(CSecurity *lpSec)
{
	pSec = lpSec;
	Time = 0;			// ��0�㿪ʼ�Ķ��ٺ���
	Open = 0;			// ���̼ۣ���Ʒ��С��λ��������2λС����Open=1234�ʹ���12.34
	High = 0;			// ��߼ۣ��洢����ͬ��
	Low = 0;			// ��ͼۣ��洢����ͬ��
	Close = 0;          // �����̼ۣ��洢����ͬ��
	New = 0;			// ���¼ۣ��洢����ͬ��
	Volume = 0;
}

CDynaQuote::CDynaQuote(CSecurity *lpSec, CDynaQuote &Dyna)
{
	pSec = lpSec;
	Time = Dyna.Time;			// ��0�㿪ʼ�Ķ��ٺ���
	Open = Dyna.Open;			// ���̼ۣ���Ʒ��С��λ��������2λС����Open=1234�ʹ���12.34
	High = Dyna.High;			// ��߼ۣ��洢����ͬ��
	Low = Dyna.Low;		    	// ��ͼۣ��洢����ͬ��
	Close = Dyna.Close;         // �����̼ۣ��洢����ͬ��
	New = Dyna.New;			    // ���¼ۣ��洢����ͬ��
	Volume = Dyna.Volume;
}

CDynaQuote::~CDynaQuote()
{
	MDepth.clear();
	pSec = NULL;
}

bool CDynaQuote::SetDepth(CDepth &Depth)
{
	DataMutex_MDepth.lock_shared();
	_Depth::iterator ite = MDepth.find(Depth.Grade);
	if (ite != MDepth.end())
	{
		ite->second -> DataMutex_CDepth.lock();
		*ite->second = Depth;      // ����CDepth��
		ite->second->DataMutex_CDepth.unlock();
	}
	else
	{
		DataMutex_MDepth.lock_upgrade();
		PtrDepth NewDepth(new CDepth(this, Depth)); // �½�CDepth��
		MDepth[NewDepth->Grade] = NewDepth;         // ����CDepth��MAP����
		DataMutex_MDepth.unlock_upgrade();
	}
	DataMutex_MDepth.unlock_shared();
	return true;
}

bool CDynaQuote::GetDepth(int iGrade, CDepth &Depth)
{
	DataMutex_MDepth.lock_shared();
	_Depth::iterator ite = MDepth.find(iGrade);
	if (ite == MDepth.end())
	{
		DataMutex_MDepth.unlock_shared();
		return false;
	}
	
	ite->second->DataMutex_CDepth.lock_shared();
	Depth = *ite->second;
	ite->second->DataMutex_CDepth.unlock_shared();
	DataMutex_MDepth.unlock_shared();
	return true;
}

