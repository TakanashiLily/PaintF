#pragma once


// PROPPAGE_FONT 對話方塊

class PROPPAGE_FONT : public CPropertyPage
{
	DECLARE_DYNAMIC(PROPPAGE_FONT)

public:
	PROPPAGE_FONT();
	virtual ~PROPPAGE_FONT();
	friend class CPaintView;
	CString Vfont;
	BOOL italic, underline, bold;

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_FONT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:


private:
	int m_combo_droplist;
private:
	afx_msg void OnCbnSelchangeCombo1();
	virtual BOOL OnApply();
	virtual BOOL OnInitDialog();
	void InitCombo(int ID);
public:
	afx_msg void OnBnClickedBold();
	afx_msg void OnBnClickedItalic();
	afx_msg void OnBnClickedUnderline();
};
