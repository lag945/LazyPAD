// �o�� MFC �d�ҭ�l�{���X�|�ܽd�p��ϥ� MFC Microsoft Office Fluent �ϥΪ̤���
// (�uFluent UI�v)�A�åB�ȴ��Ѭ��ѦҸ�ơA����
// MFC �ѦҤ� MFC C++ �{���w�n��
// �H�������q�l��󪺸ɥR�C
// ���� Fluent UI ���ƻs�B�ϥΩδ��o�����v���ګh���O���ѡC
// �p�� Fluent UI ���v�p�����ԲӸ�T�A�гy�X 
// http://go.microsoft.com/fwlink/?LinkId=238214�C
//
// Copyright (C) Microsoft Corporation
// �ۧ@�v�Ҧ��A�ëO�d�@���v�Q�C

// ChildView.cpp : CChildView ���O����@
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



// CChildView �T���B�z�`��

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
	CPaintDC dc(this); // ø�s���˸m���e

	// TODO:  �b���[�J�z���T���B�z�`���{���X

	// ���n�I�s�yø�T���� CWnd::OnPaint()

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
		str.Format(L"�̤jCOMBO�� %ld: ��%ld ��%ld ��%ld ��%ld ��%ld �t%ld", combo, h, f, w, t, s, d);
		dc.TextOut(windowX, windowY, str);

		windowY += 24;
		combo = map.CalCombo(h, f, w, t, s, d);
		str.Format(L"�ثeCOMBO�� %ld: ��%ld ��%ld ��%ld ��%ld ��%ld �t%ld", combo, h, f, w, t, s, d);
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
	// TODO:  �b���[�J�z���R�O�B�z�`���{���X
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
	// TODO:  �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	//TRACE("%u\n", nChar);

	bool bChange = false;
	if (nChar == 13)
	{
		TRACE(L"------------------�}�l�p��------------------\n");
		PUZZLE::RunPath(map.Element, 15, 3);
		TRACE(L"------------------�p�⧹��------------------\n");
	}
	else if (nChar == 13)
	{
		TRACE(L"------------------���mMAP------------------\n");
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
