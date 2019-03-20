#pragma once
#include "QdUiLib.h"
#include <map>
#include <vector>
#include <string>
//// K�����ݽṹ	CStock::dataK
typedef struct kdata_t {

	DWORD	m_date;				//����	Format is XXMMDDHHMM for 5min, Format is YYYYMMDD for day
	time_t	m_time;				//ʱ�䡡��m_dateһ�£��������ĳ�գ���Сʱ�����Ϊ0

	float	m_fOpen;			// ���̼ۣ�Ԫ��
	float	m_fHigh;			// ��߼ۣ�Ԫ��
	float	m_fLow;				// ��ͼۣ�Ԫ��
	float	m_fClose;			// ���̼ۣ�Ԫ��
	double	m_fVolume;			// �ɽ������ɣ�
	double	m_fAmount;			// �ɽ���Ԫ��
	float	m_fNew;				// ���¼ۣ�Ԫ��
	char    m_szTradeDay[9];	//������
	DWORD   m_dwSeconds;		//������������
	double	m_fOpenInterest;	// �ֲ���
} KDATA, *PKDATA,KLINEMINUTE, *PMINUTE;

#define	STKLIB_DATA_INVALID	0x7FFFFFFF

#define	STKLIB_DAYS_INONEYEAR	240
#define	STKLIB_DAYS_CACHE		60
#define	STKLIB_DAYS_CALCULATE	30
#define	STKLIB_AUTORESUMEDR_DATEBEGIN	20040519
#define	STKLIB_AUTORESUMEDR_LIMIT		11

#define	STKLIB_CODE_MAIN			"1A0001"
#define	STKLIB_CODE_MAINSZN			"399001"
#define	STKLIB_CODE_SZZS			"1A0001"	// ��ָ֤��
#define	STKLIB_CODE_SZYBL			"1A0009"	// ��֤180ָ��
#define	STKLIB_CODE_SZAG			"1A0002"	// ��֤A��
#define	STKLIB_CODE_SZBG			"1A0003"	// ��֤B��
#define	STKLIB_CODE_SZNCZ			"399001"	// ��֤��ָ
#define	STKLIB_CODE_SZNZZ			"399106"	// ��֤��ָ
#define	STKLIB_CODE_SZNCFAZ			"399002"	// ��֤�ɷ�Aָ
#define	STKLIB_CODE_SZNCFBZ			"399003"	// ��֤�ɷ�Bָ
#define	STKLIB_CODE_SZNFIRST		"000001"	// ��֤��һ֧��Ʊ
#define	STKLIB_CODE_SHAFIRST		"600000"	// ��֤��һ֧��Ʊ
#define	STKLIB_CODE_ZLDD			"000000"	// ������


// some fixed length
#define	STKLIB_MAX_CODE			8
#define	STKLIB_MAX_CODE2		16	// ���ݽϳ���Ʊ����
#define	STKLIB_MAX_NAME			32
#define	STKLIB_MAX_NAMEENU		10
#define	STKLIB_MAX_SHORTNAME	16
#define	STKLIB_MAX_DOMAIN		32
#define	STKLIB_MAX_PROVINCE		32

#define BONDINFO_MAX_CHAR		128

class CKData
{
public:
	// Constructors
	CKData();
	CKData(int ktype, int maindatatype = mdtypeClose);
	CKData(const CKData & src);

	CKData& operator = (const CKData &src);

	static	BOOL IsDayOrMin(int nKType);

	// Flag values
	enum KTypes {
		ktypeNone		=	0x00,
		ktypeMin		=	0x01,
		ktypeMin5,
		ktypeMin15,
		ktypeMin30,
		ktypeMin60,
		ktypeDay,
		ktypeWeek,
		ktypeMonth,
		ktypeYear,
		ktypeMax		=	0x09,
	};

	enum Formats {
		formatNone		=	0x00,
		formatMin		=	0x01,
		formatOriginal	=	0x01,
		formatXDRup		=	0x02,
		formatXDRdown	=	0x03,
		formatMax		=	0x03,
	};

	enum MaindataTypes {
		mdtypeNone		=	0x00,
		mdtypeMin		=	0x01,
		mdtypeClose		=	0x01,
		mdtypeOpen		=	0x02,
		mdtypeAverage	=	0x03,
		mdtypeMax		=	0x03,
		mdtypePIndex	=	0x04,
	};

	// Attributes
	int		GetSize() const;
	int		GetUpperBound() const;
	void	SetSize(int nNewSize, int nGrowBy = -1);

	// Operations
	// Clean up
	void	FreeExtra();
	void	RemoveAll();

	// Accessing elements
	KDATA	GetAt(int nIndex) const;
	void	SetAt(int nIndex, const KDATA& newElement);
	KDATA&	ElementAt(int nIndex);

	// Direct Access to the element data (may return NULL)
	const KDATA* GetData() const;
	KDATA* GetData();
	
	float	MaindataAt(int nIndex) const;	// �õ�CKData��nIndex�յ������ݣ��������������Ͳ�ͬ������ֵ�����ǿ��̼ۡ����̼ۻ���ƽ����
	BOOL	DateAt(int nIndex, int &nYear, int &nMonth, int &nDay, int &nHour, int &nMinute) const;
	BOOL	LatestDate(int &nYear, int &nMonth, int &nDay, int &nHour, int &nMinute) const;
	DWORD	GetDate(int nIndex);
	DWORD	GetDateDay(int nIndex);
	int		GetIndexByDate(DWORD date);
	int		GetAboutIndexByDate(DWORD date);

	// Potentially growing the array
	void	SetAtGrow(int nIndex, const KDATA& newElement);
	int		Add(const KDATA& newElement);

	// overloaded operator helpers
	KDATA	operator[](int nIndex) const;
	KDATA&	operator[](int nIndex);

	// Operations that move elements around
	void	InsertAt(int nIndex, const KDATA& newElement, int nCount = 1);
	void	RemoveAt(int nIndex, int nCount = 1);
	void	InsertAt(int nStartIndex, CKData* pNewArray);
	int		InsertKDataSort(KDATA newElement);

	// Operation of Analysis
	BOOL	IsNewValue(int nIndex, BOOL bTopOrBottom, int nDays);
	BOOL	GetMinMaxInfo(int nStart, int nEnd, float * pfMin, float *pfMax);

// Implementation
public:
	virtual ~CKData();

public:
	// Extra operations
	void	SetKType(int ktype);
	void	AutoSetKType();
	int		GetKType();
	int		GetCurFormat();
	void	ChangeCurFormat(int format, DWORD dateAutoDRBegin, double dAutoDRLimit);
	void	SetMaindataType(int type);
	int		GetMaindataType();
	void	Clear();

	int		CompareLatestDate(CKData &kd);
	static	int MinToMin5(CKData &kdm, CKData &kdm5);
	static	int MinToMin15(CKData &kdm, CKData &kdm15);
	static	int MinToMin30(CKData &kdm, CKData &kdm30);
	static	int MinToMin60(CKData &kdm, CKData &kdm60);
	static	int Min5ToMin15(CKData &kdm5, CKData &kdm15);
	static	int Min5ToMin30(CKData &kdm5, CKData &kdm30);
	static	int Min5ToMin60(CKData &kdm5, CKData &kdm60);
	static	int DayToYear(CKData &kdday, CKData &kdYear);
	static	int DayToMonth(CKData &kdday, CKData &kdmonth);
	static	int DayToWeek(CKData &kdday, CKData &kdweek);

	DWORD	ToDayDate(DWORD date);
	
	int		MergeKData(CKData* pother);
	int		FullFillKData(CKData & kdataMain, BOOL bFillToEnd);

	BOOL	IsAdjacentDays(int nIndex, int nDays);
	BOOL	GetDiff(double * pValue, DWORD dateCur, int nDays);
	BOOL	GetDiffPercent(double * pValue, DWORD dateCur, int nDays);
	BOOL	GetScope(double * pValue, DWORD dateCur, int nDays);
	BOOL	GetVolumeSum(double * pValue, DWORD dateCur, int nDays);
	BOOL	GetRatioVolume(double * pValue, DWORD dateCur, int nDays);
	BOOL	GetRS(double * pValue, DWORD dateCur, int nDays);
	BOOL	GetMA(double * pValue, int nIndex, int nDays);
	__int64& GetMaxDate() {return m_nMaxDate;}
	__int64& GetMinDate() {return m_nMinDate;}
	bool	GetLoadFromFlag() {return m_bLoadFromSvr;}
	void	SetLoadFromFlag(bool bFlag) {m_bLoadFromSvr=bFlag;}
	void	SetCurMaindataType(int type) {m_nCurMaindataType=type;}
	void	Sort();
protected:
	static int ConvertKData(CKData &kdSrc, CKData &kdDest, int multiple);
	void	CopyData(const CKData &src);
	void	LoadDataOriginal();
	void	StoreDataOriginal();

	static	float GetRatio(float fLastClose);

	static int SortKData(const void *p1,const void *p2);
	
protected:
	int		m_nKType;
	int		m_nCurFormat;
	int		m_nCurMaindataType;
	__int64 m_nMaxDate;
	__int64 m_nMinDate;
	bool	m_bLoadFromSvr;

	struct kdata_t * m_pDataOriginal;
	int m_nSizeOriginal;     // # of elements (upperBound - 1)
	int m_nMaxSizeOriginal;  // max allocated
	struct kdata_t * m_pData;
	int m_nSize;     // # of elements (upperBound - 1)
	int m_nMaxSize;  // max allocated
	int m_nGrowBy;   // grow amount
};

/***
	�����ʱ����������
*/
class CMinute
{
public:
// Construction
	CMinute();
	CMinute(const CMinute &src);

// Attributes
	int		GetSize() const;
	int		GetUpperBound() const;
	void	SetSize(int nNewSize, int nGrowBy = -1);

// Operations
	// Clean up
	void	FreeExtra();
	void	RemoveAll();

	// Accessing elements
	KLINEMINUTE	GetAt(int nIndex) const;
	void	SetAt(int nIndex, const KLINEMINUTE& newElement);
	KLINEMINUTE&	ElementAt(int nIndex);

	// Direct Access to the element data (may return NULL)
	const KLINEMINUTE* GetData() const;
	KLINEMINUTE* GetData();

	// Potentially growing the array
	void	SetAtGrow(int nIndex, const KLINEMINUTE& newElement);
	int		Add(const KLINEMINUTE& newElement);

	// overloaded operator helpers
	KLINEMINUTE	operator[](int nIndex) const;
	KLINEMINUTE&	operator[](int nIndex);

	// Operations that move elements around
	void	InsertAt(int nIndex, const KLINEMINUTE& newElement, int nCount = 1);
	void	RemoveAt(int nIndex, int nCount = 1);
	void	InsertAt(int nStartIndex, CMinute* pNewArray);
	int		InsertMinuteSort(KLINEMINUTE& newElement);
	void	Sort();
	void	RemoveDirty();
	CMinute& operator = (const CMinute &src);
	void	Copy(const CMinute &src);
	
	BOOL	StatVolumeInfo(double *pdVolNow, double *pdVolOuter, double *pdVolInner);	// ͳ����������
	//BOOL	StatDealInfo(CSPDWordArray & adwPrice, CSPDWordArray & adwVolume, double* pdMaxVolume); // ͳ�Ƽ�����ϵ������ֵ�еļ۸������0.001
	BOOL	GetDiffPercentMin5(double * pValue);
	BOOL	GetLBDKMinMaxInfo(double dVolAverage, double *pdMin, double *pdMax);	// ȡ�����ȶ��ָ�����ֵ��Сֵ

	BOOL	GetIndexWave(double *pdWave, int nIndex);

	int		ToKData(CKData & kdata);

// Implementation
protected:
	KLINEMINUTE* m_pData;   // the actual array of data
	int m_nSize;     // # of elements (upperBound - 1)
	int m_nMaxSize;  // max allocated
	int m_nGrowBy;   // grow amount

public:
	~CMinute();
};

/***
	������Ʊ�����ݣ�������Ʊ��Ϣ��K�����ݣ��������ϣ���Ȩ��Ϣ���ݵȡ�
*/
class CStock
{
public:
	// Constructors
	CStock();
	CStock(DWORD dwMarket, const char* code);
	virtual	~CStock();

	CKData&		GetKData(int ktype);
	CKData&		GetKDataYear();
	CKData&		GetKDataMonth();
	CKData&		GetKDataWeek();
	CKData&		GetKDataDay();
	CKData&		GetKDataMin60();
	CKData&		GetKDataMin30();
	CKData&		GetKDataMin15();
	CKData&		GetKDataMin5();
	CKData&		GetKDataMin();
	CMinute&	GetMinute();

	// Operations
	void	Clear();
	int		ExtractKData(int nKType, BOOL bForced);
	int		MergeKData(CStock &stock, int nKType);
	int     GetDotCount(){return m_nDotCount;}
	void    SetDotCount(int nDotCount){m_nDotCount = nDotCount;}
	double  GetLastClose(){return m_fLastClose;}
	void    SetLastClose(double fLastClose){m_fLastClose = fLastClose;}
	void    SetStockID(const std::string & strStockID){m_strStockID = strStockID;}
	void    SetExchangeID(const std::string &strExchangeID){m_strExChangeID = strExchangeID;}
	void    SetStockName(const std::string & strStockName){m_strStockName = strStockName;}
	void    SetPosi(const int nPosi){m_nPosi = nPosi;}
	int		GetPosi(){return m_nPosi;}
	void    SetPosiAvg(const double dPosiAvg){m_fPosiAvg = dPosiAvg;}
	double  GetPosiAvg(){return m_fPosiAvg;}
	void    SetOpenAvg(const double dOpenAvg){ m_fOpenAvg = dOpenAvg; }
	double  GetOpeAvg(){ return m_fOpenAvg; }
	std::string &GetStockID(){return m_strStockID;}
	std::string &GetExchangeID(){return m_strExChangeID;}
	std::string &GetStockName(){return m_strStockName;}
protected:
	void	SetKDataTypes();

private:
	CKData		m_kdYear;
	CKData		m_kdMonth;
	CKData		m_kdWeek;
	CKData		m_kdDay;
	CKData		m_kdMin60;
	CKData		m_kdMin30;
	CKData		m_kdMin15;
	CKData		m_kdMin5;
	CKData		m_kdMin;
	CMinute		m_minute;
	int			m_nDotCount;
	double      m_fLastClose;
	std::string m_strStockID;
	std::string	m_strExChangeID;
	std::string m_strStockName;
	double		m_fPosiAvg;//�ֲ־���
	double		m_fOpenAvg;//���־���
	int         m_nPosi;//���ֲ�
};

class CRealTime;
class CStockGraph;
class CSimplePopupMenu;
#define WM_REFRESHPARENTISLINK			 0x6002
#define WM_REFRESHPARENTTECHPARAMSSET    0x6003
#define WM_REFRESHMAXANDRESTORE			 0x6004
class CKLineGraph
{
public:
	CKLineGraph(void);
	~CKLineGraph(void);
	enum KLineType
	{
		ID_REALTIME,//��ʱͼ
		ID_MINUTE,	//������
		ID_MINUTE5, //5������
		ID_MINUTE15,//15������
		ID_MINUTE30,//30������
		ID_HOUR,	//1Сʱ��
		ID_DAY,		//����
		ID_WEEK,	//����
		ID_MONTH,	//����
		ID_YEAR,	//����
	};
public:
	BOOL Create(CWnd* pParent,CStock *pStock);
	void ReDraw(CDC* pDC, CRect rect);
	void ResetData(CStock *pStock);
	void ClearTradeSpanTime();
	void AddTradeSpanTime(const std::string &strStartTime, const std::string &strEndTime);
	void SetIsLink(BOOL bIsLink);
	BOOL GetIsLink(){return m_bIsLink;}
	void AddKData(KDATA & kData);
	std::string &GetStockID();
	void SaveStockID();
	void SetRefresh();
	void ResetDrawTech();
	void GetTechInfo(std::vector<std::string> &vctTechInfo);
	void SetTechInfo(const std::vector<std::string> &vctTechInfo);
	int  GetKLineType();
	void SetKLineType(int nKLineType);
	CStock &GetStock();
	void RefreshMinute();
	void SetIsComb(BOOL bIsComb);
	BOOL GetIsComb();
	std::string GetSelectDate();
	void SetIsCh(BOOL bIsCh);
private:
	static LRESULT CALLBACK ParentProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void   OnPopUpRightMenu(CPoint pt, CWnd *pParent);
	void   OnPopUpTechMenu(CPoint pt, CWnd *pParent);
	void   OnPopUpTechAttributeMenu(CPoint pt, CWnd *pParent);
	void   OnPopUpKLineTypeMenu(CPoint pt, CWnd *pParent);
	void   OnChangeMenuItem(UINT nID);
	void   SavePicture();
	static std::map<HWND, CKLineGraph *> m_kLineGraphmap;
private:
	CRealTime		*m_pRealTime;
	CStockGraph		*m_pStockGraph;	
	CSimplePopupMenu *m_pMainPopMenu;
	CSimplePopupMenu *m_pSub1PopMenu;
	CSimplePopupMenu *m_pSub2PopMenu;
	int             m_nKLineType;
	HWND			m_hParent;
	CWnd            *m_pParent;
	LONG			m_OriParentProc;
	BOOL			m_bIsLink;	//�Ƿ�����
	CRect           m_rectAll;
	BOOL			m_bIsComb;	//�Ƿ����������
	BOOL			m_bIsCh;	//�Ƿ�����
};

