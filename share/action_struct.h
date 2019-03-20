#pragma once
#include "Action_Define.h"
#include<string.h>
#pragma pack( push, 4 )
#pragma warning(disable:4200)

// ��������
enum _SubscribeType
{
	_SubscribeType_Market = 0, // �г�
	_SubscribeType_Security,   // ֤ȯ
	_SubscribeType_Dyna,       // ����
	_SubscribeType_EachDeal,   // ��ʳɽ�
	_SubscribeType_EachOrder,  // ���ί��
	_SubscribeType_Depth,	   // ���
	_SubscribeType_DepthOrder, // ���ί��
	_SubscribeType_Count
};

// һ����ͷ��������
enum _HeadType1
{
	_HeadType1_Login = 0,    // ��¼
	_HeadType1_Subscribe,    // ����
	_HeadType1_Issue,        // ����
	_HeadType1_Heart,        // ����
	_HeadType1_Msg,          // ��Ϣ
	_HeadType1_Require,      // ��ѯ
	_HeadType1_Cancel,       // ȡ��
	_HeadType1_Monitor,      // ���
	_HeadType1_Alert,        // Ԥ��
	_HeadType1_CancelMonitor,// ȡ�����
#ifdef New_Version
	_HeadType1_ServerInfo,	 // ����������ͻ��˵���Ϣ 
#endif
	_HeadType1_Count
};

// ������ͷ��������
enum _HeadType2
{
	//	����ı����¶���Ĵ���
	_HeadType2_Market,     // �г�
	_HeadType2_Security,   // ֤ȯ
	_HeadType2_Security_Opt, // ��Ȩ
	_HeadType2_Security_Sz, // ֤ȯ�����ڣ�
	_HeadType2_Dyna,       // ����
	_HeadType2_EachDeal,   // ��ʳɽ�
	_HeadType2_EachOrder,  // ���ί��
	_HeadType2_Depth,	   // ���
	_HeadType2_DepthOrder, // ���ί��
	_HeadType2_AlertDyna,  // Ԥ������
	_HeadType2_Count
};

// SocketͨѶһ����ͷ��Ϣ
struct socket_struct_Head1
{
	_HeadType1    Type;         // ��������
	bool          Cmprflag;     // ѹ����־��false:��ѹ�� true:ѹ����
	DWORD         Length;       // ���ݳ��� 
	DWORD         OriginLen;    // Դ���ݳ���
	QWORD         Quote_id;     // �������к�
};

// SocketͨѶ������ͷ��Ϣ������ר�ã�
struct socket_struct_Head2
{
	_HeadType2    Type;         // ��������
	DWORD         Length;       // ���ݳ��� 
};

// SocketͨѶMarket
struct socket_struct_Market
{
	char  	MarketCode[20]; 	// �г�����
	char    MarketName[50];     // �г����� 
	DWORD 	TimeZone;		    // ����ʱ��
	DWORD	OpenTime;			// ����ʱ��
	DWORD   CloseTime;          // ����ʱ��
};

// SocketͨѶSecurity_Stk  ��ͨ
struct socket_struct_Security
{
	char  	    MarketCode[20];     // �г�����
	char        SecCode[20];        // ֤ȯ����
	char	    SecType[10];    	// ֤ȯ����(STK)������ͨ�ӿ�
	char	    SecName[50];		// ���
	DWORD       UpdateTime;         // ����ʱ��HHMMDD
	char	    ISINCode[20];		    // ISIN����
	char        UnderlyingSecCode[20];  // ����֤ȯ����
	char        MarketType[10];         // �г�����
	char        SecClass[10];           // ֤ȯ���
	char        SecSubClass[10];        // ֤ȯ�����
	char	    Currency[10];	        // ���۱���
	double      ParValue;               // ��ֵ
	QWORD       TradableUnlisted;       // ����֤ͨȯδ��������
	char        EndDate[20];            // ���������
	char        StartDate[10];          // ��������
	DWORD       SETID;                  // ��Ʒ��SET���
	QWORD       BuyUnit;                // ��������λ
	QWORD       SellUnit;               // ��������λ
	QWORD       OrdMinFloor;            // �걨����
	QWORD       OrdMaxFloor;            // �걨����
	double      SecurityClosePx;        // ǰ���̼�
	double	    MinMovement;		    // ��С�۸�䶯��
	char        PriceLimitType[3];      // �ǵ�����������
	double      DailyPriceUpLimit;      // �Ƿ����޼۸�
	double      DailyPriceDownLimit;    // �������޼۸�
	double      ExRightRatio;           // ��Ȩ����
	double      DividendAmount;         // ��Ϣ���
	char        FinancingTargetFlag[3]; // ���ʱ�ı�־
	char        MarginTargetFlag[3];    // ��ȯ��ı�־
	char        SecurityStatusFlag[50]; // ��Ʒ״̬��־
	char        Bz[100];                // ��ע
};

// SocketͨѶSecurity_Opt  ��Ȩ
struct socket_struct_Security_Opt
{
	char  	    MarketCode[20];     // �г�����
	char        SecCode[20];        // ֤ȯ����
	char	    SecType[10];    	// ֤ȯ���ͣ�OPT��������Ȩ�ӿ�
	char	    SecName[50];		// ���
	DWORD       UpdateTime;         // ����ʱ��HHMMDD
	char        ContractID[50];         // ���״���
	char        UnderlyingSecCode[20];  // ���֤ȯ����
	char        UnderlyingSymbol[50];   // ����֤ȯ����
	char        UnderlyingType[10];     // ���֤ȯ����
	char        OptionType[3];          // ��Ȩ����
	char        CallOrPut[3];           // �Ϲ��Ϲ�
	QWORD       ContractMultiplierUnit; // ��Լ��λ
	double      ExercisePrice;          // ��Ȩ��Ȩ��
	char        StartDate[10];          // �׸�������
	char        EndDate[10];            // �������/��Ȩ��
	char        ExerciseDate[10];       // ��Ȩ��Ȩ��
	char        DeliveryDate[10];       // ��Ȩ������
	char        ExpireDate[10];         // ��Ȩ������
	char        UpdateVersion[3];       // ��Լ�汾��
	QWORD       TotalLongPosition;      // ��ǰ��Լδƽ����
	double      SecurityClosePx;        // ��Լǰ���̼�
	double      SettlePricePx;          // ��Լǰ�����
	double      UnderlyingClosePx;      // ���֤ȯǰ���̼�
	char        PriceLimitType[3];      // �ǵ�����������
	double      DailyPriceUpLimit;      // �Ƿ����޼۸�
	double      DailyPriceDownLimit;    // �������޼۸�
	double      MarginUnit;             // ��λ��֤��
	double      MarginRatioParam1;      // ��֤������������һ
	double      MarginRatioParam2;      // ��֤��������������
	QWORD       RoundLot;               // ������
	QWORD       LmtOrdMinFloor;         // �����޼��걨����
	QWORD       LmtOrdMaxFloor;         // �����޼��걨����
	QWORD       MktOrdMinFloor;         // �����м��걨����
	QWORD       MktOrdMaxFloor;         // �����м��걨����
	double      TickSize;               // ��С���۵�λ
	char        SecurityStatusFlag[10]; // ��Ȩ��Լ״̬��Ϣ��ǩ
	char        ReservdWord[10];        // Ԥ���ֶ�
};

// SocketͨѶSecurity_Sz  ����
struct socket_struct_Security_Sz
{
	char  	    MarketCode[20];     // �г�����
	char        SecCode[20];        // ֤ȯ����
	char	    SecType[10];    	// ֤ȯ����(STK)������ͨ�ӿ�
	char	    SecName[50];		// ���
	DWORD       UpdateTime;         // ����ʱ��HHMMDD
	char        EnglishName[50];            // Ӣ�ļ��
	char        ISIN[20];                   // ISIN����
	char        UnderlyingSecurityID[20];   // ����֤ȯ����
	char        ListDate[10];               // ��������
	char        SecurityType[10];           // ֤ȯ���
	char        Currency[10];               // ��������
	double      QtyUnit;                    // ������λ
	char        DayTrading;                 // �Ƿ�֧�ֵ��ջ�ת����
	double      PrevClosePx;                // �������̼�
	char        SecurityStatus[100];        // ֤ȯ״̬
	double      OutstandingShare;           // �ܷ�����
	double      PublicFloatShareQuantity;   // ��ͨ����
	double      ParValue;                   // ��ֵ
	char        GageFlag;                   // �Ƿ����Ϊ������ȯ�ɳ�ֱ�֤��֤ȯ
	double      GageRatio;                  // �ɳ�ֱ�֤��������
	char        CrdBuyUnderlying;           // �Ƿ�Ϊ���ʱ��
	char        CrdSellUnderlying;          // �Ƿ�Ϊ��ȯ���
	DWORD       PriceCheckMode;             // ��ۼ�鷽ʽ 
	char        PledgeFlag;                 // �Ƿ����Ѻ���
	double      ContractMultiplier;         // �Իع���׼ȯ������
	char        RegularShare[20];           // ��Ӧ�ع���׼ȯ 
	char        QualificationFlag;          // Ͷ�����ʵ��Թ����־
	char        IndustryClassification[10]; // ��ҵ����
	double      PreviousYearProfitPerShare; // ����ÿ������
	double      CurrentYearProfitPerShare;  // ����ÿ������
	char        OfferingFlag;               // �Ƿ���ҪԼ�չ���
	double      NAV;                        // T-1�ջ���ֵ
	double      CouponRate;                 // Ʊ��������
	double      IssuePrice;                 // ���ַ��м�
	double      Interest;                   // ÿ��ԪӦ����Ϣ
	char        InterestAccrualDate[10];    // ������Ϣ�ջ򱾴θ�Ϣ��Ϣ��
	char        MaturityDate[10];           // ������
	double      ExercisePrice;              // ��Ȩ��
	double      ExerciseRatio;              // ��Ȩ����
	char        ExerciseBeginDate[10];      // ��Ȩ��ʼ��
	char        ExerciseEndDate[10];        // ��Ȩ��ֹ��
	char        CallOrPut;                  // �Ϲ����Ϲ�
	char        DeliveryType;               // ���ʽ
	double      ClearingPrice;              // ����۸�
	char        ExerciseType;               // ��Ȩ��ʽ
	char        LastTradeDay[10];           // �������
	DWORD       ExpirationDays;             // ��������
	DWORD       ListType;                   // ��������
	char        DeliveryDay[10];            // ��������
	char        DeliveryMonth[10];          // �����·�
	DWORD       AdjustTimes;                // ��������
	double      ContractUnit;               // ��Լ��λ
	double      PrevClearingPrice;          // ���ս����
	double      ContractPosition;           // ��Լ�ֲ���
};

// SocketͨѶDynaQuote
struct socket_struct_Dyna
{
	char  	    MarketCode[20];    	// �г�����
	char 	    SecCode[20];		// ֤ȯ����
	DWORD	    Open;	            // ���̼ۣ�3λС��
	DWORD	    High;               // ��߼�
	DWORD	    Low;                // ��ͼ�
	DWORD       PreClose;           // �������̼�/�����
	DWORD       Close;              // �������̼�/�����
	DWORD 	    New;	            // ���¼�
	QWORD	    Volume;	            // �ɽ���
	QWORD 	    Amount;	            // �ɽ���3λС��
	QWORD	    TickCount;          // ����ɽ�����
	QWORD	    OpenInt;            // �ֲ���
	char        TradingPhaseCode[10];// ��Ʒʵʱ�׶μ���־
	DWORD       RefPrice;           // ��̬�ο���
	DWORD       Time;	            // hh:mm:ss
};

// SocketͨѶEachDealDetail
struct socket_struct_EachDealDetail
{
	DWORD     Price;          // �۸�3λС��
	QWORD     Volume;         // ����
	QWORD     Amount;         // ��3λС��
	QWORD     BuyNo;          // ��ί�к�
	QWORD     SellNo;         // ����ί�к�
	QWORD     DealNo;         // �ɽ����к�
	char      Type;           // �ɽ����� F���ɽ� 4������
	DWORD	  Time;			  // ʱ��
};

// SocketͨѶEachDeal
struct socket_struct_EachDeal
{
	char  	  MarketCode[20];   // �г�����
	char 	  SecCode[20];		// ֤ȯ����
	DWORD	  DetailCount;
	socket_struct_EachDealDetail Detail[0];
};

// SocketͨѶEachOrderDetail
struct socket_struct_EachOrderDetail
{
	DWORD     Price;          // �۸�,3λС��
	QWORD     Volume;         // ����
	QWORD     Amount;         // ��3λС��
	QWORD     OrderNo;        // ί�к�
	char      Side;           // �������� 1����  2����
	DWORD	  Time;			  // ʱ��
};

// SocketͨѶEachOrder
struct socket_struct_EachOrder
{
	char      MarketCode[20]; // �г�����
	char      SecCode[20];    // ֤ȯ����
	DWORD	  DetailCount;
	socket_struct_EachOrderDetail Detail[0];
};

// SocketͨѶDepth
struct socket_struct_DepthDetail
{
	int             Grade;          // ��λ
	DWORD			Price;		    // 3λС��
	QWORD			Quantity;    	// ί�������ڻ�Ϊ�֣���ƱΪ��
	DWORD           NumOrders;      // ��ί�б���
};

struct socket_struct_Depth
{
	char  	  MarketCode[20];       // �г�����
	char 	  SecCode[20];  	    // ֤ȯ����
	DWORD	  DetailCount;
	socket_struct_DepthDetail Detail[0];
};

// SocketͨѶDepthOrder
struct socket_struct_DepthOrderDetail
{
	QWORD       OrderID;        // ���
	QWORD       Quantity;       // ����
	char        Status;         // ״̬
};

struct socket_struct_DepthOrder
{
	char  	    MarketCode[20]; // �г�����
	char  		SecCode[20];	// ֤ȯ����
	DWORD       Price;          // �۸�
	int         Grade;          // ��λ
	DWORD		DetailCount;
	socket_struct_DepthOrderDetail Detail[0];
};

// SocketͨѶ�û���¼
struct socket_struct_Login
{
	char        UserID[10];    // �û�id
	char        Mac[20];       // mac��ַ
	char        HdSeries[20];  // Ӳ�����к�
	char        Cpuid[50];     // CPU id
	char        Version[10];   // �ͻ��˰汾
	char        Passkey[50];   // ��Կ
#ifdef New_Version
	char		Verification_ID[256];// �ͻ��˼����ַ�
	char        Operation_System;    // '0':windows '1':linux
#endif
};

// SocketͨѶSubscribeDetail
typedef struct Subscribe_Info
{
	char        MarketCode[20]; // �г�����
	char        SecCode[20];    // ֤ȯ����
	Subscribe_Info()
	{
		memset(this, 0, sizeof(Subscribe_Info));
	}
}socket_struct_SubscribeDetail;

// SocketͨѶSubscribe
struct  interface_struct_Subscribe
{
	bool        Dyna_flag = false;      // ���ı�־����Dyna
	bool        EachOrder_flag = false; // ���ı�־����EachOrder
	bool        EachDeal_flag = false;  // ���ı�־����EachDeal
	bool        Depth_flag = false;     // ���ı�־����Depth
	bool        DepthOrder_flag = false;// ���ı�־����DepthOrder
};

// SocketͨѶSubscribe
struct  socket_struct_Subscribe
{
	bool        Dyna_flag = false;      // ���ı�־����Dyna
	bool        EachOrder_flag = false; // ���ı�־����EachOrder
	bool        EachDeal_flag = false;  // ���ı�־����EachDeal
	bool        Depth_flag = false;     // ���ı�־����Depth
	bool        DepthOrder_flag = false;// ���ı�־����DepthOrder
	DWORD		DetailCount;
	socket_struct_SubscribeDetail Detail[0];
};

// SocketͨѶRequireDetail
typedef struct Require_Info
{
	char        MarketCode[20]; // �г�����
	char        SecCode[20];    // ֤ȯ����
	Require_Info()
	{
		memset(this, 0, sizeof(Require_Info));
	}
}socket_struct_RequireDetail;

// SocketͨѶRequire
struct  socket_struct_Require
{
	DWORD		DetailCount;
	socket_struct_RequireDetail Detail[0];
};


// SocketͨѶӦ��
//101 ����
//100 ���ӳɹ�
//-100 ���ӶϿ�������ʧ�ܡ�
struct socket_struct_Msg
{
	int         Msgid;          // Msgid
	char        Desc[200];      // Desciribe
};

#ifdef _WIN32
#define FUNCTION_CALL_MODE		_declspec(dllexport)
#define Xc_LoadLibrary(name) LoadLibrary(name)
#define Xc_GetProcAddress GetProcAddress
#define Xc_FreeLibrary FreeLibrary
#define Xc_Module HMODULE
#else
#define FUNCTION_CALL_MODE
#include<dlfcn.h>
#define Xc_LoadLibrary(name) dlopen(name,RTLD_LAZY)
#define Xc_Module void*
#define Xc_FreeLibrary dlclose
#define Xc_GetProcAddress dlsym
#define sprintf_s snprintf
#define _Longlong long long
#endif


#pragma pack( pop )

