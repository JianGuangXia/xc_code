
//*****************************************************
//********    SimpleButton By YaoShuLong 2017.1
//*****************************************************

#include "stdafx.h"
#include "SpecialImageButton.h"


// CSpecialImageButton

IMPLEMENT_DYNAMIC(CSpecialImageButton, CWnd)

CSpecialImageButton::CSpecialImageButton() :
m_bMouseEnter(FALSE),
m_bMouseIn(FALSE),
m_bLMouseDown(FALSE)
{
    RegisterWindowClass();
    m_bEnable = TRUE;
    m_bChangeCursor = FALSE;
    m_bEnableClickToGetFocus = FALSE;
}

CSpecialImageButton::~CSpecialImageButton()
{
}


BEGIN_MESSAGE_MAP(CSpecialImageButton, CWnd)
    ON_WM_PAINT()
    ON_WM_MOUSELEAVE()
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDOWN()
    ON_WM_ERASEBKGND()
    ON_WM_SETCURSOR()
END_MESSAGE_MAP()

// CSpecialImageButton ��Ϣ�������

//void CSpecialImageButton::OnPaint()
//{
//    CPaintDC dc(this);
//
//    CRect rCl;
//    GetClientRect(&rCl);
//    CDC dcMem;
//    CBitmap bmpMem;
//    CBitmap* pOldBmp=NULL;
//
//    if (m_bEnable)
//    {
//        if (m_bMouseIn)
//        {
//            if (m_bLMouseDown)
//            {      
//                bmpMem.LoadBitmap(m_nDefBmpID);
//            } 
//            else
//            {
//                bmpMem.LoadBitmap(m_nHoverBmpID);
//            }
//        } 
//        else
//        {    
//            bmpMem.LoadBitmap(m_nDefBmpID);
//        }
//    } 
//    else
//    {
//        bmpMem.LoadBitmap(m_nDisabledBmpID);
//    }
//
//    if(dcMem.CreateCompatibleDC(&dc))
//    {
//        pOldBmp = dcMem.SelectObject(&bmpMem);
//
//    }
//    else
//        return;
//
//    dc.BitBlt(rCl.left,rCl.top,rCl.Width(),rCl.Height(),&dcMem,rCl.left,rCl.top,SRCCOPY);
//    dcMem.SelectObject(pOldBmp);
//    dcMem.DeleteDC();
//    bmpMem.DeleteObject();
//}

void CSpecialImageButton::OnPaint()
{
	CPaintDC dc(this);

	CRect rCl;
	GetClientRect(&rCl);
	CDC dcMem;
	CBitmap bmpMem;
	CBitmap* pOldBmp = NULL;
	CString strBmpPath;

	if (m_bEnable)
	{
		if (m_bMouseIn)
		{
			if (m_bLMouseDown)
			{
				strBmpPath = m_strDefBmpPath;
			}
			else
			{
				strBmpPath = m_strHoverBmpPath;
			}
		}
		else
		{
			strBmpPath = m_strDefBmpPath;
		}
	}
	else
	{
		strBmpPath = m_strDisabledBmpPath;
	}

	HBITMAP hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), strBmpPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpMem.Attach(hBitmap);


	if (dcMem.CreateCompatibleDC(&dc))
	{
		pOldBmp = dcMem.SelectObject(&bmpMem);

	}
	else
		return;

	BITMAP bitMap;
	bmpMem.GetBitmap(&bitMap);
	bitMap.bmWidth;
	if (rCl.Height() <= bitMap.bmHeight)
	{
		int nScrTop = (bitMap.bmHeight - rCl.Height()) / 2;
		dc.BitBlt(0, 0, rCl.Width(), rCl.Height(), &dcMem, rCl.left, nScrTop, SRCCOPY);
	}
	else
	{
		int nTop = 0;
		int nHeight = 180;
		while (true)
		{
			BOOL bBreak = FALSE;
			if (nTop + nHeight > rCl.Height())
			{
				nHeight = rCl.Height() - nTop;
				bBreak = TRUE;
			}
			dc.BitBlt(0, nTop, rCl.Width(), nHeight, &dcMem, 0, 0, SRCCOPY);
			if (bBreak)
			{
				break;
			}
			nTop += nHeight;
		}
		nTop = (rCl.Height() - bitMap.bmHeight) / 2;
		dc.BitBlt(0, nTop, rCl.Width(), bitMap.bmHeight, &dcMem, 0, 0, SRCCOPY);
	}
	//dc.BitBlt(rCl.left, rCl.top, rCl.Width(), rCl.Height(), &dcMem, rCl.left, rCl.top, SRCCOPY);
	dcMem.SelectObject(pOldBmp);
	dcMem.DeleteDC();
	bmpMem.DeleteObject();
}

//BOOL CSpecialImageButton::Create(CString strCaption, UINT dwStyle, const CRect & rect, CWnd * pParentWnd, UINT nID)
BOOL CSpecialImageButton::Create(UINT nDefBmpID, UINT nHoverBmpID, UINT nDisabledBmpID, UINT dwStyle, const CRect & rect, CWnd * pParentWnd, UINT nID, CString strCaption)
{
    m_nDefBmpID = nDefBmpID;
    m_nHoverBmpID = nHoverBmpID;
    m_nDisabledBmpID = nDisabledBmpID;
    m_strCaption = strCaption;
    return CWnd::Create(SpecialImageButton_CLASSNAME, _T(""), dwStyle, rect, pParentWnd, nID);
}

BOOL CSpecialImageButton::Create(CString strDefBmpPath, CString strHoverBmpPath, CString strDisabledBmpPath, UINT dwStyle, const CRect & rect, CWnd * pParentWnd, UINT nID)
{
	m_strDefBmpPath = strDefBmpPath;
	m_strHoverBmpPath = strHoverBmpPath;
	m_strDisabledBmpPath = strDisabledBmpPath;

	return CWnd::Create(SpecialImageButton_CLASSNAME, _T(""), dwStyle, rect, pParentWnd, nID);
}

BOOL CSpecialImageButton::RegisterWindowClass()
{
    WNDCLASS wndcls;
    HINSTANCE hInst = AfxGetInstanceHandle();

    if (!(::GetClassInfo(hInst, SpecialImageButton_CLASSNAME, &wndcls)))
    {
        wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
        wndcls.lpfnWndProc      = ::DefWindowProc;
        wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
        wndcls.hInstance        = hInst;
        wndcls.hIcon            = NULL;
        wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
        wndcls.hbrBackground    = (HBRUSH) (COLOR_3DFACE + 1);
        wndcls.lpszMenuName     = NULL;
        wndcls.lpszClassName    = SpecialImageButton_CLASSNAME;

        if (!AfxRegisterClass(&wndcls))
        {
            AfxThrowResourceException();
            return FALSE;
        }
    }

    return TRUE;
}

void CSpecialImageButton::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (GetFocus()->GetSafeHwnd() != GetSafeHwnd() && m_bEnableClickToGetFocus)
    {
        SetFocus();
    }
    m_bLMouseDown = TRUE;
    Invalidate(FALSE);

    CWnd::OnLButtonDown(nFlags, point);
}

void CSpecialImageButton::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (m_bLMouseDown)
    {
        NMHDR hdr;
        hdr.idFrom = GetDlgCtrlID();
        hdr.hwndFrom = GetSafeHwnd();
        hdr.code = NM_CLICK;
        GetParent()->SendMessage(WM_NOTIFY,GetDlgCtrlID(),(LPARAM)&hdr);
        m_bLMouseDown = FALSE;
        Invalidate(FALSE);
    }
    
    CWnd::OnLButtonUp(nFlags, point);
}

void CSpecialImageButton::OnMouseLeave()
{
    m_bMouseEnter = FALSE;
    m_bLMouseDown = FALSE;
    m_bMouseIn = FALSE;
    if (!m_bLMouseDown)
    {
        Invalidate(FALSE);
    }
    CWnd::OnMouseLeave();
}


void CSpecialImageButton::OnMouseMove(UINT nFlags, CPoint point)
{
    if (!m_bMouseIn)
    {

        TRACKMOUSEEVENT csTME;
        csTME.cbSize = sizeof (csTME);    
        csTME.dwFlags = TME_LEAVE|TME_HOVER;    
        csTME.hwndTrack = GetSafeHwnd(); // ָ��Ҫ ׷�� �Ĵ���     
        csTME.dwHoverTime = 10;  // ����ڰ�ť��ͣ������ 10ms ������Ϊ״̬Ϊ HOVER   
        ::_TrackMouseEvent (&csTME); // ���� Windows �� WM_MOUSELEAVE 
        m_bMouseIn = TRUE;
        Invalidate(FALSE);
    }

    
    CWnd::OnMouseMove(nFlags, point);
}


BOOL CSpecialImageButton::OnEraseBkgnd(CDC* pDC)
{
    return TRUE;
}

void CSpecialImageButton::SetWindowText(CString string)
{
    m_strCaption = string;
    Invalidate(FALSE);
}

void CSpecialImageButton::GetWindowText(CString& string)
{
    string = m_strCaption;
}

void CSpecialImageButton::SetImage(UINT nDefBmpID, UINT nHoverBmpID, UINT nDisabledBmpID)
{
    m_nDefBmpID = nDefBmpID;
    m_nHoverBmpID = nHoverBmpID;
    m_nDisabledBmpID = nDisabledBmpID;
    Invalidate(FALSE);
}

BOOL CSpecialImageButton::EnableWindow(BOOL bEnable /* = TRUE */)
{
    m_bEnable = bEnable;
    Invalidate(FALSE);
    return CWnd::EnableWindow(bEnable);
}

BOOL CSpecialImageButton::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
    if (m_bChangeCursor)
    {
        ::SetCursor(::LoadCursor(NULL  , IDC_HAND ) );
        return TRUE;
    }
    else
    {
        return CWnd::OnSetCursor(pWnd, nHitTest, message);
    }
}

void CSpecialImageButton::SetChangeCursor(BOOL bChangeCursor)
{
    m_bChangeCursor = bChangeCursor;
}

void CSpecialImageButton::EnableClickToGetFocus(BOOL bEnable)
{
    m_bEnableClickToGetFocus = bEnable;
}