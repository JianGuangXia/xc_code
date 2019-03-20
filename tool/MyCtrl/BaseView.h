#pragma once
#include "dockwindow.h"
#include "FontSet.h"
#include "ColorSet.h"
#include "SimpleButton.h"
#include "../../share/SharedPart_Dlls.h"
#include "../../tool/TradeDlg.h"
#include "SimpleDockPane.h"
#include "GridCtrlEx.h"
#include "../baseView/GridRes.h"

#define dwStyle_ComboBox WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST |WS_VSCROLL
#define dwStyle_Static WS_CHILD | WS_VISIBLE
#define dwStyle_Edit WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL
#define dwStyle_Checkbox WS_CHILD | BS_AUTOCHECKBOX | WS_VISIBLE
#define dwStyle_Radio BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP 
#define dwStyle_button WS_CHILD | WS_VISIBLE
#define length_Time 80

/*studying �¿����mfc dll�������⣬���þ�̬�����ԣ�������Ӧ����һ����,mfc dll �����Լ����.libʹ���������Ͽ��еİ�*/
class CBaseView : public CDockWindow
{
	DECLARE_DYNAMIC(CBaseView)
public:
	CBaseView(CDockListener &listener);
	virtual ~CBaseView(void);

	virtual void SaveSetInfo(CString &strSetInfo);
	virtual void LoadSetInfo(const CString &strSetInfo);
	void SetDock(bool bDock);
	bool GetIsDock();
	enum HOVER_BUTTON
	{
		HOVER_NULL,
		HOVER_MIN,
		HOVER_MAX,
		HOVER_CLOSE,
	};
public:
	void SetBackClr(COLORREF backClr);
	void SetBorderClr(COLORREF borderClr);
	void SetFocusBorderClr(COLORREF focusBorderClr);
	void SetTilteBackClr(COLORREF titleBackClr);
	void SetTilteFocusBackClr(COLORREF focusTitleBackClr);
	void SetTilteTextClr(COLORREF titleTextClr);
	void SetButtonClr(COLORREF buttonClr);
	void SetHoverButtonClr(COLORREF hoverButtonClr);
	void SetHoverButtonBackClr(COLORREF hoverButtonBackCrl);
	void SetTilteText(CString strTitleText);
	void SetBorderSize(int nBorder);
	void SetTitleHeight(int nTilteHeight);
private:
	COLORREF m_clBackClr;	//����ɫ
	COLORREF m_clBorderClr;	//�߿�ɫ
	COLORREF m_clFocusBoderClr;	//����߿�ɫ
	COLORREF m_clTilteBackClr;//���ⱳ��ɫ
	COLORREF m_clFocusTilteBackClr;//������ⱳ��ɫ
	COLORREF m_clTilteTextClr;//����������ɫ
	COLORREF m_clButtonClr;//��ť��ɫ
	COLORREF m_clHoverButtonClr;//��ťHover��ɫ
	COLORREF m_clHoverButtonBackClr;//��ťHover����ɫ
	int		 m_nBorder;		  //�߿���
	int		 m_nTitleHeight;  //����߶�
	HFONT	 m_hTitleFont;	  //��������
	CRect    m_rcClose;		  //�ر� 
	CRect    m_rcMin;		  //��С��
	CRect    m_rcMax;		  //���
	HOVER_BUTTON m_nHover;	  //����
	BOOL	 m_bShowMaxMinButton;//�Ƿ���ʾ�����С��
	BOOL     m_bActivate;//�����ж�
protected:
	virtual void InitCtrls(); //��ʼ���ؼ�
	virtual void Relayout(); //�ı�ؼ�λ��
	virtual void DrawBackGround(HDC hDC, const RECT rc);
private:
	void DrawBorder(CDC* pDC);
	virtual void OnShowMin();
	virtual void OnShowMax();
	virtual void OnShowRestore();
	DECLARE_MESSAGE_MAP()

protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClose();
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnNcMouseLeave();
	afx_msg LRESULT OnNcHitTest(CPoint point);


public:
	virtual void ReleaseView() = 0;

	void SetViewID(const UINT nID) { m_nViewID = nID; }
	UINT GetViewID() const { return m_nViewID; }

	virtual BOOL GetDefaultRect(CRect &rect) { return FALSE; }
	virtual void OnChangeLanguage() {}

public:
	BOOL m_bMultiWindow; // �Ƿ����ͬʱ�򿪶��
	BOOL m_bStaticWindow; // �ر�ʱ����

protected:
	UINT m_nViewID;

public:
	afx_msg void OnPaint();
};

