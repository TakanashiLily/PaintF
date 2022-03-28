// PROPPAGE_FONT.cpp: 實作檔案
//

#include "pch.h"
#include "Paint.h"
#include "PROPPAGE_FONT.h"
#include "afxdialogex.h"
#include "PaintView.h"


// PROPPAGE_FONT 對話方塊

IMPLEMENT_DYNAMIC(PROPPAGE_FONT, CPropertyPage)

PROPPAGE_FONT::PROPPAGE_FONT(): CPropertyPage(IDD_PROPPAGE_FONT), m_combo_droplist(0)
{
	CFrameWnd* main = (CFrameWnd*)AfxGetMainWnd();
	CPaintView* view = (CPaintView*)main->GetActiveView();
	Vfont = view->GetFtype();
	bold = view->GetBold();
	italic = view->GetItalic();
	underline = view->GetUnderline();
	
	/*
	if (italic = true)
	{
		((CButton*)GetDlgItem(IDC_ITALIC))->SetCheck(TRUE);
	}

	if (underline = true)
	{
		((CButton*)GetDlgItem(IDC_UNDERLINE))->SetCheck(TRUE);
	}

	if (bold = true)
	{
		((CButton*)GetDlgItem(IDC_BOLD))->SetCheck(TRUE);
	}
	*/
}

PROPPAGE_FONT::~PROPPAGE_FONT()
{
}

void PROPPAGE_FONT::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_FONTTYPE, m_combo_droplist);
	CComboBox* Ocb = (CComboBox*)GetDlgItem(IDC_FONTTYPE);
	Ocb->SelectString(0, Vfont);
	CButton* BD = ((CButton*)GetDlgItem(IDC_BOLD));
	CButton* IT = ((CButton*)GetDlgItem(IDC_ITALIC));
	CButton* UL = ((CButton*)GetDlgItem(IDC_UNDERLINE));
	BD->SetCheck(bold);
	IT->SetCheck(italic);
	UL->SetCheck(underline);

}


BEGIN_MESSAGE_MAP(PROPPAGE_FONT, CPropertyPage)
	ON_CBN_SELCHANGE(IDC_FONTTYPE, &PROPPAGE_FONT::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BOLD, &PROPPAGE_FONT::OnBnClickedBold)
	ON_BN_CLICKED(IDC_ITALIC, &PROPPAGE_FONT::OnBnClickedItalic)
	ON_BN_CLICKED(IDC_UNDERLINE, &PROPPAGE_FONT::OnBnClickedUnderline)
END_MESSAGE_MAP()


// PROPPAGE_FONT 訊息處理常式


void PROPPAGE_FONT::OnCbnSelchangeCombo1()
{
	SetModified();
	// TODO: 在此加入控制項告知處理常式程式碼
}

BOOL PROPPAGE_FONT::OnApply()
{
	CString SelCombo, buffer;
	CComboBox* DropListCombo = (CComboBox*)GetDlgItem(IDC_FONTTYPE);
	DropListCombo->GetLBText(m_combo_droplist, buffer);
	Vfont = buffer;
	/*
	if (buffer == _T("Arial"))
	{
		CFrameWnd* main = (CFrameWnd*)AfxGetMainWnd();
		CPaintView* view = (CPaintView*)main->GetActiveView();
		view->SetFtype(_T("Arial"));
	}

	else if (buffer == _T("Calibri"))
	{
		CFrameWnd* main = (CFrameWnd*)AfxGetMainWnd();
		CPaintView* view = (CPaintView*)main->GetActiveView();
		view->SetFtype(_T("Calibri"));
	}

	else if (buffer == _T("Comic Sans MS"))
	{
		CFrameWnd* main = (CFrameWnd*)AfxGetMainWnd();
		CPaintView* view = (CPaintView*)main->GetActiveView();
		view->SetFtype(_T("Comic Sans MS"));
	}

	else if (buffer == _T("Times New Roman"))
	{
		CFrameWnd* main = (CFrameWnd*)AfxGetMainWnd();
		CPaintView* view = (CPaintView*)main->GetActiveView();
		view->SetFtype(_T("Times New Roman"));
	}
	*/

	//SelCombo = CString("Drop List : ") + buffer;
	//MessageBox(SelCombo, _T("Combo Box Select Result"));

	return CPropertyPage::OnApply();
}

BOOL PROPPAGE_FONT::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	InitCombo(IDC_FONTTYPE);
	return TRUE;
}

void PROPPAGE_FONT::InitCombo(int ID)
{
	CString Item[4] = { _T("Arial"),_T("Calibri"),_T("Comic Sans MS"), _T("Times New Roman")};
	CComboBox* ComboBox = (CComboBox*)GetDlgItem(ID);

	for (int i = 0; i < 4; i++)
		ComboBox->AddString(Item[i]);
	if (Vfont == _T("Arial"))
	{
		ComboBox->SetCurSel(0);
	}

	else if (Vfont == _T("Calibri"))
	{
		ComboBox->SetCurSel(1);
	}

	else if (Vfont == _T("Comic Sans MS"))
	{
		ComboBox->SetCurSel(2);
	}

	else if (Vfont == _T("Times New Roman"))
	{
		ComboBox->SetCurSel(3);
	}
}


void PROPPAGE_FONT::OnBnClickedBold()
{
	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_BOLD))->GetCheck())
	{
		bold = true;
	}

	if (BST_UNCHECKED == ((CButton*)GetDlgItem(IDC_BOLD))->GetCheck())
	{
		bold = false;
	}
	// TODO: 在此加入控制項告知處理常式程式碼
}


void PROPPAGE_FONT::OnBnClickedItalic()
{
	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_ITALIC))->GetCheck())
	{
		italic = true;
	}

	if (BST_UNCHECKED == ((CButton*)GetDlgItem(IDC_ITALIC))->GetCheck())
	{
		italic = false;
	}
	// TODO: 在此加入控制項告知處理常式程式碼
}


void PROPPAGE_FONT::OnBnClickedUnderline()
{
	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_UNDERLINE))->GetCheck())
	{
		underline = true;
	}

	if (BST_UNCHECKED == ((CButton*)GetDlgItem(IDC_UNDERLINE))->GetCheck())
	{
		underline = false;
	}
	// TODO: 在此加入控制項告知處理常式程式碼
}
