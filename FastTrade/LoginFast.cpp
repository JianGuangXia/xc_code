#include "stdafx.h"
#include "Login_Fast.h"
#include "Resource.h"

static void thread_ErrorInfo(PtrData SPtr_CData)
{
	/*��¼���治�����Ҵ�dllû���ڵ�¼��ʱ��ر�*/
	while (true)
	{
		if (true == SPtr_CData->bQuit_ErrorInfo )
		{
			break;
		}
		if (SPtr_CData->Queue_T2ErrorInfo.size() > 0)
		{
			CString s_ErrorInfo =SPtr_CData->Queue_T2ErrorInfo.front().c_str();
			SPtr_CData->Queue_T2ErrorInfo.pop();
			::MessageBox(NULL,s_ErrorInfo,_T("���ٽ���_����"),MB_OK);
			continue;
		}

		if (SPtr_CData->Queue_MarketErrorInfo.size() > 0)
		{
			CString s_ErrorInfo = SPtr_CData->Queue_MarketErrorInfo.front().c_str();
			SPtr_CData->Queue_MarketErrorInfo.pop();
			::MessageBox(NULL,s_ErrorInfo, _T("���ٽ���_����"), MB_OK);
			continue;
		}

		Sleep(20);
	}
	SPtr_CData->bQuit_ErrorInfo = false;
	SPtr_CData->bRuning_ErrorInfo = false;
}

CLogin_Fast::CLogin_Fast(PtrData SPtr_CDataTmp, HWND Hwnd_LoginDlgTmp, CApiFun *pCApiFunTmp)
	:CLogin_Base(Hwnd_LoginDlgTmp, SPtr_CDataTmp, pCApiFunTmp)
{
	Hwnd_LoginDlg = Hwnd_LoginDlgTmp;
}

void CLogin_Fast::release()
{
	SPtr_CData->bBeginRelease = true;
    SPtr_CData->bQuit_ErrorInfo = true;
	pCApiFun->release();
	tool::MyFreeLibrary(ApiDll_Alert_SSE);
	tool::MyFreeLibrary(ApiDll_Alert_SZSE);
}

bool CLogin_Fast::Login_Fast(CProgressCtrl &obj_CProgressCtrl)
{
	InitUser_Pass(SPtr_CData);
	FillAlertUser(DllId_Fast, SPtr_CData);
	initCProgressCtrl(obj_CProgressCtrl);

	/*��ʼ��������Ϣ�߳� Ҫ���ǵ�����̱߳������ˣ����ǽ�������������������ʱ��Ҫ�رմ��̵߳����*/
	std::thread t_ErrorInfo(thread_ErrorInfo, SPtr_CData);
	t_ErrorInfo.detach();
	Sleep(100);
	SPtr_CData->bRuning_ErrorInfo = true;

	if (false == loginFast_T2_Asy())
	{
		return false;
	}
	if (loginT2_Syn(&(pCApiFun->Api_T2_Syn), Api_Syn) == false)
	{
		return false;
	}
	if (false == loginFast_Market_SSE())
	{
		return false;
	}
	if (false == loginFast_Market_SZSE())
	{
		return false;
	}
	if (false == loginFast_Alert_SSE())
	{
		return false;
	}
	if (false == loginFast_Alert_SZSE())
	{
		return false;
	}
	obj_CProgressCtrl.SetPos(30);
	obj_CProgressCtrl.SetStep(30);
	
	/*�״ε�½��ѯ�ʽ��˻�*/
	if (initFund_Fast() == false)
	{
		LOG(ERROR) << "initFundModule false";
		AfxMessageBox(_T("initFundModule false�������µ�¼"));
		return false;
	}

	if (initStockAccount(SPtr_CData,pCApiFun) == false)
	{
		return false;
	}

	if (false == initStockMap(SPtr_CData, pCApiFun))
	{
		return false;
	}
	/*�����ʽ��˻��µĳɽ���ί��*/
	if (tool::initSubscribe(SPtr_CData, pCApiFun, Api_Asy) != true)
	{
		return false;
	}

	obj_CProgressCtrl.SetPos(60);
	obj_CProgressCtrl.SetStep(60);

	/*��ѯ�ֲ�*/
	if (initPosition_Fast() == false)
	{
		LOG(ERROR) << "initPosition false";
		AfxMessageBox(_T("initPosition false�������µ�¼"));
		return false;
	}

	/*��ѯȫ��ί��*/
	if (initOrderDemo_Fast() == false)
	{
		LOG(ERROR) << "initOrderDemo fail";
		AfxMessageBox(_T("initOrderDemo false�������µ�¼"));
		return false;
	}

	/*��ѯȫ���ɽ�*/
	if (initDealDemo_Fast() == false)
	{
		LOG(ERROR) << "init DealDemo fail�������µ�¼";
		AfxMessageBox(_T("init DealDemo fail�������µ�¼"));
		ExceptionInterrupt;
		return false;
	}

	obj_CProgressCtrl.SetPos(100);
	obj_CProgressCtrl.SetStep(100);
	return true;
}

/*��¼T2*/
bool CLogin_Fast::loginFast_T2_Asy()
{
	int ret = 0;
	/*��Api�Ľӿڴ��ݵ�client*/
	if (false == GainT2Api(&pCApiFun->Api_T2_Asy))
	{
		return false;
	}
	/*��spi�Ľӿڴ��ݵ�Api*/
	CT2Spi *pCT2Spi = new CT2Spi_Fast;
	pCT2Spi->SPtr_CData = SPtr_CData;
	pCT2Spi->pCApiFun = pCApiFun;
	ret = pCApiFun->Api_T2_Asy->Register(Trans_Mode_ASY, Data_Proto_Json, pCT2Spi);
	if (ret < 0)
	{
		ErrorLog(pCApiFun->Api_T2_Asy->GetLastErrorMsg());
		return false;
	}

	string s_Fun33110;
	GainLogin331100(s_Fun33110, SPtr_CData,AssetProp_��ͨ�˻�);
	if (loginT2(pCApiFun, s_Fun33110, SPtr_CData) == false)
	{
		return false;
	}
	/*��ȡ�µ����*/
	GainInfo_RiskControl(SPtr_CData);
	return true;

}



//bool  CLogin_Fast::LoginFast_T2_Syn()
//{
//	if (GainT2Api(&pCApiFun->Api_T2_Syn) == false)
//	{
//		return false;
//	}
//	int ret = pCApiFun->Api_T2_Syn->Register(Trans_Mode_SYN, Data_Proto_Json);
//	if (ret < 0)
//	{
//		ErrorLog(pCApiFun->Api_T2_Syn->GetLastErrorMsg());
//		return false;
//	}
//	if (loginT2_Syn(Api_Syn,SPtr_CData->fund_account.GetBuffer()) == false)
//	{
//		return false;
//	}
//	return true;
//
//}

/*��¼����*/
bool CLogin_Fast::loginFast_Market_SSE()
{
	/*��api�Ľӿڴ��ݸ�client*/
	if (false == GainMarketApi(&pCApiFun->Api_Market_SSE))
	{
		return false;
	}
	/*Register spi*/
    CMarketSpi *pSpi_Market_SSE_Fast = new CMarketSpi_Fast_SSE;
	pSpi_Market_SSE_Fast->pCApiFun = pCApiFun;
	pSpi_Market_SSE_Fast->SPtr_CData = SPtr_CData;
	int ret;
	ret = pCApiFun->Api_Market_SSE->Register(pSpi_Market_SSE_Fast);
	if (ret < 0)
	{
		LOG(ERROR) << "RegisterSpi_Market_SSE error";
		ExceptionInterrupt;
		return false;
	}

	if (loginMarket(SPtr_CData->s_user,IDC_Market_SSE, SPtr_CData->LoginSSEMarket_Event) == false)
	{
		return false;
	}
	return true;

}

bool CLogin_Fast::loginFast_Market_SZSE()
{
	/*��api�Ľӿڴ��ݸ�client*/
	if (false == GainMarketApi(&pCApiFun->Api_Market_SZSE))
	{
		return false;
	}
	/*Register spi*/
	CMarketSpi *pSpi_Market_SZSE_Fast = new CMarketSpi_Fast_SZSE;
	pSpi_Market_SZSE_Fast->pCApiFun = pCApiFun;
	pSpi_Market_SZSE_Fast->SPtr_CData = SPtr_CData;
	int ret = pCApiFun->Api_Market_SZSE->Register(pSpi_Market_SZSE_Fast);
	if (ret < 0)
	{
		LOG(ERROR) << "RegisterSpi_Market_SZSE error";
		ExceptionInterrupt;
		return false;
	}

	if (loginMarket(SPtr_CData->s_user, IDC_Market_SZSE, SPtr_CData->LoginSZSEMarket_Event)
		== false)
	{
		return false;
	}
	return true;
}


/*��¼Ԥ����*/
bool CLogin_Fast::loginFast_Alert_SSE()
{
	/*init WarningPoolApi_Client.dll*/
	if (false == initAlertApi_SSE(ApiDll_Alert_SSE,"AlertApi_Fast_SSE.dll"))
	{
		return false;
	}
	/*Register spi*/
	int ret = 0;
	ret = pCApiFun->RegisterSpi_Alert_SSE("AlertSpi_Fast_SSE.dll");
	if (ret < 0)
	{
		switch (ret)
		{
		case -1:
			ErrorLog("Spi�ļ�����ʧ��");
			break;
		case -2:
			ErrorLog("Spi�ļ��������ش���");
			break;
		default:
			ErrorLog("abnormal ret");
			break;
		}
		return false;
	}

	/*init CDataInSpi*/
	if (false == TransferCDataToSpi("AlertSpi_Fast_SSE.dll"))
	{
		return false;
	}

	if (loginAlert(AlertType_SSE, IDC_AlertServer_SSE, pCApiFun->Connect_Alert_SSE, pCApiFun->SendOrder_Alert_SSE,SPtr_CData->Event_ConnectPartition_SSE
	,SPtr_CData->Event_loginSSEAlert,SPtr_CData->Event_ResetAlert_SSE,SPtr_CData)
		== false)
	{
		return false;
	}
	return true;
}

bool CLogin_Fast::loginFast_Alert_SZSE()
{
	if (false == initAlertApi_SZSE(ApiDll_Alert_SZSE,"AlertApi_Fast_SZSE.dll"))
	{
		return false;
	}
	/*Register spi*/
	int ret = 0;
	ret = pCApiFun->RegisterSpi_Alert_SZSE("AlertSpi_Fast_SZSE.dll");
	if (ret < 0)
	{
		switch (ret)
		{
		case -1:
			ErrorLog("Spi�ļ�����ʧ��");
			break;
		case -2:
			ErrorLog("Spi�ļ��������ش���");
			break;
		default:
			ErrorLog("abnormal ret");
			break;
		}
		return false;
	}

	/*init CDataInSpi*/
	if (false == TransferCDataToSpi("AlertSpi_Fast_SZSE.dll"))
	{
		return false;
	}

	if (loginAlert(AlertType_SZSE, IDC_AlertServer_SZSE, pCApiFun->Connect_Alert_SZSE, pCApiFun->SendOrder_Alert_SZSE, SPtr_CData->Event_ConnectPartition_SZSE
		, SPtr_CData->Event_loginSZSEAlert,SPtr_CData->Event_ResetAlert_SZSE, SPtr_CData)
		== false)
	{
		return false;
	}
	return true;
}

bool CLogin_Fast::initFund_Fast()
{
	string s_Fun332255;
	tool::GainQueryFund332255(s_Fun332255,SPtr_CData);
	/*�첽��asynchronous*/
	int RefId_HS = tool::SendOrder(pCApiFun, Api_Asy,s_Fun332255, SPtr_CData);
	if (RefId_HS < 0)
	{
		return false;
	}
	SPtr_CData->SetRefId_T2(RefId_HS, RefType_332255_InitFund);
	if (WAIT_TIMEOUT == WaitForSingleObject(SPtr_CData->InitFund_Event, ShortTime))
	{
		ErrorLog("init fund fail");
		return false;
	}
	return true;
}

bool CLogin_Fast::initDealDemo_Fast()
{
	bool bRun = true;
	string position_str = "";
	bool bContinuousQuery = true;
	while (bRun)
	{
		if (true == bContinuousQuery)
		{
			string s_Fun333102;
			GainQuerySingleBatchDeal333102_Fast(s_Fun333102, position_str);
			if (tool::SendOrder(pCApiFun, Api_Syn,s_Fun333102, SPtr_CData) < 0)
			{
				bRun = false;
				continue;
			}
			else
			{
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
					continue;
				}
				
				OnQueryDeal_Fast(root, position_str, bContinuousQuery);
				delete[] pRespData;
			}
		}
		else
		{
			bRun = false;
		}
	}

	return true;
}

bool CLogin_Fast::GainQuerySingleBatchDeal333102_Fast(string &s_str, const string &position_str)
{
	Json::Value obj_Value;
	obj_Value["function_id"] = "333102";
	obj_Value["fund_account"] = SPtr_CData->s_user;
	obj_Value["password"] = SPtr_CData->s_pass;
	obj_Value["query_type"] = "1";
	obj_Value["op_branch_no"] = SPtr_CData->branch_no;
	obj_Value["branch_no"] = SPtr_CData->branch_no;

	obj_Value["sysnode_id"] = SPtr_CData->sysnode_id;

	obj_Value["request_num"] = convert<string>(SingleQuerySize);
	obj_Value["position_str"] = position_str;
	obj_Value["password_type"] = password_type_��������;
	s_str = obj_Value.toStyledString();
	return true;
}

bool CLogin_Fast::OnQueryDeal_Fast(const Value &root, string &position_str, bool &bContinuousQuery)
{
	if (root["json"].isNull())
	{
		bContinuousQuery = false;
		return true;
	}
	int count = root["json"].size();
	if (count >= SingleQuerySize)
	{
		position_str = root["json"][count - 1]["position_str"].asString();
		bContinuousQuery = true;
	}
	else
	{
		bContinuousQuery = false;
	}
	for (int i = 0; i < count; i++)
	{
        if (Inspect_bStock(root, i) == false)
		{
			continue;
		}
		if (tool::VerifyElement(root, i, SPtr_CData) == true)
		{
			/*�ͻ��������ǹ�Ʊ���ơ���Ʊ���롢�������򡢳ɽ��������ɽ��۸񡢳ɽ�ʱ�䡢�ɽ���š�ί�б�š�Ӷ��ӡ��˰��������*/
			CString stock_account;
			CString MarketCode;
			CDeal obj_CDeal;

			stock_account = root["json"][i]["stock_account"].asString().c_str();
			obj_CDeal.stock_code = root["json"][i]["stock_code"].asString().c_str();//֤ȯ����
			obj_CDeal.stock_name = root["json"][i]["stock_name"].asString().c_str();//֤ȯ����

			/*��������*/
			switch (root["json"][i]["entrust_bs"].asString()[0])
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
				LOG(ERROR) << "abnoraml entrust_bs";
				ExceptionInterrupt;
				break;
			}
			/*�ɽ�����*/
			obj_CDeal.business_amount = convert<UInt_64>(root["json"][i]["business_amount"].asString());
			/*�ɽ��۸�*/
			obj_CDeal.business_price = convert<double>(root["json"][i]["business_price"].asString());
			/*�ɽ�ʱ��*/
			obj_CDeal.business_time = convert<UInt_32>(root["json"][i]["business_time"].asString());
			/*�ɽ����*/
			obj_CDeal.business_id = root["json"][i]["business_id"].asString().c_str();
			/*ί�б��*/
			obj_CDeal.entrust_no = convert<UInt_64>(root["json"][i]["entrust_no"].asString());
			/*�ɽ���Ϊ�˳ɽ�����*/
			obj_CDeal.business_balance = convert<double>(root["json"][i]["business_balance"].asString());
			if (obj_CDeal.entrust_no == 0)
			{
				LOG(ERROR) << "entrust_no is 0";
				//ExceptionInterrupt;
				return false;
			}
			obj_CDeal.business_balance = convert<double>(root["json"][i]["business_balance"].asString());
			if (SPtr_CData->SetDeal(SPtr_CData->fund_account, stock_account, obj_CDeal.entrust_no, obj_CDeal) == false)
			{
				LOG(ERROR) << "SetDeal fail";
				ExceptionInterrupt;
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
	return true;
}
