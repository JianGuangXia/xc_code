// FastTrade.h : FastTrade DLL ����ͷ�ļ�
//

#pragma once


#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include <afxwin.h>
#include "OnScreenDisplayDlg.h"

// CFastTradeApp
// �йش���ʵ�ֵ���Ϣ������� FastTrade.cpp

class CFastTradeApp : public CWinApp
{
public:
	CFastTradeApp();

// ��д
public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};

extern CFastTradeApp theApp;
