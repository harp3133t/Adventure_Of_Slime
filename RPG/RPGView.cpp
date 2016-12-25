
// RPGView.cpp : CRPGView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "RPG.h"
#endif

#include "RPGDoc.h"
#include "RPGView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAP_X 45 // 맵출력시 1x1 맵의 x 방향 크기
#define MAP_Y 45 // 맵출력시 1x1 맵의 y 방향 크기


#define MAX_STACK_SIZE 500
#define MAZE_SIZE 15

// CRPGView

IMPLEMENT_DYNCREATE(CRPGView, CView)

BEGIN_MESSAGE_MAP(CRPGView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CRPGView 생성/소멸

CRPGView::CRPGView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	font1.CreateFont(20,15,0,0,1,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,
		   DEFAULT_PITCH | FF_DONTCARE,_T("바탕체")); // 폰트 초기화
	font2.CreateFont(25,15,0,0,1,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,
		   DEFAULT_PITCH | FF_DONTCARE,_T("궁서체"));
    font3.CreateFont(30,30,0,0,1,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,
		   DEFAULT_PITCH | FF_DONTCARE,_T("돋움체"));
	font4.CreateFont(30,20,0,0,1,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,
		   DEFAULT_PITCH | FF_DONTCARE,_T("굴림"));
	boss=false; // 보스전 체크 초기화
	keydown=0; // 키 눌림 체크 변수 초기화
	dia=0;  // 다이얼로그 초기화
	title=0; // 타이틀 선택 메뉴 초기화
	shopmenu=0; // 상점 선택 메뉴 초기화
	menu=0; // 일반 메뉴 초기화
	menu1=0; // 일반 메뉴 세로 초기화
	select=0; // 전투시 아이템 선택 초기화
	shop_text.Format(_T("구매 아이템 선택하세요"));
	bgm=0;
}

CRPGView::~CRPGView()
{
}

BOOL CRPGView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CRPGView 그리기

void CRPGView::OnDraw(CDC* /*pDC*/)
{
	CRPGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.


}

void CRPGView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CRPGView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CRPGView 진단

#ifdef _DEBUG
void CRPGView::AssertValid() const
{
	CView::AssertValid();
}

void CRPGView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRPGDoc* CRPGView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRPGDoc)));
	return (CRPGDoc*)m_pDocument;
}
#endif //_DEBUG


// CRPGView 메시지 처리기
// CRPGView 메시지 처리기
int MAP[6][16][16]={   // 맵선언을 3차원 배열로 [맵번호][Y좌표][X좌표]
	{                  // 만자리단위=이벤트  
		               // 천의자리+백의자리=맵칩X좌표
		               // 십의자리+일의자리=맵칩Y좌표
{   600,   600,   600,   600, 52915,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600}, //초원맵 00
{   600,   700,   600,   700,   700,   700,   700,   700,   700,   700,   700,   600,   600,   600,   600,   600},
{   600,   700,   600,   700,   700,   700,   600,   700,   700,   700,   700,   600,   600,   600,   600,   600},
{   600,   700,   600,   700,   700,   700,   700,   700,   700,   700,   700,   600,   600,   600,   600,   600},
{   600,   700,   700,   600,   700,   700,   600,   700,   700,   700,   700,   600,   600,   600,   600,   600},
{   600,   700,   700,   700,   700,   700,   700,   700,   700,   700,   700,   600,   600,   600,   600,   600},
{   600,   700,   700,   600,   600,   700,   600,   700,   700,   700,   700,   600,   600,   600,   600,   600},
{   600,   700,   700,   700,   700,   700,   700,   700,   700,   700,   700,   600,   600,   600,   600,   600},
{   600,   700,   700,   700,   700,   700,   700,   700,   700,   700,   700,   600,   600,   600,   600,   600},
{   600,   700,   700,   700,   700,   700,   700,   700,   700,   700,   700,   600,   600,   600,   600,   600},
{   600,   700,   700,   700,   700,   700,   700,   700,   700,   700,   700,   600,   600,   600,   600,   600},
{   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600},
{   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600},
{   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600},
{   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600},
{   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600}
	},{
{  1412,  1412,  1412,  1412,  1412,  1412,  1412,  1412,  1412, 31000,  1412,  1412,  1412,  1412,  1412,  1412}, // 상점맵 01
{  1412,  1014,  1014,  1014,  1014,  1014,  1014,  1014,  1000,  1000,  1000,  1412,  1412,  1412,  1412,  1412},
{  1412,  1014,  1211,  1014,  1014,  1014,  1014,  1211,  1014,  1000,  1708,  1412,  1412,  1412,  1412,  1412},
{  1412,  1014,  1014,  1014,  1014,  1014,  1014,  1014,  1014,  1014,  1014,  1412,  1412,  1412,  1412,  1412},
{  1412,  1211,  1014,  1211,  1014,  1014,  1014,  1014,  1014,  1014,  1014,  1412,  1412,  1412,  1412,  1412},
{  1412,  1014,  1412,  1412,  1014,  1014,  1014,  1014,  1014,  1211,  1014,  1412,  1412,  1412,  1412,  1412},
{  1412,  1014,  1412,  1412,  1014,  2100,  2200,  2300,  1014,  1014,  1014,  1412,  1412,  1412,  1412,  1412},
{  1412,  1014,  1014,  1014,  1014,  2101,  2201,  2301,  1014,  1014,  1211,  1412,  1412,  1412,  1412,  1412},
{  1412,  1014,  1014,  1014,  1014,  2102,  2202,  2302,  1014,  1507,  1607,  1412,  1412,  1412,  1412,  1412},
{  1412,  1014,  1014,  1014,  1014,  1014,  1014,  1014,  1014,  1508, 21608,  1412,  1412,  1412,  1412,  1412},
{  1412,  1014,  1014,  1014,  1014,  1014,  1014,  1014,  1014,  1014,  1014,  1412,  1412,  1412,  1412,  1412},
{  1412,  1412,  1014,  1412,  1412,  1412,  1412,  1412,  1014,  1412,  1412,  1412,  1014,  1412,  1412,  1412},
{  1412,  1412,  1014,  1412,  1412,  1412,  1412,  1412,  1014,  1412,  1412,  1014,  1014,  1412,  1412,  1412},
{  1412,  1412,  1014,  1412,  1412,  1412,  1412,  1412,  1014,  1412,  1412,  1014,  1412,  1412,  1412,  1412},
{  1412,  1412,  1014,  1412,  1412,  1412,  1412,  1412,  1014,  1014,  1014,  1014,  1412,  1412,  1412,  1412},
{  1412,  1412, 31014,  1412,  1412,  1412,  1412,  1412,  1412,  1412,  1412,  1412,  1412,  1412,  1412,  1412}
	},{
{   900,   900,   900,   900,   900,   900,   900,   900,   900,   900,   900,   900,   900,   900,   900,   900}, // 설원맵 02
{   900,   900,   900,  1000,  1000,  1000,  1000,   900,  1000,  1000,  1000,   900,   900,   900,   900,   900},
{   900,   900,   900,  1000,  1000,  1000,  1000,   900,  1000,  1000,  1000,   900,   909,  1009,  1109,   900},
{   900,  1000,   900,  1000,  1000,  1000,  1000,   900,  1000,  1000,  1000,   900,   910,  1010,  1110,   900},
{   900,  1000,  1000,  1000,  1000,  1000,  1000,   900,   900,  1000,   900,   900,   911, 41011,  1111,   900},
{   900,  1000,  1000,  1000,  1000,  1000,  1000,  1000,  1000,  1000,  1000,   900,   900,  1000,   900,   900},
{   900,  1000,  1000,   900,  1000,  1000,  1000,  1000,  1000,  1000,  1000,   900,   900,  1000,   900,   900},
{   900,  1000,  1000,  1000,  1000,  1000,   900,  1000,  1000,  1000,  1000,   900,   900,  1000,  1000,   900},
{   900,  1000,  1000,  1000,  1000,  1000,   900,   900,  1000,  1000,  1000,   900,   900,   900,  1000,   900},
{   900,  1000,  1000,  1000,  1000,  1000,   900,   900,   900,  1000,  1000,   900,   900,   900,  1000,   900},
{   900,  1000,  1000,  1000,  1000,  1000,   900,   900,   900,   900,  1000,   900,  1000,  1000,  1000,   900},
{   900,   900,   900,  1000,   900,   900,   900,  1000,  1000,   900,  1000,   900,  1000,   900,   900,   900},
{   900,   900,   900,  1000,   900,   900,  1000,  1000,  1000,   900,  1000,  1000,  1000,  1000,  1000,   900},
{   900,   900,   900,  1000,   900,   900,   900,  1000,  1000,  1000,  1000,   900,   900,   900,  1000,   900},
{   900,   900,   900,  1000,   900,   900,   900,   900,   900,   900,  1000,   900,   900,   900,  1000,   900},
{   900,   900,   900, 31000,   900,   900,   900,   900,   900,   900,   900,   900,   900,   900,   900,   900}
	}
	,{
{   702,   702,   702,   702,   603, 30700,   603,   702,   702,   702,   702,   702,   702,   702,   702,   702}, // 동굴맵 03
{   702,   702,   702,   802,   700,   700,   700,   603,   703,   703,   703,   702,   702,   702,   702,   702},
{   702,   702,   702,   803,   700,   212,   700,   700,    12,   700,   700,   602,   702,   702,   702,   702},
{   702,   702,   803,   700,   700,   700,   700,   700,   700,   700,  1700,   602,   702,   702,   702,   702},
{   702,   803,   700,   700,   700,   700,   700,   700,   212,   700,   700,   602,   702,   702,   702,   702},
{   802,   700,   700,   700,   700,   700,   700,   700,   700,  1700,   700,   602,   702,   702,   702,   702},
{   802,   700,   700,   212,  1700,   700,   700,   700,   700,   700,   700,   602,  2400,  2500,  2600,   702},
{   802,   700,   700,   700,  1700,   212,    13,   213,  1700,   700,   700,   700,  2401,  2501,  2601,   702},
{   802,   700,   700,   700,   700,   700,    15,   215,   700,   601,   701,   700,  2402, 12502,  2602,   702},
{   702,   801,   700,   700,   700,   700,   700,   700,   700,   700,   700,   700,  2403,  2503,  2603,   702},
{   702,   802,   700,   700,   700,   700,   700,   601,   801,   700,   700,   700,   700,   700,   602,   702},
{   702,   702,   701,   701,   701,   701,   701,   602,   702,   801,   700,   700,   700,   700,   602,   702},
{   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   701,   701,   701,   701,   702,   702},
{   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702},
{   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702},
{   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702}
},
{
{   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702}, // 미로맵 04
{   702,   700,   702,   702,   700,   700,   700,   702,   702,   700,   700,   700,   702,   702,   702,   702},
{   702,   700,   702,   702,   700,   702,   700,   702,   702,   700,   702,   700,   702,   702,   702,   702},
{   702,   700,   702,   702,   700,   700,   700,   702,   702,   700,   702,   700,   700,   702,   702,   702},
{   702,   700,   700,   702,   702,   700,   700,   700,   700,   700,   702,   702,   700,   702,   702,   702},
{   702,   702,   700,   700,   702,   700,   702,   702,   700,   700,   700,   702,   700,   702,   702,   702},
{   702,   702,   702,   700,   700,   700,   702,   702,   700,   702,   700,   702,   700,   702,   702,   702},
{   702,   702,   702,   702,   700,   702,   702,   702,   700,   702,   700,   702,   700,   702,   702,   702},
{   702,   702,   702,   702,   700,   702,   702,   702,   700,   702,   700,   702,   700,   702,   702,   702},
{   702,   702,   702,   702,   702,   702,   702,   702,   700,   702,   700,   702,   700,   702,   702,   702},
{   702,   702,   702,   702,   702,   702,   702,   702,   700,   700,   700,   702,   700,   700,   702,   702},
{   702,   702,   702,   702,   702,   702,   702,   702,   700,   700,   702,   702,   702,   700,   702,   702},
{   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   700,   702,   702},
{   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   700,   700, 30700},
{   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702},
{   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702}
},{
{   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702}, // 미로맵 05
{   702,   702,   702,   702,   702,   702,   700,   700,   700,   700,   702,   702,   702,   700,   700,   702},
{ 30700,   700,   700,   702,   702,   702,   702,   702,   700,   700,   700,   700,   702,   700,   702,   702},
{   702,   702,   700,   702,   702,   702,   702,   702,   700,   702,   702,   700,   702,   700,   702,   702},
{   702,   700,   700,   702,   702,   700,   700,   702,   700,   702,   700,   700,   700,   700,   700,   702},
{   702,   700,   702,   702,   702,   700,   700,   702,   700,   702,   702,   702,   702,   700,   700,   702},
{   702,   700,   702,   700,   702,   700,   700,   702,   700,   702,   702,   702,   702,   702,   702,   702},
{   702,   700,   700,   700,   702,   700,   700,   702,   700,   702,   702,   702,   702,   702,   702,   702},
{   702,   702,   700,   700,   702,   700,   700,   702,   700,   702,   702,   702,   702,   702,   702,   702},
{   702,   702,   702,   700,   702,   700,   700,   702,   700,   702,   700,   700,   702,   702,   702,   702},
{   702,   702,   702,   700,   702,   700,   700,   700,   700,   702,   700,   702,  2400,  2500,  2600,   702},
{   702,   700,   700,   700,   700,   700,   702,   700,   700,   700,   700,   702,  2401,  2501,  2601,   702},
{   702,   700,   702,   702,   700,   702,   702,   700,   700,   700,   700,   702,  2402,  2502,  2602,   702},
{   702,   700,   702,   702,   700,   702,   702,   702,   702,   700,   700,   702,  2403, 52503,  2603,   702},
{   702,   700,   700,   700,   700,   702,   702,   702,   702,   702,   700,   700,   700,   700,   700,   702},
{   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702}
}


};

void CRPGView::OnPaint()
{
CRPGDoc* pDoc = GetDocument();
CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.
CDC MemDC;
MemDC.CreateCompatibleDC(&dc);
CBitmap bmp[15],*pbmp;
bmp[0].LoadBitmapW(IDB_BITMAP1);// 맵
bmp[4].LoadBitmapW(IDB_BITMAP6);// 동굴 배경
bmp[5].LoadBitmapW(IDB_BITMAP7);// 슬라임
bmp[6].LoadBitmapW(IDB_BITMAP8);// 전투 인터페이스
bmp[7].LoadBitmapW(IDB_BITMAP9);// 귀뚜라미
bmp[8].LoadBitmapW(IDB_BITMAP10);// 드래곤
bmp[9].LoadBitmapW(IDB_BITMAP11);// 설원배경
bmp[10].LoadBitmapW(IDB_BITMAP12);// 실내배경
bmp[11].LoadBitmapW(IDB_BITMAP13);// 상점배경
bmp[12].LoadBitmapW(IDB_BITMAP14);// 일반 메뉴 배경
pbmp=MemDC.SelectObject(&bmp[0]);

if((pDoc->pstate)==0){
int mapNUM=pDoc->pmap; // mapNUM은 현재선택된맵 , pmap에서 받아옴
for(int x=0;x<16;x++){
	for(int y=0;y<16;y++){
MapDraw(x,y,(MAP[mapNUM][y][x]%10000)/100,MAP[mapNUM][y][x]%100,MemDC,dc);
	}
}
if(pDoc->pmap==3&&pDoc->xPos==5&&pDoc->yPos==0) // 동굴→실내 포탈
{
 potal(1,2,14);
 Invalidate();
}
if(pDoc->pmap==1&&pDoc->xPos==2&&pDoc->yPos==15) // 실내→동굴 포탈
{
 potal(3,5,1);
 Invalidate();
}
if(pDoc->pmap==1&&pDoc->xPos==9&&pDoc->yPos==0) // 실내→설원 포탈
{
 potal(2,3,14);
 Invalidate();
}
if(pDoc->pmap==2&&pDoc->xPos==3&&pDoc->yPos==15) // 설원→실내 포탈
{
 potal(1,9,1);
 Invalidate();
}
if(pDoc->pmap==4&&pDoc->xPos==15&&pDoc->yPos==13) // 미로1→미로2 포탈
{
 potal(5,1,2);
 Invalidate();
}
if(pDoc->pmap==5&&pDoc->xPos==0&&pDoc->yPos==2) // 미로2→미로1 포탈
{
 potal(4,14,13);
 Invalidate();
}

if(pDoc->chating){ // NPC와 대화중일때 화면 출력함수
bmp[1].LoadBitmapW(IDB_BITMAP2);
pbmp=MemDC.SelectObject(&bmp[1]);
dc.StretchBlt(0,480,720,250,&MemDC,0,0,734,177,SRCCOPY);
MemDC.SelectObject(pbmp);
npc_chating(npc_name,chat_line1,chat_line2,chat_line3,chat_line4,chat_line5,dc);
}
bmp[2].LoadBitmapW(IDB_BITMAP3);
pbmp=MemDC.SelectObject(&bmp[2]);
if(pDoc->parrow==2)  // 앞
dc.TransparentBlt((pDoc->xPos)*MAP_X,(pDoc->yPos)*MAP_Y,MAP_X,MAP_Y,&MemDC,0,0,32,32,RGB(255,255,255));
if(pDoc->parrow==1)  // 뒤
dc.TransparentBlt((pDoc->xPos)*MAP_X,(pDoc->yPos)*MAP_Y,MAP_X,MAP_Y,&MemDC,0,96,32,32,RGB(255,255,255));
if(pDoc->parrow==3)  // 왼쪽
dc.TransparentBlt((pDoc->xPos)*MAP_X,(pDoc->yPos)*MAP_Y,MAP_X,MAP_Y,&MemDC,0,32,32,32,RGB(255,255,255));
if(pDoc->parrow==4)  //오른쪽
dc.TransparentBlt((pDoc->xPos)*MAP_X,(pDoc->yPos)*MAP_Y,MAP_X,MAP_Y,&MemDC,0,64,32,32,RGB(255,255,255));
   }
bmp[3].LoadBitmapW(IDB_BITMAP4);
if(pDoc->pstate==1){ // 메뉴화면 출력
	CString str;
	dc.SelectObject(&font3);
	dc.SetBkMode(TRANSPARENT); // TextOut시 글자 주위가 투명하게함
	pbmp=MemDC.SelectObject(&bmp[12]);
	dc.StretchBlt(0,0,720,800,&MemDC,0,0,691,656,SRCCOPY);

	dc.Ellipse(40+(menu*250),160+(menu1*95),70+(menu*250),190+(menu1*95)); // 선택

	str.Format(_T("%d"),pDoc->ch_level);
	dc.TextOutW(220,320,str);
	str.Format(_T("%d/%d"),pDoc->ch_hp,pDoc->ch_maxhp);
	dc.TextOutW(170,385,str);
	str.Format(_T("%d/%d"),pDoc->ch_sp,pDoc->ch_maxsp);
	dc.TextOutW(170,455,str);
	str.Format(_T("%d/%d"),pDoc->ch_exp,pDoc->ch_maxexp);
	dc.TextOutW(175,520,str);
	str.Format(_T("%d"),pDoc->ch_str);
	dc.TextOutW(480,575,str);
	str.Format(_T("%d"),pDoc->ch_dex);
	dc.TextOutW(480,645,str);
	str.Format(_T("%d"),pDoc->hp_potion);
	dc.TextOutW(260,655,str);
	str.Format(_T("%d"),pDoc->mp_potion);
	dc.TextOutW(260,720,str);
	str.Format(_T("%d"),pDoc->ch_money);
	dc.TextOutW(515,710,str);
	str.Format(_T("%d"),pDoc->ch_skillpoint);
	dc.TextOutW(555,515,str);
 }
if(pDoc->pstate==2){ // 타이틀
 pbmp=MemDC.SelectObject(&bmp[3]);
 dc.StretchBlt(0,0,720,720,&MemDC,0,0,720,720,SRCCOPY);
 dc.SelectObject(&font2);
 if(title==0){dc.Rectangle(200,450,230,480);
 dc.Rectangle(460,450,490,480);}
 if(title==1){dc.Rectangle(200,520,230,550);
 dc.Rectangle(460,520,490,550);}
 if(title==2){dc.Rectangle(200,590,230,620);
 dc.Rectangle(460,590,490,620);}
 }
if(pDoc->pstate==3||pDoc->pstate==5){ // 전투화면
BITMAP bmpInfo;
BLENDFUNCTION bf;
dc.Rectangle(0,0,800,800);
if(pDoc->pmap==0||pDoc->pmap==3||pDoc->pmap>=4){ // 현재맵이 동굴일때
bmp[4].GetBitmap(&bmpInfo);
pbmp=MemDC.SelectObject(&bmp[4]);
}
if(pDoc->pmap==1){ // 현재맵이 실내일때
bmp[10].GetBitmap(&bmpInfo);
pbmp=MemDC.SelectObject(&bmp[10]);
}
if(pDoc->pmap==2){ // 현재맵이 설원일때
bmp[9].GetBitmap(&bmpInfo);
pbmp=MemDC.SelectObject(&bmp[9]);
}
bf.BlendOp = AC_SRC_OVER;
bf.BlendFlags = 0;
bf.SourceConstantAlpha = 70;
bf.AlphaFormat = 0;
dc.AlphaBlend(0,0,800,800,&MemDC,0,0,bmpInfo.bmWidth, bmpInfo.bmHeight, bf);
MemDC.SelectObject(pbmp);
if(pDoc->mo_num==0)pbmp=MemDC.SelectObject(&bmp[5]);//슬라임
if(pDoc->pmap==0)pbmp=MemDC.SelectObject(&bmp[5]); // 마지막 맵일때 슬라임선택
if(pDoc->mo_num==1)pbmp=MemDC.SelectObject(&bmp[7]);//귀뚜라미
if(pDoc->mo_num==2||pDoc->mo_num==3)pbmp=MemDC.SelectObject(&bmp[8]);//새끼용,드래곤

		
		if(bgm==0&&pDoc->mo_num==0) //슬라임 출현 사운드
		{
			PlaySound(_T(".\\slime.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			bgm++;
		}
		else if(bgm==0&&pDoc->mo_num==1) //귀뚜라미 출현 사운드
		{
			PlaySound(_T(".\\zun.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			bgm++;
		}
		else if(bgm==0&&pDoc->mo_num==2) //새끼용 출현 사운드
		{
			PlaySound(_T(".\\babydragon.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			bgm++;
		}
		else if(bgm==0&&pDoc->mo_num==3) //드래곤 출현 사운드
		{
			PlaySound(_T(".\\dragon.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			bgm++;
		}

if(pDoc->mo_num!=3)dc.TransparentBlt(300,200,((pDoc->mo_xsize)+200)/2,((pDoc->mo_ysize)+200)/2,&MemDC,0,0,
	pDoc->mo_xsize,pDoc->mo_ysize,RGB(255,255,255)); // 몬스터 화면 출력
else {
	dc.TransparentBlt(150,100,((pDoc->mo_xsize)+200),((pDoc->mo_ysize)+200),&MemDC,0,0,
	pDoc->mo_xsize,pDoc->mo_ysize,RGB(255,255,255)); // 보스전 드래곤일때 화면 출력
}
pbmp=MemDC.SelectObject(&bmp[6]);
dc.Rectangle(25,600,475,750);
for(int i=0;i<5;i++)dc.TextOutW(30,620+25*i,battle[i]); // 전투 진행상황 출력
srand((unsigned)time(NULL));
CString str;
dc.SetBkMode(TRANSPARENT);
for(int i=0;i<9;i++){       // 1~9까지 키보드 인터페이스 숫자 출력
str.Format(_T("[ %d ]"),i+1);
dc.TextOutW(510+100*(i%3),630-100*(i/3),str);
}

for(int i=0;i<6;i++){    // 1~6까지 플레이어 소지 카드 화면 출력
dc.TransparentBlt(480+100*(i%3),650-100*(i/3),80,80,&MemDC,
	(pDoc->card[i]%3)*72,(pDoc->card[i]/3)*70,72,70,RGB(255,255,255));
}
for(int i=6;i<9;i++){ // 7~9까지 몬스터 카드 화면 출력
dc.TransparentBlt(250+100*(i%3),60,70,70,&MemDC,
	(pDoc->card[i]%3)*72,(pDoc->card[i]/3)*70,72,70,RGB(255,255,255));
}
/*7~9까지 플레이어 인터페이스 화면 출력*/
dc.TransparentBlt(480,450,80,80,&MemDC,0,140,72,70,RGB(255,255,255));
dc.TransparentBlt(580,450,80,80,&MemDC,72,140,72,70,RGB(255,255,255));
dc.TransparentBlt(680,450,80,80,&MemDC,144,140,72,70,RGB(255,255,255));

/* HP,SP,경험치바 출력 */
dc.SelectObject(&font3);
dc.TextOutW(20,410,_T("HP:"));
dc.TextOutW(20,510,_T("SP:"));
CString lv;
lv.Format(_T("LV : %d"),pDoc->ch_level);
dc.TextOutW(50,360,lv);
dc.SelectObject(&font4);
dc.TextOutW(250,25,pDoc->mo_name);
dc.SelectObject(&font1);
CString str2; CRect rect;
str2.Format(_T("%d/%d"),pDoc->ch_hp,pDoc->ch_maxhp);
dc.TextOutW(120,455,str2);
str2.Format(_T("%d/%d"),pDoc->ch_sp,pDoc->ch_maxsp);
dc.TextOutW(120,555,str2);

dc.Draw3dRect(100,400,300,50,RGB(0,0,0),RGB(25,25,25));
rect.SetRect(102,402,102+((296*(pDoc->ch_hp))/(pDoc->ch_maxhp)),448);
CBrush brush(RGB(255,0,0));
dc.FillRect(rect,&brush);

dc.Draw3dRect(260,150,250,20,RGB(0,0,0),RGB(25,25,25));
rect.SetRect(262,152,262+((246*(pDoc->mo_hp))/(pDoc->mo_maxhp)),168);
dc.FillRect(rect,&brush);

str2.Format(_T("HP : %d / %d "),pDoc->mo_hp,pDoc->mo_maxhp);
dc.TextOutW(260,190,str2);

dc.Draw3dRect(100,500,300,50,RGB(0,0,0),RGB(25,25,25));
rect.SetRect(102,502,102+((296*(pDoc->ch_sp))/(pDoc->ch_maxsp)),548);
CBrush brush2(RGB(0,0,255));
dc.FillRect(rect,&brush2);

dc.Draw3dRect(25,580,425,20,RGB(0,0,0),RGB(25,25,25));
rect.SetRect(27,582,27+((396*(pDoc->ch_exp))/(pDoc->ch_maxexp)),598);
CBrush brush3(RGB(255,255,0));
dc.FillRect(rect,&brush3);

if(pDoc->pstate==5){ // 전투중 아이템 선택일때
	
	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(&font2);
	CString str;
	if(select==0)dc.TextOutW(20,350,_T(" 선택하세요 ▶"));
	if(select==1){ // HP포션사용
		str.Format(_T("◀ HP 포션 ▶ : %d개"),pDoc->hp_potion);
		dc.TextOutW(20,350,str);}
	if(select==2){// SP포션사용
		str.Format(_T("◀ SP 포션 ▶ : %d개"),pDoc->mp_potion);
		dc.TextOutW(20,350,str); }
	if(select==3)dc.TextOutW(20,350,_T("◀ 람보르기니 ▶ : 0대"));
	if(select==4)dc.TextOutW(20,350,_T("◀ 장미표창 ▶ : 0개"));
	if(select==5)dc.TextOutW(20,350,_T("◀ 돌아가기"));
}
}
if(pDoc->pstate==4){ // 상점화면
 pbmp=MemDC.SelectObject(&bmp[11]);
 dc.StretchBlt(0,0,720,720,&MemDC,0,0,720,720,SRCCOPY);
 dc.SelectObject(&font2);
 if(shopmenu==0){ // HP포션 구입 커서
 dc.Rectangle(110,460,140,490);
 dc.Rectangle(210,460,240,490);
 }
 if(shopmenu==1){ // SP포션 구입 커서
 dc.Rectangle(350,460,380,490);
 dc.Rectangle(450,460,480,490);
 }
 if(shopmenu==3){ // 람보르기니(?) 구입 커서
 dc.Rectangle(570,460,600,490);
 dc.Rectangle(720,460,750,490);
 }
 /*if(shopmenu==3){ // 돌아가기
 dc.Rectangle(570,460,590,490);
 dc.Rectangle(730,460,750,40);
 }*/
 CString str;
 str.Format(_T("%d Gold"),pDoc->ch_money); // 소지금 표시
 dc.TextOutW(600,80,str);
 str.Format(_T("%d"),pDoc->hp_potion); // HP포션 현재 소지수 표시
 dc.TextOutW(180,400,str);
 str.Format(_T("%d"),pDoc->mp_potion); // SP포션 현재 소지수 표시
 dc.TextOutW(420,400,str);
 str.Format(_T("%s"),shop_text); // 상점 거래 정보 표시
 dc.TextOutW(100,100,str);
 }
}


void CRPGView::MapDraw(int dx, int dy,int mx,int my, CDC &mem,CPaintDC &dc)  // 맵그리기(페인트)
{
dc.StretchBlt(0+dx*MAP_X,0+dy*MAP_Y,MAP_X,MAP_Y,&mem,0+16*mx,0+16*my,16,16,SRCCOPY);
}

void CRPGView::MapDraw(int dx, int dy,int mx,int my, CDC &mem,CClientDC &dc) // 맵그리기(클라이언트)
{
dc.StretchBlt(0+dx*MAP_X,0+dy*MAP_Y,MAP_X,MAP_Y,&mem,0+16*mx,0+16*my,16,16,SRCCOPY);
}


void CRPGView::npc_chating(CString name, CString text1,
	   CString text2,CString text3,CString text4,CString text5,CPaintDC &dc)
{  //대화 텍스트 표시
	dc.SetTextColor(RGB(45,125,180));
	dc.SelectObject(&font1);
	dc.TextOutW(80,500,name);
	dc.SelectObject(&font2);
	dc.TextOutW(70,535,text1);
	dc.TextOutW(70,570,text2);
	dc.TextOutW(70,605,text3);
	dc.TextOutW(70,640,text4);
	dc.TextOutW(70,675,text5);
}


void CRPGView::text_set(CString npc,CString str1,CString str2,CString str3,
	CString str4,CString str5)
{ //대화 텍스트 설정
npc_name=npc;
chat_line1=str1;
chat_line2=str2;
chat_line3=str3;
chat_line4=str4;
chat_line5=str5;
}

int Move[16][30]={ // 타일 이동불가 판정
{1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,0,1,1,1,1},
{0,0,0,1,0,0,1,0,1,1,0,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0,0,0},
{0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,0,1,0,0,1},
{0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0,0,1},
{0,0,0,1,0,0,1,1,1,1,1,1,1,0,0,1,1,0,1,1,1,1,1,0,0,0,1,0,0,0},
{0,0,0,0,0,1,0,0,0,1,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1},
{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1},
{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1},
{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
{1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0},
{1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0}
};

void CRPGView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

CRPGDoc* pDoc = GetDocument();
// 화면 출력을 위한 BMP 로드
CClientDC dc(this);
CDC MemDC;
MemDC.CreateCompatibleDC(&dc);
CBitmap bmp,bmp2,bmp3,bmp4,*pbmp;
bmp2.LoadBitmapW(IDB_BITMAP1);
bmp.LoadBitmapW(IDB_BITMAP2);
bmp3.LoadBitmapW(IDB_BITMAP3);
bmp4.LoadBitmapW(IDB_BITMAP4);
pbmp=MemDC.SelectObject(&bmp);

// 상하좌우 맵정보를 변수에다 대입
int mapnumLeft=MAP[(pDoc->pmap)][(pDoc->yPos)][(pDoc->xPos)-1];
int mapnumRight=MAP[(pDoc->pmap)][(pDoc->yPos)][(pDoc->xPos)+1];
int mapnumUP=MAP[(pDoc->pmap)][(pDoc->yPos)-1][(pDoc->xPos)];
int mapnumDown=MAP[(pDoc->pmap)][(pDoc->yPos)+1][(pDoc->xPos)];


if((pDoc->pstate)==0){ // 맵상에 있을때
if(!keydown&&pDoc->pstate==0&&pDoc->chating==1){
switch(nChar){
case VK_SPACE:
case VK_RETURN:
	pDoc->chating=2; // 대화변수 증가시 바로 조건이 만족해서 읽어지는걸 방지하기 위한 상태 [2번상태]
	Invalidate(false);
	break;
}
}

if(!keydown&&pDoc->pstate==0&&(pDoc->chating==0||pDoc->chating>=3)){ // 맵이동시
int mapnumLeft=MAP[(pDoc->pmap)][(pDoc->yPos)][(pDoc->xPos)-1];
int mapnumRight=MAP[(pDoc->pmap)][(pDoc->yPos)][(pDoc->xPos)+1];
int mapnumUP=MAP[(pDoc->pmap)][(pDoc->yPos)-1][(pDoc->xPos)];
int mapnumDown=MAP[(pDoc->pmap)][(pDoc->yPos)+1][(pDoc->xPos)];
int mapx,mapy;
switch(nChar){
	case VK_LEFT:
	if(pDoc->chating==0){
		keydown=1;
		mapx=(mapnumLeft%10000)/100;
		mapy=mapnumLeft%100;
		if(Move[mapy][mapx]==0){ // 이동가능 체크
pbmp=MemDC.SelectObject(&bmp2);
MapDraw(pDoc->xPos,pDoc->yPos,(MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]%10000)/100,MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]%100,MemDC,dc);
MapDraw(pDoc->xPos-1,pDoc->yPos,(MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos-1]%10000)/100,MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos-1]%100,MemDC,dc);
pbmp=MemDC.SelectObject(&bmp3);
		dc.TransparentBlt((pDoc->xPos)*MAP_X-(MAP_X)/3,(pDoc->yPos)*MAP_Y,MAP_X,MAP_Y,&MemDC,32,32,32,32,RGB(255,255,255));
		Invalidate(FALSE);
		PlaySound(_T(".\\move.wav"), AfxGetInstanceHandle(),  SND_ASYNC);	
			Sleep(100);
pbmp=MemDC.SelectObject(&bmp2);
MapDraw(pDoc->xPos,pDoc->yPos,(MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]%10000)/100,MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]%100,MemDC,dc);
MapDraw(pDoc->xPos-1,pDoc->yPos,(MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos-1]%10000)/100,MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos-1]%100,MemDC,dc);
pbmp=MemDC.SelectObject(&bmp3);
    dc.TransparentBlt((pDoc->xPos)*MAP_X-(MAP_X*2)/3,(pDoc->yPos)*MAP_Y,MAP_X,MAP_Y,&MemDC,64,32,32,32,RGB(255,255,255));
		Invalidate(FALSE);
			Sleep(100);
pbmp=MemDC.SelectObject(&bmp2);
MapDraw(pDoc->xPos,pDoc->yPos,(MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]%10000)/100,MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]%100,MemDC,dc);
MapDraw(pDoc->xPos-1,pDoc->yPos,(MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos-1]%10000)/100,MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos-1]%100,MemDC,dc);
pbmp=MemDC.SelectObject(&bmp3);
		dc.TransparentBlt((pDoc->xPos)*MAP_X-(MAP_X*3)/3,(pDoc->yPos)*MAP_Y,MAP_X,MAP_Y,&MemDC,0,32,32,32,RGB(255,255,255));
			Invalidate(FALSE);
	(pDoc->xPos)--;
		}
		(pDoc->parrow)=3;
		Invalidate(FALSE);
		keydown=0;
}
	if(!(rand()%15))battleset();
		break;
	case VK_RIGHT:
	if(pDoc->chating==0){
		keydown=1;
		mapx=(mapnumRight%10000)/100;
		mapy=mapnumRight%100;
		if(Move[mapy][mapx]==0){ // 이동가능 체크
pbmp=MemDC.SelectObject(&bmp2);
MapDraw(pDoc->xPos,pDoc->yPos,(MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]%10000)/100,MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]%100,MemDC,dc);
MapDraw(pDoc->xPos+1,pDoc->yPos,(MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos+1]%10000)/100,MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos+1]%100,MemDC,dc);
pbmp=MemDC.SelectObject(&bmp3);
		dc.TransparentBlt((pDoc->xPos)*MAP_X+(MAP_X)/3,(pDoc->yPos)*MAP_Y,MAP_X,MAP_Y,&MemDC,32,64,32,32,RGB(255,255,255));
			Sleep(100);
			Invalidate(FALSE);
pbmp=MemDC.SelectObject(&bmp2);
MapDraw(pDoc->xPos,pDoc->yPos,(MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]%10000)/100,MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]%100,MemDC,dc);
MapDraw(pDoc->xPos+1,pDoc->yPos,(MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos+1]%10000)/100,MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos+1]%100,MemDC,dc);
pbmp=MemDC.SelectObject(&bmp3);
		dc.TransparentBlt((pDoc->xPos)*MAP_X+(MAP_X*2)/3,(pDoc->yPos)*MAP_Y,MAP_X,MAP_Y,&MemDC,64,64,32,32,RGB(255,255,255));
			Sleep(100);
			PlaySound(_T(".\\move.wav"), AfxGetInstanceHandle(),  SND_ASYNC);	
			Invalidate(FALSE);
pbmp=MemDC.SelectObject(&bmp2);
MapDraw(pDoc->xPos,pDoc->yPos,(MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]%10000)/100,MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]%100,MemDC,dc);
MapDraw(pDoc->xPos+1,pDoc->yPos,(MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos+1]%10000)/100,MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos+1]%100,MemDC,dc);
pbmp=MemDC.SelectObject(&bmp3);
		dc.TransparentBlt((pDoc->xPos)*MAP_X+(MAP_X*3)/3,(pDoc->yPos)*MAP_Y,MAP_X,MAP_Y,&MemDC,0,64,32,32,RGB(255,255,255));
			Invalidate(FALSE);
			(pDoc->xPos)++;}
		Invalidate(FALSE);
		(pDoc->parrow)=4;
		keydown=0;
	}
	if(!(rand()%15))battleset();
		break;
	case VK_UP:
	if(pDoc->chating==0){
		keydown=1;
		mapx=(mapnumUP%10000)/100;
		mapy=mapnumUP%100;
		if(Move[mapy][mapx]==0){ // 이동가능 체크
pbmp=MemDC.SelectObject(&bmp2);
MapDraw(pDoc->xPos,pDoc->yPos,(MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]%10000)/100,MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]%100,MemDC,dc);
MapDraw(pDoc->xPos,pDoc->yPos-1,(MAP[(pDoc->pmap)][pDoc->yPos-1][pDoc->xPos]%10000)/100,MAP[(pDoc->pmap)][pDoc->yPos-1][pDoc->xPos]%100,MemDC,dc);
pbmp=MemDC.SelectObject(&bmp3);
		dc.TransparentBlt((pDoc->xPos)*MAP_X,(pDoc->yPos)*MAP_Y-(MAP_Y)/3,MAP_X,MAP_Y,&MemDC,32,96,32,32,RGB(255,255,255));
			Invalidate(FALSE);
			Sleep(100);
pbmp=MemDC.SelectObject(&bmp2);
MapDraw(pDoc->xPos,pDoc->yPos,(MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]%10000)/100,MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]%100,MemDC,dc);
MapDraw(pDoc->xPos,pDoc->yPos-1,(MAP[(pDoc->pmap)][pDoc->yPos-1][pDoc->xPos]%10000)/100,MAP[(pDoc->pmap)][pDoc->yPos-1][pDoc->xPos]%100,MemDC,dc);
pbmp=MemDC.SelectObject(&bmp3);
		dc.TransparentBlt((pDoc->xPos)*MAP_X,(pDoc->yPos)*MAP_Y-(MAP_Y*2)/3,MAP_X,MAP_Y,&MemDC,64,96,32,32,RGB(255,255,255));
			Invalidate(FALSE);
			PlaySound(_T(".\\move.wav"), AfxGetInstanceHandle(),  SND_ASYNC);	
			Sleep(100);
pbmp=MemDC.SelectObject(&bmp2);
MapDraw(pDoc->xPos,pDoc->yPos,(MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]%10000)/100,MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]%100,MemDC,dc);
MapDraw(pDoc->xPos,pDoc->yPos-1,(MAP[(pDoc->pmap)][pDoc->yPos-1][pDoc->xPos]%10000)/100,MAP[(pDoc->pmap)][pDoc->yPos-1][pDoc->xPos]%100,MemDC,dc);
pbmp=MemDC.SelectObject(&bmp3);
		dc.TransparentBlt((pDoc->xPos)*MAP_X,(pDoc->yPos)*MAP_Y-(MAP_Y*3)/3,MAP_X,MAP_Y,&MemDC,0,96,32,32,RGB(255,255,255));
		Invalidate(FALSE);
		(pDoc->yPos)--;}
		Invalidate(FALSE);
		(pDoc->parrow)=1;
		keydown=0;
	}
	if(!(rand()%15))battleset();
		break;
	case VK_DOWN:
	if(pDoc->chating==0){
		keydown=1;
		mapx=(mapnumDown%10000)/100;
		mapy=mapnumDown%100;
		if(Move[mapy][mapx]==0){ // 이동가능 체크
pbmp=MemDC.SelectObject(&bmp2);
MapDraw(pDoc->xPos,pDoc->yPos,(MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]%10000)/100,MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]%100,MemDC,dc);
MapDraw(pDoc->xPos,pDoc->yPos+1,(MAP[(pDoc->pmap)][pDoc->yPos+1][pDoc->xPos]%10000)/100,MAP[(pDoc->pmap)][pDoc->yPos+1][pDoc->xPos]%100,MemDC,dc);
pbmp=MemDC.SelectObject(&bmp3);
		dc.TransparentBlt((pDoc->xPos)*MAP_X,(pDoc->yPos)*MAP_Y+(MAP_Y)/3,MAP_X,MAP_Y,&MemDC,32,0,32,32,RGB(255,255,255));
		PlaySound(_T(".\\move.wav"), AfxGetInstanceHandle(),  SND_ASYNC);	
		Invalidate(FALSE);
			Sleep(100);
pbmp=MemDC.SelectObject(&bmp2);
MapDraw(pDoc->xPos,pDoc->yPos,(MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]%10000)/100,MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]%100,MemDC,dc);
MapDraw(pDoc->xPos,pDoc->yPos+1,(MAP[(pDoc->pmap)][pDoc->yPos+1][pDoc->xPos]%10000)/100,MAP[(pDoc->pmap)][pDoc->yPos+1][pDoc->xPos]%100,MemDC,dc);
pbmp=MemDC.SelectObject(&bmp3);
		dc.TransparentBlt((pDoc->xPos)*MAP_X,(pDoc->yPos)*MAP_Y+(MAP_Y*2)/3,MAP_X,MAP_Y,&MemDC,64,0,32,32,RGB(255,255,255));
			Invalidate(FALSE);
			Sleep(100);
pbmp=MemDC.SelectObject(&bmp2);
MapDraw(pDoc->xPos,pDoc->yPos,(MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]%10000)/100,MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]%100,MemDC,dc);
MapDraw(pDoc->xPos,pDoc->yPos+1,(MAP[(pDoc->pmap)][pDoc->yPos+1][pDoc->xPos]%10000)/100,MAP[(pDoc->pmap)][pDoc->yPos+1][pDoc->xPos]%100,MemDC,dc);
pbmp=MemDC.SelectObject(&bmp3);
		dc.TransparentBlt((pDoc->xPos)*MAP_X,(pDoc->yPos)*MAP_Y+(MAP_Y*3)/3,MAP_X,MAP_Y,&MemDC,0,0,32,32,RGB(255,255,255));
		Invalidate(FALSE);
		(pDoc->yPos)++;}
		Invalidate(FALSE);
		(pDoc->parrow)=2;
		keydown=0;
	}
	if(!(rand()%40))battleset();
	break;
case VK_SPACE:
case VK_RETURN:
	int lx,ly; // NPC를 바라보는 방향 인식
	if(pDoc->parrow==1){lx=0; ly=-1;}
	if(pDoc->parrow==2){lx=0; ly=1;}
	if(pDoc->parrow==3){lx=-1; ly=0;}
	if(pDoc->parrow==4){lx=1; ly=0;}

	if(pDoc->chating==0&&dia==0&& // NPC 운영자 (000~006)
		MAP[(pDoc->pmap)][pDoc->yPos+ly][pDoc->xPos+lx]/10000==1){
		dia=1; text_call(0);
		pDoc->chating=3; Invalidate(false); break;}
	if(pDoc->chating==3&&dia>0&&dia<6&&
		MAP[(pDoc->pmap)][pDoc->yPos+ly][pDoc->xPos+lx]/10000==1){
		dia++; text_call(dia);
		Invalidate(false); break;}
	if(pDoc->chating==3&&dia==6&&
		MAP[(pDoc->pmap)][pDoc->yPos+ly][pDoc->xPos+lx]/10000==1){
		dia=0; text_call(6);
		pDoc->chating=1;  Invalidate(false); break;}

	if(pDoc->chating==0&&dia==0&& // NPC 상인 (010~012)
		MAP[(pDoc->pmap)][pDoc->yPos+ly][pDoc->xPos+lx]/10000==2){
		dia=1; text_call(10);
		pDoc->chating=3; Invalidate(false); break;}
	if(pDoc->chating==3&&dia==1&&
		MAP[(pDoc->pmap)][pDoc->yPos+ly][pDoc->xPos+lx]/10000==2){
		dia++; text_call(11);
		Invalidate(false); break;}
	if(pDoc->chating==3&&dia==2&&
		MAP[(pDoc->pmap)][pDoc->yPos+ly][pDoc->xPos+lx]/10000==2){
		dia=0; text_call(12);
		pDoc->chating=1;  Invalidate(false); break;}

	if(pDoc->chating==0&&dia==0&& // 드래곤 (020~045)
		MAP[(pDoc->pmap)][pDoc->yPos+ly][pDoc->xPos+lx]/10000==4){
		dia=1; text_call(20);
		pDoc->chating=3; Invalidate(false); break;}
	if(pDoc->chating==3&&dia>0&&dia<25&&
		MAP[(pDoc->pmap)][pDoc->yPos+ly][pDoc->xPos+lx]/10000==4){
		dia++; text_call(dia+20);
		Invalidate(false); break;}
	if(pDoc->chating==3&&dia==25&&
		MAP[(pDoc->pmap)][pDoc->yPos+ly][pDoc->xPos+lx]/10000==4){
		dia=0; text_call(45);
		pDoc->chating=1;  Invalidate(false); break;}

	if(pDoc->chating==0&&dia==0&& // 엔딩 (050~055)
		MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]/10000==5){
		dia=1; text_call(50);
		pDoc->chating=3; Invalidate(false); break;}
	if(pDoc->chating==3&&dia>0&&dia<5&&
		MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]/10000==5){
		dia++; text_call(dia+50);
		Invalidate(false); break;}
	if(pDoc->chating==3&&dia==5&&
		MAP[(pDoc->pmap)][pDoc->yPos][pDoc->xPos]/10000==5){
		dia=0; text_call(55);
		pDoc->chating=1;  Invalidate(false); break;}
break;
case VK_ESCAPE: // 메뉴화면 실행
	pDoc->pstate=1;
		PlaySound(_T("menu.wav"),AfxGetInstanceHandle(),  SND_ASYNC);
	Invalidate();
break;
	}

}
}
if(!keydown&&pDoc->pstate==0&&pDoc->chating==2){ // 대화 마무리
switch(nChar){
case VK_SPACE:
case VK_RETURN:
	pDoc->chating=0;
	Invalidate(false);
    break;
}
}
if(pDoc->pstate==1){         //메뉴
	switch(nChar){
case VK_RIGHT:
	if(!(menu1==1&&menu==1)&&menu<2)menu++;
	PlaySound(_T(".\\System.wav"), AfxGetInstanceHandle(),  SND_ASYNC);	
	Invalidate(false);
	break;
case VK_LEFT:
	if(menu>0)menu--;
	PlaySound(_T(".\\System.wav"), AfxGetInstanceHandle(),  SND_ASYNC);	
	Invalidate(false);
	break;
case VK_UP:
	if(menu1>0&&menu<2)menu1--;
	PlaySound(_T(".\\System.wav"), AfxGetInstanceHandle(),  SND_ASYNC);	
	Invalidate(false);
	break;
case VK_DOWN:
	if(menu1<1&&menu<2)menu1++;
	PlaySound(_T(".\\System.wav"), AfxGetInstanceHandle(),  SND_ASYNC);	
	Invalidate(false);
	break;

case VK_SPACE:
case VK_RETURN:
	if(menu==0&&menu1==0){pDoc->pstate=0;PlaySound(_T(".\\menu2.wav"),AfxGetInstanceHandle(),  SND_ASYNC);} // 되돌아가기
	if(menu==1&&menu1==0){
		PlaySound(_T(".\\KT1.wav"), AfxGetInstanceHandle(),  SND_ASYNC);	
		CFile file;
		CFileException e;
		if(!file.Open(_T("save.dat"),CFile::modeWrite|CFile::modeCreate,&e))
		{
			e.ReportError();
			return;
		}
		CArchive ar(&file,CArchive::store); // 저장하기
		ar<<pDoc->ch_dex<<pDoc->ch_exp<<pDoc->ch_hp<<
			pDoc->ch_level<<pDoc->ch_maxexp<<pDoc->ch_maxhp<<
			pDoc->ch_maxsp<<pDoc->ch_money<<pDoc->ch_skillpoint<<pDoc->ch_sp<<pDoc->ch_str<<
			pDoc->xPos<<pDoc->yPos<<pDoc->card[0]<<pDoc->card[1]<<
			pDoc->card[2]<<pDoc->card[3]<<pDoc->card[4]<<pDoc->card[5]<<
			pDoc->pmap<<pDoc->hp_potion<<pDoc->mp_potion<<pDoc->parrow;
	} // 저장하기
	if(menu==2){exit(0);} // 종료하기
	if(menu==0&&menu1==1){if(pDoc->ch_skillpoint>0){ pDoc->ch_str++; pDoc->ch_skillpoint--;}}
	if(menu==1&&menu1==1){if(pDoc->ch_skillpoint>0){ pDoc->ch_dex++; pDoc->ch_skillpoint--;}}
	Invalidate();
	break;
 }
}

if(pDoc->pstate==2){ // 타이틀 메뉴화면 키보드 인식
switch(nChar){
case VK_DOWN:
	if(title<2){title++; PlaySound(_T(".\\System.wav"),AfxGetInstanceHandle(),  SND_ASYNC);}
	Invalidate(false);
	break;
case VK_UP:
	if(title>0){title--; PlaySound(_T(".\\System.wav"),AfxGetInstanceHandle(),  SND_ASYNC);}
	Invalidate(false);
	break;

case VK_SPACE:
case VK_RETURN:
	if(title==0){pDoc->pstate=0;PlaySound(_T(".\\KT1.wav"),AfxGetInstanceHandle(),  SND_ASYNC);} // 처음하기
	if(title==1) // 이어하기
	{
		CFile file;
		CFileException e;
		if(!file.Open(_T("save.dat"),CFile::modeRead,&e))
		{
			e.ReportError();
			return;
		}
		CArchive ar(&file,CArchive::load);
		ar>>pDoc->ch_dex>>pDoc->ch_exp>> // 파일로드
			pDoc->ch_hp>>pDoc->ch_level>>pDoc->ch_maxexp>>
			pDoc->ch_maxhp>>pDoc->ch_maxsp>>pDoc->ch_money>>
			pDoc->ch_skillpoint>>pDoc->ch_sp>>pDoc->ch_str>>
			pDoc->xPos>>pDoc->yPos>>pDoc->card[0]>>pDoc->card[1]>>
			pDoc->card[2]>>pDoc->card[3]>>pDoc->card[4]>>pDoc->card[5]>>
			pDoc->pmap>>pDoc->hp_potion>>pDoc->mp_potion>>pDoc->parrow;
		pDoc->pstate=0;
		PlaySound(_T(".\\KT1.wav"),AfxGetInstanceHandle(),  SND_ASYNC);
	} // 이어하기

	if(title==2){exit(0);} // 종료하기
	Invalidate();
	break;
 }
}

if(pDoc->pstate==3){ // 전투화면 키보드 인식
int number;
if(nChar==VK_NUMPAD1)number=0; // 1~6까지 플레이어카드
if(nChar==VK_NUMPAD2)number=1;
if(nChar==VK_NUMPAD3)number=2;
if(nChar==VK_NUMPAD4)number=3;
if(nChar==VK_NUMPAD5)number=4;
if(nChar==VK_NUMPAD6)number=5;
if(nChar==VK_NUMPAD7)number=10; // 아이템 사용
if(nChar==VK_NUMPAD8)number=20; // 도주(보스전 불가)
if(nChar==VK_NUMPAD9)number=30; // 카드섞기(SP10소모)
switch(nChar){
case VK_NUMPAD1:
case VK_NUMPAD2:
case VK_NUMPAD3:
case VK_NUMPAD4:
case VK_NUMPAD5:
case VK_NUMPAD6:
case VK_NUMPAD7:
case VK_NUMPAD8:
case VK_NUMPAD9:
	int monster;
	if(pDoc->battle_state==0){//플레이어 행동
		
		if(number<10){
		srand((unsigned)time(NULL));
		monster=pDoc->card[6+rand()%3];
		Sleep(20+rand()%30);
		if(pDoc->card[number]==0&&pDoc->battle_state==0){// Attack
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			int dex=rand()%(pDoc->ch_dex)+rand()%(pDoc->ch_dex)+rand()%(pDoc->ch_dex)
				+(rand()%2)*(pDoc->ch_dex);
			int damage=(rand()%(pDoc->ch_str)+rand()%(pDoc->ch_str))/2+1;
            damage=(dex>pDoc->mo_dex)?damage:0;
			battle[4]=_T("당신의 공격!"); Invalidate(); Sleep(500);
			if(damage<=0){
			battle[4]=_T("당신의 공격이 빗나갔다!");
			PlaySound(_T(".\\fail.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else if(monster==1){
			battle[4]=_T("몬스터가 방어를 하여 소용이 없었다.");
			PlaySound(_T(".\\defence.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else if(monster==4&&(rand()%3)){
			 battle[4]=_T("몬스터가 공격을 회피하였습니다.");
			 PlaySound(_T(".\\fail.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else{
				battle[4].Format(_T("당신의 공격! %s 에게 %d 의 데미지를 주었다."),pDoc->mo_name,damage);
				(pDoc->mo_hp)-=damage;
				PlaySound(_T(".\\attack.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
				if(pDoc->mo_hp<0)pDoc->mo_hp=0;
			}
			Invalidate();
			pDoc->battle_state=1;
		}
		if(pDoc->card[number]==1&&pDoc->battle_state==0){// Defense
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			battle[4]=_T("이번턴엔 방어를 합니다!"); Invalidate(); Sleep(500);
			if(pDoc->ch_sp<pDoc->ch_maxsp)pDoc->ch_sp++;
			Invalidate();
			pDoc->battle_state=1;
		}
		else if(pDoc->card[number]==2&&pDoc->battle_state==0){// Ambush
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			int dex=rand()%(pDoc->ch_dex)+rand()%(pDoc->ch_dex)+rand()%(pDoc->ch_dex)
				+(rand()%2)*(pDoc->ch_dex);
			int damage=((rand()%(pDoc->ch_str)+rand()%(pDoc->ch_str))/2)*0.8+1;
            damage=(dex>pDoc->mo_dex)?damage:0;
			battle[4]=_T("당신의 습격!"); Invalidate(); Sleep(500);
			if(damage<=0){
			battle[4]=_T("당신의 습격이 빗나갔다!");
			PlaySound(_T(".\\fail2.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else if(monster==3){
			int mondex=rand()%(pDoc->mo_dex)+rand()%(pDoc->mo_dex)+rand()%(pDoc->mo_dex)
				+(rand()%2)*(pDoc->ch_dex);
			int mondamage=(rand()%(pDoc->mo_str)+rand()%(pDoc->mo_str))/2+1;
				battle[4].Format(_T("습격중 트랩에 걸렸다. %d 의 데미지를 입었다."),mondex);
				PlaySound(_T(".\\trap.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
				(pDoc->ch_hp)-=mondex;
				if(pDoc->ch_hp<0)pDoc->ch_hp=0;
			}
			else if(monster==4&&(rand()%3)){
			 battle[4]=_T("몬스터가 공격을 회피하였습니다.");
			  PlaySound(_T(".\\fail.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else{
				battle[4].Format(_T("당신의 습격! %s 에게 %d 의 데미지를 주었다."),pDoc->mo_name,damage);
				 PlaySound(_T(".\\attack2.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
				(pDoc->mo_hp)-=damage;
				if(pDoc->mo_hp<0)pDoc->mo_hp=0;
			}
			Invalidate();
			pDoc->battle_state=1;
		}
		else if(pDoc->card[number]==3&&pDoc->battle_state==0){// Trap
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			battle[4]=_T("트랩을 설치하였습니다!"); 
			PlaySound(_T(".\\traping.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			Invalidate(); Sleep(500);
			
			if(pDoc->ch_sp<pDoc->ch_maxsp)pDoc->ch_sp++;
			Invalidate();
			pDoc->battle_state=1;
		}
		else if(pDoc->card[number]==4&&pDoc->battle_state==0){// Avoid
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			battle[4]=_T("이번턴에 회피를 시도합니다."); Invalidate(); Sleep(500);
			Invalidate();
			pDoc->battle_state=1;
		}
		else if(pDoc->card[number]==5&&pDoc->battle_state==0){// HyperSkill
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			battle[4]=_T("하이퍼 스킬! 데미지는 현재 SP에 비례합니다.");
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			int dex=rand()%(pDoc->ch_dex)+rand()%(pDoc->ch_dex)+
				rand()%(pDoc->ch_dex)+rand()%(pDoc->ch_dex)+(rand()%2)*(pDoc->ch_dex);
			int damage=((rand()%(pDoc->ch_str)+rand()%(pDoc->ch_str))/2)
				+((rand()%(pDoc->ch_str)+rand()%(pDoc->ch_str))*pDoc->ch_sp)/25+1;
            damage=(dex>pDoc->mo_dex)?damage:0;
			Invalidate(); Sleep(500);
			pDoc->ch_sp=0;
			if(damage<=0){
			battle[4]=_T("하이퍼 스킬이 빗나갔다!");
			PlaySound(_T(".\\fail.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else if(monster==1){
			battle[4].Format(_T("몬스터가 방어를하여 %d 의 데미지밖에 주지 못했다."),damage/4);
			PlaySound(_T(".\\hyper1.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
				(pDoc->mo_hp)-=(damage/4);
				if(pDoc->mo_hp<0)pDoc->mo_hp=0;
			}
			else if(monster==4&&(rand()%3)){
			 battle[4]=_T("몬스터가 공격을 회피하였습니다.");
			 PlaySound(_T(".\\fail.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else{
				battle[4].Format(_T("하이퍼 스킬로 %s 에게 %d 의 데미지를 주었다."),pDoc->mo_name,damage);
				PlaySound(_T(".\\hyper2.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
				(pDoc->mo_hp)-=damage;
				if(pDoc->mo_hp<0)pDoc->mo_hp=0;
			}
			Invalidate();
			pDoc->battle_state=1;
		}
	  }
		else if(number==10){//아이템
			pDoc->pstate=5;
			select=0;
	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(&font2);
			dc.TextOutW(20,350,_T(" 선택하세요 ▶"));
			break;
		}
		else if(number==20){
			if(pDoc->mo_num==3){	
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			battle[4]=_T("보스전에선 도망칠수 없습니다.");
			PlaySound(_T(".\\System2.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
				pDoc->battle_state=0;
				Invalidate();
			}
		    else {
				pDoc->pstate=0;Invalidate();
			}
			break;}//도주
		else if(number==30){ //카드 리셋
			if(pDoc->ch_sp>=10){
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			battle[4]=_T("당신은 카드 리셋을 실행하였습니다.");
			PlaySound(_T(".\\System2.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else{
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			battle[4]=_T("카드리셋엔 SP가 10필요합니다.");
			PlaySound(_T(".\\System2.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			Invalidate();
			pDoc->battle_state=1;
		}
	}
	Invalidate();
	if(pDoc->battle_state==1){//몬스터 행동
		srand((unsigned)time(NULL));
		Sleep(20+rand()%30);
		if(monster==0&&pDoc->battle_state==1){// Attack
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			int dex=rand()%(pDoc->mo_dex)+rand()%(pDoc->mo_dex)+rand()%(pDoc->mo_dex)
				+(rand()%2)*(pDoc->mo_dex);
			int damage=(rand()%(pDoc->mo_str)+rand()%(pDoc->mo_str))/2+1;
            damage=(dex>pDoc->ch_dex)?damage:0;
			battle[4]=_T("몬스터의 공격!"); Invalidate(); Sleep(500);
			if(damage<=0){
			battle[4]=_T("몬스터의 공격이 빗나갔다!");
			PlaySound(_T(".\\fail.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else if(pDoc->card[number]==1){
			battle[4]=_T("플레이어가 방어를하여 소용이 없었다.");
			PlaySound(_T(".\\defence.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else if(pDoc->card[number]==4&&(rand()%3)){
			 battle[4]=_T("플레이어가 공격을 회피하였습니다.");
			 PlaySound(_T(".\\fail.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else{
				battle[4].Format(_T("몬스터의 공격! 당신에게 %d 의 데미지를 주었다."),damage);
				PlaySound(_T(".\\attack.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
				(pDoc->ch_hp)-=damage;
				if(pDoc->ch_hp<0)pDoc->ch_hp=0;
				if(pDoc->ch_sp<pDoc->ch_maxsp)pDoc->ch_sp++;
			}
			Invalidate();
			pDoc->battle_state=0;
		}
		if(monster==1&&pDoc->battle_state==1){// Defense
			Invalidate();
			pDoc->battle_state=0;
		}
		else if(monster==2&&pDoc->battle_state==1){// Ambush
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			int dex=rand()%(pDoc->mo_dex)+rand()%(pDoc->mo_dex)+rand()%(pDoc->mo_dex)
				+(rand()%2)*(pDoc->mo_dex);
			int damage=(rand()%(pDoc->mo_str)+rand()%(pDoc->mo_str))/2+1;
            damage=(dex>pDoc->ch_dex)?damage:0;
			battle[4]=_T("몬스터의 공격!"); Invalidate(); Sleep(500);
			if(damage<=0){
			battle[4]=_T("몬스터의 공격이 빗나갔다!");
			PlaySound(_T(".\\fail.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}

			else if(pDoc->card[number]==3){
			int chdex=rand()%(pDoc->ch_dex)+rand()%(pDoc->ch_dex)+rand()%(pDoc->ch_dex)
				+(rand()%2)*(pDoc->mo_dex);
			int chdamage=(rand()%(pDoc->ch_str)+rand()%(pDoc->ch_str))/2+1;
				battle[4].Format(_T("몬스터가 습격중 트랩에 걸렸다. %d 의 데미지를 입었다."),chdex);
				PlaySound(_T(".\\trap.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
				(pDoc->mo_hp)-=chdex;
				if(pDoc->mo_hp<0)pDoc->mo_hp=0;
			}
			else if(pDoc->card[number]==4&&(rand()%3)){
			 battle[4]=_T("플레이어가 공격을 회피하였습니다.");
			 PlaySound(_T(".\\fail.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else{
				battle[4].Format(_T("몬스터의 습격! 당신에게 %d 의 데미지를 주었다."),damage);
				PlaySound(_T(".\\attack2.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
				(pDoc->ch_hp)-=damage;
				if(pDoc->ch_hp<0)pDoc->ch_hp=0;
				if(pDoc->ch_sp<pDoc->ch_maxsp)pDoc->ch_sp++;
			}
			Invalidate();
			pDoc->battle_state=0;
		}
		else if(monster==3&&pDoc->battle_state==1){// Trap
			Invalidate();
			pDoc->battle_state=0;
		}
		else if(monster==4&&pDoc->battle_state==1){// Avoid
			Invalidate();
			pDoc->battle_state=0;
		}
		else if(monster==5&&pDoc->battle_state==1){// HyperSkill
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			battle[4]=_T("몬스터의 하이퍼 스킬!!!");
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			int dex=rand()%(pDoc->mo_dex)+rand()%(pDoc->mo_dex)+
				rand()%(pDoc->mo_dex)+rand()%(pDoc->mo_dex)+(rand()%2)*(pDoc->mo_dex);
			int damage=((rand()%(pDoc->mo_str)+rand()%(pDoc->mo_str))/2)
				+((rand()%(pDoc->mo_str)+rand()%(pDoc->mo_str))*100)/25+1;
            damage=(dex>pDoc->ch_dex)?damage:0;
			Invalidate(); Sleep(500);
			if(damage<=0){
			battle[4]=_T("하이퍼 스킬이 빗나갔다!");
			PlaySound(_T(".\\fail.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else if(pDoc->card[number]==1){
			battle[4].Format(_T("플레이어가 방어를하여 %d 의 데미지밖에 주지 못했다."),damage/4);
			PlaySound(_T(".\\hyper1.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			if(pDoc->ch_sp<pDoc->ch_maxsp)pDoc->ch_sp++;
				(pDoc->ch_hp)-=(damage/4);
				if(pDoc->ch_hp<0)pDoc->ch_hp=0;
			}
			else if(pDoc->card[number]==4&&(rand()%3)){
			 battle[4]=_T("몬스터가 공격을 회피하였습니다.");
			 PlaySound(_T(".\\fail.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else{
				battle[4].Format(_T("하이퍼 스킬로 플레이어가 %d의 데미지를 입었다."),damage);
				PlaySound(_T(".\\hyper2.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
				(pDoc->ch_hp)-=damage;
				if(pDoc->ch_hp<0)pDoc->ch_hp=0;
				if(pDoc->ch_sp<pDoc->ch_maxsp)pDoc->ch_sp++;
				if(pDoc->ch_sp<pDoc->ch_maxsp)pDoc->ch_sp++;
			}
			Invalidate();
			pDoc->battle_state=0;
		}
	}
	if(pDoc->ch_sp<pDoc->ch_maxsp&&number<10)pDoc->ch_sp++;

	if(number==30&&!(pDoc->battle_state==2)){ //카드 리셋
			if(pDoc->ch_sp>=10){
				for(int i=0;i<6;i++)pDoc->card[i]=rand()%31/6;
				pDoc->ch_sp-=10;
			}
			pDoc->battle_state=0;
			
		}
	if(pDoc->mo_hp<=0&&!(pDoc->battle_state==2)){ //승리
		PlaySound(_T(".\\victory.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
		bgm=0;
		CString str;
		battle[0]=_T("★★★전투에서 승리했다.★★★");
		str.Format(_T(" %d Gold 를 획득 했다. "),pDoc->mo_money);
		pDoc->ch_money+=pDoc->mo_money;
		battle[1].Format(str);
		str.Format(_T(" %d 의 Exp를 획득 했다. "),pDoc->mo_exp);
		pDoc->ch_exp+=pDoc->mo_exp;
		battle[2].Format(str);
		battle[3]=_T("★★★★★★★★★★★★");
		while(pDoc->ch_exp>=pDoc->ch_maxexp){
			pDoc->ch_exp-=pDoc->ch_maxexp;
			pDoc->ch_maxexp=pDoc->ch_maxexp+(pDoc->ch_level*pDoc->ch_level)*5;
			(pDoc->ch_level)++;
			pDoc->ch_maxhp=pDoc->ch_maxhp+10+pDoc->ch_level+(pDoc->ch_str)/5;
			pDoc->ch_maxsp=pDoc->ch_maxsp+5+(pDoc->ch_level/5)+(pDoc->ch_dex)/15;
			pDoc->ch_skillpoint+=3;
			str.Format(_T("레벨이 %d 으로 상승하였다. "),pDoc->ch_level);
			pDoc->ch_hp=pDoc->ch_maxhp;
			battle[3].Format(str);
		}
		battle[4]=_T("★★★ E N T E R★★★");
		pDoc->battle_state=2;
	}
	if(pDoc->ch_hp<=0&&!(pDoc->battle_state==2)){ //패배
		PlaySound(_T(".\\ahaha.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
		CString str;
		battle[0]=_T("★★★전투에서 패배했다.★★★");
		bgm=0;
		str.Format(_T("   G A M E  O V E R "));
		pDoc->ch_money-=pDoc->mo_money;
		if(pDoc->ch_money<=0)pDoc->ch_money=0;
		battle[1].Format(str);
		battle[2]=_T("의식을 잃었다.");
		battle[3]=_T("★★★★★★★★★★★★");
		battle[4]=_T("★★★ E N T E R★★★");
		pDoc->battle_state=3;
	}
	pDoc->card[number]=rand()%31/6;
	for(int i=0;i<3;i++)pDoc->card[i+6]=rand()%31/6;
	Invalidate();
	break;
case VK_SPACE:
case VK_RETURN:
	
if(pDoc->battle_state==2){//전투종료_승리
		pDoc->battle_state=0;
		for(int i=0;i<5;i++)battle[i]=CString(_T(""));
		pDoc->pstate=0;
		Invalidate();
	}
else if(pDoc->battle_state==3){//전투종료_패배
		exit(0);
	}
	break;
 }
}
if(pDoc->pstate==4){ // 상점 메뉴화면 키보드 인식
switch(nChar){
case VK_RIGHT:
	if(shopmenu<3)shopmenu++;
	PlaySound(_T(".\\System.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
	Invalidate(false);
	break;
case VK_LEFT:
	if(shopmenu>0)shopmenu--;
	PlaySound(_T(".\\System.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
	Invalidate(false);
	break;
case VK_SPACE:
case VK_RETURN:
	if(shopmenu==0){// HP포션 구입
		if(pDoc->ch_money>=150){
			pDoc->ch_money-=150; pDoc->hp_potion++;
			PlaySound(_T(".\\buy"), AfxGetInstanceHandle(),  SND_ASYNC);
		shop_text.Format(_T("hp포션을 구매했습니다"));
		}
		else{
		shop_text.Format(_T("돈이부족합니다."));
		PlaySound(_T(".\\ahaha.wav"), AfxGetInstanceHandle(),  SND_ASYNC);}
	}
	if(shopmenu==1){// SP포션 구입
		if(pDoc->ch_money>=150){
			pDoc->ch_money-=150; pDoc->mp_potion++;
			PlaySound(_T(".\\buy"), AfxGetInstanceHandle(),  SND_ASYNC);
		shop_text.Format(_T("sp포션을 구매했습니다"));
		}
		
		else {
			PlaySound(_T(".\\ahaha.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			shop_text.Format(_T("돈이부족합니다."));}
	}
	if(shopmenu==2){// 람보르기니 구입
		shop_text.Format(_T("물품을 구매해 주세요"));
	}
	if(shopmenu==3){pDoc->pstate=0;} // 돌아가기
	Invalidate();
	break;
 }
}
if(pDoc->pstate==5){ // 전투화면 아이템 선택 키보드 인식
switch(nChar){
case VK_RIGHT:
	if(select<5)select++;
	PlaySound(_T(".\\System.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
	Invalidate(false);
	break;
case VK_LEFT:
	if(select>0)select--;
	PlaySound(_T(".\\System.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
	Invalidate(false);
	break;
case VK_SPACE:
case VK_RETURN:
	dc.SelectObject(&font2);
	if(select==0){// 아이템을 선택하세요
		Invalidate(false);
	}
	if(select==1){// HP포션 사용
		if(pDoc->hp_potion>0){
			PlaySound(_T(".\\potion.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			pDoc->hp_potion--; 
			pDoc->ch_hp+=150;
			if(pDoc->ch_hp>pDoc->ch_maxhp)pDoc->ch_hp=pDoc->ch_maxhp;
			
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			battle[4].Format(_T("hp포션을 사용했습니다"));
		pDoc->pstate=3;
		pDoc->battle_state=0;
	Invalidate(false);
	break;
		}
	}
	if(select==2){// SP포션 사용
		if(pDoc->mp_potion>0){
			PlaySound(_T(".\\potion.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			pDoc->mp_potion--; 
			pDoc->ch_sp+=150;
			if(pDoc->ch_sp>pDoc->ch_maxsp)pDoc->ch_sp=pDoc->ch_maxsp;
			
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			battle[4].Format(_T("sp포션을 사용했습니다"));
		pDoc->pstate=3;
		pDoc->battle_state=0;
	Invalidate(false);
	break;
		break;
	}
	}
	if(select==5){
	pDoc->pstate=3;
	pDoc->battle_state=0;
	
	Invalidate(false);
	break;
	} // 돌아가기
}
}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CRPGView::text_call(int index)
{
CRPGDoc* pDoc = GetDocument();
switch(index){ // 대화 관련 데이터베이스(?)
case 0:// NPC 운영자
         text_set(_T("운영자"),
	     _T("당신 저번의 그 슬라임?"),
	     _T("네 덕분에 이 마을을 구할수 있었어"),
	     _T("몸도 원래대로 돌아왔구나."),
		 _T("그런데 이 마을에 다시 찾아온 이유가"),
		 _T("드래곤을 진짜 쓰러뜨리기 위해서?"));
       break;
case 1: 
         text_set(_T("용사"),
	     _T("나는 새로운 용사로 거듭났어"),
	     _T("내가 슬라임의 몸으로는"),
	     _T("드래곤을 소멸시키지 못했지"),
		 _T("따라서 이번에이 말로"),
		 _T("정말 드래곤을 쓰러뜨릴거다..")); 
       break;
case 2: 
         text_set(_T("운영자"),
	     _T("하지만 그건 무리야"),
	     _T("당시의 드래곤은 당신을 너무 얉봤지.."),
	     _T("물론 너의 힘도 제대로 돌아왔지만"),
		 _T("드래곤이 제실력을 내면 훨씬 강하다구.."),
		 _T(""));
       break;
case 3: 
         text_set(_T("용사"),
	     _T("걱정 말라구.. 나는 강하니까"),
	     _T("누군가가 드래곤을 쓰러뜨리지 않으면"),
	     _T("곧 다시 모두 마법에 걸리고 말거야.."),
		 _T(""),
		 _T("그전에 꼭 막아야되!"));
       break;
case 4: 
         text_set(_T("운영자"),
	     _T("그래? 그렇다면 할수업지.."),
	     _T("일단 슬라임의 힘과 인간의 힘은 달라"),
	     _T("네가 다시 드래곤과 붙고싶다면"),
		 _T("몬스터를 잡으면서 일단 힘을키워봐.."),
		 _T("일단 전투 인터페이스는 다음과 같아"));
       break;
case 5: 
         text_set(_T("System"),
	     _T(" [ 전투 ]"),
	     _T("[1-6] : 행동 카드 사용"),
	     _T("  [7] : 아이템(포션 등) 사용"),
		 _T("  [8] : 도주 "),
		 _T("  [9] : 행동 카드 섞기(턴소모)"));
       break;
case 6: 
         text_set(_T("운영자"),
	     _T("그럼 행운을 빌어.."),
	     _T("드래곤의 억누르는 힘이 사라져서"),
	     _T("몬스터 또한 전보다 훨씬 강하다구"),
		 _T("물론 지금의 너라면"),
		 _T("충분히 잡을수 있을거야.."));
       break;
case 10: // NPC 상인
         text_set(_T("상인"),
	     _T("와우! 당신은!"),
	     _T("이 마을을 구하셨던 용사님!"),
	     _T("하지만 전 로봇이라"),
		 _T("질문에 대답해드릴순 없습니다"),
		 _T("물건을 사가세요"));
       break;
case 11: 
	
		 shopmenu=2; // 상점 입장
		 pDoc->pstate=4;
		 Invalidate();

         text_set(_T("상인"),
	     _T("저의 주인은 누군지 알아요?"),
	     _T("당연히 '운영자' 님이죠"),
	     _T("운영자님은 가장 강한분이지만"),
		 _T("아무곳도 개입은 안한답니다."),
		 _T(""));
       break;
case 12: 
         text_set(_T("상인"),
	     _T("몬스터가 예전보다 돈이 많죠?"),
	     _T("사실 원래는 수입의 1/2을"),
	     _T("드래곤에게 세금으로 내야했죠"),
		 _T("하지만 지금은 그럴필요가 없어요"),
		 _T(""));
       break;
case 20: // 드래곤 (보스) 와의 대화
         text_set(_T("드래곤"),
	     _T("크르릉.. 크르릉.."),
	     _T(""),
	     _T("?? 아니 너는!!"),
		 _T(""),
		 _T(""));
       break;
case 21: 
         text_set(_T("드래곤"),
	     _T("나의 마법을 풀어버린"),
	     _T("그 망할 슬라임 녀석이구만!!"),
	     _T("크르릉!!!"),
		 _T(""),
		 _T(""));
       break;
case 22: 
         text_set(_T("용사"),
	     _T("참 끈질긴 녀석이군.."),
	     _T("네놈이 아직 살아있었을 줄이야!"),
	     _T("이번에야 말로 목숨을 끊어주마!"),
		 _T(""),
		 _T(""));
       break;
case 23: 
         text_set(_T("드래곤"),
	     _T("하하하.. 가소롭군"),
	     _T("그당시엔 말이다"),
	     _T("내가 마을전체에 마법을 걸고"),
		 _T("있었기 때문에 나의 마력이"),
		 _T("분산되어있었지.."));
       break;
case 24: 
         text_set(_T("드래곤"),
	     _T("하지만 지금은 다르다.."),
	     _T("나의 모든 힘이 돌아왔고"),
	     _T("그 힘은 상상을 초월하지.."),
		 _T("네 녀석도 힘이 돌아왔다만"),
		 _T("한낱 인간의 힘일뿐"));
       break;
case 25: 
         text_set(_T("용사"),
	     _T("훗!! 과연 그럴까.."),
	     _T("슬라임의 몸으로도"),
	     _T("너를 쓰러뜨렸는데.."),
		 _T("그말인 즉슨 나는"),
		 _T("보통 인간과는 다르단거다"));
       break;
case 26: 
         text_set(_T("용사"),
	     _T("너로 인해 슬라임이 되고!"),
	     _T("그로 인해 받은 치욕!"),
	     _T("지금 풀어주마!"),
		 _T("나는 용사다!!"),
		 _T(""));
       break;
case 27: 
         text_set(_T("드래곤"),
	     _T("훗.. 10년전에도 있었지.."),
	     _T("나를 쓰러뜨리기 위해.."),
	     _T("자칭 [용사] 라고 말하는 "),
		 _T("어리석은 녀석이.."),
		 _T(""));
       break;
case 28: 
         text_set(_T("용사"),
	     _T("난 그 [용사]와는 다르다"),
	     _T("왜냐면.."),
	     _T("난.."),
		 _T("이게임의.."),
		 _T("주."));
       break;
case 29:     
         text_set(_T("용사"),
	     _T("난 그 [용사]와는 다르다"),
	     _T("왜냐면.."),
	     _T("난.."),
		 _T("이게임의.."),
		 _T("주.인"));
       break;
case 30: 
         text_set(_T("용사"),
	     _T("난 그 [용사]와는 다르다"),
	     _T("왜냐면.."),
	     _T("난.."),
		 _T("이게임의.."),
		 _T("주.인.공"));
       break;
case 31: 
       
         text_set(_T("용사"),
	     _T("난 그 [용사]와는 다르다"),
	     _T("왜냐면.."),
	     _T("난.."),
		 _T("이게임의.."),
		 _T("주.인.공 이기 때문이지.."));
       break;
case 32: 
         text_set(_T("드래곤"),
	     _T(".. 나눠서 말할필요는.."),
	     _T("에헴.. 암튼 네녀석이"),
	     _T("얼마나 터무니 없는 존재에"),
		 _T("도전 하는지를"),
		 _T("지금 깨닫게 해주마.."));
       break;
case 33: 
         text_set(_T("드래곤"),
	     _T("한낯 인간이 주제를 모르면"),
	     _T("어떠한 결과를 낳는지"),
	     _T("지금 깨닿게 해주겠다.."),
		 _T(""),
		 _T(""));
       break;
case 34: 
	  boss=true; // 드래곤과의 보스전 실행
	  battleset();
	  Invalidate();
         text_set(_T("드래곤"),
	     _T("으.. 으아아아악!!"),
	     _T("젠장.. 내가 또.."),
	     _T("인간따위에게.."),
		 _T(""),
		 _T(""));
       break;
case 35: 
         text_set(_T("용사"),
	     _T("훗.. 네녀석을 쓰러뜨렸으니"),
	     _T("이제 이 마을에는"),
	     _T("평화가 찾아오겠군.."),
		 _T(""),
		 _T("잘 가라.."));
       break;
case 36: 
         text_set(_T("드래곤"),
	     _T("하하하하하하하하..."),
	     _T("과연 그럴까.."),
	     _T("너는 드래곤 세계에서"),
		 _T("사천왕이 있다는걸 모르는구나"),
		 _T("하하하하"));
       break;
case 37: 
         text_set(_T("드래곤"),
	     _T("나는.. 그 사천왕중"),
	     _T("가장 약한 놈 중하나다."),
	     _T(""),
		 _T("이제 시작일 뿐이지."),
		 _T(""));
       break;
case 38: 
         text_set(_T("용사"),
	     _T("?? 뭐야!! 사천왕이라고??"),
	     _T("그런건 듣도 보도 못했어.."),
	     _T(""),
		 _T("이럴수가.."),
		 _T(""));
       break;
case 39: 
         text_set(_T("드래곤"),
	     _T(""),
	     _T("아마 내가 죽으면.."),
	     _T("나의 사천왕동료들이"),
		 _T("너를 죽이러 가겠지.."),
		 _T(""));
       break;
case 40: 
         text_set(_T("드래곤"),
	     _T("그리고.."),
	     _T(" 가장중요한.."),
	     _T("  우리의 보스.."),
		 _T(""),
		 _T("운영자님이 있으시다."));
       break;
case 41: 
         text_set(_T("용사"),
	     _T("뭣??"),
	     _T(""),
	     _T(""),
		 _T(""),
		 _T(""));
       break;
case 42: 
         text_set(_T("용사"),
	     _T("운영자라고?!!"),
	     _T("그건 무슨 말이야!!"),
	     _T(""),
		 _T(""),
		 _T(""));
       break;
case 43: 
         text_set(_T("드래곤"),
	     _T("사실 그가 운영자처럼"),
	     _T("행세를 하고 있지만"),
	     _T(""),
		 _T("사실.. 그는.."),
		 _T(".. 마왕이다."));
       break;
case 44: 
         text_set(_T("드래곤"),
	     _T("자세하게.."),
	     _T(" 알고싶으면"),
	     _T("그에게로 가봐라.."),
		 _T("나는... 으아아악.."),
		 _T("   (털썩)"));	 
       break;
case 45: 
         text_set(_T(""),
	     _T(""),
	     _T(""),
	     _T(""),
		 _T(""),
		 _T(""));		 
		 potal(4,1,1); // 드래곤에의한 엔딩맵 강제이동
		 Invalidate();
		 pDoc->chating=0;
		 dia=0;
       break;
case 50:  // 엔딩 스토리
         text_set(_T("운영자"),
	     _T("와우! 드래곤을 쓰러뜨리다니!!"),
	     _T("대단 하네요!!"),
	     _T("이제 모두 걱정없이 살수있어요!!."),
		 _T(""),
		 _T(""));		 
       break;
case 51: 
         text_set(_T("용사"),
	     _T("이자식!! 바른대로 말해!!"),
	     _T("네가 마왕이지!!"),
	     _T(""),
		 _T("다 듣고왔다!!"),
		 _T(""));		 
       break;
case 52: 
         text_set(_T("운영자"),
	     _T("어머.. 그게 무슨 말인가요?"),
	     _T("드래곤이 무슨 이상한말을 했나?"),
	     _T("하지만 드래곤은 거짓말을 잘해요.."),
		 _T("그런 말도 안되는 일이"),
		 _T("실제로 일어날일이 없잖아요.."));		 
       break;
case 53: 
         text_set(_T("용사"),
	     _T("그렇군.."),
	     _T("사실 생각해보니 말도안되긴했어.."),
	     _T("의심해서 미안해.."),
		 _T(" 난 이제부터"),
		 _T(" 사천왕과 마왕을 쓰러뜨리러 가겠어!!"));		 
       break;
case 54:
         text_set(_T("운영자"),
	     _T("그래야죠!! 하하"),
	     _T("그래야지 이마을에 평화가"),
	     _T("찾아 오거든요!"),
		 _T("그럼 나중에봐요!!"),
		 _T("   ..(씨익)   - E N D -"));		 
       break;
case 55: 
         text_set(_T(""),
	     _T(""),
	     _T(""),
	     _T(""),
		 _T(""),
		 _T(""));
		 exit(0);
       break;
 }
}


void CRPGView::battleset()
{
	CRPGDoc* pDoc = GetDocument();
	int random=rand()%3;


	// 디폴트로 슬라임 선택
	pDoc->mo_name=_T("(Lv 2)강한 슬라임"); // 슬라임의 출현
	pDoc->mo_hp=45;
	pDoc->mo_maxhp=45;
	pDoc->mo_exp=90;
	pDoc->mo_money=200;
	pDoc->mo_str=25;
	pDoc->mo_dex=15;
	pDoc->mo_xsize=91;
	pDoc->mo_ysize=65;
	pDoc->mo_num=0;

	if(pDoc->pmap==1){ // 전갈의 출현
	pDoc->mo_name=_T("(Lv 5)상점 귀뚜라미");
	pDoc->mo_hp=60;
	pDoc->mo_maxhp=60;
	pDoc->mo_exp=205;
	pDoc->mo_money=500;
	pDoc->mo_str=30;
	pDoc->mo_dex=20;
	pDoc->mo_xsize=114;
	pDoc->mo_ysize=121;
	pDoc->mo_num=1;
	}
	else if(pDoc->pmap==2){ // 새끼용의 출현
	pDoc->mo_name=_T("(Lv 8)어른용");
	pDoc->mo_hp=90;
	pDoc->mo_maxhp=90;
	pDoc->mo_exp=450;
	pDoc->mo_money=1350;
	pDoc->mo_str=35;
	pDoc->mo_dex=20;
	pDoc->mo_xsize=192;
	pDoc->mo_ysize=196;
	pDoc->mo_num=2;
	}

	if(boss&&pDoc->pmap==2){ // 드래곤
	pDoc->mo_name=_T("(Lv 15)드래곤");
	pDoc->mo_hp=150;
	pDoc->mo_maxhp=200;
	pDoc->mo_exp=3500;
	pDoc->mo_money=5000;
	pDoc->mo_str=40;
	pDoc->mo_dex=25;
	pDoc->mo_xsize=192;
	pDoc->mo_ysize=196;
	pDoc->mo_num=3;
	}
	else if(pDoc->pmap==4||pDoc->pmap==5){ // 마왕 고스트(탈출 숲)
	pDoc->mo_name=_T("(Lv 20)마왕고스트");
	pDoc->mo_hp=225;
	pDoc->mo_maxhp=150;
	pDoc->mo_exp=2000;
	pDoc->mo_money=3500;
	pDoc->mo_str=40;
	pDoc->mo_dex=50;
	pDoc->mo_xsize=192;
	pDoc->mo_ysize=196;
	pDoc->mo_num=0;
	}
	pDoc->pstate=3;
}

void CRPGView::potal(int map, int xpos, int ypos)
{
 CRPGDoc* pDoc = GetDocument();
 pDoc->pmap=map;
 pDoc->xPos=xpos;
 pDoc->yPos=ypos;
}

void CRPGView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnLButtonDown(nFlags, point);
}
