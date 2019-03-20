#pragma once

// CWarningPoolSetting �Ի���

#include "resource.h"
#include "../tool/AlertSetting.h"

class CAlertSetting_Fast : public CDialogEx ,public CAlertSetting
{
	DECLARE_DYNAMIC(CAlertSetting_Fast)

public:
	CAlertSetting_Fast(CWnd* pParent,  PtrData SPtr_CDataTmp, CApiFun *pCApiFunTmp);   // ��׼���캯��
	virtual ~CAlertSetting_Fast();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AlertSetting };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	bool bRun_AlertSetting;

	bool initAlertSettingNeed();
	void initAlertSettingLayout();
	bool VerifyBeforeSave();
	bool SaveAlertSettingNeed();

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
    template<class in_type>
	bool GainLegalValue(in_type &Value, const int CtrID)
	{
		CString s_str;
		GetDlgItem(CtrID)->GetWindowText(s_str);
		if ("" == s_str || "0" == s_str)
		{
			Value = 0;//Ŀǰ����UInt_64��double
			return false;
		}
		Value = convert<in_type>(s_str);
		return true;
	}
	afx_msg void OnEnChangeIncreaseratio();
	virtual void OnCancel();
	afx_msg void OnIdclose();
	afx_msg void OnEnChangeIncreaseRatioNRise();
	afx_msg void OnEnChangeBeginRatioLowRise();
	afx_msg void OnEnChangeEndRatioLowRise();
	afx_msg void OnEnChangeMinuteNRise();
	afx_msg void OnEnChangeMinuteLowRise();
};
