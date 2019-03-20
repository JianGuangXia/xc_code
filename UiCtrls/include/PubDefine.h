#ifndef __PUBDEFINE_H__
#define __PUBDEFINE_H__

#include <vector>

#define UM_DOCKSTATECHANGE			(WM_USER + 1000)
#define UM_GETDOCKWINDOWRECT		(WM_USER + 1001)
#define UM_FLOATWINDOW				(WM_USER + 1002)

#define HDOCKPARENT		HWND

#define DOCKBAR			void*

#define DC_ADJUSTDRAGRECT		(7)

typedef struct tagSPDOCKRECT
{
	DOCKBAR		dockBar;
	HWND		hWnd;

	RECT		rect;
	UINT		flag;
	BOOL		bHideTabItem;
} SPDOCKRECT;

typedef struct tagSPDOCKPOS
{
	HDOCKPARENT			hParent;
	HWND				hWnd;
	DWORD				dwDockSide;
	unsigned long		nWidth;
	unsigned long		nHeight;
	HWND				hDestWnd;
	BOOL				bHideTabItem;
} SPDOCKPOS;

typedef struct tagSPDOCKER
{
	HWND		hWnd;
	HDOCKPARENT	pDockParent;
	UINT		flag;
} SPDOCKER;

enum EM_SIDE
{
	SIDE_LEFT	= 0,	
	SIDE_TOP,
	SIDE_RIGHT,
	SIDE_BOTTOM,
	SIDE_TAB,
	
	SIDE_FULL,
		
};

typedef struct tagDockInfo
{
	CRect rcPos;					//��������
	CRect rcParentPos;				//ͣ���ĸ�����
	std::vector<HWND> vcthWnd;		//��ͣ���Ĵ���TAB�����������
	BOOL bHorizontal;				//ͣ��������ҷָ������Ϸָ�
	BOOL bContainer;				//true�����������»���������
	BOOL bHideTab;
	int nChildNo;					//-1,�Ǹ���㣬0�����ӽ��1���ӽ��
	int nSplitterType;				// -1 �޷ָ��� 1 right 2 bottom
}DOCKINFO;

class CCallBackListener
{
public:
	
	// triggered when client view client view wnd has gained the keyboard focus
	virtual void ClientActivate(HWND childWnd, HWND clientViewWnd) = 0;
	// triggered when client view client view wnd got doble mouse click on the tab button
	virtual void ClientDblClick(HWND childWnd, HWND clientViewWnd) = 0;
	// triggered the close button was pushed for the client view client
	virtual void ClientCloseClick(HWND childWnd, HWND clientViewWnd) = 0;
	
	// drag and drop notifications
	virtual void DragStart(HWND childWnd, HWND clientViewWnd, long x, long y, DWORD keysPressed) = 0;
	virtual void DragOver(HWND childWnd, HWND clientViewWnd, long x, long y, DWORD keysPressed, bool &cancelDrag) = 0;
	virtual void DragDrop(HWND childWnd, HWND clientViewWnd, long x, long y, DWORD keysPressed) = 0;
	virtual void DragCancel(HWND childWnd, HWND clientViewWnd) = 0;
}; // interface CallBackListenerr

class COrientedRect : public CRect
{
public:
	COrientedRect(bool bHorizontal,unsigned long thickness)
		:m_thickness(thickness),m_bHorizontal(bHorizontal)
	{
	}
	void SetOrientation(bool bHorizontal)
	{
		m_bHorizontal=bHorizontal;
	}
	bool GetOrientation() const
	{
		return m_bHorizontal;
	}
	bool IsHorizontal() const
	{
		return m_bHorizontal;
	}
	long GetThickness() const
	{
		return m_thickness;
	}
	bool CalculateRect(CRect& rc,bool bTop)
	{
		CopyRect(rc);
		if(IsHorizontal())
		{
			if(bTop)
				rc.top=bottom=top+GetThickness();
			else
				rc.bottom=top=bottom-GetThickness();
		}
		else
		{
			if(bTop)
				rc.left=right=left+GetThickness();
			else
				rc.right=left=right-GetThickness();
		}
		return true;
	}
protected:
	bool			m_bHorizontal;
	unsigned long	m_thickness;
};

class CDockListener
{
public:
	virtual bool Undock(HWND hWnd) = 0;
	virtual bool RefreshTabTitle(HWND hWnd) = 0;
	virtual bool AdjustDragRect(SPDOCKRECT &dockRect) = 0;
	virtual bool Dock(SPDOCKRECT &dockRect) = 0;
	virtual bool SetDragFlag(BOOL bDragFlag) = 0;
};

#endif // __PUBDEFINE_H__