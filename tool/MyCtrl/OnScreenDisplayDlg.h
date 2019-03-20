#pragma once

#include "OnScreenDisplayBDlg.h"
#include "../../FastTrade/Resource.h"

// COnScreenDisplayDlg �Ի���

class COnScreenDisplayDlg : public COnScreenDisplayBDlg
{
	DECLARE_DYNAMIC(COnScreenDisplayDlg)

	enum
	{
		IDC_MYTIMERID = 1000, // ��Ϣ��ʾ�� timer id
		IDC_LAB_TIPWORD,
	};

public:
	COnScreenDisplayDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COnScreenDisplayDlg(); 

// �Ի�������
	enum { IDD = IDD_ONSCREENDISPLAYDLG }; 

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	CString m_strTip;	// ��ʾ��Ϣ
	CStatic m_lbTip;	// ��ʾ��ʾ�Ŀؼ�
	CFont m_tipFont;
	int m_nElapseMs;
	COLORREF m_tipColor;

private:
	void ResizeWindow(CString strTip);
	void AdjustWindow();

public:
	/*
	OSD��ʾ��
	@strTip: ��ʾ��Ϣ
	@pParent: ��ʾ����ʾ�ľ��д���
	@nElapseMs: ��ʾ����ӳ�ʱ��(����)
	@tipColor: ��ʾ����ʾ��ɫ(����������ɫΪ RGB(0,255,0))
	*/
	void TipWord(CString strTip, CWnd* pParent = GetDesktopWindow(), int nElapseMs = 1000, COLORREF tipColor = RGB(255, 0, 0));

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
};
