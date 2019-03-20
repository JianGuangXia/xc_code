
//*****************************************************
//********    SimpleButtonEdit By YaoShuLong 2018.6.13
//*****************************************************

#pragma once
#include "SimpleEdit.h"
#include "SimpleButton.h"

// CSimpleButtonEdit

////���ƴ�С�İ�ť��ʽ
typedef int ButtonStyle;
#define LeftRight  1
#define UpDown   2

////�Ӽ���
typedef int PlusMinus;
#define Plus       1
#define Minus    2

////��������
typedef int DataTypeBtnEdit;
#define TypeDouble       1
#define TypeInt    2

////�༭������λ��
typedef int TextPos;
#define TextLeft                 1
#define TextCenter              2
#define TextRight              3


#define Def_Height                      25

#define Def_BtnUpDownWidth     16
#define Def_BtnLeftRightWidth     25

#define Def_BtnUpHeight              13
#define Def_BtnDownHeight         12

#define Def_EditWidth         66
#define Def_Gap                  4

#define DBL_MAX_EDIT_BUTTON         1.7976931348623158e+308 /* max value */


#define SimpleButtonEdit_CLASSNAME    _T("CSimpleButtonEdit")

class CSimpleButtonEdit : public CWnd
{
	DECLARE_DYNAMIC(CSimpleButtonEdit)

    enum
    {
        IDC_START = 0x1001,

        IDC_BUTTONEDIT_UP,
        IDC_BUTTONEDIT_DOWN,

        IDC_BUTTONEDIT_LEFT,
        IDC_BUTTONEDIT_RIGHT,

        IDC_BUTTONEDIT_EDIT,

    };

public:
	CSimpleButtonEdit();
	virtual ~CSimpleButtonEdit();

	BOOL Create(DWORD dwStyle, const CRect& rect, CWnd * pParentWnd, UINT nID);

private:
    BOOL RegisterWindowClass();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnPaint();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButtonRange(UINT nID, NMHDR *pNmhdr, LRESULT *pResult);
	afx_msg void OnEnChangeEdit();

protected:
	DECLARE_MESSAGE_MAP()

private:
	CSimpleButton m_btnUp;
	CSimpleButton m_btnDown;

    CSimpleEdit m_edit;

	CSimpleButton m_btnLeft;
	CSimpleButton m_btnRight;

private:
    COLORREF m_clrBk;
    ButtonStyle m_style;
    int m_nHeight;
	int m_nBtnLeftRightWidth;

    int m_nEditWidth;
    int m_nGap;

	double m_fTick;
	int m_nPrecision;

	DWORD m_dwStyle;

	BOOL m_bSetSel;
	BOOL m_bHotKey;	 //�˲����������ⲿ�Ŀ�ݼ��µ�������һ����������
	DataTypeBtnEdit m_dateType;
	BOOL m_IntValueControl;
	BOOL m_EnableMouseWheel;
	BOOL m_bEnableMixZero;

private:
	void DoPlusMinus(PlusMinus type, double fTick, int nPrecision);
	

	/* ���� : �� ˫�������� ת��Ϊ �ַ�������
	/* ������� : @dValue ��Ҫת����˫��������
	/*            @nSpot ��Ҫ������λ��(0 <= nSpot <= 3)
	/************************************************************************/
	CString TransDoubleToString(const double dValue, const int nSpot);

protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void InitSettings(CString strHint = _T(""), int nTextLimit = -1, HFONT hFont = NULL);
	void SetButtonStyle(ButtonStyle style);
	void SetTextPos(TextPos textPos = TextRight);
	void SetTextOffset(int nTextOffset);
	void SendMouseWheelMsg(PlusMinus type);

public:
	void SetBkColor(COLORREF clr);
	void SetEditBkColor(COLORREF clr);
	void SetTextColor(COLORREF clr);

	void EnableWindow(BOOL bEnable = TRUE);

	///���ÿؼ��ߴ�
	///@param nEditWidth  �༭����  
	///@param nBtnWidth  ����2����ť�Ŀ�ȣ��˲�����ButtonStyleΪLeftRightʱ�����ã���һ��ģʽʹ��Ĭ�ϲ���ֵ  
	///@param nHeight      �����ؼ��ĸ߶ȣ��˲�����ButtonStyleΪLeftRightʱ�����ã���һ��ģʽʹ��Ĭ�ϲ���ֵ 
	///@param nGap         ���ð�ť���༭��֮��ľ��룬�˲�����ButtonStyleΪLeftRightʱ�����ã���һ��ģʽʹ��Ĭ�ϲ���ֵ 
	void SetSize(int nEditWidth, int nBtnWidth = 0, int nHeight = Def_Height, int nGap = 0);

    ////��ȡ�����ؼ��Ŀ�Ⱥ͸߶ȣ��˷������ڵ��� SetSize����֮��ʹ��
    void GetWidthAndHeight(int& nWidth, int& nHeight);
    
	void SetTick(double tick);
	void SetPrecision(int precision);

	void SetFocus();
	BOOL IsWindowEnabled();
	HWND GetFocusHwnd();
	void EnableSetSel(BOOL bEnable = TRUE);
	void SetDateType(DataTypeBtnEdit dataType);

	void InitSettings(ButtonStyle style, DataTypeBtnEdit dataType, COLORREF clrText, HFONT hFont = NULL, TextPos textPos = TextRight, int nTextOffset = 0, CString strHint = _T(""), int nTextLimit = -1);

    void SetWindowText(CString str);
    void GetWindowText(CString& str);
	void EnableIntValueControl(BOOL bEnable);
	void EnableHotkey(BOOL bEnable);
	void SetValue(PlusMinus type);
	void EnableMouseWheel(BOOL bEnable);
	void EnableMixZero(BOOL bEnable);
};


