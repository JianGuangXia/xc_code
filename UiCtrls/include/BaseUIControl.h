#pragma once

//�����ؼ����ûص� ��ɫ��ϵ�л�
class CUIControlSetCallback
{
public:
	CUIControlSetCallback();
	virtual ~CUIControlSetCallback();
	//ͼ�����
	COLORREF GetBackColor() const;
	void	 SetBackColor(COLORREF backColor);
	COLORREF GetHoverColor() const;
	void	 SetHoverColor(COLORREF hoverColor);
	COLORREF GetDisableColor() const;
	void	 SetDisableColor(COLORREF disableColor);
	HBITMAP  GetBackBitmap() const;
	void	 SetBackBitmap(HBITMAP hBitmap);
	SIZE	 GetBorderRound() const;
	void	 SetBorderRound(SIZE cxyRound);
	//�߿����
	COLORREF GetBorderColor() const;
	void     SetBorderColor(COLORREF borderColor);
	COLORREF GetFocusBorderColor() const;
	void     SetFocusBorderColor(COLORREF focusBorderColor);
	int		 GetBorderSize() const;
	void     SetBorderSize(int nBorderSize);
	int		 GetBorderStyle() const;
	void     SetBorderStyle(int nBorderStyle);
	//�ı����
	COLORREF GetTextColor() const;
	void     SetTextColor(COLORREF textColor);
	HFONT	 GetTextFont() const;
	void	 SetTextFont(HFONT hFont);
	UINT     GetTextStyle() const;
	void	 SetTextStyle(UINT textStyle);

private:
	COLORREF m_clBackColor;			//����ɫ
	COLORREF m_clHoverColor;		//����ɫ
	COLORREF m_clDisableColor;		//����ɫ
	COLORREF m_clBorderColor;		//�߿�ɫ
	COLORREF m_clFocusBorderColor;	//����߿�ɫ
	int		 m_nBorderSize;			//�߿��ϸ
	int		 m_nBorderStyle;		//�߿���PS_SOLID
	COLORREF m_clTextColor;			//����ɫ
	HFONT	 m_hFont;				//����
	UINT	 m_uTextStyle;		    //���������
	SIZE	 m_cxyBorderRound;		//Բ�Ǵ�С
	HBITMAP  m_hBackBitmap;			//����ͼƬ
};


class CBaseUIControl
{
public:
	CBaseUIControl();
	virtual ~CBaseUIControl();
	//ͼ�����
	COLORREF GetBackColor() const;
	void	 SetBackColor(COLORREF backColor);
	COLORREF GetHoverColor() const;
	void	 SetHoverColor(COLORREF hoverColor);
	COLORREF GetDisableColor() const;
	void	 SetDisableColor(COLORREF disableColor);
	HBITMAP  GetBackBitmap() const;
	void	 SetBackBitmap(HBITMAP hBitmap);
	SIZE	 GetBorderRound() const;
	void	 SetBorderRound(SIZE cxyRound);
	//�߿����
	COLORREF GetBorderColor() const;
	void     SetBorderColor(COLORREF borderColor);
	COLORREF GetFocusBorderColor() const;
	void     SetFocusBorderColor(COLORREF focusBorderColor);
	int		 GetBorderSize() const;
	void     SetBorderSize(int nBorderSize);
	int		 GetBorderStyle() const;
	void     SetBorderStyle(int nBorderStyle);
	//�ı����
	COLORREF GetTextColor() const;
	void     SetTextColor(COLORREF textColor);
	HFONT    GetDefaultFont() const;
	HFONT	 GetTextFont() const;
	void	 SetTextFont(HFONT hFont);
	UINT     GetTextStyle() const;
	void	 SetTextStyle(UINT textStyle);

	//�ص�
	CUIControlSetCallback *GetUIControlSetCallback() const;
	void				  SetUIControlSetCallback(CUIControlSetCallback *pUIControlSetCallback);

	virtual void DoPaint(HDC hDC, const RECT &rcClient, BOOL bHover = FALSE, BOOL bDisable = FALSE, BOOL bFocus = FALSE, BOOL bHasBorder = FALSE, LPCSTR strText = "");
	virtual void PaintBackColor(HDC hDC, const RECT &rcClient, BOOL bHover, BOOL bDisable);
	virtual void PaintBackImage(HDC hDC, const RECT &rcClient);
	virtual void PaintText(HDC hDC, const RECT & rcClient, LPCSTR strText);
	virtual void PaintBorder(HDC hDC, const RECT & rcClient, BOOL bFocus);

protected:
	COLORREF m_clBackColor;			//����ɫ
	COLORREF m_clHoverColor;		//����ɫ
	COLORREF m_clDisableColor;		//����ɫ
	COLORREF m_clBorderColor;		//�߿�ɫ
	COLORREF m_clFocusBorderColor;	//����߿�ɫ
	int		 m_nBorderSize;			//�߿��ϸ
	int		 m_nBorderStyle;		//�߿���PS_SOLID
	COLORREF m_clTextColor;			//����ɫ
	HFONT	 m_hDefaultFont;		//Ĭ������
	HFONT	 m_hFont;				//����
	UINT	 m_uTextStyle;		    //���������
	SIZE	 m_cxyBorderRound;		//Բ�Ǵ�С
	HBITMAP  m_hBackBitmap;			//����ͼƬ
	CUIControlSetCallback	*m_pUIControlSetCallback;  //ɫϵ���ûص�
};

