#pragma once
#include "stdafx.h"
#include <afx.h>
#include <iostream>
#include <time.h>
#include <Windows.h>

#include "MarketSpi_Fast_SSE.h"
using namespace std;

CMarketSpi_Fast_SSE obj_CMarketSpi_Fast_SSE;

void CMarketSpi_Fast_SSE::OnUserLogin(socket_struct_Msg* pMsg)
{
	DealOnUserLogin(pMsg, SPtr_CData->LoginSSEMarket_Event);
	return;
}

/*���������˳�ʱҲ�����OnClose��ˣ�ֻ���ڳ���������˳�ʱ�Ż�����˳�*/
void CMarketSpi_Fast_SSE::OnClose()
{
	DealOnClose(SPtr_CData->bBeginRelease,SPtr_CData->bRun_MainPageDlg, SPtr_CData->hwnd_MainPageDlg, "�Ϻ�������վ�����ж�,�����µ�½");
}

void CMarketSpi_Fast_SSE::OnIssueEnd(UInt_64 qQuoteID)
{
	/*��ر�֤��������ű������100 0000*/
	DealOnIssueEnd(qQuoteID, SPtr_CData->QuerySSEStockMap_Event);
}

void CMarketSpi_Fast_SSE::OnRespSecurity(UInt_64 qQuoteID, socket_struct_Security* pSecurity)
{
	DealOnRespSecurity(qQuoteID, pSecurity);
	return;
}

void CMarketSpi_Fast_SSE::OnRespDepth(UInt_64 qQuoteID, char* MarketCode, char* SecCode, socket_struct_DepthDetail* pDepth)
{
	DealOnRespDepth(qQuoteID, MarketCode, SecCode,pDepth);
}

void CMarketSpi_Fast_SSE::OnMsg(UInt_64 qRefID, socket_struct_Msg* pMsg)
{
	dealOnMsg(qRefID, pMsg, "SSE");
}


bool CMarketSpi_Fast_SSE::dll_InitCData(PtrData SPtr_CDataTmp)
{
	SPtr_CData = SPtr_CDataTmp;
	return true;
}