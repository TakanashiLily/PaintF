#include "pch.h"
#include "CGraphicObj.h"

IMPLEMENT_SERIAL(CGraphicObj, CObject, 1)

CGraphicObj::CGraphicObj()
{

}

CGraphicObj::CGraphicObj(int sn, BOOL fl, COLORREF FC, COLORREF LC, int wh, int lt, CPoint SP, CPoint EP)
{
	shapenum = sn;
	fill = fl;
	FillColor = FC;
	LineColor = LC;
	width = wh;
	linetype = lt;
	StartPnt = SP;
	EndPnt = EP;
}

CGraphicObj::CGraphicObj(CGraphicObj &g)
{
	shapenum = g.shapenum;
	fill = g.fill;
	FillColor = g.FillColor;
	LineColor = g.LineColor;
	width = g.width;
	linetype = g.linetype;
	StartPnt = g.StartPnt;
	EndPnt = g.EndPnt;
}

CGraphicObj& CGraphicObj::operator=(CGraphicObj &g)
{
	shapenum = g.shapenum;
	fill = g.fill;
	FillColor = g.FillColor;
	LineColor = g.LineColor;
	width = g.width;
	linetype = g.linetype;
	StartPnt = g.StartPnt;
	EndPnt = g.EndPnt;

	return *this;
}

void CGraphicObj::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << shapenum << fill << FillColor << LineColor
			<< width << linetype << StartPnt << EndPnt;
	}
	else
	{
		ar >> shapenum >> fill >> FillColor >> LineColor
			>> width >> linetype >> StartPnt >> EndPnt;
	}
}