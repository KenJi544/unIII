
// LP2View.cpp : implementation of the CLP2View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "LP2.h"
#endif

#include "LP2Doc.h"
#include "LP2View.h"
#include <fstream>
#include <iomanip>
#include <string>
#include <list>
#include <sstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLP2View

IMPLEMENT_DYNCREATE(CLP2View, CView)

BEGIN_MESSAGE_MAP(CLP2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CLP2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CLP2View construction/destruction

CLP2View::CLP2View()
{
	// TODO: add construction code here

}

CLP2View::~CLP2View()
{
}

BOOL CLP2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}


int n_de_r(string s)
{
	int n = 0;
	ifstream fin(s);
	while (!fin.eof())
	{
		getline(fin, s);
		n++;
	}
	fin.close();
	return n;
}
int n_de_c(string s)
{
	int n = 0;
	ifstream fin(s);
	getline(fin, s);
	for (unsigned int i = 0; i < s.length(); i++)
		if (s[i] == ' ')
			n++;
	fin.close();
	return n;
}
COLORREF color(int i)
{
	return RGB((i * 100 + i / 5) % 255, 6 * (i + 100) % 255, i * 150 % 255);
}
void CLP2View::OnDraw(CDC* pDC)
{
	CLP2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: äîáŕâüňĺ çäĺńü ęîä îňđčńîâęč äë˙ ńîáńňâĺííűő äŕííűő


	CRect c;
	GetClientRect(&c);
	int g1x1 = 0;
	int g1y1 = 0;
	int g1x2 = c.Width() / 2;
	int g1y2 = c.Height();
	int marx = (int)((g1x2 - g1x1)*0.005);
	int mary = (int)((g1y2 - g1y1)*0.005);

	CPen p(PS_SOLID, 1, RGB(0, 0, 0));
	CBrush b(RGB(0, 0, 0));
	CFont f;
	f.CreatePointFont((int)(c.Height()*0.1), L"comic sans ms", pDC);
	CPen *pop = pDC->SelectObject(&p);
	CBrush *pob = pDC->SelectObject(&b);
	CFont *pof = pDC->SelectObject(&f);
	pDC->SetTextAlign(TA_TOP + TA_RIGHT);
	string s("C:/datefroml2.txt");
	ifstream fin(s);

	int row = n_de_r(s) - 1;//numarul de rinduri in grafic
	int col = n_de_c(s);//numarul de coloane 
	CString str("");
	CString str1("");
	string *tab = new string[row + 1];//tabel cu toate date
	string *name = new string[row];//tabel cu denumirile la stinga
	string *metadate = new string[col + 1];//tabel cu denumirile jos
	int **date = new int*[row];//date pentru grafic
	for (int count = 0; count < row; count++)
		date[count] = new int[col];
	for (int i = 0; i < row + 1; i++)//citirea datelor
	{
		string ss;
		getline(fin, ss);
		tab[i] = ss;
	}
	int k = 0;
	string sss;
	for (unsigned int i = 0; i < tab[0].length(); i++)//prelucrarea datelor din denumirile jos
	{
		if (tab[0][i] != ' ')
		{
			sss += tab[0][i];

		}
		else
		{
			metadate[k++] = sss;
			sss = "";
		}

	}
	metadate[k++] = sss;

	for (int i = 0; i < row; i++)//prelucrarea datelor din denumirile la stinga
	{
		string ss = "";
		for (unsigned int j = 0; j < tab[i + 1].length(); j++)
			if (tab[i + 1][j] != ' ')
				ss += tab[i + 1][j];
			else break;

			name[i] = ss;

	}
	k = 0;
	int m = 0;
	for (int i = 0; i < row; i++)//prelucrarea datelor pentru grafic
	{
		string ss = "";
		for (unsigned int j = 0; j < tab[i + 1].length(); j++)
		{
			if (tab[i + 1][j] != ' ')
				ss += tab[i + 1][j];
			else
			{
				if (ss != name[i]) date[k][m++] = atoi(ss.c_str());
				ss = "";
			}
		}
		date[k++][m] = atoi(ss.c_str());
		m = 0;
	}
	int max = 0;
	for (int i = 0; i < col; i++)
	{
		int suma = 0;
		for (int j = 0; j < row; j++)
			suma += date[j][i];
		if (suma > max) max = suma;
	}



	pDC->MoveTo(g1x1, g1y1);
	pDC->LineTo(g1x1, g1y2);
	pDC->LineTo(g1x2, g1y2);
	pDC->LineTo(g1x2, g1y1);
	pDC->LineTo(g1x1, g1y1);
	pDC->MoveTo(((int)((g1x2 - g1x1)*0.1 + g1x1)), (int)(((g1y2 - g1y1)*0.80 + g1y1)));
	pDC->LineTo(((int)((g1x2 - g1x1)*0.1 + g1x1)), (int)(((g1y2 - g1y1)*0.10 + g1y1)));

	for (int i = 0; i <= max; i++)
	{
		int y = (int)(((g1y2 - g1y1)*0.80 + g1y1)) + i*((((int)((g1y2 - g1y1)*0.10) - (int)((g1y2 - g1y1)*0.80)) / max));
		int x = ((int)((g1x2 - g1x1)*0.1 + g1x1));
		pDC->MoveTo(x - marx, y);
		pDC->LineTo(x + marx, y);
		str = to_string(i).c_str();
		pDC->TextOutW(x - marx, y, str);
		CPoint a[3] =
		{
			CPoint(x,y),
			CPoint(x + 10 * marx,y - 10 * mary),
			CPoint(((int)((g1x2 - g1x1)*0.9 + g1x1)) + 10 * marx,y - 10 * mary)
		};
		pDC->Polyline(a, 3);
	}
	pDC->MoveTo(((int)((g1x2 - g1x1)*0.1 + g1x1)), (int)(((g1y2 - g1y1)*0.80) + g1y1));
	pDC->LineTo(((int)((g1x2 - g1x1)*0.9 + g1x1)), (int)(((g1y2 - g1y1)*0.80) + g1y1));
	pDC->SetTextAlign(TA_TOP + TA_LEFT);
	for (int i = 1; i < col + 1; i++)
	{


		str = metadate[i].c_str();
		int x = (int)((g1x2 - g1x1)*0.1 + g1x1) + i*(((int)((g1x2 - g1x1)*0.9 + g1x1) - (int)((g1x2 - g1x1)*0.1 + g1x1)) / col);
		int y = (int)(((g1y2 - g1y1)*0.80) + g1y1);
		int y1 = y;
		int contor = 0;
		pDC->TextOutW(x - (((int)((g1x2 - g1x1)*0.9 + g1x1) - (int)((g1x2 - g1x1)*0.1 + g1x1)) / col) *0.4, y + mary, str);

		for (int j = 0; j < row; j++)
		{

			b.DeleteObject();
			b.CreateSolidBrush(color(date[j][0] + j * 7 - j % 2));
			pDC->SelectObject(&b);
			y1 += (int)(date[j][i - 1] * ((((int)((g1y2 - g1y1)*0.10) - (int)((g1y2 - g1y1)*0.80)) / max)));
			pDC->Rectangle(x, y1 - (int)(date[j][i - 1] * ((((int)((g1y2 - g1y1)*0.10) - (int)((g1y2 - g1y1)*0.80)) / max))), x - 30 * marx, y1);

			CPoint a[6] = {
				CPoint(x,y1 - (int)(date[j][i - 1] * ((((int)((g1y2 - g1y1)*0.10) - (int)((g1y2 - g1y1)*0.80)) / max)))),
				CPoint(x,y1),
				CPoint(x - 30 * marx,y1),
				CPoint(x - 30 * marx + marx * 10,y1 - mary * 10),
				CPoint(x + marx * 10,y1 - mary * 10),
				CPoint(x + marx * 10,(y1 - (int)(date[j][i - 1] * ((((int)((g1y2 - g1y1)*0.10) - (int)((g1y2 - g1y1)*0.80)) / max)))) - mary * 10)

			};
			pDC->Polygon(a, 6);
			pDC->MoveTo(x, y1);
			pDC->LineTo(x + marx * 10, y1 - mary * 10);
		}
	}
	for (int i = 0; i < row; i++)
	{
		int x = g1x1 + i*((g1x2 - g1x1)*0.9) / row + (g1x2 - g1x1)*0.05;
		int y = (int)(((g1y2 - g1y1)*0.90) + g1y1);
		b.DeleteObject();
		b.CreateSolidBrush(color(date[i][0] + i * 7 - i % 2));
		pDC->SelectObject(&b);
		pDC->Rectangle(x, y, x + marx * 5, y + mary * 5);
		str = name[i].c_str();
		pDC->TextOutW(x + marx * 6, y, str);

	}

	int g2x1 = c.Width() / 2;
	int g2y1 = 0;
	int g2x2 = c.Width();
	int g2y2 = c.Height();
	double stangle, endagle, ungrad;
	double pi = 4.0*atan(1.0);
	double radiusx = min((g2x2 - g2x1), (g2y2 - g2y1)) / 4;
	double radiusy = radiusx / 2;
	double suma;
	CPoint ptCenter, ptStart, ptEnd;


	p.DeleteObject();
	p.CreatePen(BS_SOLID, 1, RGB(0, 0, 0));
	pDC->SelectObject(&p);
	pDC->MoveTo(g2x1, g2y1);
	pDC->LineTo(g2x1, g2y2);
	pDC->LineTo(g2x2, g2y2);
	pDC->LineTo(g2x2, g2y1);
	pDC->LineTo(g2x1, g2y1);
	suma = 0;
	for (int i = 0; i <row; i++)
		suma += date[i][0];
	for (int j = -(mary * 10); j <= (mary * 10); j++)
	{

		ptCenter = CPoint((g2x2 + g2x1) / 2, (g2y2 + g2y1) / 2 - j);



		stangle = 0;

		for (int i = 0; i < row; i++)
		{
			b.DeleteObject();
			b.CreateSolidBrush(color(date[i][0] + i * 7 - i % 2));
			pDC->SelectObject(&b);
			if (abs(j) != mary * 10)
			{
				p.DeleteObject();
				p.CreatePen(BS_SOLID, 1, color(date[i][0] + i * 7 - i % 2));
				pDC->SelectObject(&p);
			}
			else
			{
				p.DeleteObject();
				p.CreatePen(BS_SOLID, 1, RGB(0, 0, 0));
				pDC->SelectObject(&p);
			}
			int idate = date[i][0];
			endagle = (i < row) ? stangle + idate * 360 / suma : 360;
			int y;
			int x;
			if (idate * 360 / suma<180)
				x = (ptCenter.x + (int)marx * 10 * cos(pi / 180 * stangle) + ptCenter.x + (int)marx * 10 * cos(pi / 180 * endagle)) / 2;
			else
				x = (ptCenter.x - (int)marx * 10 * cos(pi / 180 * stangle) + ptCenter.x - (int)marx * 10 * cos(pi / 180 * endagle)) / 2;
			if (idate * 360 / suma<180)
				y = ((ptCenter.y - (int)mary * 10 * sin(pi / 180 * stangle)) + (ptCenter.y - (int)mary * 10 * sin(pi / 180 * endagle))) / 2;
			else
				y = ((ptCenter.y + (int)mary * 10 * sin(pi / 180 * stangle)) + (ptCenter.y + (int)mary * 10 * sin(pi / 180 * endagle))) / 2;
			ungrad = pi / 180 * stangle;
			CPoint pt = CPoint(x, y);
			ptStart = CPoint(pt.x + (int)radiusx*cos(ungrad), pt.y - (int)radiusy*sin(ungrad));

			ungrad = pi / 180 * endagle;


			CRect rcPie(pt, pt);
			rcPie.InflateRect(radiusx, radiusy);
			ptEnd = CPoint(pt.x + (int)radiusx*cos(ungrad), pt.y - (int)radiusy*sin(ungrad));
			pDC->Pie(rcPie, ptStart, ptEnd);
			stangle = endagle;
			pDC->SetPixel(ptStart, RGB(0, 0, 0));
			pDC->SetPixel(ptEnd, RGB(0, 0, 0));
			pDC->SetPixel(pt, RGB(0, 0, 0));

		}
	}



	pDC->SelectObject(&pop);
	pDC->SelectObject(&pob);
	pDC->SelectObject(&pof);
	fin.close();

}


// CLP2View printing


void CLP2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CLP2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLP2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLP2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLP2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLP2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CLP2View diagnostics

#ifdef _DEBUG
void CLP2View::AssertValid() const
{
	CView::AssertValid();
}

void CLP2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLP2Doc* CLP2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLP2Doc)));
	return (CLP2Doc*)m_pDocument;
}
#endif //_DEBUG


// CLP2View message handlers
