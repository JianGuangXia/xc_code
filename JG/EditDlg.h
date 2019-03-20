#pragma once
#include "afxwin.h"


// CEditDlg �Ի���

struct CEditInfo
{
	CString strCaption;
	CString strNameTip;
	CString strName;
	CString strAddrTip;
	CString strAddr;
	CString strPort;

};

enum EditStyle
{
	EditAdd,
	EditModify,
	EditDelete,
};

class CEditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEditDlg)

public:
	CEditDlg(CEditInfo* pEditInfo, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEditDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_DIALOG_Edit
};
#endif

private:
	CEditInfo* m_pEditInfo;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	CStatic m_staName;
	CStatic m_staAddr;
	CEdit m_EditName;
	CEdit m_editAddr;
	CEdit m_editPort;

private:
	bool Check();

private:
	afx_msg void OnBnClickedButtonEditConfirm();
	afx_msg void OnBnClickedButtonEditCancel();
};
