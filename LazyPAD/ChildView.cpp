// 這個 MFC 範例原始程式碼會示範如何使用 MFC Microsoft Office Fluent 使用者介面
// (「Fluent UI」)，並且僅提供為參考資料，做為
// MFC 參考及 MFC C++ 程式庫軟體
// 隨附相關電子文件的補充。
// 關於 Fluent UI 之複製、使用或散發的授權條款則分別提供。
// 如需 Fluent UI 授權計劃的詳細資訊，請造訪 
// http://go.microsoft.com/fwlink/?LinkId=238214。
//
// Copyright (C) Microsoft Corporation
// 著作權所有，並保留一切權利。

// ChildView.cpp : CChildView 類別的實作
//

#include "stdafx.h"
#include "LazyPAD.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_CFileDialog_FILE_COUNT 99
#define FILE_LIST_BUFFER_SIZE ((MAX_CFileDialog_FILE_COUNT * (MAX_PATH + 1)) + 1)

// CChildView

CChildView::CChildView()
{
	m_X = 0;
	m_Y = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_FILE_OPEN, &CChildView::OnFileOpen)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// CChildView 訊息處理常式

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this); // 繪製的裝置內容

	// TODO:  在此加入您的訊息處理常式程式碼

	// 不要呼叫描繪訊息的 CWnd::OnPaint()

	CRect rc;
	GetClientRect(&rc);
	dc.FillSolidRect(&rc, RGB(182, 220, 231));

	DrawPuzzle(dc, map);


	int windowX = 10;
	int windowY = 360;
	int h = 0, f = 0, w = 0, t = 0, s = 0, d = 0;
	int combo = 0;

	dc.SetBkMode(TRANSPARENT);
	CString str;
	{
		combo = map.GetMaxCombo(h, f, w, t, s, d);
		str.Format(L"最大COMBO數 %ld: 心%ld 火%ld 水%ld 木%ld 光%ld 暗%ld", combo, h, f, w, t, s, d);
		dc.TextOut(windowX, windowY, str);

		windowY += 24;
		combo = map.CalCombo(h, f, w, t, s, d);
		str.Format(L"目前COMBO數 %ld: 心%ld 火%ld 水%ld 木%ld 光%ld 暗%ld", combo, h, f, w, t, s, d);
		dc.TextOut(windowX, windowY, str);
	}


}

void CChildView::DrawPuzzle(CDC& dc, PUZZLE::CMap& map)
{
	int size = 64;
	int space = 5;
	int h = 0 + space;
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	dc.SelectObject(&pen);
	for (int y = 4; y >= 0; y--)
	{
		int w = 0 + space;
		for (int x = 0; x <= 5; x++)
		{
			dc.Rectangle(w, h, w + size, h + size);
			COLORREF clr = 0;
			clr = PUZZLE::GetColor(map.Element[x][y]);
			dc.FillSolidRect(w, h, size - 2, size - 2, clr);
			w += size + space;;
		}
		h += size + space;
	}
}

void CChildView::OnFileOpen()
{
	// TODO:  在此加入您的命令處理常式程式碼
	CString fileName;
	wchar_t* p = fileName.GetBuffer(FILE_LIST_BUFFER_SIZE);
	CFileDialog dlgFile(TRUE);
	OPENFILENAME& ofn = dlgFile.GetOFN();
	ofn.Flags |= OFN_ALLOWMULTISELECT;
	ofn.lpstrFile = p;
	ofn.nMaxFile = FILE_LIST_BUFFER_SIZE;

	if (dlgFile.DoModal() == IDOK)
	{
		MessageBox(dlgFile.GetPathName());
	}
	fileName.ReleaseBuffer();
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	//TRACE("%u\n", nChar);

	bool bChange = false;
	if (nChar == 13)
	{
		TRACE(L"------------------開始計算------------------\n");
		PUZZLE::RunPath(map.Element, 15, 3);
		TRACE(L"------------------計算完成------------------\n");
	}
	else if (nChar == 13)
	{
		TRACE(L"------------------重置MAP------------------\n");
		m_X = 0;
		m_Y = 0;
	}
	else if (nChar == 96)
	{
		map.Element[m_X][m_Y] = 0;
		bChange = true;
	}
	else if (nChar == 97)
	{
		map.Element[m_X][m_Y] = 1;
		bChange = true;
	}
	else if (nChar == 98)
	{
		map.Element[m_X][m_Y] = 2;
		bChange = true;
	}
	else if (nChar == 99)
	{
		map.Element[m_X][m_Y] = 3;
		bChange = true;
	}
	else if (nChar == 100)
	{
		map.Element[m_X][m_Y] = 4;
		bChange = true;
	}
	else if (nChar == 101)
	{
		map.Element[m_X][m_Y] = 5;
		bChange = true;
	}
	else if (nChar == 48)
	{
		m_X = 0;
		m_Y = 0;
	}
	else if (nChar == 49)
	{
		m_X = 0;
		m_Y = 1;
	}
	else if (nChar == 50)
	{
		m_X = 0;
		m_Y = 2;
	}
	else if (nChar == 51)
	{
		m_X = 0;
		m_Y = 3;
	}
	else if (nChar == 52)
	{
		m_X = 0;
		m_Y = 4;
	}


	if (bChange)
	{
		if (m_X < 5) m_X++;
		else
		{
			m_X = 0;
			if (m_Y < 4)m_Y++;
			else m_Y = 0;
		}
		Invalidate();
	}

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
