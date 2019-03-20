
// JG.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "JG.h"
// #include "MainPageDlg.h"
//#include "MyCOccManager.h"
#include "../tool/MyCtrl/MyCOccManager.h"

// CJGApp

BEGIN_MESSAGE_MAP(CJGApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CJGApp ����

CJGApp::CJGApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CJGApp ����

CJGApp theApp;
MyCOccManager obj_MyCOccManager;



int GenerateMiniDump(PEXCEPTION_POINTERS pExceptionPointers)
{
	// ���庯��ָ��
	typedef BOOL(WINAPI * MiniDumpWriteDumpT)(
		HANDLE,
		DWORD,
		HANDLE,
		MINIDUMP_TYPE,
		PMINIDUMP_EXCEPTION_INFORMATION,
		PMINIDUMP_USER_STREAM_INFORMATION,
		PMINIDUMP_CALLBACK_INFORMATION
		);
	// �� "DbgHelp.dll" ���л�ȡ "MiniDumpWriteDump" ����
	MiniDumpWriteDumpT pfnMiniDumpWriteDump = NULL;
	HMODULE hDbgHelp = LoadLibrary(_T("DbgHelp.dll"));
	if (NULL == hDbgHelp)
	{
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	pfnMiniDumpWriteDump = (MiniDumpWriteDumpT)GetProcAddress(hDbgHelp, "MiniDumpWriteDump");

	if (NULL == pfnMiniDumpWriteDump)
	{
		FreeLibrary(hDbgHelp);
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	// ���� dmp �ļ���
	char szFileName[MAX_PATH] = { 0 };
	char* szVersion = _T("Dump");
	SYSTEMTIME stLocalTime;
	GetLocalTime(&stLocalTime);
	sprintf(szFileName, "%s-%04d%02d%02d-%02d%02d%02d.dmp",
		szVersion, stLocalTime.wYear, stLocalTime.wMonth, stLocalTime.wDay,
		stLocalTime.wHour, stLocalTime.wMinute, stLocalTime.wSecond);
	HANDLE hDumpFile = CreateFile(szFileName, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_WRITE | FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0);
	if (INVALID_HANDLE_VALUE == hDumpFile)
	{
		FreeLibrary(hDbgHelp);
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	// д�� dmp �ļ�
	MINIDUMP_EXCEPTION_INFORMATION expParam;
	expParam.ThreadId = GetCurrentThreadId();
	expParam.ExceptionPointers = pExceptionPointers;
	expParam.ClientPointers = FALSE;
	pfnMiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
		hDumpFile, MiniDumpWithDataSegs, (pExceptionPointers ? &expParam : NULL), NULL, NULL);
	// �ͷ��ļ�
	CloseHandle(hDumpFile);
	FreeLibrary(hDbgHelp);
	return EXCEPTION_EXECUTE_HANDLER;
}


LONG WINAPI ExceptionFilter(LPEXCEPTION_POINTERS lpExceptionInfo)
{
	if (IsDebuggerPresent())
	{
		return EXCEPTION_CONTINUE_SEARCH;
	}
	return GenerateMiniDump(lpExceptionInfo);
}


// CJGApp ��ʼ��
BOOL CJGApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
#ifndef _DEBUG
	SetUnhandledExceptionFilter(ExceptionFilter);
#endif
	CWinApp::InitInstance();

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		//AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	
	AfxEnableControlContainer(&obj_MyCOccManager);
	//AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	//CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	//CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//CJGDlg dlg;
	if (IsAlreadyRunning() == FALSE)
	{
		return FALSE;
	}

	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// ���������ؿ�ܼ�����Դ
	pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL, NULL);

	if (!HandleLogin(pFrame))
	{
		return FALSE;
	}
	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	pFrame->ShowWindow(SW_SHOWMAXIMIZED);
	//pFrame->ShowWindow(SW_SHOWNORMAL);
	pFrame->UpdateWindow();
	HandleNotice(pFrame);

	return TRUE;
}

void CJGApp::HandleNotice(CMainFrame* pFrame)
{
	try
	{
		ptree pt;
		string s_ConfigPath("..\\share\\config.xml");
		read_xml(s_ConfigPath, pt);

		CString strCurNoticeNO = pt.get<string>("content.CurNoticeNO").c_str();
		CString strNewNoticeNO = pt.get<string>("content.NewNoticeNO").c_str();
		bool bConnectState = pt.get<bool>("content.ConnectUpdateServerState");

		if (strCurNoticeNO.Trim() != strNewNoticeNO.Trim() && bConnectState)
		{
			MessageBox(pFrame->GetSafeHwnd(), GetNotice(), "����", MB_OK);
			pt.put("content.CurNoticeNO", strNewNoticeNO);
			xml_writer_settings<string> settings('\t', 1, "GB2312");
			write_xml(s_ConfigPath, pt, std::locale(), settings);
		}	
	}
	catch (std::exception& e)
	{
		LOG(ERROR) << "Error:" << e.what();
		ExceptionInterrupt;
	}

}

CString CJGApp::GetNotice()
{
	CString strNoticeFinal;
	try
	{
		ptree pt;
		read_xml("..\\share\\config.xml", pt);

		CString strNotice = pt.get<string>("content.Notice").c_str();

		int nIndex = 0;
		while ((nIndex = strNotice.Find("$$$")) >= 0)
		{
			CString strNoticeNo = strNotice.Mid(0, nIndex);
			strNotice.Delete(0, nIndex + 3);

			nIndex = strNotice.Find("@@@");
			if (nIndex >= 0)
			{
				CString strNoticeContent = strNotice.Mid(0, nIndex);
				strNotice.Delete(0, nIndex + 3);
				strNoticeFinal += (strNoticeNo + "\r\n" + strNoticeContent + "\r\n\r\n");
// 				CString str;
// 				str.Format("%s\r\n%s\r\n\r\n", strNoticeNo, strNoticeContent);
//				strNoticeFinal += str;
			}
		}


	}
	catch (std::exception& e)
	{
		LOG(ERROR) << "Error:" << e.what();
		ExceptionInterrupt;
		return "";
	}
	return strNoticeFinal;
}


//LONG WINAPI CJGApp::ExceptionFilter(LPEXCEPTION_POINTERS lpExceptionInfo)
//{
//	// ������һЩ�쳣�Ĺ��˻���ʾ
//	
//}

BOOL CJGApp::IsAlreadyRunning()
{
	char exeFullPath[MAX_PATH] = { 0 }; // MAX_PATH��API���ж���
	int len = GetModuleFileNameA(NULL,
		exeFullPath, //Ӧ�ó����ȫ·����ŵ�ַ
		MAX_PATH);
	string s_str = tool::deleteBackSlash(string(exeFullPath));
	Event_Exe = CreateMutex(NULL, FALSE, s_str.c_str());
	if (GetLastError() == ERROR_ALREADY_EXISTS || ERROR_ACCESS_DENIED == GetLastError())
	{
		LOG(ERROR) << "�����Ѿ������������ظ����У�";
		MessageBox(NULL, "�����Ѿ������������ظ����У�", "��ʾ��Ϣ", MB_ICONWARNING | MB_OK);
		CloseHandle(Event_Exe);
		Event_Exe = NULL;
		return FALSE;
	}
	return TRUE;
}

int CJGApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);
	return CWinApp::ExitInstance();
}

void CJGApp::InitModuleDLLInfo(MapModuleInfo& mapModule, VecModuleName& vecModule, CSharedByALLCData* pSharedByALLCData)
{
	try
	{
		string strExePath;
		tool::initExePath(strExePath);

		ptree pt;
		read_xml(ConfigPath, pt);
		BOOST_AUTO(child_User, pt.get_child("content.ModuleDLLInfo"));
		for (BOOST_AUTO(pos, child_User.begin()); pos != child_User.end(); ++pos)
		{
			CModuleDLLInfo dllInfo;
			dllInfo.bEnable = pos->second.get<bool>("Enable");
			if (dllInfo.bEnable)
			{
				dllInfo.strDllName = pos->second.get<string>("DllName");
				vecModule.push_back(pos->second.get<string>("Des"));

				string strDllPath = strExePath + "\\" + dllInfo.strDllName;
				HINSTANCE hInstance = LoadLibrary(strDllPath.c_str());
				if (hInstance != NULL)
				{
					dllInfo.hInstance = hInstance;
					dllInfo.pShowDlg = (ShowDlg*)GetProcAddress(hInstance, "dll_ShowDlg");
					dllInfo.pHideDlg = (HideDlg*)GetProcAddress(hInstance, "dll_HideDlg");
					dllInfo.pLogin = (Login*)GetProcAddress(hInstance, "dll_Login");
					dllInfo.strDes = pos->second.get<string>("Des");
					dllInfo.SPtr_CData = make_shared<CData>();
					if (pSharedByALLCData)
					{
						dllInfo.SPtr_CData->bRun_MainPageDlg = pSharedByALLCData->bRun_MainPageDlg;
						dllInfo.SPtr_CData->hwnd_MainPageDlg = pSharedByALLCData->hwnd_MainPageDlg;
						dllInfo.SPtr_CData->TestSpeed = pSharedByALLCData->TestSpeed;
					}

					mapModule.insert(make_pair(dllInfo.strDes, dllInfo));
				}
				else
				{
					FreeLibrary(hInstance);
				}
			}
		}
	}
	catch (std::exception& e)
	{
		LOG(ERROR) << "Error:" << e.what();
		ExceptionInterrupt;
	}
}

bool CJGApp::HandleLogin(CMainFrame* pFrame)
{
	if (!pFrame)
	{
		return false;
	}
	CSharedByALLCData* pSharedByALLCData = pFrame->GetSharedByALLCData();
// 	VecModuleName vecModuleName;
// 	InitModuleDLLInfo(m_mapModuleDLLInfo, vecModuleName, pSharedByALLCData);

	CLoginDlg loginDlg(&m_mapModuleDLLInfo, nullptr, pSharedByALLCData, true);
	if (loginDlg.DoModal() == -1)
	{
		LOG(ERROR) << "DoModal:" << GetLastError() << endl;
		ExceptionInterrupt;
		return false;
	}
	if (!loginDlg.LoginedDllName.empty())
	{
		pFrame->m_wndView.SetModuleDLLInfo(&m_mapModuleDLLInfo, loginDlg.LoginedDllName);
		pFrame->m_wndView.showSpecificDlg(loginDlg.LoginedDllName);
	}
	else
	{
		return false;
	}
	return true;
}
