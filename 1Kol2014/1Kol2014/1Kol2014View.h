
// 1Kol2014View.h : interface of the CMy1Kol2014View class
//

#pragma once
#include "DImage.h"

class CMy1Kol2014View : public CView
{
private:
	void DrawGround(CDC* pDC, float angle);
	int angle = 20;
	int m_hPos = 0;
	void DrawCar(CDC* pDC, int x, int y, int w, int h, float angle);
	//void DrawImgTransparent(CDC* pDC, DImage* pImage);
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void Scale(CDC* pDC, float sX, float sY, bool rightMultiply);

	void DrawWheel(CDC* pDC, int x, int y, int r, float angle);
	DImage* m_pTocak;
	HENHMETAFILE m_met;


protected: // create from serialization only
	CMy1Kol2014View() noexcept;
	DECLARE_DYNCREATE(CMy1Kol2014View)

// Attributes
public:
	CMy1Kol2014Doc* GetDocument() const;

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
	virtual ~CMy1Kol2014View();
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

#ifndef _DEBUG  // debug version in 1Kol2014View.cpp
inline CMy1Kol2014Doc* CMy1Kol2014View::GetDocument() const
   { return reinterpret_cast<CMy1Kol2014Doc*>(m_pDocument); }
#endif

