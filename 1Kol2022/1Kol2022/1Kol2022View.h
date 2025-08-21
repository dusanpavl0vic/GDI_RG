
// 1Kol2022View.h : interface of the CMy1Kol2022View class
//

#pragma once
#include "DImage.h"

class CMy1Kol2022View : public CView
{
private:
	DImage* base;
	DImage* arm1;
	DImage* arm2;
	DImage* head;
	DImage* pozadina;
	DImage* base_shadow;
	DImage* arm1_shadow;
	DImage* arm2_shadow;
	DImage* head_shadow;

	void DrawBackground(CDC* pDC);
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void Scale(CDC* pDC, float sX, float sY, bool rightMultiply);
	void DrawImgTransparent(CDC* pDC, DImage* pImage);

	void point(CDC* pDC);
	void DrawLamp(CDC* pDC, bool bIsShadow);
	void DrawLampBase(CDC* pDC, bool bIsShadow);
	void DrawLampArm1(CDC* pDC, bool bIsShadow);
	void DrawLampArm2(CDC* pDC, bool bIsShadow);
	void DrawLampHead(CDC* pDC, bool bIsShadow);

	int arm1R = 0;
	int arm2R = 0;
	int headR = 0;

	void DrawLampShadow(CDC* pDC);

protected: // create from serialization only
	CMy1Kol2022View() noexcept;
	DECLARE_DYNCREATE(CMy1Kol2022View)

// Attributes
public:
	CMy1Kol2022Doc* GetDocument() const;

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
	virtual ~CMy1Kol2022View();
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

#ifndef _DEBUG  // debug version in 1Kol2022View.cpp
inline CMy1Kol2022Doc* CMy1Kol2022View::GetDocument() const
   { return reinterpret_cast<CMy1Kol2022Doc*>(m_pDocument); }
#endif

