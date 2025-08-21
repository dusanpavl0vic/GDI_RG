
// 1Kol2022View.cpp : implementation of the CMy1Kol2022View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "1Kol2022.h"
#endif

#include "1Kol2022Doc.h"
#include "1Kol2022View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "DImage.h"

// CMy1Kol2022View

IMPLEMENT_DYNCREATE(CMy1Kol2022View, CView)

BEGIN_MESSAGE_MAP(CMy1Kol2022View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CMy1Kol2022View construction/destruction

void CMy1Kol2022View::DrawBackground(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	int imgWidth = pozadina->Width();
	int imgHeight = pozadina->Height();

	int x = (rect.Width() - imgWidth) / 2;
	int y = rect.Height() - imgHeight;

	CRect srcRect(0, 0, imgWidth, imgHeight);
	CRect destRect(x, y, x + imgWidth, y + imgHeight);

	pozadina->Draw(pDC, srcRect, destRect);
}

void CMy1Kol2022View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
{
	XFORM f;
	f.eM11 = 1;
	f.eM12 = 0;
	f.eM21 = 0;
	f.eM22 = 1;
	f.eDx = dX;
	f.eDy = dY;

	if (rightMultiply) {
		pDC->ModifyWorldTransform(&f, MWT_RIGHTMULTIPLY);
	}
	else {
		pDC->ModifyWorldTransform(&f, MWT_LEFTMULTIPLY);
	}
}

void CMy1Kol2022View::Rotate(CDC* pDC, float angle, bool rightMultiply)
{
	XFORM f;
	float rad = angle * (3.14 / 180);
	f.eM11 = cos(rad);
	f.eM12 = sin(rad);
	f.eM21 = -sin(rad);
	f.eM22 = cos(rad);
	f.eDx = 0;
	f.eDy = 0;

	if (rightMultiply) {
		pDC->ModifyWorldTransform(&f, MWT_RIGHTMULTIPLY);
	}
	else {
		pDC->ModifyWorldTransform(&f, MWT_LEFTMULTIPLY);
	}
}

void CMy1Kol2022View::Scale(CDC* pDC, float sX, float sY, bool rightMultiply)
{
	XFORM f;
	f.eM11 = sX;
	f.eM12 = 0;
	f.eM21 = 0;
	f.eM22 = sY;
	f.eDx = 0;
	f.eDy = 0;

	if (rightMultiply) {
		pDC->ModifyWorldTransform(&f, MWT_RIGHTMULTIPLY);
	}
	else {
		pDC->ModifyWorldTransform(&f, MWT_LEFTMULTIPLY);
	}
}

void CMy1Kol2022View::DrawImgTransparent(CDC* pDC, DImage* pImage)
{
	unsigned char* bajt = pImage->GetDIBBits();
	COLORREF transparent = RGB(bajt[2], bajt[1], bajt[0]);
	pImage->DrawTransparent(pDC, CRect(0, 0, pImage->Width(), pImage->Height()), CRect(0, 0, pImage->Width(), pImage->Height()), transparent);
}

void CMy1Kol2022View::point(CDC* pDC)
{
	CPen* pen = new CPen(PS_GEOMETRIC, 1, RGB(255, 0, 0));
	CPen* oldPen = pDC->SelectObject(pen);

	pDC->Rectangle(0, 0, 10, 10);

	pDC->SelectObject(oldPen);

}

void CMy1Kol2022View::DrawLamp(CDC* pDC, bool bIsShadow)
{
	XFORM f;
	pDC->GetWorldTransform(&f);
	
	DrawLampBase(pDC, bIsShadow);
	DrawLampArm1(pDC, bIsShadow);
	DrawLampArm2(pDC, bIsShadow);
	DrawLampHead(pDC, bIsShadow);
	pDC->SetWorldTransform(&f);
	//point(pDC);
}

void CMy1Kol2022View::DrawLampBase(CDC* pDC, bool bIsShadow)
{

	Translate(pDC, 700, 450, false);

	if (bIsShadow)
		DrawImgTransparent(pDC, base);
	else
		DrawImgTransparent(pDC, base_shadow);
	//point(pDC);

}

void CMy1Kol2022View::DrawLampArm1(CDC* pDC, bool bIsShadow)
{
	Translate(pDC, 102, -31, false);
	Translate(pDC, 58, 61, false);
	Rotate(pDC, -45 - arm1R, false);
	Translate(pDC, -58, -61, false);

	if (bIsShadow) {
		DrawImgTransparent(pDC, arm1);
	}
	else {
		DrawImgTransparent(pDC, arm1_shadow);
	}
	Translate(pDC, 309, 61, false);
}

void CMy1Kol2022View::DrawLampArm2(CDC* pDC, bool bIsShadow)
{
	//point(pDC);
	Rotate(pDC, arm2R - 90, false);
	Translate(pDC, -36, -40, false);
	//DrawImgTransparent(pDC, arm2);
	Translate(pDC, 272, 40, false);

}

void CMy1Kol2022View::DrawLampHead(CDC* pDC, bool bIsShadow)
{

	XFORM f;
	pDC->GetWorldTransform(&f);
	Rotate(pDC, -180 - headR, false);
	Translate(pDC, -178, -100, false);
	if (bIsShadow) {
		DrawImgTransparent(pDC, head);
	}
	else {
		DrawImgTransparent(pDC, head_shadow);
	}
	Translate(pDC, 178, 100, false);
	Translate(pDC, 178, 100, false);

	pDC->SetWorldTransform(&f);
	Translate(pDC, -272, -40, false);
	if (bIsShadow) {
		DrawImgTransparent(pDC, arm2);
	}
	else {
		DrawImgTransparent(pDC, arm2_shadow);
	}
	//point(pDC);
}

void CMy1Kol2022View::DrawLampShadow(CDC* pDC)
{

	XFORM f;
	pDC->GetWorldTransform(&f);

	Translate(pDC, 700, 450, false);
	Translate(pDC, 80, 68, false);
	Scale(pDC, 1, 0.25, false);
	Rotate(pDC, -90, false);
	//point(pDC);
	Translate(pDC, -700, -450, false);
	Translate(pDC, -80, -68, false);
	DrawLamp(pDC, false);
	pDC->SetWorldTransform(&f);

}

CMy1Kol2022View::CMy1Kol2022View() noexcept
{
	base = new DImage();
	arm1 = new DImage();
	arm2 = new DImage();
	head = new DImage();
	pozadina = new DImage();
	base_shadow = new DImage();
	arm1_shadow = new DImage();
	arm2_shadow = new DImage();
	head_shadow = new DImage();

	base->Load(CString("./slike/base.png"));
	arm1->Load(CString("./slike/arm1.png"));
	arm2->Load(CString("./slike/arm2.png"));
	head->Load(CString("./slike/head.png"));
	pozadina->Load(CString("./slike/pozadina.jpg"));
	base_shadow->Load(CString("./slike/base_shadow.png"));
	arm1_shadow->Load(CString("./slike/arm1_shadow.png"));
	arm2_shadow->Load(CString("./slike/arm2_shadow.png"));
	head_shadow->Load(CString("./slike/head_shadow.png"));

}

CMy1Kol2022View::~CMy1Kol2022View()
{
	delete base;
	delete arm1;
	delete arm2;
	delete head;
	delete pozadina;
	delete base_shadow;
	delete arm1_shadow;
	delete arm2_shadow;
	delete head_shadow;
}

BOOL CMy1Kol2022View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMy1Kol2022View drawing

void CMy1Kol2022View::OnDraw(CDC* /*pDC*/)
{
	CMy1Kol2022Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDC* pDC = GetDC();

	CRect rect;
	GetClientRect(&rect);

	int oldGM = pDC->SetGraphicsMode(GM_ADVANCED);


	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	int memGM = memDC->SetGraphicsMode(GM_ADVANCED);

	CBitmap mem;
	mem.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	memDC->SelectObject(mem);


	XFORM t;
	memDC->GetWorldTransform(&t);
	DrawBackground(memDC);

	DrawLampShadow(memDC);
	DrawLamp(memDC, true);

	memDC->SetWorldTransform(&t);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->SelectObject(&memGM);
	pDC->SelectObject(&oldGM);

	memDC->DeleteDC();
	delete memDC;

	// TODO: add draw code for native data here
}


// CMy1Kol2022View printing

BOOL CMy1Kol2022View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy1Kol2022View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy1Kol2022View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMy1Kol2022View diagnostics

#ifdef _DEBUG
void CMy1Kol2022View::AssertValid() const
{
	CView::AssertValid();
}

void CMy1Kol2022View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy1Kol2022Doc* CMy1Kol2022View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy1Kol2022Doc)));
	return (CMy1Kol2022Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy1Kol2022View message handlers


void CMy1Kol2022View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == '1') {
		arm1R += 10;

		Invalidate(false);
	}
	if (nChar == '2') {
		arm1R -= 10;

		Invalidate(false);
	}
	if (nChar == '3') {
		arm2R += 10;

		Invalidate(false);
	}
	if (nChar == '4') {
		arm2R -= 10;

		Invalidate(false);
	}
	if (nChar == '5') {
		headR += 10;

		Invalidate(false);
	}
	if (nChar == '6') {
		headR -= 10;

		Invalidate(false);
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
