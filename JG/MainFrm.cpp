
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "JG.h"
#include "MainFrm.h"
#include "../share/define.h"
#include "Resource.h"
#include "../tool/TradeDlg.h"
#include "../tool/MyCtrl/FontSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_CLOSE()
	ON_WM_NCCALCSIZE()
	ON_MESSAGE(WM_SETDELLHWND, &CMainFrame::OnSetDellHwnd)
END_MESSAGE_MAP()

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	m_hMainIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMainFrame::~CMainFrame()
{
#ifdef _DEBUG
	fclose(stderr);
	::FreeConsole();
#endif
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// ����һ����ͼ��ռ�ÿ�ܵĹ�����
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("δ�ܴ�����ͼ����\n");
		return -1;
	}
	
	SetIcon(m_hMainIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hMainIcon, FALSE);		// ����Сͼ��
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	if (cs.hMenu != NULL)
	{
		::DestroyMenu(cs.hMenu);      // delete menu if loaded
		cs.hMenu = NULL;              // no menu for this window
	}

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// ������ǰ�Ƶ���ͼ����
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// ����ͼ��һ�γ��Ը�����
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// ����ִ��Ĭ�ϴ���
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnClose()
{	
	int nResult = MessageBox("ȷ���رճ���", "��ʾ", MB_ICONEXCLAMATION | MB_OKCANCEL);
	if (IDOK == nResult)
	{
		m_wndView.CloseWnd();
		CFrameWnd::OnClose();
	}
}

void CMainFrame::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	CFrameWnd::OnNcCalcSize(bCalcValidRects, lpncsp);
}


LRESULT CMainFrame::OnSetDellHwnd(WPARAM wParam, LPARAM lParam)
{
	HWND hWnd = (HWND)wParam;
	m_vecDllFrameHwnd.push_back(hWnd);
	return 0;
}

CSharedByALLCData* CMainFrame::GetSharedByALLCData()
{
	return &(m_wndView.m_sharedByALLCData);
}




