#include "stdafx.h"
#include "T2Spi_Credit.h"

VOID CALLBACK OneMilliSecondProc(PVOID lpParameter, BOOLEAN ret)
{
	CT2Spi_Credit *pCT2Spi_Credit = (CT2Spi_Credit *)lpParameter;
	map<string, atomic_bool>::iterator iter;
	for (iter = pCT2Spi_Credit->M_QueryData.begin(); iter != pCT2Spi_Credit->M_QueryData.end(); iter++)
	{
		if (iter->second)
		{
			string SecCode = iter->first;
			/*���κβ��������ʽ��ֱֲ仯��ʱ�����һ���ʽ�ͳֲ�*/
			if (pCT2Spi_Credit->QueryFund() == false)
			{
				LOG(ERROR) << "QueryFund fail";
				ExceptionInterrupt;
			}

			if (pCT2Spi_Credit->QueryCreditAsset() == false)
			{
				LOG(ERROR) << "QueryCreditAsset fail";
				ExceptionInterrupt;
			}

			if (pCT2Spi_Credit->QuerySinglePosition(SecCode) == false)
			{
				LOG(ERROR) << "QuerySinglePosition fail";
				ExceptionInterrupt;
			}
			iter->second = false;
		}
	}
}

VOID CALLBACK OnProc_Order(PVOID lpParameter, BOOLEAN ret)
{
	CT2Spi_Credit *pCT2Spi_Credit = (CT2Spi_Credit *)lpParameter;
	if (pCT2Spi_Credit->bPostMessage)
	{
		tool::MyPostMessage(pCT2Spi_Credit->SPtr_CData->hwnd_TradeDlg, WM_RedrawOrder, pCT2Spi_Credit->bPostMessage);
	}
	pCT2Spi_Credit->bPostMessage = false;
}

CT2Spi_Credit::CT2Spi_Credit()
{
	if (!CreateTimerQueueTimer(&hTimer, NULL, WAITORTIMERCALLBACK(OneMilliSecondProc), (PVOID)this, DueTime, Timer_ms_Query, NULL))
	{
		LOG(ERROR) << "CreateTimerQueueTimer fail";
	}
	if (!CreateTimerQueueTimer(&hTimer_Order, NULL, WAITORTIMERCALLBACK(OnProc_Order), (PVOID)this, DueTime, Timer_ms_Order, NULL))
	{
		LOG(ERROR) << "CreateTimerQueueTimer fail";
	}
}

CT2Spi_Credit::~CT2Spi_Credit()
{
	if (!DeleteTimerQueueTimer(NULL, hTimer, NULL))
	{
		LOG(ERROR) << "DeleteTimerQueueTimer fail";
	}
	if (!DeleteTimerQueueTimer(NULL, hTimer_Order, NULL))
	{
		LOG(ERROR) << "DeleteTimerQueueTimer fail";
	}
}

void CT2Spi_Credit::OnClose()
{
	if (SPtr_CData->bRun_MainPageDlg == true && false == SPtr_CData->bBeginRelease)
	{
		/*�쳣�˳�����*/
		LOG(ERROR) << "CT2Spi_Credit Close.........";
		MessageBox(SPtr_CData->hwnd_MainPageDlg, _T("�����жϣ������µ�¼"), "error", 0);
		/*�˳�����*/
		if (PostMessage(SPtr_CData->hwnd_MainPageDlg, WM_AbnormalExit, 0, 0) == 0)
		{
			LOG(ERROR) << "PostMessage fail";
			ExceptionInterrupt;
		}
	}
}

void CT2Spi_Credit::OnDisConnect()
{
	static int count = 0;
	if (count % 5 == 0)
	{
		PostMessage(SPtr_CData->hwnd_TradeDlg, WM_DisConnect_T2, NULL, NULL);
	}
	count++;
}

void CT2Spi_Credit::OnConnected()
{
	PostMessage(SPtr_CData->hwnd_TradeDlg, WM_Connected_T2, NULL, NULL);

	LOG(ERROR) << "OnConnected" << endl;
	if (tool::initSubscribe(SPtr_CData, pCApiFun, Api_Asy) != true)
	{
		return;
	}
}

bool CT2Spi_Credit::OnLogin(const Value &root)
{
	if (root["json"].isNull())
	{
		/*δ�ҵ� ��¼�Ҳ�����������쳣*/
		LOG(ERROR) << "OnLogin no json";
		ExceptionInterrupt;
		return false;
	}

	int count = root["json"].size();
	for (int i = 0; i< count; i++)
	{
		if (tool::VerifyElement(root, i,SPtr_CData))
		{
			SPtr_CData->branch_no = root["json"][i]["branch_no"].asString();
			SPtr_CData->sysnode_id = root["json"][i]["sysnode_id"].asString();

			string uft_sysnode_id = root["json"][i]["uft_sysnode_id"].asString();
			if (uft_sysnode_id != "0" && uft_sysnode_id == "51")
			{
				SPtr_CData->sysnode_id = uft_sysnode_id;
			}
			if (root["json"][i]["asset_prop"].asString()[0] != '7')
			{
				MessageBox(NULL, "��ʹ�������˻���¼", "��¼�쳣", MB_OK);
				return false;
			}
			string s_ClientRights = root["json"][i]["client_rights"].asString();
			if (s_ClientRights.find("E") == string::npos)
			{
				/*û�ҵ�E(����Ȩ��ֱ���˳�)*/
				MessageBox(NULL, "ȱ��Ȩ��E(ί�С��ɽ�����Ȩ��)�������µ�½", "��¼�쳣", MB_OK);
				return false;
			}
		}
		else
		{
			LOG(ERROR) << "function id:" << root["function_id"].asString() << " a element illegal";
			ExceptionInterrupt;
			return false;//ֻ��һ��Ԫ�أ�����Ҫ��������ж��Ƿ��¼�ɹ������һ��Ҫ��return
		}
	}
	
	return true;
}

bool CT2Spi_Credit::OnQueryStockAccount(const Value &root)
{
	if (root["json"].isNull())
	{
		/*δ�ҵ� �ʽ��˻���û�йɶ��˻��ǿ��ܵģ��������ȷ�ġ�����֮�⻹�в�ֲ֡��ɽ���ί�з���NULLҲ��������*/
		return true;
	}

	int count = root["json"].size();
	for (int i = 0; i < count; i++)
	{
		if (tool::VerifyElement(root, i, SPtr_CData) == true)
		{
			/*��T2��msg_idΪ0������Ҳ���error_no�Ĺ��ܺţ�Ĭ����ȷ������ҵõ�Ҫȷ����Ϊ0�Ŵ�����ȷ����Щ�����ӿ���ȷ��ʱ�򲻷���error_no��ֻ���ڳ����ʱ��Ż᷵��*/
			CString market_code = "";
			CString exchange_type = root["json"][i]["exchange_type"].asString().c_str();
			switch (exchange_type[0]) 
			{
			case '1':
			{
				market_code = SSE;
				CAccount obj_CAccount;
				CString fund_account = root["json"][i]["fund_account"].asString().c_str();//�ʽ��˻�
				obj_CAccount.stock_account = root["json"][i]["stock_account"].asString().c_str();//�ɶ��˻�
				obj_CAccount.market_code = market_code;
				if (SPtr_CData->SetAccount(fund_account, obj_CAccount) == false)
				{
					LOG(ERROR) << "SetAccount fail";
					ExceptionInterrupt;
				}
				break;
			}
			case '2':
			{
				market_code = SZSE;
				CAccount obj_CAccount;
				CString fund_account = root["json"][i]["fund_account"].asString().c_str();//�ʽ��˻�
				obj_CAccount.stock_account = root["json"][i]["stock_account"].asString().c_str();//�ɶ��˻�
				obj_CAccount.market_code = market_code;
				if (SPtr_CData->SetAccount(fund_account, obj_CAccount) == false)
				{
					LOG(ERROR) << "SetAccount fail";
					ExceptionInterrupt;
				}
				break;
			}
			default:
				ErrorLog("abnormal exchange_type");
				break;
			}
		}
		else
		{
			LOG(ERROR) << "function id:" << root["function_id"].asString() << " a element illegal";
			ExceptionInterrupt;
			/*����continueԭ����ֻҪ��һ�������͸���Ϊ��ѯ�ɶ��˻��ɹ��������Ͷ�Ӧ�źţ���������źŻ��������⣬����ֲ֣���һ�����˾��϶���ѯʧ�ܲ�ˢ��*/
			return false;
		}
	
	}
	
	return true;
}

bool CT2Spi_Credit::OnRevoke(const Value &root)
{
	//uft��ͨ��entrust_no��ί�е���Ϊ���ӣ�����ڳ���Ӧ���в������ʽ�ͳֲ�
	//if (root["json"].isNull())
	//{
	//	LOG(ERROR) << "OnRevoke no json";
	//	ExceptionInterrupt;
	//	return false;
	//}

	//int count = root["json"].size();
	//for (int i = 0; i < count; i++)
	//{
	//	if (tool::VerifyElement(root, i, SPtr_CData))
	//	{
	//		string stock_code;
	//		stock_code = root["json"][i]["stock_code"].asString().c_str();
	//		UpdateFund_Position(stock_code);
	//	}
	//	else
	//	{
	//		LOG(ERROR) << "function id:" << root["function_id"].asString() << " a element illegal";
	//		return false;//ֻ��һ��Ԫ�أ�����Ҫ��������ж��Ƿ��¼�ɹ������һ��Ҫ��return
	//	}
	//}
	return true;
}

/*Position*/
bool CT2Spi_Credit::QuerySinglePosition(const string &stock_code)
{
	string s_Fun335102;
	GainQuerySinglePosition(s_Fun335102, stock_code);

	if (tool::SendOrder(pCApiFun, Api_Asy,s_Fun335102,SPtr_CData) == false)
	{
		return false;
	}
	return true;
}

bool CT2Spi_Credit::GainQuerySinglePosition(string &s_str, const string &stock_code)
{
	/*�ֲֲ�ѯ*/
	Json::Value obj_Value;
	obj_Value["function_id"] = "335102";
	obj_Value["op_entrust_way"] = op_entrust_way_����ί��;
	obj_Value["op_station"] = op_station_My;
	obj_Value["op_branch_no"] = SPtr_CData->branch_no;
	obj_Value["branch_no"] = SPtr_CData->branch_no;

	obj_Value["sysnode_id"] = SPtr_CData->sysnode_id;

	obj_Value["fund_account"] = SPtr_CData->s_user;
	obj_Value["password"] = SPtr_CData->s_pass;
	obj_Value["password_type"] = password_type_��������;
	obj_Value["stock_code"] = string(stock_code);
	obj_Value["asset_prop"] = AssetProp_�����˻�;

	obj_Value["position_str"] = "";
	obj_Value["request_num"] = "1";
	s_str = obj_Value.toStyledString();
	return true;
}

bool CT2Spi_Credit::OnQuerySinglePosition(const Value &root)
{
	bool bBeginRedrawPosition = false;
	if (root["json"].isNull())
	{
		return true;
	}

	int count = root["json"].size();

	if (count >= SingleQuerySize)
	{
	}
	else
	{
		bBeginRedrawPosition = true;
	}
	for (int i = 0; i < count; i++)
	{
		if (tool::VerifyElement(root, i, SPtr_CData) == true)
		{
			CPosition obj_CPosition;

			CString fund_account = root["json"][i]["fund_account"].asString().c_str();//�ʽ��˻�
			CString stock_account = root["json"][i]["stock_account"].asString().c_str();//�ɶ��˻�

			obj_CPosition.stock_name = root["json"][i]["stock_name"].asString().c_str();//��Ʊ����
			obj_CPosition.stock_code = root["json"][i]["stock_code"].asString().c_str();//��Ʊ����
			obj_CPosition.current_amount = convert<UInt_64>(root["json"][i]["current_amount"].asString());//��Ʊ���
			obj_CPosition.enable_amount = convert<UInt_64>(root["json"][i]["enable_amount"].asString());//��������
			obj_CPosition.market_value = convert<double>(root["json"][i]["market_value"].asString());//��ֵ

			obj_CPosition.income_balance = convert<double>(root["json"][i]["income_balance"].asString());//ӯ��
			obj_CPosition.cost_price = convert<double>(root["json"][i]["cost_price"].asString());//�ɱ���
			obj_CPosition.last_price = convert<double>(root["json"][i]["last_price"].asString());//���¼�
			obj_CPosition.profit_ratio = convert<double>(root["json"][i]["profit_ratio"].asString());

			if (SPtr_CData->SetPosition(fund_account, stock_account, obj_CPosition) == false)
			{
				ErrorLog("SetPosition fail");
				return false;
			}
		}
		else
		{
			LOG(ERROR) << "function id:" << root["function_id"].asString() << " a element illegal";
			ExceptionInterrupt;
			return false;
		}
	}
	if (true == bBeginRedrawPosition)
	{
		if (SPtr_CData->hwnd_TradeDlg == NULL)
		{
			SPtr_CData->Queue_WmMessage.push(WM_ReDrawPosition);
		}
		else
		{
			if (::PostMessage(SPtr_CData->hwnd_TradeDlg, WM_ReDrawPosition, 0, 0) == 0)
			{
				ErrorLog("PostMessage fail");
			}
		}
	}
	return true;
}

bool CT2Spi_Credit::OnQueryCreditAsset(const Value &root)
{
	if (root["json"].isNull())
	{
		return true;
	}

	int count = root["json"].size();
	for (int i = 0; i < count; i++)
	{
		if (tool::VerifyElement(root, i, SPtr_CData) == true)
		{
			VecCreditAsset VCreditAsset;
			VCreditAsset.resize(Size_Row);
			InitVCreditAsset(VCreditAsset);
			FillVCreditAsset(VCreditAsset,root,i);
			
			if (SPtr_CData->SetVCreditAsset(SPtr_CData->fund_account, VCreditAsset) == false)
			{
				ErrorLog("SetVCreditAsset fail");
				return false;
			}
		}
		else
		{
			LOG(ERROR) << "function id:" << root["function_id"].asString() << " a element illegal";
			ExceptionInterrupt;
			return false;
		}
	}

	if (PostMessage(SPtr_CData->hwnd_TradeDlg, WM_RedrawCreditAsset, 0, 0) == 0)
	{
		ErrorLog("PostMessage fail");
	}
	
	return true;
}

void CT2Spi_Credit::InitVCreditAsset(VecCreditAsset &VCreditAsset)
{
	VCreditAsset.resize(Size_Row);
	for (unsigned int i = 0; i < VCreditAsset.size(); i++)
		VCreditAsset[i].resize(Siz_Column);

	VCreditAsset[0][0] = MaintenanceGuaranteeRatio;
	VCreditAsset[0][2] = "���ʿ��ö��";
	VCreditAsset[0][4] = "��ȯ���ö��";

	VCreditAsset[1][0] = "���ñ�֤��";
	VCreditAsset[1][2] = "�������ö��";
	VCreditAsset[1][4] = "��ȯ���ö��";

	VCreditAsset[2][0] = "��ծ�ܸ�ӯ";
	VCreditAsset[2][2] = "���ʺ�Լ���";
	VCreditAsset[2][4] = "��ȯ��Լ���";

	VCreditAsset[3][0] = "���ñ�֤��";
	VCreditAsset[3][2] = "���ʺ�Լ����";
	VCreditAsset[3][4] = "��ȯ��Լ����";

	VCreditAsset[4][0] = "�򵣱�Ʒ�����ʽ�";
	VCreditAsset[4][2] = "���ʺ�Լ��Ϣ";
	VCreditAsset[4][4] = "��ȯ��Լ��Ϣ";

	VCreditAsset[5][0] = "�ֽ𻹿�����ʽ�";
	VCreditAsset[5][2] = "������ֵ";
	VCreditAsset[5][4] = "��ȯ��ֵ";

	VCreditAsset[6][0] = "�����ʱ�Ŀ����ʽ�";
	VCreditAsset[6][2] = "���ʺ�Լӯ��";
	VCreditAsset[6][4] = "��ȯ��Լӯ��";

	VCreditAsset[7][0] = "֤ȯ��ֵ";
	VCreditAsset[7][2] = "�������ñ�֤��";
	VCreditAsset[7][4] = "��ȯ���ñ�֤��";

	VCreditAsset[8][0] = "��ȡ���";
	VCreditAsset[8][2] = "�ֽ��ʲ�";
	VCreditAsset[8][4] = "��ȯ���������ܶ�";

	VCreditAsset[9][0] = "��ȯ�������";
	VCreditAsset[9][2] = "�����ʲ�";
	VCreditAsset[9][4] = "��ծ�ܶ�";

	VCreditAsset[10][0] = "";
	VCreditAsset[10][2] = "��������";
	VCreditAsset[10][4] = "���ʶ������";

	VCreditAsset[11][0] = "";
	VCreditAsset[11][2] = "���ʲ�";
	VCreditAsset[11][4] = "��ȯ��ȯ�����ʽ�";
}

string CT2Spi_Credit::GainPer_assurescale_value(const Value &root, const int i)
{
	//fin_income + slo_income
	string per_assurescale_value;
	string s_str = root["json"][i]["fin_income"].asString().c_str();
	double fin_income = convert<double>(s_str);
	s_str = root["json"][i]["slo_income"].asString().c_str();
	double slo_income = convert<double>(s_str);
	per_assurescale_value = to_string(fin_income + slo_income);
	return per_assurescale_value;
}

bool CT2Spi_Credit::GainFetch_balance(string &fetch_balance)
{
    string s_Fun332255;
	tool::GainQueryFund332255(s_Fun332255, SPtr_CData);
	int RefId_HS = tool::SendOrder(pCApiFun, Api_Syn, s_Fun332255, SPtr_CData);
	if (RefId_HS < 0)
	{
		ErrorLog("abnormal RefId_HS");
		return false;
	}
	int ret = pCApiFun->Api_T2_Syn->RecvMsg();
	if (ret < 0)
	{
		ErrorLog(pCApiFun->Api_T2_Syn->GetLastErrorMsg());
		tool::ExceptionHandle_RecvMsg();
		return false;
	}
	char* pRespData = new char[ret + 1];
	ret = pCApiFun->Api_T2_Syn->GetJsonValue(pRespData);

	Json::Reader reader;
	Json::Value root;

	if (!reader.parse(string(pRespData), root, false))
	{
		ExceptionInterrupt;
		LOG(ERROR) << "parse fail";
		return false;
	}
	fetch_balance = root["json"][0u]["fetch_balance"].asString();
	delete[] pRespData;
	return true;
}

void CT2Spi_Credit::FillVCreditAsset(VecCreditAsset &VCreditAsset, const Value &root, const int i)
{
	VCreditAsset[0][1] = root["json"][i]["per_assurescale_value"].asString();//ά�ֵ������� N16.4
	VCreditAsset[0][3] = root["json"][i]["fin_enable_quota"].asString();
	VCreditAsset[0][5] = root["json"][i]["slo_enable_quota"].asString();

	VCreditAsset[1][1] = root["json"][i]["enable_bail_balance"].asString();
	VCreditAsset[1][3] = root["json"][i]["fin_used_quota"].asString();
	VCreditAsset[1][5] = root["json"][i]["slo_used_quota"].asString();
	
	VCreditAsset[2][1] = GainPer_assurescale_value(root, i); //fin_income + slo_income
	VCreditAsset[2][3] = root["json"][i]["fin_compact_balance"].asString();
	VCreditAsset[2][5] = root["json"][i]["slo_compact_balance"].asString();

	VCreditAsset[3][1] = root["json"][i]["used_bail_balance"].asString();
	VCreditAsset[3][3] = root["json"][i]["fin_compact_fare"].asString();
	VCreditAsset[3][5] = root["json"][i]["slo_compact_fare"].asString();

	VCreditAsset[4][1] = root["json"][i]["assure_enbuy_balance"].asString();
	VCreditAsset[4][3] = root["json"][i]["fin_compact_interest"].asString();
	VCreditAsset[4][5] = root["json"][i]["slo_compact_interest"].asString();

	VCreditAsset[5][1] = root["json"][i]["fin_enrepaid_balance"].asString();
	VCreditAsset[5][3] = root["json"][i]["fin_market_value"].asString();
	VCreditAsset[5][5] = root["json"][i]["slo_market_value"].asString();

	VCreditAsset[6][1] = root["json"][i]["fin_enbuy_balance"].asString();
	VCreditAsset[6][3] = root["json"][i]["fin_income"].asString();
	VCreditAsset[6][5] = root["json"][i]["slo_income"].asString();

	VCreditAsset[7][1] = root["json"][i]["market_value"].asString();
	VCreditAsset[7][3] = root["json"][i]["fin_used_bail"].asString();
	VCreditAsset[7][5] = root["json"][i]["slo_used_bail"].asString();

	string fetch_balance;
	GainFetch_balance(fetch_balance);
	VCreditAsset[8][1] = fetch_balance;//��ȡ��ȡ�ʽ�
	VCreditAsset[8][3] = root["json"][i]["cash_asset"].asString();
	VCreditAsset[8][5] = root["json"][i]["slo_sell_balance"].asString();

	VCreditAsset[9][1] = root["json"][i]["slo_max_quota"].asString();
	VCreditAsset[9][3] = root["json"][i]["assure_asset"].asString();
	VCreditAsset[9][5] = root["json"][i]["total_debit"].asString();

	VCreditAsset[10][1] = "";
	VCreditAsset[10][3] = root["json"][i]["other_fare"].asString();
	VCreditAsset[10][5] = root["json"][i]["fin_max_quota"].asString();

	VCreditAsset[11][1] = "";
	VCreditAsset[11][3] = root["json"][i]["net_asset"].asString();
	VCreditAsset[11][5] = root["json"][i]["slo_enrepaid_balance"].asString();
}

string CT2Spi_Credit::Modifystring(string s_str)
{
	string s_dst;
	double d_tmp;
	d_tmp = convert<double>(s_str);
	d_tmp = tool::round(d_tmp, 2);

	return s_dst;
}

/*fund*/
bool CT2Spi_Credit::OnQueryFund(const Value &root)
{
	if (root["json"].isNull())
	{
		/*δ�ҵ� ��ѯ�ʽ�Ϊ�ճ����쳣*/
		LOG(ERROR) << "OnQueryFund no json";
		ExceptionInterrupt;
		return false;
	}

	int count = root["json"].size();
	for (int i = 0; i < count; i++)
	{
		if (tool::VerifyElement(root, i, SPtr_CData) == true)
		{
			CFund obj_CFund;
			obj_CFund.fund_account = SPtr_CData->fund_account;
			//��ǰ��� �����ʽ� �����ʽ� �ⶳ�ʽ� �ر������� �ر��������
			obj_CFund.current_balance = convert<double>(root["json"][i]["current_balance"].asString().c_str());//��ǰ���
			obj_CFund.enable_balance = convert<double>(root["json"][i]["enable_balance"].asString().c_str());//�����ʽ�
			obj_CFund.frozen_balance = convert<double>(root["json"][i]["frozen_balance"].asString().c_str());//�����ʽ�
			obj_CFund.unfrozen_balance = convert<double>(root["json"][i]["unfrozen_balance"].asString().c_str());//�ⶳ�ʽ�
			obj_CFund.real_buy_balance = convert<double>(root["json"][i]["real_buy_balance"].asString().c_str());//�ر�������
			obj_CFund.real_sell_balance = convert<double>(root["json"][i]["real_sell_balance"].asString().c_str());//�ر��������
			if (SPtr_CData->SetFund(obj_CFund) == false)
			{
				LOG(ERROR) << "SetFund fail";
				ExceptionInterrupt;
			}
		}
		else
		{
			LOG(ERROR) << "function id:" << root["function_id"].asString() << " a element illegal";
			ExceptionInterrupt;
			return false;
		}
	}
	return true;
}

bool CT2Spi_Credit::QueryFund()
{
	string s_Fun335101;
	tool::GainQueryFund335101(s_Fun335101,SPtr_CData);
	int RefId_HS = tool::SendOrder(pCApiFun,Api_Asy, s_Fun335101, SPtr_CData);
	if (RefId_HS < 0)
	{
		LOG(ERROR) << "abnormal RefId_HS";
		return false;
	}
	SPtr_CData->SetRefId_T2(RefId_HS, RefType_335101_NoFirstQueryFund);
	return true;
}

bool CT2Spi_Credit::QueryCreditAsset()
{
	string s_Fun335504;
	tool::GainQueryCreditAsset335504(s_Fun335504, SPtr_CData);
	int RefId_HS = tool::SendOrder(pCApiFun, Api_Asy, s_Fun335504, SPtr_CData);
	if (RefId_HS < 0)
	{
		ErrorLog("abnormal RefId_HS");
		return false;
	}
	return true;
}

void CT2Spi_Credit::updateEntrust_status(COrder &obj_COrder, const string &entrust_status,string cancel_info)
{
	switch (entrust_status[0])
	{
	case '0'://δ��
	{
		obj_COrder.entrust_status = WeiBao;
		break;
	}
	case '1'://����
	{
		obj_COrder.entrust_status = DaiBao;
		break;
	}
	case '2'://�ѱ�
	{
		obj_COrder.entrust_status = YiBao;
		break;
	}
	case '3'://�ѱ�����
	{
		obj_COrder.entrust_status = YiBaoDaiChe;
		break;
	}
	case '4'://���ɴ���
	{
		obj_COrder.entrust_status = BuChengDaiChe;
		break;
	}
	case '5'://����
	{
		obj_COrder.entrust_status = BuChe;
		break;
	}
	case '6'://�ѳ�
	{
		obj_COrder.entrust_status = YiChe;
		break;
	}
	case '7'://����
	{
		obj_COrder.entrust_status = BuCheng;
		break;
	}
	case '8'://�ѳ�
	{
		obj_COrder.entrust_status = YiCheng;
		break;
	}
	case '9'://�ϵ�
	{
		obj_COrder.entrust_status = FeiDan;
		LOG(ERROR) << "�ϵ�ԭ��:cancel_info:" << cancel_info<< " entrust_no"<<obj_COrder.entrust_no;
		break;
	}
	default:
		break;
	}
}

void CT2Spi_Credit::updateEntrust_bs(COrder &obj_COrder, const string &entrust_bs)
{
	switch (entrust_bs[0])
	{
	case '1':
	{
		obj_COrder.entrust_bs = _Buy;
		break;
	}
	case '2':
	{
		obj_COrder.entrust_bs = _Sell;
		break;
	}
	default:
		break;
	}
}


void CT2Spi_Credit::updateEntrust_bs(CDeal &obj_CDeal, const string &entrust_bs)
{
	switch (entrust_bs[0])
	{
	case '1':
	{
		obj_CDeal.entrust_bs = _Buy;
		break;
	}
	case '2':
	{
		obj_CDeal.entrust_bs = _Sell;
		break;
	}
	default:
		break;
	}
}

void CT2Spi_Credit::updateEntrust_type(COrder &obj_COrder, const string &entrust_type)
{
	switch (entrust_type[0])
	{
	case '6':
	{
		obj_COrder.entrust_type = enumXinYongRongZi;
		break;
	}
	case '9':
	{
		obj_COrder.entrust_type = enumXinYongJiaoYi;
		break;
	}
	default:
		ErrorLog("abnormal entrust_type");
		break;
	}
}

bool CT2Spi_Credit::OnSendOrder(const Value &root)
{
	if (root["json"].isNull())
	{
		/*δ�ҵ� false�˳�����*/
		ErrorLog("OnSendOrder no json");
		return false;
	}

	int count = root["json"].size();
	for (int i = 0; i < count; i++)
	{
		if (tool::VerifyElement(root, i, SPtr_CData) == true)
		{
			/*ί�з��ͷ���*/
			CString stock_account;
			COrder obj_COrder;
			
			Type_OrderList::iterator iter_RawOrder = SPtr_CData->M_OrderList.find(convert<int>(root["ref_id"].asString()));
			if (SPtr_CData->M_OrderList.end() == iter_RawOrder)
			{
				ErrorLog("abanormal ref_id");
			}
			obj_COrder.stock_name = iter_RawOrder->second.stock_name;
			obj_COrder.stock_code = iter_RawOrder->second.stock_code;
			obj_COrder.entrust_bs = iter_RawOrder->second.entrust_bs;
			obj_COrder.entrust_price = iter_RawOrder->second.entrust_price;
			obj_COrder.entrust_amount = iter_RawOrder->second.entrust_amount;

			obj_COrder.entrust_no = convert<UInt_64>(root["json"][i]["entrust_no"].asString());//ί�б��
			if (VerifyEntrust_no(obj_COrder.entrust_no) == false)
			{
				return false;
			}
			if (SPtr_CData->SecCode2StockAccount(obj_COrder.stock_code, stock_account) == false)
			{
				ErrorLog("SecCode2StockAccount fail");
				return false;
			}

			tool::WriteCheckList(SPtr_CData,root, i, stock_account);
			/*���жϵ����Ƿ���ڣ����ھ�ʲô������������ί���������Ѿ����걨ʱ����¹���*/
			if (VerifybExist(stock_account, obj_COrder.entrust_no) == true)
			{
				return true;
			}
			if (SPtr_CData->SetOrder(SPtr_CData->fund_account, stock_account, obj_COrder) == false)
			{
				ErrorLog("SetOrder return fail");
				return false;
			}
			UpdateFund_Position(string(obj_COrder.stock_code));
		}
		else
		{
			LOG(ERROR) << "function id:" << root["json"][i]["function_id"].asString() << " a element illegal";
			return false;
		}
	}

	bPostMessage = true;
	return true;
}


void CT2Spi_Credit::OnRecvJsonMsg(char* pRespdata)
{
	/*���ĵĺϷ���У���Ϊ�����������ж��Ƿ�ɹ�ת��(msg_idΪ0),����ж��Ƿ������ݣ�û������û��json�ֶ�
	�����������ͨ��error_no�ж��Ƿ�Ϸ������� �Ҳ����Ϸ����ҵõ�Ϊ0�Ϸ�*/
	pRsp = pRespdata;
	DealQuit(SPtr_CData->bBeginRelease);
	Json::Reader reader;
	Json::Value root;
	
	if (!reader.parse(string(pRespdata), root, false))
	{
		return;
	}
	
	int function_id = convert<int>(root["function_id"].asString());
	switch (function_id)
	{
	case 331100://T2��½
	{
		if (OnLogin(root) == true)
		{
			SetEvent(SPtr_CData->LoginT2_Event);
		}
		break;
	}
	case 331300://֤ȯ�ɶ���Ϣ��ѯ
	{
		if (OnQueryStockAccount(root) == true)
		{
			SetEvent(SPtr_CData->QueryStockAccount_Event);
		}
		else
		{
			LOG(ERROR) << "warning:OnQueryStockAccount return fail in OnReceivedBiz";
			ExceptionInterrupt;
		}
		break;
	}
	case 335002://ί���µ�����
	{
		if (SPtr_CData->TestSpeed == 1)
		{
			GetSystemTime(&(SPtr_CData->systime_OnSendOrder));
			LOG(ERROR) << "Recv Rsp of SendOrder consume time:" << SPtr_CData->systime_OnSendOrder.wSecond * 1000 + SPtr_CData->systime_OnSendOrder.wMilliseconds
				- (SPtr_CData->systime_SendOrder.wSecond * 1000 + SPtr_CData->systime_SendOrder.wMilliseconds) << " ����";
		}
		OnSendOrder(root);
		break;
	}
	case 335004://ί�г�������
	{
		OnRevoke(root);
		break;
	}
	case 335101://�ʽ��˻���ѯ
	{
		/*���ǵ�������ؾͱ���û��Ҫ�������������̣߳�ˢ��һ����*/
		if (OnQueryFund(root) == true)
		{
			int ref_id = convert<int>(root["ref_id"].asString());
			int MyRefId;
			if (SPtr_CData->GetEraseRefId_T2(ref_id, MyRefId) == false)
			{
				return;
			}
			switch (MyRefId)
			{
			case RefType_335101_InitFund:
			{
				SetEvent(SPtr_CData->InitFund_Event);
				break;
			}
			default:
				break;
			}
			if (SPtr_CData->hwnd_TradeDlg == NULL)
			{
				SPtr_CData->Queue_WmMessage.push(WM_RedrawFund);
			}
			else if (PostMessage(SPtr_CData->hwnd_TradeDlg, WM_RedrawFund, 0, 0) == 0)
			{
				ErrorLog("PostMessage fail");
			}
		}
		break;
	}
	case 335102://�����ֲֲ�ѯ
	{
		OnQuerySinglePosition(root);
		break;
	}
	case 335504:
		OnQueryCreditAsset(root);
		break;
	case 620001:
		On620001(root);
		break;
	case 620003://����(ί�С��ɽ�)����
	{
		/*fixing ������ȯ��������12:55������ʧ�����ٽ���������������Ϊδ�������µ�¼����Ϊ��������������µ�¼�ͻᵼ�µ�1������Ϊ�Ǵ����޷�����*/
		LOG(INFO) << pRsp;/*fixing*/
		OnSubscribe(root);
		break;
	}
	default:
		break;
	}
	return;
}
