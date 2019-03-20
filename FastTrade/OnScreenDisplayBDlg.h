#pragma once


// COnScreenDisplayBDlg �Ի���

class COnScreenDisplayBDlg : public CDialog
{
	DECLARE_DYNAMIC(COnScreenDisplayBDlg)

public:
	COnScreenDisplayBDlg(UINT nTemplateIDD, COLORREF clrTransparent = RGB(0, 255, 0), CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COnScreenDisplayBDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()

private:
	COLORREF m_clrTransparent;
	CBrush m_brush;

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
