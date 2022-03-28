#include "pch.h"
#include "CShapeObj.h"

CShapeObj::CShapeObj()
{

}


CShapeObj::CShapeObj(CPoint SP, CPoint EP, int sn)
{
	StartPnt = SP;
	EndPnt = EP;
	shapenum = sn;

}

CShapeObj::CShapeObj(CShapeObj &s)
{
	StartPnt = s.StartPnt;
	EndPnt = s.EndPnt;
	shapenum = s.shapenum;

}

CShapeObj& CShapeObj::operator=(CShapeObj &s)
{
	StartPnt = s.StartPnt;
	EndPnt = s.EndPnt;
	return *this;
}

int CShapeObj::GetShapeNum()
{
	return shapenum;
}

void CShapeObj::SetPoint(CPoint SPnt, CPoint EPnt)
{
	StartPnt = SPnt;
	EndPnt = EPnt;
}
