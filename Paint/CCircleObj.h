#pragma once
#include "CShapeObj.h"
class CCircleObj : public CShapeObj
{
public:
	CCircleObj();
	CCircleObj(CPoint StartPnt, CPoint EndPnt);
	CCircleObj(CCircleObj &C);
	CCircleObj& operator=(CCircleObj &C);

	void draw(CDC& aDC, COLORREF color, COLORREF fcolor, int width, int linetype, BOOL Filled = true)
	{
		CRect rect(StartPnt, EndPnt);
		if (linetype == 1)
		{
			CPen pen(PS_SOLID, width, color);
			CPen* oldPen = aDC.SelectObject(&pen);
			CBrush bsh(fcolor);
			CBrush* oldbsh = aDC.SelectObject(&bsh);
			//aDC.SelectStockObject(NULL_BRUSH);
			aDC.Ellipse(rect);
			aDC.SelectObject(oldPen);
		}
		else if (linetype == 2)
		{
				CPen pen(PS_DASH, width, color);
				CPen* oldPen = aDC.SelectObject(&pen);
				CBrush bsh(fcolor);
				CBrush* oldbsh = aDC.SelectObject(&bsh);
				//aDC.SelectStockObject(NULL_BRUSH);
				aDC.Ellipse(rect);
				aDC.SelectObject(oldPen);
		}
		else if (linetype == 3)
		{
			CPen pen(PS_DOT, width, color);
			CPen* oldPen = aDC.SelectObject(&pen);
			CBrush bsh(fcolor);
			CBrush* oldbsh = aDC.SelectObject(&bsh);
			//aDC.SelectStockObject(NULL_BRUSH);
			aDC.Ellipse(rect);
			aDC.SelectObject(oldPen);
		}
	}
};




