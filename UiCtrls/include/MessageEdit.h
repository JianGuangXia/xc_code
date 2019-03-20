#if !defined(AFX_MESSAGEEDIT_H__19625AA2_0AC7_4735_BAF5_BAA34BAB60B3__INCLUDED_)
#define AFX_MESSAGEEDIT_H__19625AA2_0AC7_4735_BAF5_BAA34BAB60B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MessageEdit.h : header file
//

#include "QdControlMsgID.h"

#define ME_IsSHIFTpressed() ( (GetKeyState(VK_SHIFT) & (1 << (sizeof(SHORT)*8-1))) != 0 )

/////////////////////////////////////////////////////////////////////////////
// CMessageEdit window
typedef struct
{
	char nChar; // �ͻ�������ַ�
	CString ViewStr;//�ͻ���ʾ������
}INPUT_MAP;

typedef struct
{
	CString InputStr; // �ͻ�������ַ���
	CString ViewStr;//�ͻ���ʾ������
}INPUT_STR_MAP;

class CMessageEdit : public CEdit
{
// Construction
public:
	CMessageEdit();
	int m_LastKey;
// Attributes
public:
	typedef struct 
	{
		int RowIndex;
		int ColIndex;
	} ATTACH_POSITION;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessageEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DeleteCharMap();
	void SetFastKey();
	void DeleteMap();
	void SetParentWnd(CWnd *pParent);
	void SetPriceInput(bool flag );
	void SetQtyInput(bool flag);
	void SetListSort(bool flag);
	void SetLimitCharInput(char cPress,CString str);
	void SetLimitStrInput(CString InputStr,CString str);
	void SetInputLength(int len = 100)
	{
		m_MaxLength = len;
	}
	
	//�Զ���0λ��
	void SetZeroLength(int len )
	{
		m_nZeroLength = len;
	}
	void SetAttachPosition(const ATTACH_POSITION &attachPosition);
	
	virtual ~CMessageEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMessageEdit)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChange();
	afx_msg void OnNcPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CString m_InputStr ;
	
	CList <INPUT_MAP *,INPUT_MAP *> m_MapList;
	CList <INPUT_STR_MAP *,INPUT_STR_MAP *> m_MapStrList;
	
	bool m_bCharMap;//�Ƿ��ǵ���map
	bool m_bPrice;//�Ƿ�����۸�
	int  m_MaxLength;//�������󳤶�
	bool m_bQtyInput;//�Ƿ���������
	bool m_bListSort;//�Ƿ��б�ɸѡ
	CWnd *m_ParentWnd;//������

	int m_nZeroLength;//�Զ���0�ĳ���

	ATTACH_POSITION m_attachPosition;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSAGEEDIT_H__19625AA2_0AC7_4735_BAF5_BAA34BAB60B3__INCLUDED_)
