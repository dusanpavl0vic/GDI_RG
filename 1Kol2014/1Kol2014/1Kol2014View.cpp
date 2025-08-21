
// 1Kol2014View.cpp : implementation of the CMy1Kol2014View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "1Kol2014.h"
#endif


#include "DImage.h"
#include "1Kol2014Doc.h"
#include "1Kol2014View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy1Kol2014View

IMPLEMENT_DYNCREATE(CMy1Kol2014View, CView)

BEGIN_MESSAGE_MAP(CMy1Kol2014View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CMy1Kol2014View construction/destruction

CMy1Kol2014View::CMy1Kol2014View() noexcept
{
	// TODO: add construction code here
	m_pTocak = new DImage();
	m_pTocak->Load(CString("./slike/Wheel.png"));
	m_met = GetEnhMetaFile(CString("./slike/clio.emf"));

}

CMy1Kol2014View::~CMy1Kol2014View()
{
}

BOOL CMy1Kol2014View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}
void CMy1Kol2014View::DrawCar(CDC* pDC, int x, int y, int w, int h, float angle)
{
	pDC->PlayMetaFile(m_met, CRect(x + w / 2, y - h / 2, x - w / 2, y + h / 2));
}

void CMy1Kol2014View::DrawGround(CDC* pDC, float angle)
{
	CRect rect;
	GetClientRect(&rect);

	CPen* pen = new CPen(PS_GEOMETRIC | PS_SOLID, 3, RGB(128, 32, 32));
	CBrush* brush = new CBrush(HS_FDIAGONAL, RGB(128, 32, 32));

	CPen* penO = pDC->SelectObject(pen);
	CBrush* bO = pDC->SelectObject(brush);

	POINT pts[3];
	pts[0].x = rect.left;
	pts[0].y = rect.bottom;
	pts[1].x = rect.right;
	pts[1].y = rect.bottom;
	pts[2].x = rect.right;
	pts[2].y = rect.bottom - rect.Width()*tan(angle * 3.14/180);
	COLORREF bg = pDC->SetBkColor(RGB(220, 255, 192));

	pDC->Polygon(pts, 3);

	pDC->SetBkColor(bg);
	pDC->SelectObject(penO);
	pDC->SelectObject(bO);
}

void CMy1Kol2014View::DrawWheel(CDC* pDC, int x, int y, int r, float angle)
{
	XFORM transOld;
	pDC->GetWorldTransform(&transOld);
	Translate(pDC, x, y, false); // MWT_LEFTMULTIPLY
	Rotate(pDC, angle, false); // MWT_LEFTMULTIPLY
	int dx = 52, dy = 15, w = 376;
	CRect srcRc(dx, dy, dx + w, dy + w);
	CRect dstRc(-r, -r, r, r);
	m_pTocak->DrawTransparent(pDC, srcRc, dstRc, RGB(255, 255, 255));
	pDC->SetWorldTransform(&transOld);
}

void CMy1Kol2014View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
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

void CMy1Kol2014View::Rotate(CDC* pDC, float angle, bool rightMultiply)
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

void CMy1Kol2014View::Scale(CDC* pDC, float sX, float sY, bool rightMultiply)
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

// CMy1Kol2014View drawing

void CMy1Kol2014View::OnDraw(CDC* /*pDC*/)
{
	CMy1Kol2014Doc* pDoc = GetDocument();
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
	XFORM t;
	memDC->GetWorldTransform(&t);

	CBrush* pozadina = new CBrush(RGB(200, 220, 255));
	CBrush* oldB = memDC->SelectObject(pozadina);


	memDC->Rectangle(0, 0, rect.Width(), rect.Height());
	DrawGround(memDC, angle);

	int carWidth = 450;
	int carHeight = carWidth / 2.5;
	int x = 0 + m_hPos, y = 0, r = 38;
	float alpha = 180/3.14 * m_hPos / (2 * 3.14);
	memDC->GetWorldTransform(&t);
	Translate(memDC, carWidth / 2.0, -carHeight / 2.0 - r / 2.0, true);
	Rotate(memDC, -angle, true); // MWT_RIGHTMULTIPLY
	Translate(memDC, 0.0, rect.Height(), true);
	DrawCar(memDC, x, y, carWidth, carWidth / 2.5, 0.0f); // Kola
	DrawWheel(memDC, x - 155, y + 70, r, alpha); // tockovi
	DrawWheel(memDC, x + 135, y + 70, r, alpha);

	memDC->SelectObject(&oldB);


	memDC->SetWorldTransform(&t);


	//prekopiramo iz memdc u pdc
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	pDC->SetGraphicsMode(oldmod);
	memDC->SetGraphicsMode(memMode);

	memDC->DeleteDC();
	delete memDC;
	// TODO: add draw code for native data here
}


// CMy1Kol2014View printing

BOOL CMy1Kol2014View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy1Kol2014View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy1Kol2014View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMy1Kol2014View diagnostics

#ifdef _DEBUG
void CMy1Kol2014View::AssertValid() const
{
	CView::AssertValid();
}

void CMy1Kol2014View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy1Kol2014Doc* CMy1Kol2014View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy1Kol2014Doc)));
	return (CMy1Kol2014Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy1Kol2014View message handlers


void CMy1Kol2014View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
	if (nChar == VK_RIGHT)
	{
		m_hPos += 10.0;
		Invalidate(false);
	}
	if (nChar == VK_LEFT)
	{
		m_hPos -= 10.0;
		if (m_hPos < 0.0)
			m_hPos = 0.0;
		Invalidate(false);
	}
	if (nChar == VK_UP)
	{
		angle += 10.0f;
		if (angle > 80.0f)
			angle = 80.0f;
		Invalidate(false);
	}
	if (nChar == VK_DOWN)
	{
		angle -= 10.0f;
		if (angle < -10.0f)
			angle = -10.0f;
		Invalidate(false);
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
