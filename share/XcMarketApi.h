#pragma once
#include "Action_Struct.h"

#if defined(_WIN32)
#ifdef LIB_XC_API_EXPORT
#define XC_API_EXPORT __declspec(dllexport)
#else
#define XC_API_EXPORT __declspec(dllimport)
#endif
#else
#define XC_API_EXPORT 
#endif

class CXcMarketSpi
{
public:

	///����
	virtual void OnHeart() {};

	///��¼������Ӧ
	virtual void OnUserLogin(socket_struct_Msg* pMsg) {};

	///�г�������Ӧ
	virtual void OnRespMarket(QWORD qQuoteID, socket_struct_Market* pMarket) {};
	
	/// �Ϻ�A��֤ȯ������Ӧ
	virtual void OnRespSecurity(QWORD qQuoteID, socket_struct_Security* pSecurity) {};
	
	/// �Ϻ���Ȩ֤ȯ������Ӧ
	virtual void OnRespSecurity_Opt(QWORD qQuoteID, socket_struct_Security_Opt* pSecurity) {};
	
	/// ����A��֤ȯ������Ӧ
	virtual void OnRespSecurity_Sz(QWORD qQuoteID, socket_struct_Security_Sz* pSecurity) {};
	
	/// ��̬����������Ӧ
	virtual void OnRespDyna(QWORD qQuoteID, socket_struct_Dyna* pDyna) {};
	
	/// ��̬���������Ӧ
	virtual void OnRespDepth(QWORD qQuoteID, char* MarketCode, char* SecCode, socket_struct_DepthDetail* pDepth) {};
	
	/// ��̬ί�ж���������Ӧ
	virtual void OnRespDepthOrder(QWORD qQuoteID, char* MarketCode, char* SecCode, int Grade, DWORD Price, socket_struct_DepthOrderDetail* pDepthOrder) {};
	
	/// ��̬���ί��������Ӧ
	virtual void OnRespEachOrder(QWORD qQuoteID, char* MarketCode, char* SecCode, socket_struct_EachOrderDetail* pEachOrder) {};
	
	/// ��̬��ʳɽ�������Ӧ
	virtual void OnRespEachDeal(QWORD qQuoteID, char* MarketCode, char* SecCode, socket_struct_EachDealDetail* pEachDeal) {};
	
	/// �������������ʾ
	virtual void OnIssueEnd(QWORD qQuoteID) {};
	
	/// ��Ϣ��ʾ
	virtual void OnMsg(QWORD qRefID, socket_struct_Msg* pMsg) {};
	
	/// ������ʾ
	virtual void OnClose() {};
};

class XC_API_EXPORT CXcMarketApi
{
public:
	///����MdApi
	///@param pszFlowPath ����������Ϣ�ļ���Ŀ¼��Ĭ��Ϊ��ǰĿ¼
	///@return ��������UserApi
	///modify for udp marketdata
	static CXcMarketApi *CreateMarketApi();


	///ע��ص��ӿ�
	///@param pSpi �����Իص��ӿ����ʵ��
	virtual int Register(CXcMarketSpi *pSpi) = 0;


	///ɾ���ӿڶ�����
	///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
	virtual void Release() = 0;

	///��ʼ��
	///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
	virtual int Connect(const char* UserId, const char* IP, const char* Port, const char* LicensePath = "") = 0;

	///������������
	///@remark �Ƿ������������������������
	virtual int SetConnectParam(bool bReconnect, int dReconnect_Time, int dReconnect_Count) = 0;

	/// ����
	virtual int Subscribe(QWORD RefID, interface_struct_Subscribe* pSubscribe, socket_struct_SubscribeDetail SubList[MaxSize], int SubSize) = 0;
	
	/// ȡ������
	virtual int Cancel(QWORD RefID, interface_struct_Subscribe* pCancel, socket_struct_SubscribeDetail CanList[MaxSize], int CanSize) = 0;

	/// ��ѯ
	virtual int Require(QWORD RefID, socket_struct_RequireDetail ReqList[MaxSize], int ReqSize) = 0;

protected:
	~CXcMarketApi() {};
};

