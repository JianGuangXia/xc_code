#pragma once


// CTest �Ի���

class CTest : public CDialogEx
{
	DECLARE_DYNAMIC(CTest)

public:
	CTest(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTest();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGQQQ };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
