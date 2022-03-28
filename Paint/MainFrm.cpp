
// MainFrm.cpp: CMainFrame 類別的實作
//

#include "pch.h"
#include "framework.h"
#include "Paint.h"

#include "MainFrm.h"
#include "PROPPAGE_BORDER.h"
#include "PROPPAGE_COLOR.h"
#include "PROPPAGE_FONT.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnTooltipHandler)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 狀態列指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
	IDS_FCOLOR,
	IDS_Color,
	IDS_Shape,
};

// CMainFrame 建構/解構

CMainFrame::CMainFrame() noexcept
{

	// TODO: 在此加入成員初始化程式碼
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("無法建立工具列\n");
		return -1;      // 無法建立
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("無法建立狀態列\n");
		return -1;      // 無法建立
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	// TODO: 如果您不要可以固定工具列，請刪除這三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	m_wndToolBar.EnableToolTips(TRUE);
	return 0;
}



BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	// TODO: 在此經由修改 CREATESTRUCT cs 
	// 達到修改視窗類別或樣式的目的

	return TRUE;
}

BOOL CMainFrame::OnTooltipHandler(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
{
	TOOLTIPTEXT* pTTT = (TOOLTIPTEXT*)pNMHDR;
	UINT nID = static_cast<int>(pNMHDR->idFrom);
	CString strTip = _T("");

	switch (nID)
	{
		case ID_POLYGON_TRIANGLE:
			strTip = "Triangle tool";
			break;

		case ID_POLYGON_ELLIPSE:
			strTip = "Ellipse tool";
			break;

		case ID_CURNORMAL:
			strTip = "Select tool";
			break;

		case ID_TEXT:
			strTip = "Text tool";
			break;

		case ID_ZOOMIN:
			strTip = "Zoom in(+)";
			break;

		case ID_ZOOMOUT:
			strTip = "Zoom out(-)";
			break;

		case ID_FILE_NEW:
			strTip = "New";
			break;

		case ID_FILE_OPEN:
			strTip = "Load";
			break;

		case ID_FILE_SAVE:
			strTip = "Save";
			break;
	}

	wcscpy_s(pTTT->szText, strTip.GetBuffer(0));
	return 0;
}

// CMainFrame 診斷

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 訊息處理常式




	
	// TODO: 在此加入您的命令處理常式程式碼

