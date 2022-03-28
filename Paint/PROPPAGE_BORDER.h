#pragma once

// PROPPAGE_BORDER 對話方塊

class PROPPAGE_BORDER : public CPropertyPage
{
	DECLARE_DYNAMIC(PROPPAGE_BORDER)

public:
	PROPPAGE_BORDER();
	virtual ~PROPPAGE_BORDER();
	friend class CPaintView;

public:
	COLORREF lcolor;
	int linetype;
	CString VLtype;
// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_BORDER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()

private:

private:
	int m_combo_droplist;
private:
	afx_msg void OnCbnSelchangeComboDroplist();
	virtual BOOL OnApply();
	virtual BOOL OnInitDialog();
	void InitCombo(int ID);
public:
	afx_msg void OnBnClickedLncolor();
};




