#include "pch.h"
#include "CTriangleObj.h"

CTriangleObj::CTriangleObj()
{
	shapenum = 2;
}


CTriangleObj::CTriangleObj(CPoint StartPnt, CPoint EndPnt) : CShapeObj(StartPnt, EndPnt, 2) {}

CTriangleObj::CTriangleObj(CTriangleObj& T) : CShapeObj(T.StartPnt, T.EndPnt, 2) {}

CTriangleObj& CTriangleObj::operator=(CTriangleObj& T)
{
	StartPnt = T.StartPnt;
	EndPnt = T.EndPnt;
	return *this;
}

