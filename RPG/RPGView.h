
// RPGView.h : CRPGView Ŭ������ �������̽�
//

#pragma once
#pragma comment(lib, "winmm")
#include <mmsystem.h>


class CRPGView : public CView
{
protected: // serialization������ ��������ϴ�.
	CRPGView();
	DECLARE_DYNCREATE(CRPGView)

// Ư���Դϴ�.
public:
	CRPGDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	bool boss; // �������� �������� üũ
	int bgm;
	int dia;   // ���̾�α� ����
	int title; // Ÿ��Ʋ �޴�
	int shopmenu; // ���� �޴�
    int menu; // ���� �޴� ���� ��ǥ
	int menu1;// ���� �޴� ���� ��ǥ
	CFont font1; // ��Ʈ
	CFont font2; 
	CFont font3;
	CFont font4;
	CString shop_text; // ���������� ��� �ؽ�Ʈ
	CString battle[5]; // ���� �����Ȳ ǥ��
	CString npc_name; // ��ȭ�� NPC �̸�
	CString chat_line1; // ���� �����Ȳ ����
	CString chat_line2;
	CString chat_line3;
	CString chat_line4;
	CString chat_line5;
	int select;
	int keydown;
// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void potal(int map, int xpos, int ypos);
protected:

// �����Դϴ�.
public:
	virtual ~CRPGView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	void MapDraw(int dx, int dy,int mx,int my,CDC &mem,CPaintDC &dc);
	void MapDraw(int dx, int dy,int mx,int my, CDC &mem,CClientDC &dc);
	void npc_chating(CString name, CString text1,
	                      CString text2,CString text3,
						  CString text4,CString text5,CPaintDC &dc);
	
	void text_set(CString npc,CString str1,CString str2,CString str3,
	CString str4,CString str5);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void text_call(int index);
	void battleset();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // RPGView.cpp�� ����� ����
inline CRPGDoc* CRPGView::GetDocument() const
   { return reinterpret_cast<CRPGDoc*>(m_pDocument); }
#endif

