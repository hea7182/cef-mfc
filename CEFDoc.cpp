
// CEFDoc.cpp : implementation of the CCEFDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "cef_mfc.h"
#endif

#include "CEFDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCEFDoc

IMPLEMENT_DYNCREATE(CCEFDoc, CDocument)

BEGIN_MESSAGE_MAP(CCEFDoc, CDocument)
END_MESSAGE_MAP()


// CCEFDoc construction/destruction

CCEFDoc::CCEFDoc()
{
	// TODO: add one-time construction code here

}

CCEFDoc::~CCEFDoc()
{
}

BOOL CCEFDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CView* pView;
	POSITION pos = GetFirstViewPosition();
    if (pos != NULL)
    {
      pView = GetNextView(pos);   
    }

    CefSettings settings;
	settings.multi_threaded_message_loop = true;
	CefRefPtr<CefApp> app;
    // Initialize CEF.
    CefInitialize(settings, app);

    CefWindowInfo info;
	RECT rect;
	pView->GetClientRect(&rect);
	info.SetAsChild(pView->GetSafeHwnd(), rect);

	CefBrowserSettings browserSettings;

    CefRefPtr<CefClient> client(new ClientHandler());
	CefBrowser::CreateBrowser(info, client, L"http://www.google.com", browserSettings); 
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

// CCEFDoc serialization

void CCEFDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CCEFDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
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

// Support for Search Handlers
void CCEFDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CCEFDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCEFDoc diagnostics

#ifdef _DEBUG
void CCEFDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCEFDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCEFDoc commands
