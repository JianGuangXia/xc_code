#pragma once
class CDockLayoutWnd
{
public:
	enum LAYOUT_DIR
	{
		ROOT_LEFT,
		ROOT_RIGHT,
		ROOT_TOP,
		ROOT_BOTTOM,
		ROOT_CENTER,
		LEFT,
		RIGHT,
		TOP,
		BOTTOM,
		CENTER,
	};
	CDockLayoutWnd(void);
	~CDockLayoutWnd(void);
	HWND GetHWND() const;
	operator HWND() const;
	bool RegisterWindowClass();
	HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL);
	void ShowWindow(bool bShow = true, bool bTakeFocus = true);
	LRESULT SendMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);
	LRESULT PostMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);
	LPCTSTR GetWindowClassName() const;
	void ResizeDockButton(LPPOINT pt,LPRECT rcDockPage);
	LPRECT GetDockRect();
	LAYOUT_DIR GetLayoutDir();
protected:
	static LRESULT CALLBACK __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void Draw(HDC hdc);
	HBITMAP LoadImageFromResource(UINT nId);
	void DrawAlpha(HDC hDC, const CRect& rect, const COLORREF clrMask, const int alp);
	void DrawImage(HDC hDC, const CRect& rect,HBITMAP hBitMap);
	HMODULE GetCurrentModule();
protected:
	HWND	m_hWnd;
	CRect	m_rcLeft;		//�н�ͣ���������ָʾ��ť
	CRect	m_rcRight;		//�н�ͣ�������Ҳ�ָʾ��ť
	CRect 	m_rcTop;		//�н�ͣ�������ϲ�ָʾ��ť
	CRect	m_rcBottom;		//�н�ͣ�������²�ָʾ��ť
	CRect   m_rcDrawDock;	//��Ҫͣ��������
	CRect	m_rcCenter;		//Ҫͣ���Ĵ���ָʾ��ť
	LAYOUT_DIR m_nEmSize;
	HBITMAP m_hBitmapDockCenter;
	HBITMAP m_hBitmapDockLeft;
	HBITMAP m_hBitmapDockRight;
	HBITMAP m_hBitmapDockUp;
	HBITMAP m_hBitmapDockDown;

};

