#pragma once
#include <afx.h>
#include <iostream>
#include <time.h>
#include <Windows.h>

#include "AlertSpi_Fast_SZSE.h"

using namespace std;

CAlertSpi_Fast_SZSE obj_CAlertSpi_Fast_SZSE;

VOID CALLBACK OneMilliSecondProc(PVOID lpParameter, BOOLEAN ret)
{
	if (obj_CAlertSpi_Fast_SZSE.bPostMessage)
	{
		tool::MyPostMessage(obj_CAlertSpi_Fast_SZSE.SPtr_CData->hwnd_TradeDlg, WM_RedrawAlert, obj_CAlertSpi_Fast_SZSE.bPostMessage);
	}
	obj_CAlertSpi_Fast_SZSE.bPostMessage = false;
}

CAlertSpi_Fast_SZSE::CAlertSpi_Fast_SZSE()
{
	if (!CreateTimerQueueTimer(&hTimer, NULL, WAITORTIMERCALLBACK(OneMilliSecondProc), NULL, DueTime, Timer_ms, NULL))
	{
		LOG(ERROR) << "CreateTimerQueueTimer fail";
	}
}

CAlertSpi_Fast_SZSE::~CAlertSpi_Fast_SZSE()
{
	if (!DeleteTimerQueueTimer(NULL, hTimer, NULL))
	{
		LOG(ERROR) << "DeleteTimerQueueTimer fail";
	}
}

void CAlertSpi_Fast_SZSE::OnClose()
{
	DealOnClose(SPtr_CData->bBeginRelease, SPtr_CData->bRun_MainPageDlg, SPtr_CData->hwnd_MainPageDlg, "����Ԥ����վ�����ж�,�����µ�½");
}
extern "C" bool dll_InitCData(PtrData SPtr_CDataTmp)
{
	return obj_CAlertSpi_Fast_SZSE.dll_InitCData(SPtr_CDataTmp);
}

extern "C" void OnData(char* strJson)
{
	return obj_CAlertSpi_Fast_SZSE.OnData(strJson, false);
}

extern "C" void OnClose()
{
	return obj_CAlertSpi_Fast_SZSE.OnClose();
}
