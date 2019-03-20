#pragma once
#include "stdafx.h"
#include <afx.h>
#include <iostream>
#include <time.h>
#include <Windows.h>

#include "MarketSpi_index_SZSE.h"

using namespace std;


CMarketSpi_index_SZSE obj_CMarketSpi_index_SZSE;

void CMarketSpi_index_SZSE::OnUserLogin(socket_struct_Msg* pMsg)
{
	DealOnUserLogin(pMsg, SPtr_CData->LoginSZSEMarket_Event);
}

/*���������˳�ʱҲ�����OnClose��ˣ�ֻ���ڳ���������˳�ʱ�Ż�����˳�*/
void CMarketSpi_index_SZSE::OnClose()
{
	DealOnClose(SPtr_CData->bBeginRelease, SPtr_CData->bRun_MainPageDlg, SPtr_CData->hwnd_MainPageDlg, "����������վ�����ж�,�����µ�½");
}

void CMarketSpi_index_SZSE::OnIssueEnd(UInt_64 qQuoteID)
{
	DealOnIssueEnd(qQuoteID, SPtr_CData->QuerySZSEStockMap_Event);
}

void CMarketSpi_index_SZSE::OnRespSecurity_Sz(UInt_64 qQuoteID, socket_struct_Security_Sz* pSecurity)
{
	DealOnRespSecurity_Sz(qQuoteID, pSecurity);
}