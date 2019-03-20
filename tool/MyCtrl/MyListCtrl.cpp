#include "stdafx.h"
#include "MyListCtrl.h"
#include <iostream>
using namespace std;


CMyListCtrl::CMyListCtrl()
{
	hwnd_Alert = NULL;
}

CMyListCtrl::~CMyListCtrl()
{
}

BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


void CMyListCtrl::init_HwndAlert(HWND hwnd)
{
	hwnd_Alert = hwnd;
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
		::SendMessage(hwnd_Alert, WM_EndScrollAlert, 0, 0);
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

void CMyListCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CButton::OnPaint()
					   //  Calculate Frame rect  
	CRect rect;
	GetClientRect(rect);
	CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
	CPen* pOldPen = dc.SelectObject(&pen);
	const int padding = 2;
	dc.MoveTo(padding, padding);
	dc.LineTo(rect.Width() - padding, padding);
	dc.LineTo(rect.Width() - padding, rect.Height() - padding);
	dc.LineTo(padding, rect.Height() - padding);
	dc.LineTo(padding, padding);
	dc.SelectObject(pOldPen);
}
