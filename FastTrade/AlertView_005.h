#pragma once

#include "SimpleDockPane.h"
#include "../tool/MyCtrl/BaseView.h"
#include "SimpleCheckBox.h"
#include "GridCtrlEx.h"
#include "SimpleButton.h"
#include "AlertSetting_Fast.h"
#include "FastTradeMainView.h"

// CAlertView
class CAlertView : public CBaseView
{
	DECLARE_DYNAMIC(CAlertView)

	enum
	{
		IDC_START = 0x1001,

		IDC_CHEC_NOTRADE,
		IDC_LISTBOX_ORDER,
		IDC_Grid_AlertView,
		IDC_Check_Refresh,
		IDC_Button_Setting,
		IDC_Check_RightMouseOrder,
		IDC_Check_AutoScroll,

	};

public:
	CAlertView(CDockListener &listener);
	virtual ~CAlertView();

	static CBaseView *CreateView(CDockListener &listener) { return new CAlertView(listener); }
	virtual void ReleaseView();
	virtual void PostNcDestroy();
	CGridCtrlEx* GetGrid_T();
	void ClearGrid();

private:
	void InitialWindow();/*fix ������ȫ����*/
	void CreateControls();
	void InitGrid();

protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL GetDefaultRect(CRect &rect);
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnGridLMouseDown(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBtnRange(UINT nID, NMHDR *pNmhdr, LRESULT *pResult);
	afx_msg void OnGridRMouseDown(NMHDR *pNmhdr, LRESULT *pResult);
	bool RemoveOrder(const UInt_64 entrust_no, const string &exchange_type);
	bool GainRevoke333017(string &s_str, const UInt_64 entrust_no, const string &exchange_type);
	//���ص�
	static BOOL CALLBACK GridCallback(GV_DISPINFO *pDispInfo, LPARAM lParam);
    //��ȡÿһ�����ӵ�����
	void GetVirtualCellInfo(GV_DISPINFO & dispinfo, const CAlertNeed& alertNeed);
	COLORREF GetClor(UINT nID);
	BOOL GetOrderNoCheck(UInt_64 entrust_no);
	void dealSendBuyEntrust_Directly(const CString &stock_code, const CString &MarketCode);
	bool GainBuy333002(string &s_str, const CString stock_code, const double &entrust_price, UInt_64 &entrust_amount);

	DECLARE_MESSAGE_MAP()

private:
	map<CString, BOOL> m_mapCheckInfo;//CStringΪί�к�
	CAlertSetting_Fast* m_pCAlertSetting;
	COLORREF m_clr;

private:
	CSimpleCheckbox m_chcRefresh;
	CSimpleButton CSimpleButton_TradeSetting;
	CSimpleCheckbox m_chcRightMouseOrder;
	CSimpleCheckbox m_chcAutoScroll;

	CGridCtrlEx m_gridAlert;
	vector<tagColumn> vec_ViewCol
	{
		{ ColId_stockName, "��Ʊ����", 120, COLTYPE_FIX, FALSE }
		,{ COLID_stockCode, "��Ʊ����", 120, COLTYPE_FIX, FALSE }
		,{ ColId_RiseRate, "�ǵ���%", 120, COLTYPE_FIX, FALSE }
		,{ ColId_LastPrice, "���¼�", 120, COLTYPE_FIX, FALSE }
		,{ ColId_AppearPrice, "�����۸�", 120, COLTYPE_FIX, FALSE }
		,{ ColId_AppearTime, "����ʱ��", 120, COLTYPE_FIX, FALSE }
	};

};


