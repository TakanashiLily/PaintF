
// PaintDoc.cpp: CPaintDoc 類別的實作
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以定義在實作預覽、縮圖和搜尋篩選條件處理常式的
// ATL 專案中，並允許與該專案共用文件程式碼。
#ifndef SHARED_HANDLERS
#include "Paint.h"
#endif

#include "PaintDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPaintDoc

IMPLEMENT_DYNCREATE(CPaintDoc, CDocument)

BEGIN_MESSAGE_MAP(CPaintDoc, CDocument)
END_MESSAGE_MAP()


// CPaintDoc 建構/解構

CPaintDoc::CPaintDoc() noexcept
{
	// TODO: 在此加入一次建構程式碼

}


CPaintDoc::~CPaintDoc()
{
}

BOOL CPaintDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此加入重新初始化程式碼
	// (SDI 文件會重用此文件)

	return TRUE;
}




// CPaintDoc 序列化
/*
void CPaintDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此加入儲存程式碼
	}
	else
	{
		// TODO: 在此加入載入程式碼
	}
}

*/

void CPaintDoc::AddObject(CGraphicObj& g)
{
	SetModifiedFlag(true);
	gArray.Add(g);
}


CGraphicObj& CPaintDoc::GetObject(int i)
{
	return gArray[i];
}

int CPaintDoc::GetSize()
{
	return gArray.GetSize();
}

void CPaintDoc::AddObjectT(CTextObj& abc)
{
	SetModifiedFlag(true);
	tArray.Add(abc);
}


CTextObj& CPaintDoc::GetObjectT(int i)
{
	return tArray[i];
}

int CPaintDoc::GetSizeT()
{
	return tArray.GetSize();
}

void CPaintDoc::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	gArray.Serialize(ar);
	tArray.Serialize(ar);
}

void CPaintDoc::DeleteContents()
{
	gArray.RemoveAll();
	CDocument::DeleteContents();
}

void CPaintDoc::RemoveAt(int i)
{
	gArray.RemoveAt(i);
}

void CPaintDoc::DeleteContentsT()
{
	tArray.RemoveAll();
	CDocument::DeleteContents();
}

void CPaintDoc::RemoveAtT(int i)
{
	tArray.RemoveAt(i);
}

#ifdef SHARED_HANDLERS

// 縮圖的支援
void CPaintDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改這段程式碼以繪製文件的資料
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜尋處理常式的支援
void CPaintDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 設定來自文件資料的搜尋內容。
	// 內容部分應該以 ";" 隔開

	// 範例:     strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CPaintDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CPaintDoc 診斷

#ifdef _DEBUG
void CPaintDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPaintDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPaintDoc 命令
