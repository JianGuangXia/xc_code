#include "stdafx.h"
#include "T2Spi_Fast.h"

VOID CALLBACK OneMilliSecondProc(PVOID lpParameter, BOOLEAN ret)
{
	CT2Spi_Fast *pCT2Spi_Fast = (CT2Spi_Fast *)lpParameter;
	map<string, atomic_bool>::iterator iter;
	for (iter = pCT2Spi_Fast->M_QueryData.begin();iter != pCT2Spi_Fast->M_QueryData.end(); iter++)
	{
		if (iter->second)
		{
			string SecCode = iter->first;
			/*���κβ��������ʽ��ֱֲ仯��ʱ�����һ���ʽ�ͳֲ�*/
			if (pCT2Spi_Fast->QueryFund() == false)
			{
				LOG(ERROR) << "OnQueryFund fail";
				ExceptionInterrupt;
			}

			if (pCT2Spi_Fast->QuerySinglePosition(SecCode) == false)
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
	CT2Spi_Fast *pCT2Spi_Fast = (CT2Spi_Fast *)lpParameter;
	if (pCT2Spi_Fast->bPostMessage)
	{
		tool::MyPostMessage(pCT2Spi_Fast->SPtr_CData->hwnd_TradeDlg, WM_RedrawOrder, pCT2Spi_Fast->bPostMessage);
	}
	pCT2Spi_Fast->bPostMessage = false;
}

CT2Spi_Fast::CT2Spi_Fast()
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

CT2Spi_Fast::~CT2Spi_Fast()
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

void CT2Spi_Fast::OnClose()
{
	if (SPtr_CData->bRun_MainPageDlg == true && false == SPtr_CData->bBeginRelease)
	{
		/*�쳣�˳�����*/
		LOG(ERROR) << "CT2Spi_Fast Close.........";
		MessageBox(SPtr_CData->hwnd_MainPageDlg, _T("�����жϣ������µ�¼"), "error", 0);
		/*�˳�����*/
		if (PostMessage(SPtr_CData->hwnd_MainPageDlg, WM_AbnormalExit, 0, 0) == 0)
		{
			LOG(ERROR) << "PostMessage fail";
			ExceptionInterrupt;
		}
	}
}

void CT2Spi_Fast::OnDisConnect()
{
	static int count = 0;
	if (count %5 == 0)
	{
		PostMessage(SPtr_CData->hwnd_TradeDlg, WM_DisConnect_T2,NULL,NULL);
	}
	count++;
}

void CT2Spi_Fast::OnConnected()
{
	PostMessage(SPtr_CData->hwnd_TradeDlg, WM_Connected_T2, NULL, NULL);

	LOG(ERROR) << "OnConnected" << endl;
	if (tool::initSubscribe(SPtr_CData, pCApiFun, Api_Asy) != true)
	{
		return ;
	}
}

bool CT2Spi_Fast::OnLogin(const Value &root)
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

			string sysnode_id = root["json"][i]["sysnode_id"].asString();
			string uft_sysnode_id = root["json"][i]["uft_sysnode_id"].asString();
			if (uft_sysnode_id != "0" && uft_sysnode_id == "31") //���Ժ�������һ�����㵽�����ļ���
			{
				SPtr_CData->sysnode_id = uft_sysnode_id;
			}
			else
			{
				SPtr_CData->sysnode_id = sysnode_id;
			}
			
			if (root["json"][i]["asset_prop"].asString()[0] != '0')
			{
				MessageBox(NULL, "��ʹ����ͨ�˻���¼", "��¼�쳣", MB_OK);
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
			return false;//ֻ��һ��Ԫ�أ�����Ҫ��������ж��Ƿ��¼�ɹ������һ��Ҫ��return
		}
	}	
	return true;
}


bool CT2Spi_Fast::OnQueryStockAccount(const Value &root)
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
			CString market_code = "";
			CString main_flag = root["json"][i]["main_flag"].asString().c_str();
			if ('0' == main_flag[0])
			{
				ErrorLog("main_flag is 0");
				::MessageBox(SPtr_CData->hwnd_MainPageDlg,"�˿ͻ��˲�֧�ָ��ɶ��˻��������˳�","����",NULL);
				if (PostMessage(SPtr_CData->hwnd_MainPageDlg, WM_AbnormalExit, 0, 0) == 0)
				{
					ErrorLog("PostMessage fail");
				}
				return false;
			}

			CString exchange_type = root["json"][i]["exchange_type"].asString().c_str();
			switch (exchange_type[0]) {
			case '1':
			{
				market_code = SSE;
				CAccount obj_CAccount;
				obj_CAccount.stock_account = root["json"][i]["stock_account"].asString().c_str();//�ɶ��˻�
				obj_CAccount.market_code = market_code;
				if (SPtr_CData->SetAccount(SPtr_CData->s_user.c_str() , obj_CAccount) == false)
				{
					ErrorLog("SetAccount fail");
				}
				break;
			}
			case '2':
			{
				market_code = SZSE;
				CAccount obj_CAccount;
				obj_CAccount.stock_account = root["json"][i]["stock_account"].asString().c_str();//�ɶ��˻�
				obj_CAccount.market_code = market_code;
				if (SPtr_CData->SetAccount(SPtr_CData->s_user.c_str(), obj_CAccount) == false)
				{
					ErrorLog("SetAccount fail");
				}
				break;
			}
			default:
				break;
			}
		}
		else
		{
			LOG(ERROR) << "function id:" << root["function_id"].asString() << " a element illegal";
			/*����continueԭ����ֻҪ��һ�������͸���Ϊ��ѯ�ɶ��˻��ɹ��������Ͷ�Ӧ�źţ���������źŻ��������⣬����ֲ֣���һ�����˾��϶���ѯʧ�ܲ�ˢ��*/
			return false;
		}
	}
	
	return true;
}

bool CT2Spi_Fast::OnRevoke(const Value &root)
{
	if (root["json"].isNull())
	{
		ErrorLog("OnRevoke no json");
		return false;
	}

	int count = root["json"].size();
	for (int i = 0; i < count; i++)
	{
		if (tool::VerifyElement(root, i, SPtr_CData))
		{
			COrder obj_COrder;
			CString stock_account;
			stock_account = root["json"][i]["stock_account"].asString().c_str();
			/*ί�����͡��ɽ������ȵ���Ӧ���ȵ�*/
			if (GainObjOrder(root, i, obj_COrder) == false)
			{
				ErrorLog("GainObjOrder fail");
				return false;
			}
			//obj_COrder.ArrivalSequence_WithdrawOrder[index_Reply] = '1';
			/*���ԭί��Ϊδ����ֱ���ڳ���Ӧ�������Ϊ�ѳ�*/
			string stock_code = root["json"][i]["stock_code"].asString();
			switch ((root["json"][i]["entrust_status_old"].asString())[0])
			{
			case '0'://δ��(����������)
			{
				obj_COrder.entrust_status = YiChe;
				break;
			}
			default:
				break;
			}
			
			if (SPtr_CData->SetOrder(SPtr_CData->fund_account, stock_account, obj_COrder) == false)
			{
				LOG(ERROR) << "SetOrder fail";
				ExceptionInterrupt;
				return false;
			}
			UpdateFund_Position(stock_code);
			bPostMessage = true;
		}
		else
		{
			LOG(ERROR) << "function id:" << root["function_id"].asString() << " a element illegal";
			return false;//ֻ��һ��Ԫ�أ�����Ҫ��������ж��Ƿ��¼�ɹ������һ��Ҫ��return
		}
	}
	return true;
}

/*position*/
bool CT2Spi_Fast::QuerySinglePosition(const string &stock_code)
{
	string s_Fun333104;
	GainQuerySinglePosition(s_Fun333104, stock_code);
	if (tool::SendOrder(pCApiFun, Api_Asy,s_Fun333104, SPtr_CData)< 0)
	{
		return false;
	}
	return true;
}

bool CT2Spi_Fast::GainQuerySinglePosition(string &s_str, const string &stock_code)
{
	/*�ֲֲ�ѯ*/
	Json::Value obj_Value;
	obj_Value["function_id"] = "333104";
	obj_Value["password"] = SPtr_CData->s_pass;
	obj_Value["fund_account"] = SPtr_CData->s_user;
	obj_Value["password_type"] = password_type_��������;
	obj_Value["op_branch_no"] = SPtr_CData->branch_no;

	obj_Value["branch_no"] = SPtr_CData->branch_no;
	obj_Value["sysnode_id"] = SPtr_CData->sysnode_id;
	obj_Value["stock_code"] = stock_code;
	obj_Value["position_str"] = "";
	obj_Value["request_num"] = "1";

	obj_Value["op_entrust_way"] = op_entrust_way_����ί��;
	
	s_str = obj_Value.toStyledString();
	return true;
}

bool CT2Spi_Fast::OnQuerySinglePosition(const Value &root)
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
				LOG(ERROR) << "SetPosition fail";
				ExceptionInterrupt;
				return false;
			}
		}
		else
		{
			LOG(ERROR) << "function id:" << root["function_id"].asString() << " a element illegal";
			return false;
		}
	}
	if (true == bBeginRedrawPosition)
	{
		if (SPtr_CData->hwnd_TradeDlg == NULL)
		{
			SPtr_CData->Queue_WmMessage.push(WM_ReDrawPosition);
		}
		else if (PostMessage(SPtr_CData->hwnd_TradeDlg, WM_ReDrawPosition, 0, 0) == 0)
		{
			LOG(ERROR) << "PostMessage fail";
			ExceptionInterrupt;
			return false;
		}
	}
	return true;
}

/*fund*/
bool CT2Spi_Fast::OnQueryFund(const Value &root)
{
	if (root["json"].isNull())
	{
		/*δ�ҵ� ��ѯ�ʽ�Ϊ�ճ����쳣*/
		ErrorLog("OnQueryFund no json");
		return false;
	}

	int count = root["json"].size();
	for (int i = 0; i < count; i++)
	{
		if (tool::VerifyElement(root, i, SPtr_CData) == true)
		{
			CFund obj_CFund;
			obj_CFund.fund_account = SPtr_CData->fund_account;
			//�������� �ʲ�ֵ ֤ȯ��ֵ ��ǰ��� �����ʽ� ��ȡ���  �ر������� �ر��������
			CString money_type; 
			switch (root["json"][i]["money_type"].asString()[0])
			{
			case '0':
			{
				money_type = "�����";
				break;
			}
			case '1':
			{
				money_type = "��Ԫ";
				break;
			}
			case '2':
			{
				money_type = "�۱�";
				break;
			}
			default:
				break;
			}
			obj_CFund.money_type = money_type;

			obj_CFund.asset_balance = convert<double>(root["json"][i]["asset_balance"].asString().c_str());//�ʲ�ֵ
			obj_CFund.market_value = convert<double>(root["json"][i]["market_value"].asString().c_str());//֤ȯ��ֵ
			obj_CFund.current_balance = convert<double>(root["json"][i]["current_balance"].asString().c_str());//��ǰ���
			obj_CFund.enable_balance = convert<double>(root["json"][i]["enable_balance"].asString().c_str());//�����ʽ�
			
			obj_CFund.fetch_balance = convert<double>(root["json"][i]["fetch_balance"].asString().c_str());//��ȡ���
			obj_CFund.real_buy_balance = convert<double>(root["json"][i]["real_buy_balance"].asString().c_str());//�ر�������
			obj_CFund.real_sell_balance = convert<double>(root["json"][i]["real_sell_balance"].asString().c_str());//�ر��������																		 
																										
			if (SPtr_CData->SetFund(obj_CFund) == false)
			{
				ErrorLog("SetFund fail");
			}
		}
		else
		{
			LOG(ERROR) << "function id:" << root["function_id"].asString() << " a element illegal";
			return false;
		}
	}
	return true;
}

bool CT2Spi_Fast::QueryFund()
{
	string s_Fun332255;
	tool::GainQueryFund332255(s_Fun332255,SPtr_CData);
	int RefId_HS = tool::SendOrder(pCApiFun,Api_Asy,s_Fun332255, SPtr_CData);
	if (RefId_HS < 0)
	{
		ErrorLog("abnormal RefId_HS");
		return false;
	}
	SPtr_CData->SetRefId_T2(RefId_HS, RefType_332255_NoFirstQueryFund);
	return true;
}

void CT2Spi_Fast::updateEntrust_status(COrder &obj_COrder,const string &entrust_status, const string &cancel_info)
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
		LOG(ERROR) << "entrust_no:" << obj_COrder.entrust_no << " �ϵ�ԭ��:"<< cancel_info;
		break;
	}
	default:
		ExceptionInterrupt;
		LOG(ERROR) << "abnormal entrust_status";
		break;
	}
}

void CT2Spi_Fast::updateEntrust_bs(COrder &obj_COrder, const string &entrust_bs)
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
		ExceptionInterrupt;
		LOG(ERROR) << "abnormal entrust_bs";
		break;
	}
}


void CT2Spi_Fast::updateEntrust_bs(CDeal &obj_CDeal, const string &entrust_bs)
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

bool CT2Spi_Fast::OnSendOrder(const Value &root)
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

			Type_OrderList::iterator iter_RawOrder = SPtr_CData->M_OrderList.find(convert<int>(root["ref_id"].asString()) );
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
				ErrorLog("SetOrder fail");
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

void CT2Spi_Fast::OnRecvJsonMsg(char* pRespdata)
{
	/*���ĵĺϷ���У���Ϊ�����������ж��Ƿ�ɹ�ת��(msg_idΪ0),����ж��Ƿ������ݣ�û������û��json�ֶ�*/
	/*�����ж������Ƿ���ȷ��ͨ��error_no������ �Ҳ����Ϸ����ҵõ�Ϊ0�Ϸ�* /
	/*�����ж�T2�Ƿ�ɹ�ת����*/
	pRsp = pRespdata;
	DealQuit(SPtr_CData->bBeginRelease);
	Json::Reader reader;
	Json::Value root;

	/*SYSTEMTIME s_time;
	GetSystemTime(&s_time);*/
	//cerr << "begin parse:" << s_time.wMinute << ":" << s_time.wSecond << ":" << s_time.wMilliseconds << endl;
	if (!reader.parse(string(pRespdata), root, false))
	{
		LOG(ERROR) << "parse error";
		return;
	}
	
	//GetSystemTime(&s_time);
	//cerr << "end parse:" << s_time.wMinute << ":" << s_time.wSecond << ":" << s_time.wMilliseconds << endl;
	
	int function_id = convert<int>(root["function_id"].asString());
	switch (function_id)
	{
	case 331100://T2��½
	{
		if (OnLogin(root) == true)
		{
			SetEvent(SPtr_CData->LoginT2_Event);
		}
		else
		{
			LOG(ERROR) << "OnLogin fail";
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
			ErrorLog("OnQueryStockAccount fail");
		}
		break;
	}
	case 332255://�ʽ��˻���ѯ
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
			case RefType_332255_InitFund:
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
				LOG(ERROR) << "PostMessage fail";
				ExceptionInterrupt;
			}
		}
		else
		{
			LOG(ERROR) << "OnQueryFund fail";
			ExceptionInterrupt;
		}

		break;
	}
	case 333002://ί���µ�����
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
	case 333017://��������
	{
		OnRevoke(root);
		break;
	}
	case 333104://�����ֲֲ�ѯ
	{
		OnQuerySinglePosition(root);
		break;
	}
	case 620001://����Ӧ��
	{
		On620001(root);
		break;
	}
	case 620003://����(ί�С��ɽ�)����
	{
		OnSubscribe(root);
		break;
	}
	default:
		break;
	}
	return;
}

