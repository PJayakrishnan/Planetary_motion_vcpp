// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// palanetaryMotionView.cpp : implementation of the CpalanetaryMotionView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "palanetaryMotion.h"
#endif

#include "palanetaryMotionDoc.h"
#include "palanetaryMotionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CpalanetaryMotionView

IMPLEMENT_DYNCREATE(CpalanetaryMotionView, CView)

BEGIN_MESSAGE_MAP(CpalanetaryMotionView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CpalanetaryMotionView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_START, &CpalanetaryMotionView::OnButtonStart)
	ON_COMMAND(ID_BUTTON_PAUSE, &CpalanetaryMotionView::OnButtonPause)
	ON_COMMAND(ID_BUTTON_RESUME, &CpalanetaryMotionView::OnButtonResume)
END_MESSAGE_MAP()

// CpalanetaryMotionView construction/destruction

CpalanetaryMotionView::CpalanetaryMotionView() noexcept
{
	// TODO: add construction code here
	m_pCurrentThread = NULL;
	x = 400;
	y = 300;
	x1 = 300 + 200 * cos(3);
	y1 = 300 + 200 * sin(3);

}

CpalanetaryMotionView::~CpalanetaryMotionView()
{
}

BOOL CpalanetaryMotionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CpalanetaryMotionView drawing

void CpalanetaryMotionView::OnDraw(CDC* pDC)
{
	CpalanetaryMotionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDC->Ellipse(100, 100, 500, 500);
	pDC->Ellipse(200, 200, 400, 400);
	CBrush red_brush;
	CBrush blue_brush;
	CBrush green_brush;

	red_brush.CreateSolidBrush(RGB(255, 0, 0));
	blue_brush.CreateSolidBrush(RGB(0, 0, 255));
	green_brush.CreateSolidBrush(RGB(0, 255, 0));

	pDC->SelectObject(red_brush);
	pDC->Ellipse(260, 260, 340, 340);//center circle

	pDC->SelectObject(blue_brush);
	pDC->Ellipse(x1+10, y1+10, x1-10, y1-10);
	pDC->SelectObject(green_brush);
	pDC->Ellipse(x+10, y+10, x-10, y-10);//planets


	// TODO: add draw code for native data here
}


// CpalanetaryMotionView printing


void CpalanetaryMotionView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CpalanetaryMotionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CpalanetaryMotionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CpalanetaryMotionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CpalanetaryMotionView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CpalanetaryMotionView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CpalanetaryMotionView diagnostics

#ifdef _DEBUG
void CpalanetaryMotionView::AssertValid() const
{
	CView::AssertValid();
}

void CpalanetaryMotionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CpalanetaryMotionDoc* CpalanetaryMotionView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CpalanetaryMotionDoc)));
	return (CpalanetaryMotionDoc*)m_pDocument;
}
#endif //_DEBUG


// CpalanetaryMotionView message handlers


void CpalanetaryMotionView::OnButtonStart()
{
	// TODO: Add your command handler code here
    m_pCurrentThread = AfxBeginThread(CpalanetaryMotionView::StartThread, this);
}


void CpalanetaryMotionView::OnButtonPause()
{
	// TODO: Add your command handler code 
	m_pCurrentThread->SuspendThread();
}


void CpalanetaryMotionView::OnButtonResume()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->ResumeThread();
}

UINT CpalanetaryMotionView::StartThread(LPVOID Param)
{
	// TODO: Add your implementation code here.
	CpalanetaryMotionView* pView((CpalanetaryMotionView*)Param);
	CPoint MyPoint(0, 0);
	int j = 0;
	while (1)
	{
		j = j + 6;
		pView->x = 300 + 100 * cos(j);
		pView->y = 300 + 100 * sin(j);
		pView->x1 = 300 + 200 * cos(j+3);
		pView->y1 = 300 + 200 * sin(j+3);

		pView->Invalidate();
		Sleep(300);
	}
	return 0;
}
