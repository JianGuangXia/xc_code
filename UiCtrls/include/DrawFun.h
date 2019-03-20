#pragma once

class CUserCustomClip
{
public:
	~CUserCustomClip();
	RECT rcItem;
	HDC hDC;
	HRGN hRgn;
	HRGN hOldRgn;

	static void GenerateClip(HDC hDC, RECT rc, CUserCustomClip& clip);
	static void GenerateRoundClip(HDC hDC, RECT rc, RECT rcItem, int width, int height, CUserCustomClip& clip);
	static void UseOldClipBegin(HDC hDC, CUserCustomClip& clip);
	static void UseOldClipEnd(HDC hDC, CUserCustomClip& clip);
};

typedef struct tagTImageInfo
{
	HBITMAP hBitmap;
	LPBYTE pBits;
	int nX;
	int nY;
	bool bAlpha;
} TImageInfo;

//��ͼ����������GDI��ֱ�ӻ�ͼ�ĳ��ú����ķ�װ
class CDrawFun
{
public:
	CDrawFun();
	~CDrawFun();
	//����Դ�ļ��л�ȡHBITMAP bAlpha͸���� typeͼƬ����PNG BMP
	static HBITMAP LoadImageFromResource(bool & bAlpha, UINT nId, LPCTSTR type, HINSTANCE hInst);
	//����Դ�ļ��л�ȡHBITMAP typeͼƬ����PNG BMP
	static TImageInfo* LoadImageFromResource(UINT nId, LPCTSTR type, HINSTANCE hInst);
	//����Դ�ļ��л�ȡHBITMAP bAlpha͸���� strPath·��
	static HBITMAP LoadImagePath(bool & bAlpha, LPCTSTR strPath);
	//����Դ�ļ��л�ȡHBITMAP strPath·��
	static TImageInfo* LoadImagePath(LPCTSTR strPath);
	//�ͷ�ͼƬ��Դ
	static void FreeImage(TImageInfo* bitmap);
	//�ͷ�ͼƬ��Դ
	static void FreeImage(HBITMAP hBitmap);
	//��ͼ
	static void DrawImage(HDC hDC, HBITMAP hBitmap, const RECT & rc, bool bAlpha = false, UINT nAlpha = 255);
	//��ͼ
	static void DrawImage(HDC hDC, TImageInfo *pImageInfo, const RECT & rc);
	//Alpha��ɫ���
	void DrawAlpha(HDC hDC, const RECT & rc, const COLORREF clrMask, const int alp);
	//����
	static void DrawLine(HDC hDC, const RECT& rc, int nSize, COLORREF dwPenColor, int nStyle = PS_SOLID);
	//����
	static void DrawLine(HDC hDC, int x1, int y1, int x2, int y2, int nSize, COLORREF dwPenColor, int nStyle = PS_SOLID);
	//������
	static void DrawRect(HDC hDC, const RECT& rc, int nSize, COLORREF dwPenColor, int nStyle = PS_SOLID);
	//��Բ�Ǿ���
	static void DrawRoundRect(HDC hDC, const RECT& rc, int width, int height, int nSize, COLORREF dwPenColor, int nStyle = PS_SOLID);
	//DrawText
	static void DrawText(HDC hDC, RECT& rc, LPCTSTR pstrText, COLORREF dwTextColor, HFONT hFont, UINT uStyle = DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	//������
	static void FillRect(HDC hDC, COLORREF color, const RECT &rc);
	//���Բ�Ǿ���
	static void RoundRect(HDC hDC, COLORREF color, const RECT &rc, int nRoundWidth = 10, int nRoundHeight = 10);
	//��ȡ�ֵĿ��
	static SIZE GetTextSize(HDC hDC, LPCTSTR pstrText, HFONT hFont, UINT uStyle = DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	//32λλͼ
	static HBITMAP CreateARGB32Bitmap(HDC hDC, int cx, int cy, COLORREF** pBits);
	//��ȡICON��С
	static SIZE GetIconSize(HICON hIcon);
	//��ȡHBITMAP��С
	static SIZE GetBmpSize(HBITMAP hBitmap);
	//����С����ť
	static void DrawMinButton(HDC hDC, const RECT &rc, COLORREF dwPenColor, int nSize = 2);
	//����󻯰�ť
	static void DrawMaxButton(HDC hDC, const RECT &rc, COLORREF dwPenColor, int nSize = 2, bool bIsMax = false, COLORREF dwBkColor = RGB(0, 0, 255));
	//���رհ�ť
	static void DrawCloseButton(HDC hDC, const RECT &rc, COLORREF dwPenColor, int nSize = 2);
};

