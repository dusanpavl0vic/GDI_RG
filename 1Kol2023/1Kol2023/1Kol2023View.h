
// 1Kol2023View.h : interface of the CMy1Kol2023View class
//

#pragma once
#include "DImage.h"

class CMy1Kol2023View : public CView
{
private:
	DImage* glava;
	DImage* nadkolenica;
	DImage* nadlaktica;
	DImage* podkolenica;
	DImage* podlaktica;
	DImage* saka;
	DImage* stopalo;
	DImage* telo;
	DImage* pozadina;

	void DrawBackground(CDC* pDC, CRect rect);
	void DrawImgTransparent(CDC* pDC, DImage* pImage);
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void Scale(CDC* pDC, float sX, float sY, bool rightMultiply);
	void point(CDC* pDC);

	int rNadlaktica = 0;
	int rPodlaktica = 0;
	int rSaka = 0;
	int rRobot = 0;
	float skaliranje = 1.0f;

	void DrawHalf(CDC* pDC);
	void DrawHead(CDC* pDC);
	void DrawRobot(CDC* pDC);



protected: // create from serialization only
	CMy1Kol2023View() noexcept;
	DECLARE_DYNCREATE(CMy1Kol2023View)

// Attributes
public:
	CMy1Kol2023Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMy1Kol2023View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in 1Kol2023View.cpp
inline CMy1Kol2023Doc* CMy1Kol2023View::GetDocument() const
   { return reinterpret_cast<CMy1Kol2023Doc*>(m_pDocument); }
#endif

