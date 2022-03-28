#include "pch.h"
#include "CTextObj.h"



CTextObj::CTextObj()
{

}

CTextObj::CTextObj(CString tx, CString ft,COLORREF tc,int ts,BOOL bo , BOOL it, BOOL un,CPoint SP, CPoint EP)
{
	txt = tx;
	font = ft;
	tcolor = tc;
	tsize = ts;
	bold = bo;
	italic = it;
	underline = un;
	StartPnt = SP;
	EndPnt = EP;
}

CTextObj::CTextObj(CTextObj& t)
{
	txt = t.txt;
	font = t.font;
	tcolor = t.tcolor;
	tsize = t.tsize;
	bold = t.bold;
	italic = t.italic;
	underline = t.underline;
	StartPnt = t.StartPnt;
	EndPnt = t.EndPnt;
}



CTextObj& CTextObj::operator=(CTextObj& t)
{
	txt = t.txt;
	font = t.font;
	tcolor = t.tcolor;
	tsize = t.tsize;
	bold = t.bold;
	italic = t.italic;
	underline = t.underline;
	StartPnt = t.StartPnt;
	EndPnt = t.EndPnt;

	return *this;
}


void CTextObj::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << txt << font << tcolor << tsize << bold
			<< italic << underline << StartPnt << EndPnt;
	}
	else
	{
		ar >> txt >> font >> tcolor >> tsize >> bold
			>> italic >> underline >> StartPnt >> EndPnt;
	}
}

void CTextObj::SetPoint(CPoint SPnt, CPoint EPnt)
{
	StartPnt = SPnt;
	EndPnt = EPnt;
}



















/*
CTextObj::CTextObj()
{
	
}


CTextObj::CTextObj(CPoint StartPnt, CPoint EndPnt) : CGraphicObj(shapenum, false, FillColor, LineColor, width, linetype, StartPnt, EndPnt) {}

CTextObj::CTextObj(CTextObj& x) : CGraphicObj(x.shapenum, false, FillColor, LineColor, width, linetype, x.StartPnt, x.EndPnt) {}

CTextObj& CTextObj::operator=(CTextObj& x)
{
	shapenum = x.shapenum;
	StartPnt = x.StartPnt;
	EndPnt = x.EndPnt;
	return *this;
}
*/