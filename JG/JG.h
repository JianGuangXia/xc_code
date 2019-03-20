
// JG.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include <Windows.h>
#include "DbgHelp.h"
#include "../tool/tool.h"
//#include "..\share\through.h"
#include "LoginDlg.h"
#include "MainFrm.h"

// CJGApp: 
// �йش����ʵ�֣������ JG.cpp
//

class CJGApp : public CWinApp
{
public:
	CJGApp();

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
// ʵ��

	DECLARE_MESSAGE_MAP()

	HANDLE Event_Exe;
	BOOL IsAlreadyRunning();

private:
	void InitModuleDLLInfo(MapModuleInfo& mapModule, VecModuleName& vecModule, CSharedByALLCData* pSharedByALLCData);
	bool HandleLogin(CMainFrame* pFrame);
	CString GetNotice();
	void HandleNotice(CMainFrame* pFrame);

private:
	//���ص�ģ��DLL����Ϣ
	MapModuleInfo m_mapModuleDLLInfo;

};

extern CJGApp theApp;
