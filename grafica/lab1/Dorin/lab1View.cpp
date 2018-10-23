

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
#include <iostream>
#include <fstream>
using namespace std;

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

double formula(double x, double eps){
	double sum = x + 1;
	double t = x;
	double k = 2;

	do{
		t *= x / k++;

		sum += t;
		std::cout << sum << "\n";
	} while (fabs(t)>eps);
	return sum;
}




void Clab1View::OnDraw(CDC* pDC)
{
	Clab1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	ofstream myfile;
	myfile.open("fisier1.txt");
	ofstream myfile2;
	myfile2.open("fisier2.txt");

	// TODO: add draw code for native data here

	double a = -4, b = 0.98;//punem limitele
	double precizie = 0.0001;//plasam precizia
	int nseg = 300;
	double step = (b - a) / nseg;//marimea pasului
	double scalex = 320.0;//marimea axelor
	double scaley = 200.0;
	double x, y;
	double diff;


	CPen penAxa(PS_SOLID, 2, RGB(0, 0, 255));// intializam creioanele a axei si a funtiei
	CPen penFun(PS_SOLID, 1, RGB(255, 0, 0));
	CPen *pOLDPen = NULL;
	CRect rcClient;
	GetClientRect(&rcClient);// aflam centrul 
	pOLDPen = pDC->SelectObject(&penAxa);


	pDC->SelectObject(&penAxa);//desenam axa
	pDC->MoveTo(0, rcClient.CenterPoint().y);
	pDC->LineTo(rcClient.Width() - 1, rcClient.CenterPoint().y);
	pDC->MoveTo(rcClient.CenterPoint().x, 0);
	pDC->LineTo(rcClient.CenterPoint().x, rcClient.Height() - 1);


	pDC->SelectObject(&penFun);//schimbam pixul si desenam functia proprie cu lin
	x = a;
	y = formula(x, precizie);
	pDC->MoveTo(rcClient.CenterPoint().x + (int)(x*scalex), rcClient.CenterPoint().y - (int)(y*scaley));
	for (int i = 1; i <= nseg; i++)
	{
	x += step;
	y = formula(x, precizie);
	diff = exp(x) ;
	myfile2 <<   x << " \t"<< y << "\n";//tabulare
	myfile << " functia proprie x=" << x << " y=" << y << " ";
	myfile << " functia bibliotecii x=" << x << " y=" << exp(x) << " ";
	myfile << " valoarea absoluta a lui y "  << diff-y << " \n";

	pDC->LineTo(rcClient.CenterPoint().x + (int)(x*scalex), rcClient.CenterPoint().y - (int)(y*scaley));
	}
	pDC->SetTextColor(RGB(255, 0, 0));
	pDC->SetTextAlign(TA_TOP + TA_RIGHT);
	pDC->TextOutW(rcClient.Width() - 1, 0, L"y=formula(x,eps)");

	step = 0.02;
	for (x = a; x <= b; x += step){

		y = exp(x);

		pDC->SetPixel(rcClient.CenterPoint().x + (int)(x*scalex)+5, rcClient.CenterPoint().y - (int)(y*scaley)+5, RGB(0, 255, 0));


		
		
		
		
	}

	pDC->SetTextColor(RGB(0, 255, 0));
	pDC->SetTextAlign(TA_TOP + TA_LEFT);
	pDC->TextOutW(0, 0, L"y=exp(1-x)");
	myfile.close();
	myfile2.close();
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
