#pragma once
#include "CGraphicObj.h"
class CShapeObj : public CGraphicObj
{
protected:
	CPoint StartPnt, EndPnt;
	int shapenum;
	friend class CPaintView;
public:
	CShapeObj();
	CShapeObj(CPoint SP, CPoint EP, int sn);
	CShapeObj(CShapeObj &s);
	CShapeObj& operator=(CShapeObj &s);
	virtual void draw(CDC &aDC, COLORREF color, COLORREF fcolor, int width, int linetype, BOOL Filled = true) = 0;
	int GetShapeNum();
	void SetPoint(CPoint SPnt, CPoint EPnt);

};



