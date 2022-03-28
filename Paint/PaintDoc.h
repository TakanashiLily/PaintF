
// PaintDoc.h: CPaintDoc 類別的介面
//
#include "CGraphicObj.h"
#include "CCircleObj.h"
#include "CTriangleObj.h"
#include "CTextObj.h"

#pragma once


class CPaintDoc : public CDocument
{
private:
	CArray<CGraphicObj, CGraphicObj> gArray;
	CArray<CTextObj, CTextObj> tArray;

public:
	void AddObject(CGraphicObj& g);
	void AddObjectT(CTextObj& T);
	CGraphicObj& GetObject(int i);
	CTextObj& GetObjectT(int i);
	int GetSize();
	int GetSizeT();
	void Serialize(CArchive& ar);
	void DeleteContents();
	void RemoveAt(int i);
	void DeleteContentsT();
	void RemoveAtT(int i);


protected: // 僅從序列化建立
	CPaintDoc() noexcept;
	DECLARE_DYNCREATE(CPaintDoc)

// 屬性
public:

// 作業
public:

// 覆寫
public:
	virtual BOOL OnNewDocument();
	/*virtual void Serialize(CArchive& ar);*/
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 程式碼實作
public:
	virtual ~CPaintDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 產生的訊息對應函式
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 為搜尋處理常式設定搜尋內容的 Helper 函式
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
