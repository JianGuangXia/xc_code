#include "stdafx.h"
#include "MessageEdit.h"
//#include "mainfrm.h"
//#include "SimpleGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessageEdit

CMessageEdit::CMessageEdit()
{
	m_bCharMap = true;
	m_bPrice = false;
	m_bQtyInput = false;
	m_bListSort = false;
	m_ParentWnd = NULL;
	m_MaxLength = 100;


	m_nZeroLength = -1;

	m_attachPosition.RowIndex = -1;
	m_attachPosition.ColIndex = -1;
}

CMessageEdit::~CMessageEdit()
{
}


BEGIN_MESSAGE_MAP(CMessageEdit, CEdit)
	//{{AFX_MSG_MAP(CMessageEdit)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_CHAR()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	//ON_WM_NCPAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*************************************************************
* �������ƣ� PreTranslateMessage
* ���������� �༭�����ϢԤ������,�����û�����Ļس���ESC����
* ��������� pMsg   �������Ϣ�ṹ
* ��������� void
* �� �� ֵ�� void
* ����˵���� ��
*************************************************************/
BOOL CMessageEdit::PreTranslateMessage(MSG* pMsg) 
{
	
	switch(pMsg->message)
	{
		case WM_KEYDOWN :
		{
			m_LastKey = pMsg->wParam;
			switch (pMsg->wParam)
			{
				case VK_TAB:
					if(ME_IsSHIFTpressed())
					{
						GetWindowText(m_InputStr );
						//g_AnyTraderDoc.AddZeroLeft(m_nZeroLength,m_InputStr);
						SetWindowText(m_InputStr );
						GetParent()->PostMessage(WM_BACKTAB,(WPARAM)(&m_InputStr ),0);
						return TRUE;
					}
					else
					{
						GetWindowText(m_InputStr );
						//g_AnyTraderDoc.AddZeroLeft(m_nZeroLength,m_InputStr);
						SetWindowText(m_InputStr );
						//SetWindowText()
						//if(GetDlgCtrlID() == IDC_EDIT_SORT)
						//	GetParent()->PostMessage(WM_ENTERDOWN,(WPARAM)(&m_InputStr ),1);
						//else
							GetParent()->PostMessage(WM_ENTERDOWN,(WPARAM)(&m_InputStr ),0);
						return TRUE;
					}

				case VK_RETURN:
					{
					GetWindowText(m_InputStr );
					/*if(!m_InputStr.IsEmpty())
					{
						g_AnyTraderDoc.AddZeroLeft(m_nZeroLength,m_InputStr);
					}*/
					SetWindowText(m_InputStr );
					//if(GetDlgCtrlID() == IDC_EDIT_SORT)
					//	GetParent()->PostMessage(WM_ENTERDOWN,(WPARAM)(&m_InputStr ),1);
					//else
						//if(GetDlgCtrlID() == IDC_EDIT_INPUT)
						//	GetParent()->PostMessage(WM_ENTERDOWN,(WPARAM)(&m_InputStr ),1);
						//else
							GetParent()->GetParent()->PostMessage(WM_ENTERDOWN,(WPARAM)(&m_InputStr ),0);
						//g_pArbiDialog->PostMessage(WM_ENTERDOWN,(WPARAM)(&m_InputStr ),0);
					return TRUE;
					}
				break;
				case VK_ESCAPE:

					GetWindowText(m_InputStr );
					//g_AnyTraderDoc.AddZeroLeft(m_nZeroLength,m_InputStr);
					SetWindowText(m_InputStr );
					if(m_bListSort == TRUE)
					{
						ShowWindow(FALSE);
						//GetParent()->PostMessage(WM_ENTERESCAPE,(WPARAM)(&m_InputStr ),1);
					}
					else
					{
						GetParent()->GetParent()->PostMessage(WM_ENTERESCAPE,(WPARAM)(&m_InputStr),1);
						//g_pArbiDialog->PostMessage(WM_ENTERESCAPE,(WPARAM)(&m_InputStr ),0);
					}
					return TRUE;
				default:
				break;
			}
		}
		break;
	}
	return CEdit::PreTranslateMessage(pMsg);
}

/*************************************************************
* �������ƣ� OnSetFocus
* ���������� ����ǰ�Ľ�������Ϊ�༭��
* ��������� pOldWnd   �´��ڵľ��
* ��������� void
* �� �� ֵ�� void
* ����˵���� ��
*************************************************************/
void CMessageEdit::OnSetFocus(CWnd* pOldWnd) 
{
	//RedrawWindow();
	//SetSel(0,2);
	GetParent()->PostMessage(WM_EDITSETFOCUS,(WPARAM)(GetDlgCtrlID()));
	CEdit::OnSetFocus(pOldWnd);
	//SetSel(0,2);
	
}

/*************************************************************
* �������ƣ� OnKillFocus
* ���������� �༭��ʧȥ����
* ��������� pNewWnd   �´��ڵľ��
* ��������� void
* �� �� ֵ�� void
* ����˵���� ��
*************************************************************/
void CMessageEdit::OnKillFocus(CWnd* pNewWnd) 
{

	CEdit::OnKillFocus(pNewWnd);

	if(m_nZeroLength > 0)
	{
		GetWindowText(m_InputStr );
		CString ZeroStr('0',m_nZeroLength);
		if(m_InputStr.GetLength() > 0 && m_InputStr.GetLength() < m_nZeroLength) 
		{
			m_InputStr = ZeroStr.Left(m_nZeroLength-m_InputStr.GetLength())+m_InputStr;
		}
		SetWindowText(m_InputStr);
	}
	//���ڻ��Ի�����ʧȥ�������Ϣ
	if(m_bListSort == TRUE)
	{
		//GetParent()->PostMessage(WM_ENTERDOWN,(WPARAM)(&m_InputStr ),2);
	}
	else
	{
		GetParent()->GetParent()->PostMessage(WM_EDITKILLFOCUS,(WPARAM)this, (LPARAM)(&m_attachPosition));
		//g_pArbiDialog->PostMessage(WM_EDITKILLFOCUS,(WPARAM)this);
	}
	// TODO: Add your message handler code here
	
}


/************************************************************
* �������ƣ� CMessageEdit::OnChar
* ���������� �����û�������
* ���������� UINT nChar
* ���������� UINT nRepCnt
* ���������� UINT nFlags
* �� �� ֵ�� void 
*************************************************************/
void CMessageEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar == 22 || nChar == 3)
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
		GetParent()->PostMessage(WM_CHANGED,0,0);
		return;
	}
	if(m_bPrice == true)
	{
		GetWindowText(m_InputStr);
		if (nChar == '.' && m_InputStr.Find(nChar, 0) > 0)
		{
			return;
		}
		if(/*nChar == '-' || */nChar == '.' || isdigit(nChar) || nChar == VK_BACK || nChar == VK_TAB)
		{
			;
		}
		else
		{
			return;
		}
	}
	if(m_bQtyInput == true)
	{
		if(isdigit(nChar) || nChar == VK_BACK || nChar == VK_TAB)
		{
			;
		}
		else
		{
			return;
		}
	}
	int nStartChar = 0;
	int nEndChar = 0;
	GetSel(nStartChar, nEndChar) ;
	if(m_bCharMap == true)
	{//����ǵ�������map
		POSITION Pos = m_MapList.GetHeadPosition();
		while(Pos)
		{
			INPUT_MAP *pMap = m_MapList.GetNext(Pos);
			if(pMap->nChar == nChar)
			{
				SetWindowText(pMap->ViewStr);
				/*if(GetDlgCtrlID() == IDC_EDIT_ORDER)
				{
					GetParent()->PostMessage(WM_CHANGEORDER,(WPARAM)nChar);
				}*/
				SetSel(0,-1);
				return;
			}
		}
		if(m_MapList.GetCount() > 0)
		{
			SetWindowText("");
			return;
		}
	}
	else 
	{
		if(nStartChar != nEndChar)
		{
			//CString ReplStr = nChar;
			CString ReplStr;
			ReplStr.Format("%c", nChar);
			ReplaceSel(ReplStr);
		}

		CString strTemp;
		int nCount = m_MapStrList.GetCount();
		POSITION Pos = m_MapStrList.GetHeadPosition();
		while(Pos)
		{
			INPUT_STR_MAP *pMap = m_MapStrList.GetNext(Pos);
			CString CurStr;
			GetWindowText(CurStr);
			if(nStartChar == nEndChar)
			{
				strTemp.Format("%c", nChar);
				CurStr += strTemp;
			}
		}
	}

	CString strTemp;
	CString CurStr;
	GetWindowText(CurStr);
	if(nStartChar == nEndChar)
	{
		strTemp.Format("%c", nChar);
		CurStr += strTemp;
	}
	if(m_MaxLength > 0 && CurStr.GetLength() > m_MaxLength)
	{
		if(nChar == 8 || nStartChar != nEndChar) 
		{
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		}
		return ;
	}
	if(m_bCharMap == false && nStartChar != nEndChar)
	{
		return;
	}
	if( m_MapList.IsEmpty() || nStartChar != nEndChar)
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	//SendDlgItemMessage
	GetParent()->PostMessage(WM_CHANGED,0,0);
	//GetParent()->SendDlgItemMessage(IDC_EDIT_INPUT,EN_CHANGE,0,0);
}


/************************************************************
* �������ƣ� CMessageEdit::SetLimitCharInput
* ���������� ��������Ŀ��ת��
* ���������� char cPress
* ���������� CString str
* �� �� ֵ�� void 
*************************************************************/
void CMessageEdit::SetLimitCharInput(char cPress,CString str)
{
	m_bCharMap = true;
	INPUT_MAP *pMap = new INPUT_MAP;
	pMap->nChar = cPress;
	pMap->ViewStr = str;
	m_MapList.AddTail(pMap); 
}


/************************************************************
* �������ƣ� CMessageEdit::SetLimitStrInput
* ���������� �����ַ��������ת����
* ���������� CString InputStr
* ���������� CString str
* �� �� ֵ�� void 
*************************************************************/
void CMessageEdit::SetLimitStrInput(CString InputStr,CString str)
{
	m_bCharMap = false;
	INPUT_STR_MAP *pMap = new INPUT_STR_MAP ;
	pMap->InputStr = InputStr;
	pMap->ViewStr = str;
	m_MapStrList.AddTail(pMap); 
}


/************************************************************
* �������ƣ� CMessageEdit::OnDestroy
* ���������� ���ٴ���
* �� �� ֵ�� void 
*************************************************************/
void CMessageEdit::OnDestroy() 
{
	CEdit::OnDestroy();
	while(!	m_MapList.IsEmpty()) delete m_MapList.RemoveHead();
	while(!	m_MapStrList.IsEmpty()) delete m_MapStrList.RemoveHead();
	// TODO: Add your message handler code here
	
}



/************************************************************
* �������ƣ� CMessageEdit::DeleteMap
* ���������� ɾ�����е�map����
* �� �� ֵ�� void 
*************************************************************/
void CMessageEdit::DeleteMap()
{
	while(!	m_MapList.IsEmpty()) delete m_MapList.RemoveHead();
	while(!	m_MapStrList.IsEmpty()) delete m_MapStrList.RemoveHead();
}

void CMessageEdit::DeleteCharMap()
{
	while(!	m_MapList.IsEmpty()) delete m_MapList.RemoveHead();
}


/************************************************************
* �������ƣ� CMessageEdit::OnKeyDown
* ���������� ��Ӧ��������
* ���������� UINT nChar
* ���������� UINT nRepCnt
* ���������� UINT nFlags
* �� �� ֵ�� void 
*************************************************************/
void CMessageEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
	/*if(GetDlgCtrlID() == IDC_EDIT_LEGPRICE1 || GetDlgCtrlID() == IDC_EDIT_LEGPRICE2)
	{
		GetParent()->PostMessage(WM_CHANGEPRICEEDIT,0,GetDlgCtrlID());
	}*/
}



/************************************************************
* �������ƣ� CMessageEdit::SetPriceInput
* ���������� ����Ϊ�۸�����
* ���������� bool flag
* �� �� ֵ�� void 
*************************************************************/
void CMessageEdit::SetPriceInput(bool flag)
{
	m_bPrice = flag;
	m_bQtyInput = !m_bPrice;
}


/************************************************************
* �������ƣ� CMessageEdit::SetQtyInput
* ���������� ����Ϊ��������
* ���������� bool flag
* �� �� ֵ�� void 
*************************************************************/
void CMessageEdit::SetQtyInput(bool flag)
{
	m_bQtyInput = flag;
	m_bPrice = !m_bQtyInput;
}

void CMessageEdit::SetListSort(bool flag)
{
	m_bListSort = flag;
}


/************************************************************
* �������ƣ� CMessageEdit::SetParentWnd
* ���������� ���ø�����
* ���������� CWnd *pParent
* �� �� ֵ�� void 
*************************************************************/
void CMessageEdit::SetParentWnd(CWnd *pParent)
{
	m_ParentWnd = pParent;
}

/************************************************************
* �������ƣ� CMessageEdit::SetFastKey
* ���������� ���ú�Լ��ݼ�
* �� �� ֵ�� void 
*************************************************************/
void CMessageEdit::SetFastKey()
{
	CString CurStr;
	GetWindowText(CurStr);
	POSITION Pos = m_MapStrList.GetHeadPosition();
	while(Pos)
	{
		INPUT_STR_MAP *pMap = m_MapStrList.GetNext(Pos);


		if(pMap->InputStr == CurStr)
		{
			SetWindowText(pMap->ViewStr);
			SetSel(0,-1);
			return;
		}
	}
}

void CMessageEdit::OnChange() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CEdit::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	/*if(GetDlgCtrlID() == IDC_EDIT_MBL )
	{
		CMainFrame *pMain;
		pMain = (CMainFrame *)AfxGetMainWnd();
		CString str ,strOld;
		GetWindowText(str);
		int nCon,nRet;
		nRet = GetPrivateProfileInt("config", "������鼶��", nCon, WATCHTABLE_FILE);
		strOld.Format("%d",nRet);
		if(atoi(str.GetBuffer(0)) > 50)
		{
			SetWindowText(strOld);
			AfxMessageBox("������鼶���������Ϊ50");
			SetSel(0,-1);
			return;
		}
		if(atoi(str.GetBuffer(0)) < 1)
		{
			SetWindowText(strOld);
			AfxMessageBox("������鼶����С����Ϊ1");
			SetSel(0,-1);
			return;
		}
		int nCtrlID = GetParent()->GetDlgCtrlID();
		//pMain->m_TraderFrame->m_Frame.m_MmpPaneCtrl.m_pMmpDialog->PostMessage(WM_PAINT);
		
	}*/

}


void CMessageEdit::OnNcPaint() 
{
	CRect rcWnd;
    GetWindowRect(&rcWnd);
         
    CWnd *pParent = GetParent();            
    pParent->ScreenToClient(&rcWnd);        
    CDC *pDC = pParent->GetDC();    
         
    COLORREF crPen = RGB(215,215,215);
    COLORREF crPen2 = RGB(241,241,241);

    CPen aPen,bPen;
    aPen.CreatePen(PS_SOLID, 1, crPen);
    bPen.CreatePen(PS_SOLID, 1, crPen2);
    CBrush* oldbrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)); 

    CPen* pOldPen = pDC->SelectObject(&bPen);
    rcWnd.top-=2;
    rcWnd.left-=2;
    rcWnd.right+=2;
    rcWnd.bottom+=2;
	pDC->SelectObject(&bPen);
    pDC->Rectangle(&rcWnd);

	pDC->SelectObject(&aPen);	
	rcWnd.top-=1;
    rcWnd.left-=1;
    rcWnd.right+=1;
    rcWnd.bottom+=1;
    pDC->Rectangle(&rcWnd);

	

    pDC->SelectObject(pOldPen);
 
    pDC->SelectObject(oldbrush);
    pParent->ReleaseDC(pDC);
}

void CMessageEdit::SetAttachPosition(const ATTACH_POSITION &attachPosition)
{
	memcpy(&m_attachPosition, &attachPosition, sizeof(attachPosition));
}
