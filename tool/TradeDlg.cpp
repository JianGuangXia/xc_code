#include "TradeDlg.h"
#include "./MyCtrl/FontSet.h"

HFONT CTradeDlg::s_hFontOrder = NULL;
HFONT CTradeDlg::s_hFontGrid = NULL;
HFONT CTradeDlg::s_hFontTab = NULL;
HFONT CTradeDlg::s_hFontTabSel = NULL;

CTradeDlg::CTradeDlg()
{
	s_ConfigPath = ConfigPath;
	bCreate_TradeDlg = false;
	bShowAll = true;
	m_strStyle = GetFontStyle();
	m_hMainViewWnd = nullptr;
}

bool CTradeDlg::initCaption(const unsigned int CtrID, const CString &s_caption)
{
	unsigned int fontSize;
	ptree pt;
	try {
		read_xml(s_ConfigPath, pt);
		fontSize = pt.get<int>("content.FontSize");
	}
	catch (std::exception& e)
	{
		LOG(ERROR) << "Error:" << e.what();
		ExceptionInterrupt;
		return false;
	}
	unsigned int size = fontSize*1.5;
	size *= 10;
	font_Caption.CreatePointFont(size, "MS Shell Dlg");//�ؼ�1		
	GetDlgItem(CtrID)->SetWindowText(s_caption);
	GetDlgItem(CtrID)->SetFont(&font_Caption, true); //���Ŀؼ�1������
	return true;
}

bool CTradeDlg::initBDirectlyOrder(const string &treePath,const unsigned int &CtrID)
{
	ptree pt;
	try {
		read_xml(s_ConfigPath, pt);
		bDirectlyOrder = pt.get<bool>(treePath);
	}
	catch (std::exception& e)
	{
		LOG(ERROR) << "Error:" << e.what();
		ExceptionInterrupt;
		return false;
	}

	switch (bDirectlyOrder)
	{
	case false://δ��ѡ��
		((CButton*)GetDlgItem(CtrID))->SetCheck(BST_UNCHECKED);
		break;
	case true://��ѡ��ѡ��
		((CButton*)GetDlgItem(CtrID))->SetCheck(BST_CHECKED);
		break;
	}
	return true;
}

bool CTradeDlg::init_bStockAssociated(const string &treePath)
{
	ptree pt;
	try {
		read_xml(s_ConfigPath, pt);
		bStockAssociated = pt.get<bool>(treePath);
	}
	catch (std::exception& e)
	{
		LOG(ERROR) << "Error:" << e.what();
		ExceptionInterrupt;
		return false;
	}
	return true;
}

void CTradeDlg::InitialAutoCheck(CSimpleCheckbox* pCheck, string str)
{
	if (IsWindowValid(pCheck))
	{
		ptree pt;
		try {
			read_xml(s_ConfigPath, pt);
			bAutoRoll = pt.get<bool>(str);
		}
		catch (std::exception& e)
		{
			LOG(ERROR) << "Error:" << e.what();
			ExceptionInterrupt;
			return;
		}

		pCheck->SetCheck(bAutoRoll);
	}
}

void CTradeDlg::InitialRMouseOrderCheck(CSimpleCheckbox* pCheck, string str)
{
	if (IsWindowValid(pCheck))
	{
		ptree pt;
		try {
			read_xml(s_ConfigPath, pt);
			bDirectlyOrder = pt.get<bool>(str);
		}
		catch (std::exception& e)
		{
			LOG(ERROR) << "Error:" << e.what();
			ExceptionInterrupt;
			return;
		}

		pCheck->SetCheck(bDirectlyOrder);
	}
}


void CTradeDlg::initLayout_BEntrustQueue()
{
	obj_CListCtrlInfo.str_vector.clear();
	obj_CListCtrlInfo.str_vector.push_back("��һ");
	obj_CListCtrlInfo.str_vector.push_back("");
	obj_CListCtrlInfo.str_vector.push_back("");
	obj_CListCtrlInfo.str_vector.push_back("");
	obj_CListCtrlInfo.str_vector.push_back("");
	obj_CListCtrlInfo.str_vector.push_back("");
	obj_CListCtrlInfo.str_vector.push_back("����");
	UInt_32 dwStyle = GainNormalExtendedStyle(CListCtrl_BEntrustQueue)& ~LVS_EX_GRIDLINES;
	uniformClistCtrl(obj_CListCtrlInfo, CListCtrl_BEntrustQueue, dwStyle);
}

void CTradeDlg::initLayout_SEntrustQueue()
{
	obj_CListCtrlInfo.str_vector.clear();
	obj_CListCtrlInfo.str_vector.push_back("��һ");
	obj_CListCtrlInfo.str_vector.push_back("");
	obj_CListCtrlInfo.str_vector.push_back("");
	obj_CListCtrlInfo.str_vector.push_back("");
	obj_CListCtrlInfo.str_vector.push_back("");
	obj_CListCtrlInfo.str_vector.push_back("");
	obj_CListCtrlInfo.str_vector.push_back("����");
	UInt_32 dwStyle = GainNormalExtendedStyle(CListCtrl_SEntrustQueue)& ~LVS_EX_GRIDLINES;
	uniformClistCtrl(obj_CListCtrlInfo, CListCtrl_SEntrustQueue, dwStyle);
}

void CTradeDlg::initLayout_EntrustEach()
{
	obj_CListCtrlInfo.str_vector.clear();
	obj_CListCtrlInfo.str_vector.push_back("ʱ��");
	obj_CListCtrlInfo.str_vector.push_back(Name_EntrustNo);
	obj_CListCtrlInfo.str_vector.push_back("�۸�");
	obj_CListCtrlInfo.str_vector.push_back("����");
	obj_CListCtrlInfo.str_vector.push_back("���");
	obj_CListCtrlInfo.str_vector.push_back(Name_EntrustBs);
	UInt_32 dwStyle = GainNormalExtendedStyle(CListCtrl_EntrustEach)& ~LVS_EX_GRIDLINES;
	uniformClistCtrl(obj_CListCtrlInfo, CListCtrl_EntrustEach, dwStyle);
}

void CTradeDlg::initLayout_CustomPool()
{
	obj_CListCtrlInfo.str_vector.clear();
	obj_CListCtrlInfo.str_vector.push_back("�г�");
	obj_CListCtrlInfo.str_vector.push_back("��Ʊ����");
	obj_CListCtrlInfo.str_vector.push_back(Name_SecCode);
	UInt_32 dwStyle = GainNormalExtendedStyle(CListCtrl_CustomPool) | LVS_EX_CHECKBOXES;
	uniformClistCtrl(obj_CListCtrlInfo, CListCtrl_CustomPool, dwStyle);
}

void CTradeDlg::initRefreshAlert(const unsigned int CtrID)
{
	( (CButton *)GetDlgItem(CtrID)) ->SetCheck(BST_CHECKED);
}

void CTradeDlg::RedrawCustomPool(string s_Path, CGridCtrlEx* pCustomPool)
{
	if (!IsWindowValid(pCustomPool))
	{
		return;
	}
	map<CString, CCustomInfo> M_CustomPool;//key stock_code value stock_name
	if (File2MCustomPool(s_Path, M_CustomPool) == false)
	{
		return;
	}
	pCustomPool->SetRowCount(M_CustomPool.size() + 1);
	int i = 0;
	for (auto iter = M_CustomPool.begin(); iter != M_CustomPool.end(); iter++)
	{
		CString s_str;
		// �г�
		switch (tool::find_enumMarketCode(string(iter->second.MarketCode)))
		{
		case enumSSE:
			s_str = "�Ϻ�";
			break;
		case enumSZSE:
			s_str = "����";
			break;
		default:
			ExceptionInterrupt;
			LOG(ERROR) << "abnormal MarketCode";
			break;
		}
		pCustomPool->SetCellCheckBox(i + 1, 0);
		pCustomPool->SetItemEditable(i + 1, 0, TRUE);

		pCustomPool->SetItemTextEx(i + 1, 0, s_str);

		//��Ʊ����
		pCustomPool->SetItemTextEx(i + 1, 1, iter->second.stock_name);
		//��Ʊ����
		pCustomPool->SetItemTextEx(i + 1, 2, iter->second.stock_code);
		i++;
	}
	//pCustomPool->MySetSelectedRangeEx(-1, -1, -1, -1, TRUE);
	pCustomPool->Invalidate();
}

bool CTradeDlg::File2MCustomPool(string s_Path, map<CString, CCustomInfo> &M_CustomPool)
{
	std::string s_FileContent;
	tool::File2String(s_Path, s_FileContent);
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(s_FileContent, root, false))
	{
		int Sum = root["CustomInfo"].size();
		if (Sum >= Max_Monitor)
		{
			ExceptionInterrupt;
			LOG(ERROR) << "Ԥ����������";
			return false;
		}
		for (int i = 0; i < Sum; ++i)
		{
			CCustomInfo obj_CCustomInfo;
			obj_CCustomInfo.stock_code = root["CustomInfo"][i]["stock_code"].asString().c_str();
			obj_CCustomInfo.stock_name = root["CustomInfo"][i]["stock_name"].asString().c_str();
			obj_CCustomInfo.MarketCode = root["CustomInfo"][i]["MarketCode"].asString().c_str();
			M_CustomPool.insert(make_pair(obj_CCustomInfo.stock_code, obj_CCustomInfo));
		}
	}
	else
	{
		if ("" == s_FileContent)
		{
			return false;
		}
		else
		{
			ExceptionInterrupt;
			LOG(ERROR) << "prase fail:" << s_FileContent;
			return false;
		}
	}
	return true;
}

void CTradeDlg::DealClickedRemovePick(string s_Path, CGridCtrlEx* pCustomPool)
{
	if (!IsWindowValid(pCustomPool))
	{
		return;
	}
	map<CString, CCustomInfo> Map_CustomPool;
	if (File2MCustomPool(s_Path, Map_CustomPool) == false)
	{
		return;
	}
	int nRowCount = pCustomPool->GetRowCount();
	for (int nRow = 1; nRow < nRowCount; nRow++)
	{
		if (pCustomPool->GetCellCheck(nRow, 0))
		{
			CString stock_code = pCustomPool->GetItemText(nRow, 2);
			Map_CustomPool.erase(stock_code);
		}
	}
	/*д�����ļ�*/
	Json::Reader reader;
	Json::Value root;
	string s_FileContent;
	tool::File2String(s_Path, s_FileContent);

	if (reader.parse(s_FileContent, root, false))
	{
		root.removeMember("CustomInfo");
		for (auto iter = Map_CustomPool.begin(); iter != Map_CustomPool.end(); iter++)
		{
			Json::Value val;
			val["stock_code"] = Json::Value(iter->second.stock_code);
			val["stock_name"] = Json::Value(iter->second.stock_name);
			val["MarketCode"] = Json::Value(iter->second.MarketCode);
			root["CustomInfo"].append(Json::Value(val));
		}

		Json::StyledWriter sw;
		std::string res_str = sw.write(root);
		tool::string2File(s_Path, res_str);
	}
	else
	{
		ExceptionInterrupt;
		LOG(ERROR) << "parse fail:" << s_FileContent;
		return;
	}
	/*�ػ���ѡ��*/	
	RedrawCustomPool(s_Path, pCustomPool);
}

bool CTradeDlg::DealInsertStock(CSimpleEdit* pEditCode, string s_Path, CGridCtrlEx* pCustomPool)
{
	if (!IsWindowValid(pEditCode) || !IsWindowValid(pCustomPool))
	{
		return false;
	}
	CCustomInfo obj_CCustomInfo;
	/*У����Ӵ����Ƿ�Ϸ�*/
	if (GainAlertInfo(pEditCode, obj_CCustomInfo) == false)
	{
		return false;
	}
	/*д����Ӵ���*/
	if (WriteAlertInfo(s_Path, obj_CCustomInfo) == false)
	{
		return false;
	}
	/*�ػ���ѡ��*/
	RedrawCustomPool(s_Path, pCustomPool);
	return true;
}

void CTradeDlg::DealClickedRefreshAlert(CSimpleCheckbox* pRefresh)
{
	if (IsWindowValid(pRefresh))
	{
		bRefreshAlert = pRefresh->GetCheck();		
	}
}

bool CTradeDlg::save_bStockAssociated(const string &treePath, const unsigned int &CtrID)
{
	ptree pt;
	try {
		read_xml(s_ConfigPath, pt, xml_parser::trim_whitespace);
		CString s_tmp;
		if (((CButton*)GetDlgItem(CtrID))->GetCheck() == BST_CHECKED)
		{
			s_tmp = "1";
		}
		else
		{
			s_tmp = "0";
		}
		pt.put(treePath, s_tmp);
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


bool CTradeDlg::SubscribePosition()
{
	interface_struct_Subscribe sSubscribe1;
	sSubscribe1.Dyna_flag = true;
	socket_struct_SubscribeDetail SubList1[MaxSize];
	int Sum_Subscribe = 0;
	CString MarketCode;

	_Account obj_MAccount;
	_Account::iterator iter_MAccount;
	if (true == SPtr_CData->GetMAccount(SPtr_CData->fund_account, obj_MAccount))
	{
		for (iter_MAccount = obj_MAccount.begin(); iter_MAccount != obj_MAccount.end(); iter_MAccount++)
		{
			_Position obj_MPosition;
			if (SPtr_CData->GetMPosition(SPtr_CData->fund_account, iter_MAccount->first, obj_MPosition) == false)
			{
				ErrorLog("GetMPosition fail");
				continue;
			}
			if (SPtr_CData->Account2Market(SPtr_CData->fund_account, iter_MAccount->first,MarketCode) == false)
			{
				ErrorLog("Account2Market fail");
				continue;
			}

			for (auto iter = obj_MPosition.begin(); iter != obj_MPosition.end(); iter++)
			{
				strcpy(SubList1[Sum_Subscribe].MarketCode, MarketCode);
				strcpy(SubList1[Sum_Subscribe].SecCode, iter->second->stock_code);
				Sum_Subscribe++;
			}
			SendSubscribeMarket(false, MarketCode, IDMarket_SubscribePosition, &sSubscribe1, SubList1, Sum_Subscribe);/*fixing ������ȯ��������*/
			memset(SubList1, 0,sizeof(socket_struct_SubscribeDetail)*Sum_Subscribe);
			Sum_Subscribe = 0;
		}
	}
	else
	{
		ErrorLog("GetAccountMap fail");
		return false;
	}

	return true;
}

bool CTradeDlg::Subscribed_SingleStock(bool bLock, const CString &MarketCode, const CString &SecCode, bool bEntrustQueue, bool bEntrustEach)
{
	interface_struct_Subscribe sSubscribe1;
	sSubscribe1.Dyna_flag = false;
	if (true == bEntrustQueue)
	{
		sSubscribe1.DepthOrder_flag = true;
	}
	else
	{
		sSubscribe1.DepthOrder_flag = false;
	}
	sSubscribe1.Depth_flag = true;
	sSubscribe1.EachDeal_flag = false;
	if (true == bEntrustEach)
	{
		sSubscribe1.EachOrder_flag = true;
	}
	else
	{
		sSubscribe1.EachOrder_flag = false;
	}

	socket_struct_SubscribeDetail SubList1[MaxSize];
	if (sSubscribe1.EachOrder_flag == true)
	{
		if (SPtr_CData->ClearEntrustEach(MarketCode, SecCode) == false)
		{
			ExceptionInterrupt;
			LOG(ERROR) << "ClearEntrustEach fail";
			Sleep(1000);
		}
	}

	strcpy(SubList1[0].MarketCode, MarketCode);
	strcpy(SubList1[0].SecCode, SecCode);
	SendSubscribeMarket(bLock,MarketCode, IDMarket_SubscribeSingle, &sSubscribe1, SubList1, 1);
	return true;
}

bool CTradeDlg::SendSubscribeMarket(bool bLock,const CString MarketCode, UInt_64 RefID, interface_struct_Subscribe* pSubscribe,
	socket_struct_SubscribeDetail SubList[MaxSize], int SubSize)
{
	if (SubSize < 1)
	{
		return true;
	}
	int ret;
	switch (tool::find_enumMarketCode(string(MarketCode)))
	{
	case enumSSE:
	{
		ret = pCApiFun->Api_Market_SSE->Subscribe(RefID, pSubscribe, SubList, SubSize);
		break;
	}
	case enumSZSE:
	{
		ret = pCApiFun->Api_Market_SZSE->Subscribe(RefID, pSubscribe, SubList, SubSize);
		break;
	}
	default:
		LOG(ERROR) << "abnormal MarketCode";
		ExceptionInterrupt;
		return false;
		break;
	}
	if (ret < 0)
	{
		LOG(ERROR) << "SendSubscribeMarket fail! ret:" << ret;
		ExceptionInterrupt;
		return false;
	}
	if (true == bLock)
	{
		/*���������lock unlockӦ����һ�ԣ�������������ģ��������ԣ�������ģ�������unlock��ȴֻ�е���ģ��lock��ʹlock��Ч*/
		ResetEvent(SPtr_CData->Subscribe_Event);
		/*�ȴ���Ϊ�˱�֤����������Ѵﵽ*/
		UInt_32 ret_Wait = WaitForSingleObject(SPtr_CData->Subscribe_Event, TimeShortest);
		bool b_ret;
		DealReturnValue_WaitForSingleObject(ret_Wait, b_ret);
	}
	return true;
}

bool CTradeDlg::SendAllOrder(vector<string> &Vec_Dismantling, CApiFun *pCApiFun, const int ApiType,
	const string &s_Fun, PtrData &SPtr_CData)
{
	int OrderInterval = GainSleepTime(SPtr_CData);
	int Size = Vec_Dismantling.size();
	if (Size == 1)//����ָ��
	{
		string s_str;
		if (modifyEntrustAmount(s_str, s_Fun, Vec_Dismantling[0]) == true)
		{
			if (tool::SendOrder(pCApiFun, ApiType, s_str, SPtr_CData) < 0)
			{
				ExceptionInterrupt;
				LOG(ERROR) << "SendOrder fail";
				return false;
			}
		}
	}
	else
	{
		std::thread t_ErrorInfo(Thread_SendAllOrder, OrderInterval, Vec_Dismantling, pCApiFun,
			ApiType, s_Fun, SPtr_CData);
		t_ErrorInfo.detach();
	}
	return true;
}

void CTradeDlg::Thread_SendAllOrder(int OrderInterval, vector<string> Vec_Dismantling, CApiFun *pCApiFun,
	const int ApiType, const string s_Fun, PtrData SPtr_CData)
{
	bool b_ret;
	DWORD ret_Event = WaitForSingleObject(SPtr_CData->Event_SendAllOrder, INFINITE);
	DealReturnValue_WaitForSingleObject(ret_Event, b_ret);
	if (b_ret == false)
	{
		return;
	}
	int Size = Vec_Dismantling.size();
	Json::Reader reader;
	Json::Value root;
	for (int i = 0; i < Size; i++)
	{
		string s_str;
		//���ַ����ж�ȡ����
		if (reader.parse(s_Fun, root))
		{
			root["entrust_amount"] = Vec_Dismantling[i];
			s_str = root.toStyledString();
			//cerr << "now tid is " << GetCurrentThreadId() << endl;
			if (tool::SendOrder(pCApiFun, ApiType, s_str, SPtr_CData) < 0)
			{
				ExceptionInterrupt;
				LOG(ERROR) << "SendOrder fail";
				return;
			}
			if (0 != OrderInterval)
			{
				Sleep(OrderInterval);
			}
		}
		else
		{
			string s_error = "parse fail:";
			s_error += s_Fun;
			ErrorLog(s_error);
			return;
		}
	}
	SetEvent(SPtr_CData->Event_SendAllOrder);
}


int CTradeDlg::GainSleepTime(PtrData &SPtr_CData)
{
	/*�µ����Ϊ0��ʱ�򣬿ͻ��˲���Ч�µ������ÿs�µ���������Ϊ0��ʱ��ȡ�������ֵ*/
	int OrderInterval = SPtr_CData->OrderInterval;
	if (0 == OrderInterval)
	{
		return 0;
	}
	int Frequency = SPtr_CData->Frequency;
	int Space = 1 * 1000 / Frequency;
	int max;
	if (Space > OrderInterval)
	{
		max = Space;
	}
	else
	{
		max = OrderInterval;
	}
	return (int)(1.5*max);
}

bool CTradeDlg::modifyEntrustAmount(string &s_dst, string s_src, string entrust_amount)
{
	Json::Reader reader;
	Json::Value root;

	//���ַ����ж�ȡ����
	if (reader.parse(s_src, root))
	{
		string s_str;
		root["entrust_amount"] = entrust_amount;
		s_dst = root.toStyledString();
	}
	else
	{
		string s_error = "parse fail:";
		s_error += s_src;
		ErrorLog(s_error);
		return false;
	}
	return true;
}

bool CTradeDlg::GainAlertInfo(const int ID_InsertStock, CCustomInfo &obj_CCustomInfo)
{
	GetDlgItem(ID_InsertStock)->GetWindowText(obj_CCustomInfo.stock_code);
	if (SPtr_CData->SecCode2MarketCode(obj_CCustomInfo.stock_code, obj_CCustomInfo.MarketCode) == false)
	{
		return false;
	}
	/*������ѡ�ء�Ԥ���ء��ػ���ѡ��map�������ļ�*/
	CSecurity obj_CSecurity;
	if (SPtr_CData->GetSecurity(obj_CCustomInfo.MarketCode, obj_CCustomInfo.stock_code, obj_CSecurity) == false)
	{
		ExceptionInterrupt;
		LOG(ERROR) << "GetSecurity fail";
		return false;
	}
	obj_CCustomInfo.stock_name = obj_CSecurity.stock_name;
	return true;
}

bool CTradeDlg::GainAlertInfo(CSimpleEdit* pEditCode, CCustomInfo &obj_CCustomInfo)
{
	if (!IsWindowValid(pEditCode))
	{
		return false;
	}
	pEditCode->GetWindowText(obj_CCustomInfo.stock_code);
	if (SPtr_CData->SecCode2MarketCode(obj_CCustomInfo.stock_code, obj_CCustomInfo.MarketCode) == false)
	{
		return false;
	}
	CSecurity obj_CSecurity;
	if (SPtr_CData->GetSecurity(obj_CCustomInfo.MarketCode, obj_CCustomInfo.stock_code, obj_CSecurity) == false)
	{
		ExceptionInterrupt;
		LOG(ERROR) << "GetSecurity fail";
		return false;
	}
	obj_CCustomInfo.stock_name = obj_CSecurity.stock_name;
	return true;
}

bool CTradeDlg::WriteAlertInfo(string s_Path, CCustomInfo &obj_CCustomInfo)
{
	Json::Reader reader;
	Json::Value root;
	string s_FileContent;
	tool::File2String(s_Path, s_FileContent);

	/*s_strΪ�յ�ʱ��������Ҳ���ǽ���ʧ��({}�����ɹ�)��ʵ����Ҳ��ȷ�ǽ���ʧ��*/
	if (reader.parse(s_FileContent, root, false))
	{
		Json::Value val;
		val["stock_code"] = Json::Value(obj_CCustomInfo.stock_code);
		val["stock_name"] = Json::Value(obj_CCustomInfo.stock_name);
		val["MarketCode"] = Json::Value(obj_CCustomInfo.MarketCode);
		root["CustomInfo"].append(Json::Value(val));
		Json::StyledWriter  sw;
		std::string res_str = sw.write(root);
		tool::string2File(s_Path, res_str);
	}
	else
	{
		if ("" == s_FileContent)
		{
			Json::Value val;
			val["stock_code"] = Json::Value(obj_CCustomInfo.stock_code);
			val["stock_name"] = Json::Value(obj_CCustomInfo.stock_name);
			val["MarketCode"] = Json::Value(obj_CCustomInfo.MarketCode);
			root["CustomInfo"].append(Json::Value(val));
			Json::StyledWriter  sw;
			std::string res_str = sw.write(root);
			tool::string2File(s_Path, res_str);
		}
		else
		{
			ExceptionInterrupt;
			LOG(ERROR) << "parse fail:" << s_FileContent;
			return false;
		}
	}
	return true;
}
bool CTradeDlg::IsSubscribed(CString stock_account, CString SecCode)
{
	_Security obj_MSecurity;
	if (SPtr_CData->GetMSecurity(SPtr_CData->fund_account, stock_account, obj_MSecurity) == false)
	{
		LOG(ERROR) << "GetMSecurity fail";
		ExceptionInterrupt;
		return true;
	}

	auto iter = obj_MSecurity.find(SecCode);
	if (iter == obj_MSecurity.end())
	{
		return false;
	}
	return true;
}

bool CTradeDlg::GuaranteedSubscription(bool bLock, CString MarketCode, CString SecCode, bool bEntrustQueue, bool bEntrustEach)
{
	UnSubscribe_All(MarketCode);
	Subscribed_SingleStock(bLock,MarketCode, SecCode, bEntrustQueue, bEntrustEach);
	return true;
}

void CTradeDlg::DealSubscribe(bool bLock, CString MarketCode, CString SecCode, bool bEntrustQueue, bool bEntrustEach)
{
	GuaranteedSubscription(bLock,MarketCode, SecCode, bEntrustQueue, bEntrustEach);
	CListCtrl_BEntrustQueue.SetItemCount(0);//���ԭ������
	CListCtrl_SEntrustQueue.SetItemCount(0);
	CListCtrl_EntrustEach.SetItemCount(0);
	SetClistColoumnText(CListCtrl_BEntrustQueue, 1, "");
	SetClistColoumnText(CListCtrl_SEntrustQueue, 1, "");
}

void CTradeDlg::DealSubscribe(bool bLock, CString MarketCode, CString SecCode, bool bEntrustQueue, bool bEntrustEach, CGridCtrlEx* pGridBuy1, CGridCtrlEx* pGridSell1, CGridCtrlEx* pGridOrderEach)
{
	if (IsWindowValid(pGridBuy1))
	{
		pGridBuy1->SetRowCount(1);
		m_strGearBuy1.Empty();
		m_strNumOrdersBuy1.Empty();
	}
	if (IsWindowValid(pGridSell1))
	{
		pGridSell1->SetRowCount(1);
		m_strGearSell1.Empty();
		m_strNumOrdersSell1.Empty();
	}
	if (IsWindowValid(pGridOrderEach))
	{
		pGridOrderEach->SetRowCount(1);
	}
	GuaranteedSubscription(bLock, MarketCode, SecCode, bEntrustQueue, bEntrustEach);
	
}

bool CTradeDlg::UnSubscribe_All(CString MarketCode)
{
	interface_struct_Subscribe sCancel1;
	sCancel1.Dyna_flag = false;//����ֻ���ó��˿���������������顢ϵͳ���ݴ����׻��ƿ������飬��ȡ�ί�ж��С����ί������
	sCancel1.DepthOrder_flag = true;//true�����޸����ֵ��ȫ��Ϊtrue
	sCancel1.Depth_flag = true;
	sCancel1.EachDeal_flag = true;
	sCancel1.EachOrder_flag = true;
	socket_struct_SubscribeDetail CanList[MaxSize];
	strcpy(CanList[0].MarketCode, "*");
	CXcMarketApi * pAPI_Unsubscribe = NULL;
	switch (tool::find_enumMarketCode(string(MarketCode)))
	{
	case enumSSE:
		pAPI_Unsubscribe = pCApiFun->Api_Market_SSE;
		break;
	case enumSZSE:
		pAPI_Unsubscribe = pCApiFun->Api_Market_SZSE;;
		break;
	default:
		ExceptionInterrupt;
		LOG(ERROR) << "abnormal MarketCode";
		break;
	}
	if (pAPI_Unsubscribe->Cancel(IDMarket_UnSubscribe, &sCancel1, CanList, 1) < 0)
	{
		ExceptionInterrupt;
		LOG(ERROR) << "API_Cancel fail";
		return false;
	}
	return true;

}

bool CTradeDlg::DrawDepth(const CString &MarketCode, const CString &SecCode,
	const int grade, const int IDC_Price, const int IDC_Quantity)
{
	CString s_str;
	CDepth obj_CDepth;
	if (SPtr_CData->GetDepth(MarketCode, SecCode, grade, obj_CDepth) == false)
	{
	}
	s_str.Format(_T("%0.2f"), obj_CDepth.Price);
	GetDlgItem(IDC_Price)->SetWindowText(s_str);
	s_str.Format(_T("%u"), obj_CDepth.Quantity);
	GetDlgItem(IDC_Quantity)->SetWindowText(s_str);
	return true;
}

bool CTradeDlg::DrawDepth(const CString &MarketCode, const CString &SecCode,
	const int grade, CSimpleStatic* pPrice, CSimpleStatic* pQuantity)
{
	CString s_str;
	CDepth obj_CDepth;
	if (SPtr_CData->GetDepth(MarketCode, SecCode, grade, obj_CDepth) == false)
	{
	}
	s_str.Format(_T("%0.2f"), obj_CDepth.Price);
	if (IsWindowValid(pPrice))
	{
		pPrice->SetWindowText(s_str);
	}
	s_str.Format(_T("%u"), obj_CDepth.Quantity);
	if (IsWindowValid(pQuantity))
	{
		pQuantity->SetWindowText(s_str);
	}
	return true;
}

bool CTradeDlg::DrawDepth(const CString &MarketCode, const CString &SecCode,
	const int grade, CSimpleButton* pPrice, CSimpleStatic* pQuantity)
{
	CString s_str;
	CDepth obj_CDepth;
	if (SPtr_CData->GetDepth(MarketCode, SecCode, grade, obj_CDepth) == false)
	{
	}
	s_str.Format(_T("%0.2f"), obj_CDepth.Price);
	if (IsWindowValid(pPrice))
	{
		pPrice->SetWindowText(s_str);
	}
	s_str.Format(_T("%u"), obj_CDepth.Quantity);
	if (IsWindowValid(pQuantity))
	{
		pQuantity->SetWindowText(s_str);
	}
	return true;
}

void CTradeDlg::OnClickedBDirectlyOrder(const int ID_bDirectlyOrder, const string &NodePath)
{
	switch (bDirectlyOrder)
	{
	case true:
		bDirectlyOrder = false;
		((CButton*)GetDlgItem(ID_bDirectlyOrder))->SetCheck(BST_UNCHECKED);
		break;
	case false:
		((CButton*)GetDlgItem(ID_bDirectlyOrder))->SetCheck(BST_CHECKED);
		bDirectlyOrder = true;
		break;
	}

	ptree pt;
	try {
		read_xml(s_ConfigPath, pt, xml_parser::trim_whitespace);
		CString s_tmp;
		if (true == bDirectlyOrder)
		{
			s_tmp = "1";
		}
		else
		{
			s_tmp = "0";
		}
		pt.put(NodePath, s_tmp);
		xml_writer_settings<string> settings('\t', 1, "GB2312");
		write_xml(s_ConfigPath, pt, std::locale(), settings);
	}
	catch (std::exception& e)
	{
		LOG(ERROR) << "Error:" << e.what();
		ExceptionInterrupt;
		return;
	}
}

void CTradeDlg::OnClickedBDirectlyOrder(CSimpleCheckbox* pRMouseOrder, const string &NodePath)
{
	if (!IsWindowValid(pRMouseOrder))
	{
		return;
	}
	bDirectlyOrder = pRMouseOrder->GetCheck();

	ptree pt;
	try {
		read_xml(s_ConfigPath, pt, xml_parser::trim_whitespace);
		CString s_tmp;
		if (true == bDirectlyOrder)
		{
			s_tmp = "1";
		}
		else
		{
			s_tmp = "0";
		}
		pt.put(NodePath, s_tmp);
		xml_writer_settings<string> settings('\t', 1, "GB2312");
		write_xml(s_ConfigPath, pt, std::locale(), settings);
	}
	catch (std::exception& e)
	{
		LOG(ERROR) << "Error:" << e.what();
		ExceptionInterrupt;
		return;
	}
}

bool CTradeDlg::OnClickedbStockAssociated(const string &NodePath, const unsigned int &CtrID)
{
	switch (((CButton*)GetDlgItem(CtrID))->GetCheck())
	{
	case BST_CHECKED:
		bStockAssociated = true;
		break;
	case BST_UNCHECKED:
		bStockAssociated = false;
		break;
	default:
		break;
	}
	save_bStockAssociated(NodePath, CtrID);
	return true;
}

bool CTradeDlg::OnQRedrawFund(CListCtrl &CListCtrl_Funds,const int CtrlId)
{
	CFund obj_CFund;
	if (SPtr_CData->GetFund(SPtr_CData->fund_account, obj_CFund) == false)
	{
		LOG(ERROR) << "GetFund fail";
		ExceptionInterrupt;
	}
	int n = 1;//�ʽ��˻�ֻ��һ��
	CListCtrl_Funds.Invalidate(false);
	CListCtrl_Funds.SetItemCount(n);
	/*ͬ�����¿����ʽ� IDC_BEnableBalance*/
	CString s_str;
	s_str.Format("%0.2f", obj_CFund.enable_balance);
	GetDlgItem(CtrlId)->SetWindowText(s_str);
	return true;
}

void CTradeDlg::ClickedShowNoTrade(CSimpleCheckbox& chcShowNoTrade, CGridCtrlEx &gridCtrl)
{
	int state = chcShowNoTrade.GetCheck();
	switch (state)
	{
	case 0://δ��ѡ��
		bShowAll = true;
		OnRedrawOrder(&gridCtrl);
		break;
	case 1://��ѡ��ѡ��
		bShowAll = false;
		OnRedrawOrder(&gridCtrl);
		break;
	default:
		break;
	}
}

void CTradeDlg::OnRedrawOrder(CGridCtrlEx* pGrid)
{
	if (!IsWindowValid(pGrid))
	{
		return;
	}
	/*ÿ���ػ�ǰ��������ϴα����������յ��������´�tradedata�л�ȡ,����mfc��Ϣ���ƣ�ͬʱֻ��ִ��һ����˲�����ͬʱִ��*/
	_Order MOrder_Redraw;
	_Account obj_MAccount;
	_Account::iterator iter_MAccount;
	if (true == SPtr_CData->GetMAccount(SPtr_CData->fund_account, obj_MAccount))
	{
		for (iter_MAccount = obj_MAccount.begin(); iter_MAccount != obj_MAccount.end(); iter_MAccount++)
		{
			_Order obj_MOrder;
			_Order::iterator iter_MOrder;
			_Order::iterator iter_MOrder_Redraw;

			if (SPtr_CData->GetMOrder(SPtr_CData->fund_account, iter_MAccount->first, obj_MOrder) == false)
			{
				LOG(ERROR) << "GetMOrder fail";
				ExceptionInterrupt;
				continue;
			}
			if (obj_MOrder.find(0) != obj_MOrder.end())
			{
				LOG(ERROR) << "entrust_no is 0";
				ExceptionInterrupt;
			}
			if (obj_MOrder.size() > 0)
			{
				/*����checkbox*/
				for (iter_MOrder = obj_MOrder.begin(); iter_MOrder != obj_MOrder.end(); iter_MOrder++)
				{
					/*����order�е�ÿһ���ί�б���ǲ�����OrderCheckBox_map�У�û�о�insert��false�ķ���ʲô��������*/
					if (OrderCheckBox_map.find(iter_MOrder->first) == OrderCheckBox_map.end())
					{
						OrderCheckBox_map.insert(make_pair(iter_MOrder->first, false));
					}
				}

				/*ΪMOrder_Redraw��ֵ*/
				for (iter_MOrder = obj_MOrder.begin(); iter_MOrder != obj_MOrder.end(); iter_MOrder++)
				{
					if (bShowAll == false)
					{
						/*����ʾ�ɳ�*/
						if (iter_MOrder->second->entrust_status != WeiBao && iter_MOrder->second->entrust_status != YiBao
							&& iter_MOrder->second->entrust_status != BuCheng)
						{
							continue;
						}
					}

					/*���MOrder_Redraw��û����insert��������ø�ֵ������map�и�����Ĳ���������
					ͬʱinsetͬһ��key�����ǲ�ͬvalue�ļ�ֵ����ֵ�������滻*/
					iter_MOrder_Redraw = MOrder_Redraw.find(iter_MOrder->first);

					if (iter_MOrder_Redraw == MOrder_Redraw.end())
					{
						MOrder_Redraw.insert(make_pair(iter_MOrder->first, iter_MOrder->second));
					}
					else
					{
						iter_MOrder_Redraw->second = iter_MOrder->second;
					}

				}
			}
		}
	}
	else
	{
		LOG(ERROR) << "GetAccountMap fail";
		ExceptionInterrupt;
		return;
	}
	/*��map�е�����ת�Ƶ�Vector��*/
	VOrder_Redraw.clear();
	for (auto iter = MOrder_Redraw.rbegin(); iter != MOrder_Redraw.rend(); iter++)
	{
		VOrder_Redraw.push_back(iter->second);
	}

	pGrid->SetRowCount(VOrder_Redraw.size() + 1);
	if (pGrid->GetRowCount() <= 1)
	{
		return;
	}
	pGrid->MySetSelectedRangeEx(1, 0, 1, pGrid->GetColumnCount() - 1, TRUE);
	pGrid->Invalidate();
}

bool CTradeDlg::OnRedrawPosition(CGridCtrlEx* pGrid)
{
	if (!IsWindowValid(pGrid))
	{
		return false;
	}
	_Account obj_MAccount;
	_Account::iterator iter_MAccount;
	VPosition_Redraw.clear();
	if (true == SPtr_CData->GetMAccount(SPtr_CData->fund_account, obj_MAccount))
	{
		for (iter_MAccount = obj_MAccount.begin(); iter_MAccount != obj_MAccount.end(); iter_MAccount++)
		{
			_Position obj_MPosition;
			if (SPtr_CData->GetMPosition(SPtr_CData->fund_account, iter_MAccount->first, obj_MPosition) == false)
			{
				LOG(ERROR) << "GetMPosition fail";
				ExceptionInterrupt;
				continue;
			}

			for (auto iter = obj_MPosition.begin(); iter != obj_MPosition.end(); iter++)
			{
				VPosition_Redraw.push_back(iter->second);
			}
		}
	}
	else
	{
		LOG(ERROR) << "GetAccountMap fail";
		ExceptionInterrupt;
		return false;
	}
	pGrid->SetRowCount(VPosition_Redraw.size() + 1);
	pGrid->Invalidate();
	return true;
}

bool CTradeDlg::RedrawOrder(CListCtrl &CListCtrl_Order)
{
	/*ÿ���ػ�ǰ��������ϴα����������յ��������´�tradedata�л�ȡ,����mfc��Ϣ���ƣ�ͬʱֻ��ִ��һ����˲�����ͬʱִ��*/
	_Order MOrder_Redraw;
	_Account obj_MAccount;
	_Account::iterator iter_MAccount;
	if (true == SPtr_CData->GetMAccount(SPtr_CData->fund_account, obj_MAccount))
	{
		for (iter_MAccount = obj_MAccount.begin(); iter_MAccount != obj_MAccount.end(); iter_MAccount++)
		{
			_Order obj_MOrder;
			_Order::iterator iter_MOrder;
			_Order::iterator iter_MOrder_Redraw;

			if (SPtr_CData->GetMOrder(SPtr_CData->fund_account, iter_MAccount->first, obj_MOrder) == false)
			{
				LOG(ERROR) << "GetMOrder fail";
				ExceptionInterrupt;
				continue;
			}
			if (obj_MOrder.find(0) != obj_MOrder.end())
			{
				LOG(ERROR) << "entrust_no is 0";
				ExceptionInterrupt;
			}
			if (obj_MOrder.size() > 0)
			{
				/*����checkbox*/
				for (iter_MOrder = obj_MOrder.begin(); iter_MOrder != obj_MOrder.end(); iter_MOrder++)
				{
					/*����order�е�ÿһ���ί�б���ǲ�����OrderCheckBox_map�У�û�о�insert��false�ķ���ʲô��������*/
					if (OrderCheckBox_map.find(iter_MOrder->first) == OrderCheckBox_map.end())
					{
						OrderCheckBox_map.insert(make_pair(iter_MOrder->first, false));
					}
				}

				/*ΪMOrder_Redraw��ֵ*/
				for (iter_MOrder = obj_MOrder.begin(); iter_MOrder != obj_MOrder.end(); iter_MOrder++)
				{
					if (bShowAll == false)
					{
						/*����ʾ�ɳ�*/
						if (iter_MOrder->second->entrust_status != WeiBao && iter_MOrder->second->entrust_status != YiBao
							&& iter_MOrder->second->entrust_status != BuCheng)
						{
							continue;
						}
					}

					/*���MOrder_Redraw��û����insert��������ø�ֵ������map�и�����Ĳ���������
					ͬʱinsetͬһ��key�����ǲ�ͬvalue�ļ�ֵ����ֵ�������滻*/
					iter_MOrder_Redraw = MOrder_Redraw.find(iter_MOrder->first);

					if (iter_MOrder_Redraw == MOrder_Redraw.end())
					{
						MOrder_Redraw.insert(make_pair(iter_MOrder->first, iter_MOrder->second));
					}
					else
					{
						iter_MOrder_Redraw->second = iter_MOrder->second;
					}

				}
			}
		}
	}
	else
	{
		LOG(ERROR) << "GetAccountMap fail";
		ExceptionInterrupt;
		return false;
	}
	/*��map�е�����ת�Ƶ�Vector��*/
	VOrder_Redraw.clear();
	for (auto iter = MOrder_Redraw.rbegin(); iter != MOrder_Redraw.rend(); iter++)
	{
		VOrder_Redraw.push_back(iter->second);
	}
	//CListCtrl_Order.Invalidate(false);
	CListCtrl_Order.SetItemCount(VOrder_Redraw.size());
	CListCtrl_Order.EnsureVisible(0,FALSE);
	return true;
}

void CTradeDlg::OnRedrawAlert(CGridCtrlEx* pAlertGrid)
{
	if (false == bRefreshAlert || !IsWindowValid(pAlertGrid))
	{
		return;
	}
	bool bJump = false;
	int JumpIndex = 0;
	int index_vec_Alert = 0;
	bool bFirstRedraw = false;
	if (SPtr_CData->M_PreviousRedrawList.size() == 0)
	{
		bFirstRedraw = true;
	}

	_MSpecialAlert MSpecialAlert;
	_MSpecialAlert::reverse_iterator iter;
	vec_Alert.clear();
	int nIndexHighlighted = -1;
	GetMAlert_Special(MSpecialAlert);
	for (iter = MSpecialAlert.rbegin(); iter != MSpecialAlert.rend(); iter++)
	{
		if (iter->second->SecCode == highlightedSecCode)
		{
			nIndexHighlighted = vec_Alert.size();
		}
		vec_Alert.push_back(iter->second);
		index_vec_Alert++;
		if (true == bAutoRoll)
		{
			if (false == bFirstRedraw)
			{
				/*�������������Ĺ�Ʊ*/
				if (SPtr_CData->VerifybJump(iter->second->SecCode) == true)
				{
					highlightedSecCode = iter->second->SecCode;
					bJump = true;
					JumpIndex = index_vec_Alert;
#ifdef _DEBUG
					static int count = 0;
					cerr << "jump count:" << count << " jump coude:" << highlightedSecCode << endl;
					count++;
#endif
					if (SPtr_CData->obj_CAlertConfig.Template_Stock == CustomizePool)
					{
						PlaySound(TEXT(s_path_AlertSound.c_str()), NULL, SND_FILENAME | SND_ASYNC);
					}
				}
			}
		}
	}
	
	if (true == bAutoRoll)
	{
		fillPreviousRedrawList(MSpecialAlert);
	}

	int nSelected = 0;
	if (true == bJump)
	{
		nSelected = JumpIndex;
	}
	else
	{
		if (-1 == nIndexHighlighted)
		{
			nSelected = -1;
		}
		else
		{
			nSelected = nIndexHighlighted + 1;
		}

	}
	pAlertGrid->SetRowCount(vec_Alert.size() + 1);
	int nColCount = pAlertGrid->GetColumnCount();
	if (-1 == nSelected && bAutoRoll)
	{
		pAlertGrid->MySetEndVScroll();
	}
	if (bAutoRoll || pAlertGrid->MyGetEnableSelectHighlight())
	{
		pAlertGrid->MySetSelectedRangeEx(nSelected, 0, nSelected, nColCount - 1, TRUE);
	}

	pAlertGrid->Invalidate(FALSE);
} 

////void CTradeDlg::OnRedrawAlert(CGridCtrlEx* pAlertGrid)
////{
////	if (false == bRefreshAlert || !IsWindowValid(pAlertGrid))
////	{
////		return;
////	}
////	bool bJump = false;
////	int JumpIndex = 0;
////	int index_vec_Alert = 0;
////	bool bFirstRedraw = false;
////	if (SPtr_CData->M_PreviousRedrawList.size() == 0)
////	{
////		bFirstRedraw = true;
////	}
////	_MSpecialAlert MSpecialAlert;
////	_MSpecialAlert::reverse_iterator iter;
////	vec_Alert.clear();
////	if (GetMAlert_Special(MSpecialAlert) == false)
////	{
////		return;
////	}
////	for (iter = MSpecialAlert.rbegin(); iter != MSpecialAlert.rend(); iter++)
////	{
////		vec_Alert.push_back(iter->second);
////		index_vec_Alert++;
////		if (true == bAutoRoll)
////		{
////			if (false == bFirstRedraw)
////			{
////				/*�������������Ĺ�Ʊ*/
////				if (SPtr_CData->VerifybJump(iter->second->SecCode) == true)
////				{
////					highlightedSecCode = iter->second->SecCode;
////					bJump = true;
////					JumpIndex = index_vec_Alert;
////#ifdef _DEBUG
////					static int count = 0;
////					cerr << "jump count:" << count << " jump coude:" << highlightedSecCode << endl;
////					count++;
////#endif
////					if (SPtr_CData->obj_CAlertConfig.Template_Stock == CustomizePool)
////					{
////						tool::MyPlaySound(s_path_AlertSound);
////					}
////				}
////			}
////		}
////	}
////	
////	if (true == bAutoRoll)
////	{
////		fillPreviousRedrawList(MSpecialAlert);
////	}
////
////	pAlertGrid->SetRowCount(vec_Alert.size() + 1);
////	if (true == bJump)
////	{
////		pAlertGrid->SetEndVScroll();
////	}
////	pAlertGrid->Invalidate(FALSE);
////}/*studying ��ȫ���Ըĳ���������setCell����ѡ�����оͺ�*/

bool CTradeDlg::GetMAlert_Special(_MSpecialAlert &MSpecialAlert)
{
	string warnningID;
	switch (SPtr_CData->obj_CAlertConfig.Template_Alert)
	{
	case enum_Increase:
		warnningID = warnningId_Increase;
		break;
	case enum_N_Increase:
		warnningID = warnningId_N_Increase;
		break;
	case enum_Low_Rise:
		warnningID = warnningId_Low_Rise;
		break;
	default:
		ErrorLog("abnormal Template_Alert");
		break;
	}
	if (SPtr_CData->GetMAlert_Special(warnningID, MSpecialAlert) == false)
	{
		//ErrorLog("GetMAlert_Special fail");/*����û���ݵ�ʱ��Ҫˢ��Ԥ����*/
		return false;
	}
	return true;
}

void CTradeDlg::fillPreviousRedrawList(_MSpecialAlert &MSpecialAlert)
{
	SPtr_CData->ClearPreviousRedrawList();
	for (auto iter = MSpecialAlert.rbegin(); iter != MSpecialAlert.rend(); iter++)
	{
		SPtr_CData->insertPreviousRedrawList(iter->second->SecCode);
	}
	return;
}

bool CTradeDlg::OnStnClickedBigCanBuyTotal(const int ID_BigCanBuyTotal, const int ID_BEntrustAmount)
{
	UInt_64 BigCanBuyTotal;
	GainLegalValue(BigCanBuyTotal, ID_BigCanBuyTotal);
	GetDlgItem(ID_BEntrustAmount)->SetWindowText(_T(convert<string>(BigCanBuyTotal).c_str()));
	return true;
}

void CTradeDlg::ClickedbStockAssociated(const string &NodePath, CSimpleCheckbox* pSimpleCheckbox)
{
	ptree pt;
	try {
		read_xml(s_ConfigPath, pt, xml_parser::trim_whitespace);
		CString s_tmp;
		if (IsWindowValid(pSimpleCheckbox))
		{
			if (pSimpleCheckbox->GetCheck())
			{
				s_tmp = "1";
			}
			else
			{
				s_tmp = "0";
			}
			pt.put(NodePath, s_tmp);
			xml_writer_settings<string> settings('\t', 1, "GB2312");
			write_xml(s_ConfigPath, pt, std::locale(), settings);
		}

	}
	catch (std::exception& e)
	{
		LOG(ERROR) << "Error:" << e.what();
		ExceptionInterrupt;
		return;
	}
}

void CTradeDlg::OnClickedShowNoTrade(const int ID_ShowNoTrade,CListCtrl &CListCtrl_Order)
{
	int state = ((CButton*)GetDlgItem(ID_ShowNoTrade))->GetCheck();
	switch (state)
	{
	case 0://δ��ѡ��
		bShowAll = true;
		RedrawOrder(CListCtrl_Order);
		break;
	case 1://��ѡ��ѡ��
		bShowAll = false;
		RedrawOrder(CListCtrl_Order);
		break;
	default:
		break;
	}	
}

void CTradeDlg::OnRedrawEntrustQueue(VecEntrustQueue &VEntrustQueue, int Grade, CListCtrl &CListCtrl_EntrustQueue, unsigned int &Sum_Coloumn)
{
	int sum_entrust = 0;
	int item = 0;
	string Gear1;
	CString MarketCode;
	CString SecCode = SPtr_CData->TradingSecCode;
	if (SPtr_CData->SecCode2MarketCode(SecCode, MarketCode) == false)
	{
		ErrorLog("SecCode2MarketCode fail");
		return;
	}
	/*����ί���ܱ���*/
	CDepth obj_CDepth;
	if (SPtr_CData->GetDepth(MarketCode, SecCode, Grade, obj_CDepth) == false)
	{
		ErrorLog("GetDepth fail");
	}
	string NumOrders = convert<string>(obj_CDepth.NumOrders);
	NumOrders += " ��";

	VEntrustQueue.clear();
	if (SPtr_CData->GetMEntrustQueue(MarketCode, SecCode, Grade, VEntrustQueue) == false)
	{
		ErrorLog("GetMEntrustQueue fail");
		return;
	}
	if (VEntrustQueue[0])
	{
		Gear1 = convert<string>(VEntrustQueue[0]->Price);
	}
	else
	{
		Gear1 = "";
	}
	
	for (auto iter : VEntrustQueue)
	{
		if (iter)
		{
			if (iter->Quantity != 0)
			{
				sum_entrust++;
			}
			else
			{
				break;
			}
		}
		else
		{
			break;
		}
	}
	Sum_Coloumn = tool::GetColoumnSum(CListCtrl_EntrustQueue);
	item = sum_entrust / Sum_Coloumn + 1;
	CListCtrl_EntrustQueue.SetItemCount(item);
	SetClistColoumnText(CListCtrl_EntrustQueue, 1, Gear1);
	SetClistColoumnText(CListCtrl_EntrustQueue, 2, NumOrders);
}

void CTradeDlg::OnRedrawEntrustQueue(VecEntrustQueue &VEntrustQueue, int Grade, CGridCtrlEx* pGridQueue, unsigned int &Sum_Coloumn)
{
	if (!IsWindowValid(pGridQueue))
	{
		return;
	}
	int sum_entrust = 0;
	int item = 0;
	string Gear1;
	CString MarketCode;
	CString SecCode = SPtr_CData->TradingSecCode;
	if (SPtr_CData->SecCode2MarketCode(SecCode, MarketCode) == false)
	{
		ErrorLog("SecCode2MarketCode fail");
		return;
	}
	/*����ί���ܱ���*/
	CDepth obj_CDepth;
	if (SPtr_CData->GetDepth(MarketCode, SecCode, Grade, obj_CDepth) == false)
	{
		ErrorLog("GetDepth fail");
	}
	string NumOrders = convert<string>(obj_CDepth.NumOrders);
	NumOrders += " ��";

	VEntrustQueue.clear();
	if (SPtr_CData->GetMEntrustQueue(MarketCode, SecCode, Grade, VEntrustQueue) == false)
	{
		ErrorLog("GetMEntrustQueue fail");
		return;
	}
	if (VEntrustQueue[0])
	{
		Gear1 = convert<string>(VEntrustQueue[0]->Price);
	}
	else
	{
		Gear1 = "";
	}

	for (auto iter : VEntrustQueue)
	{
		if (iter)
		{
			if (iter->Quantity != 0)
			{
				sum_entrust++;
			}
			else
			{
				break;
			}
		}
		else
		{
			break;
		}
	}
	Sum_Coloumn = pGridQueue->GetColumnCount();
	item = sum_entrust / Sum_Coloumn + 1;
	
	CString strGear;
	strGear.Format("%s", Gear1.c_str());
	CString strNumOrders;
	strNumOrders.Format("%s", NumOrders.c_str());
	if (-1 == Grade)
	{
		m_strGearBuy1 = strGear;
		m_strNumOrdersBuy1 = strNumOrders;
	}
	else if (1 == Grade)
	{
		m_strGearSell1 = strGear;
		m_strNumOrdersSell1 = strNumOrders;
	}
	pGridQueue->SetRowCount(item + 1);
	pGridQueue->Invalidate();
}

void CTradeDlg::OnGetdispinfoEntrustQueue(LV_ITEM* pItem, unsigned int Sum_Coloumn, VecEntrustQueue &VEntrustQueue)
{
	int iItemIndx = pItem->iItem;
	CString s_str;
	if (pItem->mask & LVIF_TEXT)
	{
		switch (pItem->iSubItem)
		{
		case 0:
		{
			s_str = GetQuantity(iItemIndx, pItem->iSubItem, Sum_Coloumn, VEntrustQueue);
			lstrcpyn(pItem->pszText, s_str, pItem->cchTextMax);
			break;
		}
		case 1:
		{
			s_str = GetQuantity(iItemIndx, pItem->iSubItem, Sum_Coloumn, VEntrustQueue);
			lstrcpyn(pItem->pszText, s_str, pItem->cchTextMax);
			break;
		}
		case 2:
		{
			s_str = GetQuantity(iItemIndx, pItem->iSubItem, Sum_Coloumn, VEntrustQueue);
			lstrcpyn(pItem->pszText, s_str, pItem->cchTextMax);
			break;
		}
		case 3:
		{
			s_str = GetQuantity(iItemIndx, pItem->iSubItem, Sum_Coloumn, VEntrustQueue);
			lstrcpyn(pItem->pszText, s_str, pItem->cchTextMax);
			break;
		}
		case 4:
		{
			s_str = GetQuantity(iItemIndx, pItem->iSubItem, Sum_Coloumn, VEntrustQueue);
			lstrcpyn(pItem->pszText, s_str, pItem->cchTextMax);
			break;
		}
		case 5:
		{
			s_str = GetQuantity(iItemIndx, pItem->iSubItem, Sum_Coloumn, VEntrustQueue);
			lstrcpyn(pItem->pszText, s_str, pItem->cchTextMax);
			break;
		}
		case 6:
		{
			s_str = GetQuantity(iItemIndx, pItem->iSubItem, Sum_Coloumn, VEntrustQueue);
			lstrcpyn(pItem->pszText, s_str, pItem->cchTextMax);
			break;
		}
		default:
			break;
		}
	}
}

void CTradeDlg::OnCustomDrawEntrustQueue(LPNMTVCUSTOMDRAW &pNMCD, string &s_str)
{
	UInt_64 Quantity = convert<UInt_64>(s_str);
	if (Quantity > Threshold_Discoloration)
	{
		pNMCD->clrText = RGB(255, 0, 0);//��ɫ		
	}
	else
	{
		pNMCD->clrText = RGB(51, 153, 255);
	}
}

void CTradeDlg::OnRedrawEntrustEach(VecEntrustEach &VEntrustEach)
{
	CString MarketCode;
	CString SecCode = SPtr_CData->TradingSecCode;
	SPtr_CData->SecCode2MarketCode(SecCode, MarketCode);
	VEntrustEach.clear();
	if (SPtr_CData->GetVEntrustEach(MarketCode, SecCode, VEntrustEach, RedrawSum_EntrustEach) == false)
	{
		ExceptionInterrupt;
		LOG(ERROR) << "GetVEntrustEach fail";
		return;
	}
	CListCtrl_EntrustEach.SetItemCount(VEntrustEach.size());
}

void CTradeDlg::OnRedrawEntrustEach(CGridCtrlEx* pOrderEach)
{
	if (!IsWindowValid(pOrderEach))
	{
		return;
	}
	CString MarketCode;
	CString SecCode = SPtr_CData->TradingSecCode;
	SPtr_CData->SecCode2MarketCode(SecCode, MarketCode);
	VEntrustEach.clear();
	if (SPtr_CData->GetVEntrustEach(MarketCode, SecCode, VEntrustEach, RedrawSum_EntrustEach) == false)
	{
		ExceptionInterrupt;
		LOG(ERROR) << "GetVEntrustEach fail";
		return;
	}
// 	CListCtrl_EntrustEach.SetItemCount(VEntrustEach.size());
	pOrderEach->SetRowCount(VEntrustEach.size() + 1);
	pOrderEach->Invalidate();
}

void CTradeDlg::OnGetdispinfoEntrustEach(LV_ITEM* pItem, VecEntrustEach &VEntrustEach)
{
	int iItemIndx = pItem->iItem;
	CString s_str;
	if (pItem->mask & LVIF_TEXT)
	{
		switch (pItem->iSubItem)
		{
		case 0://ʱ��
		{
			s_str = convert<string>(VEntrustEach[iItemIndx]->Time).c_str();
			lstrcpyn(pItem->pszText, s_str, pItem->cchTextMax);
			break;
		}
		case 1://ί�к�
		{
			s_str = convert<string>(VEntrustEach[iItemIndx]->OrderNo).c_str();
			lstrcpyn(pItem->pszText, s_str, pItem->cchTextMax);
			break;
		}
		case 2://�۸�
		{
			s_str.Format("%0.2f", VEntrustEach[iItemIndx]->Price);
			lstrcpyn(pItem->pszText, s_str, pItem->cchTextMax);
			break;
		}
		case 3://����
		{
			s_str = convert<string>(VEntrustEach[iItemIndx]->Volume).c_str();
			lstrcpyn(pItem->pszText, s_str, pItem->cchTextMax);
			break;
		}
		case 4://���
		{
			s_str.Format("%0.2f", VEntrustEach[iItemIndx]->Amount);
			lstrcpyn(pItem->pszText, s_str, pItem->cchTextMax);
			break;
		}
		case 5://��������
		{
			switch (VEntrustEach[iItemIndx]->Side)
			{
			case '1':
				s_str = "B";
				break;
			case '2':
				s_str = "S";
				break;
			default:
				ExceptionInterrupt;
				LOG(ERROR) << "abnoraml Side";
				break;
			}
			lstrcpyn(pItem->pszText, s_str, pItem->cchTextMax);
			break;
		}
		default:break;
		}
	}
}

void CTradeDlg::OnCustomDrawEntrustEach(LPNMTVCUSTOMDRAW &pNMCD, string &s_str)
{
	switch (tool::find_enumSide_EntrustEach(s_str))
	{
	case enumBuy:
		pNMCD->clrText = RGB(255, 0, 0);//��ɫ
		break;
	case enumSell:
		pNMCD->clrText = RGB(51, 153, 255);//��ɫ
		break;
	case enumBC:
		break;
	case enumSC:
		break;
	default:
		ExceptionInterrupt;
		LOG(ERROR) << "abnormal Side";
		break;
	}
}


bool CTradeDlg::InspectbRedraw(const CString &stock_code, unsigned int CtrID)
{
	CString s_str;
	GetDlgItem(CtrID)->GetWindowText(s_str);
	if (s_str == stock_code)
	{
		return false;
	}
	return true;
}

bool CTradeDlg::VerifybUpdateMoudle(const int ID_SecCode)
{
	CString s_str;
	(GetDlgItem(ID_SecCode))->GetWindowText(s_str);
	if (s_str == SPtr_CData->TradingSecCode)
	{
		return true;
	}
	return false;
}

bool CTradeDlg::InitStockAssociated(const string &treePath)
{
	bool bResult = false;
	ptree pt;
	try {
		read_xml(s_ConfigPath, pt);
		bResult = pt.get<bool>(treePath);
	}
	catch (std::exception& e)
	{
		LOG(ERROR) << "Error:" << e.what();
		ExceptionInterrupt;
		return false;
	}
	return bResult;
}

bool CTradeDlg::VerifybUpdateMoudle(CSimpleEdit* pEdit)
{
	CString s_str;
	if (IsWindowValid(pEdit))
	{
		pEdit->GetWindowText(s_str);
	}
	if (s_str == SPtr_CData->TradingSecCode)
	{
		return true;
	}
	return false;
}

bool CTradeDlg::VerifyMarketStatus()
{
	_Market::iterator iter_MMarket;
	bool bMarketServerStatus = false;
	for (iter_MMarket = SPtr_CData->MMarket.begin(); iter_MMarket != SPtr_CData->MMarket.end(); )
	{
		if (iter_MMarket->second->MSecurity.size() <= 0)
		{
			bMarketServerStatus = false;
			break;
		}
		iter_MMarket++;
		bMarketServerStatus = true;
	}
	return bMarketServerStatus;
}

bool CTradeDlg::getDepthPrice(const CString &MarketCode, const CString &SecCode, const int grade, double &EntrustPrice)
{
	CDepth obj_CDepth;
	if (SPtr_CData->GetDepth(MarketCode, SecCode, grade, obj_CDepth) == false)
	{
		EntrustPrice = 0;
		return false;
	}
	else
	{
		EntrustPrice = obj_CDepth.Price;
	}

	return true;
}

bool CTradeDlg::getDefalutPrice(const CString &DefalutGear, const CString &MarketCode, const CString &SecCode, double &EntrustPrice)
{
	switch (tool::find_enumPriceType(string(DefalutGear)))
	{
	case enum��ͣ��:
	{
		CSecurity obj_CSecurity;
		if (SPtr_CData->GetSecurity(MarketCode, SecCode, obj_CSecurity) == false)
		{
			ErrorLog("GetSecurity fail");
			EntrustPrice = 0;
			return false;
		}
		else
		{
			EntrustPrice = obj_CSecurity.UpLimitPrice;
		}

		break;
	}
	case enum��ͣ��:
	{
		CSecurity obj_CSecurity;
		if (SPtr_CData->GetSecurity(MarketCode, SecCode, obj_CSecurity) == false)
		{
			LOG(ERROR) << "GetSecurity fail";
			ExceptionInterrupt;
			EntrustPrice = 0;
			return false;
		}
		else
		{
			EntrustPrice = obj_CSecurity.DownLimitPrice;
		}
		break;
	}
	case enum��һ��:
	{
		getDepthPrice(MarketCode, SecCode, -1, EntrustPrice);
		break;
	}
	case enum�����:
	{
		getDepthPrice(MarketCode, SecCode, -2, EntrustPrice);
		break;
	}
	case enum������:
	{
		getDepthPrice(MarketCode, SecCode, -3, EntrustPrice);
		break;
	}
	case enum���ļ�:
	{
		getDepthPrice(MarketCode, SecCode, -4, EntrustPrice);
		break;
	}
	case enum�����:
	{
		getDepthPrice(MarketCode, SecCode, -5, EntrustPrice);
		break;
	}
	case enum��һ��:
	{
		getDepthPrice(MarketCode, SecCode, 1, EntrustPrice);
		break;
	}
	case enum������:
	{
		getDepthPrice(MarketCode, SecCode, 2, EntrustPrice);
		break;
	}
	case enum������:
	{
		getDepthPrice(MarketCode, SecCode, 3, EntrustPrice);
		break;
	}
	case enum���ļ�:
	{
		getDepthPrice(MarketCode, SecCode, 4, EntrustPrice);
		break;
	}
	case enum�����:
	{
		getDepthPrice(MarketCode, SecCode, 5, EntrustPrice);
		break;
	}
	default:
		ErrorLog("abnoraml DefaultGear");
		break;
	}
	return true;
}

bool CTradeDlg::GainCSecurity(CSecurity &obj_CSecurity, const CString stock_code)
{
	if ("" == stock_code)
	{
		MessageBox("��Ʊ����Ϊ��", "��ʾ", MB_OK);
		return false;
	}
	else
	{
		CString MarketCode;
		if (SPtr_CData->SecCode2MarketCode(stock_code, MarketCode) == false)
		{
			LOG(ERROR) << "SecCode2MarketCode fail";
			ExceptionInterrupt;
			return false;
		}
		if (SPtr_CData->GetSecurity(MarketCode, stock_code, obj_CSecurity) == false)
		{
			LOG(ERROR) << "GetSecurity fail";
			ExceptionInterrupt;
			return false;
		}
	}
	return true;
}

bool CTradeDlg::GaineEable_amount(const CString &SecCode, UInt_64 &enable_amount)
{
	/*��ȡ�ֲ���Ŀ�������*/
	CString StockAccount;
	if (SPtr_CData->SecCode2StockAccount(SecCode, StockAccount) == false)
	{
		enable_amount = 0;
		return false;
	}

	CPosition obj_CPosition;
	if (SPtr_CData->GetPosition(SPtr_CData->fund_account, StockAccount, SecCode, obj_CPosition) == false)
	{
		enable_amount = 0;
		return true;
	}
	else
	{
		enable_amount = obj_CPosition.enable_amount;
	}
	return true;
}

bool CTradeDlg::GainEntrustInfoByEntrustNo(const UInt_64 entrust_no, enumEntrustStatus &entrust_status, string &exchange_type)
{
	bool bFind = false;
	_Account obj_MAccount;
	_Account::iterator iter_MAccount;
	if (true == SPtr_CData->GetMAccount(SPtr_CData->fund_account, obj_MAccount))
	{
		for (iter_MAccount = obj_MAccount.begin(); iter_MAccount != obj_MAccount.end(); iter_MAccount++)
		{
			_Order obj_MOrder;
			if (SPtr_CData->GetMOrder(SPtr_CData->fund_account, iter_MAccount->first, obj_MOrder) == false)
			{
				LOG(ERROR) << "GetMOrder fail";
				ExceptionInterrupt;
				continue;
			}
			auto iter = obj_MOrder.find(entrust_no);
			if (iter != obj_MOrder.end())
			{
				entrust_status = iter->second->entrust_status;
				SPtr_CData->Account2ExchangeType(iter_MAccount->first, exchange_type);
				bFind = true;
			}
		}
	}
	else
	{
		LOG(ERROR) << "GetAccountMap fail";
		ExceptionInterrupt;
		return false;
	}
	return bFind;
}

double CTradeDlg::GainPoundage(double EntrustBalance)
{
	if (EntrustBalance <= 0)
		return 0;
	double Poundage;
	Poundage = EntrustBalance*(Ratio_poundage);
	if (Poundage < 5)
	{
		Poundage = 5;
	}
	return Poundage;
}

double CTradeDlg::GainBalance_MaxEnable(bool bFinancingBuy)
{
	double balance_MaxEnable;
	if (bFinancingBuy == true)//��������
	{
		VecCreditAsset VCreditAsset;
		if (SPtr_CData->GetVCreditAsset(SPtr_CData->fund_account, VCreditAsset) == false)
		{
			ErrorLog("GetVCreditAsset fail");
			balance_MaxEnable = 0;
		}
		else
		{
			VCreditAsset[0][1]; //per_assurescale_value ά�ֵ������� 0<=x<1.5���Թ��� -1 ����û�и�ծ
			VCreditAsset[0][3];//���ʿ��ö�� fin_enable_quota
			VCreditAsset[1][1];//"���ñ�֤��"; enable_bail_balance 
			double per_assurescale_value = convert<double>(VCreditAsset[0][1]);
			if (0 <= per_assurescale_value &&  per_assurescale_value < 1.5)
			{
				balance_MaxEnable = 0;
			}
			else
			{
				double fin_enable_quota = convert<double>(VCreditAsset[0][3]);
				double enable_bail_balance = convert<double>(VCreditAsset[1][1]);
				BOOST_AUTO(x, boost::minmax(fin_enable_quota, enable_bail_balance));
				balance_MaxEnable = x.get<0>();
			}
		}
	}
	else
	{
		CFund obj_CFund;
		if (SPtr_CData->GetFund(SPtr_CData->fund_account, obj_CFund) == false)
		{
			ErrorLog("GetFund fail");
			balance_MaxEnable = 0;
		}
		else
			balance_MaxEnable = obj_CFund.enable_balance;
	}

	if (balance_MaxEnable < 0)
	{
		balance_MaxEnable = 0;
	}
	return balance_MaxEnable;
}

UInt_64 CTradeDlg::GainBigCanBuy(bool bFinancingBuy, const double &entrust_price)
{
	double enable_balance = GainBalance_MaxEnable(bFinancingBuy);
	enable_balance = enable_balance - GainPoundage(enable_balance);
	return modifyNum(enable_balance / entrust_price);
}

UInt_64 CTradeDlg::GainCanBuy(bool bFinancingBuy, double DefaultBalance, const double &entrust_price)
{
	double balance_MaxEnable = GainBalance_MaxEnable(bFinancingBuy);
	BOOST_AUTO(x, boost::minmax(balance_MaxEnable, DefaultBalance));
	DefaultBalance = x.get<0>();
	DefaultBalance = DefaultBalance - GainPoundage(DefaultBalance);
	return modifyNum(DefaultBalance / entrust_price);
}

bool CTradeDlg::GainSetModuleInfo(const int CtrlId, CString &MarketCode, CString &SecCode)
{
	GetDlgItem(CtrlId)->GetWindowText(SecCode);
	if (SPtr_CData->SecCode2MarketCode(SecCode, MarketCode) == false)
	{
		return false;
	}
	return true;
}

bool CTradeDlg::GainSetModuleInfo(CSimpleEdit* pCode, CString &MarketCode, CString &SecCode)
{
	if (IsWindowValid(pCode))
	{
		pCode->GetWindowText(SecCode);
	}
	if (SPtr_CData->SecCode2MarketCode(SecCode, MarketCode) == false)
	{
		return false;
	}
	return true;
}

void CTradeDlg::GainOrderInfo(CString &s_dst, CString entrust_bs, int ID_SecCode, int ID_SecName, int ID_EntrustPrice, int ID_EntrustAmount)
{
	s_dst = "               ��������:";
	s_dst += entrust_bs;
	s_dst += "\n";
	FillElement(s_dst, "               ��Ʊ����:", ID_SecCode);
	FillElement(s_dst, "               ��Ʊ����:", ID_SecName);
	FillElement(s_dst, "               ί�м۸�:", ID_EntrustPrice);
	FillElement(s_dst, "               ί������:", ID_EntrustAmount);
	s_dst += "               ��ȷ�Ϸ���ί����?";
}

void CTradeDlg::GainOrderInfo(CString &s_dst, CString entrust_bs, CSimpleEdit* pCode, CSimpleStatic* pName, CSimpleEdit* pEntrustPrice, CSimpleEdit* pEntrustAmount)
{
	s_dst = "               ��������:";
	s_dst += entrust_bs;
	s_dst += "\n";
	FillElement(s_dst, "               ��Ʊ����:", pCode);
	FillElement(s_dst, "               ��Ʊ����:", pName);
	FillElement(s_dst, "               ί�м۸�:", pEntrustPrice);
	FillElement(s_dst, "               ί������:", pEntrustAmount);
	s_dst += "               ��ȷ�Ϸ���ί����?";
}

void CTradeDlg::FillElement(CString &s_dst, CString s_elementName, int CtrlID)
{
	CString s_str;
	GetDlgItem(CtrlID)->GetWindowText(s_str);
	s_dst += s_elementName;
	s_dst += s_str;
	s_dst += "\n";
}

void CTradeDlg::FillElement(CString &s_dst, CString s_elementName, CSimpleEdit* pEdit)
{
	if (IsWindowValid(pEdit))
	{
		CString s_str;
		pEdit->GetWindowText(s_str);
		s_dst += s_elementName;
		s_dst += s_str;
		s_dst += "\n";
	}
}

void CTradeDlg::FillElement(CString &s_dst, CString s_elementName, CSimpleStatic* pStatic)
{
	if (IsWindowValid(pStatic))
	{
		CString s_str;
		pStatic->GetWindowText(s_str);
		s_dst += s_elementName;
		s_dst += s_str;
		s_dst += "\n";
	}
}

void CTradeDlg::GainOrderInfo(CString &s_dst, CString entrust_bs, CString stock_code, const double &entrust_price, UInt_64 entrust_amount)
{
	s_dst = "               ��������:";
	s_dst += entrust_bs;
	s_dst += "\n";

	s_dst += "               ��Ʊ����:";
	s_dst += stock_code;
	s_dst += "\n";

	CString stock_name;
	if (SPtr_CData->SecCode2SecName(stock_code, stock_name) == false)
	{
		ExceptionInterrupt;
		LOG(ERROR) << "SecCode2SecName fail";
		return;
	}
	s_dst += "               ��Ʊ����:";
	s_dst += stock_name;
	s_dst += "\n";

	s_dst += "               ί�м۸�:";
	s_dst += convert<string>(entrust_price).c_str();
	s_dst += "\n";

	s_dst += "               ί������:";
	s_dst += convert<string>(entrust_amount).c_str();
	s_dst += "\n";
	s_dst += "               ��ȷ�Ϸ���ί����?";
}


bool CTradeDlg::gainBEntrustAmount_Directly(bool bFinancingBuy, const double &entrust_price, UInt_64 &entrust_amount, bool bCalculateByBalance,
	double DefaultBalance, int DefaultAmount)
{
	if (true == bCalculateByBalance)
	{
		/*����Ĭ���ʽ����*/
		entrust_amount = GainCanBuy(bFinancingBuy,DefaultBalance,entrust_price);
	}
	else
	{
		/*���Ȼ�ȡ�������ڱȽ��������Ĭ�Ϲ���*/
		UInt_64 BigCanBuyTotal = GainBigCanBuy(bFinancingBuy, entrust_price);
		BOOST_AUTO(y, boost::minmax(BigCanBuyTotal, (UInt_64)DefaultAmount));
		entrust_amount = y.get<0>(); 
	}
	return true;
}

CString CTradeDlg::GetQuantity(const int &iItem, const int &iSubItem, const int &Sum_Coloumn, VecEntrustQueue &VEntrustQueue)
{
	UInt_64 Quantity;
	CString s_str;
	int index = iItem * Sum_Coloumn + iSubItem;
	if (VEntrustQueue[index])
	{
		Quantity = VEntrustQueue[index]->Quantity;
		if (Quantity != 0)
		{
			s_str = convert<string>(Quantity).c_str();
		}
		else
		{
			s_str = "0";
		}
	}
	else
	{
		s_str = "";
	}
	return s_str;
}

bool CTradeDlg::FillVec_Dismantling(vector<string> &Vec_Dismantling, UInt_64 entrust_amount,bool bDismantling, bool bRandom, int BaseQuantity
,UInt_32 Order_Minimum,UInt_32 Order_Maximum)
{
	if (true == bDismantling && entrust_amount > BaseQuantity*Unit_BaseQuantiry)
	{
		if (FillByDismantling(Vec_Dismantling, entrust_amount, bRandom,BaseQuantity
			,Order_Minimum, Order_Maximum) == false)
		{
			return false;
		}
	}
	else
	{
		Vec_Dismantling.push_back(convert<string>(entrust_amount));
	}
	return true;
}

bool CTradeDlg::FillByDismantling(vector<string> &Vec_Dismantling, UInt_64 entrust_amount, bool bRandom, int BaseQuantity
	, UInt_32 Order_Minimum, UInt_32 Order_Maximum)
{
	if (true == bRandom)
	{
		return FillByRandom(Vec_Dismantling, entrust_amount, Order_Minimum, Order_Maximum);
	}
	else
	{
		return FillByAverage(Vec_Dismantling, entrust_amount, BaseQuantity);
	}
}

bool CTradeDlg::FillByRandom(vector<string> &Vec_Dismantling, UInt_64 entrust_amount, UInt_32 Order_Minimum, UInt_32 Order_Maximum)
{
	int sum = 0;
	int i = 0;
	for (i = 0;i < Toplimit_Dismantling;i++)
	{
		if (Order_Minimum > Order_Maximum)
		{
			MessageBox("��������С�ڵ������ޣ���ʧ�ܣ��������µ�����", "����", NULL);
			return false;
		}
		UInt_64 Each_EntrustAmount = random(Order_Minimum, Order_Maximum)*100;
		sum += Each_EntrustAmount;
		if (sum >= entrust_amount)
		{
			Each_EntrustAmount -= (sum - entrust_amount);
			if (Each_EntrustAmount < Order_Minimum*100)
			{
				int tmp = convert<UInt_64>(Vec_Dismantling[i - 1]) + Each_EntrustAmount;
				Vec_Dismantling[i - 1] = convert<string>(tmp);
			}
			else
			{
				Vec_Dismantling.push_back(convert<string>(Each_EntrustAmount));
			}
			break;
		}
		Vec_Dismantling.push_back(convert<string>(Each_EntrustAmount));
	}
	if (sum < entrust_amount)
	{
		string  s_str = "��ί�еķֲִ����ѳ���ϵͳ��������ֲִ���(";
		s_str += convert<string>(Toplimit_Dismantling);
		s_str += ")";
		MessageBox(s_str.c_str(), "��ʾ", MB_OK);
		return false;
	}
	return true;
}

bool CTradeDlg::FillByAverage(vector<string> &Vec_Dismantling, UInt_64 entrust_amount, int BaseQuantity)
{
	BaseQuantity = BaseQuantity * Unit_BaseQuantiry;
	int Sum_Entrust = entrust_amount / BaseQuantity;
	for (int i = 0;i < Sum_Entrust; i++)
	{
		Vec_Dismantling.push_back(convert<string>(BaseQuantity));
	}
	int remainder = entrust_amount%BaseQuantity;
	if (remainder != 0)
	{
		Vec_Dismantling.push_back(convert<string>(remainder));
		Sum_Entrust++;
	}
	if (Sum_Entrust >= Toplimit_Dismantling)
	{
		string  s_str = "��ί�еķֲִ����ѳ���ϵͳ��������ֲִ���(";
		s_str += convert<string>(Toplimit_Dismantling);
		s_str += ")";
		MessageBox(s_str.c_str(), "��ʾ", MB_OK);
		Vec_Dismantling.clear();
		return false;
	}
	return true;
}

bool CTradeDlg::VerifyBEntrustPrice(const int ID_BSecName, const int Id_BSecCode, const int Id_BEntrustPrice)
{
	/*CString SecName;
	GetDlgItem(ID_BSecName)->GetWindowText(SecName);
	if (SecName[0] == 'N')
	{
		return true;
	}*/

	double UpLimitPrice;
	CString stock_code;
	GetDlgItem(Id_BSecCode)->GetWindowText(stock_code);
	CSecurity obj_CSecurity;
	if (GainCSecurity(obj_CSecurity, stock_code) == false)
	{
		ErrorLog("GainCSecurity fail");
		return false;
	}
	UpLimitPrice = obj_CSecurity.UpLimitPrice;
	/*ί�м۸������ͣ�۷Ƿ�*/
	double EntrustPrice = 0;
	if (GainLegalValue(EntrustPrice, Id_BEntrustPrice) == false)
	{
		MessageBox("ί�м۸��쳣", "��ʾ", MB_OK);
		return false;
	}
	if (tool::round(EntrustPrice, 2) > tool::round(UpLimitPrice, 2))
	{
		if (MessageBox("ί�м۸������ͣ��,�µ�����ʧ��", "��ʾ", MB_YESNO) == IDYES)
		{
			return true;
		}
		else
		{
			return false;
		}
		return true;
	}
	return true;
}

bool CTradeDlg::VerifyBEntrustPrice(CSimpleStatic* pBSecName, CSimpleEdit* pBSecCode, CSimpleEdit* pBEntrustPrice)
{
	double UpLimitPrice;
	CString stock_code;
	if (pBSecCode != nullptr && IsWindow(pBSecCode->GetSafeHwnd()))
	{
		pBSecCode->GetWindowText(stock_code);
	}
	CSecurity obj_CSecurity;
	if (GainCSecurity(obj_CSecurity, stock_code) == false)
	{
		ErrorLog("GainCSecurity fail");
		return false;
	}
	UpLimitPrice = obj_CSecurity.UpLimitPrice;
	/*ί�м۸������ͣ�۷Ƿ�*/
	double EntrustPrice = 0;
	if (GainLegalValue(EntrustPrice, pBEntrustPrice) == false)
	{
		MessageBox("ί�м۸��쳣", "��ʾ", MB_OK);
		return false;
	}
	if (tool::round(EntrustPrice, 2) > tool::round(UpLimitPrice, 2))
	{
		if (MessageBox("ί�м۸������ͣ��,�µ�����ʧ��", "��ʾ", MB_YESNO) == IDYES)
		{
			return true;
		}
		else
		{
			return false;
		}
		return true;
	}
	return true;
}

bool CTradeDlg::VerifySEntrustPrice(const int ID_SSecName, const int Id_SSecCode, const int Id_SEntrustPrice)
{
	CString stock_code;
	GetDlgItem(Id_SSecCode)->GetWindowText(stock_code);
	
	CSecurity obj_CSecurity;
	if (GainCSecurity(obj_CSecurity, stock_code) == false)
	{
		ErrorLog("GainCSecurity fail");
		return false;
	}

	/*ί�м۸�С�ڵ�ͣ��۷Ƿ�*/
	double EntrustPrice = 0;
	if (GainLegalValue(EntrustPrice, Id_SEntrustPrice) == false)
	{
		MessageBox("ί�м۸�Ƿ�", "��ʾ", MB_OK);
		return false;
	}

	if (tool::round(EntrustPrice, 2) < tool::round(obj_CSecurity.DownLimitPrice, 2))
	{
		if (MessageBox("ί�м۸�С�ڵ�ͣ��,�µ�����ʧ��", "��ʾ", MB_YESNO) == IDYES)
		{
			return true;
		}
		else
		{
			return false;
		}
		return true;
	}
	return true;
}

bool CTradeDlg::VerifySEntrustPrice(CSimpleStatic* pSSecName, CSimpleEdit* pSSecCode, CSimpleEdit* pSEntrustPrice)
{
	CString stock_code;
	if (IsWindowValid(pSSecCode))
	{
		pSSecCode->GetWindowText(stock_code);
	}

	CSecurity obj_CSecurity;
	if (GainCSecurity(obj_CSecurity, stock_code) == false)
	{
		ErrorLog("GainCSecurity fail");
		return false;
	}

	/*ί�м۸�С�ڵ�ͣ��۷Ƿ�*/
	double EntrustPrice = 0;
	if (GainLegalValue(EntrustPrice, pSEntrustPrice) == false)
	{
		MessageBox("ί�м۸�Ƿ�", "��ʾ", MB_OK);
		return false;
	}

	if (tool::round(EntrustPrice, 2) < tool::round(obj_CSecurity.DownLimitPrice, 2))
	{
		if (MessageBox("ί�м۸�С�ڵ�ͣ��,�µ�����ʧ��", "��ʾ", MB_YESNO) == IDYES)
		{
			return true;
		}
		else
		{
			return false;
		}
		return true;
	}
	return true;
}

bool CTradeDlg::VerifyBEntrustAmount(bool bDismantling, CSimpleStatic* pBigCanBuyTotal, CSimpleEdit* pBEntrustAmount)
{
	/*ί����������100 0000���߿��������Ƿ�*/
	UInt_64 EntrustAmount = 0;
	UInt_64 BigCanBuyTotal = 0;
	if (GainLegalValue(BigCanBuyTotal, pBigCanBuyTotal) == false)
	{
		MessageBox("��������쳣", "��ʾ", MB_OK);
		return false;
	}
	if (GainLegalValue(EntrustAmount, pBEntrustAmount) == false)
	{
		MessageBox("ί�������쳣", "��ʾ", MB_OK);
		return false;
	}

	if (EntrustAmount > BigCanBuyTotal)
	{
		MessageBox("ί�������Ƿ�", "��ʾ", MB_OK);
		return false;
	}

	if (!VerifyEntrustAmount(true, pBEntrustAmount))
	{
		return false;
	}

	if (false == bDismantling)
	{
		if (EntrustAmount > Max_EntrustAmount)
		{
			MessageBox("ί�������Ƿ�", "��ʾ", MB_OK);
			return false;
		}
	}
	return true;
}

bool CTradeDlg::VerifyEntrustAmount(bool bBuyModule, CSimpleEdit* pEntrustAmount)
{
	CString s_str;
	if (!IsWindowValid(pEntrustAmount))
	{
		return false;
	}
	pEntrustAmount->GetWindowText(s_str);
	if ("" == s_str || "0" == s_str)
	{
		MessageBox("�����ί�������Ƿ�������������", "��ʾ", MB_OK);
		return false;
	}
	else
	{
		if (true == bBuyModule)
		{
			if (convert<unsigned int>(s_str) % 100 != 0)
			{
				MessageBox("�����ί�������Ƿ�������������", "��ʾ", MB_OK);
				return false;
			}
		}
		/*��ģ��ֱ�Ӳ�У��*/
	}
	return true;
}

bool CTradeDlg::VerifySEntrustAmount(bool bDismantling, CSimpleStatic* pSCanSellTotal, CSimpleEdit* pSEntrustAmount)
{
	/*��ȡ��������*/
	double CanSellTotal = 0;
	if (GainLegalValue(CanSellTotal, pSCanSellTotal) == false)
	{
		MessageBox("���������Ƿ�", "��ʾ", MB_OK);
		return false;
	}

	/*ί���������ڿ��������Ƿ�*/
	UInt_64 EntrustAmount = 0;
	if (GainLegalValue(EntrustAmount, pSEntrustAmount) == false)
	{
		MessageBox("ί�������쳣", "��ʾ", MB_OK);
		return false;
	}

	if (EntrustAmount > CanSellTotal)
	{
		MessageBox("ί�������Ƿ�", "��ʾ", MB_OK);
		return false;
	}

	if (false == bDismantling)
	{
		if (EntrustAmount > Max_EntrustAmount)
		{
			MessageBox("ί�������Ƿ�", "��ʾ", MB_OK);
			return false;
		}
	}

	return true;
}

bool CTradeDlg::VerifySEntrustAmount(bool bDismantling, const int Id_SCanSellTotal, const int Id_SEntrustAmount)
{
	/*��ȡ��������*/
	double CanSellTotal = 0;
	if (GainLegalValue(CanSellTotal, Id_SCanSellTotal) == false)
	{
		MessageBox("���������Ƿ�", "��ʾ", MB_OK);
		return false;
	}

	/*ί���������ڿ��������Ƿ�*/
	UInt_64 EntrustAmount = 0;
	if (GainLegalValue(EntrustAmount, Id_SEntrustAmount) == false)
	{
		MessageBox("ί�������쳣", "��ʾ", MB_OK);
		return false;
	}

	if (EntrustAmount > CanSellTotal)
	{
		MessageBox("ί�������Ƿ�", "��ʾ", MB_OK);
		return false;
	}

	if (false == bDismantling)
	{
		if (EntrustAmount > Max_EntrustAmount)
		{
			MessageBox("ί�������Ƿ�", "��ʾ", MB_OK);
			return false;
		}
	}

	return true;
}

bool CTradeDlg::VerifyBEntrustBalance(bool bFinancingBuy, const int Id_BEnableBalance, const int Id_BEntrustBalance)
{
	/*��ȡ�����ʽ�*/
	double EnableBalance = GainBalance_MaxEnable(bFinancingBuy);
	/*ί�н����ڿ����ʽ�Ƿ�*/
	double EntrustBalance = 0;
	if (GainLegalValue(EntrustBalance, Id_BEntrustBalance) == false)
	{
		MessageBox("ί�н���쳣", "��ʾ", MB_OK);
		return false;
	}

	if (EntrustBalance > EnableBalance)
	{
		MessageBox("ί�зǷ���ί�н����ڿ����ʽ�", "��ʾ", MB_OK);
		return false;
	}
	return true;
}

bool CTradeDlg::VerifyBEntrustBalance(bool bFinancingBuy, CSimpleStatic* pBEnableBalance, CSimpleStatic* pBEntrustBalance)
{
	/*��ȡ�����ʽ�*/
	double EnableBalance = GainBalance_MaxEnable(bFinancingBuy);
	/*ί�н����ڿ����ʽ�Ƿ�*/
	double EntrustBalance = 0;
	if (GainLegalValue(EntrustBalance, pBEntrustBalance) == false)
	{
		MessageBox("ί�н���쳣", "��ʾ", MB_OK);
		return false;
	}

	if (EntrustBalance > EnableBalance)
	{
		MessageBox("ί�зǷ���ί�н����ڿ����ʽ�", "��ʾ", MB_OK);
		return false;
	}
	return true;
}

bool CTradeDlg::VerifybEmpty_SecCode(const int ID_SecCode)
{
	CString stock_code;
	GetDlgItem(ID_SecCode)->GetWindowText(stock_code);
	if ("" == stock_code)
	{
		return true;
	}
	return false;
}

bool CTradeDlg::VerifybEmpty_SecCode(CSimpleEdit* pSecCode)
{
	CString stock_code;
	if (IsWindowValid(pSecCode))
	{
		pSecCode->GetWindowText(stock_code);
	}

	if ("" == stock_code)
	{
		return true;
	}
	return false;
}

bool CTradeDlg::VerifyBuyEntrustment_Directly(bool bDismantling, const double &entrust_price, const UInt_64 &entrust_amount)
{
	if (entrust_price <= 0)
	{
		ExceptionInterrupt;
		LOG(ERROR) << "ί�м۸񲻺Ϸ�";
		MessageBox("ί�м۸񲻺Ϸ�", "ί�д���", NULL);
		return false;
	}

	if (entrust_amount <= 0)
	{
		ExceptionInterrupt;
		LOG(ERROR) << "ί���������Ϸ�";
		MessageBox("ί���������Ϸ�", "ί�д���", NULL);
		return false;
	}

	if (false == bDismantling)
	{
		if (entrust_amount > Max_EntrustAmount)
		{
			ExceptionInterrupt;
			LOG(ERROR) << "ί���������Ϸ�";
			MessageBox("ί���������Ϸ�", "ί�д���", NULL);
			return false;
		}
	}

	//CFund obj_CFund;
	//if (SPtr_CData->GetFund(SPtr_CData->fund_account, obj_CFund) == false)
	//{
	//	ExceptionInterrupt;
	//	LOG(ERROR) << "GetFund fail";
	//	return false;
	//}

	//double entrust_balance = entrust_price * entrust_amount;
	//if (entrust_balance <= 0 || entrust_balance > obj_CFund.enable_balance)
	//{
	//	ExceptionInterrupt;
	//	LOG(ERROR) << "ί�н��Ϸ�";
	//	MessageBox("ί�н��Ϸ�", "ί�д���", NULL);
	//	return false;
	//}
	return true;
}


bool CTradeDlg::SetSecName(const CString &MarketCode, const CString SecCode, const int ID_SecName)
{
	CSecurity obj_CSecurity;
	if (SPtr_CData->GetSecurity(MarketCode, SecCode, obj_CSecurity) == false)
	{
		LOG(ERROR) << "GetSecurity fail";
		ExceptionInterrupt;
	}

	GetDlgItem(ID_SecName)->SetWindowText(obj_CSecurity.stock_name);
	return true;
}

bool CTradeDlg::SetSecName(const CString &MarketCode, const CString SecCode, CSimpleStatic* pSecName)
{
	CSecurity obj_CSecurity;
	if (SPtr_CData->GetSecurity(MarketCode, SecCode, obj_CSecurity) == false)
	{
		LOG(ERROR) << "GetSecurity fail";
		ExceptionInterrupt;
	}
	if (IsWindowValid(pSecName))
	{
		pSecName->SetWindowText(obj_CSecurity.stock_name);
	}

	return true;
}

bool CTradeDlg::SetEntrustPrice(const int Id_EntrustPrice, const CString &DefalutGear, const CString &MarketCode,
	const CString &SecCode)
{
	CString s_EntrustPrice;
	double EntrustPrice = 0;
	if (getDefalutPrice(DefalutGear, MarketCode, SecCode, EntrustPrice) == false)
	{
		LOG(ERROR) << "getDefalutPrice fail";
		ExceptionInterrupt;
	}
	s_EntrustPrice.Format(_T("%0.2f"), EntrustPrice);
	GetDlgItem(Id_EntrustPrice)->SetWindowText(s_EntrustPrice);
	return true;
}

bool CTradeDlg::SetEntrustPrice(CSimpleEdit* pEntrustPrice, const CString &DefalutGear, const CString &MarketCode,
	const CString &SecCode)
{
	CString s_EntrustPrice;
	double EntrustPrice = 0;
	if (getDefalutPrice(DefalutGear, MarketCode, SecCode, EntrustPrice) == false)
	{
		LOG(ERROR) << "getDefalutPrice fail";
		ExceptionInterrupt;
	}
	s_EntrustPrice.Format(_T("%0.2f"), EntrustPrice);
	if (IsWindowValid(pEntrustPrice))
	{
		pEntrustPrice->SetWindowText(s_EntrustPrice);
	}
	return true;
}

bool CTradeDlg::SetCanSellTotal(const int Id_CanSellTotal, const CString &SecCode)
{
	CString s_str;
	UInt_64 enable_amount;
	GaineEable_amount(SecCode, enable_amount);
	s_str.Format(_T("%u"), enable_amount);
	GetDlgItem(Id_CanSellTotal)->SetWindowText(s_str);
	return true;
}

bool CTradeDlg::SetCanSellTotal(CSimpleStatic* pCanSellTotal, const CString &SecCode)
{
	CString s_str;
	UInt_64 enable_amount;
	GaineEable_amount(SecCode, enable_amount);
	s_str.Format(_T("%u"), enable_amount);
	if (IsWindowValid(pCanSellTotal))
	{
		pCanSellTotal->SetWindowText(s_str);
	}

	return true;
}

bool CTradeDlg::SetEntrustBalance(const int ID_EntrustPrice, const int ID_EntrustAmount, const int ID_EntrustBalance)
{
	CString s_str;
	double EntrustPrice;
	GainLegalValue(EntrustPrice, ID_EntrustPrice);
	UInt_64 EntrustAmount;
	GainLegalValue(EntrustAmount, ID_EntrustAmount);
	double EntrustBalance = EntrustPrice*EntrustAmount;
	s_str.Format(_T("%0.2f"), EntrustBalance);
	GetDlgItem(ID_EntrustBalance)->SetWindowText(s_str);
	return true;
}
/*fixing ���д����������ȫ������ �µ����������µ����ɫ*/
bool CTradeDlg::SetEntrustBalance(CSimpleEdit* pEntrustPrice, CSimpleEdit* pEntrustAmount, CSimpleStatic* pEntrustBalance)
{
	CString s_str;
	double EntrustPrice;
	GainLegalValue(EntrustPrice, pEntrustPrice);
	UInt_64 EntrustAmount;
	GainLegalValue(EntrustAmount, pEntrustAmount);
	double EntrustBalance = EntrustPrice*EntrustAmount;
	s_str.Format(_T("%0.2f"), EntrustBalance);
	if (IsWindowValid(pEntrustBalance))
	{
		pEntrustBalance->SetWindowText(s_str);
	}
	return true;
}

bool CTradeDlg::SetEnable_balance(const int ID_EnableBalance)
{
	/*CString s_str;

	CFund obj_CFund;
	if (SPtr_CData->GetFund(SPtr_CData->fund_account, obj_CFund) == false)
	{
		LOG(ERROR) << "GetFund fail";
		ExceptionInterrupt;
	}
	s_str.Format(_T("%0.2f"), obj_CFund.enable_balance);
	GetDlgItem(ID_EnableBalance)->SetWindowText(s_str);*/
	return true;
}

bool CTradeDlg::SetEnable_balance(CSimpleStatic* pEnableBalance, bool bFinancingBuy)
{
	CString s_str;
	double enable_balance = GainBalance_MaxEnable(bFinancingBuy);;
	s_str.Format(_T("%0.2f"), enable_balance);
	if (IsWindowValid(pEnableBalance))
	{
		pEnableBalance->SetWindowText(s_str);
	}
	return true;
}

bool CTradeDlg::SetDefaultBalance(bool &bCalculateByBalance, double &DefaultBalance, const int ID_DefaultBalance)
{
	CString s_DefaultBalance;
	if (true == bCalculateByBalance)
	{
		s_DefaultBalance.Format(_T("%0.0f"), DefaultBalance);
		(GetDlgItem(ID_DefaultBalance))->SetWindowText(s_DefaultBalance);
		GetDlgItem(ID_DefaultBalance)->EnableWindow(TRUE);
	}
	else
	{
		s_DefaultBalance = "0";
		(GetDlgItem(ID_DefaultBalance))->SetWindowText(s_DefaultBalance);
		GetDlgItem(ID_DefaultBalance)->EnableWindow(FALSE);
	}

	return true;
}

bool CTradeDlg::SetDefaultBalance(bool &bCalculateByBalance, double &DefaultBalance, CSimpleEdit* pDefaultBalance)
{
	CString s_DefaultBalance;
	if (IsWindowValid(pDefaultBalance))
	{
		if (true == bCalculateByBalance)
		{
			s_DefaultBalance.Format(_T("%0.0f"), DefaultBalance);
			pDefaultBalance->SetWindowText(s_DefaultBalance);
			pDefaultBalance->EnableWindow(TRUE);
		}
		else
		{
			s_DefaultBalance = "0";
			pDefaultBalance->SetWindowText(s_DefaultBalance);
			pDefaultBalance->EnableWindow(FALSE);
		}
	}

	return true;
}

bool CTradeDlg::SetBigCanBuyTotal(bool bFinancingBuy, CSimpleEdit* pEntrustPrice, CSimpleStatic* pBigCanBuyTotal)
{
	CString s_str;
	double EntrustPrice;
	GainLegalValue(EntrustPrice, pEntrustPrice);
	UInt_64 BigCanBuyTotal = 0;
	if (EntrustPrice == 0)
	{
		BigCanBuyTotal = 0;
	}
	else
	{
		BigCanBuyTotal = GainBigCanBuy(bFinancingBuy, EntrustPrice);
	}
	s_str.Format(_T("%u"), BigCanBuyTotal);
	if (IsWindowValid(pBigCanBuyTotal))
	{
		pBigCanBuyTotal->SetWindowText(s_str);
	}
	return true;
}

bool CTradeDlg::SetBottomTop(const CString &MarketCode, const CString &SecCode, const int ID_Bottom, const int ID_Top)
{
	CSecurity obj_CSecurity;
	CString s_str;
	if (SPtr_CData->GetSecurity(MarketCode, SecCode, obj_CSecurity) == false)
	{
		LOG(ERROR) << "GetSecurity fail";
		ExceptionInterrupt;
	}
	/*��ͣ��*/
	s_str.Format(_T("%0.2f"), obj_CSecurity.UpLimitPrice);
	GetDlgItem(ID_Top)->SetWindowText(s_str);
	/*��ͣ��*/
	s_str.Format(_T("%0.2f"), obj_CSecurity.DownLimitPrice);
	GetDlgItem(ID_Bottom)->SetWindowText(s_str);
	return true;
}

bool CTradeDlg::SetBottomTop(const CString &MarketCode, const CString &SecCode, CSimpleButton* pBottom, CSimpleButton* pTop)
{
	CSecurity obj_CSecurity;
	CString s_str;
	if (SPtr_CData->GetSecurity(MarketCode, SecCode, obj_CSecurity) == false)
	{
		LOG(ERROR) << "GetSecurity fail";
		ExceptionInterrupt;
	}
	/*��ͣ��*/
	s_str.Format(_T("%0.2f"), obj_CSecurity.UpLimitPrice);
	if (pTop != nullptr && IsWindow(pTop->GetSafeHwnd()))
	{
		pTop->SetWindowText(s_str);
	}

	/*��ͣ��*/
	s_str.Format(_T("%0.2f"), obj_CSecurity.DownLimitPrice);
	if (pBottom != nullptr && IsWindow(pBottom->GetSafeHwnd()))
	{
		pBottom->SetWindowText(s_str);
	}
	return true;
}

bool CTradeDlg::SetCanBuyTotal(bool bFinancingBuy, CSimpleEdit* pBEntrustPrice, CSimpleEdit* pBDefaultBalance, CSimpleStatic* p_BCanBuyTotal,
	CSimpleStatic* p_BigCanBuyTotal, bool bCalculateByBalance, const int DefaultAmount)
{
	CString s_str;
	double EntrustPrice;
	UInt_64 CanBuyTotal;
	GainLegalValue(EntrustPrice, pBEntrustPrice);
	if (EntrustPrice == 0)
	{
		CanBuyTotal = 0;
	}
	else
	{
		if (true == bCalculateByBalance)
		{
			/*����Ĭ���ʽ����*/
			double DefaultBalance;
			if (GainLegalValue(DefaultBalance, pBDefaultBalance) == false)
			{
				MessageBox("Ĭ���ʽ��쳣", "error", MB_OK);
			}
			CanBuyTotal = GainCanBuy(bFinancingBuy, DefaultBalance, EntrustPrice);
		}
		else
		{
			/*���Ȼ�ȡ�������ڱȽ�������Ϳ������*/
			UInt_64 BigCanBuyTotal;
			GainLegalValue(BigCanBuyTotal, p_BigCanBuyTotal);
			if (BigCanBuyTotal >= DefaultAmount)
			{
				CanBuyTotal = DefaultAmount;
			}
			else
			{
				CanBuyTotal = BigCanBuyTotal;
			}
		}
	}
	s_str.Format(_T("%u"), CanBuyTotal);
	if (IsWindowValid(p_BCanBuyTotal))
	{
		p_BCanBuyTotal->SetWindowText(s_str);
	}
	return true;
}

void CTradeDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case EventId_SetTimer_Invalidate:
		//CListCtrl_Alert.Invalidate();
		KillTimer(EventId_SetTimer_Invalidate);
		break;
	default:
		break;
	}
	CWnd::OnTimer(nIDEvent);
}

void CTradeDlg::ClearPosition_Order_Deal(CListCtrl &CListCtrl_Position, CListCtrl &CListCtrl_Order, 
	CListCtrl &CListCtrl_Deal)
{
	/*�ֲ���Ϊ���ܻ�������Ҫ���ڴ棬�������������������*/
	CListCtrl_Position.SetItemCount(0);
	SPtr_CData->ClearMPosition(SPtr_CData->fund_account);
	CListCtrl_Order.SetItemCount(0);
	CListCtrl_Deal.DeleteAllItems();
}

void CTradeDlg::ClearData_DisConnect(CGridCtrlEx* pGridPosition, CGridCtrlEx* pGridOrder, CGridCtrlEx* pGridDeal)
{
	/*�ֲ���Ϊ���ܻ�������Ҫ���ڴ棬�������������������*/
	if (IsWindowValid(pGridPosition))
	{
		pGridPosition->SetRowCount(1);
	}
	
	SPtr_CData->ClearMPosition(SPtr_CData->fund_account);
	SPtr_CData->ClearMOrder(SPtr_CData->fund_account);
	SPtr_CData->M_OrderList.clear();
	if (IsWindowValid(pGridOrder))
	{
		pGridOrder->SetRowCount(1);
	}
	if (IsWindowValid(pGridDeal))
	{
		pGridDeal->SetRowCount(1);
	}
}

bool CTradeDlg::IsWindowValid(CWnd* pWnd)
{
	bool bValid = false;
	if (pWnd != nullptr && IsWindow(pWnd->GetSafeHwnd()))
	{
		bValid = true;
	}
	else
	{
		ExceptionInterrupt;
		bValid = false;
	}
	return bValid;
}

bool CTradeDlg::InspectbRedraw(const CString &stock_code, const CString &stock_codeBuy)
{
	bool bResult = true;
	if (stock_code == stock_codeBuy)
	{
		bResult = false;
	}
	return bResult;
}

/*subDeal�������ʵʱˢ�¾Ͳ��ò��������㷨*/
bool CTradeDlg::RedrawSubDeal(CString SecCode, CGridCtrlEx* pDealEachGrid)
{
	if (!IsWindowValid(pDealEachGrid))
	{
		return false;
	}
	VDealEach.clear();
	CString stock_account;
	if (SPtr_CData->SecCode2StockAccount(SecCode, stock_account) == false)
	{
		LOG(ERROR) << "SecCode2StockAccount fail";
		ExceptionInterrupt;
		return false;
	}

	if (SPtr_CData->GetMDeal(SPtr_CData->fund_account, stock_account, ShowingEntrust_no, m_mapDealEach) == false)
	{
		LOG(ERROR) << "GetMDeal fail";
		ExceptionInterrupt;
		return false;
	}
	for (auto iter = m_mapDealEach.begin(); iter != m_mapDealEach.end(); iter++)
	{
		if (iter->first == "0")
		{
			LOG(ERROR) << "business_id is 0";
			ExceptionInterrupt;
			continue;
		}
		VDealEach.push_back(iter->second);
	}
	pDealEachGrid->SetRowCount(VDealEach.size() + 1);
	pDealEachGrid->Invalidate();
	return true;
}

bool CTradeDlg::RedrawDealSummary(CGridCtrlEx* pDealSummaryGrid)
{
	if (!IsWindowValid(pDealSummaryGrid))
	{
		return false;
	}
	
	m_mapDealSummary.clear();
	VDealSummary.clear();

	_Account obj_MAccount;
	_Account::iterator iter_MAccount;
	if (true == SPtr_CData->GetMAccount(SPtr_CData->fund_account, obj_MAccount))
	{
		for (iter_MAccount = obj_MAccount.begin(); iter_MAccount != obj_MAccount.end(); iter_MAccount++)
		{
			_Order obj_MOrder;
			_Order::iterator iter_MOrder;

			if (SPtr_CData->GetMOrder(SPtr_CData->fund_account, iter_MAccount->first, obj_MOrder) == false)
			{
				LOG(ERROR) << "GetMOrder fail";
				ExceptionInterrupt;
				continue;
			}

			if (obj_MOrder.size() > 0)
			{
				/*����ÿ��ί�е��µ�Deal*/
				for (iter_MOrder = obj_MOrder.begin(); iter_MOrder != obj_MOrder.end(); iter_MOrder++)
				{
					enumEntrustStatus entrust_status = iter_MOrder->second->entrust_status;
					if (BuChengDaiChe == entrust_status || BuChe == entrust_status || BuCheng == entrust_status ||
						YiCheng == entrust_status)
					{
						_Deal obj_MDeal;
						if (SPtr_CData->GetMDeal(SPtr_CData->fund_account, iter_MAccount->first, iter_MOrder->first, obj_MDeal) == false)
						{
							ErrorLog("GetMDeal fail");
							continue;
						}
						for (auto iter = obj_MDeal.begin(); iter != obj_MDeal.end(); iter++)
						{
							iter->second;/*�ɽ��ṹ��*/
							auto iter_DealSummary = m_mapDealSummary.find(iter->second->stock_code);
							if (iter_DealSummary == m_mapDealSummary.end())
							{
								/*û���ҵ���֤ȯ����*/
								CDealSummary obj_CDealSummary;
								obj_CDealSummary.stock_code = iter->second->stock_code;
								obj_CDealSummary.stock_name = iter->second->stock_name;
								m_mapDealSummary.insert(make_pair(iter->second->stock_code, obj_CDealSummary));
								iter_DealSummary = m_mapDealSummary.find(iter->second->stock_code);
							}

							if (iter->second->entrust_bs == _Buy)
							{
								iter_DealSummary->second.Buy_BusinessAmount += iter->second->business_amount;
								iter_DealSummary->second.Buy_BusinessBalance += iter->second->business_balance;
								iter_DealSummary->second.AverageBuyPrice = iter_DealSummary->second.Buy_BusinessBalance /
									iter_DealSummary->second.Buy_BusinessAmount;
							}
							else
							{
								iter_DealSummary->second.Sell_BusinessAmount += iter->second->business_amount;
								iter_DealSummary->second.Sell_BusinessBalance += iter->second->business_balance;
								iter_DealSummary->second.AverageSellPrice = iter_DealSummary->second.Sell_BusinessBalance /
									iter_DealSummary->second.Sell_BusinessAmount;
							}
						}
					}				
				}

			}
		}
	}
	else
	{
		LOG(ERROR) << "GetAccountMap fail";
		ExceptionInterrupt;
	}

	/*�ػ�ɽ����ܱ�*/
	for (auto iter = m_mapDealSummary.begin(); iter != m_mapDealSummary.end(); iter++)
	{
		VDealSummary.push_back(iter->second);
	}

	pDealSummaryGrid->SetRowCount(VDealSummary.size() + 1);
	pDealSummaryGrid->Invalidate();

	return true;
}

CString CTradeDlg::GetFontStyle()
{
	CString s_FontSize;
	ptree pt;
	try 
	{
		read_xml(s_ConfigPath, pt);
		s_FontSize = pt.get<string>("content.FontSize").c_str();
	}
	catch (std::exception& e)
	{
		LOG(ERROR) << "Error:" << e.what();
		ExceptionInterrupt;
		return "";
	}
	return s_FontSize;
}

void CTradeDlg::SetGlobalFont()
{
	CTradeDlg func;
	CString strStyle = func.GetFontStyle();
	if (FontStandard == strStyle.Trim())
	{
		s_hFontOrder = SingleFontSet.GetDefaultFont(DEFAULT_FONT_12B);
		s_hFontGrid = SingleFontSet.GetDefaultFont(DEFAULT_FONT_14N);
		s_hFontTab = SingleFontSet.GetDefaultFont(DEFAULT_FONT_14N);
		s_hFontTabSel = SingleFontSet.GetDefaultFont(DEFAULT_FONT_14N);
	}
	else if (FontMedium == strStyle.Trim())
	{
		s_hFontOrder = SingleFontSet.GetDefaultFont(DEFAULT_FONT_14B);
		s_hFontGrid = SingleFontSet.GetDefaultFont(DEFAULT_FONT_16N);
		s_hFontTab = SingleFontSet.GetDefaultFont(DEFAULT_FONT_16N);
		s_hFontTabSel = SingleFontSet.GetDefaultFont(DEFAULT_FONT_16N);
	}
	else if (FontBig == strStyle.Trim())
	{
		s_hFontOrder = SingleFontSet.GetDefaultFont(DEFAULT_FONT_16B);
		s_hFontGrid = SingleFontSet.GetDefaultFont(DEFAULT_FONT_16N);
		s_hFontTab = SingleFontSet.GetDefaultFont(DEFAULT_FONT_16N);
		s_hFontTabSel = SingleFontSet.GetDefaultFont(DEFAULT_FONT_16N);
	}
}

void CTradeDlg::CalculateTextRect(CString strText, HFONT hFont, CRect& rect)
{
	if (::IsWindow(m_hMainViewWnd))
	{
		CWnd* pWnd = FromHandle(m_hMainViewWnd);
		if (pWnd != nullptr)
		{
			CDC *pDC = pWnd->GetDC();
			CFont *pOld = pDC->SelectObject(CFont::FromHandle(hFont));
			pDC->DrawText(strText, rect, DT_CALCRECT | DT_LEFT | DT_VCENTER);
			pDC->SelectObject(pOld);
			pWnd->ReleaseDC(pDC);
		}
	}
	
}

void CTradeDlg::GetBtnRect(CString strText, HFONT hFont, CRect& rect)
{
	CRect rc;
	CalculateTextRect(strText, hFont, rc);
	
	int nHeight = 0;
	if (FontStandard == m_strStyle)
	{
		nHeight = 23;
	}
	else if (FontMedium == m_strStyle)
	{
		nHeight = 25;
	}
	else if (FontBig == m_strStyle)
	{
		nHeight = 27;
	}
	rect.SetRect(0, 0, rc.Width() + 20, nHeight);
}

void CTradeDlg::GetCheckRadioRect(CString strText, HFONT hFont, CRect& rect)
{
	CRect rc;
	CalculateTextRect(strText, hFont, rc);
	
	rect.SetRect(0, 0, rc.Width() + 18, rc.Height());
}

bool CTradeDlg::initBLog()
{
	ptree pt;
	try {
		read_xml(s_ConfigPath, pt);
		SPtr_CData->bLog_MarketAlert = pt.get<bool>("content.bLog_MarketAlert");
	}
	catch (std::exception& e)
	{
		ExceptionInterrupt;
		LOG(ERROR) << "initBLog fail Error:" << e.what();
		return false;
	}

	return true;
}


