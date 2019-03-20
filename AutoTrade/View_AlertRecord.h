#pragma once
#include "SimpleDockPane.h"
#include "../tool/MyCtrl/BaseView.h"
#include "SimpleCheckbox.h"
#include "SimpleEdit.h"
#include "SimpleStatic.h"
#include "SimpleButton.h"
#include "SimpleComboBox.h"
#include "SimpleRadioButton.h"
#include "ViewManager_auto.h"
#include "SimpleButtonEdit.h"
#include "SimpleTime.h"
#include "GridCtrlEx.h"
#include "MainView_AutoTrade.h"

class CView_AlertRecord : public CBaseView
{
	DECLARE_DYNAMIC(CView_AlertRecord)
public:
	CView_AlertRecord(CDockListener &listener);
	~CView_AlertRecord();
	static CBaseView *CreateView(CDockListener &listener) 
	{ 
		return new CView_AlertRecord(listener);
	}
	virtual void ReleaseView();
protected:
	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void InitialWindow();
	void CreateControls();
	bool initPreRecord();
	virtual BOOL GetDefaultRect(CRect &rect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void InitGrid();
	//���ص�
	static BOOL CALLBACK GridCallback(GV_DISPINFO *pDispInfo, LPARAM lParam);
	void SetCell(GV_DISPINFO & dispinfo, CAertRecord &obj_CAertRecord);
public:
	void SetAlertRecord();
private:
	enum
	{
		IDC_Start = 0x1001,
		//���ί�й���
		IDC_Grid_AlertRecord,

	};
	CGridCtrlEx CGridCtrlEx_alertRecord;
	CApiFun *pCApiFun;
	PtrData SPtr_CData;

	vector<tagColumn> vec_ViewCol
	{
		{ ColID_time, "����ʱ��", 90, COLTYPE_FIX, TRUE }
		,{ ColID_secCode, "��Ʊ����", 90, COLTYPE_FIX, TRUE }
		,{ ColID_secName, "��Ʊ����", 90, COLTYPE_FIX, TRUE }
		,{ ColID_triggerName, "����ԭ��", 300, COLTYPE_FIX, TRUE }
		,{ ColID_entrustNo, "ί�к�", 90, COLTYPE_FIX, TRUE }
		,{ ColID_entrustPrice, "ί�м۸�", 90, COLTYPE_FIX, TRUE }
		,{ ColID_entrustAmount, "ί������", 90, COLTYPE_FIX, TRUE }
		,{ ColID_note, "ע��", 150, COLTYPE_FIX, TRUE }
	};
};