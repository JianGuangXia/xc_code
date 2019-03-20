#pragma once

#include "SimpleDockPane.h"
#include "../tool/MyCtrl/BaseView.h"
#include "GridCtrlEx.h"
#include "CreditTradeMainView.h"

// CDanBaoQuanView


class CDanBaoQuanView : public CBaseView
{
	DECLARE_DYNAMIC(CDanBaoQuanView)

	enum
	{
		IDC_START = 0x1001,

		IDC_Grid_BiaoDiQuan,
		IDC_Edit_StockCode

	};

public:
	CDanBaoQuanView(CDockListener &listener);
	virtual ~CDanBaoQuanView();

	static CBaseView *CreateView(CDockListener &listener) { return new CDanBaoQuanView(listener); }
	virtual void ReleaseView();
	void InitGrid();
	void SetData();

private:
	void InitialWindow();
	void CreateControls();

protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	virtual BOOL GetDefaultRect(CRect &rect);
	virtual void PostNcDestroy();
	CString GetAssureStatus(char fin_status);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEditResturn(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()

private:
	//*********�ؼ�����********************************
	CGridCtrlEx m_gridDanBaoQuan;
	CSimpleEdit m_editStockCode;
	vector<tagColumn> vec_ViewCol
	{
		{ ColId_stockName, "��Ʊ����", 120, COLTYPE_FIX, FALSE }
		,{ COLID_stockCode, "��Ʊ����", 120, COLTYPE_FIX, FALSE }
		,{ ColId_AssureRatio, "����������", 120, COLTYPE_FIX, FALSE }
		,{ ColId_AssureStatus, "����״̬", 120, COLTYPE_FIX, FALSE }
	};
};


