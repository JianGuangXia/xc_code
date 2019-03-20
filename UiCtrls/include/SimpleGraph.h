
//*****************************************************
//********    SimpleGraph By YaoShuLong 2017.9
//*****************************************************

#pragma once

#include<vector>
using namespace std;

// CSimpleGraph

#define SimpleGraph_CLASSNAME    _T("CSimpleGraph")

class CSimpleGraph : public CWnd
{
	DECLARE_DYNAMIC(CSimpleGraph)

public:
	CSimpleGraph();
	virtual ~CSimpleGraph();

    BOOL Create(UINT dwStyle, CWnd * pParentWnd, UINT nID);

private:
    BOOL RegisterWindowClass();
    double TransY(double dMix, double dMax, double dY, double dYLength);
    void GetLimit(double& dLowerLimit, double& dUpperLimit);

private:
   
    UINT m_nIDLine1;
    UINT m_nIDLine2;

    COLORREF m_clrBk;
    COLORREF m_clrLine1;
    COLORREF m_clrLine2;

    int m_nTick;
    int m_nPos;
    int m_nSingleLinePointsMaxCounts;

    int m_nUpperOffset;
    int m_nLowerOffset;
    vector<double> m_vecY;
    vector<double> m_vecY1;
    vector<double> m_vecY2;
    CRect m_rectClient;

protected:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnPaint();
    afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

public:
    //����2���ߵ���ɫ
    void SetLineColor(COLORREF clrLine1, COLORREF clrLine2);
    //���ñ�����ɫ
    void SetBkColor(COLORREF clr);
    //2���ߵ�Yֵ��ע���1��ֵ��Ӧ��1���ߣ���2��ֵ��ͬ
    void DrawLine(double dY1, double dY2);
    //X��ÿ����һ����ľ���
    void SetXTick(int nTick);
    //���ߵľ������ұߵ�λ�ã�
    void SetDrawPosToRight(int nPos);
    //�����
    void Clear();
    //�������¼��
    void SetOffset(int nUpperOffset, int nLowerOffset);
};


