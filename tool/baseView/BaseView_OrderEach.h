#pragma once

#include "../MyCtrl/BaseView.h"
// COrderEachView

class CBaseView_OrderEach : public CBaseView
{
	DECLARE_DYNAMIC(CBaseView_OrderEach)

	enum
	{
		IDC_START = 0x1001,

		IDC_Grid_OrderEach,
	};

public:
	CBaseView_OrderEach(CDockListener &listener, CTradeDlg *pCTradeDlg_tmp);
	virtual ~CBaseView_OrderEach();

	virtual void ReleaseView();
	CGridCtrlEx* GetGrid_T();
public:
	void InitialWindow();
	void CreateControls();
	void InitGrid();
	//��ȡÿһ�����ӵ�����
	void GetVirtualCellInfo(GV_DISPINFO & dispinfo, const CEntrustEach& entrustEach);


protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	virtual BOOL GetDefaultRect(CRect &rect);


protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

public:
	//*********�ؼ�����********************************
	CGridCtrlEx m_gridOrderEach;
};


