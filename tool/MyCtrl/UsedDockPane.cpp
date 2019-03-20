#include "stdafx.h"
#include "UsedDockPane.h"

IMPLEMENT_DYNAMIC(CUsedDockPane, CSimpleDockPane)
CUsedDockPane::CUsedDockPane(void)
{
	m_nShowStyle = SW_SHOWNORMAL;
}

CUsedDockPane::~CUsedDockPane(void)
{
}

BEGIN_MESSAGE_MAP(CUsedDockPane, CSimpleDockPane)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

/*
bShow
ָ�������Ƿ���ʾ�� ���������ʾ������ TRUE ;��������������صģ����� FALSE��

nStatus
ָ����ʾ�Ĵ��ڵ�״̬�� ����0������������ں������õ� ShowWindow ��Ա;���� nStatus Ϊ����֮һ��

SW_PARENTCLOSING �������ǽ���(ʹͼ����ʽ)�򵯳��������ء�

SW_PARENTOPENING �����ڴ�(��ʾ)�򵯳�������ʾ��
*/
void CUsedDockPane::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CSimpleDockPane::OnShowWindow(bShow, nStatus);

	// TODO: �ڴ˴������Ϣ����������
	if (!bShow && nStatus != 0)
	{
		WINDOWPLACEMENT wp;
		::memset(&wp, 0, sizeof(WINDOWPLACEMENT));
		wp.length = sizeof(WINDOWPLACEMENT);
		::GetWindowPlacement(m_hWnd, &wp);
		m_nShowStyle = wp.showCmd;
	}
	else if(bShow && nStatus)
	{
		ShowWindow(m_nShowStyle);
	}
}
