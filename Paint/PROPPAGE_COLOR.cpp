// PROPPAGE_COLOR.cpp: 實作檔案
//

#include "pch.h"
#include "Paint.h"
#include "PROPPAGE_COLOR.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "PaintView.h"


// PROPPAGE_COLOR 對話方塊

IMPLEMENT_DYNAMIC(PROPPAGE_COLOR, CPropertyPage)

PROPPAGE_COLOR::PROPPAGE_COLOR(): CPropertyPage(IDD_PROPPAGE_COLOR)
{
	CFrameWnd* main = (CFrameWnd*)AfxGetMainWnd();
	CPaintView* view = (CPaintView*)main->GetActiveView();
	fcolor = view->GetFcolor();

}

PROPPAGE_COLOR::~PROPPAGE_COLOR()
{
}

void PROPPAGE_COLOR::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	CMFCButton* mfcb = (CMFCButton*)GetDlgItem(IDC_FORECOLOR);
	mfcb->SetFaceColor(fcolor);
}


BEGIN_MESSAGE_MAP(PROPPAGE_COLOR, CPropertyPage)
	ON_BN_CLICKED(IDC_FORECOLOR, &PROPPAGE_COLOR::OnBnClickedForecolor)
	ON_BN_CLICKED(IDC_BGCOLOR, &PROPPAGE_COLOR::OnBnClickedBgcolor)
END_MESSAGE_MAP()


// PROPPAGE_COLOR 訊息處理常式


void PROPPAGE_COLOR::OnBnClickedForecolor()
{

	COLORREF FLcolor = fcolor;
	CColorDialog cdlg(FLcolor, CC_FULLOPEN);

	if (cdlg.DoModal() == IDOK)
	{
		FLcolor = cdlg.GetColor();
		//((CMainFrame*)GetParentFrame())->m_wndStatusBar.SetPaneText(1, _T("UserDefine"));
		CMFCButton* mfcb = (CMFCButton*)GetDlgItem(IDC_FORECOLOR);
		mfcb->SetFaceColor(FLcolor);
		fcolor = FLcolor;
		
	}


	// TODO: 在此加入控制項告知處理常式程式碼
}


void PROPPAGE_COLOR::OnBnClickedBgcolor()
{
	// TODO: 在此加入控制項告知處理常式程式碼
}
