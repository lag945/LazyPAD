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

// ChildView.h : CChildView ���O������
//


#pragma once
#include "Puzzle.h"

// CChildView ����

class CChildView : public CWnd
{
// �غc
public:
	CChildView();

// �ݩ�
public:

// �@�~
public:

// �мg
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �{���X��@
public:
	virtual ~CChildView();

	// ���ͪ��T�������禡
protected:
	PUZZLE::CMap map;
	int m_X, m_Y;
	void DrawPuzzle(CDC& dc, PUZZLE::CMap& map);
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

