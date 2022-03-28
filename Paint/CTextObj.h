#pragma once
#include "CGraphicObj.h"
class CTextObj : public CObject
{
protected:
	//CFont font;
	CString font, txt;
	COLORREF tcolor;
	int tsize;
	BOOL bold = false, italic = false, underline = false;
	CPoint StartPnt, EndPnt;
	friend class CPaintView;
public:
	CTextObj();
	CTextObj(CString txt, CString font, COLORREF tcolor, int tsize, BOOL bold, BOOL italic, BOOL underline, CPoint StartPnt, CPoint EndPnt);
	CTextObj(CTextObj& t);
	CTextObj& operator=(CTextObj& t);
	void Serialize(CArchive& ar);
	void SetPoint(CPoint SPnt, CPoint EPnt);
};

































	//CTextObj();
	/*
	CTextObj(CPoint SP, CPoint EP);
	CTextObj(CTextObj& x);
	CTextObj& operator=(CTextObj& x);
	void drawA(CDC& aDC, CFont font, COLORREF tcolor, int tsize, BOOL bold, BOOL italic, BOOL underline)
	{
			CRect rect(StartPnt.x, StartPnt.y, StartPnt.x + 500, StartPnt.y + 80);
			CPen pen(PS_DASH, 1, RGB(0, 0, 0));
			CPen* oldPen = aDC.SelectObject(&pen);
			
			//aDC.SelectStockObject(NULL_BRUSH);
			aDC.Rectangle(rect);
			aDC.SelectObject(oldPen);
	}
	void drawC(CDC& aDC, CFont font, COLORREF tcolor, int tsize, BOOL bold, BOOL italic, BOOL underline)
	{
		CRect rect(StartPnt, EndPnt);
		CPen pen(PS_DASH, 1, RGB(0, 0, 0));
		CPen* oldPen = aDC.SelectObject(&pen);

		//aDC.SelectStockObject(NULL_BRUSH);
		aDC.Rectangle(rect);
		aDC.SelectObject(oldPen);
	}
	*/


