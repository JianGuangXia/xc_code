// CreditTrade.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "CreditTrade.h"
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

// CCreditTradeApp

BEGIN_MESSAGE_MAP(CCreditTradeApp, CWinApp)
END_MESSAGE_MAP()


// CCreditTradeApp ����

CCreditTradeApp::CCreditTradeApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CCreditTradeApp ����

CCreditTradeApp theApp;
MyCOccManager obj_MyCOccManager;

// CCreditTradeApp ��ʼ��

BOOL CCreditTradeApp::InitInstance()
{
	CWinApp::InitInstance();
	AfxEnableControlContainer(&obj_MyCOccManager);
 	return TRUE;
}
