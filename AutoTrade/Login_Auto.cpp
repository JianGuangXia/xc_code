#include "stdafx.h"
#include "Login_Auto.h"
#include "Resource.h"

CLogin_Auto::CLogin_Auto(PtrData SPtr_CDataTmp, HWND Hwnd_LoginDlgTmp, CApiFun *pCApiFunTmp)
	:CLogin_Base(Hwnd_LoginDlgTmp, SPtr_CDataTmp, pCApiFunTmp)
{
}

bool CLogin_Auto::loginIndex(CProgressCtrl &obj_CProgressCtrl)
{
	InitUser_Pass(SPtr_CData);
	FillAlertUser(DllId_Auto, SPtr_CData);
	initCProgressCtrl(obj_CProgressCtrl);
	
	if (loginIndex_t2_Syn() == false)
	{
		return false;
	}
	/*����ʱ�ʽ��ѯ��*/
	if (loginT2_Syn(&(pCApiFun->Api_T2_SZSE_Syn), Api_Syn_SZSE) == false)
	{
		return false;
	}
	if (loginIndex_Market_SZSE() == false)
	{
		return false;
	}
	if (initStockMap_Single(SPtr_CData, pCApiFun, SZSE, SPtr_CData->QuerySZSEStockMap_Event) == false)
	{
		return false;
	}
	if (loginIndex_alert_SZSE() == false)
	{
		return false;
	}
	return true;
}

bool CLogin_Auto::loginIndex_t2_Syn()
{
	if (loginT2_Syn(&(pCApiFun->Api_T2_Syn), Api_Syn) == false)
	{
		return false;
	}
	string s_Fun33110;
	GainLogin331100(s_Fun33110, SPtr_CData, AssetProp_��ͨ�˻�);
	if (tool::SendOrder(pCApiFun, Api_Syn, s_Fun33110, SPtr_CData) < 0)
	{
		return false;
	}
	if (OnLogin() == false)
	{
		return false;
	}
	return true;
}

bool CLogin_Auto::OnLogin()
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
		return true;
	}
	if (root["json"].isNull())
	{
		/*δ�ҵ� ��¼�Ҳ�����������쳣*/
		LOG(ERROR) << "OnLogin no json";
		ExceptionInterrupt;
		return false;
	}
	int i = 0;
	if (tool::VerifyElement(root, i, SPtr_CData))
	{
		SPtr_CData->branch_no = root["json"][i]["branch_no"].asString();
		string sysnode_id = root["json"][i]["sysnode_id"].asString();
		string uft_sysnode_id = root["json"][i]["uft_sysnode_id"].asString();
		if (uft_sysnode_id != "0" && uft_sysnode_id == "31") 
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
	delete[] pRespData;
	return true;
}

bool CLogin_Auto::loginIndex_Market_SZSE()
{
	if (false == GainMarketApi(&pCApiFun->Api_Market_SZSE))
	{
		return false;
	}
	/*Register spi*/
	CMarketSpi *pCMarketSpi = new CMarketSpi_index_SZSE;
	pCMarketSpi->pCApiFun = pCApiFun;
	pCMarketSpi->SPtr_CData = SPtr_CData;
	int ret;
	ret = pCApiFun->Api_Market_SZSE->Register(pCMarketSpi);
	if (ret < 0)
	{
		LOG(ERROR) << "Register error";
		ExceptionInterrupt;
		return false;
	}
	if (loginMarket(SPtr_CData->s_user, IDC_Market_SZSE, SPtr_CData->LoginSZSEMarket_Event) == false)
	{
		return false;
	}
	return true;
}

bool CLogin_Auto::loginIndex_alert_SZSE()
{
	if (false == initAlertApi_SZSE(ApiDll_Index_Asy, "AlertApi_index.dll"))
	{
		return false;
	}
	/*Register spi*/
	int ret = 0;
	ret = pCApiFun->RegisterSpi_Alert_SZSE("indexSpi.dll");
	if (ret < 0)
	{
		LOG(ERROR) << "RegisterSpi error ret:" << ret;
		ExceptionInterrupt;
		return false;
	}

	if (false == TransferCDataToSpi("indexSpi.dll"))
	{
		return false;
	}

	if (false == TransferFunToSpi("indexSpi.dll", pCApiFun))
	{
		return false;
	}
	if (loginAlert(AlertType_Auto, IDC_AlertServer_SZSE, pCApiFun->Connect_Alert_SZSE, pCApiFun->SendOrder_Alert_SZSE,
		SPtr_CData->Event_ConnectPartition_SZSE, SPtr_CData->Event_loginSZSEAlert,
		SPtr_CData->Event_ResetAlert_SZSE, SPtr_CData)
		== false)
	{
		return false;
	}
	return true;
}

void CLogin_Auto::release()
{
	SPtr_CData->bBeginRelease = true;
	SPtr_CData->bQuit_ErrorInfo = true;
	pCApiFun->release();
	tool::MyFreeLibrary(ApiDll_Index_Asy);
}

bool CLogin_Auto::TransferFunToSpi(char* SpiPath, CApiFun *pCApiFun)
{
	HINSTANCE hSpiTmp;
	if (MyLoadLibrary(hSpiTmp, SpiPath) == false)
	{
		return false;
	}
	InitFun* pInitFun;
	pInitFun = (InitFun*)GetProcAddress(hSpiTmp, "dll_InitFun");
	if (NULL == pInitFun)
	{
		LOG(ERROR) << "pInitFun fail";
		FreeLibrary(hSpiTmp);
		return false;
	}
	pInitFun(pCApiFun);
	FreeLibrary(hSpiTmp);
	return true;
}