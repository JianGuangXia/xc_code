#pragma once

#include "SimpleDockPane.h"
#include "../MyCtrl/BaseView.h"
#include "GridCtrlEx.h"

class CBaseView_DealSummary : public CBaseView
{
	DECLARE_DYNAMIC(CBaseView_DealSummary)

	enum
	{
		IDC_START = 0x1001,

		IDC_Grid_DealSummary,
		IDC_Button_Refresh
	};

public:
	CBaseView_DealSummary(CDockListener &listener, CTradeDlg *pCTradeDlg_tmp);

	virtual ~CBaseView_DealSummary();
	virtual void ReleaseView();
public:
	void InitialWindow();
	void CreateControls();
	void InitGrid();
	//��ȡÿһ�����ӵ�����
	void GetVirtualCellInfo(GV_DISPINFO & dispinfo, const CDealSummary& dealSummary);
	afx_msg void OnBtnRefresh(NMHDR *pNmhdr, LRESULT *pResult);

	
protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	virtual BOOL GetDefaultRect(CRect &rect);


protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	DECLARE_MESSAGE_MAP()

public:
	//*********�ؼ�����********************************
	CGridCtrlEx m_gridDealSummary;
	CSimpleButton m_btnRefresh;
	
};


