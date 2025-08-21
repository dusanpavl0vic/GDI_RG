
// 1Kol2018View.cpp : implementation of the CMy1Kol2018View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "1Kol2018.h"
#endif

#include "1Kol2018Doc.h"
#include "1Kol2018View.h"

#include "DImage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy1Kol2018View

IMPLEMENT_DYNCREATE(CMy1Kol2018View, CView)

BEGIN_MESSAGE_MAP(CMy1Kol2018View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CMy1Kol2018View construction/destruction

void CMy1Kol2018View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
{
	XFORM f;
	f.eM11 = 1;
	f.eM12 = 0;
	f.eM21 = 0;
	f.eM22 = 1;
	f.eDx = dX;
	f.eDy = dY;

	if (rightMultiply)
		pDC->ModifyWorldTransform(&f, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&f, MWT_LEFTMULTIPLY);

}

void CMy1Kol2018View::Rotate(CDC* pDC, float angle, bool rightMultiply)
{
	XFORM f;
	float rad = angle * 3.14 / 180;
	f.eM11 = cos(rad);
	f.eM12 = sin(rad);
	f.eM21 = -sin(rad);
	f.eM22 = cos(rad);
	f.eDx = 0;
	f.eDy = 0;

	if (rightMultiply)
		pDC->ModifyWorldTransform(&f, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&f, MWT_LEFTMULTIPLY);
}

void CMy1Kol2018View::Scale(CDC* pDC, float sX, float sY, bool rightMultiply)
{
	XFORM f;
	f.eM11 = sX;
	f.eM12 = 0;
	f.eM21 = 0;
	f.eM22 = sY;
	f.eDx = 0;
	f.eDy = 0;

	if (rightMultiply)
		pDC->ModifyWorldTransform(&f, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&f, MWT_LEFTMULTIPLY);
}

void CMy1Kol2018View::DrawBackground(CDC* pDC)
{
	CRect rect;

	GetClientRect(&rect);
	int x = (rect.Width() - pozadina->Width()) / 2;
	int y = rect.Height() - pozadina->Height();


	pozadina->Draw(pDC, CRect(0, 0, pozadina->Width(), pozadina->Height()), CRect(x, y, x + pozadina->Width(), y + pozadina->Height()));
}

void CMy1Kol2018View::DrawImgTransparent(CDC* pDC, DImage* pImage)
{
	unsigned char* b = pImage->GetDIBBits();
	COLORREF t = RGB(b[2], b[1], b[0]);
	pImage->DrawTransparent(pDC, CRect(0, 0, pImage->Width(), pImage->Height()), CRect(0, 0, pImage->Width(), pImage->Height()), t);
}

void CMy1Kol2018View::point(CDC* pDC)
{
	CPen* pen = new CPen(PS_GEOMETRIC, 1, RGB(255, 0, 0));
	CPen* old = pDC->SelectObject(pen);

	pDC->Rectangle(0, 0, 10, 10);

	pDC->SelectObject(old);
}

void CMy1Kol2018View::DrawExcavator(CDC* pDC)
{
	CRect rect;

	GetClientRect(&rect);
	XFORM f;
	pDC->GetWorldTransform(&f);

	Translate(pDC, rect.Width() - 371 - xBager, rect.Height() - 301, false);
	DrawBody(pDC);
	DrawArm1(pDC);
	DrawArm2(pDC);
	DrawFork(pDC);




	pDC->SetWorldTransform(&f);
}

void CMy1Kol2018View::DrawBody(CDC* pDC)
{
	DrawImgTransparent(pDC, bager);
	Translate(pDC, 65, 165, false);
	point(pDC);
}

void CMy1Kol2018View::DrawArm1(CDC* pDC)
{

	Rotate(pDC, -90 - arm1R, false);
	Translate(pDC, -58, -61, false);
	DrawImgTransparent(pDC, arm1);
	//point(pDC);
	
	Translate(pDC, 309, 61, false);
	point(pDC);

}

void CMy1Kol2018View::DrawArm2(CDC* pDC)
{
	Rotate(pDC, -90 - arm2R, false);
	Translate(pDC, -36, -40, false);
	DrawImgTransparent(pDC, arm2);
	Translate(pDC, 272, 40, false);

	point(pDC);


}
void CMy1Kol2018View::DrawFork(CDC* pDC)
{
	//ENHMETAHEADER header;
	//GetEnhMetaFileHeader(viljuska, sizeof(ENHMETAHEADER), &header);
	//Rotate(pDC, -90 + viljuskaR, false);
	//Translate(pDC, 0, -20, false);
	//Scale(pDC, 2.5, 2.5, false);
	//pDC->PlayMetaFile(viljuska, CRect(header.rclBounds.left, header.rclBounds.top, header.rclBounds.right, header.rclBounds.bottom));
	//

	///*Translate(pDC, 14, 20, false);
	//Translate(pDC, -14, -20, false);*/
	CPen* pen = new CPen(PS_GEOMETRIC, 1, RGB(255, 0, 0));
	CPen* old = pDC->SelectObject(pen);
	

	CRect rect = CRect(0, 0, 200, 200);

	int width = rect.Width();      // Širina duha
	int height = rect.Height();    // Visina duha

	// Poluprečnici za lukove
	int rTop = width / 2;          // Poluprečnik za gornji luk (polovina širine)
	int rBottom = rTop / 6;        // Poluprečnik za donje talase

	// Koordinate za crtanje
	int xCenter = rect.left + width / 2; // Središte duha po x osi
	int yTop = rect.top;                 // Gornja ivica
	int yBottom = rect.bottom;           // Donja ivica

	// 1. Crtanje gornjeg dela duha (polukrug)
	pDC->Rectangle(rect);
	pDC->Chord(rect.left, rect.top, rect.right, rect.top + rect.bottom, rect.left, rect.top + rTop, rect.right, rect.top + rTop);
	pDC->SelectObject(old);
}
CMy1Kol2018View::CMy1Kol2018View() noexcept
{
	bager = new DImage();
	arm1 = new DImage();
	arm2 = new DImage();
	pozadina = new DImage();

	bager->Load(CString("./slike/bager.png"));
	arm1->Load(CString("./slike/arm1.png"));
	arm2->Load(CString("./slike/arm2.png"));
	pozadina->Load(CString("./slike/pozadina.png"));

	viljuska = GetEnhMetaFile(CString("./slike/viljuska.emf"));

}

CMy1Kol2018View::~CMy1Kol2018View()
{
	delete bager;
	delete arm1;
	delete arm2;
	delete pozadina;

}

BOOL CMy1Kol2018View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMy1Kol2018View drawing

void CMy1Kol2018View::OnDraw(CDC* /*pDC*/)
{
	CMy1Kol2018Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDC* pDC = GetDC();
	int oldM = pDC->SetGraphicsMode(GM_ADVANCED);

	CRect rect;
	GetClientRect(&rect);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	int modeM = memDC->SetGraphicsMode(GM_ADVANCED);

	CBitmap mem;
	mem.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	CBitmap* old = memDC->SelectObject(&mem);

	//Crtanje
	DrawBackground(memDC);
	XFORM f;
	memDC->GetWorldTransform(&f);

	DrawExcavator(memDC);



	memDC->SetWorldTransform(&f);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0,  SRCCOPY);

	pDC->SetGraphicsMode(oldM);
	memDC->SetGraphicsMode(modeM);

	memDC->DeleteDC();
	delete memDC;

	// TODO: add draw code for native data here
}


// CMy1Kol2018View printing

BOOL CMy1Kol2018View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy1Kol2018View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy1Kol2018View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMy1Kol2018View diagnostics

#ifdef _DEBUG
void CMy1Kol2018View::AssertValid() const
{
	CView::AssertValid();
}

void CMy1Kol2018View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy1Kol2018Doc* CMy1Kol2018View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy1Kol2018Doc)));
	return (CMy1Kol2018Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy1Kol2018View message handlers


void CMy1Kol2018View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
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
		viljuskaR += 10;

		Invalidate(false);
	}
	if (nChar == '6') {
		viljuskaR -= 10;

		Invalidate(false);
	}
	if (nChar == VK_LEFT) {
		xBager += 10;

		Invalidate(false);
	}
	if (nChar == VK_RIGHT) {
		xBager -= 10;

		Invalidate(false);
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
