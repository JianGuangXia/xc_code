#pragma once

#include "SimpleDockPane.h"
#include "../share/MyCtrl/BaseView.h"
#include "GridCtrlEx.h"
#include "CreditTradeMainView.h"

// CDealEachView

class CDealEachView : public CBaseView
{
	DECLARE_DYNAMIC(CDealEachView)

	enum
	{
		IDC_START = 0x1001,

		IDC_Grid_OrderEach,
	};

public:
	CDealEachView(CDockListener &listener);
	virtual ~CDealEachView();

	static CBaseView *CreateView(CDockListener &listener) { return new CDealEachView(listener); }
	virtual void ReleaseView();
	virtual void PostNcDestroy();
	CGridCtrlEx* GetOrderEachGrid();

private:
	void InitialWindow();
	void CreateControls();
	void InitGrid();
	//����ص�
	static BOOL CALLBACK GridCallback(GV_DISPINFO *pDispInfo, LPARAM lParam);
	//��ȡÿһ�����ӵ�����
	void GetVirtualCellInfo(GV_DISPINFO & dispinfo, const CDeal& deal);
	

protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	virtual BOOL GetDefaultRect(CRect &rect);


protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

private:
	//*********�ؼ�����********************************
	CGridCtrlEx m_gridDealEach;

};

