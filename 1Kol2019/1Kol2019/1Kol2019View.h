
// 1Kol2019View.h : interface of the CMy1Kol2019View class
//

#pragma once

#include "DImage.h"

class CMy1Kol2019View : public CView
{
private:
	DImage* body1;
	DImage* arm1;
	DImage* arm2;
	DImage* leg1;
	DImage* leg2;
	DImage* background;
	void DrawBackground(CDC* pDC, CRect rc);
	void DrawImgTransparent(CDC* pDC, DImage* pImage);
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void Scale(CDC* pDC, float sX, float sY, bool rightMultiply);
	void DrawArm1(CDC* pDC);
	void DrawArm2(CDC* pDC);
	void DrawBody1(CDC* pDC);
	void DrawLeg1(CDC* pDC);
	void DrawLeg2(CDC* pDC);

	int arm1R = 0;
	int arm2R = 0;
	int body1R = 0;
	int leg1R = 0;
	int leg2R = 0;


	void DrawTransformer(CDC* pDC);

protected: // create from serialization only
	CMy1Kol2019View() noexcept;
	DECLARE_DYNCREATE(CMy1Kol2019View)

// Attributes
public:
	CMy1Kol2019Doc* GetDocument() const;

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
	virtual ~CMy1Kol2019View();
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

#ifndef _DEBUG  // debug version in 1Kol2019View.cpp
inline CMy1Kol2019Doc* CMy1Kol2019View::GetDocument() const
   { return reinterpret_cast<CMy1Kol2019Doc*>(m_pDocument); }
#endif

