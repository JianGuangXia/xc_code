#pragma once


class CSimpleDateTimePicker;

#define SIMPLECALENDAR_CLASSNAME    _T("CSimpleCalendar")

#define SCSC_BACKGROUND   0   // the background color (between months)
#define SCSC_TEXT         1   // the dates
#define SCSC_TITLEBK      2   // background of the title
#define SCSC_TITLETEXT    3
#define SCSC_MONTHBK      4   // background within the month cal
#define SCSC_TRAILINGTEXT 5   // the text color of header & trailing days
#define SCSC_SELBK        6   // the text color of Sel cell bk 
#define SCSC_SELBORDER    7   // the text color of Sel cell Border

// CSimpleCalendar

class CSimpleCalendar : public CWnd
{
	DECLARE_DYNAMIC(CSimpleCalendar)
	enum {
		IDC_EDIT_YEAR = 0X10001,
		IDC_EDIT_MONTH,
		IDC_BUTTON_MONTHPRE,
		IDC_BUTTON_MONTHNEXT
	};
	enum MC_STATE 
	{
		EMPTY = 0X0001,
		UNSELECTED,
		SELECTED,
	};
	struct MC_DATE
	{
		int mcDay;
		MC_STATE mcState;
		bool mcToday;
		bool mcWeekendDay; 
		CRect mcRcCell;
	};


public:
	CSimpleCalendar();
	virtual ~CSimpleCalendar();

	BOOL Create(CWnd *pParent);
	void ShowCalendar(int nCmdShow);
	void SetFont(HFONT hFont);
	void SetColor(int nRegion, COLORREF ref);

	int GetYear();
	int GetMonth();
	int GetDay();

	void SetYear(int year);
	void SetMonth(int month);
	void SetDay(int day);

private:
	bool RegisterWindowClass();
	bool IsLeapYear(int year);//�Ƿ�������

	void InitCellRect();// ��ʼ������cell
	void RefreshCellDate();//ˢ������������������
	void RefreshTitleDate();//ˢ��title������
	void RefreshMonthCell();//ˢ������

	void DrawTitleDate(CDC *pDC);//��title������
	void DrawWeek(CDC *pDC);//��week������
	void DrawDate(CDC *pDC);//������

	int GetDayOfWeek(int year, int month, int day);//�����������ݼ�
	int GetDaysOfMonth(int year, int month);//��ȡ���µ�����
	int GetClickedCell(CPoint pt); //��ȡѡ�е�������

	void SetCellState(int nIndex, bool bHighlight);//����ѡ�������񱳾�ɫ

private:
	int m_nYear;
	int m_nMonth;
	int m_nDay;

    CFont m_font;
	HFONT m_Font;
	CBrush m_brushBk;

	COLORREF m_crlBackground;
	COLORREF m_crlText;
	COLORREF m_crlSelBk;
	COLORREF m_crlSelBorder;
	COLORREF m_crlTitleBk;
	COLORREF m_crlTitleText;
	COLORREF m_crlTrailingText;
	COLORREF m_crlMonthBk;

	CRect m_rcTitleDate;

	CEdit m_tbYear;
	CEdit m_tbMonth;
	CBitmapButton m_btnMonthPre;
	CBitmapButton m_btnMonthNext;

	int m_nSelIndex;
	MC_DATE m_Dates[42];
	CSimpleDateTimePicker *m_pParent;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);

	afx_msg void OnClickedButtonMonthPre();
	afx_msg void OnClickedButtonMonthNext();
	afx_msg void OnChangeEditYear();
	afx_msg void OnChangeEditMonth();
	afx_msg void OnKillfocusEditYear();
	afx_msg void OnKillfocusEditMonth();
};


