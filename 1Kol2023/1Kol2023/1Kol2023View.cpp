
// 1Kol2023View.cpp : implementation of the CMy1Kol2023View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "1Kol2023.h"
#endif
#include "DImage.h"
#include "1Kol2023Doc.h"
#include "1Kol2023View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy1Kol2023View

IMPLEMENT_DYNCREATE(CMy1Kol2023View, CView)

BEGIN_MESSAGE_MAP(CMy1Kol2023View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CMy1Kol2023View construction/destruction

void CMy1Kol2023View::DrawBackground(CDC* pDC, CRect rect)
{
	this->pozadina->Draw(pDC, CRect(0, 0, pozadina->Width(), pozadina->Height()), CRect(0, 0, pozadina->Width(), pozadina->Height()));
}

void CMy1Kol2023View::DrawImgTransparent(CDC* pDC, DImage* pImage)
{
	unsigned char* byte = pImage->GetDIBBits();
	COLORREF transparent = RGB(byte[2], byte[1], byte[0]);
	pImage->DrawTransparent(pDC, CRect(0, 0, pImage->Width(), pImage->Height()), CRect(0, 0, pImage->Width(), pImage->Height()), transparent);
}

void CMy1Kol2023View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
{
	XFORM t;
	t.eM11 = 1;
	t.eM12 = 0;
	t.eM21 = 0;
	t.eM22 = 1;
	t.eDx = dX;
	t.eDy = dY;

	if (rightMultiply) {
		pDC->ModifyWorldTransform(&t, MWT_RIGHTMULTIPLY);
	}
	else {
		pDC->ModifyWorldTransform(&t, MWT_LEFTMULTIPLY);
	}
}

void CMy1Kol2023View::Rotate(CDC* pDC, float angle, bool rightMultiply)
{
	XFORM t;
	float rad = angle * (3.14f / 180.0f);
	t.eM11 = cos(rad);
	t.eM12 = sin(rad);
	t.eM21 = -sin(rad);
	t.eM22 = cos(rad);
	t.eDx = 0;
	t.eDy = 0;


	if (rightMultiply) {
		pDC->ModifyWorldTransform(&t, MWT_RIGHTMULTIPLY);
	}
	else {
		pDC->ModifyWorldTransform(&t, MWT_LEFTMULTIPLY);
	}
}

void CMy1Kol2023View::Scale(CDC* pDC, float sX, float sY, bool rightMultiply)
{
	XFORM t;
	t.eM11 = sX;
	t.eM12 = 0;
	t.eM21 = 0;
	t.eM22 = sY;
	t.eDx = 0;
	t.eDy = 0;

	if (rightMultiply) {
		pDC->ModifyWorldTransform(&t, MWT_RIGHTMULTIPLY);
	}
	else {
		pDC->ModifyWorldTransform(&t, MWT_LEFTMULTIPLY);
	}
}

void CMy1Kol2023View::point(CDC* pDC)
{
	CPen* pen = new CPen(PS_GEOMETRIC, 1, RGB(255, 0, 0));
	CPen* pOldPen = pDC->SelectObject(pen);
	pDC->Rectangle(0, 0, 10, 10);
	pDC->SelectObject(pOldPen);
}

void CMy1Kol2023View::DrawHalf(CDC* pDC)
{
	XFORM f;
	/*Scale(pDC, skaliranje, skaliranje, false);*/
	Translate(pDC, -106, 170, false);
	//point(pDC);


	DrawImgTransparent(pDC, telo);

	//uzimam prethodnu
	pDC->GetWorldTransform(&f);

	Translate(pDC, -10, 30, false);
	Translate(pDC, 35, 35, false);
	Rotate(pDC, rNadlaktica, false);
	Translate(pDC, -35, -35, false);
	

	DrawImgTransparent(pDC, nadlaktica);
	Translate(pDC, -8, 134, false);

	
	Translate(pDC, 30, 33, false);
	Rotate(pDC, rPodlaktica, false);
	Translate(pDC, -30, -33, false);


	DrawImgTransparent(pDC, podlaktica);
	Translate(pDC, 5, 137, false);


	Translate(pDC, 25, 3, false);
	Rotate(pDC, rSaka, false);
	Translate(pDC, -25, -3, false);

	DrawImgTransparent(pDC, saka);


	Translate(pDC, -5, -137, false);
	Translate(pDC, 8, -134, false);
	Translate(pDC, 10, -30, false);

	//vrati f
	pDC->SetWorldTransform(&f);

	Translate(pDC, 32, 242, false);
	DrawImgTransparent(pDC, nadkolenica);
	Translate(pDC, 5, 147, false);
	DrawImgTransparent(pDC, podkolenica);
	Translate(pDC, 5, 232, false);
	DrawImgTransparent(pDC, stopalo);
	Translate(pDC, -5, -232, false);
	Translate(pDC, -5, -147, false);
	Translate(pDC, -32, -242, false);
	
	//point(pDC);


	Translate(pDC, 106, -170, false);

}

CMy1Kol2023View::CMy1Kol2023View() noexcept
{

	glava = new DImage();
	nadkolenica = new DImage();
	nadlaktica = new DImage();
	podkolenica = new DImage();
	podlaktica = new DImage();
	saka = new DImage();
	stopalo = new DImage();
	telo = new DImage();
	pozadina = new DImage();
	glava->Load(CString("./slike/glava.png"));
	nadlaktica->Load(CString("./slike/nadlaktica.png"));
	nadkolenica->Load(CString("./slike/nadkolenica.png"));
	podkolenica->Load(CString("./slike/podkolenica.png"));
	podlaktica->Load(CString("./slike/podlaktica.png"));
	saka->Load(CString("./slike/saka.png"));
	stopalo->Load(CString("./slike/stopalo.png"));
	this->telo->Load(CString("./slike/telo.png"));
	this->pozadina->Load(CString("./slike/pozadina.jpg"));



}

void CMy1Kol2023View::DrawHead(CDC* pDC)
{
	Translate(pDC, -49, 70, false);
	DrawImgTransparent(pDC, glava);
	Translate(pDC, 49, -70, false);
}

void CMy1Kol2023View::DrawRobot(CDC* pDC)
{
	Translate(pDC, pozadina->Width() / 2, 0, false);

	/*XFORM f;
	pDC->GetWorldTransform(&f);*/

	Translate(pDC, 0, pozadina->Height() / 2, false);
	Scale(pDC, skaliranje, skaliranje, false);
	Rotate(pDC, rRobot, false);
	Translate(pDC, 0, -pozadina->Height() / 2, false);
	DrawHalf(pDC);

	Scale(pDC, -1, 1, false);
	DrawHalf(pDC);
	Scale(pDC, -1, 1, false);

	DrawHead(pDC);

	/*pDC->SetWorldTransform(&f);*/
}

CMy1Kol2023View::~CMy1Kol2023View()
{
	delete pozadina;
}

BOOL CMy1Kol2023View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMy1Kol2023View drawing

void CMy1Kol2023View::OnDraw(CDC* /*pDC*/)
{
	CMy1Kol2023Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDC* pDC = GetDC();
	CRect rect;

	



	GetClientRect(&rect);
	int oldmod = pDC->SetGraphicsMode(GM_ADVANCED);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	int memMode = memDC->SetGraphicsMode(GM_ADVANCED);
	CBitmap mem;
	mem.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	CBitmap* old = memDC->SelectObject(&mem);


	//Crtam ovde

	DrawBackground(memDC, rect);

	XFORM t;
	memDC->GetWorldTransform(&t);

	DrawRobot(memDC);
	

	memDC->SetWorldTransform(&t);


	//prekopiramo iz memdc u pdc
	pDC->BitBlt(0, 0, pozadina->Width(), pozadina->Height(), memDC, 0, 0, SRCCOPY);

	pDC->SetGraphicsMode(oldmod);
	memDC->SetGraphicsMode(memMode);

	memDC->DeleteDC();
	delete memDC;


	// TODO: add draw code for native data here
}


// CMy1Kol2023View printing

BOOL CMy1Kol2023View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy1Kol2023View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy1Kol2023View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMy1Kol2023View diagnostics

#ifdef _DEBUG
void CMy1Kol2023View::AssertValid() const
{
	CView::AssertValid();
}

void CMy1Kol2023View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy1Kol2023Doc* CMy1Kol2023View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy1Kol2023Doc)));
	return (CMy1Kol2023Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy1Kol2023View message handlers


void CMy1Kol2023View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 'G') {
		if(rNadlaktica < 90)
			rNadlaktica += 10;

		Invalidate(false);
	}
	if (nChar == 'H') {
		if(rNadlaktica > -10)
			rNadlaktica -= 10;

		Invalidate(false);

	}

	if (nChar == 'D') {
		if (rPodlaktica < 80)
			rPodlaktica += 10;

		Invalidate(false);
	}
	if (nChar == 'F') {
		if (rPodlaktica > -10)
			rPodlaktica -= 10;

		Invalidate(false);

	}

	if (nChar == 'A') {
		if (rSaka < 30)
			rSaka += 10;

		Invalidate(false);
	}
	if (nChar == 'S') {
		if (rSaka > -10)
			rSaka -= 10;

		Invalidate(false);

	}
	if (nChar == '1') {
		rRobot += 10;
		skaliranje += 0.1;

		Invalidate(false);
	}

	if (nChar == '2') {
		rRobot -= 10;
		skaliranje -= 0.1;

		Invalidate(false);
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
