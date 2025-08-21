
// 1Kol2023.h : main header file for the 1Kol2023 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy1Kol2023App:
// See 1Kol2023.cpp for the implementation of this class
//

class CMy1Kol2023App : public CWinApp
{
public:
	CMy1Kol2023App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy1Kol2023App theApp;
