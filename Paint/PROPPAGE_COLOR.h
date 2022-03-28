#pragma once


// PROPPAGE_COLOR 對話方塊

class PROPPAGE_COLOR : public CPropertyPage
{
	DECLARE_DYNAMIC(PROPPAGE_COLOR)

public:
	COLORREF lcolor, fcolor;
	PROPPAGE_COLOR();
	virtual ~PROPPAGE_COLOR();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_COLOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedForecolor();
	afx_msg void OnBnClickedBgcolor();
};
