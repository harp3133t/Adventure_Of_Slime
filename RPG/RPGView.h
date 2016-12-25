
// RPGView.h : CRPGView 클래스의 인터페이스
//

#pragma once
#pragma comment(lib, "winmm")
#include <mmsystem.h>


class CRPGView : public CView
{
protected: // serialization에서만 만들어집니다.
	CRPGView();
	DECLARE_DYNCREATE(CRPGView)

// 특성입니다.
public:
	CRPGDoc* GetDocument() const;

// 작업입니다.
public:
	bool boss; // 보스와의 전투인지 체크
	int bgm;
	int dia;   // 다이얼로그 변수
	int title; // 타이틀 메뉴
	int shopmenu; // 상점 메뉴
    int menu; // 게임 메뉴 가로 좌표
	int menu1;// 게임 메뉴 세로 좌표
	CFont font1; // 폰트
	CFont font2; 
	CFont font3;
	CFont font4;
	CString shop_text; // 상점에서의 출력 텍스트
	CString battle[5]; // 전투 진행상황 표시
	CString npc_name; // 대화시 NPC 이름
	CString chat_line1; // 전투 진행상황 라인
	CString chat_line2;
	CString chat_line3;
	CString chat_line4;
	CString chat_line5;
	int select;
	int keydown;
// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void potal(int map, int xpos, int ypos);
protected:

// 구현입니다.
public:
	virtual ~CRPGView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // RPGView.cpp의 디버그 버전
inline CRPGDoc* CRPGView::GetDocument() const
   { return reinterpret_cast<CRPGDoc*>(m_pDocument); }
#endif

