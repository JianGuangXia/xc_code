// Setting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FastTradeSetting.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CFastTradeSetting, CDialogEx)

CFastTradeSetting::CFastTradeSetting(CWnd* pParent /*=NULL*/, CTradeConfig* pCTradeConfigtmp)
	: CDialogEx(IDD_FastTradeSetting, pParent), Vector_DefaultGear({ "��ͣ��","��ͣ��","��һ��","�����","������","���ļ�","�����",
	"��һ��","������","������","���ļ�","�����" })
{
	pCTradeConfig = pCTradeConfigtmp;
	s_ConfigPath = "..\\share\\config.xml";
}

CFastTradeSetting::~CFastTradeSetting()
{
}

void CFastTradeSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BuyDefaultGear, CComboBox_BuyDefaultGear);
	DDX_Control(pDX, IDC_SellDefaultGear, CComboBox_SellDefaultGear);
}


BEGIN_MESSAGE_MAP(CFastTradeSetting, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_bRandom, &CFastTradeSetting::OnBnClickedbRandom)
	ON_EN_CHANGE(IDC_Order_Minimum, &CFastTradeSetting::OnChangeOrderMinimum)
	ON_EN_CHANGE(IDC_Order_Maximum, &CFastTradeSetting::OnChangeOrderMaximum)
	ON_EN_CHANGE(IDC_BaseQuantity, &CFastTradeSetting::OnEnChangeBaseQuantity)
END_MESSAGE_MAP()


// CFastTradeSetting ��Ϣ�������

void CFastTradeSetting::fillCComboBox_BuyDefaultGear()
{
	CString s_tmp = pCTradeConfig->BuyDefalutGear;
	CComboBox_BuyDefaultGear.SetCurSel(CComboBox_BuyDefaultGear.InsertString(0,s_tmp));
	int i = 1;
	for (auto iter = Vector_DefaultGear.begin(); iter != Vector_DefaultGear.end(); iter++)
	{
		if (s_tmp.Compare(*iter) != 0)
		{
			CComboBox_BuyDefaultGear.InsertString(i,*iter);
			i++;
		}
	}
}

void CFastTradeSetting::fillCComboBox_SellDefaultGear()
{
	CString s_tmp = pCTradeConfig->SellDefalutGear;
	CComboBox_SellDefaultGear.SetCurSel(CComboBox_SellDefaultGear.InsertString(0, s_tmp));
	int i = 1;
	for (auto iter = Vector_DefaultGear.begin(); iter != Vector_DefaultGear.end(); iter++)
	{
		if (s_tmp.Compare(*iter) != 0)
		{
			CComboBox_SellDefaultGear.InsertString(i, *iter);
			i++;
		}
	}
}

void CFastTradeSetting::initFastTradeSettingLayout()
{
	fillCComboBox_BuyDefaultGear();
	fillCComboBox_SellDefaultGear();
	
	CString s_tmp;
	tool::SetEdit_Int(this->m_hWnd, (int)pCTradeConfig->DefaultBalance, IDC_DefaultBalance);
	tool::SetEdit_Int(this->m_hWnd, pCTradeConfig->DefaultAmount, IDC_DefaultAmount);

	tool::SetCheckBox(this->m_hWnd, pCTradeConfig->bTradePopover, IDC_TradePopover);
	tool::SetCheckBox(this->m_hWnd, pCTradeConfig->bEntrustQueue, IDC_bEntrustQueue);
	tool::SetCheckBox(this->m_hWnd, pCTradeConfig->bEntrustEach, IDC_bEntrustEach);

	if (true == pCTradeConfig->bCalculateByBalance)
	{
		((CButton*)GetDlgItem(IDC_bBalance) )->SetCheck(1);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_bAmount))->SetCheck(1);
	}

	/*��Ʊ�ֲ� ���� ����� �ֲ�ʱ��ʾ*/
	tool::SetCheckBox(this->m_hWnd, pCTradeConfig->bDismantling, IDC_bDismantling);
	tool::SetCheckBox(this->m_hWnd, pCTradeConfig->bRandom, IDC_bRandom);
	DealClickbRandom(this->m_hWnd, IDC_bRandom, IDC_Order_Minimum, IDC_Order_Maximum);
	tool::SetEdit_Int(this->m_hWnd, pCTradeConfig->BaseQuantity,IDC_BaseQuantity);


	tool::SetEdit_Int(this->m_hWnd, pCTradeConfig->Order_Minimum, IDC_Order_Minimum);
	tool::SetEdit_Int(this->m_hWnd, pCTradeConfig->Order_Maximum, IDC_Order_Maximum);
}

BOOL CFastTradeSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	initFastTradeSettingLayout();
	((CEdit *)GetDlgItem(IDC_BaseQuantity))->SetLimitText(MaxBaseQuantity);//����������λ�� ������󲻿ɳ���100 0000
	((CEdit *)GetDlgItem(IDC_Order_Minimum))->SetLimitText(Len_SingleOrderNum); //������󲻿ɳ���100 0000
	((CEdit *)GetDlgItem(IDC_Order_Maximum))->SetLimitText(Len_SingleOrderNum);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

bool CFastTradeSetting::SaveFastTradeSettingNeed()
{
	/*���ǵ���δ򿪣���˲���Ҫ���������ļ�������Ҫ�����ڴ�ṹ��*/
	string s_bCalculateByBalance;
	switch (GetCheckedRadioButton(IDC_bBalance, IDC_bAmount))
	{
	case IDC_bBalance:
		pCTradeConfig->bCalculateByBalance = 1;
		s_bCalculateByBalance = "1";
		break;
	case IDC_bAmount:
		pCTradeConfig->bCalculateByBalance = 0;
		s_bCalculateByBalance = "0";
		break;
	default:
		break;
	}
	
	ptree pt;
	try {
		read_xml(s_ConfigPath, pt, xml_parser::trim_whitespace);
		SaveCComboBox(CComboBox_BuyDefaultGear, pCTradeConfig->BuyDefalutGear, pt, "content.FastTradeSetting.��Ĭ�ϵ�λ");
		SaveCComboBox(CComboBox_SellDefaultGear, pCTradeConfig->SellDefalutGear, pt, "content.FastTradeSetting.��Ĭ�ϵ�λ");
		SaveCEdit(this->m_hWnd, IDC_DefaultBalance, pCTradeConfig->DefaultBalance, pt, "content.FastTradeSetting.Ĭ�Ͻ��");
		SaveCEdit(this->m_hWnd,IDC_DefaultAmount, pCTradeConfig->DefaultAmount, pt, "content.FastTradeSetting.Ĭ������");

		SaveCheckBox(this->m_hWnd,IDC_TradePopover, pCTradeConfig->bTradePopover, pt, "content.FastTradeSetting.bTradePopover");
		SaveCheckBox(this->m_hWnd, IDC_bEntrustQueue, pCTradeConfig->bEntrustQueue, pt, "content.FastTradeSetting.bEntrustQueue");
		SaveCheckBox(this->m_hWnd, IDC_bEntrustEach, pCTradeConfig->bEntrustEach, pt, "content.FastTradeSetting.bEntrustEach");

		pt.put("content.FastTradeSetting.bCalculateByBalance", s_bCalculateByBalance);

		SaveCheckBox(this->m_hWnd, IDC_bDismantling, pCTradeConfig->bDismantling, pt, "content.FastTradeSetting.bDismantling");
		SaveCEdit(this->m_hWnd, IDC_BaseQuantity, pCTradeConfig->BaseQuantity,pt, "content.FastTradeSetting.BaseQuantity");
		SaveCheckBox(this->m_hWnd, IDC_bRandom, pCTradeConfig->bRandom, pt, "content.FastTradeSetting.bRandom");

		SaveCEdit(this->m_hWnd, IDC_Order_Minimum, pCTradeConfig->Order_Minimum, pt, "content.FastTradeSetting.Order_Minimum");
		SaveCEdit(this->m_hWnd, IDC_Order_Maximum, pCTradeConfig->Order_Maximum, pt, "content.FastTradeSetting.Order_Maximum");

		xml_writer_settings<string> settings('\t', 1, "GB2312");
		write_xml(s_ConfigPath, pt, std::locale(), settings);
	}
	catch (std::exception& e)
	{
		LOG(ERROR) << "Error:" << e.what();
		ExceptionInterrupt;
		return false;
	}

	return true;
}

void CFastTradeSetting::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
    if (SaveFastTradeSettingNeed() == false)
    {
		LOG(ERROR) << "SaveFastTradeSettingNeed fail";
		ExceptionInterrupt;
    }
	::SendMessage(pCTradeConfig->hwnd_TradeDlg,WM_RedrawTrade, 0, 0);
	CDialogEx::OnOK();
}


void CFastTradeSetting::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	CDialogEx::OnCancel();
}

/*OnClose�����Ի����OnCancel*/
void CFastTradeSetting::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnClose();
}


void CFastTradeSetting::OnBnClickedbRandom()
{
	// TODO: Add your control notification handler code here
	DealClickbRandom(this->m_hWnd,IDC_bRandom,IDC_Order_Minimum,IDC_Order_Maximum);
}


void CFastTradeSetting::OnChangeOrderMinimum()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the __super::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CControlFun::OnlyPositiveInteger(this->m_hWnd, IDC_Order_Minimum);
}


void CFastTradeSetting::OnChangeOrderMaximum()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the __super::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CControlFun::OnlyPositiveInteger(this->m_hWnd, IDC_Order_Maximum);
}


void CFastTradeSetting::OnEnChangeBaseQuantity()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the __super::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CControlFun::OnlyPositiveInteger(this->m_hWnd, IDC_BaseQuantity);
}