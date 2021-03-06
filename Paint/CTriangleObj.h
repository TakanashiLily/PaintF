#pragma once
#include "CShapeObj.h"
class CTriangleObj : public CShapeObj
{
public:
	CTriangleObj();
	CTriangleObj(CPoint StartPnt, CPoint EndPnt);
	CTriangleObj(CTriangleObj &T);
	CTriangleObj& operator=(CTriangleObj &T);
	void draw(CDC& aDC, COLORREF color, COLORREF fcolor, int width, int linetype, BOOL Filled = true)
	{
		CRect rect(StartPnt, EndPnt);
		linetype = linetype;
		if (linetype == 1)
		{
			CPen pen(PS_SOLID, width, color);
			CPen* oldPen = aDC.SelectObject(&pen);

			CBrush bsh(fcolor);
			CBrush* oldbsh = aDC.SelectObject(&bsh);

			CPoint pt[4];
			if (StartPnt.y < EndPnt.y)
			{
				//起點
				pt[0].x = (StartPnt.x + EndPnt.x) / 2;
				pt[0].y = StartPnt.y;

				//頂點1
				pt[1].x = EndPnt.x;
				pt[1].y = EndPnt.y;

				//頂點2
				pt[2].x = StartPnt.x;
				pt[2].y = EndPnt.y;

				//回起點
				pt[3].x = (StartPnt.x + EndPnt.x) / 2;
				pt[3].y = StartPnt.y;

				aDC.Polygon(pt, 3);
			}

			else if (StartPnt.y > EndPnt.y)
			{
				//起點
				pt[0].x = StartPnt.x;
				pt[0].y = StartPnt.y;

				//頂點1
				pt[1].x = EndPnt.x;
				pt[1].y = StartPnt.y;

				//頂點2
				pt[2].x = (StartPnt.x + EndPnt.x) / 2;
				pt[2].y = EndPnt.y;

				//回起點
				pt[3].x = StartPnt.x;
				pt[3].y = StartPnt.y;

				aDC.Polygon(pt, 3);
			}
			aDC.SelectObject(oldPen);
		}

		else if (linetype == 2)
		{
			CPen pen(PS_DASH, width, color);
			CPen* oldPen = aDC.SelectObject(&pen);

			CBrush bsh(fcolor);
			CBrush* oldbsh = aDC.SelectObject(&bsh);

			CPoint pt[4];
			if (StartPnt.y < EndPnt.y)
			{
				//起點
				pt[0].x = (StartPnt.x + EndPnt.x) / 2;
				pt[0].y = StartPnt.y;

				//頂點1
				pt[1].x = EndPnt.x;
				pt[1].y = EndPnt.y;

				//頂點2
				pt[2].x = StartPnt.x;
				pt[2].y = EndPnt.y;

				//回起點
				pt[3].x = (StartPnt.x + EndPnt.x) / 2;
				pt[3].y = StartPnt.y;

				aDC.Polygon(pt, 3);
			}

			else if (StartPnt.y > EndPnt.y)
			{
				//起點
				pt[0].x = StartPnt.x;
				pt[0].y = StartPnt.y;

				//頂點1
				pt[1].x = EndPnt.x;
				pt[1].y = StartPnt.y;

				//頂點2
				pt[2].x = (StartPnt.x + EndPnt.x) / 2;
				pt[2].y = EndPnt.y;

				//回起點
				pt[3].x = StartPnt.x;
				pt[3].y = StartPnt.y;

				aDC.Polygon(pt, 3);
			}
			aDC.SelectObject(oldPen);
		}

		else if (linetype == 3)
		{
		CPen pen(PS_DOT, width, color);
		CPen* oldPen = aDC.SelectObject(&pen);

		CBrush bsh(fcolor);
		CBrush* oldbsh = aDC.SelectObject(&bsh);

		CPoint pt[4];
		if (StartPnt.y < EndPnt.y)
		{
			//起點
			pt[0].x = (StartPnt.x + EndPnt.x) / 2;
			pt[0].y = StartPnt.y;

			//頂點1
			pt[1].x = EndPnt.x;
			pt[1].y = EndPnt.y;

			//頂點2
			pt[2].x = StartPnt.x;
			pt[2].y = EndPnt.y;

			//回起點
			pt[3].x = (StartPnt.x + EndPnt.x) / 2;
			pt[3].y = StartPnt.y;

			aDC.Polygon(pt, 3);
		}

		else if (StartPnt.y > EndPnt.y)
		{
			//起點
			pt[0].x = StartPnt.x;
			pt[0].y = StartPnt.y;

			//頂點1
			pt[1].x = EndPnt.x;
			pt[1].y = StartPnt.y;

			//頂點2
			pt[2].x = (StartPnt.x + EndPnt.x) / 2;
			pt[2].y = EndPnt.y;

			//回起點
			pt[3].x = StartPnt.x;
			pt[3].y = StartPnt.y;

			aDC.Polygon(pt, 3);
		}
		aDC.SelectObject(oldPen);
		}

	}
};

