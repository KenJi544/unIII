
// lab1View.cpp : implementation of the Clab1View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "lab1.h"
#endif

#include "lab1Doc.h"
#include "lab1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Clab1View

IMPLEMENT_DYNCREATE(Clab1View, CView)

BEGIN_MESSAGE_MAP(Clab1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Clab1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Clab1View construction/destruction

Clab1View::Clab1View()
{
	// TODO: add construction code here

}

Clab1View::~Clab1View()
{
}

BOOL Clab1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Clab1View drawing

void Clab1View::OnDraw(CDC* pDC)
{

	Clab1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)

		return;


		// TODO: add draw code for native data here
	//	CPen pensula(PS_SOLID, 3, RGB(123, 245, 136));
	//pDC->SelectObject(&pensula);
	//CRect rcClient;
	//GetClientRect(&rcClient);
	//rcClient.CenterPoint();

	//pDC->MoveTo(0, rcClient.CenterPoint().y);
	//pDC->LineTo(rcClient.Width(), rcClient.CenterPoint().y);
	//pDC->MoveTo(rcClient.CenterPoint().x, 0);
	//pDC->LineTo(rcClient.CenterPoint().x, rcClient.Height());

	//CPen pensula1(PS_SOLID, 3, RGB(230, 145, 236));
	//pDC->SelectObject(&pensula1);
	//for (int i = 0; i < rcClient.Width(); i = i + 6){
	//	pDC->MoveTo(i, rcClient.CenterPoint().y);
	//	pDC->LineTo(i, rcClient.CenterPoint().y - 5);
	//pDC->LineTo(i, rcClient.CenterPoint().y + 5);
		//	pDC->MoveTo(rcClient.CenterPoint().x, i);
	//pDC->LineTo(rcClient.CenterPoint().x - 5, i);
	//pDC->LineTo(rcClient.CenterPoint().x + 5, i);

		// TODO: add draw code for native data here'
		CPen pensula(PS_SOLID, 3, RGB(123, 245, 136));
	pDC->SelectObject(&pensula);
	CRect rcClient;
	GetClientRect(&rcClient);
	rcClient.CenterPoint();

	pDC->MoveTo(0, rcClient.CenterPoint().y);
	pDC->LineTo(rcClient.Width(), rcClient.CenterPoint().y);
	pDC->MoveTo(rcClient.CenterPoint().x, 0);
	pDC->LineTo(rcClient.CenterPoint().x, rcClient.Height());

	int centerX = rcClient.Width() / 2;
	int centerY = rcClient.Height() / 2;
	int interval = 8;
	int semiInt = interval/2;

	CPen pensula1(PS_SOLID, 3, RGB(230, 145, 236));
	pDC->SetPixel(rcClient.CenterPoint().x, rcClient.CenterPoint().y, RGB(255, 0, 0));
	pDC->SelectObject(&pensula1);
	for (int i = 0; i < rcClient.Width(); i = i + interval){
		if ((centerX - i<semiInt && centerX - i>=0) || (i - centerX<semiInt && i - centerX>=0)){}
		else{
			pDC->MoveTo(i, rcClient.CenterPoint().y);
			pDC->LineTo(i, rcClient.CenterPoint().y - 5);
			pDC->LineTo(i, rcClient.CenterPoint().y + 5);

		}
	}
	for (int i = 0; i < rcClient.Height(); i = i + interval){
		if ((centerY - i<semiInt && centerY - i>=0) || (i - centerY<semiInt && i - centerY>=0))
			{}
			else{
				pDC->MoveTo(rcClient.CenterPoint().x, i);
				pDC->LineTo(rcClient.CenterPoint().x - 5, i);
				pDC->LineTo(rcClient.CenterPoint().x + 5, i);
			}
		}
	}



		

	// TODO: add draw code for native data her


// Clab1View printing


void Clab1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Clab1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Clab1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Clab1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void Clab1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Clab1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Clab1View diagnostics

#ifdef _DEBUG
void Clab1View::AssertValid() const
{
	CView::AssertValid();
}

void Clab1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Clab1Doc* Clab1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Clab1Doc)));
	return (Clab1Doc*)m_pDocument;
}
#endif //_DEBUG


// Clab1View message handlers
