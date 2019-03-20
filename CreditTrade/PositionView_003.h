#pragma once

#include "SimpleDockPane.h"
#include "../share/MyCtrl/BaseView.h"
#include "GridCtrlEx.h"
#include "CreditTradeMainView.h"

// CPositionView
COLORREF GetClor(double balance);

class CPositionView : public CBaseView
{
	DECLARE_DYNAMIC(CPositionView)

	enum
	{
		IDC_START = 0x1001,

		IDC_LISTBOX_POSITION,
		IDC_GRID_POSITION,
		IDC_SubPosition
	};

public:
	CPositionView(CDockListener &listener);
	virtual ~CPositionView();

	static CBaseView *CreateView(CDockListener &listener) { return new CPositionView(listener); }
	virtual void ReleaseView();
	virtual void PostNcDestroy();
	CGridCtrlEx* GetGridPosition();

private:
	void InitialWindow();
	void CreateControls();
	void InitGrid();
	//���ص�
	static BOOL CALLBACK GridCallback(GV_DISPINFO *pDispInfo, LPARAM lParam);
	//�������ص�
	static bool CompareVirtual(int nCol, BOOL bAscending, LPARAM lParam);
	static void GetVirtualCellText(CString &strText, PtrPosition pPosition, const int nColID);//������ID ��ȡ����
	static BOOL CompareOrderData(PtrPosition pPosition1, PtrPosition pPosition2);  //ί����������
																	 //��ȡÿһ�����ӵ�����
	void GetVirtualCellInfo(GV_DISPINFO & dispinfo, const CPosition& position);
	//afx_msg void OnBtnSubPosition(NMHDR *pNmhdr, LRESULT *pResult);

private:
	static BOOL m_bAscending;//����������
	static int  m_nColID;	 //������ID

	

protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	virtual BOOL GetDefaultRect(CRect &rect);


protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGridPositionSelChange(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()

private:
	//*********�ؼ�����********************************
	CGridCtrlEx m_gridPosition;
	CSimpleButton m_btnSubPosition;

};


