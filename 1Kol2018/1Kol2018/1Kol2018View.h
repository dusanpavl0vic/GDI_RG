
// 1Kol2018View.h : interface of the CMy1Kol2018View class
//

#pragma once
#include "DImage.h"

class CMy1Kol2018View : public CView
{
private:
	DImage* bager;
	DImage* arm1;
	DImage* arm2;
	DImage* pozadina;

	HENHMETAFILE viljuska;

	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void Scale(CDC* pDC, float sX, float sY, bool rightMultiply);

	void DrawBackground(CDC* pDC);
	void DrawImgTransparent(CDC* pDC, DImage* pImage);
	void point(CDC* pDC);

	void DrawExcavator(CDC* pDC);
	void DrawBody(CDC* pDC);
	void DrawArm1(CDC* pDC);
	void DrawArm2(CDC* pDC);
	void DrawFork(CDC* pDC);

	int arm1R = 0;
	int arm2R = 0;
	int viljuskaR = 0;
	int xBager = 0;

protected: // create from serialization only
	CMy1Kol2018View() noexcept;
	DECLARE_DYNCREATE(CMy1Kol2018View)

// Attributes
public:
	CMy1Kol2018Doc* GetDocument() const;

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
	virtual ~CMy1Kol2018View();
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

#ifndef _DEBUG  // debug version in 1Kol2018View.cpp
inline CMy1Kol2018Doc* CMy1Kol2018View::GetDocument() const
   { return reinterpret_cast<CMy1Kol2018Doc*>(m_pDocument); }
#endif

