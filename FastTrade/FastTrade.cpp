// FastTrade.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "FastTrade.h"
#include "../tool/MyCtrl/MyCOccManager.h"



//
//TODO:  ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ��  ����ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CFastTradeApp

BEGIN_MESSAGE_MAP(CFastTradeApp, CWinApp)
END_MESSAGE_MAP()


// CFastTradeApp ����

CFastTradeApp::CFastTradeApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CFastTradeApp ����

CFastTradeApp theApp;
MyCOccManager obj_MyCOccManager;


// CFastTradeApp ��ʼ��

BOOL CFastTradeApp::InitInstance()
{
	CWinApp::InitInstance();
	AfxEnableControlContainer(&obj_MyCOccManager);
	return TRUE;
}


