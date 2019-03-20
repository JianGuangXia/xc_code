
#include "stdafx.h"
#include "ColorSet.h"
//#include "GlobeVar.h"
//#include "QdAppTool.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#define DEFAULT_COLOR_BLACK		RGB(0,   0,   0)
#define DEFAULT_COLOR_WHITE		RGB(215, 215, 215)
#define DEFAULT_COLOR_WHITE1	RGB(255, 255, 255)
#define DEFAULT_COLOR_WHITE2	RGB(170, 170, 170)
#define DEFAULT_COLOR_RED		RGB(228, 106, 94)
#define DEFAULT_COLOR_RED2		RGB(200, 85,  75)
#define DEFAULT_COLOR_RED3		RGB(153, 61,  61)
#define DEFAULT_COLOR_GREEN		RGB(113, 200, 85)
#define DEFAULT_COLOR_GREEN1	RGB(44,  130, 44)
#define DEFAULT_COLOR_GREEN2	RGB(20,  137, 44)
#define DEFAULT_COLOR_GREEN3	RGB(87,  153, 61)
#define DEFAULT_COLOR_GREEN4	RGB(76,  111, 64)
#define DEFAULT_COLOR_GREEN5	RGB(113,  200, 85)
#define DEFAULT_COLOR_GRAY		RGB(189, 189, 189)
#define DEFAULT_COLOR_GRAY1		RGB(46,  48,  61)
#define DEFAULT_COLOR_GRAY2		RGB(105, 105, 105)
#define DEFAULT_COLOR_GRAY3		RGB(37,  39,  53)
#define DEFAULT_COLOR_GRAY4		RGB(126, 127, 116)
#define DEFAULT_COLOR_GRAY5		RGB(63, 65, 77)
#define DEFAULT_COLOR_BLUE		RGB(74,  144, 226)
#define DEFAULT_COLOR_BLUE1		RGB(58,  104, 138)
#define DEFAULT_COLOR_BLUE2		RGB(0,   106, 186)
#define DEFAULT_COLOR_BLUE3		RGB(61, 91, 153)
#define DEFAULT_COLOR_BLUE4		RGB(102, 182, 240)
#define DEFAULT_COLOR_BLUE5	    RGB(51,  153, 255)
#define DEFAULT_COLOR_BLUE6	    RGB(50, 79, 118)
#define DEFAULT_COLOR_BLUE7	    RGB(0, 122, 204)
#define DEFAULT_COLOR_BLUE8	    RGB(104, 104, 104)
#define DEFAULT_COLOR_YELLOW    RGB(240, 192, 78)
#define DEFAULT_COLOR_YELLOW2	RGB(255, 159, 25)
#define DEFAULT_COLOR_YELLOW3	RGB(255, 205, 0)
#define DEFAULT_COLOR_BK		RGB(18,  20,  22)
//#define DEFAULT_COLOR_BK		RGB(240,  240,  240)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TCHAR CColorSet::m_szColorFile[_MAX_PATH];

static COLORSET m_arrColorSet[MAX_COLORSET-1] =
{
	{EDIT_BACK_ACTIVE,		GetSysColor(COLOR_BACKGROUND)+RGB(30,30,30), _T("����༭�򱳾�")},
	{EDIT_BACK_INACTIVE,	GetSysColor(COLOR_BACKGROUND), _T("�ǽ���༭�򱳾�")},
	{EDIT_BACK_DISABLE,		GetSysColor(COLOR_BTNFACE), _T("��ұ༭�򱳾�")},
	{EDIT_TEXT_ACTIVE,		RGB(10,100,10), _T("����༭���ı�")},
	{EDIT_TEXT_INACTIVE,	RGB(100,10,10), _T("�ǽ���༭���ı�")},

	{STATIC_ACTIVE,			RGB(50,50,100), _T("���㾲̬�ı�")},
	{STATIC_INACTIVE,		RGB(0,0,0),		_T("�ǽ��㾲̬�ı�")},
	{STATIC_TEXT_WHITE,			     DEFAULT_COLOR_WHITE,		_T("�ı���ɫ")},
	{STATIC_TEXT_WHITE1,			 DEFAULT_COLOR_WHITE1,		_T("�ı���ɫ")},
    {STATIC_TEXT_WHITE2,			 DEFAULT_COLOR_WHITE2,		_T("�ı���ɫ")},
    {STATIC_TEXT_RED,			     DEFAULT_COLOR_RED,		    _T("�ı���ɫ")},
	{STATIC_TEXT_GREEN,			     DEFAULT_COLOR_GREEN,		_T("�ı���ɫ")},
    {STATIC_TEXT_BLUE5,			     DEFAULT_COLOR_BLUE5,		_T("�ı���ɫ")},
	{STATIC_TEXT_GRAY,			     DEFAULT_COLOR_GRAY,		_T("�ı���ɫ")},
	{STATIC_TEXT_GRAY5,			     DEFAULT_COLOR_GRAY5,		_T("�ı���ɫ")},
    {STATIC_LOGIN_WHITE,             DEFAULT_COLOR_GRAY,        _T("�ı���ɫ")},
    {STATIC_MODIFYPWD_RED,           DEFAULT_COLOR_RED,         _T("��ɫ�ı���ɫ")},
    {STATIC_MODIFYPWD_WHITE,         DEFAULT_COLOR_WHITE,       _T("�ı���ɫ")},
    {STATIC_FUNDVIEW_GRAY,           DEFAULT_COLOR_GRAY1,       _T("�ı���ɫ")},
	{STATIC_ORDERCONFIRM_GRAY,       DEFAULT_COLOR_GRAY,        _T("�ı���ɫ")},
	{STATIC_TEXT_BK_GRAY1,			 DEFAULT_COLOR_GRAY1,       _T("�ı�����ɫ")},
	{STATIC_TEXT_BK_GRAY2,			 DEFAULT_COLOR_GRAY2,       _T("�ı�����ɫ")},
	{STATIC_TEXT_BK_GRAY5,			 DEFAULT_COLOR_GRAY5,       _T("�ı�����ɫ")},
	{STATIC_TEXT_BK_RED3,			 DEFAULT_COLOR_RED3,       _T("�ı�����ɫ")},
	{STATIC_TEXT_BK_GREEN3,			 DEFAULT_COLOR_GREEN3,       _T("�ı�����ɫ")},
	{STATIC_TEXT_BK_BLUE3,			 DEFAULT_COLOR_BLUE3,       _T("�ı�����ɫ")},
	{STATIC_TEXT_BK_BLUE4,			 DEFAULT_COLOR_BLUE4,       _T("�ı�����ɫ")},
	{STATIC_GUARDIAN_YELLOW3,        DEFAULT_COLOR_YELLOW3,     _T("�ı���ɫ")},

	{BUTTON_BACK_ACTIVE,		GetSysColor(COLOR_BTNFACE)+RGB(30,30,30), _T("���㰴ť����")},
    {BUTTON_BACK_INACTIVE,		GetSysColor(COLOR_BTNFACE), _T("�ǽ��㰴ť����")},
    {BUTTON_HOVER_RED,		         DEFAULT_COLOR_RED, _T("HOVER RED")},
    {BUTTON_HOVER_GREEN,		     DEFAULT_COLOR_GREEN5, _T("HOVER GREEN")},
    {BUTTON_HOVER_BLUE,		         DEFAULT_COLOR_BLUE4, _T("HOVER BLUE")},
    {BUTTON_HOVER_GRAY,		         DEFAULT_COLOR_GRAY2, _T("HOVER GRAY")},
	{BUTTON_TEXT_WHITE,	             DEFAULT_COLOR_WHITE1, _T("��ť��ɫ������ɫ")},
	{BUTTON_TEXT_RED,	             DEFAULT_COLOR_RED, _T("��ť��ɫ������ɫ")},
	{BUTTON_FACE_BLUE,	             DEFAULT_COLOR_BLUE3, _T("��ɫ��ť��ɫ")},
	{BUTTON_FACE_RED,	             DEFAULT_COLOR_RED3, _T("��ɫ��ť��ɫ")},
    {BUTTON_FACE_GREEN,	             DEFAULT_COLOR_GREEN3, _T("��ɫ��ť��ɫ")},


    {CHECKBOX_BACK_ACTIVE,		GetSysColor(COLOR_BTNFACE)+RGB(30,30,30), _T("���㸴ѡ�򱳾�")},
	{CHECKBOX_BACK_INACTIVE,	GetSysColor(COLOR_BTNFACE), _T("��ѡ�򱳾�")},
	{CHECKBOX_BACK_BLACK,	         DEFAULT_COLOR_BLACK, _T("��ѡ�򱳾�")},

	{RADIOBTN_BACK_ACTIVE,		GetSysColor(COLOR_BTNFACE)+RGB(30,30,30), _T("���㵥ѡ�򱳾�")},
	{RADIOBTN_BACK_INACTIVE,	GetSysColor(COLOR_BTNFACE), _T("��ѡ�򱳾�")},
	
	{LISTBOX_BACK_ACTIVE,		GetSysColor(COLOR_BTNFACE)+RGB(30,30,30), _T("�����б�򱳾�")},
	{LISTBOX_BACK_INACTIVE,		GetSysColor(COLOR_BTNFACE), _T("�ǽ����б�򱳾�")},
	{LISTBOX_TEXT_ACTIVE,		RGB(92,92,92),				_T("�����б���ı�")},
	{LISTBOX_TEXT_INACTIVE,		RGB(100,10,10),				_T("�ǽ����б���ı�")},
	
	{FORMVIEW_BACK,				RGB(240,243,245),			_T("���屳��")},
	{INFOTIP_BACK,				RGB(242,254,197),			_T("��ʾ�򱳾�")},
	{MSGBOX_BACK,				RGB(240,243,245),			_T("��Ϣ�򱳾�")},
	
	{GRID_BKCOLOR,				RGB(18, 20, 22),			_T("��񱳾�")},
    {GRID_FIXED_BKCOLOR,			 DEFAULT_COLOR_GRAY3,	    _T("����ͷ����")},
	{GRID_TEXT_BKCOLOR,			     DEFAULT_COLOR_GRAY1,	    _T("����ı�����")},
	{GRID_TEXT_WHITE,			     DEFAULT_COLOR_WHITE,		_T("����ı�")},
    {GRID_TEXT_RED,			         DEFAULT_COLOR_RED,		    _T("����ı�")},
	{GRID_TEXT_GREEN,			     DEFAULT_COLOR_GREEN,		_T("����ı�")},
	{GRID_TEXT_YELLOW,			     DEFAULT_COLOR_YELLOW,		_T("����ı�")},
	{GRID_ODDLINE_COLOR,		     DEFAULT_COLOR_GRAY1,		_T("�����б���")},
	{GRID_EVENLINE_COLOR,		     DEFAULT_COLOR_GRAY3,		_T("ż���б���")},
	{GRID_BK_GRAY,		             DEFAULT_COLOR_GRAY4,		_T("����ı�����")},
	{GRID_BK_RED,		             DEFAULT_COLOR_RED2,		_T("����ı�����")},
	{GRID_BK_GREEN,		             DEFAULT_COLOR_GREEN,		_T("����ı�����")},
	{GRID_BK_GRAYGREEN,		         DEFAULT_COLOR_GREEN4,		_T("����ı�����")},
	{GRID_BK_YELLOW,		         DEFAULT_COLOR_YELLOW2,		_T("����ı�����")},

	{TABCTRL_ITEM_ACTIVE,		RGB(240,243,245),			_T("����TABҳ����")},
	{TABCTRL_ITEM_INACTIVE,		RGB(240,243,245),			_T("�ǽ���TABҳ����")},
	{TABCTRL_TEXT_ACTIVE,		RGB(90,20,20),				_T("����TABҳ�ı�")},
	{TABCTRL_TEXT_INACTIVE,		RGB(0,0,0),					_T("�ǽ���TABҳ�ı�")},
	{TABCTRL_BACK,				RGB(240,243,245),			_T("TAB����")},
	
	{VIEWTAB_ITEM_ACTIVE,		GetSysColor(COLOR_BTNFACE),	_T("�����ǩ����")},
	{VIEWTAB_ITEM_INACTIVE,		GetSysColor(COLOR_BTNFACE),	_T("�ǽ����ǩ����")},
	{VIEWTAB_TEXT_ACTIVE,		RGB(0,0,225),				_T("�����ǩ�ı�")},
	{VIEWTAB_TEXT_INACTIVE,		RGB(50,50,50),				_T("�ǽ����ǩ�ı�")},
	
	{VIEWBORDER_ACTIVE,		    DEFAULT_COLOR_BLUE7,		_T("�ǽ����ǩ�ı�")},
	{VIEWBORDER_UNACTIVE,		DEFAULT_COLOR_BLUE8,		_T("�ǽ����ǩ�ı�")},	

	{TREEMENU_BACK,				RGB(240,243,245),			_T("���Ͳ˵�����")},
	{TREEMENU_SELECTD_BACK,		RGB(208,221,234),			_T("���Ͳ˵�ѡ�б���")},
	{TREEMENU_SELECTD_TEXT,		RGB(0,0,225),				_T("���Ͳ˵�ѡ���ı�")},
	{TREEMENU_NOTSELECTD_TEXT,	RGB(0,0,0),					_T("���Ͳ˵���ѡ���ı�")},
	
	{TREECTRL_BACK,				RGB(240,243,245),			_T("���Ϳؼ�����")},

	{GROUPBOX_BACK,				RGB(240,243,245),			_T("GROUP�ؼ�����")},
	{MARKET_FONT_UP,			RGB(255, 0, 0),				_T("����۸�����������ɫ")},
	{MARKET_FONT_DOWN,			RGB(0, 153, 0),				_T("����۸��µ�������ɫ")},

	{SELL_BACK,					RGB(180, 204, 187),			_T("������񱳾�")},
	{BUY_BACK,					RGB(241, 197, 191),			_T("�򷽱�񱳾�")},
	{ERROR_TEXT_COLOR,			RGB(255, 0, 0),				_T("�ҵ�����������ɫ")},
	{PEN_BACK_BLUE,					 DEFAULT_COLOR_BLUE6,		_T("������ɫ")},
	{DLG_BACK,					     DEFAULT_COLOR_BK,			_T("�Ի��򱳾���ɫ")},
    {FUNDVIEW_BACK,				     DEFAULT_COLOR_BK,			_T("ʵʱ�ʽ𱳾�ɫ")},

	{TAB_BK_COLOR,				RGB(28, 30, 32),			_T("Dock ��Tab�ı���ɫ")},
	{TABITEM_SELECTED_COLOR,    RGB(38, 40, 42),			_T("Dock��TabItemѡ��ʱ����ɫ")},

	{CONNECT_COLOR,					DEFAULT_COLOR_GREEN,		_T("������ɫ")},
	{DISCONNECT_COLOR,				DEFAULT_COLOR_RED,		_T("������ɫ")},
};

COLORREF CColorSet::m_crCurArr[MAX_COLORSET-1];

CColorSet::CColorSet()
{
	m_bLoadColor  = FALSE;
	for (int i = MIN_COLORSET; i < MAX_COLORSET-1; i++)
	{
		m_crCurArr[i] = m_arrColorSet[i].crDefault;
	}

}

CColorSet::~CColorSet()
{
	SaveColorFile();
}


void CColorSet::LoadColorFile(CString const& szOpCode,CString const& szPath)
{
	sprintf_s(m_szColorFile, "%s\\%s.clr", szPath,szOpCode);

	for (int i = MIN_COLORSET; i < MAX_COLORSET-1; i++)
	{
		m_crCurArr[i] = ReadColorValue(m_arrColorSet[i].szComment, m_arrColorSet[i].crDefault);
	}
	m_bLoadColor = true;
}

void CColorSet::SaveColorFile()
{
	for (int i = MIN_COLORSET; i < MAX_COLORSET-1; i++)
	{
		WriteColorValue(m_arrColorSet[i].szComment, m_crCurArr[i]);
	}
}

COLORREF CColorSet::ReadColorValue(LPCTSTR szColorID, int nDefColor)
{
	TCHAR szValue[32] = {0};

	GetPrivateProfileString(_T("COLOR"), szColorID, _T("FFFFFFFF"), szValue, 32, m_szColorFile);

	COLORREF crValue = nDefColor;
	sscanf_s(szValue, "%X", &crValue);
	if (crValue == -1)
		crValue = nDefColor;

	return crValue;
}

void CColorSet::WriteColorValue(LPCTSTR szColorID, COLORREF crValue)
{
	CString csValue;
	csValue.Format("%X", crValue);

	WritePrivateProfileString(_T("COLOR"), szColorID, csValue, m_szColorFile);
}

LPCTSTR CColorSet::GetComment(COLOR_IT it)
{
	if (it > MIN_COLORSET && it < MAX_COLORSET)
		return m_arrColorSet[it-1].szComment;
	else
		return NULL;
}

COLORREF CColorSet::GetColor(int it)
{

	if (it > MIN_COLORSET && it < MAX_COLORSET)
		return m_crCurArr[it-1];
	else
		return 0;
}

void CColorSet::SetColor(COLOR_IT it, COLORREF crValue)
{
	if (it > MIN_COLORSET && it < MAX_COLORSET)
		m_crCurArr[it-1] = crValue;
}

BOOL CColorSet::ResetColor(COLOR_IT it)
{
	BOOL bColorChanged = FALSE;

	if (it > MIN_COLORSET && it < MAX_COLORSET-1)
	{
		if (m_crCurArr[it-1] != m_arrColorSet[it-1].crDefault)
		{
			m_crCurArr[it-1] = m_arrColorSet[it-1].crDefault;
			bColorChanged = TRUE;
		}
	}

	return bColorChanged;
}

BOOL CColorSet::ResetAllColor()
{
	BOOL bColorChanged = FALSE;

	for (int i = MIN_COLORSET; i < MAX_COLORSET-1; i++)
	{
		if (m_crCurArr[i] != m_arrColorSet[i].crDefault)
		{
			m_crCurArr[i] = m_arrColorSet[i].crDefault;
			bColorChanged = TRUE;
		}
	}

	return bColorChanged;
}
