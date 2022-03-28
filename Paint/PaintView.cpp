
// PaintView.cpp: CPaintView 類別的實作
//

#include "pch.h"
#include "framework.h"
#include "winuser.h"
// SHARED_HANDLERS 可以定義在實作預覽、縮圖和搜尋篩選條件處理常式的
// ATL 專案中，並允許與該專案共用文件程式碼。
#ifndef SHARED_HANDLERS
#include "Paint.h"
#endif

#include "PaintDoc.h"
#include "PaintView.h"
#include "MainFrm.h"
#include "PROPPAGE_BORDER.h"
#include "PROPPAGE_COLOR.h"
#include "PROPPAGE_FONT.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPaintView

IMPLEMENT_DYNCREATE(CPaintView, CScrollView)

BEGIN_MESSAGE_MAP(CPaintView, CScrollView)
	// 標準列印命令
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SYSKEYDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_CONTEXTMENU()
	ON_WM_LBUTTONDBLCLK()

	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_POLYGON_TRIANGLE, &CPaintView::OnPolygonTriangle)
	ON_COMMAND(ID_POLYGON_ELLIPSE, &CPaintView::OnPolygonEllipse)
	ON_COMMAND(IDM_Black, &CPaintView::OnBlack)
	ON_COMMAND(IDM_Blue, &CPaintView::OnBlue)
	ON_COMMAND(IDM_Red, &CPaintView::OnRed)
	ON_COMMAND(ID_CURNORMAL, &CPaintView::OnNormal)
	ON_UPDATE_COMMAND_UI(ID_CURNORMAL, &CPaintView::OnUpdateNormal)
	ON_UPDATE_COMMAND_UI(ID_POLYGON_TRIANGLE, &CPaintView::OnUpdateTriangle)
	ON_UPDATE_COMMAND_UI(ID_POLYGON_ELLIPSE, &CPaintView::OnUpdateCircle)
	ON_UPDATE_COMMAND_UI(IDM_Black, &CPaintView::OnUpdateBlack)
	ON_UPDATE_COMMAND_UI(IDM_Blue, &CPaintView::OnUpdateBlue)
	ON_UPDATE_COMMAND_UI(IDM_Red, &CPaintView::OnUpdateRed)
	ON_COMMAND(ID_MOVE, &CPaintView::OnMove)
	ON_UPDATE_COMMAND_UI(ID_MOVE, &CPaintView::OnUpdateMove)
	ON_COMMAND(IDM_BlackF, &CPaintView::OnBlackf)
	ON_UPDATE_COMMAND_UI(IDM_BlackF, &CPaintView::OnUpdateBlackf)
	ON_COMMAND(IDM_BlueF, &CPaintView::OnBluef)
	ON_UPDATE_COMMAND_UI(IDM_BlueF, &CPaintView::OnUpdateBluef)
	ON_COMMAND(IDM_RedF, &CPaintView::OnRedf)
	ON_UPDATE_COMMAND_UI(IDM_RedF, &CPaintView::OnUpdateRedf)
	ON_COMMAND(ID_ZOOMIN, &CPaintView::OnZoomin)
	ON_COMMAND(ID_ZOOMOUT, &CPaintView::OnZoomout)
	ON_COMMAND(ID_TEXT, &CPaintView::OnText)
	ON_UPDATE_COMMAND_UI(ID_TEXT, &CPaintView::OnUpdateText)
	//ON_COMMAND(IDC_FORECOLOR, &CPaintView::OnUserdefine)

	ON_COMMAND(ID_PROPERTY, &CPaintView::OnProperty)

	ON_COMMAND(ID_LINETYPE_LINE, &CPaintView::OnLn)
	ON_COMMAND(ID_LINETYPE_DASHLINE, &CPaintView::OnDtln)
	ON_COMMAND(ID_LINETYPE_DOTLINE, &CPaintView::OnDt)

	ON_UPDATE_COMMAND_UI(ID_LINETYPE_LINE, &CPaintView::OnUpdateLn)
	ON_UPDATE_COMMAND_UI(ID_LINETYPE_DASHLINE, &CPaintView::OnUpdateDtln)
	ON_UPDATE_COMMAND_UI(ID_LINETYPE_DOTLINE, &CPaintView::OnUpdateDt)
	

END_MESSAGE_MAP()

// CPaintView 建構/解構

void CPaintView::SetLColor(COLORREF LCOLOR)
{
	lcolor = LCOLOR;
}

COLORREF CPaintView::GetLcolor()
{
	return lcolor;
}

COLORREF CPaintView::GetFcolor()
{
	return fcolor;
}

int CPaintView::GetLtype()
{
	return linetype;
}

CString CPaintView::GetFtype()
{
	return fonttype;
}

BOOL CPaintView::GetBold()
{
	return bold;
}
/*
void CPaintView::SetBold(int bd)
{
	bold = bd;
}
*/
BOOL CPaintView::GetItalic()
{
	return italic;
}
/*
void CPaintView::SetItalic(BOOL it)
{
	italic = it;
}
*/
BOOL CPaintView::GetUnderline()
{
	return underline;
}
/*
void CPaintView::SetUnderline(BOOL ul)
{
	underline = ul;
}
*/
CString CPaintView::SLineType(int ln)
{
	if (ln == 1)
	{
		return _T("----------------");
	}
	else if (ln == 2)
	{
		return _T("- - - - - - - - - - - -");
	}

	else if (ln == 3)
	{
		return _T("-   -   -   -   -   -   -   -   -");
	}
}

int CPaintView::TLineType(CString ln)
{
	if (ln == _T("----------------"))
	{
		return 1;
	}
	else if (ln == _T("- - - - - - - - - - - -"))
	{
		return 2;
	}

	else if (ln == _T("-   -   -   -   -   -   -   -   -"))
	{
		return 3;
	}
}



CPaintView::CPaintView() noexcept
{
	lcolor = RGB(0, 0, 0);
	aShape = new CCircleObj;
	atxt = new CTextObj;
	fcolor = RGB(255, 0, 0);
	width = 1;
	linetype = 1;
	mousemode = 0;
	// TODO: 在此加入建構程式碼
	bmpBk.LoadBitmap(IDB_BLACK);
	bmpBl.LoadBitmap(IDB_BLUE);
	bmpRd.LoadBitmap(IDB_RED);
	bmpLn.LoadBitmap(IDB_LN);
	bmpDtln.LoadBitmap(IDB_DTLN);
	bmpDt.LoadBitmap(IDB_DT);
	fonttype = _T("Comic Sans MS");
	


}

CPaintView::~CPaintView()
{
}

BOOL CPaintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此經由修改 CREATESTRUCT cs 
	// 達到修改視窗類別或樣式的目的

	return CView::PreCreateWindow(cs);
}

// CPaintView 繪圖

void CPaintView::OnDraw(CDC* aDC)
{
	CPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	int num = pDoc->GetSize();
	int numT = pDoc->GetSizeT();
	CView::OnDraw(aDC);
	int i;
	for (i = 0; i < num; i++)
	{
		CGraphicObj* object = &(pDoc->GetObject(i));
		if (object->shapenum == 1)
		{
			rdShape = new CCircleObj;
			rdShape->SetPoint(object->StartPnt, object->EndPnt);
			rdShape->draw((*aDC), object->LineColor, object->FillColor, object->width, object->linetype);
			if (i == num - 1)
			{
				CPoint startPoint = object->StartPnt;
				CPoint endPoint = object->EndPnt;
				PhysicalCoor(&startPoint);
				PhysicalCoor(&endPoint);
				CClientDC aDC(this);
				if (choose == true)
				{
				CRectTracker CRT;
				CRT.m_rect.SetRect(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
				CRT.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeOutside;
				CRT.m_nHandleSize = 6;
				CRT.GetHandleMask();
				CRT.Draw(&aDC);
				}
			}

			delete rdShape;
		}
		else if (object->shapenum == 2)
		{
			rdShape = new CTriangleObj;
			rdShape->SetPoint(object->StartPnt, object->EndPnt);
			rdShape->draw((*aDC), object->LineColor, object->FillColor, object->width, object->linetype);
			if (i == num - 1)
			{
				CPoint startPoint = object->StartPnt;
				CPoint endPoint = object->EndPnt;
				PhysicalCoor(&startPoint);
				PhysicalCoor(&endPoint);
				CClientDC aDC(this);
				if (choose == true)
				{
					CRectTracker CRT;
					CRT.m_rect.SetRect(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
					CRT.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeOutside;
					CRT.m_nHandleSize = 6;
					CRT.GetHandleMask();
					CRT.Draw(&aDC);
				}
			}
			delete rdShape;
		}
	}
	
	for (i = 0; i < numT; i++)
	{
		
		CTextObj* Tobject = &(pDoc->GetObjectT(i));
		rdtxt = new CTextObj;
		rdtxt->SetPoint(Tobject->StartPnt, Tobject->EndPnt);
		PhysicalCoor(&rdtxt->StartPnt);
		PhysicalCoor(&rdtxt->EndPnt);
		CRect crt(rdtxt->StartPnt.x, rdtxt->StartPnt.y, rdtxt->EndPnt.x, rdtxt->EndPnt.y );
		rdtxt->txt = Tobject->txt;
		CClientDC dc(this);
		CFont font;
		font.CreateFont(
			32,                       // nHeight
			0,                        // nWidth
			0,                        // nEscapement
			0,                        // nOrientation
			Tobject->bold,                // nWeight
			Tobject->italic,                    // bItalic
			Tobject->underline,                    // bUnderline
			0,                        // cStrikeOut
			ANSI_CHARSET,             // nCharSet
			OUT_DEFAULT_PRECIS,       // nOutPrecision
			CLIP_DEFAULT_PRECIS,      // nClipPrecision
			DEFAULT_QUALITY,          // nQuality
			DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
			Tobject->font);

		CGdiObject* pOldFont = dc.SelectObject(&font);

		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(Tobject->tcolor);
		dc.DrawText(Tobject->txt, crt, DT_WORDBREAK | DT_EDITCONTROL | DT_TOP | DT_LEFT);
		dc.SelectObject(pOldFont);
		if (TextChoose == true && i == numT - 1)
		{
			CPen pen(PS_DOT, 1, RGB(0, 0, 0));
			CPen* oldPen = dc.SelectObject(&pen);
			dc.SelectStockObject(NULL_BRUSH);
			dc.Rectangle(crt);
			dc.SelectObject(oldPen);
		}
		/*
		CTextObj* Tobject = &(pDoc->GetObjectT(i));
		rdtxt = new CTextObj;
		rdtxt->SetPoint(Tobject->StartPnt, Tobject->EndPnt);

		PhysicalCoor(&rdtxt->StartPnt);
		PhysicalCoor(&rdtxt->EndPnt);
		CRect crt(Tobject->StartPnt.x, Tobject->StartPnt.y, Tobject->StartPnt.x + 500, Tobject->StartPnt.y + 80);
		rdtxt->txt = Tobject->txt;
		CClientDC dc(this);
		CFont font;
		font.CreateFont(
			32,                       // nHeight
			0,                        // nWidth
			0,                        // nEscapement
			0,                        // nOrientation
			Tobject->bold,                // nWeight
			Tobject->italic,                    // bItalic
			Tobject->underline,                    // bUnderline
			0,                        // cStrikeOut
			ANSI_CHARSET,             // nCharSet
			OUT_DEFAULT_PRECIS,       // nOutPrecision
			CLIP_DEFAULT_PRECIS,      // nClipPrecision
			DEFAULT_QUALITY,          // nQuality
			DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
			Tobject->font);

		CGdiObject* pOldFont = dc.SelectObject(&font);

		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(Tobject->tcolor);
		dc.DrawText(Tobject->txt, crt, DT_WORDBREAK | DT_EDITCONTROL | DT_TOP | DT_LEFT);
		dc.SelectObject(pOldFont);
			*/
			/*
			if (i == num - 1)
			{
				CPoint startPoint = Tobject->StartPnt;
				CPoint endPoint = Tobject->EndPnt;
				PhysicalCoor(&startPoint);
				PhysicalCoor(&endPoint);
				
				CClientDC aDC(this);				
				CRectTracker CRT;
				CRT.m_rect.SetRect(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
				CRT.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeOutside;
				CRT.m_nHandleSize = 6;
				CRT.GetHandleMask();
				CRT.Draw(&aDC);
				
			}
			*/
			delete rdtxt;
	}
		

	// TODO: 在此加入原生資料的描繪程式碼
}


// CPaintView 列印

BOOL CPaintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 預設的準備列印程式碼
	return DoPreparePrinting(pInfo);
}

void CPaintView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 加入列印前額外的初始設定
}

void CPaintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 加入列印後的清除程式碼
}


// CPaintView 診斷

#ifdef _DEBUG
void CPaintView::AssertValid() const
{
	CView::AssertValid();
}

void CPaintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPaintDoc* CPaintView::GetDocument() const // 內嵌非偵錯版本
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPaintDoc)));
	return (CPaintDoc*)m_pDocument;
}
#endif //_DEBUG


// CPaintView 訊息處理常式

void CPaintView::OnNormal()
{
	mousemode = 0;
	CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
	int MAX = pDoc->GetSize();
	int MAXT = pDoc->GetSizeT();
	if (MAX > 0  || MAXT > 0)
	{
		if (MAX > 0)
		{
		choose = false;
		CGraphicObj object = pDoc->GetObject(MAX - 1);
		pDoc->RemoveAt(MAX - 1);
		pDoc->AddObject(object);

		PhysicalCoor(&object.StartPnt);
		PhysicalCoor(&object.EndPnt);
		CRect rect(object.StartPnt, object.EndPnt);

		rect.NormalizeRect();
		rect.InflateRect(size, size);

		InvalidateRect(&rect);
		}
	}
	if (isEdit == true)
	{
		CRect crt(atxt->StartPnt.x, atxt->StartPnt.y, atxt->EndPnt.x , atxt->EndPnt.y );
		pEdit->GetWindowText(txt);
		atxt->txt = txt;
		delete(pEdit);

		CClientDC dc(this);
		/*
		//虛框
		CPen pen(PS_DOT, 1, RGB(0, 0, 0));
		CPen* oldPen = dc.SelectObject(&pen);
		dc.SelectStockObject(NULL_BRUSH);
		dc.Rectangle(crt);
		dc.SelectObject(oldPen);
		*/
		CFont font;

		//font.CreatePointFont(Ctxt.tsize, fontS);

		font.CreateFont(
			32,                       // nHeight
			0,                        // nWidth
			0,                        // nEscapement
			0,                        // nOrientation
			Tbold,                // nWeight
			italic,                    // bItalic
			underline,                    // bUnderline
			0,                        // cStrikeOut
			ANSI_CHARSET,             // nCharSet
			OUT_DEFAULT_PRECIS,       // nOutPrecision
			CLIP_DEFAULT_PRECIS,      // nClipPrecision
			DEFAULT_QUALITY,          // nQuality
			DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
			fonttype);

		CGdiObject* pOldFont = dc.SelectObject(&font);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(Ctxt.tcolor);
		Ctxt.StartPnt = atxt->StartPnt;
		Ctxt.EndPnt.x = atxt->EndPnt.x ;
		Ctxt.EndPnt.y = atxt->EndPnt.y ;
		CRect tmct(Ctxt.StartPnt, Ctxt.EndPnt);
		dc.DrawText(txt, tmct, DT_WORDBREAK | DT_EDITCONTROL | DT_TOP | DT_LEFT);
		dc.SelectObject(pOldFont);

		isEdit = false;

		CPaintDoc* pDoc = (CPaintDoc*)GetDocument();

		CTextObj object(atxt->txt, fonttype, Ctxt.tcolor, 32, Tbold, italic, underline, atxt->StartPnt, Ctxt.EndPnt);
		pDoc->AddObjectT(object);
		//PhysicalCoor(&atxt->StartPnt);
	}
}

void CPaintView::OnPolygonEllipse()
{
	mousemode = 1;
	aShape = new CCircleObj;
	((CMainFrame*)GetParentFrame())->m_wndStatusBar.SetPaneText(6, _T("Ellipse"));
	if (isEdit == true)
	{
		CRect crt(atxt->StartPnt.x, atxt->StartPnt.y, atxt->EndPnt.x, atxt->EndPnt.y );
		pEdit->GetWindowText(txt);
		atxt->txt = txt;
		delete(pEdit);

		CClientDC dc(this);
		/*
		//虛框
		CPen pen(PS_DOT, 1, RGB(0, 0, 0));
		CPen* oldPen = dc.SelectObject(&pen);
		dc.SelectStockObject(NULL_BRUSH);
		dc.Rectangle(crt);
		dc.SelectObject(oldPen);
		*/
		CFont font;

		//font.CreatePointFont(Ctxt.tsize, fontS);

		font.CreateFont(
			32,                       // nHeight
			0,                        // nWidth
			0,                        // nEscapement
			0,                        // nOrientation
			Tbold,                // nWeight
			italic,                    // bItalic
			underline,                    // bUnderline
			0,                        // cStrikeOut
			ANSI_CHARSET,             // nCharSet
			OUT_DEFAULT_PRECIS,       // nOutPrecision
			CLIP_DEFAULT_PRECIS,      // nClipPrecision
			DEFAULT_QUALITY,          // nQuality
			DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
			fonttype);

		CGdiObject* pOldFont = dc.SelectObject(&font);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(Ctxt.tcolor);
		Ctxt.StartPnt = atxt->StartPnt;
		Ctxt.EndPnt.x = atxt->EndPnt.x ;
		Ctxt.EndPnt.y = atxt->EndPnt.y ;
		CRect tmct(Ctxt.StartPnt, Ctxt.EndPnt);
		dc.DrawText(txt, tmct, DT_WORDBREAK | DT_EDITCONTROL | DT_TOP | DT_LEFT);
		dc.SelectObject(pOldFont);

		isEdit = false;

		CPaintDoc* pDoc = (CPaintDoc*)GetDocument();

		CTextObj object(atxt->txt, fonttype, Ctxt.tcolor, 32, Tbold, italic, underline, atxt->StartPnt, Ctxt.EndPnt);
		pDoc->AddObjectT(object);
		//PhysicalCoor(&atxt->StartPnt);
	}
	// TODO: 在此加入您的命令處理常式程式碼
}

void CPaintView::OnPolygonTriangle()
{
	mousemode = 2;
	aShape = new CTriangleObj;
	((CMainFrame *)GetParentFrame())->m_wndStatusBar.SetPaneText(6, _T("Triangle"));
	// TODO: 在此加入您的命令處理常式程式碼
	if (isEdit == true)
	{
		CRect crt(atxt->StartPnt.x, atxt->StartPnt.y, atxt->EndPnt.x, atxt->EndPnt.y);
		pEdit->GetWindowText(txt);
		atxt->txt = txt;
		delete(pEdit);

		CClientDC dc(this);
		/*
		//虛框
		CPen pen(PS_DOT, 1, RGB(0, 0, 0));
		CPen* oldPen = dc.SelectObject(&pen);
		dc.SelectStockObject(NULL_BRUSH);
		dc.Rectangle(crt);
		dc.SelectObject(oldPen);
		*/
		CFont font;

		//font.CreatePointFont(Ctxt.tsize, fontS);

		font.CreateFont(
			32,                       // nHeight
			0,                        // nWidth
			0,                        // nEscapement
			0,                        // nOrientation
			Tbold,                // nWeight
			italic,                    // bItalic
			underline,                    // bUnderline
			0,                        // cStrikeOut
			ANSI_CHARSET,             // nCharSet
			OUT_DEFAULT_PRECIS,       // nOutPrecision
			CLIP_DEFAULT_PRECIS,      // nClipPrecision
			DEFAULT_QUALITY,          // nQuality
			DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
			fonttype);

		CGdiObject* pOldFont = dc.SelectObject(&font);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(Ctxt.tcolor);
		Ctxt.StartPnt = atxt->StartPnt;
		Ctxt.EndPnt.x = atxt->EndPnt.x ;
		Ctxt.EndPnt.y = atxt->EndPnt.y ;
		CRect tmct(Ctxt.StartPnt, Ctxt.EndPnt);
		dc.DrawText(txt, tmct, DT_WORDBREAK | DT_EDITCONTROL | DT_TOP | DT_LEFT);
		dc.SelectObject(pOldFont);

		isEdit = false;

		CPaintDoc* pDoc = (CPaintDoc*)GetDocument();

		CTextObj object(atxt->txt, fonttype, Ctxt.tcolor, 32, Tbold, italic, underline, atxt->StartPnt, Ctxt.EndPnt);
		pDoc->AddObjectT(object);
		//PhysicalCoor(&atxt->StartPnt);
	}
}

void  CPaintView::OnLButtonDblClk(UINT, CPoint point)
{
	if (mousemode == 0 && move == 0)
	{
		CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
		int MAXT = pDoc->GetSizeT();
		for (int j = 0; j < MAXT; j++)
		{
			CTextObj Tobj = pDoc->GetObjectT(MAXT - j - 1);
			StartPnt = Tobj.StartPnt;
			EndPnt = Tobj.EndPnt;
			PhysicalCoor(&StartPnt);
			PhysicalCoor(&EndPnt);
			if (StartPnt.x < point.x && point.x < EndPnt.x
				&& StartPnt.y < point.y && point.y < EndPnt.y)
			{
				mousemode = 3;
				recordT = MAXT - j - 1;
				press = false;
				checked = false;
				Tcho = false;
				mousepoint = point;
				txt = Tobj.txt;
				fonttype = Tobj.font;
				Tbold = Tobj.bold;
				italic = Tobj.italic;
				underline = Tobj.underline;
				atxt->StartPnt = StartPnt;
				atxt->EndPnt = EndPnt;
				pDoc->RemoveAtT(recordT);
				pEdit = new CEdit;
				pEdit->Create(ES_MULTILINE | ES_AUTOVSCROLL | WS_CHILD | WS_SIZEBOX | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_MULTILINE,
				CRect(atxt->StartPnt, atxt->EndPnt), this, 1);
				CFont font;

				font.CreateFont(
					32,                       // nHeight
					0,                        // nWidth
					0,                        // nEscapement
					0,                        // nOrientation
					Tbold,                // nWeight
					italic,                    // bItalic
					underline,                    // bUnderline
					0,                        // cStrikeOut
					ANSI_CHARSET,             // nCharSet
					OUT_DEFAULT_PRECIS,       // nOutPrecision
					CLIP_DEFAULT_PRECIS,      // nClipPrecision
					DEFAULT_QUALITY,          // nQuality
					DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
					fonttype);
				pEdit->SetFont(&font);
				pEdit->SetWindowText(txt);
				isEdit = true;
			}
			ReleaseCapture();
			break;
		}
	}
}

void CPaintView::OnLButtonDown(UINT,CPoint point)
{
	if (move == 1 || move==2 ||move ==3 || move==4) 
	{
		 mchecked = true;
	}
	if (mousemode == 0 && move ==0)
	{
		CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
		int MAX = pDoc->GetSize();
		int MAXT = pDoc->GetSizeT();
		for (int i = 0; i < MAX; i++)
		{
			CGraphicObj obj = pDoc->GetObject(MAX - i - 1);
			StartPnt = obj.StartPnt;
			EndPnt = obj.EndPnt;
			PhysicalCoor(&StartPnt);
			PhysicalCoor(&EndPnt);
			if (StartPnt.x < point.x && point.x < EndPnt.x
				&& StartPnt.y < point.y && point.y < EndPnt.y)
			{	
				choose = true;
				record = MAX - i - 1;
				press = true;
				checked = true;
				mousepoint = point;
				lcolor = obj.LineColor;
				fcolor = obj.FillColor;
				linetype = obj.linetype;
				if (obj.shapenum == 1)
				{
					aShape = new CCircleObj;
				}

				else if (obj.shapenum == 2)
				{
					aShape = new CTriangleObj;
				}
				aShape->StartPnt = StartPnt;
				aShape->EndPnt = EndPnt;
				aShape->shapenum = obj.shapenum;
				aShape->linetype = obj.linetype;
				break;
			}
			else if (!(StartPnt.x < point.x && point.x < EndPnt.x
				&& StartPnt.y < point.y && point.y < EndPnt.y))
			{
				choose = false;
				press = false;
				checked = false;
				/*
				CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
				int MAX = pDoc->GetSize();
				CGraphicObj object = pDoc->GetObject(MAX - 1);
				pDoc->RemoveAt(MAX - 1);
				pDoc->AddObject(object);

				PhysicalCoor(&object.StartPnt);
				PhysicalCoor(&object.EndPnt);
				CRect rect(object.StartPnt, object.EndPnt);

				rect.NormalizeRect();
				rect.InflateRect(size, size);

				InvalidateRect(&rect);
				*/
			}
		}

		for (int j = 0; j < MAXT; j++)
		{
			CTextObj Tobj = pDoc->GetObjectT(MAXT - j - 1);
			StartPnt = Tobj.StartPnt;
			EndPnt = Tobj.EndPnt;
			PhysicalCoor(&StartPnt);
			PhysicalCoor(&EndPnt);
			if (StartPnt.x < point.x && point.x < EndPnt.x
				&& StartPnt.y < point.y && point.y < EndPnt.y)
			{
				choose = false;
				recordT = MAXT - j - 1;
				press = true;
				checked = true;
				Tcho = true;
				mousepoint = point;
				txt = Tobj.txt;
				fonttype = Tobj.font;
				Tbold = Tobj.bold;
				italic = Tobj.italic;
				underline = Tobj.underline;
				atxt->StartPnt = StartPnt;
				atxt->EndPnt = EndPnt;
				break;
			}
		}

	}
	else if (mousemode == 1 || mousemode == 2) 
	{
		hcursor = AfxGetApp()->LoadCursor(IDC_CROSS_M);
		::SetCursor(hcursor);
		SetCapture();
		if (this == GetCapture())
		{
			LogicalCoor(&point);
			(*aShape).StartPnt = (*aShape).EndPnt = point;
		}
	}
	else if (mousemode == 3)
	{
		hcursor = AfxGetApp()->LoadCursor(IDC_CURSOR1);
		::SetCursor(hcursor);
		SetCapture();
		if (this == GetCapture()&& isEdit == false)
		{
			LogicalCoor(&point);
			(*atxt).StartPnt = point;
			(*atxt).EndPnt.x = (*atxt).EndPnt.x ;
			(*atxt).EndPnt.y = (*atxt).EndPnt.y;
		}
		/*
		CClientDC aDC(this);
		CRectTracker CRT;
		CRT.m_rect.SetRect(point.x, point.y, point.x + 500, point.y + 50);
		CRT.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeOutside;
		CRT.m_nHandleSize = 6;
		CRT.GetHandleMask();
		CRT.Draw(&aDC);
		*/
	}
	else if (mousemode == 4) 
	{
		drag = true;
		mousepoint = point;
	}
	/*
	if (TextMove == 1 || TextMove == 2 || TextMove == 3 || TextMove == 4  ) 
	{
		TextCheck == true;
	}
	*/
}

void CPaintView::OnMouseMove(UINT, CPoint point)
{
	
	if (checked) 
	{
		if (aShape->StartPnt.x - 5 < point.x &&
			aShape->StartPnt.x + 5 > point.x &&
			aShape->StartPnt.y - 5 < point.y &&
			aShape->StartPnt.y + 5 > point.y) 
		{
			hcursor = AfxGetApp()->LoadCursor(IDC_CURSOR5);
			::SetCursor(hcursor);
			move = 1;
			if (mchecked) {
				CClientDC aDC(this);
				aDC.SetROP2(R2_NOT);

				OnPrepareDC(&aDC);
				LogicalCoor(&point);

				(*aShape).draw(aDC, lcolor, fcolor, width, linetype);
				(*aShape).StartPnt = point;
				(*aShape).draw(aDC, lcolor, fcolor, width, linetype);
			}
		}
		else if (aShape->EndPnt.x - 5 < point.x &&
			aShape->EndPnt.x + 5 > point.x &&
			aShape->StartPnt.y - 5 < point.y &&
			aShape->StartPnt.y + 5 > point.y)
		{
			hcursor = AfxGetApp()->LoadCursor(IDC_CURSOR4);
			::SetCursor(hcursor);
			move = 2;
			if (mchecked) {
				CClientDC aDC(this);
				aDC.SetROP2(R2_NOT);

				OnPrepareDC(&aDC);
				LogicalCoor(&point);

				(*aShape).draw(aDC, lcolor, fcolor, width, linetype);
				(*aShape).StartPnt.y = point.y;
				(*aShape).EndPnt.x = point.x;
				(*aShape).draw(aDC, lcolor, fcolor, width, linetype);
			}
		}
		else if (aShape->EndPnt.x - 5 < point.x &&
			aShape->EndPnt.x + 5 > point.x &&
			aShape->EndPnt.y - 5 < point.y &&
			aShape->EndPnt.y + 5 > point.y
			)
		{
			hcursor = AfxGetApp()->LoadCursor(IDC_CURSOR5);
			::SetCursor(hcursor);
			move = 3;
			if (mchecked) {
				CClientDC aDC(this);
				aDC.SetROP2(R2_NOT);

				OnPrepareDC(&aDC);
				LogicalCoor(&point);

				(*aShape).draw(aDC, lcolor, fcolor, width, linetype);
				(*aShape).EndPnt = point;
				(*aShape).draw(aDC, lcolor, fcolor, width, linetype);
			}
		}
		else if (aShape->StartPnt.x - 5 < point.x &&
			aShape->StartPnt.x + 5 > point.x &&
			aShape->EndPnt.y - 5 < point.y &&
			aShape->EndPnt.y + 5 > point.y)
		{
			hcursor = AfxGetApp()->LoadCursor(IDC_CURSOR4);
			::SetCursor(hcursor);
			move = 4;
			if (mchecked) {
				CClientDC aDC(this);
				aDC.SetROP2(R2_NOT);

				OnPrepareDC(&aDC);
				LogicalCoor(&point);

				(*aShape).draw(aDC, lcolor, fcolor, width, linetype);
				(*aShape).StartPnt.x = point.x;
				(*aShape).EndPnt.y = point.y;
				(*aShape).draw(aDC, lcolor, fcolor, width, linetype);
			}
		}
		else
		{
			move = 0;
		}
			
	}
	if (press)
	{
		
		if (Tcho == true)
		{
			CClientDC aDC(this);
			aDC.SetROP2(R2_NOT);

			OnPrepareDC(&aDC);
			LogicalCoor(&point);
			/*
			CFont font;
			font.CreateFont(
				32,                       // nHeight
				0,                        // nWidth
				0,                        // nEscapement
				0,                        // nOrientation
				(*atxt).bold,                // nWeight
				(*atxt).italic,                    // bItalic
				(*atxt).underline,                    // bUnderline
				0,                        // cStrikeOut
				ANSI_CHARSET,             // nCharSet
				OUT_DEFAULT_PRECIS,       // nOutPrecision
				CLIP_DEFAULT_PRECIS,      // nClipPrecision
				DEFAULT_QUALITY,          // nQuality
				DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
				(*atxt).font);

			CGdiObject* pOldFont = aDC.SelectObject(&font);
			aDC.SetBkMode(TRANSPARENT);
			aDC.SetTextColor((*atxt).tcolor);
			aDC.TextOut((*atxt).StartPnt.x + 5, (*atxt).StartPnt.y + 2, (*atxt).txt);
			aDC.TextOut((*atxt).StartPnt.x + 5, (*atxt).StartPnt.y + 2, (*atxt).txt);
			aDC.SelectObject(pOldFont);
			*/
			CPen penT(PS_DASH, 1, (*atxt).tcolor);
			CPen* oldPenT = aDC.SelectObject(&penT);
			//CBrush bsh(fcolor);
			//CBrush* oldbsh = aDC.SelectObject(&bsh);
			aDC.SelectStockObject(NULL_BRUSH);
			CRect tcrt(atxt->StartPnt, atxt->EndPnt);
			aDC.Rectangle(tcrt);
			aDC.SelectObject(oldPenT);
			
			//PhysicalCoor(&atxt->StartPnt);
			//PhysicalCoor(&atxt->EndPnt);
			(*atxt).StartPnt = (*atxt).StartPnt + point - mousepoint;
			(*atxt).EndPnt = (*atxt).EndPnt + point - mousepoint;

			CPen penTE(PS_DASH, 1, (*atxt).tcolor);
			CPen* oldPenTE = aDC.SelectObject(&penTE);
			//CBrush bsh(fcolor);
			//CBrush* oldbsh = aDC.SelectObject(&bsh);
			//aDC.SelectStockObject(NULL_BRUSH);
			CRect tcrtE(atxt->StartPnt, atxt->EndPnt);
			aDC.Rectangle(tcrtE);
			aDC.SelectObject(oldPenTE);

			mousepoint = point;
			Tmove = true;
		}
		
		else
		{
			CClientDC aDC(this);
			aDC.SetROP2(R2_NOT);

			OnPrepareDC(&aDC);
			LogicalCoor(&point);

			(*aShape).draw(aDC, lcolor, fcolor, width, linetype);
			(*aShape).StartPnt = aShape->StartPnt + point - mousepoint;
			(*aShape).EndPnt = aShape->EndPnt + point - mousepoint;
			(*aShape).draw(aDC, lcolor, fcolor, width, linetype);
			mousepoint = point;
		}
	}
	if (this == GetCapture()&& mousemode !=3 && Tcho == false)
	{
		CClientDC aDC(this);
		aDC.SetROP2(R2_NOT);

		OnPrepareDC(&aDC);
		LogicalCoor(&point);

		(*aShape).draw(aDC, lcolor, fcolor, width, linetype);
		(*aShape).EndPnt = point;
		(*aShape).draw(aDC, lcolor, fcolor, width, linetype);
	}
	if (mousemode == 4 && drag) 
	{
		CPoint Origin = GetScrollPosition();
		Origin = Origin - (point - mousepoint);
		ScrollToPosition(Origin);
		mousepoint = point;
	}
	/*
	if (TextChoose == true) 
	{
		if (atxt->StartPnt.x - 5 < point.x && point.x < atxt->StartPnt.x + 5 
			&& atxt->StartPnt.y -5 <point.y && point.y<atxt->StartPnt.y +5) 
		{
			hcursor = AfxGetApp()->LoadCursor(IDC_CURSOR5);
			::SetCursor(hcursor);
			TextMove = 1;
		}
		else if (atxt->EndPnt.x - 5 < point.x && point.x < atxt->EndPnt.x + 5
			&& atxt->StartPnt.y - 5 < point.y && point.y < atxt->StartPnt.y + 5)
		{
			hcursor = AfxGetApp()->LoadCursor(IDC_CURSOR4);
			::SetCursor(hcursor);
			TextMove = 2;
		}
		else if (atxt->EndPnt.x - 5 < point.x && point.x < atxt->EndPnt.x + 5
			&& atxt->EndPnt.y - 5 < point.y && point.y < atxt->EndPnt.y + 5)
		{
			hcursor = AfxGetApp()->LoadCursor(IDC_CURSOR5);
			::SetCursor(hcursor);
			TextMove = 3;
			if (TextCheck)
			{
				CClientDC dc(this);
				OnPrepareDC(&dc);
				LogicalCoor(&point);
				CPen pen(PS_DOT, 1, RGB(0, 0, 0));
				CPen* oldPen = dc.SelectObject(&pen);
				dc.SelectStockObject(NULL_BRUSH);
				CRect crt(rdtxt->StartPnt.x, rdtxt->StartPnt.y, point.x, point.y);
				dc.Rectangle(crt);
				dc.SelectObject(oldPen);
			}
		}
		else if (atxt->StartPnt.x - 5 < point.x && point.x < atxt->StartPnt.x + 5
			&& atxt->EndPnt.y - 5 < point.y && point.y < atxt->EndPnt.y + 5)
		{
			hcursor = AfxGetApp()->LoadCursor(IDC_CURSOR4);
			::SetCursor(hcursor);
			TextMove = 4;
		}
	}
	*/
}

void CPaintView::OnLButtonUp(UINT, CPoint point)
{
	/*
	CRect crt(aShape->StartPnt.x, aShape->StartPnt.y, aShape->StartPnt.x + 500, aShape->StartPnt.y + 80);
	CClientDC dc(this);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0, 0, 0));
	dc.DrawText(_T("112321"), &crt, DT_TOP | DT_CALCRECT | DT_LEFT);
	*/

	TextChoose = false;

	CRect rectb(atxt->StartPnt, atxt->EndPnt);
	rectb.NormalizeRect();
	rectb.InflateRect(size, size);
	InvalidateRect(&rectb);
	
	if (mchecked)
	{
		mchecked = !mchecked;
		CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
		int MAX = pDoc->GetSize();
		pDoc->RemoveAt(MAX-1);
		CGraphicObj object(aShape->GetShapeNum(), true, fcolor, lcolor, width, linetype, aShape->StartPnt, aShape->EndPnt);
		pDoc->AddObject(object);

		PhysicalCoor(&aShape->StartPnt);
		PhysicalCoor(&aShape->EndPnt);
		CRect rect(aShape->StartPnt, aShape->EndPnt);

		rect.NormalizeRect();
		rect.InflateRect(size, size);

		InvalidateRect(&rect);
	}
	if (press && Tmove == false && Tcho == false)
	{
		CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
		pDoc->RemoveAt(record);
		CGraphicObj object(aShape->GetShapeNum(), true, fcolor, lcolor, width, linetype, aShape->StartPnt, aShape->EndPnt);
		pDoc->AddObject(object);

		PhysicalCoor(&aShape->StartPnt);
		PhysicalCoor(&aShape->EndPnt);
		CRect rect(aShape->StartPnt, aShape->EndPnt);

		rect.NormalizeRect();
		rect.InflateRect(size, size);

		InvalidateRect(&rect);

		ReleaseCapture();
		press = false;
	}

	if (press == false && choose == false && checked == false && mousemode != 3 && Tmove == false)
	{
		CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
		int MAX = pDoc->GetSize();
		CGraphicObj object = pDoc->GetObject(MAX - 1);
		pDoc->RemoveAt(MAX - 1);
		pDoc->AddObject(object);

		PhysicalCoor(&object.StartPnt);
		PhysicalCoor(&object.EndPnt);
		CRect rect(object.StartPnt, object.EndPnt);

		rect.NormalizeRect();
		rect.InflateRect(size, size);

		InvalidateRect(&rect);
	}


	{
		if (this == GetCapture() && mousemode!=3 && Tmove == false)
		{
			choose = true;
			LogicalCoor(&point);
			CClientDC aDC(this);
			(*aShape).EndPnt = point;
			//(*aShape).draw(aDC, lcolor, fcolor, width);
			if (aShape->StartPnt.x > aShape->EndPnt.x)
			{
				int tmp = aShape->StartPnt.x;
				aShape->StartPnt.x = aShape->EndPnt.x;
				aShape->EndPnt.x = tmp;
			}
			if (aShape->StartPnt.y > aShape->EndPnt.y)
			{
				int tmp = aShape->StartPnt.y;
				aShape->StartPnt.y = aShape->EndPnt.y;
				aShape->EndPnt.y = tmp;
			}
			CGraphicObj object(aShape->GetShapeNum(), true, fcolor, lcolor, width, linetype, aShape->StartPnt, aShape->EndPnt);
			CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
			pDoc->AddObject(object);
			PhysicalCoor(&aShape->StartPnt);
			PhysicalCoor(&aShape->EndPnt);

			CRect rect(aShape->StartPnt, aShape->EndPnt);
			rect.NormalizeRect();
			rect.InflateRect(size, size);

			InvalidateRect(&rect);

			ReleaseCapture();
		}
		else if (this == GetCapture() && mousemode == 3 )
		{
			if (isEdit)
			{
				CRect crt;
				CRect window;
				pEdit->GetRect(crt);

				CFrameWnd* main = (CFrameWnd*)AfxGetMainWnd();
				CPaintView* view = (CPaintView*)main->GetActiveView();
				view->GetWindowRect(window);
				pEdit->GetWindowRect(crt);
				atxt->StartPnt.x = crt.left - window.left;
				atxt->StartPnt.y = crt.top - window.top;
				atxt->EndPnt.x = atxt->StartPnt.x + (crt.right - crt.left);
				atxt->EndPnt.y = atxt->StartPnt.y + (crt.bottom - crt.top);
				//Delete text box
				if (!(atxt->StartPnt.x < point.x &&
					atxt->StartPnt.y <point.y &&
					atxt->EndPnt.x  >point.x &&
					atxt->EndPnt.y  >point.y))
				{

					pEdit->GetWindowText(txt);
					atxt->txt = txt;
					delete(pEdit);
					if (atxt->txt != "")
					{ 
					CClientDC dc(this);	

					CFont font ;

					font.CreateFont(
						32,                       // nHeight
						0,                        // nWidth
						0,                        // nEscapement
						0,                        // nOrientation
						Tbold,                // nWeight
						italic,                    // bItalic
						underline,                    // bUnderline
						0,                        // cStrikeOut
						ANSI_CHARSET,             // nCharSet
						OUT_DEFAULT_PRECIS,       // nOutPrecision
						CLIP_DEFAULT_PRECIS,      // nClipPrecision
						DEFAULT_QUALITY,          // nQuality
						DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
						fonttype);

					CGdiObject* pOldFont = dc.SelectObject(&font);
					dc.SetBkMode(TRANSPARENT);
					dc.SetTextColor(Ctxt.tcolor);
					/*
					Ctxt.StartPnt = atxt->StartPnt;
					Ctxt.EndPnt.x = atxt->StartPnt.x+500;
					Ctxt.EndPnt.y = atxt->StartPnt.y + 80;
					*/
					CRect tmct(atxt->StartPnt, atxt->EndPnt);
					dc.DrawText(txt, tmct, DT_WORDBREAK | DT_EDITCONTROL | DT_TOP | DT_LEFT);
					dc.SelectObject(pOldFont);
					
					isEdit = false;

					CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
					CTextObj object(atxt->txt, fonttype, Ctxt.tcolor, 32, Tbold, italic, underline, atxt->StartPnt, atxt->EndPnt);
					mousepoint;
					pDoc->AddObjectT(object);
					//PhysicalCoor(&atxt->StartPnt);
					}
					isEdit = false;
				}
			}
			else
			{
				//Create text box
				pEdit = new CEdit;
				pEdit->Create(ES_MULTILINE | ES_AUTOVSCROLL | WS_CHILD | WS_SIZEBOX | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_MULTILINE,
				CRect(atxt->StartPnt.x, atxt->StartPnt.y, atxt->StartPnt.x + 500, atxt->StartPnt.y + 80), this, 1);
				CFont font;

				font.CreateFont(
					32,                       // nHeight
					0,                        // nWidth
					0,                        // nEscapement
					0,                        // nOrientation
					Tbold,                // nWeight
					italic,                    // bItalic
					underline,                    // bUnderline
					0,                        // cStrikeOut
					ANSI_CHARSET,             // nCharSet
					OUT_DEFAULT_PRECIS,       // nOutPrecision
					CLIP_DEFAULT_PRECIS,      // nClipPrecision
					DEFAULT_QUALITY,          // nQuality
					DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
					fonttype);
				pEdit->SetFont(&font);
				isEdit = true; 
				mousepoint = point;
			}


			ReleaseCapture();
			//pEdit->GetWindowText(strText);
			/*
			CClientDC aDC(this);
			//(*aShape).draw(aDC, lcolor, fcolor, width);
			CGraphicObj object(aShape->GetShapeNum(), true, fcolor, lcolor, width, aShape->StartPnt, aShape->EndPnt);
			CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
			pDoc->AddObject(object);
			PhysicalCoor(&aShape->StartPnt);
			PhysicalCoor(&aShape->EndPnt);

			CRect rect(aShape->StartPnt, aShape->EndPnt);
			rect.NormalizeRect();
			rect.InflateRect(size, size);

			InvalidateRect(&rect);

			ReleaseCapture();
			*/
		}

		else if (Tmove == true || Tcho == true)
		{
			CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
			pDoc->RemoveAtT(recordT);
			CTextObj objectT(txt, fonttype, atxt->tcolor, 32, Tbold, italic, underline, atxt->StartPnt, atxt->EndPnt);

			pDoc->AddObjectT(objectT);

			PhysicalCoor(&atxt->StartPnt);
			PhysicalCoor(&atxt->EndPnt);

			CRect rect(atxt->StartPnt, atxt->EndPnt);

			rect.NormalizeRect();
			rect.InflateRect(size, size);

			InvalidateRect(&rect);

			ReleaseCapture();
			Tmove = false;
			Tcho = false;
			press = false;
			if (atxt->StartPnt.x < point.x && point.x < atxt->EndPnt.x && atxt->StartPnt.y < point.y && point.y < atxt->EndPnt.y) {
				TextChoose = true;
			}
		}
	}


	if (mousemode == 4 && drag)
	{
		drag = false;
	}

}

void CPaintView::OnRButtonDown(UINT, CPoint point)
{

		CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
		int MAX = pDoc->GetSize();
		int MAXT = pDoc->GetSizeT();
		for (int i = 0; i < MAX; i++)
		{
			CGraphicObj obj = pDoc->GetObject(MAX - i - 1);
			StartPnt = obj.StartPnt;
			EndPnt = obj.EndPnt;
			PhysicalCoor(&StartPnt);
			PhysicalCoor(&EndPnt);
			//LogicalCoor(&StartPnt);
			//LogicalCoor(&EndPnt);

			if (StartPnt.x < point.x && point.x < EndPnt.x
				&& StartPnt.y < point.y && point.y < EndPnt.y)
			{
				lcolor = obj.LineColor;
				fcolor = obj.FillColor;
				linetype = obj.linetype;
				/*
				CClientDC aDC(this);
				CRectTracker CRT;
				CRT.m_rect.SetRect(obj.StartPnt.x, obj.StartPnt.y, obj.EndPnt.x, obj.EndPnt.y);
				CRT.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeOutside;
				CRT.m_nHandleSize = 6;
				CRT.Draw(&aDC);
				*/
				record = MAX - i - 1;
				pressR = true;
				mousepoint = point;
				aShape->StartPnt = StartPnt;
				aShape->EndPnt = EndPnt;
				aShape->shapenum = obj.shapenum;
				aShape->linetype = obj.linetype;
				break;
			}
		}

		for (int j = 0; j < MAXT; j++)
		{
			CTextObj Tobj = pDoc->GetObjectT(MAXT - j - 1);
			StartPnt = Tobj.StartPnt;
			EndPnt = Tobj.EndPnt;
			PhysicalCoor(&StartPnt);
			PhysicalCoor(&EndPnt);
			if (StartPnt.x < point.x && point.x < EndPnt.x
				&& StartPnt.y < point.y && point.y < EndPnt.y)
			{
				recordT = MAXT - j - 1;
				pressT = true;
				txt = Tobj.txt;
				fonttype = Tobj.font;
				Tbold = Tobj.bold;
				italic = Tobj.italic;
				underline = Tobj.underline;
				atxt->StartPnt = StartPnt;
				atxt->EndPnt = EndPnt;
				break;
			}
		}
}


void CPaintView::OnBlack()
{
	lcolor = RGB(0, 0, 0);
	//((CMainFrame*)GetParentFrame())->m_wndStatusBar.SetPaneText(5, _T("Black"));
	if (pressR == true)
	{
		aShape->LineColor = lcolor;
		CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
		pDoc->RemoveAt(record);
		StartPnt = aShape->StartPnt;
		EndPnt = aShape->EndPnt;
		LogicalCoor(&StartPnt);
		LogicalCoor(&EndPnt);
		CGraphicObj object(aShape->GetShapeNum(), true, fcolor, lcolor, width, linetype, StartPnt, EndPnt);
		pDoc->AddObject(object);

		PhysicalCoor(&aShape->StartPnt);
		PhysicalCoor(&aShape->EndPnt);
		CRect rect(aShape->StartPnt, aShape->EndPnt);

		rect.NormalizeRect();
		rect.InflateRect(size, size);

		InvalidateRect(&rect);

		ReleaseCapture();
		pressR = false;
	}
	// TODO: 在此加入您的命令處理常式程式碼
}


void CPaintView::OnBlue()
{
	lcolor = RGB(0, 0, 255);
	//((CMainFrame*)GetParentFrame())->m_wndStatusBar.SetPaneText(5, _T("Blue"));
	if (pressR == true)
	{
		aShape->LineColor = lcolor;
		CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
		pDoc->RemoveAt(record);
		StartPnt = aShape->StartPnt;
		EndPnt = aShape->EndPnt;
		LogicalCoor(&StartPnt);
		LogicalCoor(&EndPnt);
		CGraphicObj object(aShape->GetShapeNum(), true, fcolor, lcolor, width, linetype, StartPnt, EndPnt);
		pDoc->AddObject(object);

		PhysicalCoor(&aShape->StartPnt);
		PhysicalCoor(&aShape->EndPnt);
		CRect rect(aShape->StartPnt, aShape->EndPnt);

		rect.NormalizeRect();
		rect.InflateRect(size, size);

		InvalidateRect(&rect);

		ReleaseCapture();
		pressR = false;
	}
	// TODO: 在此加入您的命令處理常式程式碼
}


void CPaintView::OnRed()
{
	lcolor = RGB(255, 0, 0);
	//((CMainFrame*)GetParentFrame())->m_wndStatusBar.SetPaneText(5, _T("Red"));
	if (pressR == true)
	{
		aShape->LineColor = lcolor;
		CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
		pDoc->RemoveAt(record);
		StartPnt = aShape->StartPnt;
		EndPnt = aShape->EndPnt;
		LogicalCoor(&StartPnt);
		LogicalCoor(&EndPnt);
		CGraphicObj object(aShape->GetShapeNum(), true, fcolor, lcolor, width, linetype, StartPnt, EndPnt);
		pDoc->AddObject(object);

		PhysicalCoor(&aShape->StartPnt);
		PhysicalCoor(&aShape->EndPnt);
		CRect rect(aShape->StartPnt, aShape->EndPnt);

		rect.NormalizeRect();
		rect.InflateRect(size, size);

		InvalidateRect(&rect);

		ReleaseCapture();
		pressR = false;
	}
	// TODO: 在此加入您的命令處理常式程式碼
}


void CPaintView::OnUpdateCircle(CCmdUI* aCmdUI)
{
	aCmdUI->SetCheck(mousemode == 1);
}

void CPaintView::OnUpdateTriangle(CCmdUI* aCmdUI)
{
	
	aCmdUI->SetCheck(mousemode == 2);
}

void CPaintView::OnUpdateRed(CCmdUI* aCmdUI)
{
	aCmdUI->SetCheck(lcolor == RGB(255, 0, 0));
}

void CPaintView::OnUpdateBlue(CCmdUI* aCmdUI)
{
	aCmdUI->SetCheck(lcolor == RGB(0, 0, 255));
}

void CPaintView::OnUpdateBlack(CCmdUI* aCmdUI)
{
	aCmdUI->SetCheck(lcolor == RGB(0, 0, 0));
}

void CPaintView::OnUpdateNormal(CCmdUI* aCmdUI)
{
	aCmdUI->SetCheck(mousemode == 0);
}

int CPaintView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	CSize DCSize(size, size);
	SetScrollSizes(MM_TEXT, DCSize);
	return 0;
}

void CPaintView::LogicalCoor(CPoint* point)
{
	CPoint Origin = GetScrollPosition();

	point->x = Origin.x + point->x;
	point->y = Origin.y + point->y;
}

void CPaintView::PhysicalCoor(CPoint* point)
{
	CPoint Origin = GetScrollPosition();

	point->x = point->x - Origin.x;
	point->y = point->y - Origin.y;
}



void CPaintView::OnBlackf()
{
	fcolor = RGB(0, 0, 0);
	((CMainFrame*)GetParentFrame())->m_wndStatusBar.SetPaneText(4, _T("Black"));
	if (pressR == true)
	{
		aShape->FillColor = fcolor;
		CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
		pDoc->RemoveAt(record);

		StartPnt = aShape->StartPnt;
		EndPnt = aShape->EndPnt;
		LogicalCoor(&StartPnt);
		LogicalCoor(&EndPnt);
		CGraphicObj object(aShape->GetShapeNum(), true, fcolor, lcolor, width, linetype, StartPnt, EndPnt);
		pDoc->AddObject(object);

		PhysicalCoor(&aShape->StartPnt);
		PhysicalCoor(&aShape->EndPnt);
		CRect rect(aShape->StartPnt, aShape->EndPnt);

		rect.NormalizeRect();
		rect.InflateRect(size, size);

		InvalidateRect(&rect);

		ReleaseCapture();
		pressR = false;
	}
	// TODO: 在此加入您的命令處理常式程式碼
}


void CPaintView::OnUpdateBlackf(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(fcolor == RGB(0, 0, 0));
	// TODO: 在此加入您的命令更新 UI 處理常式程式碼
}


void CPaintView::OnBluef()
{
	fcolor = RGB(0, 0, 255);
	((CMainFrame*)GetParentFrame())->m_wndStatusBar.SetPaneText(4, _T("Blue"));
	if (pressR == true)
	{
		aShape->FillColor = fcolor;
		CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
		pDoc->RemoveAt(record);
		StartPnt = aShape->StartPnt;
		EndPnt = aShape->EndPnt;
		LogicalCoor(&StartPnt);
		LogicalCoor(&EndPnt);
		CGraphicObj object(aShape->GetShapeNum(), true, fcolor, lcolor, width, linetype, StartPnt, EndPnt);
		pDoc->AddObject(object);

		PhysicalCoor(&aShape->StartPnt);
		PhysicalCoor(&aShape->EndPnt);
		CRect rect(aShape->StartPnt, aShape->EndPnt);

		rect.NormalizeRect();
		rect.InflateRect(size, size);

		InvalidateRect(&rect);

		ReleaseCapture();
		pressR = false;
	}
	// TODO: 在此加入您的命令處理常式程式碼
}


void CPaintView::OnUpdateBluef(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(fcolor == RGB(0, 0, 255));
	// TODO: 在此加入您的命令更新 UI 處理常式程式碼
}


void CPaintView::OnRedf()
{
	fcolor = RGB(255, 0, 0);
	((CMainFrame*)GetParentFrame())->m_wndStatusBar.SetPaneText(4, _T("Red"));
	if (pressR == true)
	{
		aShape->FillColor = fcolor;
		CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
		pDoc->RemoveAt(record);
		StartPnt = aShape->StartPnt;
		EndPnt = aShape->EndPnt;
		LogicalCoor(&StartPnt);
		LogicalCoor(&EndPnt);
		CGraphicObj object(aShape->GetShapeNum(), true, fcolor, lcolor, width, linetype, StartPnt, EndPnt);
		pDoc->AddObject(object);

		PhysicalCoor(&aShape->StartPnt);
		PhysicalCoor(&aShape->EndPnt);
		CRect rect(aShape->StartPnt, aShape->EndPnt);

		rect.NormalizeRect();
		rect.InflateRect(size, size);

		InvalidateRect(&rect);

		ReleaseCapture();
		pressR = false;
	}
	// TODO: 在此加入您的命令處理常式程式碼
}


void CPaintView::OnUpdateRedf(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(fcolor == RGB(255, 0, 0));
	// TODO: 在此加入您的命令更新 UI 處理常式程式碼
}

void CPaintView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	int x = 0;
	int y = 0;
	if (VK_UP == nChar)
	{
		y = -1;
	}

	else if (VK_DOWN == nChar)
	{
		y = 1;
	}

	else if (VK_LEFT == nChar)
	{
		x = -1;
	}

	else if (VK_RIGHT == nChar)
	{
		x = 1;
	}

	else if (VK_DELETE == nChar)
	{
		if (checked)
		{
			checked = !checked;
			choose = false;
			CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
			int MAX = pDoc->GetSize();
			pDoc->RemoveAt(MAX - 1);
			CRect rect(CPoint(size, size), CPoint(size, size));

			rect.NormalizeRect();
			rect.InflateRect(size, size);

			InvalidateRect(&rect);
		}
	}

	if (checked) 
	{
		CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
		int MAX = pDoc->GetSize();
		pDoc->RemoveAt(MAX-1);
		aShape->StartPnt.x = aShape->StartPnt.x + x;
		aShape->EndPnt.x = aShape->EndPnt.x + x;
		aShape->StartPnt.y = aShape->StartPnt.y + y;
		aShape->EndPnt.y = aShape->EndPnt.y + y;
		CGraphicObj object(aShape->GetShapeNum(), true, fcolor, lcolor, width, linetype, aShape->StartPnt, aShape->EndPnt);
		pDoc->AddObject(object);

		PhysicalCoor(&aShape->StartPnt);
		PhysicalCoor(&aShape->EndPnt);
		CRect rect(aShape->StartPnt, aShape->EndPnt);

		rect.NormalizeRect();
		rect.InflateRect(size, size);

		InvalidateRect(&rect);
	}
}

void CPaintView::OnZoomin()
{
	float number = 1.2;
	CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
	int MAX = pDoc->GetSize();
	for (int i = 0; i < MAX; i++)
	{
		CGraphicObj obj = pDoc->GetObject(0);
		lcolor = obj.LineColor;
		fcolor = obj.FillColor;
		linetype = obj.linetype;
		if (obj.shapenum == 1)
		{
			aShape = new CCircleObj;
		}

		else if (obj.shapenum == 2)
		{
			aShape = new CTriangleObj;
		}
		aShape->StartPnt.x = obj.StartPnt.x* number;
		aShape->StartPnt.y = obj.StartPnt.y * number;
		aShape->EndPnt.x = obj.EndPnt.x* number;
		aShape->EndPnt.y = obj.EndPnt.y* number;
		aShape->shapenum = obj.shapenum;
		aShape->linetype = obj.linetype;

		CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
		pDoc->RemoveAt(0);
		CGraphicObj object(aShape->GetShapeNum(), true, fcolor, lcolor, width, linetype, aShape->StartPnt, aShape->EndPnt);
		pDoc->AddObject(object);
	}
	PhysicalCoor(&aShape->StartPnt);
	PhysicalCoor(&aShape->EndPnt);
	CRect rect(aShape->StartPnt, aShape->EndPnt);
	size = size * number;
	rect.NormalizeRect();
	rect.InflateRect(size, size);

	InvalidateRect(&rect);

	CSize DCSize(size, size);
	SetScrollSizes(MM_TEXT, DCSize);
}

void CPaintView::OnZoomout()
{

	float number = 1/1.2;
	CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
	int MAX = pDoc->GetSize();
	for (int i = 0; i < MAX; i++)
	{
		CGraphicObj obj = pDoc->GetObject(0);
		lcolor = obj.LineColor;
		fcolor = obj.FillColor;
		if (obj.shapenum == 1)
		{
			aShape = new CCircleObj;
		}

		else if (obj.shapenum == 2)
		{
			aShape = new CTriangleObj;
		}
		aShape->StartPnt.x = obj.StartPnt.x * number;
		aShape->StartPnt.y = obj.StartPnt.y * number;
		aShape->EndPnt.x = obj.EndPnt.x * number;
		aShape->EndPnt.y = obj.EndPnt.y * number;
		aShape->shapenum = obj.shapenum;

		CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
		pDoc->RemoveAt(0);
		CGraphicObj object(aShape->GetShapeNum(), true, fcolor, lcolor, width, linetype, aShape->StartPnt, aShape->EndPnt);
		pDoc->AddObject(object);
	}
	PhysicalCoor(&aShape->StartPnt);
	PhysicalCoor(&aShape->EndPnt);
	CRect rect(aShape->StartPnt, aShape->EndPnt);
	size = size * number;
	rect.NormalizeRect();
	rect.InflateRect(size, size);

	InvalidateRect(&rect);

	CSize DCSize(size, size);
	SetScrollSizes(MM_TEXT, DCSize);
}

void CPaintView::OnText()
{
	mousemode = 3;
	((CMainFrame*)GetParentFrame())->m_wndStatusBar.SetPaneText(6, _T("Text"));
	/*
	CEdit* pEdit;
	pEdit = new CEdit;
	pEdit->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_MULTILINE , CRect(150, 10, 500, 50), this, 1);
	CString strText;
	pEdit->GetWindowText(strText);
	*/
}

void CPaintView::OnUpdateText(CCmdUI* aCmdUI)
{
	aCmdUI->SetCheck(mousemode == 3);
}
/*
void CPaintView::OnUserdefine()
{
	COLORREF dcolor = RGB(255, 0, 0);
	CColorDialog cdlg(lcolor, CC_FULLOPEN);

	if (cdlg.DoModal() == IDOK)
	{
		lcolor = cdlg.GetColor();
		((CMainFrame*)GetParentFrame())->m_wndStatusBar.SetPaneText(1, _T("UserDefine"));
	}
}
*/

void CPaintView::OnProperty()
{
	CPropertySheet sheet(_T("Properties Setting"));
	PROPPAGE_BORDER combopage;
	PROPPAGE_COLOR checkcolor;
	PROPPAGE_FONT font;

	sheet.AddPage(&checkcolor);
	sheet.AddPage(&combopage);
	sheet.AddPage(&font);

	INT_PTR pmenu = sheet.DoModal();
	if (pmenu == IDOK) 
	{
		fcolor = checkcolor.fcolor;
//		Ctxt.tcolor = fcolor;
		lcolor = combopage.lcolor;
		bold = font.bold;
		if (bold == true)
		{
			Tbold = 700;
		}
		else if (bold == false)
		{
			Tbold = 400;
		}
		italic = font.italic;
		underline = font.underline;
		CLtype = combopage.VLtype;
		linetype = TLineType(CLtype);
		fonttype = font.Vfont;

		CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
		int max = pDoc->GetSize();
		int maxT = pDoc->GetSizeT();
		if (pressR == true)
		{
			if (max > 0) {
				pressR = false;
				pDoc->RemoveAt(max - 1);

				StartPnt = aShape->StartPnt;
				EndPnt = aShape->EndPnt;
				LogicalCoor(&StartPnt);
				LogicalCoor(&EndPnt);
				CGraphicObj object(aShape->GetShapeNum(), true, fcolor, lcolor, width, linetype, StartPnt, EndPnt);
				pDoc->AddObject(object);
				//LogicalCoor(&aShape->StartPnt);
				//LogicalCoor(&aShape->EndPnt);
				PhysicalCoor(&aShape->StartPnt);
				PhysicalCoor(&aShape->EndPnt);
				CRect rect(aShape->StartPnt, aShape->EndPnt);

				rect.NormalizeRect();
				rect.InflateRect(size, size);

				InvalidateRect(&rect);
			}
		}
		else if (pressT == true)
		{
			pressT == false;
			pDoc->RemoveAtT(maxT-1);
			TStartPnt = atxt->StartPnt;
			TEndPnt = atxt->EndPnt;
			LogicalCoor(&TStartPnt);
			LogicalCoor(&TEndPnt);
			CTextObj objectT(txt, fonttype, atxt->tcolor, 32, Tbold, italic, underline, TStartPnt, TEndPnt);

			pDoc->AddObjectT(objectT);

			PhysicalCoor(&atxt->StartPnt);
			PhysicalCoor(&atxt->EndPnt);

			CRect rect(atxt->StartPnt, atxt->EndPnt);

			rect.NormalizeRect();
			rect.InflateRect(size, size);

			InvalidateRect(&rect);

			ReleaseCapture();
		}

	}
	if (pmenu == IDCANCEL)
	{

	}
}


void CPaintView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu menu;
	menu.CreatePopupMenu();
	if (fcolor == RGB(0, 0, 0))
	{
		menu.AppendMenu(MF_CHECKED, IDM_BlackF, &bmpBk);
		menu.AppendMenu(MF_BITMAP, IDM_BlueF, &bmpBl);
		menu.AppendMenu(MF_BITMAP, IDM_RedF, &bmpRd);
	}

	else if (fcolor == RGB(0, 0, 255))
	{
		menu.AppendMenu(MF_BITMAP, IDM_BlackF, &bmpBk);
		menu.AppendMenu(MF_CHECKED, IDM_BlueF, &bmpBl);
		menu.AppendMenu(MF_BITMAP, IDM_RedF, &bmpRd);
	}

	else if (fcolor == RGB(255, 0, 0))
	{
		menu.AppendMenu(MF_BITMAP, IDM_BlackF, &bmpBk);
		menu.AppendMenu(MF_BITMAP, IDM_BlueF, &bmpBl);
		menu.AppendMenu(MF_CHECKED, IDM_RedF, &bmpRd);
	}

	else
	{
		menu.AppendMenu(MF_BITMAP, IDM_BlackF, &bmpBk);
		menu.AppendMenu(MF_BITMAP, IDM_BlueF, &bmpBl);
		menu.AppendMenu(MF_BITMAP, IDM_RedF, &bmpRd);
	}


	menu.AppendMenu(MF_SEPARATOR);																				   //插入分隔線

	if (linetype == 1)
	{
		menu.AppendMenu(MF_CHECKED, ID_LINETYPE_LINE, &bmpLn);
		menu.AppendMenu(MF_BITMAP, ID_LINETYPE_DASHLINE, &bmpDtln);
		menu.AppendMenu(MF_BITMAP, ID_LINETYPE_DOTLINE, &bmpDt);
	}

	else if (linetype == 2)
	{
		menu.AppendMenu(MF_BITMAP, ID_LINETYPE_LINE, &bmpLn);
		menu.AppendMenu(MF_CHECKED, ID_LINETYPE_DASHLINE, &bmpDtln);
		menu.AppendMenu(MF_BITMAP, ID_LINETYPE_DOTLINE, &bmpDt);
	}

	else if (linetype == 3)
	{
		menu.AppendMenu(MF_BITMAP, ID_LINETYPE_LINE, &bmpLn);
		menu.AppendMenu(MF_BITMAP, ID_LINETYPE_DASHLINE, &bmpDtln);
		menu.AppendMenu(MF_CHECKED, ID_LINETYPE_DOTLINE, &bmpDt);
	}

	menu.AppendMenu(MF_SEPARATOR);																				   //插入分隔線
	menu.AppendMenu(MF_STRING, ID_PROPERTY, _T("Property..."));
	
	menu.TrackPopupMenu(TPM_CENTERALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	menu.DestroyMenu();

}

void CPaintView::OnLn()
{
	linetype = 1;
	if (pressR == true)
	{
		//aShape->linetype = linetype;
		CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
		pDoc->RemoveAt(record);
		StartPnt = aShape->StartPnt;
		EndPnt = aShape->EndPnt;
		LogicalCoor(&StartPnt);
		LogicalCoor(&EndPnt);
		CGraphicObj object(aShape->GetShapeNum(), true, fcolor, lcolor, width, linetype, StartPnt, EndPnt);
		pDoc->AddObject(object);

		PhysicalCoor(&aShape->StartPnt);
		PhysicalCoor(&aShape->EndPnt);
		CRect rect(aShape->StartPnt, aShape->EndPnt);

		rect.NormalizeRect();
		rect.InflateRect(size, size);

		InvalidateRect(&rect);

		ReleaseCapture();
		pressR = false;
	}
}

void CPaintView::OnDtln()
{
	linetype = 2;
	if (pressR == true)
	{
		//aShape->linetype = linetype;
		CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
		pDoc->RemoveAt(record);

		StartPnt = aShape->StartPnt;
		EndPnt = aShape->EndPnt;
		LogicalCoor(&StartPnt);
		LogicalCoor(&EndPnt);
		CGraphicObj object(aShape->GetShapeNum(), true, fcolor, lcolor, width, linetype, StartPnt, EndPnt);
		pDoc->AddObject(object);

		PhysicalCoor(&aShape->StartPnt);
		PhysicalCoor(&aShape->EndPnt);
		CRect rect(aShape->StartPnt, aShape->EndPnt);

		rect.NormalizeRect();
		rect.InflateRect(size, size);

		InvalidateRect(&rect);

		ReleaseCapture();
		pressR = false;
	}
}

void CPaintView::OnDt()
{
	linetype = 3;
	if (pressR == true)
	{
		//aShape->linetype = linetype;
		CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
		pDoc->RemoveAt(record);
		StartPnt = aShape->StartPnt;
		EndPnt = aShape->EndPnt;
		LogicalCoor(&StartPnt);
		LogicalCoor(&EndPnt);
		CGraphicObj object(aShape->GetShapeNum(), true, fcolor, lcolor, width, linetype, StartPnt, EndPnt);
		pDoc->AddObject(object);

		PhysicalCoor(&aShape->StartPnt);
		PhysicalCoor(&aShape->EndPnt);
		CRect rect(aShape->StartPnt, aShape->EndPnt);

		rect.NormalizeRect();
		rect.InflateRect(size, size);

		InvalidateRect(&rect);

		ReleaseCapture();
		pressR = false;
	}
}

void CPaintView::OnUpdateLn(CCmdUI* aCmdUI)
{
	aCmdUI->SetCheck(linetype == 1);
}

void CPaintView::OnUpdateDtln(CCmdUI* aCmdUI)
{
	aCmdUI->SetCheck(linetype == 2);
}

void CPaintView::OnUpdateDt(CCmdUI* aCmdUI)
{
	aCmdUI->SetCheck(linetype == 3);
}

void CPaintView::OnMove()
{
	mousemode = 4;
	if (isEdit == true)
	{
		CRect crt(atxt->StartPnt.x, atxt->StartPnt.y, atxt->EndPnt.x , atxt->EndPnt.y );
		pEdit->GetWindowText(txt);
		atxt->txt = txt;
		delete(pEdit);

		CClientDC dc(this);
		/*
		//虛框
		CPen pen(PS_DOT, 1, RGB(0, 0, 0));
		CPen* oldPen = dc.SelectObject(&pen);
		dc.SelectStockObject(NULL_BRUSH);
		dc.Rectangle(crt);
		dc.SelectObject(oldPen);
		*/
		CFont font;

		//font.CreatePointFont(Ctxt.tsize, fontS);

		font.CreateFont(
			32,                       // nHeight
			0,                        // nWidth
			0,                        // nEscapement
			0,                        // nOrientation
			Tbold,                // nWeight
			italic,                    // bItalic
			underline,                    // bUnderline
			0,                        // cStrikeOut
			ANSI_CHARSET,             // nCharSet
			OUT_DEFAULT_PRECIS,       // nOutPrecision
			CLIP_DEFAULT_PRECIS,      // nClipPrecision
			DEFAULT_QUALITY,          // nQuality
			DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
			fonttype);

		CGdiObject* pOldFont = dc.SelectObject(&font);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(Ctxt.tcolor);
		Ctxt.StartPnt = atxt->StartPnt;
		Ctxt.EndPnt.x = atxt->EndPnt.x;
		Ctxt.EndPnt.y = atxt->EndPnt.y;
		CRect tmct(Ctxt.StartPnt, Ctxt.EndPnt);
		dc.DrawText(txt, tmct, DT_WORDBREAK | DT_EDITCONTROL | DT_TOP | DT_LEFT);
		dc.SelectObject(pOldFont);

		isEdit = false;

		CPaintDoc* pDoc = (CPaintDoc*)GetDocument();

		CTextObj object(atxt->txt, fonttype, Ctxt.tcolor, 32, Tbold, italic, underline, atxt->StartPnt, Ctxt.EndPnt);
		pDoc->AddObjectT(object);
		//PhysicalCoor(&atxt->StartPnt);
	}
}

void CPaintView::OnUpdateMove(CCmdUI* aCmdUI)
{
	aCmdUI->SetCheck(mousemode == 4);
}