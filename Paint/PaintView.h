
// PaintView.h: CPaintView 類別的介面
//
#include "CShapeObj.h"
#include "CCircleObj.h"
#include "CTriangleObj.h"
#include "CTextObj.h"
#include "PaintDoc.h"
#pragma once


class CPaintView : public CScrollView
{
protected: // 僅從序列化建立
	CPaintView() noexcept;
	DECLARE_DYNCREATE(CPaintView)
	friend class PROPPAGE_BORDER;

private:
	COLORREF lcolor, fcolor;
	CTextObj Ctxt= CTextObj(_T(""), _T("Comic Sans MS"), RGB(0, 0, 0), 32, 0, 0, 0, 0, 0);
	CTextObj* atxt;
	CTextObj* rdtxt;
	CShapeObj* aShape;
	CShapeObj* rdShape;
	int width, linetype;
	HCURSOR hcursor;
	int mousemode;
	int record, recordT;
	BOOL press = false;
	BOOL pressR = false;
	BOOL pressT = false;
	CPoint mousepoint;
	BOOL checked = false, mchecked = false;
	int  move = 0;
	int size = 5000;
	CEdit* pEdit;
	BOOL isEdit=false;
	CString txt, CLtype, context;
	CString fonttype = _T("Comic Sans MS");
	BOOL Tmove = false;
	BOOL italic = false, underline = false, bold = false;
	BOOL Tcho = false;
	BOOL choose;
	int Tbold = false;
	CPoint StartPnt;
	CPoint EndPnt;
	BOOL drag = false;
	BOOL TextChoose = false;
	int TextMove = 0;
	BOOL TextCheck = false;
	CPoint TStartPnt;
	CPoint TEndPnt;
// 屬性
public:
	CPaintDoc* GetDocument() const;
	void LogicalCoor(CPoint *point);
	void PhysicalCoor(CPoint* point);
	CString SLineType(int ln);
	int TLineType(CString ln);

	CBitmap bmpBk, bmpBl, bmpRd, bmpLn, bmpDt, bmpDtln;
	int LN, DTLN, DT;
	
// 作業
public:

// 覆寫
public:
	virtual void OnDraw(CDC* pDC);  // 覆寫以描繪此檢視
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 程式碼實作
public:
	virtual ~CPaintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 產生的訊息對應函式
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPolygonTriangle();
	afx_msg void OnPolygonEllipse();
	afx_msg void OnLButtonDown(UINT, CPoint point);
	afx_msg void OnLButtonUp(UINT, CPoint point);
	afx_msg void OnMouseMove(UINT, CPoint point);
	afx_msg void OnUpdateCircle(CCmdUI *aCmdUI);
	afx_msg void OnUpdateTriangle(CCmdUI* aCmdUI);
	afx_msg void OnUpdateRed(CCmdUI* aCmdUI);
	afx_msg void OnUpdateBlue(CCmdUI* aCmdUI);
	afx_msg void OnUpdateBlack(CCmdUI* aCmdUI);
	afx_msg void OnBlack();
	afx_msg void OnBlue();
	afx_msg void OnRed();
	afx_msg void OnNormal();
	afx_msg void OnUpdateNormal(CCmdUI* aCmdUI);
	afx_msg void OnMove();
	afx_msg void OnUpdateMove(CCmdUI* aCmdUI);
	
	afx_msg void OnRButtonDown(UINT,CPoint point);
	afx_msg void OnLButtonDblClk(UINT, CPoint point);
	//afx_msg void OnRButtonUp(UINT, CPoint point);
	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBlackf();
	afx_msg void OnUpdateBlackf(CCmdUI* pCmdUI);
	afx_msg void OnBluef();
	afx_msg void OnUpdateBluef(CCmdUI* pCmdUI);
	afx_msg void OnRedf();
	afx_msg void OnUpdateRedf(CCmdUI* pCmdUI);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnZoomin();
	afx_msg void OnZoomout();
	afx_msg void OnText();
	afx_msg void OnUpdateText(CCmdUI* aCmdUI);
	//afx_msg void OnBnClickedButton();
	//afx_msg void OnUserdefine();
	afx_msg void SetLColor(COLORREF LCOLOR);
	afx_msg COLORREF GetLcolor();
	afx_msg void SetFColor(COLORREF FCOLOR);
	afx_msg COLORREF GetFcolor();

	afx_msg void OnProperty();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLn();
	afx_msg void OnDtln();
	afx_msg void OnDt();
	afx_msg void OnUpdateLn(CCmdUI* aCmdUI);
	afx_msg void OnUpdateDtln(CCmdUI* aCmdUI);
	afx_msg void OnUpdateDt(CCmdUI* aCmdUI);
	afx_msg int GetLtype();
	afx_msg void SetLtype(int Lt);
	afx_msg CString GetFtype();
	afx_msg void SetFtype(CString ft);
	afx_msg BOOL GetBold();
	afx_msg void SetBold(int bd);
	afx_msg BOOL GetItalic();
	afx_msg void SetItalic(BOOL it);
	afx_msg BOOL GetUnderline();
	afx_msg void SetUnderline(BOOL ul);
};


#ifndef _DEBUG  // 對 PaintView.cpp 中的版本進行偵錯
inline CPaintDoc* CPaintView::GetDocument() const
   { return reinterpret_cast<CPaintDoc*>(m_pDocument); }
#endif

