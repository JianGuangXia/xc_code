// CreditTrade.h : CreditTrade DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCreditTradeApp
// �йش���ʵ�ֵ���Ϣ������� CreditTrade.cpp
//

class CCreditTradeApp : public CWinApp
{
public:
	CCreditTradeApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CCreditTradeApp theApp;
