#pragma once

#include "SimpleDockPane.h"
#include "../tool/MyCtrl/BaseView.h"
#include "GridCtrlEx.h"
#include "FastTradeMainView.h"
// CFundView


class CFundView : public CBaseView
{
	DECLARE_DYNAMIC(CFundView)

	enum
	{
		IDC_START = 0x1001,

		IDC_LISTBOX_FUND,
		IDC_GRID_FUNDVIEW,
		IDC_Button_Refresh

	};

public:
	CFundView(CDockListener &listener);
	virtual ~CFundView();

	static CBaseView *CreateView(CDockListener &listener) { return new CFundView(listener); }
	virtual void ReleaseView();
	void InitGrid();
	void SetGridData(CFund& fund);
	void SetData();

private:
	void InitialWindow();
	void CreateControls();

protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	virtual BOOL GetDefaultRect(CRect &rect);
	virtual void PostNcDestroy();
	bool UpdateQueryFund_Fast();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBtnRefresh(NMHDR *pNmhdr, LRESULT *pResult);


	DECLARE_MESSAGE_MAP()

private:
	//*********�ؼ�����********************************
	CGridCtrlEx m_gridFund;
	CSimpleButton m_btnRefresh;
	vector<tagColumn> vec_ViewCol
	{
		{ ColId_MoneyType, "��������", 80, COLTYPE_FIX }
		,{ ColId_AssetBalance, "�ʲ�ֵ", 120, COLTYPE_FIX, TRUE }
		,{ ColId_MarketValue, "֤ȯ��ֵ", 120, COLTYPE_FIX, TRUE }
		,{ ColId_CurrentBalance, "��ǰ���", 120, COLTYPE_FIX, TRUE }
		,{ ColId_EnableBalance, "�����ʽ�", 120, COLTYPE_FIX, TRUE }
		,{ ColId_FetchBalance, "��ȡ���", 120, COLTYPE_FIX, TRUE }
		,{ ColId_RealBuyBalance, "�ر�������", 120, COLTYPE_FIX, TRUE }
		,{ ColId_RealSellBalance, "�ر��������", 120, COLTYPE_FIX, TRUE }
	};
};


