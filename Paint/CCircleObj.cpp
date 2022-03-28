#include "pch.h"
#include "CCircleObj.h"

CCircleObj::CCircleObj()
{
	shapenum = 1;
}


CCircleObj::CCircleObj(CPoint StartPnt, CPoint EndPnt) : CShapeObj(StartPnt, EndPnt, 1){}

CCircleObj::CCircleObj(CCircleObj &C) : CShapeObj(C.StartPnt, C.EndPnt, 1){}

CCircleObj& CCircleObj::operator=(CCircleObj &C)
{
	StartPnt = C.StartPnt;
	EndPnt = C.EndPnt;
	return *this;
}

