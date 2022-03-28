#pragma once

class CGraphicObj : public CObject
{
public:
	DECLARE_SERIAL(CGraphicObj)
	int shapenum;
	BOOL fill;
	COLORREF FillColor, LineColor;
	int width, linetype;
	CPoint StartPnt, EndPnt;

public:
	CGraphicObj();
	CGraphicObj(int sn, BOOL fl, COLORREF FC, COLORREF LC, int wh, int lt, CPoint SP, CPoint EP);
	CGraphicObj(CGraphicObj &g);
	void Serialize(CArchive &ar);
	CGraphicObj& operator=(CGraphicObj &g);
};

