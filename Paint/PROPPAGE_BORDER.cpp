// PROPPAGE_BORDER.cpp: 實作檔案
//

#include "pch.h"
#include "Paint.h"
#include "PROPPAGE_BORDER.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "PaintView.h"



// PROPPAGE_BORDER 對話方塊

IMPLEMENT_DYNAMIC(PROPPAGE_BORDER, CPropertyPage)

PROPPAGE_BORDER::PROPPAGE_BORDER(): CPropertyPage(IDD_PROPPAGE_BORDER), m_combo_droplist(0)
{
	CFrameWnd* main = (CFrameWnd*)AfxGetMainWnd();
	CPaintView* view = (CPaintView*)main->GetActiveView();
	lcolor = view->GetLcolor();
	VLtype = view->SLineType(view->GetLtype());
}

PROPPAGE_BORDER::~PROPPAGE_BORDER()
{
}

void PROPPAGE_BORDER::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_BDLINETYPE, m_combo_droplist);
	CMFCButton* LNCL = (CMFCButton*)GetDlgItem(IDC_LNCOLOR);
	CComboBox* Ocb = (CComboBox*)GetDlgItem(IDC_BDLINETYPE);
	LNCL->SetFaceColor(lcolor);
	Ocb->SelectString(0, VLtype);
	
}


BEGIN_MESSAGE_MAP(PROPPAGE_BORDER, CPropertyPage)
	ON_CBN_SELCHANGE(IDC_BDLINETYPE, &PROPPAGE_BORDER::OnCbnSelchangeComboDroplist)
	ON_BN_CLICKED(IDC_LNCOLOR, &PROPPAGE_BORDER::OnBnClickedLncolor)
END_MESSAGE_MAP()


// PROPPAGE_BORDER 訊息處理常式

void PROPPAGE_BORDER::OnCbnSelchangeComboDroplist()
{
	SetModified();
}
	
BOOL PROPPAGE_BORDER::OnApply()
{
	CString SelCombo, buffer;
	CComboBox* DropListCombo = (CComboBox*)GetDlgItem(IDC_BDLINETYPE);
	DropListCombo->GetLBText(m_combo_droplist, buffer);
	VLtype = buffer;
	/*
	if (buffer == _T("----------------"))
	{
		CFrameWnd* main = (CFrameWnd*)AfxGetMainWnd();
		CPaintView* view = (CPaintView*)main->GetActiveView();
		view->SetLtype(1);
	}

	else if (buffer == _T("- - - - - - - - - - - -"))
	{
		CFrameWnd* main = (CFrameWnd*)AfxGetMainWnd();
		CPaintView* view = (CPaintView*)main->GetActiveView();
		view->SetLtype(2);
	}

	else if (buffer == _T("-   -   -   -   -   -   -   -   -"))
	{
		CFrameWnd* main = (CFrameWnd*)AfxGetMainWnd();
		CPaintView* view = (CPaintView*)main->GetActiveView();
		view->SetLtype(3);
	}
	*/

	//SelCombo = CString("Drop List : ") + buffer;
	//MessageBox(SelCombo, _T("Combo Box Select Result"));

	return CPropertyPage::OnApply();
}

BOOL PROPPAGE_BORDER::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	InitCombo(IDC_BDLINETYPE);
	return TRUE;
}

void PROPPAGE_BORDER::InitCombo(int ID)
{
	CString Item[3] = { _T("----------------"),_T("- - - - - - - - - - - -"),_T("-   -   -   -   -   -   -   -   -")};
	CComboBox* ComboBox = (CComboBox*)GetDlgItem(ID);

	for (int i = 0; i < 3; i++)
		ComboBox->AddString(Item[i]);
	if (VLtype == _T("----------------"))
	{
		ComboBox->SetCurSel(0);
	}
	
	else if (VLtype == _T("- - - - - - - - - - - -"))
	{
		ComboBox->SetCurSel(1);
	}

	else if (VLtype == _T("-   -   -   -   -   -   -   -   -"))
	{
		ComboBox->SetCurSel(2);
	}
}




void PROPPAGE_BORDER::OnBnClickedLncolor()
{
		
	COLORREF LNcolor = lcolor;
	CColorDialog BDcdlg(LNcolor, CC_FULLOPEN);

	if (BDcdlg.DoModal() == IDOK)
	{
		LNcolor = BDcdlg.GetColor();
		//((CMainFrame*)GetParentFrame())->m_wndStatusBar.SetPaneText(1, _T("FZZX"));
		CMFCButton* BDCL = (CMFCButton*)GetDlgItem(IDC_LNCOLOR);
		BDCL->SetFaceColor(LNcolor);

		lcolor = LNcolor;
	}
	
	// TODO: 在此加入控制項告知處理常式程式碼
}
