#include "stdafx.h"
#include "CMyListCtrl.h"
#include <iostream>
using namespace std;


CMyListCtrl::CMyListCtrl()
{
	hwnd_WarningPool = NULL;
}

CMyListCtrl::~CMyListCtrl()
{
}

BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


void CMyListCtrl::init_HwndWarningPool(HWND hwnd)
{
	hwnd_WarningPool = hwnd;
}

void CMyListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nSBCode)
	{
	case SB_ENDSCROLL:
		break;
	case SB_THUMBPOSITION:
	{
		itemIndex = nPos;
		::SendMessage(hwnd_WarningPool, WM_EndScrollWarningPool, 0, 0);
		break;
	}
	case SB_THUMBTRACK:
	{
		break;
	}
	default:
		break;
	}
	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}
