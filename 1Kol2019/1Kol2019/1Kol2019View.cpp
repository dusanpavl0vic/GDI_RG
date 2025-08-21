
// 1Kol2019View.cpp : implementation of the CMy1Kol2019View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "1Kol2019.h"
#endif

#include "1Kol2019Doc.h"
#include "1Kol2019View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "DImage.h"
// CMy1Kol2019View

IMPLEMENT_DYNCREATE(CMy1Kol2019View, CView)

BEGIN_MESSAGE_MAP(CMy1Kol2019View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CMy1Kol2019View construction/destruction

void CMy1Kol2019View::DrawBackground(CDC* pDC, CRect rc)
{
	this->background->Draw(pDC, CRect(0, 0, this->background->Width(), this->background->Height()), CRect(0, 0, this->background->Width(), this->background->Height()));
}

void CMy1Kol2019View::DrawImgTransparent(CDC* pDC, DImage* pImage)
{
	unsigned char* bajtovi = pImage->GetDIBBits();
	COLORREF transparent = RGB(bajtovi[2], bajtovi[1], bajtovi[0]);
	pImage->DrawTransparent(pDC, CRect(0, 0, pImage->Width(), pImage->Height()), CRect(0, 0, pImage->Width(), pImage->Height()), transparent);
}

void CMy1Kol2019View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
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

void CMy1Kol2019View::Rotate(CDC* pDC, float angle, bool rightMultiply)
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

void CMy1Kol2019View::Scale(CDC* pDC, float sX, float sY, bool rightMultiply)
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

void CMy1Kol2019View::DrawArm1(CDC* pDC)
{
	XFORM old;
	pDC->GetWorldTransform(&old);

	
	
	DrawImgTransparent(pDC, arm1);
	pDC->SetWorldTransform(&old);
	
}

void CMy1Kol2019View::DrawArm2(CDC* pDC)
{
	
	XFORM old;
	pDC->GetWorldTransform(&old);
	
	Translate(pDC, 210, 102, false);
	Rotate(pDC, 180, false);
	Rotate(pDC, arm2R, false);
	Translate(pDC, -23, -61, false);
	DrawImgTransparent(pDC, arm2);
	Translate(pDC, 23, 61, false);
	Translate(pDC, -210, -102, false);

	pDC->SetWorldTransform(&old);


}

void CMy1Kol2019View::DrawBody1(CDC* pDC)
{
	XFORM old;
	pDC->GetWorldTransform(&old);

	DrawImgTransparent(pDC, body1);

	pDC->SetWorldTransform(&old);
}

void CMy1Kol2019View::DrawLeg1(CDC* pDC)
{
	XFORM old;
	pDC->GetWorldTransform(&old);

	DrawImgTransparent(pDC, leg1);

	pDC->SetWorldTransform(&old);
}

void CMy1Kol2019View::DrawLeg2(CDC* pDC)
{
	XFORM old;
	pDC->GetWorldTransform(&old);

	DrawImgTransparent(pDC, leg2);

	pDC->SetWorldTransform(&old);
}

void CMy1Kol2019View::DrawTransformer(CDC* pDC)
{
	XFORM old;
	pDC->GetWorldTransform(&old);

	Translate(pDC, 380, 380, false);

	XFORM old2;
	pDC->GetWorldTransform(&old2);

	Translate(pDC, -220, 70, false);
	Translate(pDC, 35, 60, false);
	Rotate(pDC, leg2R, false);
	Translate(pDC, -36, -60, false);
	DrawLeg2(pDC);
	Translate(pDC, 220, -70, false);

	pDC->SetWorldTransform(&old2);


	Translate(pDC, -215, 5, false);
	Translate(pDC, 30, 125, false);
	Rotate(pDC, leg1R, false);
	Translate(pDC, -30, -125, false);
	DrawLeg1(pDC);
	Translate(pDC, 215, -5, false);

	


	Translate(pDC, 26, 133, false);
	Rotate(pDC, body1R, false);
	Translate(pDC, -26, -133, false);

	DrawBody1(pDC);

	Translate(pDC, 180, 55, false);

	Translate(pDC, 34, 31, false);
	Rotate(pDC, arm1R, false);
	Translate(pDC, -34, -31, false);
	DrawArm2(pDC);
	DrawArm1(pDC);


	Translate(pDC, -180, -55, false);


	pDC->SetWorldTransform(&old);


}

CMy1Kol2019View::CMy1Kol2019View() noexcept
{
	// TODO: add construction code here
	body1 = new DImage();
	arm1 = new DImage();
	arm2 = new DImage();
	leg1 = new DImage();
	leg2 = new DImage();
	this->background = new DImage();

	body1->Load(CString("./slike/body1.png"));
	arm1->Load(CString("./slike/arm1.png"));
	arm2->Load(CString("./slike/arm2.png"));
	leg1->Load(CString("./slike/leg1.png"));
	leg2->Load(CString("./slike/leg2.png"));
	this->background->Load(CString("./slike/background.jpg"));

	

}

CMy1Kol2019View::~CMy1Kol2019View()
{
}

BOOL CMy1Kol2019View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMy1Kol2019View drawing

void CMy1Kol2019View::OnDraw(CDC* /*pDC*/)
{
	CMy1Kol2019Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDC* pDC = GetDC();
	int oldMode = pDC->SetGraphicsMode(GM_ADVANCED);
	CRect rect;
	GetClientRect(&rect);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	int memOldMode = memDC->SetGraphicsMode(GM_ADVANCED);

	CBitmap memB;
	memB.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	CBitmap* oldM = memDC->SelectObject(&memB);
	
	
	//crtamo ovde

	DrawBackground(memDC, rect);
	DrawTransformer(memDC);
	


	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	pDC->SelectObject(&oldMode);
	memDC->SelectObject(&memOldMode);

	memDC->DeleteDC();
	delete memDC;
	// TODO: add draw code for native data here
}


// CMy1Kol2019View printing

BOOL CMy1Kol2019View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy1Kol2019View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy1Kol2019View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMy1Kol2019View diagnostics

#ifdef _DEBUG
void CMy1Kol2019View::AssertValid() const
{
	CView::AssertValid();
}

void CMy1Kol2019View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy1Kol2019Doc* CMy1Kol2019View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy1Kol2019Doc)));
	return (CMy1Kol2019Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy1Kol2019View message handlers


void CMy1Kol2019View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == 'Q') {
		arm1R -= 27;
		leg1R -= 10;
		

		Invalidate(false);
	}
	if (nChar == 'A') {
		arm1R += 27;
		leg1R += 10;

		Invalidate(false);
	}

	if (nChar == 'T') {
		arm2R -= 10;

		Invalidate(false);
	}
	if (nChar == 'G') {
		arm2R += 10;

		Invalidate(false);
	}
	if (nChar == 'W') {
		body1R -= 10;

		Invalidate(false);
	}
	if (nChar == 'S') {
		body1R += 10;

		Invalidate(false);
	}
	if (nChar == 'R') {
		leg2R -= 10;

		Invalidate(false);
	}
	if (nChar == 'F') {
		leg2R += 10;

		Invalidate(false);
	}

	if (nChar == VK_LEFT) {
		if (arm1R > -270 && leg1R > -100 && body1R < 10 && leg2R < 100 && arm2R > -260) {
			arm1R -= 27;
			leg1R -= 10;
			body1R += 1;
			leg2R += 10;
			arm2R -= 26;

			Invalidate(false);
		}
	}
	if (nChar == VK_RIGHT) {
		if (arm1R < 0 && leg1R < 0 && body1R > 0 && leg2R > 0 && arm2R < 0) {
			arm1R += 27;
			leg1R += 10;
			body1R -= 1;
			leg2R -= 10;
			arm2R += 26;

			Invalidate(false);
			//260
		}
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
