#pragma once
#include "stdafx.h"
#include <afx.h>
#include <iostream>
#include <time.h>
#include <Windows.h>

#include "MarketSpi_Credit_SZSE.h"
using namespace std;


CMarketSpi_Credit_SZSE obj_CMarketSpi_Credit_SZSE;

void CMarketSpi_Credit_SZSE::OnUserLogin(socket_struct_Msg* pMsg)
{
	DealOnUserLogin(pMsg, SPtr_CData->LoginSZSEMarket_Event);
}

/*���������˳�ʱҲ�����OnClose��ˣ�ֻ���ڳ���������˳�ʱ�Ż�����˳�*/
void CMarketSpi_Credit_SZSE::OnClose()
{
	DealOnClose(SPtr_CData->bBeginRelease, SPtr_CData->bRun_MainPageDlg, SPtr_CData->hwnd_MainPageDlg, "����������վ�����ж�,�����µ�½");
}

void CMarketSpi_Credit_SZSE::OnIssueEnd(UInt_64 qQuoteID)
{
	DealOnIssueEnd(qQuoteID, SPtr_CData->QuerySZSEStockMap_Event);
}

void CMarketSpi_Credit_SZSE::OnRespSecurity_Sz(UInt_64 qQuoteID, socket_struct_Security_Sz* pSecurity)
{
	DealOnRespSecurity_Sz(qQuoteID, pSecurity);
}

void CMarketSpi_Credit_SZSE::OnRespDepth(UInt_64 qQuoteID, char* MarketCode, char* SecCode, socket_struct_DepthDetail* pDepth)
{
	DealOnRespDepth(qQuoteID, MarketCode,SecCode,pDepth);
}

void CMarketSpi_Credit_SZSE::OnMsg(UInt_64 qRefID, socket_struct_Msg* pMsg)
{
	dealOnMsg(qRefID, pMsg, "SZSE");
}

bool CMarketSpi_Credit_SZSE::dll_InitCData(PtrData SPtr_CDataTmp)
{
	SPtr_CData = SPtr_CDataTmp;
	return true;
}