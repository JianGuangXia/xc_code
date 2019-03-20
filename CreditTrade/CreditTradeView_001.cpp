#include "stdafx.h"
#include "CreditTradeView_001.h"

#include "ViewManager_credit.h"
#include "../tool/MyCtrl/FontSet.h"
#include "OrderQueueView.h"
#include "OrderEachView.h"

//��Ʊ�������༭��֮��ľ���
#define  Gap1  30
//����������������ľ���
#define  Gap2  6
//����������������ı༭�����߾���
#define  Gap3  20
//����������������ı༭������¾���
#define  Gap4  13
//�ʼ����ߵľ���
#define  Gap5  12
//�����֮��
#define  Gap6  35


// CCreditTradeView

IMPLEMENT_DYNAMIC(CCreditTradeView, CBaseView)

CCreditTradeView::CCreditTradeView(CDockListener &listener)
: CBaseView(listener)
{
	m_bMultiWindow = false;
	m_bStaticWindow = true;
	bool bEnableDock = FALSE;
	EnableDock(true);

	m_nHeight = 0;
	m_nAssociatedWidth = 0;
	m_nWidth4Word = 0;
	m_nWidth2Word = 0;
	m_nEditHeight = 0;
	m_nEditWidth = 0;
	m_nWidthRadio1 = 0;
	m_nWidthRadio2 = 0;
	m_nButtonHeight = 0;
	m_nButtonGap = 0;
	m_nPriceWidth = 0;
	m_nGap1 = 0;
	m_nGap2 = 0;
	m_nGap3 = 0;
	m_nGap4 = 0;
	m_nGap5 = 0;
	m_nGap6 = 0;
}

CCreditTradeView::~CCreditTradeView()
{
}

//CBaseView* GetViewByID(UINT nID)
//{
//	CBaseView* pBaseView = nullptr;
//	set<CBaseView*>* pSetQuote;
//	pSetQuote = SingleViewManager.FindView(nID);
//	if (pSetQuote != nullptr)
//	{
//		set<CBaseView*> setQuote;
//		setQuote = *pSetQuote;
//		if (1 == setQuote.size())
//		{
//			pBaseView = *(setQuote.begin());
//		}
//	}
//	return pBaseView;
//}

void CCreditTradeView::PostNcDestroy()
{
	CBaseView::PostNcDestroy();

	SingleViewManager.RemoveView(this);
}

BEGIN_MESSAGE_MAP(CCreditTradeView, CBaseView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_NOTIFY(NM_CLICK, IDC_Check_bStockAssociated, &CCreditTradeView::OnClickedbStockAssociated)
	ON_EN_CHANGE(IDC_Edit_BSecCode, &CCreditTradeView::OnEnChangeBSeccode)
	ON_EN_CHANGE(IDC_Edit_SSecCode, &CCreditTradeView::OnEnChangeSSecCode)
	ON_NOTIFY(NM_CLICK, IDC_Button_TradeSetting, &CCreditTradeView::OnBtnCreditTradeSetting)
	ON_NOTIFY_RANGE(NM_CLICK, IDC_STATIC_SELL10_1, IDC_Button_bottom, &CCreditTradeView::OnButtonPrice)
	ON_NOTIFY(NM_CLICK, IDC_Button_sell, &CCreditTradeView::OnBtnSell)
	ON_NOTIFY(NM_CLICK, IDC_Button_Buy, &CCreditTradeView::OnBtnBuy)
	ON_NOTIFY_RANGE(NM_CLICK, IDC_Radio_1, IDC_Radio_5, &CCreditTradeView::OnRadioBuy)
	ON_NOTIFY_RANGE(NM_CLICK, IDC_Radio_6, IDC_Radio_10, &CCreditTradeView::OnRadioSell)
	ON_EN_SETFOCUS(IDC_Edit_BSecCode, &CCreditTradeView::OnEnSetFocusBuyCode)
	ON_EN_SETFOCUS(IDC_Edit_BEntrustPrice, &CCreditTradeView::OnEnSetFocusBuyEntrustPrice)
	ON_EN_SETFOCUS(IDC_Edit_BEntrustAmount, &CCreditTradeView::OnEnSetFocusBuyAmout)

	ON_EN_SETFOCUS(IDC_Edit_SSecCode, &CCreditTradeView::OnEnSetFocusSellCode)
	ON_EN_SETFOCUS(IDC_Edit_SEntrustPrice, &CCreditTradeView::OnEnSetFocusSellEntrustPrice)
	ON_EN_SETFOCUS(IDC_Edit_SEntrustAmount, &CCreditTradeView::OnEnSetFocusSellAmout)

	ON_CBN_SELENDOK(IDC_Combo_BEntrustType, &CCreditTradeView::OnSelendokBEntrustType)
	ON_CBN_SELENDOK(IDC_Combo_SEntrustType, &CCreditTradeView::OnSelendokSEntrustType)

	ON_NOTIFY(NM_RETURN, IDC_Edit_BSecCode, &CCreditTradeView::OnEditResturnCodeBuy)
	ON_NOTIFY(NM_RETURN, IDC_Edit_BDefaultBalance, &CCreditTradeView::OnEditResturnDefBalanceBuy)
	ON_NOTIFY(NM_RETURN, IDC_Edit_BEntrustPrice, &CCreditTradeView::OnEditResturnEntrustPriceBuy)
	ON_NOTIFY(NM_RETURN, IDC_Edit_BEntrustAmount, &CCreditTradeView::OnEditResturnEntrustAmountBuy)

	ON_NOTIFY(NM_RETURN, IDC_Edit_SSecCode, &CCreditTradeView::OnEditResturnCodeSell)
	ON_NOTIFY(NM_RETURN, IDC_Edit_SEntrustPrice, &CCreditTradeView::OnEditResturnEntrustPriceSell)
	ON_NOTIFY(NM_RETURN, IDC_Edit_SEntrustAmount, &CCreditTradeView::OnEditResturnEntrustAmountSell)

	ON_EN_KILLFOCUS(IDC_Edit_BSecCode, &CCreditTradeView::OnKillfocusBSecCode)
	ON_EN_KILLFOCUS(IDC_Edit_SSecCode, &CCreditTradeView::OnKillfocusSSecCode)

	ON_EN_KILLFOCUS(IDC_Edit_BDefaultBalance, &CCreditTradeView::OnKillfocusBDefaultBalance)

	ON_EN_KILLFOCUS(IDC_Edit_BEntrustPrice, &CCreditTradeView::OnKillfocusBEntrustPrice)
	ON_EN_KILLFOCUS(IDC_Edit_BEntrustAmount, &CCreditTradeView::OnKillfocusBEntrustAmount)

	ON_EN_KILLFOCUS(IDC_Edit_SEntrustPrice, &CCreditTradeView::OnKillfocusSEntrustPrice)
	ON_EN_KILLFOCUS(IDC_Edit_SEntrustAmount, &CCreditTradeView::OnKillfocusSEntrustAmount)

	ON_NOTIFY(NM_CLICK, IDC_Static_BigCanBuy_2, &CCreditTradeView::OnClickBuyLimit)


END_MESSAGE_MAP()

// CCreditTradeView ��Ϣ�������

void CCreditTradeView::ReleaseView()
{
	delete this;
}

int CCreditTradeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBaseView::OnCreate(lpCreateStruct) == -1)
		return -1;

	//InitialWindow();
	CreateControls();
	InitialData();
	return 0;
}

void CCreditTradeView::dealBuyEntrustPriceChanged()
{
	if (G.VerifybEmpty_SecCode(&CSimpleEdit_BSecCode) == true)
	{
		return;
	}
	/*��д������*/
	G.SetBigCanBuyTotal(GainbFinancingBuy(), &CSimpleEdit_BEntrustPrice, &CSimpleStatic_BigCanBuy_2);
	/*��д��������*/
	G.SetCanBuyTotal(GainbFinancingBuy(), &CSimpleEdit_BEntrustPrice, &CSimpleEdit_BDefaultBalance, &CSimpleStatic_CanBuyTotal_2, &CSimpleStatic_BigCanBuy_2,
		obj_CTradeConfig.bCalculateByBalance, obj_CTradeConfig.DefaultAmount);
	/*��дί�н��*/
	G.SetEntrustBalance(&CSimpleEdit_BEntrustPrice, &CSimpleEdit_BEntrustAmount, &CSimpleStatic_BEntrustBalance_2);
	return;
}

BOOL CCreditTradeView::IsBuySectionShow()
{
	BOOL bResult = FALSE;
	if (m_separatorBuy1.IsWindowVisible())
	{
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}

BOOL CCreditTradeView::IsSellSectionShow()
{
	BOOL bResult = FALSE;
	if (m_separatorSell1.IsWindowVisible())
	{
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}

void CCreditTradeView::OnClickedbStockAssociated(NMHDR *pNmhdr, LRESULT *pResult)
{
	G.ClickedbStockAssociated("content.bStockAssociated_Credit", &CSimpleCheckbox_bStockAssociated);
}

void CCreditTradeView::OnEnSetFocusBuyCode()
{
	switchToBuySection();
}

void CCreditTradeView::OnEnSetFocusBuyEntrustPrice()
{
	switchToBuySection();
}

void CCreditTradeView::OnEnSetFocusBuyAmout()
{
	switchToBuySection();
}

void CCreditTradeView::OnEnSetFocusSellCode()
{
	switchToSellSection();
}

void CCreditTradeView::OnEnSetFocusSellEntrustPrice()
{
	switchToSellSection();
}

void CCreditTradeView::OnEnSetFocusSellAmout()
{
	switchToSellSection();
}

CString CCreditTradeView::GetSecCode(bool bBuyModule)
{
	CString str;
	if (bBuyModule)
	{
		if (IsWindow(CSimpleEdit_BSecCode.GetSafeHwnd()))
		{
			CSimpleEdit_BSecCode.GetWindowText(str);
		}
	}
	else
	{
		if (IsWindow(CSimpleEdit_SSecCode.GetSafeHwnd()))
		{
			CSimpleEdit_SSecCode.GetWindowText(str);
		}
	}
	return str;
}

void CCreditTradeView::OnClickedPrice(CSimpleButton* pClick, CSimpleEdit* pBEntrustPrice, CSimpleEdit* pSEntrustPrice)
{
	CString s_str;
	if (pClick != nullptr && IsWindow(pClick->GetSafeHwnd()))
	{
		pClick->GetWindowText(s_str);
	}

	if (G.VerifybUpdateMoudle(&CSimpleEdit_BSecCode) == true)
	{
		if (pBEntrustPrice != nullptr && IsWindow(pBEntrustPrice->GetSafeHwnd()))
		{
			pBEntrustPrice->SetWindowText(s_str);
		}
		dealBuyEntrustPriceChanged();
	}
	if (G.VerifybUpdateMoudle(&CSimpleEdit_SSecCode) == true)
	{
		if (pSEntrustPrice != nullptr && IsWindow(pSEntrustPrice->GetSafeHwnd()))
		{
			pSEntrustPrice->SetWindowText(s_str);
		}
		dealSellEntrustPriceChanged();
	}
}

void CCreditTradeView::OnButtonPrice(UINT nID, NMHDR *pNmhdr, LRESULT *pResult)
{
	if (nID >= IDC_STATIC_SELL10_1 && nID <= IDC_Button_bottom)
	{
		CSimpleButton* pButton = (CSimpleButton*)GetDlgItem(nID);
		OnClickedPrice(pButton, &CSimpleEdit_BEntrustPrice, &CSimpleEdit_SEntrustPrice);
	}
	*pResult = 0;
}

void CCreditTradeView::OnRadioBuy(UINT nID, NMHDR *pNmhdr, LRESULT *pResult)
{
	if (nID >= IDC_Radio_1 && nID <= IDC_Radio_5)
	{	
		for (UINT nIndex = IDC_Radio_1; nIndex <= IDC_Radio_5; nIndex ++)
		{
			CSimpleRadioButton* pRadio = (CSimpleRadioButton*)GetDlgItem(nIndex);
			if (nIndex == nID)
			{
				pRadio->SetCheck(TRUE);
			} 
			else
			{
				pRadio->SetCheck(FALSE);
			}
		}
		switchToBuySection();
		if (G.VerifybEmpty_SecCode(&CSimpleEdit_BSecCode))
		{
			return;
		}
		/*ί������*/
		SetBEntrustAmount();
		/*ί�н��*/
		G.SetEntrustBalance(&CSimpleEdit_BEntrustPrice, &CSimpleEdit_BEntrustAmount, &CSimpleStatic_BEntrustBalance_2);
	}
}

void CCreditTradeView::OnRadioSell(UINT nID, NMHDR *pNmhdr, LRESULT *pResult)
{
	if (nID >= IDC_Radio_6 && nID <= IDC_Radio_10)
	{
		for (UINT nIndex = IDC_Radio_6; nIndex <= IDC_Radio_10; nIndex++)
		{
			CSimpleRadioButton* pRadio = (CSimpleRadioButton*)GetDlgItem(nIndex);
			if (nIndex == nID)
			{
				pRadio->SetCheck(TRUE);
			}
			else
			{
				pRadio->SetCheck(FALSE);
			}
		}
		switchToSellSection();
		CString stock_code;
		/*���е�killfocus�ڹ�Ʊ����Ϊ�յ�ʱ��Ӧ��ʲô������*/
		if (G.VerifybEmpty_SecCode(&CSimpleEdit_SSecCode))
		{
			return;
		}
		CSimpleEdit_SSecCode.GetWindowText(stock_code);
		/*ί������*/
		SetSEntrustAmount(stock_code);
		/*ί�н��*/
		G.SetEntrustBalance(&CSimpleEdit_SEntrustPrice, &CSimpleEdit_SEntrustAmount, &CSimpleStatic_SEntrustBalance_2);
	}
}

void CCreditTradeView::InitialWindow()
{
	LONG style = GetWindowLong(GetSafeHwnd(), GWL_STYLE);
	style |= WS_CLIPCHILDREN;
	SetWindowLong(GetSafeHwnd(), GWL_STYLE, style);
	SetWindowText("������ȯ");
}

void CCreditTradeView::InitialData()
{
	ColorBuySection();
	bool bResult = G.InitStockAssociated("content.bStockAssociated_Credit");
	CSimpleCheckbox_bStockAssociated.SetCheck(bResult);
	initCreditTradeSettingNeeds();

	CFund obj_CFund;
	if (G.SPtr_CData->GetFund(G.SPtr_CData->fund_account, obj_CFund) == false)
	{
		LOG(ERROR) << "GetFund fail";
		ExceptionInterrupt;
	}

	CString str;
	str.Format("%0.2f", obj_CFund.enable_balance);

	CSimpleStatic_BEnableBalance_2.SetWindowText(str);

	CRect rec4Words;
	G.CalculateTextRect("��Ʊ����", CTradeDlg::s_hFontOrder, rec4Words);

	CRect rec2Words;
	G.CalculateTextRect("����", CTradeDlg::s_hFontOrder, rec2Words);

	m_nHeight = rec4Words.Height();
	m_nWidth4Word = rec4Words.Width();
	m_nWidth2Word = rec2Words.Width();
	m_nAssociatedWidth = m_nWidth4Word + 18;

	CRect rec1Radio;
	G.CalculateTextRect("1", CTradeDlg::s_hFontOrder, rec1Radio);
	CRect rec2Radio;
	G.CalculateTextRect("1/5", CTradeDlg::s_hFontOrder, rec2Radio);
	m_nWidthRadio1 = rec1Radio.Width() + 18;
	m_nWidthRadio2 = rec2Radio.Width() + 18;

	CString strFontStyle = G.GetFontStyle();
	if (FontStandard == strFontStyle)
	{
		m_nEditHeight = 25;
		m_nEditWidth = 120;
		m_nButtonHeight = 23;
		m_nButtonGap = 15;
		m_nPriceWidth = 76;
		m_nGap1 = 2;
		m_nGap2 = 6;
		m_nGap3 = 15;
		m_nGap4 = 16;
		m_nGap5 = 20;
		m_nGap6 = 10;
	}
	else if (FontMedium == strFontStyle)
	{
		m_nEditHeight = 27;
		m_nEditWidth = 137;
		m_nButtonHeight = 25;
		m_nButtonGap = 23;
		m_nPriceWidth = 82;
		m_nGap1 = 4;
		m_nGap2 = 6;
		m_nGap3 = 19;
		m_nGap4 = 10;
		m_nGap5 = 20;
		m_nGap6 = 10;
	}
	else if (FontBig == strFontStyle)
	{
		m_nEditHeight = 30;
		m_nEditWidth = 148;
		m_nButtonHeight = 27;
		m_nButtonGap = 26;
		m_nPriceWidth = 90;
		m_nGap1 = 5;
		m_nGap2 = 6;
		m_nGap3 = 22;
		m_nGap4 = 15;
		m_nGap5 = 20;
		m_nGap6 = 16;
	}

}

bool CCreditTradeView::initCreditTradeSettingNeeds()
{
	ptree pt;
	try {
		read_xml(G.s_ConfigPath, pt);
		obj_CTradeConfig.BuyDefalutGear = pt.get<string>("content.CreditTradeSetting.��Ĭ�ϵ�λ").c_str();
		obj_CTradeConfig.SellDefalutGear = pt.get<string>("content.CreditTradeSetting.��Ĭ�ϵ�λ").c_str();
		obj_CTradeConfig.DefaultAmount = pt.get<int>("content.CreditTradeSetting.Ĭ������");
		obj_CTradeConfig.DefaultBalance = pt.get<double>("content.CreditTradeSetting.Ĭ�Ͻ��");
		obj_CTradeConfig.bTradePopover = pt.get<bool>("content.CreditTradeSetting.bTradePopover");

		obj_CTradeConfig.bCalculateByBalance = pt.get<bool>("content.CreditTradeSetting.bCalculateByBalance");
		obj_CTradeConfig.BEntrustType_Alert = pt.get<string>("content.CreditTradeSetting.BEntrustType_Alert").c_str();

		obj_CTradeConfig.bEntrustQueue = pt.get<bool>("content.CreditTradeSetting.bEntrustQueue");
		obj_CTradeConfig.bEntrustEach = pt.get<bool>("content.CreditTradeSetting.bEntrustEach");

		obj_CTradeConfig.bDismantling = pt.get<bool>("content.CreditTradeSetting.bDismantling");
		obj_CTradeConfig.BaseQuantity = pt.get<int>("content.CreditTradeSetting.BaseQuantity");
		obj_CTradeConfig.bRandom = pt.get<bool>("content.CreditTradeSetting.bRandom");

		obj_CTradeConfig.Order_Minimum = pt.get<int>("content.CreditTradeSetting.Order_Minimum");
		obj_CTradeConfig.Order_Maximum = pt.get<int>("content.CreditTradeSetting.Order_Maximum");
	}
	catch (std::exception& e)
	{
		LOG(INFO) << "Error:" << e.what();
		ExceptionInterrupt;
		AfxMessageBox("�����ļ�����");
		return false;
	}
	return true;
}

void CCreditTradeView::CreateControls()
{
	CStatic_Test.Create("", dwStyle_Static, CRect(0, 0, 0, 0), this, IDC_Static_Test);
	CSimpleCheckbox_bStockAssociated.Create("��������", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Check_bStockAssociated);

	CSimpleStatic_BSecCode.Create("��Ʊ����", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_BSecCode);
	CRect rcData(90, 33, 209, 58);
	CSimpleEdit_BSecCode.Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER, CRect(0, 0, 0, 0), this, IDC_Edit_BSecCode);
	CSimpleEdit_BSecCode.InitSettings();
	CSimpleEdit_BSecCode.EnableNumberControl(FALSE);
	CSimpleEdit_BSecCode.SetLimitText(MaxSecCodeLen_A);

	CSimpleStatic_BSecName_1.Create("��Ʊ����", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_BSecName_1);
	CSimpleStatic_BSecName_2.Create("", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_BSecName_2);

	CSimpleStatic_BEnableBalance_1.Create("�����ʽ�", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_BEnableBalance_1);
	CSimpleStatic_BEnableBalance_2.Create("", SS_CENTERIMAGE | WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_BEnableBalance_2);

	CSimpleStatic_BDefaultBalance.Create("Ĭ���ʽ�", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_BDefaultBalance);
	CSimpleEdit_BDefaultBalance.Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL , CRect(0, 0, 0, 0), this, IDC_Edit_BDefaultBalance);
	CSimpleEdit_BDefaultBalance.InitSettings();

	CSimpleStatic_BEntrustType.Create("ί������", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_BEntrustType);
	CSimpleComboBox_BEntrustType.Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_VSCROLL, CRect(0, 0, 0, 0), this, IDC_Combo_BEntrustType);
	CSimpleComboBox_BEntrustType.AddString(_T(CollateralBuy));
	CSimpleComboBox_BEntrustType.AddString(_T(FinancingBuy));
	CSimpleComboBox_BEntrustType.SetCurSel(0);

	CSimpleStatic_BQuotationWay.Create("���۷�ʽ", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_BQuotationWay);
	CSimpleComboBox_BQuotationWay.Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_VSCROLL, CRect(0, 0, 0, 0), this, IDC_Combo_BQuotationWay);
	CSimpleComboBox_BQuotationWay.SetCurSel(CSimpleComboBox_BQuotationWay.AddString(_T(LimitPrice)));

	CSimpleStatic_BEntrustPrice.Create("ί�м۸�", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_BEntrustPrice);
	CSimpleEdit_BEntrustPrice.Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, CRect(0, 0, 0, 0), this, IDC_Edit_BEntrustPrice);
	CSimpleEdit_BEntrustPrice.InitSettings();

	CSimpleStatic_BigCanBuy_1.Create("������", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_BigCanBuy_1);
	CSimpleStatic_BigCanBuy_2.Create("", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_BigCanBuy_2);
	CSimpleStatic_BigCanBuy_2.EnableClick(TRUE);

	CSimpleStatic_CanBuyTotal_1.Create("�������", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_CanBuyTotal_1);
	CSimpleStatic_CanBuyTotal_2.Create("", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_CanBuyTotal_2);

	m_radio1.Create("1", BS_AUTORADIOBUTTON | WS_GROUP | WS_CHILD | WS_VISIBLE, BUTTON_COLOR_RED, CRect(0, 0, 0, 0), this, IDC_Radio_1);
	m_radio1.SetCheck(true);
	m_radio2.Create("1/2", BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE, BUTTON_COLOR_RED, CRect(0, 0, 0, 0), this, IDC_Radio_2);
	m_radio3.Create("1/3", BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE, BUTTON_COLOR_RED, CRect(0, 0, 0, 0), this, IDC_Radio_3);
	m_radio4.Create("1/4", BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE, BUTTON_COLOR_RED, CRect(0, 0, 0, 0), this, IDC_Radio_4);
	m_radio5.Create("1/5", BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE, BUTTON_COLOR_RED, CRect(0, 0, 0, 0), this, IDC_Radio_5);

	CSimpleStatic_BEntrustAmount.Create("ί������", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_BEntrustAmount);
	CSimpleEdit_BEntrustAmount.Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER, CRect(0, 0, 0, 0), this, IDC_Edit_BEntrustAmount);
	CSimpleEdit_BEntrustAmount.InitSettings();

	CSimpleStatic_BEntrustBalance_1.Create("ί�н��", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_BEntrustBalance_1);
	CSimpleStatic_BEntrustBalance_2.Create("", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_BEntrustBalance_2);

	int nSeparator = IDC_Separator;
	
	m_separatorBuy1.Create(WS_CHILD, COLOR_1, CRect(0, 0, 0, 0), this, nSeparator++);
	m_separatorBuy2.Create(WS_CHILD, COLOR_1, CRect(0, 0, 0, 0), this, nSeparator++);
	m_separatorBuy3.Create(WS_CHILD, COLOR_1, CRect(0, 0, 0, 0), this, nSeparator++);
	m_separatorBuy4.Create(WS_CHILD, COLOR_1, CRect(0, 0, 0, 0), this, nSeparator++);

	m_groupBoxBuySection.Create("", WS_CHILD | BS_GROUPBOX, CRect(0, 0, 0, 0), this, IDC_GroupBox_BuySection);

	CSimpleButton_TradeSetting.Create(WS_CHILD | WS_VISIBLE, BUTTON_GRAY, CRect(0, 0, 0, 0), this, IDC_Button_TradeSetting, "���ײ�������");
	CSimpleButton_Buy.Create(WS_CHILD | WS_VISIBLE, BUTTON_RED, CRect(0, 0, 0, 0), this, IDC_Button_Buy, "����(F3)");

	UINT nID = IDC_STATIC_SELLBUY;

	CSimpleStatic_sell10_1.Create("��ʮ", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_sell9_1.Create("����", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_sell8_1.Create("����", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_sell7_1.Create("����", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_sell6_1.Create("����", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_sell5_1.Create("����", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_sell4_1.Create("����", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_sell3_1.Create("����", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_sell2_1.Create("����", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_sell1_1.Create("��һ", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_buy1_1.Create("��һ", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_buy2_1.Create("���", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_buy3_1.Create("����", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_buy4_1.Create("����", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_buy5_1.Create("����", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_buy6_1.Create("����", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_buy7_1.Create("����", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_buy8_1.Create("���", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_buy9_1.Create("���", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_buy10_1.Create("��ʮ", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_top.Create("��ͣ", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_top);

	nID = IDC_STATIC_SELL10_1;
	CSimpleButton_sell10.Create(WS_CHILD | WS_VISIBLE, NULL, CRect(0, 0, 0, 0), this, nID++, "--", DT_CENTER, FALSE, FALSE, FALSE, FALSE);
	CSimpleButton_sell10.EnableClickToGetFocus(FALSE);
	CSimpleButton_sell10.SetRgnDefColor(RGB(50, 78, 117));
	CSimpleButton_sell10.SetRgnHoverColor(RGB(61, 91, 153));

	CSimpleButton_sell10.SetChangeCursor(TRUE);
	CSimpleButton_sell10.EnableHoverLeaveNotify(TRUE);
	CSimpleButton_sell9.Create(WS_CHILD | WS_VISIBLE, NULL, CRect(0, 0, 0, 0), this, nID++, "--", DT_CENTER, FALSE, FALSE, FALSE, FALSE);
	CSimpleButton_sell9.EnableClickToGetFocus(FALSE);
	CSimpleButton_sell9.SetRgnDefColor(RGB(50, 78, 117));
	CSimpleButton_sell9.SetRgnHoverColor(RGB(61, 91, 153));
	CSimpleButton_sell9.SetChangeCursor(TRUE);
	CSimpleButton_sell9.EnableHoverLeaveNotify(TRUE);
	CSimpleButton_sell8.Create(WS_CHILD | WS_VISIBLE, NULL, CRect(0, 0, 0, 0), this, nID++, "--", DT_CENTER, FALSE, FALSE, FALSE, FALSE);
	CSimpleButton_sell8.EnableClickToGetFocus(FALSE);
	CSimpleButton_sell8.SetRgnDefColor(RGB(50, 78, 117));
	CSimpleButton_sell8.SetRgnHoverColor(RGB(61, 91, 153));
	CSimpleButton_sell8.SetChangeCursor(TRUE);
	CSimpleButton_sell8.EnableHoverLeaveNotify(TRUE);

	CSimpleButton_sell7.Create(WS_CHILD | WS_VISIBLE, NULL, CRect(0, 0, 0, 0), this, nID++, "--", DT_CENTER, FALSE, FALSE, FALSE, FALSE);
	CSimpleButton_sell7.EnableClickToGetFocus(FALSE);
	CSimpleButton_sell7.SetRgnDefColor(RGB(50, 78, 117));
	CSimpleButton_sell7.SetRgnHoverColor(RGB(61, 91, 153));
	CSimpleButton_sell7.SetChangeCursor(TRUE);
	CSimpleButton_sell7.EnableHoverLeaveNotify(TRUE);

	CSimpleButton_sell6.Create(WS_CHILD | WS_VISIBLE, NULL, CRect(0, 0, 0, 0), this, nID++, "--", DT_CENTER, FALSE, FALSE, FALSE, FALSE);
	CSimpleButton_sell6.EnableClickToGetFocus(FALSE);
	CSimpleButton_sell6.SetRgnDefColor(RGB(50, 78, 117));
	CSimpleButton_sell6.SetRgnHoverColor(RGB(61, 91, 153));
	CSimpleButton_sell6.SetChangeCursor(TRUE);
	CSimpleButton_sell6.EnableHoverLeaveNotify(TRUE);

	CSimpleButton_sell5.Create(WS_CHILD | WS_VISIBLE, NULL, CRect(0, 0, 0, 0), this, nID++, "--", DT_CENTER, FALSE, FALSE, FALSE, FALSE);
	CSimpleButton_sell5.EnableClickToGetFocus(FALSE);
	CSimpleButton_sell5.SetRgnDefColor(RGB(50, 78, 117));
	CSimpleButton_sell5.SetRgnHoverColor(RGB(61, 91, 153));
	CSimpleButton_sell5.SetChangeCursor(TRUE);
	CSimpleButton_sell5.EnableHoverLeaveNotify(TRUE);
	CSimpleButton_sell4.Create(WS_CHILD | WS_VISIBLE, NULL, CRect(0, 0, 0, 0), this, nID++, "--", DT_CENTER, FALSE, FALSE, FALSE, FALSE);
	CSimpleButton_sell4.EnableClickToGetFocus(FALSE);
	CSimpleButton_sell4.SetRgnDefColor(RGB(50, 78, 117));
	CSimpleButton_sell4.SetRgnHoverColor(RGB(61, 91, 153));
	CSimpleButton_sell4.SetChangeCursor(TRUE);
	CSimpleButton_sell4.EnableHoverLeaveNotify(TRUE);
	CSimpleButton_sell3.Create(WS_CHILD | WS_VISIBLE, NULL, CRect(0, 0, 0, 0), this, nID++, "--", DT_CENTER, FALSE, FALSE, FALSE, FALSE);
	CSimpleButton_sell3.EnableClickToGetFocus(FALSE);
	CSimpleButton_sell3.SetRgnDefColor(RGB(50, 78, 117));
	CSimpleButton_sell3.SetRgnHoverColor(RGB(61, 91, 153));
	CSimpleButton_sell3.SetChangeCursor(TRUE);
	CSimpleButton_sell3.EnableHoverLeaveNotify(TRUE);
	CSimpleButton_sell2.Create(WS_CHILD | WS_VISIBLE, NULL, CRect(0, 0, 0, 0), this, nID++, "--", DT_CENTER, FALSE, FALSE, FALSE, FALSE);
	CSimpleButton_sell2.EnableClickToGetFocus(FALSE);
	CSimpleButton_sell2.SetRgnDefColor(RGB(50, 78, 117));
	CSimpleButton_sell2.SetRgnHoverColor(RGB(61, 91, 153));
	CSimpleButton_sell2.SetChangeCursor(TRUE);
	CSimpleButton_sell2.EnableHoverLeaveNotify(TRUE);
	CSimpleButton_sell1.Create(WS_CHILD | WS_VISIBLE, NULL, CRect(0, 0, 0, 0), this, nID++, "--", DT_CENTER, FALSE, FALSE, FALSE, FALSE);
	CSimpleButton_sell1.EnableClickToGetFocus(FALSE);
	CSimpleButton_sell1.SetRgnDefColor(RGB(50, 78, 117));
	CSimpleButton_sell1.SetRgnHoverColor(RGB(61, 91, 153));
	CSimpleButton_sell1.SetChangeCursor(TRUE);
	CSimpleButton_sell1.EnableHoverLeaveNotify(TRUE);

	CSimpleButton_buy1.Create(WS_CHILD | WS_VISIBLE, NULL, CRect(0, 0, 0, 0), this, nID++, "--", DT_CENTER, FALSE, FALSE, FALSE, FALSE);
	CSimpleButton_buy1.EnableClickToGetFocus(FALSE);
	CSimpleButton_buy1.SetRgnDefColor(RGB(128, 46, 46));
	CSimpleButton_buy1.SetRgnHoverColor(RGB(153, 61, 61));
	CSimpleButton_buy1.SetChangeCursor(TRUE);
	CSimpleButton_buy1.EnableHoverLeaveNotify(TRUE);

	CSimpleButton_buy2.Create(WS_CHILD | WS_VISIBLE, NULL, CRect(0, 0, 0, 0), this, nID++, "--", DT_CENTER, FALSE, FALSE, FALSE, FALSE);
	CSimpleButton_buy2.EnableClickToGetFocus(FALSE);
	CSimpleButton_buy2.SetRgnDefColor(RGB(128, 46, 46));
	CSimpleButton_buy2.SetRgnHoverColor(RGB(153, 61, 61));
	CSimpleButton_buy2.SetChangeCursor(TRUE);
	CSimpleButton_buy2.EnableHoverLeaveNotify(TRUE);
	CSimpleButton_buy3.Create(WS_CHILD | WS_VISIBLE, NULL, CRect(0, 0, 0, 0), this, nID++, "--", DT_CENTER, FALSE, FALSE, FALSE, FALSE);
	CSimpleButton_buy3.EnableClickToGetFocus(FALSE);
	CSimpleButton_buy3.SetRgnDefColor(RGB(128, 46, 46));
	CSimpleButton_buy3.SetRgnHoverColor(RGB(153, 61, 61));
	CSimpleButton_buy3.SetChangeCursor(TRUE);
	CSimpleButton_buy3.EnableHoverLeaveNotify(TRUE);
	CSimpleButton_buy4.Create(WS_CHILD | WS_VISIBLE, NULL, CRect(0, 0, 0, 0), this, nID++, "--", DT_CENTER, FALSE, FALSE, FALSE, FALSE);
	CSimpleButton_buy4.EnableClickToGetFocus(FALSE);
	CSimpleButton_buy4.SetRgnDefColor(RGB(128, 46, 46));
	CSimpleButton_buy4.SetRgnHoverColor(RGB(153, 61, 61));
	CSimpleButton_buy4.SetChangeCursor(TRUE);
	CSimpleButton_buy4.EnableHoverLeaveNotify(TRUE);
	CSimpleButton_buy5.Create(WS_CHILD | WS_VISIBLE, NULL, CRect(0, 0, 0, 0), this, nID++, "--", DT_CENTER, FALSE, FALSE, FALSE, FALSE);
	CSimpleButton_buy5.EnableClickToGetFocus(FALSE);
	CSimpleButton_buy5.SetRgnDefColor(RGB(128, 46, 46));
	CSimpleButton_buy5.SetRgnHoverColor(RGB(153, 61, 61));
	CSimpleButton_buy5.SetChangeCursor(TRUE);
	CSimpleButton_buy5.EnableHoverLeaveNotify(TRUE);
	CSimpleButton_buy6.Create(WS_CHILD | WS_VISIBLE, NULL, CRect(0, 0, 0, 0), this, nID++, "--", DT_CENTER, FALSE, FALSE, FALSE, FALSE);
	CSimpleButton_buy6.EnableClickToGetFocus(FALSE);
	CSimpleButton_buy6.SetRgnDefColor(RGB(128, 46, 46));
	CSimpleButton_buy6.SetRgnHoverColor(RGB(153, 61, 61));
	CSimpleButton_buy6.SetChangeCursor(TRUE);
	CSimpleButton_buy6.EnableHoverLeaveNotify(TRUE);
	CSimpleButton_buy7.Create(WS_CHILD | WS_VISIBLE, NULL, CRect(0, 0, 0, 0), this, nID++, "--", DT_CENTER, FALSE, FALSE, FALSE, FALSE);
	CSimpleButton_buy7.EnableClickToGetFocus(FALSE);
	CSimpleButton_buy7.SetRgnDefColor(RGB(128, 46, 46));
	CSimpleButton_buy7.SetRgnHoverColor(RGB(153, 61, 61));
	CSimpleButton_buy7.SetChangeCursor(TRUE);
	CSimpleButton_buy7.EnableHoverLeaveNotify(TRUE);
	CSimpleButton_buy8.Create(WS_CHILD | WS_VISIBLE, NULL, CRect(0, 0, 0, 0), this, nID++, "--", DT_CENTER, FALSE, FALSE, FALSE, FALSE);
	CSimpleButton_buy8.EnableClickToGetFocus(FALSE);
	CSimpleButton_buy8.SetRgnDefColor(RGB(128, 46, 46));
	CSimpleButton_buy8.SetRgnHoverColor(RGB(153, 61, 61));
	CSimpleButton_buy8.SetChangeCursor(TRUE);
	CSimpleButton_buy8.EnableHoverLeaveNotify(TRUE);
	CSimpleButton_buy9.Create(WS_CHILD | WS_VISIBLE, NULL, CRect(0, 0, 0, 0), this, nID++, "--", DT_CENTER, FALSE, FALSE, FALSE, FALSE);
	CSimpleButton_buy9.EnableClickToGetFocus(FALSE);
	CSimpleButton_buy9.SetRgnDefColor(RGB(128, 46, 46));
	CSimpleButton_buy9.SetRgnHoverColor(RGB(153, 61, 61));
	CSimpleButton_buy9.SetChangeCursor(TRUE);
	CSimpleButton_buy9.EnableHoverLeaveNotify(TRUE);
	CSimpleButton_buy10.Create(WS_CHILD | WS_VISIBLE, NULL, CRect(0, 0, 0, 0), this, nID++, "--", DT_CENTER, FALSE, FALSE, FALSE, FALSE);
	CSimpleButton_buy10.EnableClickToGetFocus(FALSE);
	CSimpleButton_buy10.SetRgnDefColor(RGB(128, 46, 46));
	CSimpleButton_buy10.SetRgnHoverColor(RGB(153, 61, 61));
	CSimpleButton_buy10.SetChangeCursor(TRUE);
	CSimpleButton_buy10.EnableHoverLeaveNotify(TRUE);
	CSimpleButton_top.Create(WS_CHILD | WS_VISIBLE, NULL, CRect(0, 0, 0, 0), this, IDC_Button_top, "--", DT_CENTER, FALSE, FALSE, FALSE, FALSE);
	CSimpleButton_top.EnableClickToGetFocus(FALSE);
	CSimpleButton_top.SetRgnDefColor(RGB(128, 46, 46));
	CSimpleButton_top.SetRgnHoverColor(RGB(153, 61, 61));
	CSimpleButton_top.SetChangeCursor(TRUE);
	CSimpleButton_top.EnableHoverLeaveNotify(TRUE);


	nID = IDC_STATIC_SELL10_2;
	CSimpleStatic_sell10_3.Create("--", WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_sell10_3.SetBkColor(RGB(50, 78, 117));
	CSimpleStatic_sell9_3.Create("--", WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_sell9_3.SetBkColor(RGB(50, 78, 117));
	CSimpleStatic_sell8_3.Create("--", WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_sell8_3.SetBkColor(RGB(50, 78, 117));
	CSimpleStatic_sell7_3.Create("--", WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_sell7_3.SetBkColor(RGB(50, 78, 117));
	CSimpleStatic_sell6_3.Create("--", WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_sell6_3.SetBkColor(RGB(50, 78, 117));
	CSimpleStatic_sell5_3.Create("--", WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_sell5_3.SetBkColor(RGB(50, 78, 117));
	CSimpleStatic_sell4_3.Create("--", WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_sell4_3.SetBkColor(RGB(50, 78, 117));
	CSimpleStatic_sell3_3.Create("--", WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_sell3_3.SetBkColor(RGB(50, 78, 117));
	CSimpleStatic_sell2_3.Create("--", WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_sell2_3.SetBkColor(RGB(50, 78, 117));
	CSimpleStatic_sell1_3.Create("--", WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_sell1_3.SetBkColor(RGB(50, 78, 117));
	CSimpleStatic_buy1_3.Create("--", WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_buy1_3.SetBkColor(RGB(128, 46, 46));
	CSimpleStatic_buy2_3.Create("--", WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_buy2_3.SetBkColor(RGB(128, 46, 46));
	CSimpleStatic_buy3_3.Create("--", WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_buy3_3.SetBkColor(RGB(128, 46, 46));
	CSimpleStatic_buy4_3.Create("--", WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_buy4_3.SetBkColor(RGB(128, 46, 46));
	CSimpleStatic_buy5_3.Create("--", WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_buy5_3.SetBkColor(RGB(128, 46, 46));
	CSimpleStatic_buy6_3.Create("--", WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_buy6_3.SetBkColor(RGB(128, 46, 46));
	CSimpleStatic_buy7_3.Create("--", WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_buy7_3.SetBkColor(RGB(128, 46, 46));
	CSimpleStatic_buy8_3.Create("--", WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_buy8_3.SetBkColor(RGB(128, 46, 46));
	CSimpleStatic_buy9_3.Create("--", WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_buy9_3.SetBkColor(RGB(128, 46, 46));
	CSimpleStatic_buy10_3.Create("--", WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(0, 0, 0, 0), this, nID++);
	CSimpleStatic_buy10_3.SetBkColor(RGB(128, 46, 46));
	CSimpleStatic_bottom.Create("��ͣ", WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(0, 0, 0, 0), this, IDC_Static_bottom);

	CSimpleButton_bottom.Create(WS_CHILD | WS_VISIBLE, NULL, CRect(0, 0, 0, 0), this, IDC_Button_bottom, "--", DT_CENTER, FALSE, FALSE, FALSE, FALSE);
	CSimpleButton_bottom.EnableClickToGetFocus(FALSE);
	CSimpleButton_bottom.SetRgnDefColor(RGB(50, 78, 117));
	CSimpleButton_bottom.SetRgnHoverColor(RGB(61, 91, 153));
	CSimpleButton_bottom.SetChangeCursor(TRUE);
	CSimpleButton_bottom.EnableHoverLeaveNotify(TRUE);

	////*********������***********************
	CSimpleStatic_TradingCode_1.Create("�������", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_TradingCode_1);
	CSimpleStatic_TradingCode_2.Create("", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_TradingCode_2);

	CSimpleStatic_SSecCode.Create("��Ʊ����", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_SSecCode);
	CSimpleEdit_SSecCode.Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER, CRect(0, 0, 0, 0), this, IDC_Edit_SSecCode);
	CSimpleEdit_SSecCode.EnableNumberControl(FALSE);
	CSimpleEdit_SSecCode.InitSettings();
	CSimpleEdit_SSecCode.SetLimitText(MaxSecCodeLen_A);

	CSimpleStatic_SSecName_1.Create("��Ʊ����", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_SSecName_1);

	CSimpleStatic_SSecName_2.Create("", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_SSecName_2);

	CSimpleStatic_SEntrustType.Create("ί������", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_SEntrustType);
	CSimpleComboBox_SEntrustType.Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_VSCROLL, CRect(0, 0, 0, 0), this, IDC_Combo_SEntrustType);
	CSimpleComboBox_SEntrustType.AddString(_T(CollateralSell));
	CSimpleComboBox_SEntrustType.AddString(_T(FinancingSell));
	CSimpleComboBox_SEntrustType.SetCurSel(0);

	CSimpleStatic_SQuotationWay.Create("���۷�ʽ", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_SQuotationWay);
	CSimpleComboBox_SQuotationWay.Create(CBS_DROPDOWNLIST | CBS_SORT | WS_VSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Combo_SQuotationWay);
	CSimpleComboBox_SQuotationWay.SetCurSel(CSimpleComboBox_SQuotationWay.AddString(_T(LimitPrice)));

	CSimpleStatic_SEntrustPrice.Create("ί�м۸�", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_SEntrustPrice);
	CSimpleEdit_SEntrustPrice.Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, CRect(0, 0, 0, 0), this, IDC_Edit_SEntrustPrice);
	CSimpleEdit_SEntrustPrice.InitSettings();

	CSimpleStatic_CanSellTotal_1.Create("��������", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_CanSellTotal_1);

	CSimpleStatic_CanSellTotal_2.Create("", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_CanSellTotal_2);

	m_radio6.Create("1", BS_AUTORADIOBUTTON | WS_GROUP | WS_CHILD | WS_VISIBLE, BUTTON_COLOR_BLUE, CRect(0, 0, 0, 0), this, IDC_Radio_6);
	m_radio6.SetCheck(true);
	m_radio7.Create("1/2", BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE, BUTTON_COLOR_BLUE, CRect(0, 0, 0, 0), this, IDC_Radio_7);
	m_radio8.Create("1/3", BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE, BUTTON_COLOR_BLUE, CRect(0, 0, 0, 0), this, IDC_Radio_8);
	m_radio9.Create("1/4", BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE, BUTTON_COLOR_BLUE, CRect(0, 0, 0, 0), this, IDC_Radio_9);
	m_radio10.Create("1/5", BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE, BUTTON_COLOR_BLUE, CRect(0, 0, 0, 0), this, IDC_Radio_10);

	CSimpleStatic_SEntrustAmount.Create("ί������", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_SEntrustAmount);
	CSimpleEdit_SEntrustAmount.Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER, CRect(0, 0, 0, 0), this, IDC_Edit_SEntrustAmount);
	CSimpleEdit_SEntrustAmount.InitSettings();

	CSimpleStatic_SEntrustBalance_1.Create("ί�н��", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_SEntrustBalance_1);
	CSimpleStatic_SEntrustBalance_2.Create("", WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_Static_SEntrustBalance_2);

	CSimpleButton_sell.Create(WS_CHILD | WS_VISIBLE, BUTTON_BLUE, CRect(0, 0, 0, 0), this, IDC_Button_sell, "����(F4)");

	m_separatorSell1.Create(WS_CHILD, COLOR_1, CRect(0, 0, 0, 0), this, nSeparator++);
	m_separatorSell2.Create(WS_CHILD, COLOR_1, CRect(0, 0, 0, 0), this, nSeparator++);
	m_separatorSell3.Create(WS_CHILD, COLOR_1, CRect(0, 0, 0, 0), this, nSeparator++);
	m_separatorSell4.Create(WS_CHILD, COLOR_1, CRect(0, 0, 0, 0), this, nSeparator++);

}

void CCreditTradeView::GetRect(CRect& rect, CWnd* pWnd)
{
	if (G.IsWindowValid(pWnd))
	{
		pWnd->GetWindowRect(&rect);
		ScreenToClient(&rect);
	}
}

void CCreditTradeView::OnSize(UINT nType, int cx, int cy)
{
	CBaseView::OnSize(nType, cx, cy);

	if (cx <= 0 || cy <= 0 || !IsWindow(CSimpleCheckbox_bStockAssociated.GetSafeHwnd()))
		return;

	CRect rcAssociated;
	rcAssociated.left = Gap5 + m_nWidth4Word + Gap1 + Gap3;
	rcAssociated.top = Gap2;
	rcAssociated.right = rcAssociated.left + m_nAssociatedWidth;
	rcAssociated.bottom = rcAssociated.top + m_nHeight;
	CSimpleCheckbox_bStockAssociated.MoveWindow(&rcAssociated);

	CRect rcEditCodeBuy;
	rcEditCodeBuy.left = Gap5 + m_nWidth4Word + Gap1;
	rcEditCodeBuy.top = rcAssociated.bottom + Gap4;
	rcEditCodeBuy.right = rcEditCodeBuy.left + m_nEditWidth;
	rcEditCodeBuy.bottom = rcEditCodeBuy.top + m_nEditHeight;
	CSimpleEdit_BSecCode.MoveWindow(rcEditCodeBuy);

	int nGap1 = (rcEditCodeBuy.Height() - m_nHeight) / 2;//��Ʊ������ұ߱༭���top����
	CRect rcStaticCodeBuy;
	rcStaticCodeBuy.left = Gap5;
	rcStaticCodeBuy.top = rcEditCodeBuy.top + nGap1;
	rcStaticCodeBuy.right = rcStaticCodeBuy.left + m_nWidth4Word;
	rcStaticCodeBuy.bottom = rcStaticCodeBuy.top + m_nHeight;
	CSimpleStatic_BSecCode.MoveWindow(&rcStaticCodeBuy);

	int nOffset1 = m_nEditHeight + m_nGap1;
	rcStaticCodeBuy.OffsetRect(0, nOffset1);
	CSimpleStatic_BSecName_1.MoveWindow(&rcStaticCodeBuy);
	CSimpleStatic_BSecName_2.MoveWindow(&CRect(rcEditCodeBuy.left, rcStaticCodeBuy.top, rcEditCodeBuy.right, rcStaticCodeBuy.bottom));

	int nOffset2 = m_nHeight + m_nGap2;
	rcStaticCodeBuy.OffsetRect(0, nOffset2);
	CSimpleStatic_BEnableBalance_1.MoveWindow(&rcStaticCodeBuy);
	CSimpleStatic_BEnableBalance_2.MoveWindow(&CRect(rcEditCodeBuy.left, rcStaticCodeBuy.top, rcEditCodeBuy.right, rcStaticCodeBuy.bottom));

	rcStaticCodeBuy.OffsetRect(0, nOffset1);
	CSimpleStatic_BDefaultBalance.MoveWindow(&rcStaticCodeBuy);
	CSimpleEdit_BDefaultBalance.MoveWindow(&CRect(rcEditCodeBuy.left, rcStaticCodeBuy.top - nGap1, rcEditCodeBuy.right, rcStaticCodeBuy.top - nGap1 + m_nEditHeight));

	rcStaticCodeBuy.OffsetRect(0, nOffset1);
	CSimpleStatic_BEntrustType.MoveWindow(&rcStaticCodeBuy);
	CSimpleComboBox_BEntrustType.MoveWindow(&CRect(rcEditCodeBuy.left, rcStaticCodeBuy.top - nGap1, rcEditCodeBuy.right, rcStaticCodeBuy.top + 300));

	rcStaticCodeBuy.OffsetRect(0, nOffset1);
	CSimpleStatic_BQuotationWay.MoveWindow(&rcStaticCodeBuy);
	CSimpleComboBox_BQuotationWay.MoveWindow(&CRect(rcEditCodeBuy.left, rcStaticCodeBuy.top - nGap1, rcEditCodeBuy.right, rcStaticCodeBuy.top + 300));

	rcStaticCodeBuy.OffsetRect(0, nOffset1);
	CSimpleStatic_BEntrustPrice.MoveWindow(&rcStaticCodeBuy);
	CSimpleEdit_BEntrustPrice.MoveWindow(&CRect(rcEditCodeBuy.left, rcStaticCodeBuy.top - nGap1, rcEditCodeBuy.right, rcStaticCodeBuy.top - nGap1 + m_nEditHeight));

	rcStaticCodeBuy.OffsetRect(0, nOffset1);
	CSimpleStatic_BigCanBuy_1.MoveWindow(&rcStaticCodeBuy);
	CSimpleStatic_BigCanBuy_2.MoveWindow(&CRect(rcEditCodeBuy.left, rcStaticCodeBuy.top, rcEditCodeBuy.right, rcStaticCodeBuy.bottom));

	rcStaticCodeBuy.OffsetRect(0, nOffset1 + 2);
	CSimpleStatic_CanBuyTotal_1.MoveWindow(&rcStaticCodeBuy);
	CSimpleStatic_CanBuyTotal_2.MoveWindow(&CRect(rcEditCodeBuy.left, rcStaticCodeBuy.top, rcEditCodeBuy.right, rcStaticCodeBuy.bottom));

	CRect rcRadio1;
	rcRadio1.left = Gap5;
	rcRadio1.top = rcStaticCodeBuy.bottom + m_nGap6;
	rcRadio1.right = rcRadio1.left + m_nWidthRadio1;
	rcRadio1.bottom = rcRadio1.top + m_nHeight;
	m_radio1.MoveWindow(&rcRadio1);

	CRect rcRadio;
	rcRadio.left = rcRadio1.right + 6;
	rcRadio.top = rcRadio1.top;
	rcRadio.right = rcRadio.left + m_nWidthRadio2;
	rcRadio.bottom = rcRadio1.bottom;

	m_radio2.MoveWindow(&rcRadio);
	int nOffset3 = m_nWidthRadio2 + 6;
	rcRadio.OffsetRect(nOffset3, 0);
	m_radio3.MoveWindow(&rcRadio);
	rcRadio.OffsetRect(nOffset3, 0);
	m_radio4.MoveWindow(&rcRadio);
	rcRadio.OffsetRect(nOffset3, 0);
	m_radio5.MoveWindow(&rcRadio);

	rcStaticCodeBuy.OffsetRect(0, m_nHeight + m_nGap6 + m_nHeight + m_nGap6);
	CSimpleStatic_BEntrustAmount.MoveWindow(&rcStaticCodeBuy);
	CSimpleEdit_BEntrustAmount.MoveWindow(&CRect(rcEditCodeBuy.left, rcStaticCodeBuy.top - nGap1, rcEditCodeBuy.right, rcStaticCodeBuy.top - nGap1 + m_nEditHeight));

	rcStaticCodeBuy.OffsetRect(0, nOffset1);
	CSimpleStatic_BEntrustBalance_1.MoveWindow(&rcStaticCodeBuy);
	CSimpleStatic_BEntrustBalance_2.MoveWindow(&CRect(rcEditCodeBuy.left, rcStaticCodeBuy.top, rcEditCodeBuy.right, rcStaticCodeBuy.bottom));

	CRect rcBtnSetting;
	rcBtnSetting.left = rcStaticCodeBuy.left;
	rcBtnSetting.top = rcStaticCodeBuy.bottom + m_nGap5;
	rcBtnSetting.right = rcBtnSetting.left + m_nWidth4Word + 30 + m_nButtonGap;
	rcBtnSetting.bottom = rcBtnSetting.top + m_nButtonHeight;
	CSimpleButton_TradeSetting.MoveWindow(&rcBtnSetting);

	CRect rcBtnBuy;
	rcBtnBuy.left = rcBtnSetting.right + 25;
	rcBtnBuy.top = rcBtnSetting.top;
	rcBtnBuy.right = rcEditCodeBuy.right;
	rcBtnBuy.bottom = rcBtnSetting.bottom;
	CSimpleButton_Buy.MoveWindow(&rcBtnBuy);

	int nOffset4 = m_nHeight + 1;
	CRect rtBuySell(rcEditCodeBuy.right + Gap6, Gap2, rcEditCodeBuy.right + Gap6 + m_nWidth2Word, Gap2 + m_nHeight);
	CSimpleStatic_sell10_1.MoveWindow(&rtBuySell);
	rtBuySell.OffsetRect(0, nOffset4);
	CSimpleStatic_sell9_1.MoveWindow(&rtBuySell);
	rtBuySell.OffsetRect(0, nOffset4);
	CSimpleStatic_sell8_1.MoveWindow(&rtBuySell);
	rtBuySell.OffsetRect(0, nOffset4);
	CSimpleStatic_sell7_1.MoveWindow(&rtBuySell);
	rtBuySell.OffsetRect(0, nOffset4);
	CSimpleStatic_sell6_1.MoveWindow(&rtBuySell);
	rtBuySell.OffsetRect(0, nOffset4);
	CSimpleStatic_sell5_1.MoveWindow(&rtBuySell);
	rtBuySell.OffsetRect(0, nOffset4);
	CSimpleStatic_sell4_1.MoveWindow(&rtBuySell);
	rtBuySell.OffsetRect(0, nOffset4);
	CSimpleStatic_sell3_1.MoveWindow(&rtBuySell);
	rtBuySell.OffsetRect(0, nOffset4);
	CSimpleStatic_sell2_1.MoveWindow(&rtBuySell);
	rtBuySell.OffsetRect(0, nOffset4);
	CSimpleStatic_sell1_1.MoveWindow(&rtBuySell);
	rtBuySell.OffsetRect(0, nOffset4);
	CSimpleStatic_buy1_1.MoveWindow(&rtBuySell);
	rtBuySell.OffsetRect(0, nOffset4);
	CSimpleStatic_buy2_1.MoveWindow(&rtBuySell);
	rtBuySell.OffsetRect(0, nOffset4);
	CSimpleStatic_buy3_1.MoveWindow(&rtBuySell);
	rtBuySell.OffsetRect(0, nOffset4);
	CSimpleStatic_buy4_1.MoveWindow(&rtBuySell);
	rtBuySell.OffsetRect(0, nOffset4);
	CSimpleStatic_buy5_1.MoveWindow(&rtBuySell);
	rtBuySell.OffsetRect(0, nOffset4);
	CSimpleStatic_buy6_1.MoveWindow(&rtBuySell);
	rtBuySell.OffsetRect(0, nOffset4);
	CSimpleStatic_buy7_1.MoveWindow(&rtBuySell);
	rtBuySell.OffsetRect(0, nOffset4);
	CSimpleStatic_buy8_1.MoveWindow(&rtBuySell);
	rtBuySell.OffsetRect(0, nOffset4);
	CSimpleStatic_buy9_1.MoveWindow(&rtBuySell);
	rtBuySell.OffsetRect(0, nOffset4);
	CSimpleStatic_buy10_1.MoveWindow(&rtBuySell);
	rtBuySell.OffsetRect(0, nOffset4 + 5);
	CSimpleStatic_top.MoveWindow(&rtBuySell);

	CRect rt1(rtBuySell.right + 10, Gap2, rtBuySell.right + m_nPriceWidth, Gap2 + m_nHeight);
	CSimpleButton_sell10.MoveWindow(&rt1);
	rt1.OffsetRect(0, nOffset4);
	CSimpleButton_sell9.MoveWindow(&rt1);
	rt1.OffsetRect(0, nOffset4);
	CSimpleButton_sell8.MoveWindow(&rt1);
	rt1.OffsetRect(0, nOffset4);
	CSimpleButton_sell7.MoveWindow(&rt1);
	rt1.OffsetRect(0, nOffset4);
	CSimpleButton_sell6.MoveWindow(&rt1);
	rt1.OffsetRect(0, nOffset4);
	CSimpleButton_sell5.MoveWindow(&rt1);
	rt1.OffsetRect(0, nOffset4);
	CSimpleButton_sell4.MoveWindow(&rt1);
	rt1.OffsetRect(0, nOffset4);
	CSimpleButton_sell3.MoveWindow(&rt1);
	rt1.OffsetRect(0, nOffset4);
	CSimpleButton_sell2.MoveWindow(&rt1);
	rt1.OffsetRect(0, nOffset4);
	CSimpleButton_sell1.MoveWindow(&rt1);
	rt1.OffsetRect(0, nOffset4);
	CSimpleButton_buy1.MoveWindow(&rt1);
	rt1.OffsetRect(0, nOffset4);
	CSimpleButton_buy2.MoveWindow(&rt1);
	rt1.OffsetRect(0, nOffset4);
	CSimpleButton_buy3.MoveWindow(&rt1);
	rt1.OffsetRect(0, nOffset4);
	CSimpleButton_buy4.MoveWindow(&rt1);
	rt1.OffsetRect(0, nOffset4);
	CSimpleButton_buy5.MoveWindow(&rt1);
	rt1.OffsetRect(0, nOffset4);
	CSimpleButton_buy6.MoveWindow(&rt1);
	rt1.OffsetRect(0, nOffset4);
	CSimpleButton_buy7.MoveWindow(&rt1);
	rt1.OffsetRect(0, nOffset4);
	CSimpleButton_buy8.MoveWindow(&rt1);
	rt1.OffsetRect(0, nOffset4);
	CSimpleButton_buy9.MoveWindow(&rt1);
	rt1.OffsetRect(0, nOffset4);
	CSimpleButton_buy10.MoveWindow(&rt1);
	rt1.OffsetRect(0, nOffset4 + 5);
	CSimpleButton_top.MoveWindow(&rt1);

	CRect rt2(rt1.right + 1, Gap2, rt1.right + 1 + m_nPriceWidth, Gap2 + m_nHeight);
	CSimpleStatic_sell10_3.MoveWindow(&rt2);
	CRect rectMark = rt2;
	rt2.OffsetRect(0, nOffset4);
	CSimpleStatic_sell9_3.MoveWindow(&rt2);
	rt2.OffsetRect(0, nOffset4);
	CSimpleStatic_sell8_3.MoveWindow(&rt2);
	rt2.OffsetRect(0, nOffset4);
	CSimpleStatic_sell7_3.MoveWindow(&rt2);
	rt2.OffsetRect(0, nOffset4);
	CSimpleStatic_sell6_3.MoveWindow(&rt2);
	rt2.OffsetRect(0, nOffset4);
	CSimpleStatic_sell5_3.MoveWindow(&rt2);
	rt2.OffsetRect(0, nOffset4);
	CSimpleStatic_sell4_3.MoveWindow(&rt2);
	rt2.OffsetRect(0, nOffset4);
	CSimpleStatic_sell3_3.MoveWindow(&rt2);
	rt2.OffsetRect(0, nOffset4);
	CSimpleStatic_sell2_3.MoveWindow(&rt2);
	rt2.OffsetRect(0, nOffset4);
	CSimpleStatic_sell1_3.MoveWindow(&rt2);
	rt2.OffsetRect(0, nOffset4);
	CSimpleStatic_buy1_3.MoveWindow(&rt2);
	rt2.OffsetRect(0, nOffset4);
	CSimpleStatic_buy2_3.MoveWindow(&rt2);
	rt2.OffsetRect(0, nOffset4);
	CSimpleStatic_buy3_3.MoveWindow(&rt2);
	rt2.OffsetRect(0, nOffset4);
	CSimpleStatic_buy4_3.MoveWindow(&rt2);
	rt2.OffsetRect(0, nOffset4);
	CSimpleStatic_buy5_3.MoveWindow(&rt2);
	rt2.OffsetRect(0, nOffset4);
	CSimpleStatic_buy6_3.MoveWindow(&rt2);
	rt2.OffsetRect(0, nOffset4);
	CSimpleStatic_buy7_3.MoveWindow(&rt2);
	rt2.OffsetRect(0, nOffset4);
	CSimpleStatic_buy8_3.MoveWindow(&rt2);
	rt2.OffsetRect(0, nOffset4);
	CSimpleStatic_buy9_3.MoveWindow(&rt2);
	rt2.OffsetRect(0, nOffset4);
	CSimpleStatic_buy10_3.MoveWindow(&rt2);
	rt2.OffsetRect(0, nOffset4 + 5);

	rt2.SetRect(rt2.left + 15, rt2.top, rt2.left + 15 + m_nWidth2Word, rt2.bottom);
	CSimpleStatic_bottom.MoveWindow(&rt2);

	CSimpleButton_bottom.MoveWindow(&CRect(rt2.right + 15, rt2.top, rt2.right + 15 + m_nPriceWidth, rt2.bottom));

	////*********������***********************
	CRect rcQuto(rectMark.right + Gap6, Gap2, rectMark.right + Gap6 + m_nWidth4Word, Gap2 + m_nHeight);
	CSimpleStatic_TradingCode_1.MoveWindow(&rcQuto);
	CRect rcQutoValue(rcQuto.right + Gap1, rcQuto.top, rcQuto.right + Gap1 + m_nEditWidth, rcQuto.bottom);
	CSimpleStatic_TradingCode_2.MoveWindow(&rcQutoValue);

	rcQuto.OffsetRect(0, m_nHeight + m_nGap3);
	rcQutoValue.OffsetRect(0, m_nHeight + m_nGap3);
	CSimpleStatic_SSecCode.MoveWindow(&rcQuto);
	CRect rcEditCodeSelll;
	rcEditCodeSelll.left = rcQutoValue.left;
	rcEditCodeSelll.top = rcQuto.top - nGap1;
	rcEditCodeSelll.right = rcQutoValue.right;
	rcEditCodeSelll.bottom = rcEditCodeSelll.top + m_nEditHeight;
	CSimpleEdit_SSecCode.MoveWindow(&rcEditCodeSelll);

	rcQuto.OffsetRect(0, m_nHeight + m_nGap3 + 3);
	rcQutoValue.OffsetRect(0, m_nHeight + m_nGap3 + 3);
	CSimpleStatic_SSecName_1.MoveWindow(&rcQuto);
	CSimpleStatic_SSecName_2.MoveWindow(&rcQutoValue);

	rcQuto.OffsetRect(0, m_nHeight + m_nGap3 + 2);
	rcQutoValue.OffsetRect(0, m_nHeight + m_nGap3 + 2);
	CSimpleStatic_SEntrustType.MoveWindow(&rcQuto);
	CSimpleComboBox_SEntrustType.MoveWindow(&CRect(rcQutoValue.left, rcQuto.top - nGap1, rcQutoValue.right, rcQuto.top + 300));

	rcQuto.OffsetRect(0, m_nHeight + m_nGap3 + 2);
	rcQutoValue.OffsetRect(0, m_nHeight + m_nGap3 + 2);
	CSimpleStatic_SQuotationWay.MoveWindow(&rcQuto);
	CSimpleComboBox_SQuotationWay.MoveWindow(&CRect(rcQutoValue.left, rcQuto.top - nGap1, rcQutoValue.right, rcQuto.top + 300));

	rcQuto.OffsetRect(0, m_nHeight + m_nGap3 + 6);
	rcQutoValue.OffsetRect(0, m_nHeight + m_nGap3 + 6);
	CSimpleStatic_SEntrustPrice.MoveWindow(&rcQuto);
	CSimpleEdit_SEntrustPrice.MoveWindow(&CRect(rcQutoValue.left, rcQuto.top - nGap1, rcQutoValue.right, rcQuto.top - nGap1 + m_nEditHeight));

	rcQuto.OffsetRect(0, m_nHeight + m_nGap3 + 6);
	rcQutoValue.OffsetRect(0, m_nHeight + m_nGap3 + 6);
	CSimpleStatic_CanSellTotal_1.MoveWindow(&rcQuto);
	CSimpleStatic_CanSellTotal_2.MoveWindow(&rcQutoValue);

	CRect rcRadio6;
	rcRadio6.left = rcQuto.left;
	rcRadio6.top = rcQuto.bottom + m_nGap3 + 5;
	rcRadio6.right = rcRadio6.left + m_nWidthRadio1;
	rcRadio6.bottom = rcRadio6.top + m_nHeight;
	m_radio6.MoveWindow(&rcRadio6);

	CRect rcRadioEx;
	rcRadioEx.left = rcRadio6.right + 6;
	rcRadioEx.top = rcRadio6.top;
	rcRadioEx.right = rcRadioEx.left + m_nWidthRadio2;
	rcRadioEx.bottom = rcRadio6.bottom;
	m_radio7.MoveWindow(&rcRadioEx);
	rcRadioEx.OffsetRect(nOffset3, 0);
	m_radio8.MoveWindow(&rcRadioEx);
	rcRadioEx.OffsetRect(nOffset3, 0);
	m_radio9.MoveWindow(&rcRadioEx);
	rcRadioEx.OffsetRect(nOffset3, 0);
	m_radio10.MoveWindow(&rcRadioEx);

	rcQuto.OffsetRect(0, m_nHeight + m_nGap3 + 5 + m_nHeight + m_nGap4);
	rcQutoValue.OffsetRect(0, m_nHeight + m_nGap3 + 5 + m_nHeight + m_nGap4);
	CSimpleStatic_SEntrustAmount.MoveWindow(&rcQuto);
	CSimpleEdit_SEntrustAmount.MoveWindow(&CRect(rcQutoValue.left, rcQuto.top - nGap1, rcQutoValue.right, rcQuto.top - nGap1 + m_nEditHeight));

	rcQuto.OffsetRect(0, m_nHeight + m_nGap3 + 8);
	rcQutoValue.OffsetRect(0, m_nHeight + m_nGap3 + 8);
	CSimpleStatic_SEntrustBalance_1.MoveWindow(&rcQuto);
	CSimpleStatic_SEntrustBalance_2.MoveWindow(&rcQutoValue);

	CSimpleButton_sell.MoveWindow(&CRect(rcQutoValue.right - rcBtnBuy.Width(), rcQuto.bottom + m_nGap5, rcQutoValue.right, rcQuto.bottom + m_nGap5 + m_nButtonHeight));

	CRect rect1;
	GetRect(rect1, &CSimpleStatic_BSecName_1);
	CRect rect3;
	GetRect(rect3, &CSimpleStatic_BEntrustBalance_1);

	int nLeft = rect1.left - 8;
	int nTop = rcEditCodeBuy.top - 6;
	int nRight = rcEditCodeBuy.right + 8;
	int nBottom = rect3.bottom + 6;

	m_separatorBuy1.MoveWindow(&CRect(nLeft, nTop, nLeft + 2, nBottom), FALSE);
	m_separatorBuy2.MoveWindow(&CRect(nLeft, nBottom, nRight + 2, nBottom + 2), FALSE);
	m_separatorBuy3.MoveWindow(&CRect(nRight, nTop, nRight + 2, nBottom), FALSE);
	m_separatorBuy4.MoveWindow(&CRect(nLeft, nTop, nRight, nTop + 2), FALSE);

	CRect rect11;
	GetRect(rect11, &CSimpleStatic_SSecName_1);
	CRect rect33;
	GetRect(rect33, &CSimpleStatic_SEntrustBalance_1);

	nLeft = rect11.left - 8;
	nTop = rcEditCodeSelll.top - 6;
	nRight = rcEditCodeSelll.right + 8;
	nBottom = rect33.bottom + 6;

	m_separatorSell1.MoveWindow(&CRect(nLeft, nTop, nLeft + 2, nBottom), FALSE);
	m_separatorSell2.MoveWindow(&CRect(nLeft, nBottom, nRight + 2, nBottom + 2), FALSE);
	m_separatorSell3.MoveWindow(&CRect(nRight, nTop, nRight + 2, nBottom), FALSE);
	m_separatorSell4.MoveWindow(&CRect(nLeft, nTop, nRight, nTop + 2), FALSE);

}


BOOL CCreditTradeView::GetDefaultRect(CRect &rect)
{
	CString strFontStyle = G.GetFontStyle();
	if (FontStandard == strFontStyle)
	{
		rect.SetRect(0, 0, 677, 436);
	}
	else if (FontMedium == strFontStyle)
	{
		rect.SetRect(0, 0, 741, 483);
	}
	else if (FontBig == strFontStyle)
	{
		rect.SetRect(0, 0, 800, 545);
	}
	return TRUE;
}

BOOL CCreditTradeView::PreTranslateMessage(MSG* pMsg)
{
	return CBaseView::PreTranslateMessage(pMsg);
}

void CCreditTradeView::SetTradeModuleData(const CString &stock_code)
{
	if (CSimpleCheckbox_bStockAssociated.GetCheck())
	{
		CSimpleEdit_BSecCode.SetWindowText(stock_code);
	}
	CSimpleEdit_SSecCode.SetWindowText(stock_code);
}

void CCreditTradeView::switchToSellSection()
{
	ColorSellSection();
	if (true == G.bStockAssociated)
	{
		return;
	}

	CString SecCode;
	CString MarketCode;
	CSimpleEdit_SSecCode.GetWindowText(SecCode);
	if ("" == SecCode)
	{
		return;
	}
	if (G.SPtr_CData->SecCode2MarketCode(SecCode, MarketCode) == false)
	{
		return;
	}
	if (ensureSecCodeMarket(false, false, SecCode, MarketCode, GetEntrustType(false)) == false)
	{
		return;
	}
	G.SPtr_CData->TradingSecCode = SecCode;
	RedrawMarket(MarketCode, SecCode);
}

void CCreditTradeView::switchToBuySection()
{
	if (IsBuySectionShow())
	{
		return;
	}
	ColorBuySection();

	if (true == G.bStockAssociated)
	{
		return;
	}

	CString SecCode;
	CString MarketCode;
	CSimpleEdit_BSecCode.GetWindowText(SecCode);
	
	if ("" == SecCode)
	{
		return;
	}
	if (G.SPtr_CData->SecCode2MarketCode(SecCode, MarketCode) == false)
	{
		return;
	}
	if (ensureSecCodeMarket(false, true, SecCode, MarketCode, GetEntrustType(true)) == false)
	{
		return;
	}
	G.SPtr_CData->TradingSecCode = SecCode;
	RedrawMarket(MarketCode, SecCode);
}

void CCreditTradeView::ColorBuySection()
{
	if (IsWindow(m_separatorBuy1.GetSafeHwnd()))
	{
		m_separatorBuy1.ShowWindow(SW_SHOW);
		m_separatorBuy2.ShowWindow(SW_SHOW);
		m_separatorBuy3.ShowWindow(SW_SHOW);
		m_separatorBuy4.ShowWindow(SW_SHOW);

		m_separatorSell1.ShowWindow(SW_HIDE);
		m_separatorSell2.ShowWindow(SW_HIDE);
		m_separatorSell3.ShowWindow(SW_HIDE);
		m_separatorSell4.ShowWindow(SW_HIDE);
	}
}

void CCreditTradeView::ColorSellSection()
{
	if (IsWindow(m_separatorBuy1.GetSafeHwnd()))
	{
		m_separatorBuy1.ShowWindow(SW_HIDE);
		m_separatorBuy2.ShowWindow(SW_HIDE);
		m_separatorBuy3.ShowWindow(SW_HIDE);
		m_separatorBuy4.ShowWindow(SW_HIDE);

		m_separatorSell1.ShowWindow(SW_SHOW);
		m_separatorSell2.ShowWindow(SW_SHOW);
		m_separatorSell3.ShowWindow(SW_SHOW);
		m_separatorSell4.ShowWindow(SW_SHOW);
	}
}

bool CCreditTradeView::DealTradeModule(bool bBuyMoudle, const CString &stock_code, const CString &MarketCode)
{
	G.SPtr_CData->TradingSecCode = stock_code;
	/*�м�����ģ�鴦��*/
	SetMarketModule(MarketCode, stock_code);
	if (bBuyMoudle)
	{
		ColorBuySection();
		if (CSimpleCheckbox_bStockAssociated.GetCheck())
		{
			/*��ģ�鴦��*/
			SetSellModule(MarketCode, stock_code);
		}
		/*��ģ�鴦��*/
		SetBuyModule(MarketCode, stock_code);
	}
	else
	{
		ColorSellSection();
		if (CSimpleCheckbox_bStockAssociated.GetCheck())
		{
			/*��ģ�鴦��*/
			SetBuyModule(MarketCode, stock_code);
		}
		/*��ģ�鴦��*/
		SetSellModule(MarketCode, stock_code);
	}
	return true;
}

void CCreditTradeView::SetMarketModule(const CString &MarketCode, const CString &SecCode)
{
	RedrawMarket(MarketCode, SecCode);
}

bool CCreditTradeView::RedrawMarket(const CString MarketCode, const CString stock_code)
{
	CSimpleStatic_TradingCode_2.SetWindowText(stock_code);
	G.DrawDepth(MarketCode, stock_code, 10, &CSimpleButton_sell10, &CSimpleStatic_sell10_3);
	G.DrawDepth(MarketCode, stock_code, 9, &CSimpleButton_sell9, &CSimpleStatic_sell9_3);
	G.DrawDepth(MarketCode, stock_code, 8, &CSimpleButton_sell8, &CSimpleStatic_sell8_3);
	G.DrawDepth(MarketCode, stock_code, 7, &CSimpleButton_sell7, &CSimpleStatic_sell7_3);
	G.DrawDepth(MarketCode, stock_code, 6, &CSimpleButton_sell6, &CSimpleStatic_sell6_3);

	G.DrawDepth(MarketCode, stock_code, 5, &CSimpleButton_sell5, &CSimpleStatic_sell5_3);
	G.DrawDepth(MarketCode, stock_code, 4, &CSimpleButton_sell4, &CSimpleStatic_sell4_3);
	G.DrawDepth(MarketCode, stock_code, 3, &CSimpleButton_sell3, &CSimpleStatic_sell3_3);
	G.DrawDepth(MarketCode, stock_code, 2, &CSimpleButton_sell2, &CSimpleStatic_sell2_3);
	G.DrawDepth(MarketCode, stock_code, 1, &CSimpleButton_sell1, &CSimpleStatic_sell1_3);

	G.DrawDepth(MarketCode, stock_code, -10, &CSimpleButton_buy10, &CSimpleStatic_buy10_3);
	G.DrawDepth(MarketCode, stock_code, -9, &CSimpleButton_buy9, &CSimpleStatic_buy9_3);
	G.DrawDepth(MarketCode, stock_code, -8, &CSimpleButton_buy8, &CSimpleStatic_buy8_3);
	G.DrawDepth(MarketCode, stock_code, -7, &CSimpleButton_buy7, &CSimpleStatic_buy7_3);
	G.DrawDepth(MarketCode, stock_code, -6, &CSimpleButton_buy6, &CSimpleStatic_buy6_3);

	G.DrawDepth(MarketCode, stock_code, -5, &CSimpleButton_buy5, &CSimpleStatic_buy5_3);
	G.DrawDepth(MarketCode, stock_code, -4, &CSimpleButton_buy4, &CSimpleStatic_buy4_3);
	G.DrawDepth(MarketCode, stock_code, -3, &CSimpleButton_buy3, &CSimpleStatic_buy3_3);
	G.DrawDepth(MarketCode, stock_code, -2, &CSimpleButton_buy2, &CSimpleStatic_buy2_3);
	G.DrawDepth(MarketCode, stock_code, -1, &CSimpleButton_buy1, &CSimpleStatic_buy1_3);

	/*��ͣ Top*/
	/*��ͣ Bottom*/
	G.SetBottomTop(MarketCode, stock_code, &CSimpleButton_bottom, &CSimpleButton_top);
	return true;
}

void CCreditTradeView::SetSellModule(const CString &MarketCode, const CString &SecCode)
{
	CSimpleEdit_SSecCode.SetWindowText(SecCode);
	/*��Ʊ����*/
	G.SetSecName(MarketCode, SecCode, &CSimpleStatic_SSecName_2);
	/*��������*/
	G.SetCanSellTotal(&CSimpleStatic_CanSellTotal_2, SecCode);
	/*ί�м۸�*/
	G.SetEntrustPrice(&CSimpleEdit_SEntrustPrice, obj_CTradeConfig.SellDefalutGear, MarketCode, SecCode);
	/*ί������*/
	SetSEntrustAmount(SecCode);
	/*ί�н��*/
	G.SetEntrustBalance(&CSimpleEdit_SEntrustPrice, &CSimpleEdit_SEntrustAmount, &CSimpleStatic_SEntrustBalance_2);
}

int CCreditTradeView::GetCheckedRadioButtonEx(int nIDFirstButton, int nIDLastButton)
{
	for (int nIndex = nIDFirstButton; nIndex <= nIDLastButton; nIndex ++)
	{
		CSimpleRadioButton* pBtn = (CSimpleRadioButton*)GetDlgItem(nIndex);
		if (pBtn != nullptr && IsWindow(pBtn->GetSafeHwnd()))
		{
			if (pBtn->GetCheck())
			{
				return nIndex;
			}
		}
	}
	return nIDFirstButton;
}

bool CCreditTradeView::SetSEntrustAmount(const CString stock_code)
{
	CString s_str;
	UINT nSex;
	UInt_64 enable_amount;
	G.GaineEable_amount(stock_code, enable_amount);
	nSex = GetCheckedRadioButtonEx(IDC_Radio_6, IDC_Radio_10);
	switch (nSex) {
	case IDC_Radio_6:
		s_str.Format(_T("%u"), enable_amount);
		break;
	case IDC_Radio_7:
		s_str.Format(_T("%u"), G.modifyNum(enable_amount / 2));
		break;
	case IDC_Radio_8:
		s_str.Format(_T("%u"), G.modifyNum(enable_amount / 3));
		break;
	case IDC_Radio_9:
		s_str.Format(_T("%u"), G.modifyNum(enable_amount / 4));
		break;
	case IDC_Radio_10:
		s_str.Format(_T("%u"), G.modifyNum(enable_amount / 5));
		break;
	default:
		break;
	}
	CSimpleEdit_SEntrustAmount.SetWindowText(s_str);
	return true;
}

void CCreditTradeView::SetBuyModule(const CString &MarketCode, const CString &SecCode)
{
	/*������������������ˣ����ܲ���return����Ϊ�п���֮ǰ���������ݣ����return���Ļ��ͻ���������ݣ������޷������û��������쳣����*/
	CString s_str;
	/*��ģ�鴦��*/
	CSimpleEdit_BSecCode.SetWindowText(SecCode);
	/*��Ʊ����*/
	G.SetSecName(MarketCode, SecCode, &CSimpleStatic_BSecName_2);
	/*�����ʽ�*/
	G.SetEnable_balance(&CSimpleStatic_BEnableBalance_2, GainbFinancingBuy());
	/*Ĭ���ʽ� Ĭ���ʽ�����������ΪĬ�ϵ�ʱ����ʾΪ0*/
	G.SetDefaultBalance(obj_CTradeConfig.bCalculateByBalance, obj_CTradeConfig.DefaultBalance, &CSimpleEdit_BDefaultBalance);
	/*ί�м۸�*/
	G.SetEntrustPrice(&CSimpleEdit_BEntrustPrice, obj_CTradeConfig.BuyDefalutGear, MarketCode, SecCode);
	/*������ IDC_BigCanBuyTotal*/
	G.SetBigCanBuyTotal(GainbFinancingBuy(), &CSimpleEdit_BEntrustPrice, &CSimpleStatic_BigCanBuy_2);
	/*�������*/
	G.SetCanBuyTotal(GainbFinancingBuy(), &CSimpleEdit_BEntrustPrice, &CSimpleEdit_BDefaultBalance, &CSimpleStatic_CanBuyTotal_2, &CSimpleStatic_BigCanBuy_2,
		obj_CTradeConfig.bCalculateByBalance, obj_CTradeConfig.DefaultAmount);
	/*ί������*/
	SetBEntrustAmount();
	/*ί�н��*/
	G.SetEntrustBalance(&CSimpleEdit_BEntrustPrice, &CSimpleEdit_BEntrustAmount, &CSimpleStatic_BEntrustBalance_2);
}

bool CCreditTradeView::SetBEntrustAmount()
{
	UInt_64 CanBuyTotal;
	G.GainLegalValue(CanBuyTotal, &CSimpleStatic_CanBuyTotal_2);
	CString s_str;
	UINT nSex;
	nSex = GetCheckedRadioButtonEx(IDC_Radio_1, IDC_Radio_5);
	switch (nSex) {
	case IDC_Radio_1:
		s_str.Format(_T("%u"), G.modifyNum(CanBuyTotal));
		break;
	case IDC_Radio_2:
		s_str.Format(_T("%u"), G.modifyNum(CanBuyTotal / 2));
		break;
	case IDC_Radio_3:
		s_str.Format(_T("%u"), G.modifyNum(CanBuyTotal / 3));
		break;
	case IDC_Radio_4:
		s_str.Format(_T("%u"), G.modifyNum(CanBuyTotal / 4));
		break;
	case IDC_Radio_5:
		s_str.Format(_T("%u"), G.modifyNum(CanBuyTotal / 5));
		break;
	default:
		break;
	}
	CSimpleEdit_BEntrustAmount.SetWindowText(s_str);
	return true;
}

void CCreditTradeView::OnEnableBalanceChange()
{
	G.SetEnable_balance(&CSimpleStatic_BEnableBalance_2, GainbFinancingBuy());
	G.SetBigCanBuyTotal(GainbFinancingBuy(), &CSimpleEdit_BEntrustPrice, &CSimpleStatic_BigCanBuy_2);
}

CString CCreditTradeView::GetSellStockCode()
{
	CString str;
	CSimpleEdit_SSecCode.GetWindowText(str);
	return str;
}

CSimpleStatic* CCreditTradeView::GetCanSellAmountCtrl()
{
	return &CSimpleStatic_CanSellTotal_2;
}

bool CCreditTradeView::VerifySellEntrustment()
{
	if (G.VerifybEmpty_SecCode(&CSimpleEdit_SSecCode) == true)
	{
		MessageBox("��Ʊ����Ϊ��", "��ʾ", MB_OK);
		return false;
	}
	if (G.VerifySEntrustPrice(&CSimpleStatic_SSecName_2, &CSimpleEdit_SSecCode, &CSimpleEdit_SEntrustPrice) == false)
	{
		return false;
	}

	if (G.VerifySEntrustAmount(obj_CTradeConfig.bDismantling, &CSimpleStatic_CanSellTotal_2, &CSimpleEdit_SEntrustAmount) == false)
	{
		return false;
	}
	return true;
}

void CCreditTradeView::dealSendSellEntrust()
{
	(CStatic*)GetDlgItem(IDC_Static_Test)->SetFocus();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (VerifySellEntrustment() == false)
	{
		return;
	}

	if (obj_CTradeConfig.bTradePopover == 1)
	{
		CString s_str;
		G.GainOrderInfo(s_str, "����", &CSimpleEdit_SSecCode, &CSimpleStatic_SSecName_2, &CSimpleEdit_SEntrustPrice, &CSimpleEdit_SEntrustAmount);
		if (MessageBox(s_str, "��ʾ", MB_YESNO) == IDNO)
		{
			return;
		}
	}

	int entrust_amount;
	G.GainLegalValue(entrust_amount, &CSimpleEdit_SEntrustAmount);
	vector<string> Vec_Dismantling;
	if (G.FillVec_Dismantling(Vec_Dismantling, entrust_amount, obj_CTradeConfig.bDismantling,
		obj_CTradeConfig.bRandom, obj_CTradeConfig.BaseQuantity, obj_CTradeConfig.Order_Minimum
		, obj_CTradeConfig.Order_Maximum) == false)
	{
		return;
	}

	string s_Fun335002;
	GainSell335002(s_Fun335002);
	G.SendAllOrder(Vec_Dismantling, G.pCApiFun, Api_Asy, s_Fun335002, G.SPtr_CData);
	switchToSellSection();
}

bool CCreditTradeView::GainSell335002(string &s_str)
{
	CString s_tmp;
	string stock_code;
	GetDlgItem(IDC_Edit_SSecCode)->GetWindowText(s_tmp);
	stock_code = s_tmp;
	string exchange_type;
	if (G.SPtr_CData->SecCode2ExchangeType(stock_code.c_str(), exchange_type) == false)
	{
		LOG(ERROR) << "SecCode2ExchangeType  fail" << endl;
		ExceptionInterrupt;
		return false;
	}

	string entrust_amount;
	GetDlgItem(IDC_Edit_SEntrustAmount)->GetWindowText(s_tmp);
	entrust_amount = s_tmp;
	string entrust_price;
	GetDlgItem(IDC_Edit_SEntrustPrice)->GetWindowText(s_tmp);
	entrust_price = s_tmp;

	string entrust_type;
	GetDlgItem(IDC_Combo_SEntrustType)->GetWindowText(s_tmp);
	switch (tool::find_enumEntrustType(string(s_tmp)))
	{
	case enumXinYongJiaoYi:
		entrust_type = "9";
		break;
	case enumXinYongRongZi:
		entrust_type = "6";
		break;
	default:
		ErrorLog("abnormal entrust_type");
		break;
	}

	Json::Value obj_Value;
	obj_Value["function_id"] = "335002";
	obj_Value["op_entrust_way"] = op_entrust_way_����ί��;
	obj_Value["exchange_type"] = exchange_type;
	obj_Value["op_branch_no"] = G.SPtr_CData->branch_no;
	obj_Value["branch_no"] = G.SPtr_CData->branch_no;

	obj_Value["sysnode_id"] = G.SPtr_CData->sysnode_id;

	obj_Value["fund_account"] = G.SPtr_CData->s_user;
	obj_Value["password"] = G.SPtr_CData->s_pass;
	obj_Value["password_type"] = password_type_��������;
	obj_Value["stock_code"] = string(stock_code);
	obj_Value["entrust_amount"] = entrust_amount;

	obj_Value["entrust_price"] = entrust_price;
	obj_Value["entrust_bs"] = entrust_bs_����;
	obj_Value["entrust_prop"] = entrust_prop_����;
	obj_Value["entrust_type"] = entrust_type;
	obj_Value["asset_prop"] = AssetProp_�����˻�;
	s_str = obj_Value.toStyledString();
	return true;
}

void CCreditTradeView::dealSendBuyEntrust()
{
	/*Ϊ��Ӧ�Կ�ݼ����µĿ����޷�ʹ��ģ���ʧȥ������������������ý���*/
    (CStatic*)GetDlgItem(IDC_Static_Test)->SetFocus();
	if (VerifyBuyEntrustment() == false)
	{
		return;
	}
	/*����ǰ���û��㵯��ȷ���Ƿ��µ�*/
	if (obj_CTradeConfig.bTradePopover == 1)
	{
		CString s_str;
		G.GainOrderInfo(s_str, "����", &CSimpleEdit_BSecCode, &CSimpleStatic_BSecName_2, &CSimpleEdit_BEntrustPrice, &CSimpleEdit_BEntrustAmount);
		if (MessageBox(s_str, "��ʾ", MB_YESNO) == IDNO)
		{
			return;
		}
	}
	vector<string> Vec_Dismantling;
	UInt_64 entrust_amount;
	G.GainLegalValue(entrust_amount, &CSimpleEdit_BEntrustAmount);
	if (G.FillVec_Dismantling(Vec_Dismantling, entrust_amount, obj_CTradeConfig.bDismantling,
		obj_CTradeConfig.bRandom, obj_CTradeConfig.BaseQuantity, obj_CTradeConfig.Order_Minimum,
		obj_CTradeConfig.Order_Maximum) == false)
	{
		return;
	}
	string s_Fun335002;
	GainBuy335002(s_Fun335002);
	G.SendAllOrder(Vec_Dismantling, G.pCApiFun, Api_Asy, s_Fun335002, G.SPtr_CData);
	if (G.SPtr_CData->TestSpeed == 1)
	{
		LOG(ERROR) << "begin SendOrder";
		GetSystemTime(&G.SPtr_CData->systime_SendOrder);
	}
	switchToBuySection();
}

bool CCreditTradeView::GainBuy335002(string &s_str)
{
	CString s_tmp;
	string stock_code;
	GetDlgItem(IDC_Edit_BSecCode)->GetWindowText(s_tmp);
	stock_code = s_tmp;
	string exchange_type;
	if (G.SPtr_CData->SecCode2ExchangeType(stock_code.c_str(), exchange_type) == false)
	{
		LOG(ERROR) << "SecCode2ExchangeType  fail" << endl;
		ExceptionInterrupt;
		return false;
	}

	string entrust_type;
	GetDlgItem(IDC_Combo_BEntrustType)->GetWindowText(s_tmp);
	switch (tool::find_enumEntrustType(string(s_tmp)))
	{
	case enumXinYongJiaoYi:
		entrust_type = "9";
		break;
	case enumXinYongRongZi:
		entrust_type = "6";
		break;
	default:
		ErrorLog("abnoraml entrust_type");
		return false;
		break;
	}

	string entrust_amount;
	GetDlgItem(IDC_Edit_BEntrustAmount)->GetWindowText(s_tmp);
	entrust_amount = s_tmp;
	string entrust_price;
	GetDlgItem(IDC_Edit_BEntrustPrice)->GetWindowText(s_tmp);
	entrust_price = s_tmp;

	Json::Value obj_Value;
	obj_Value["function_id"] = "335002";
	obj_Value["op_entrust_way"] = op_entrust_way_����ί��;
	obj_Value["exchange_type"] = exchange_type;
	obj_Value["op_branch_no"] = G.SPtr_CData->branch_no;
	obj_Value["branch_no"] = G.SPtr_CData->branch_no;

	obj_Value["sysnode_id"] = G.SPtr_CData->sysnode_id;

	obj_Value["fund_account"] = G.SPtr_CData->s_user;
	obj_Value["password"] = G.SPtr_CData->s_pass;
	obj_Value["password_type"] = password_type_��������;
	obj_Value["stock_code"] = string(stock_code);
	obj_Value["entrust_amount"] = entrust_amount;

	obj_Value["entrust_price"] = entrust_price;
	obj_Value["entrust_bs"] = entrust_bs_����;
	obj_Value["entrust_prop"] = entrust_prop_����;
	obj_Value["entrust_type"] = entrust_type;
	obj_Value["asset_prop"] = AssetProp_�����˻�;
	s_str = obj_Value.toStyledString();
	return true;
}

bool CCreditTradeView::VerifyBuyEntrustment()
{
	if (G.VerifybEmpty_SecCode(&CSimpleEdit_BSecCode) == true)
	{
		MessageBox("��Ʊ����Ϊ��", "��ʾ", MB_OK);
		return false;
	}

	if (G.VerifyBEntrustPrice(&CSimpleStatic_BSecName_2, &CSimpleEdit_BSecCode, &CSimpleEdit_BEntrustPrice) == false)
	{
		return false;
	}
	/*ί��������ʱ����У�飬���ǵ����û���ʱ�;����˲����ܳ���100������ֻУ������Ƿ�Ϲ����*/
	if (G.VerifyBEntrustAmount(obj_CTradeConfig.bDismantling, &CSimpleStatic_BigCanBuy_2, &CSimpleEdit_BEntrustAmount) == false)
	{
		return false;
	}

	if (G.VerifyBEntrustBalance(GainbFinancingBuy(), &CSimpleStatic_BEnableBalance_2, &CSimpleStatic_BEntrustBalance_2) == false)
	{
		return false;
	}
	return true;
}

bool CCreditTradeView::GainBuy333002(string &s_str)
{
	CString s_tmp;
	string stock_code;
	GetDlgItem(IDC_Edit_BSecCode)->GetWindowText(s_tmp);
	stock_code = s_tmp;
	string exchange_type;
	if (G.SPtr_CData->SecCode2ExchangeType(stock_code.c_str(), exchange_type) == false)
	{
		LOG(ERROR) << "SecCode2ExchangeType  fail" << endl;
		ExceptionInterrupt;
		return false;
	}

	string entrust_price;
	GetDlgItem(IDC_Edit_BEntrustPrice)->GetWindowText(s_tmp);
	entrust_price = s_tmp;

	string entrust_amount;
	GetDlgItem(IDC_Edit_BEntrustAmount)->GetWindowText(s_tmp);
	entrust_amount = s_tmp;


	Json::Value obj_Value;
	obj_Value["function_id"] = "333002";
	obj_Value["op_entrust_way"] = op_entrust_way_����ί��;
	obj_Value["exchange_type"] = exchange_type;
	obj_Value["op_branch_no"] = G.SPtr_CData->branch_no;
	obj_Value["branch_no"] = G.SPtr_CData->branch_no;

	obj_Value["sysnode_id"] = G.SPtr_CData->sysnode_id;

	obj_Value["fund_account"] = G.SPtr_CData->s_user;
	obj_Value["password"] = G.SPtr_CData->s_pass;
	obj_Value["password_type"] = password_type_��������;
	obj_Value["stock_code"] = string(stock_code);
	obj_Value["entrust_amount"] = entrust_amount;

	obj_Value["entrust_price"] = entrust_price;
	obj_Value["entrust_bs"] = entrust_bs_����;
	obj_Value["entrust_prop"] = entrust_prop_����;
	s_str = obj_Value.toStyledString();
	return true;
}

bool CCreditTradeView::GainSell333002(string &s_str)
{
	/*Ĭ�ϲ�����ȫ�Ǳ����entrust_prop 0(����) ref_id(���HS no) op_branch_no(������֧���� �ɲ���)
	op_entrust_way(ί�з�ʽ 7����ί��)sysnode_id(ϵͳ�ڵ��� ��½��ȡ) op_station(վ���ַ �ɲ���)
	branch_no(��֧���� �����½��ȡ) exchange_type(���Եô˿��Բ�������Ⱑ) */
	CString s_tmp;
	string stock_code;
	GetDlgItem(IDC_Edit_SSecCode)->GetWindowText(s_tmp);
	stock_code = s_tmp;
	string exchange_type;
	if (G.SPtr_CData->SecCode2ExchangeType(stock_code.c_str(), exchange_type) == false)
	{
		LOG(ERROR) << "SecCode2ExchangeType fail" << endl;
		ExceptionInterrupt;
		return false;
	}

	string entrust_amount;
	GetDlgItem(IDC_Edit_SEntrustAmount)->GetWindowText(s_tmp);
	entrust_amount = s_tmp;
	string entrust_price;
	GetDlgItem(IDC_Edit_SEntrustPrice)->GetWindowText(s_tmp);
	entrust_price = s_tmp;

	Json::Value obj_Value;
	obj_Value["function_id"] = "333002";
	obj_Value["op_entrust_way"] = op_entrust_way_����ί��;
	obj_Value["exchange_type"] = exchange_type;
	obj_Value["op_branch_no"] = G.SPtr_CData->branch_no;
	obj_Value["branch_no"] = G.SPtr_CData->branch_no;

	obj_Value["sysnode_id"] = G.SPtr_CData->sysnode_id;

	obj_Value["fund_account"] = G.SPtr_CData->s_user;
	obj_Value["password"] = G.SPtr_CData->s_pass;
	obj_Value["password_type"] = password_type_��������;
	obj_Value["stock_code"] = string(stock_code);
	obj_Value["entrust_amount"] = entrust_amount;

	obj_Value["entrust_price"] = entrust_price;
	obj_Value["entrust_bs"] = entrust_bs_����;
	obj_Value["entrust_prop"] = entrust_prop_����;
	s_str = obj_Value.toStyledString();
	return true;
}

void CCreditTradeView::OnEnChangeBSeccode()
{
	if (GetFocus() != &CSimpleEdit_BSecCode)
	{
		/*���㲻�ڱ༭���ɵ���ֲ֡�Ԥ��ֱ�������*/
		return;
	}
	static bool bEndDraw = true;
	CString s_str;
	CSimpleEdit_BSecCode.GetWindowText(s_str);
	// ֻ����������
	int Length = s_str.GetLength();
	if (MaxSecCodeLen_A == Length)
	{
		if (bEndDraw == false)
		{
			return;
		}
		bEndDraw = false;
		cerr << "BSeccode = 6" << endl;
		RedrawBuyMoudle();
		bEndDraw = true;
	}
}

bool CCreditTradeView::RedrawBuyMoudle()
{
	CString SecCode;
	CString MarketCode;
	CSimpleEdit_BSecCode.GetWindowText(SecCode);

	if (ensureSecCodeMarket(true, true, SecCode, MarketCode, GetEntrustType(true)) == true)
	{
		DealTradeModule(true, SecCode, MarketCode);
	}
	else
	{
		DealIllegal_BSecCode();
	}
	return true;
}

bool CCreditTradeView::DealIllegal_BSecCode()
{
	G.SPtr_CData->TradingSecCode = "";
	EmptyBuyModule();
	EmptyMarketModule();
	if (CSimpleCheckbox_bStockAssociated.GetCheck())
	{
		EmptySellModule();
	}
	return true;
}

bool CCreditTradeView::EmptySellModule()
{
	((CButton *)GetDlgItem(IDC_Radio_6))->SetCheck(TRUE);
	m_radio6.SetCheck(TRUE);
	m_radio7.SetCheck(FALSE);
	m_radio8.SetCheck(FALSE);
	m_radio9.SetCheck(FALSE);
	m_radio10.SetCheck(FALSE);

	/*��Ʊ���� IDC_SSecCode*/
	/*��Ʊ���� IDC_SSecName*/
	/*ί�м۸� IDC_SEntrustPrice*/
	/*�������� IDC_SCanSellTotal*/
	/*ί������ IDC_SEntrustAmount*/

	/*ί�н�� IDC_SEntrustBalance*/
	CSimpleEdit_SSecCode.SetWindowText(_T(""));
	CSimpleStatic_SSecName_2.SetWindowText(_T(""));
	CSimpleEdit_SEntrustPrice.SetWindowText(_T(""));
	CSimpleStatic_CanSellTotal_2.SetWindowText(_T(""));
	CSimpleEdit_SEntrustAmount.SetWindowText(_T(""));

	CSimpleStatic_SEntrustBalance_2.SetWindowText(_T(""));
	return true;
}

bool CCreditTradeView::EmptyMarketModule()
{
	/*��ͣ Top*/
	/*��ͣ Bottom*/
	CSimpleButton_top.SetWindowText(_T(""));
	CSimpleButton_bottom.SetWindowText(_T(""));
	/*�������*/
	CSimpleStatic_TradingCode_2.SetWindowText(_T(""));
	for (UINT iID = IDC_STATIC_SELL10_1; iID <= IDC_STATIC_BUY10_1; iID++)
	{
		CSimpleButton* pCSimpleButton = (CSimpleButton*)GetDlgItem(iID);
		if (G.IsWindowValid(pCSimpleButton))
		{
			pCSimpleButton->SetWindowText(_T(""));
		}
	}
	for (UINT iID = IDC_STATIC_SELL10_2; iID <= IDC_STATIC_BUY10_2; iID++)
	{
		CSimpleStatic* pStatic = (CSimpleStatic*)GetDlgItem(iID);
		if (G.IsWindowValid(pStatic))
		{
			pStatic->SetWindowText(_T(""));
		}
	}

	return true;
}

bool CCreditTradeView::EmptyBuyModule()
{
	m_radio1.SetCheck(TRUE);
	m_radio2.SetCheck(FALSE);
	m_radio3.SetCheck(FALSE);
	m_radio4.SetCheck(FALSE);
	m_radio5.SetCheck(FALSE);
	/*��Ʊ���� IDC_BSecCode*/
	/*��Ʊ���� IDC_BSecName*/
	/*�����ʽ� IDC_BEnableBalance*/
	/*Ĭ���ʽ� IDC_BDefaultBalance*/
	/*ί�м۸� IDC_BEntrustPrice*/

	/*������ IDC_BigCanBuyTotal*/
	/*������� IDC_BCanBuyTotal*/
	/*ί������ IDC_BEntrustAmount*/
	/*ί�н�� IDC_BEntrustBalance*/
	CSimpleEdit_BSecCode.SetWindowText(_T(""));
	CSimpleStatic_BSecName_2.SetWindowText(_T(""));
	CSimpleStatic_BEnableBalance_2.SetWindowText(_T(""));
	CSimpleEdit_BDefaultBalance.SetWindowText(_T(""));
	CSimpleEdit_BEntrustPrice.SetWindowText(_T(""));

	CSimpleStatic_BigCanBuy_2.SetWindowText(_T(""));
	CSimpleStatic_CanBuyTotal_2.SetWindowText(_T(""));
	CSimpleEdit_BEntrustAmount.SetWindowText(_T(""));
	CSimpleStatic_BEntrustBalance_2.SetWindowText(_T(""));
	return true;
}

void CCreditTradeView::OnEnChangeSSecCode()
{
	if (GetFocus() != &CSimpleEdit_SSecCode)
	{
		/*���㲻�ڱ༭���ɵ���ֲ֡�Ԥ��ֱ�������*/
		return;
	}

	static bool bEndDraw = true;
	CString s_str;
	CSimpleEdit_SSecCode.GetWindowText(s_str);
	// ֻ����������
	int Length = s_str.GetLength();
	if (MaxSecCodeLen_A == Length)
	{
		if (bEndDraw == false)
		{
			return;
		}
		bEndDraw = false;
		cerr << "SSeccode = 6" << endl;
		RedrawSellMoudle();
		bEndDraw = true;
	}
}

bool CCreditTradeView::RedrawSellMoudle()
{
	CString SecCode;
	CString MarketCode;
	CSimpleEdit_SSecCode.GetWindowText(SecCode);

	if (ensureSecCodeMarket(true, false, SecCode, MarketCode, GetEntrustType(false)) == true)
	{
		DealTradeModule(false, SecCode, MarketCode);
	}
	else
	{
		DealIllegal_SSecCode();
	}
	return true;
}

bool CCreditTradeView::DealIllegal_SSecCode()
{
	G.SPtr_CData->TradingSecCode = "";
	EmptySellModule();
	EmptyMarketModule();
	if (CSimpleCheckbox_bStockAssociated.GetCheck())
	{
		EmptyBuyModule();
	}
	return true;
}

void CCreditTradeView::OnBtnCreditTradeSetting(NMHDR *pNmhdr, LRESULT *pResult)
{
	CCreditTradeSetting setting(this, &obj_CTradeConfig);
	setting.DoModal();
}

void CCreditTradeView::dealSellEntrustPriceChanged()
{
	if (G.VerifybEmpty_SecCode(&CSimpleEdit_SSecCode) == true)
	{
		return;
	}
	G.SetEntrustBalance(&CSimpleEdit_SEntrustPrice, &CSimpleEdit_SEntrustAmount, &CSimpleStatic_SEntrustBalance_2);
	return;
}

void CCreditTradeView::dealDefaultBalanceChanged()
{
	if (G.VerifybEmpty_SecCode(&CSimpleEdit_BSecCode) == true)
	{
		return;
	}
	/*��д������*/
	G.SetBigCanBuyTotal(GainbFinancingBuy(), &CSimpleEdit_BEntrustPrice, &CSimpleStatic_BigCanBuy_2);
	/*��д��������*/
	G.SetCanBuyTotal(GainbFinancingBuy(), &CSimpleEdit_BEntrustPrice, &CSimpleEdit_BDefaultBalance, &CSimpleStatic_CanBuyTotal_2, &CSimpleStatic_BigCanBuy_2,
		obj_CTradeConfig.bCalculateByBalance, obj_CTradeConfig.DefaultAmount);
	/*��дί������*/
	SetBEntrustAmount();
	/*��дί�н��*/
	G.SetEntrustBalance(&CSimpleEdit_BEntrustPrice, &CSimpleEdit_BEntrustAmount, &CSimpleStatic_BEntrustBalance_2);
}

void CCreditTradeView::OnBtnSell(NMHDR *pNmhdr, LRESULT *pResult)
{
	dealSendSellEntrust();
	*pResult = 0;
}

void CCreditTradeView::OnBtnBuy(NMHDR *pNmhdr, LRESULT *pResult)
{
	dealSendBuyEntrust();
	*pResult = 0;
}

bool CCreditTradeView::ensureSecCodeMarket(bool bLock, bool bBuyModule, const CString &SecCode, CString &MarketCode, const CString &entrust_type)
{
	if ("" == SecCode)
	{
		return false;
	}
	/*�������������Ƿ�����*/
	if (G.VerifyMarketStatus() == false)
	{
		LOG(ERROR) << "ȫ�г�����Ϊ�գ������˳�";
		MessageBox(_T("ȫ�г�����Ϊ�գ������˳�"), "ϵͳ�쳣", 0);

		if (G.SPtr_CData->bRun_MainPageDlg == true)
		{
			/*�˳�����*/
			if (::PostMessage(G.SPtr_CData->hwnd_MainPageDlg, WM_AbnormalExit, 0, 0) == 0)
			{
				LOG(ERROR) << "PostMessage fail";
				ExceptionInterrupt;
			}
		}
		return false;
	}

	/*У��֤ȯ������֧���б�*/
	if (G.SPtr_CData->SecCode2MarketCode(SecCode, MarketCode) == false)
	{
		return false;
	}
	/*У��֤ȯ������֧���б�*/
	if (bBuyModule)//��У�飬����У��
	{
		if (VerifyEntrustType(entrust_type, MarketCode, SecCode) == false)
		{
			MessageBox("ί�����Ͳ���ȷ", "��ʾ", MB_OK);
			return false;
		}
	}
	CGridCtrlEx* pBuy1Grid = nullptr;
	CGridCtrlEx* pSell1Grid = nullptr;
	COrderQueueView* pViewOrderQueue = (COrderQueueView*)GetViewByID(ID_view_orderQueue);
	if (G.IsWindowValid(pViewOrderQueue))
	{
		pBuy1Grid = pViewOrderQueue->GetBuy1Grid();
		pSell1Grid = pViewOrderQueue->GetSell1Grid();
	}
	COrderEachView* pViewOrderEach = (COrderEachView*)GetViewByID(ID_view_orderEach);

	CGridCtrlEx* pOrderEachGrid = nullptr;
	if (G.IsWindowValid(pViewOrderEach))
	{
		pOrderEachGrid = pViewOrderEach->GetGrid_T();
	}
	G.DealSubscribe(bLock, MarketCode, SecCode, obj_CTradeConfig.bEntrustQueue, obj_CTradeConfig.bEntrustEach, pBuy1Grid, pSell1Grid, pOrderEachGrid);
	
	return true;
}

CSimpleEdit* CCreditTradeView::GetBuyCodeEdit()
{
	return &CSimpleEdit_BSecCode;
}

bool CCreditTradeView::VerifyEntrustType(const CString & entrust_type, const CString &MarketCode,
	const CString &stock_code)
{
	CString stock_account;
	if (G.SPtr_CData->Market2Account(G.SPtr_CData->fund_account, MarketCode, stock_account) == false)
	{
		LOG(ERROR) << "Market2Account fail";
		ExceptionInterrupt;
		return false;
	}

	if (CollateralBuy == entrust_type || CollateralSell == entrust_type)
	{
		/*����ǲ����ڵ���Ʒ�б��� */
		CSecurity obj_Security;
		if (G.SPtr_CData->GetSecurity_DanBao(G.SPtr_CData->fund_account, stock_account, stock_code, obj_Security) == false)
		{
			return false;
		}
		return true;
	}
	else if (FinancingBuy == entrust_type || FinancingSell == entrust_type)
	{
		/*����Ƿ��ڱ��ȯ��*/
		CSecurity obj_Security;
		if (G.SPtr_CData->GetSecurity_BiaoDi(G.SPtr_CData->fund_account, stock_account, stock_code, obj_Security) == false)
		{
			return false;
		}
		return true;
	}
	else
	{
		ExceptionInterrupt;
		LOG(ERROR) << "abnormal BuyEntrustType";
		return false;
	}

	return true;
}

bool CCreditTradeView::VerifyEntrustTyep(CString secCode,bool bBuy)
{
	CString entrust_type;
	CString marketCode;
	if (bBuy)
	{
		CSimpleComboBox_BEntrustType.GetWindowTextA(entrust_type);
	}
	else
	{
		CSimpleComboBox_SEntrustType.GetWindowTextA(entrust_type);
	}

	if (G.SPtr_CData->SecCode2MarketCode(secCode, marketCode) == false)
	{
		return false;
	}
	
	return VerifyEntrustType(entrust_type, marketCode, secCode);
}

CString CCreditTradeView::GetEntrustType(bool bBuyModule)
{
	CString str;
	if (bBuyModule)
	{
		if (IsWindow(CSimpleComboBox_BEntrustType.GetSafeHwnd()))
		{
			CSimpleComboBox_BEntrustType.GetWindowText(str);
		}
	}
	else
	{
		if (IsWindow(CSimpleComboBox_SEntrustType.GetSafeHwnd()))
		{
			CSimpleComboBox_SEntrustType.GetWindowText(str);
		}
	}
	return str;
}

void CCreditTradeView::OnSelendokBEntrustType()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString stock_code;
	CString latest_BEntrustType;
	CString MarketCode;
	CSimpleEdit_BSecCode.GetWindowText(stock_code);
	if (G.SPtr_CData->SecCode2MarketCode(stock_code, MarketCode) == false)
	{
		return;
	}
	CSimpleComboBox_BEntrustType.GetWindowText(latest_BEntrustType);
	if (VerifyEntrustType(latest_BEntrustType, MarketCode, stock_code) == false)
	{
		DealIllegal_BSecCode();
		return;
	}

	/*����ˢ��*/
	G.SetEnable_balance(&CSimpleStatic_BEnableBalance_2, GainbFinancingBuy());
	dealBuyEntrustPriceChanged();
}

void CCreditTradeView::OnSelendokSEntrustType()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString stock_code;
	CString latest_SEntrustType;
	CString MarketCode;
	CSimpleEdit_SSecCode.GetWindowText(stock_code);
	if (G.SPtr_CData->SecCode2MarketCode(stock_code, MarketCode) == false)
	{
		return;
	}
	CSimpleComboBox_SEntrustType.GetWindowText(latest_SEntrustType);
	if (VerifyEntrustType(latest_SEntrustType, MarketCode, stock_code) == false)
	{
		DealIllegal_SSecCode();
		return;
	}

	dealSellEntrustPriceChanged();
}

bool CCreditTradeView::GainbFinancingBuy()
{
	CString BEntrustType;
	CSimpleComboBox_BEntrustType.GetWindowText(BEntrustType);
	if (FinancingBuy == BEntrustType)
	{
		return true;
	}
	return false;
}

void CCreditTradeView::OnEditResturnCodeBuy(NMHDR *pNMHDR, LRESULT *pResult)
{
	CSimpleEdit_BDefaultBalance.SetFocus();
}

void CCreditTradeView::OnEditResturnDefBalanceBuy(NMHDR *pNMHDR, LRESULT *pResult)
{
	CSimpleEdit_BEntrustPrice.SetFocus();
}

void CCreditTradeView::OnEditResturnEntrustPriceBuy(NMHDR *pNMHDR, LRESULT *pResult)
{
	CSimpleEdit_BEntrustAmount.SetFocus();
}

void CCreditTradeView::OnEditResturnEntrustAmountBuy(NMHDR *pNMHDR, LRESULT *pResult)
{
	CSimpleEdit_BSecCode.SetFocus();
	dealSendBuyEntrust();
}

void CCreditTradeView::OnEditResturnCodeSell(NMHDR *pNMHDR, LRESULT *pResult)
{
	CSimpleEdit_SEntrustPrice.SetFocus();
}

void CCreditTradeView::OnEditResturnEntrustPriceSell(NMHDR *pNMHDR, LRESULT *pResult)
{
	CSimpleEdit_SEntrustAmount.SetFocus();
}

void CCreditTradeView::OnEditResturnEntrustAmountSell(NMHDR *pNMHDR, LRESULT *pResult)
{
	CSimpleEdit_SSecCode.SetFocus();
	dealSendSellEntrust();
}

void CCreditTradeView::OnKillfocusBSecCode()
{
	/*��Ʊ������enchange��killfocus���ߴ�����Ʊ���ֻ������ںϷ��Ĺ�Ʊ�������""�����ƽʱʹ��У���Ƿ�Ϊ�ռ�����Ϸ���
	��Ҳ��ζ�Ž������Ϣ��Ӧ���Ʊ����ת�г����붼�����ܱ�������ί��������Ǽ��ϣ����ּ�������־����Assert����*/
	/*killfocusֻ����У���Ʊ�����Ƿ�Ϸ�(���enchangeû�ﵽ�ض�λ����killcocu��bug)�����Ϸ��ͽ��ж�Ӧ����*/
	DealKillFocusSecCode(true);
}

void CCreditTradeView::OnKillfocusSSecCode()
{
	DealKillFocusSecCode(false);
}


void CCreditTradeView::DealKillFocusSecCode(bool bBuy)
{
	CString secCode;
	CString marketCode;
	if (bBuy)
	{
		CSimpleEdit_BSecCode.GetWindowText(secCode);
	}
	else
	{
		CSimpleEdit_SSecCode.GetWindowText(secCode);
	}
	if (G.SPtr_CData->SecCode2MarketCode(secCode, marketCode) == false)
	{
		if (bBuy)
		{
			DealIllegal_BSecCode();
		}
		else
		{
			DealIllegal_SSecCode();
		}
	}
}

void CCreditTradeView::OnKillfocusBDefaultBalance()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	dealDefaultBalanceChanged();
}

/*ί�м۸����仯������ԭ�е�ί��������ֻ���¼��������򡢿��������ί�н��*/
void CCreditTradeView::OnKillfocusBEntrustPrice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	dealBuyEntrustPriceChanged();
}

/*��ģ���ί������killFocus��������Ҫ�޸���ģ���ί�н���*/
void CCreditTradeView::OnKillfocusBEntrustAmount()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (G.VerifybEmpty_SecCode(&CSimpleEdit_BSecCode) == true)
	{
		return;
	}
	if (G.VerifyEntrustAmount(true, &CSimpleEdit_BEntrustAmount) == false)
	{
		CSimpleEdit_BEntrustAmount.SetWindowText(_T(""));
		CSimpleStatic_BEntrustBalance_2.SetWindowText(_T(""));
		return;
	}
	/*ί�н��*/
	G.SetEntrustBalance(&CSimpleEdit_BEntrustPrice, &CSimpleEdit_BEntrustAmount, &CSimpleStatic_BEntrustBalance_2);
}

/*��ģ���ί�м۸�killFocus��������ֻ�޸�ί�н���*/
void CCreditTradeView::OnKillfocusSEntrustPrice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	dealSellEntrustPriceChanged();
}


/*��ģ���ί������killFocus��������Ҫ�޸���ģ���ί�н���*/
void CCreditTradeView::OnKillfocusSEntrustAmount()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (G.VerifybEmpty_SecCode(&CSimpleEdit_SSecCode) == true)
	{
		return;
	}
	if (G.VerifyEntrustAmount(false, &CSimpleEdit_SEntrustAmount) == false)
	{
		CSimpleEdit_SEntrustAmount.SetWindowText(_T(""));
		CSimpleStatic_SEntrustBalance_2.SetWindowText(_T(""));
		return;
	}
	/*ί�н��*/
	G.SetEntrustBalance(&CSimpleEdit_SEntrustPrice, &CSimpleEdit_SEntrustAmount, &CSimpleStatic_SEntrustBalance_2);
}

void CCreditTradeView::OnClickBuyLimit(NMHDR *pNmhdr, LRESULT *pResult)
{
	CString s_str;
	CSimpleStatic_BigCanBuy_2.GetWindowText(s_str);
	CSimpleEdit_BEntrustAmount.SetWindowText(s_str);
	*pResult = 0;
}

void CCreditTradeView::RedrawTradeModule(bool bBuy, CString SecCode)
{
	CCreditTradeView* pCreditTradeView = (CCreditTradeView*)GetViewByID(ID_viw_creditTrade);
	if (G.IsWindowValid(pCreditTradeView))
	{
		if (!G.InspectbRedraw(SecCode, pCreditTradeView->GetSecCode(bBuy)))
		{
			return;
		}

		CString MarketCode;
		if (pCreditTradeView->ensureSecCodeMarket(true, bBuy, SecCode, MarketCode, pCreditTradeView->GetEntrustType(bBuy)) == true)
		{
			pCreditTradeView->DealTradeModule(bBuy, SecCode, MarketCode);
		}
		else
		{
			MessageBox("��Ʊ���벻�Ϸ�", "��ʾ", MB_OK);
		}
	}
}












