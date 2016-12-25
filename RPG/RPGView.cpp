
// RPGView.cpp : CRPGView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "RPG.h"
#endif

#include "RPGDoc.h"
#include "RPGView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAP_X 45 // ����½� 1x1 ���� x ���� ũ��
#define MAP_Y 45 // ����½� 1x1 ���� y ���� ũ��


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

// CRPGView ����/�Ҹ�

CRPGView::CRPGView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	font1.CreateFont(20,15,0,0,1,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,
		   DEFAULT_PITCH | FF_DONTCARE,_T("����ü")); // ��Ʈ �ʱ�ȭ
	font2.CreateFont(25,15,0,0,1,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,
		   DEFAULT_PITCH | FF_DONTCARE,_T("�ü�ü"));
    font3.CreateFont(30,30,0,0,1,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,
		   DEFAULT_PITCH | FF_DONTCARE,_T("����ü"));
	font4.CreateFont(30,20,0,0,1,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,
		   DEFAULT_PITCH | FF_DONTCARE,_T("����"));
	boss=false; // ������ üũ �ʱ�ȭ
	keydown=0; // Ű ���� üũ ���� �ʱ�ȭ
	dia=0;  // ���̾�α� �ʱ�ȭ
	title=0; // Ÿ��Ʋ ���� �޴� �ʱ�ȭ
	shopmenu=0; // ���� ���� �޴� �ʱ�ȭ
	menu=0; // �Ϲ� �޴� �ʱ�ȭ
	menu1=0; // �Ϲ� �޴� ���� �ʱ�ȭ
	select=0; // ������ ������ ���� �ʱ�ȭ
	shop_text.Format(_T("���� ������ �����ϼ���"));
	bgm=0;
}

CRPGView::~CRPGView()
{
}

BOOL CRPGView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CRPGView �׸���

void CRPGView::OnDraw(CDC* /*pDC*/)
{
	CRPGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.


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


// CRPGView ����

#ifdef _DEBUG
void CRPGView::AssertValid() const
{
	CView::AssertValid();
}

void CRPGView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRPGDoc* CRPGView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRPGDoc)));
	return (CRPGDoc*)m_pDocument;
}
#endif //_DEBUG


// CRPGView �޽��� ó����
// CRPGView �޽��� ó����
int MAP[6][16][16]={   // �ʼ����� 3���� �迭�� [�ʹ�ȣ][Y��ǥ][X��ǥ]
	{                  // ���ڸ�����=�̺�Ʈ  
		               // õ���ڸ�+�����ڸ�=��ĨX��ǥ
		               // �����ڸ�+�����ڸ�=��ĨY��ǥ
{   600,   600,   600,   600, 52915,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600,   600}, //�ʿ��� 00
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
{  1412,  1412,  1412,  1412,  1412,  1412,  1412,  1412,  1412, 31000,  1412,  1412,  1412,  1412,  1412,  1412}, // ������ 01
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
{   900,   900,   900,   900,   900,   900,   900,   900,   900,   900,   900,   900,   900,   900,   900,   900}, // ������ 02
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
{   702,   702,   702,   702,   603, 30700,   603,   702,   702,   702,   702,   702,   702,   702,   702,   702}, // ������ 03
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
{   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702}, // �̷θ� 04
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
{   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702,   702}, // �̷θ� 05
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CView::OnPaint()��(��) ȣ������ ���ʽÿ�.
CDC MemDC;
MemDC.CreateCompatibleDC(&dc);
CBitmap bmp[15],*pbmp;
bmp[0].LoadBitmapW(IDB_BITMAP1);// ��
bmp[4].LoadBitmapW(IDB_BITMAP6);// ���� ���
bmp[5].LoadBitmapW(IDB_BITMAP7);// ������
bmp[6].LoadBitmapW(IDB_BITMAP8);// ���� �������̽�
bmp[7].LoadBitmapW(IDB_BITMAP9);// �ͶѶ��
bmp[8].LoadBitmapW(IDB_BITMAP10);// �巡��
bmp[9].LoadBitmapW(IDB_BITMAP11);// �������
bmp[10].LoadBitmapW(IDB_BITMAP12);// �ǳ����
bmp[11].LoadBitmapW(IDB_BITMAP13);// �������
bmp[12].LoadBitmapW(IDB_BITMAP14);// �Ϲ� �޴� ���
pbmp=MemDC.SelectObject(&bmp[0]);

if((pDoc->pstate)==0){
int mapNUM=pDoc->pmap; // mapNUM�� ���缱�õȸ� , pmap���� �޾ƿ�
for(int x=0;x<16;x++){
	for(int y=0;y<16;y++){
MapDraw(x,y,(MAP[mapNUM][y][x]%10000)/100,MAP[mapNUM][y][x]%100,MemDC,dc);
	}
}
if(pDoc->pmap==3&&pDoc->xPos==5&&pDoc->yPos==0) // ������ǳ� ��Ż
{
 potal(1,2,14);
 Invalidate();
}
if(pDoc->pmap==1&&pDoc->xPos==2&&pDoc->yPos==15) // �ǳ��浿�� ��Ż
{
 potal(3,5,1);
 Invalidate();
}
if(pDoc->pmap==1&&pDoc->xPos==9&&pDoc->yPos==0) // �ǳ��漳�� ��Ż
{
 potal(2,3,14);
 Invalidate();
}
if(pDoc->pmap==2&&pDoc->xPos==3&&pDoc->yPos==15) // ������ǳ� ��Ż
{
 potal(1,9,1);
 Invalidate();
}
if(pDoc->pmap==4&&pDoc->xPos==15&&pDoc->yPos==13) // �̷�1��̷�2 ��Ż
{
 potal(5,1,2);
 Invalidate();
}
if(pDoc->pmap==5&&pDoc->xPos==0&&pDoc->yPos==2) // �̷�2��̷�1 ��Ż
{
 potal(4,14,13);
 Invalidate();
}

if(pDoc->chating){ // NPC�� ��ȭ���϶� ȭ�� ����Լ�
bmp[1].LoadBitmapW(IDB_BITMAP2);
pbmp=MemDC.SelectObject(&bmp[1]);
dc.StretchBlt(0,480,720,250,&MemDC,0,0,734,177,SRCCOPY);
MemDC.SelectObject(pbmp);
npc_chating(npc_name,chat_line1,chat_line2,chat_line3,chat_line4,chat_line5,dc);
}
bmp[2].LoadBitmapW(IDB_BITMAP3);
pbmp=MemDC.SelectObject(&bmp[2]);
if(pDoc->parrow==2)  // ��
dc.TransparentBlt((pDoc->xPos)*MAP_X,(pDoc->yPos)*MAP_Y,MAP_X,MAP_Y,&MemDC,0,0,32,32,RGB(255,255,255));
if(pDoc->parrow==1)  // ��
dc.TransparentBlt((pDoc->xPos)*MAP_X,(pDoc->yPos)*MAP_Y,MAP_X,MAP_Y,&MemDC,0,96,32,32,RGB(255,255,255));
if(pDoc->parrow==3)  // ����
dc.TransparentBlt((pDoc->xPos)*MAP_X,(pDoc->yPos)*MAP_Y,MAP_X,MAP_Y,&MemDC,0,32,32,32,RGB(255,255,255));
if(pDoc->parrow==4)  //������
dc.TransparentBlt((pDoc->xPos)*MAP_X,(pDoc->yPos)*MAP_Y,MAP_X,MAP_Y,&MemDC,0,64,32,32,RGB(255,255,255));
   }
bmp[3].LoadBitmapW(IDB_BITMAP4);
if(pDoc->pstate==1){ // �޴�ȭ�� ���
	CString str;
	dc.SelectObject(&font3);
	dc.SetBkMode(TRANSPARENT); // TextOut�� ���� ������ �����ϰ���
	pbmp=MemDC.SelectObject(&bmp[12]);
	dc.StretchBlt(0,0,720,800,&MemDC,0,0,691,656,SRCCOPY);

	dc.Ellipse(40+(menu*250),160+(menu1*95),70+(menu*250),190+(menu1*95)); // ����

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
if(pDoc->pstate==2){ // Ÿ��Ʋ
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
if(pDoc->pstate==3||pDoc->pstate==5){ // ����ȭ��
BITMAP bmpInfo;
BLENDFUNCTION bf;
dc.Rectangle(0,0,800,800);
if(pDoc->pmap==0||pDoc->pmap==3||pDoc->pmap>=4){ // ������� �����϶�
bmp[4].GetBitmap(&bmpInfo);
pbmp=MemDC.SelectObject(&bmp[4]);
}
if(pDoc->pmap==1){ // ������� �ǳ��϶�
bmp[10].GetBitmap(&bmpInfo);
pbmp=MemDC.SelectObject(&bmp[10]);
}
if(pDoc->pmap==2){ // ������� �����϶�
bmp[9].GetBitmap(&bmpInfo);
pbmp=MemDC.SelectObject(&bmp[9]);
}
bf.BlendOp = AC_SRC_OVER;
bf.BlendFlags = 0;
bf.SourceConstantAlpha = 70;
bf.AlphaFormat = 0;
dc.AlphaBlend(0,0,800,800,&MemDC,0,0,bmpInfo.bmWidth, bmpInfo.bmHeight, bf);
MemDC.SelectObject(pbmp);
if(pDoc->mo_num==0)pbmp=MemDC.SelectObject(&bmp[5]);//������
if(pDoc->pmap==0)pbmp=MemDC.SelectObject(&bmp[5]); // ������ ���϶� �����Ӽ���
if(pDoc->mo_num==1)pbmp=MemDC.SelectObject(&bmp[7]);//�ͶѶ��
if(pDoc->mo_num==2||pDoc->mo_num==3)pbmp=MemDC.SelectObject(&bmp[8]);//������,�巡��

		
		if(bgm==0&&pDoc->mo_num==0) //������ ���� ����
		{
			PlaySound(_T(".\\slime.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			bgm++;
		}
		else if(bgm==0&&pDoc->mo_num==1) //�ͶѶ�� ���� ����
		{
			PlaySound(_T(".\\zun.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			bgm++;
		}
		else if(bgm==0&&pDoc->mo_num==2) //������ ���� ����
		{
			PlaySound(_T(".\\babydragon.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			bgm++;
		}
		else if(bgm==0&&pDoc->mo_num==3) //�巡�� ���� ����
		{
			PlaySound(_T(".\\dragon.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			bgm++;
		}

if(pDoc->mo_num!=3)dc.TransparentBlt(300,200,((pDoc->mo_xsize)+200)/2,((pDoc->mo_ysize)+200)/2,&MemDC,0,0,
	pDoc->mo_xsize,pDoc->mo_ysize,RGB(255,255,255)); // ���� ȭ�� ���
else {
	dc.TransparentBlt(150,100,((pDoc->mo_xsize)+200),((pDoc->mo_ysize)+200),&MemDC,0,0,
	pDoc->mo_xsize,pDoc->mo_ysize,RGB(255,255,255)); // ������ �巡���϶� ȭ�� ���
}
pbmp=MemDC.SelectObject(&bmp[6]);
dc.Rectangle(25,600,475,750);
for(int i=0;i<5;i++)dc.TextOutW(30,620+25*i,battle[i]); // ���� �����Ȳ ���
srand((unsigned)time(NULL));
CString str;
dc.SetBkMode(TRANSPARENT);
for(int i=0;i<9;i++){       // 1~9���� Ű���� �������̽� ���� ���
str.Format(_T("[ %d ]"),i+1);
dc.TextOutW(510+100*(i%3),630-100*(i/3),str);
}

for(int i=0;i<6;i++){    // 1~6���� �÷��̾� ���� ī�� ȭ�� ���
dc.TransparentBlt(480+100*(i%3),650-100*(i/3),80,80,&MemDC,
	(pDoc->card[i]%3)*72,(pDoc->card[i]/3)*70,72,70,RGB(255,255,255));
}
for(int i=6;i<9;i++){ // 7~9���� ���� ī�� ȭ�� ���
dc.TransparentBlt(250+100*(i%3),60,70,70,&MemDC,
	(pDoc->card[i]%3)*72,(pDoc->card[i]/3)*70,72,70,RGB(255,255,255));
}
/*7~9���� �÷��̾� �������̽� ȭ�� ���*/
dc.TransparentBlt(480,450,80,80,&MemDC,0,140,72,70,RGB(255,255,255));
dc.TransparentBlt(580,450,80,80,&MemDC,72,140,72,70,RGB(255,255,255));
dc.TransparentBlt(680,450,80,80,&MemDC,144,140,72,70,RGB(255,255,255));

/* HP,SP,����ġ�� ��� */
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

if(pDoc->pstate==5){ // ������ ������ �����϶�
	
	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(&font2);
	CString str;
	if(select==0)dc.TextOutW(20,350,_T(" �����ϼ��� ��"));
	if(select==1){ // HP���ǻ��
		str.Format(_T("�� HP ���� �� : %d��"),pDoc->hp_potion);
		dc.TextOutW(20,350,str);}
	if(select==2){// SP���ǻ��
		str.Format(_T("�� SP ���� �� : %d��"),pDoc->mp_potion);
		dc.TextOutW(20,350,str); }
	if(select==3)dc.TextOutW(20,350,_T("�� ��������� �� : 0��"));
	if(select==4)dc.TextOutW(20,350,_T("�� ���ǥâ �� : 0��"));
	if(select==5)dc.TextOutW(20,350,_T("�� ���ư���"));
}
}
if(pDoc->pstate==4){ // ����ȭ��
 pbmp=MemDC.SelectObject(&bmp[11]);
 dc.StretchBlt(0,0,720,720,&MemDC,0,0,720,720,SRCCOPY);
 dc.SelectObject(&font2);
 if(shopmenu==0){ // HP���� ���� Ŀ��
 dc.Rectangle(110,460,140,490);
 dc.Rectangle(210,460,240,490);
 }
 if(shopmenu==1){ // SP���� ���� Ŀ��
 dc.Rectangle(350,460,380,490);
 dc.Rectangle(450,460,480,490);
 }
 if(shopmenu==3){ // ���������(?) ���� Ŀ��
 dc.Rectangle(570,460,600,490);
 dc.Rectangle(720,460,750,490);
 }
 /*if(shopmenu==3){ // ���ư���
 dc.Rectangle(570,460,590,490);
 dc.Rectangle(730,460,750,40);
 }*/
 CString str;
 str.Format(_T("%d Gold"),pDoc->ch_money); // ������ ǥ��
 dc.TextOutW(600,80,str);
 str.Format(_T("%d"),pDoc->hp_potion); // HP���� ���� ������ ǥ��
 dc.TextOutW(180,400,str);
 str.Format(_T("%d"),pDoc->mp_potion); // SP���� ���� ������ ǥ��
 dc.TextOutW(420,400,str);
 str.Format(_T("%s"),shop_text); // ���� �ŷ� ���� ǥ��
 dc.TextOutW(100,100,str);
 }
}


void CRPGView::MapDraw(int dx, int dy,int mx,int my, CDC &mem,CPaintDC &dc)  // �ʱ׸���(����Ʈ)
{
dc.StretchBlt(0+dx*MAP_X,0+dy*MAP_Y,MAP_X,MAP_Y,&mem,0+16*mx,0+16*my,16,16,SRCCOPY);
}

void CRPGView::MapDraw(int dx, int dy,int mx,int my, CDC &mem,CClientDC &dc) // �ʱ׸���(Ŭ���̾�Ʈ)
{
dc.StretchBlt(0+dx*MAP_X,0+dy*MAP_Y,MAP_X,MAP_Y,&mem,0+16*mx,0+16*my,16,16,SRCCOPY);
}


void CRPGView::npc_chating(CString name, CString text1,
	   CString text2,CString text3,CString text4,CString text5,CPaintDC &dc)
{  //��ȭ �ؽ�Ʈ ǥ��
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
{ //��ȭ �ؽ�Ʈ ����
npc_name=npc;
chat_line1=str1;
chat_line2=str2;
chat_line3=str3;
chat_line4=str4;
chat_line5=str5;
}

int Move[16][30]={ // Ÿ�� �̵��Ұ� ����
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

CRPGDoc* pDoc = GetDocument();
// ȭ�� ����� ���� BMP �ε�
CClientDC dc(this);
CDC MemDC;
MemDC.CreateCompatibleDC(&dc);
CBitmap bmp,bmp2,bmp3,bmp4,*pbmp;
bmp2.LoadBitmapW(IDB_BITMAP1);
bmp.LoadBitmapW(IDB_BITMAP2);
bmp3.LoadBitmapW(IDB_BITMAP3);
bmp4.LoadBitmapW(IDB_BITMAP4);
pbmp=MemDC.SelectObject(&bmp);

// �����¿� �������� �������� ����
int mapnumLeft=MAP[(pDoc->pmap)][(pDoc->yPos)][(pDoc->xPos)-1];
int mapnumRight=MAP[(pDoc->pmap)][(pDoc->yPos)][(pDoc->xPos)+1];
int mapnumUP=MAP[(pDoc->pmap)][(pDoc->yPos)-1][(pDoc->xPos)];
int mapnumDown=MAP[(pDoc->pmap)][(pDoc->yPos)+1][(pDoc->xPos)];


if((pDoc->pstate)==0){ // �ʻ� ������
if(!keydown&&pDoc->pstate==0&&pDoc->chating==1){
switch(nChar){
case VK_SPACE:
case VK_RETURN:
	pDoc->chating=2; // ��ȭ���� ������ �ٷ� ������ �����ؼ� �о����°� �����ϱ� ���� ���� [2������]
	Invalidate(false);
	break;
}
}

if(!keydown&&pDoc->pstate==0&&(pDoc->chating==0||pDoc->chating>=3)){ // ���̵���
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
		if(Move[mapy][mapx]==0){ // �̵����� üũ
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
		if(Move[mapy][mapx]==0){ // �̵����� üũ
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
		if(Move[mapy][mapx]==0){ // �̵����� üũ
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
		if(Move[mapy][mapx]==0){ // �̵����� üũ
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
	int lx,ly; // NPC�� �ٶ󺸴� ���� �ν�
	if(pDoc->parrow==1){lx=0; ly=-1;}
	if(pDoc->parrow==2){lx=0; ly=1;}
	if(pDoc->parrow==3){lx=-1; ly=0;}
	if(pDoc->parrow==4){lx=1; ly=0;}

	if(pDoc->chating==0&&dia==0&& // NPC ��� (000~006)
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

	if(pDoc->chating==0&&dia==0&& // NPC ���� (010~012)
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

	if(pDoc->chating==0&&dia==0&& // �巡�� (020~045)
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

	if(pDoc->chating==0&&dia==0&& // ���� (050~055)
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
case VK_ESCAPE: // �޴�ȭ�� ����
	pDoc->pstate=1;
		PlaySound(_T("menu.wav"),AfxGetInstanceHandle(),  SND_ASYNC);
	Invalidate();
break;
	}

}
}
if(!keydown&&pDoc->pstate==0&&pDoc->chating==2){ // ��ȭ ������
switch(nChar){
case VK_SPACE:
case VK_RETURN:
	pDoc->chating=0;
	Invalidate(false);
    break;
}
}
if(pDoc->pstate==1){         //�޴�
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
	if(menu==0&&menu1==0){pDoc->pstate=0;PlaySound(_T(".\\menu2.wav"),AfxGetInstanceHandle(),  SND_ASYNC);} // �ǵ��ư���
	if(menu==1&&menu1==0){
		PlaySound(_T(".\\KT1.wav"), AfxGetInstanceHandle(),  SND_ASYNC);	
		CFile file;
		CFileException e;
		if(!file.Open(_T("save.dat"),CFile::modeWrite|CFile::modeCreate,&e))
		{
			e.ReportError();
			return;
		}
		CArchive ar(&file,CArchive::store); // �����ϱ�
		ar<<pDoc->ch_dex<<pDoc->ch_exp<<pDoc->ch_hp<<
			pDoc->ch_level<<pDoc->ch_maxexp<<pDoc->ch_maxhp<<
			pDoc->ch_maxsp<<pDoc->ch_money<<pDoc->ch_skillpoint<<pDoc->ch_sp<<pDoc->ch_str<<
			pDoc->xPos<<pDoc->yPos<<pDoc->card[0]<<pDoc->card[1]<<
			pDoc->card[2]<<pDoc->card[3]<<pDoc->card[4]<<pDoc->card[5]<<
			pDoc->pmap<<pDoc->hp_potion<<pDoc->mp_potion<<pDoc->parrow;
	} // �����ϱ�
	if(menu==2){exit(0);} // �����ϱ�
	if(menu==0&&menu1==1){if(pDoc->ch_skillpoint>0){ pDoc->ch_str++; pDoc->ch_skillpoint--;}}
	if(menu==1&&menu1==1){if(pDoc->ch_skillpoint>0){ pDoc->ch_dex++; pDoc->ch_skillpoint--;}}
	Invalidate();
	break;
 }
}

if(pDoc->pstate==2){ // Ÿ��Ʋ �޴�ȭ�� Ű���� �ν�
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
	if(title==0){pDoc->pstate=0;PlaySound(_T(".\\KT1.wav"),AfxGetInstanceHandle(),  SND_ASYNC);} // ó���ϱ�
	if(title==1) // �̾��ϱ�
	{
		CFile file;
		CFileException e;
		if(!file.Open(_T("save.dat"),CFile::modeRead,&e))
		{
			e.ReportError();
			return;
		}
		CArchive ar(&file,CArchive::load);
		ar>>pDoc->ch_dex>>pDoc->ch_exp>> // ���Ϸε�
			pDoc->ch_hp>>pDoc->ch_level>>pDoc->ch_maxexp>>
			pDoc->ch_maxhp>>pDoc->ch_maxsp>>pDoc->ch_money>>
			pDoc->ch_skillpoint>>pDoc->ch_sp>>pDoc->ch_str>>
			pDoc->xPos>>pDoc->yPos>>pDoc->card[0]>>pDoc->card[1]>>
			pDoc->card[2]>>pDoc->card[3]>>pDoc->card[4]>>pDoc->card[5]>>
			pDoc->pmap>>pDoc->hp_potion>>pDoc->mp_potion>>pDoc->parrow;
		pDoc->pstate=0;
		PlaySound(_T(".\\KT1.wav"),AfxGetInstanceHandle(),  SND_ASYNC);
	} // �̾��ϱ�

	if(title==2){exit(0);} // �����ϱ�
	Invalidate();
	break;
 }
}

if(pDoc->pstate==3){ // ����ȭ�� Ű���� �ν�
int number;
if(nChar==VK_NUMPAD1)number=0; // 1~6���� �÷��̾�ī��
if(nChar==VK_NUMPAD2)number=1;
if(nChar==VK_NUMPAD3)number=2;
if(nChar==VK_NUMPAD4)number=3;
if(nChar==VK_NUMPAD5)number=4;
if(nChar==VK_NUMPAD6)number=5;
if(nChar==VK_NUMPAD7)number=10; // ������ ���
if(nChar==VK_NUMPAD8)number=20; // ����(������ �Ұ�)
if(nChar==VK_NUMPAD9)number=30; // ī�弯��(SP10�Ҹ�)
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
	if(pDoc->battle_state==0){//�÷��̾� �ൿ
		
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
			battle[4]=_T("����� ����!"); Invalidate(); Sleep(500);
			if(damage<=0){
			battle[4]=_T("����� ������ ��������!");
			PlaySound(_T(".\\fail.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else if(monster==1){
			battle[4]=_T("���Ͱ� �� �Ͽ� �ҿ��� ������.");
			PlaySound(_T(".\\defence.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else if(monster==4&&(rand()%3)){
			 battle[4]=_T("���Ͱ� ������ ȸ���Ͽ����ϴ�.");
			 PlaySound(_T(".\\fail.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else{
				battle[4].Format(_T("����� ����! %s ���� %d �� �������� �־���."),pDoc->mo_name,damage);
				(pDoc->mo_hp)-=damage;
				PlaySound(_T(".\\attack.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
				if(pDoc->mo_hp<0)pDoc->mo_hp=0;
			}
			Invalidate();
			pDoc->battle_state=1;
		}
		if(pDoc->card[number]==1&&pDoc->battle_state==0){// Defense
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			battle[4]=_T("�̹��Ͽ� �� �մϴ�!"); Invalidate(); Sleep(500);
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
			battle[4]=_T("����� ����!"); Invalidate(); Sleep(500);
			if(damage<=0){
			battle[4]=_T("����� ������ ��������!");
			PlaySound(_T(".\\fail2.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else if(monster==3){
			int mondex=rand()%(pDoc->mo_dex)+rand()%(pDoc->mo_dex)+rand()%(pDoc->mo_dex)
				+(rand()%2)*(pDoc->ch_dex);
			int mondamage=(rand()%(pDoc->mo_str)+rand()%(pDoc->mo_str))/2+1;
				battle[4].Format(_T("������ Ʈ���� �ɷȴ�. %d �� �������� �Ծ���."),mondex);
				PlaySound(_T(".\\trap.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
				(pDoc->ch_hp)-=mondex;
				if(pDoc->ch_hp<0)pDoc->ch_hp=0;
			}
			else if(monster==4&&(rand()%3)){
			 battle[4]=_T("���Ͱ� ������ ȸ���Ͽ����ϴ�.");
			  PlaySound(_T(".\\fail.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else{
				battle[4].Format(_T("����� ����! %s ���� %d �� �������� �־���."),pDoc->mo_name,damage);
				 PlaySound(_T(".\\attack2.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
				(pDoc->mo_hp)-=damage;
				if(pDoc->mo_hp<0)pDoc->mo_hp=0;
			}
			Invalidate();
			pDoc->battle_state=1;
		}
		else if(pDoc->card[number]==3&&pDoc->battle_state==0){// Trap
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			battle[4]=_T("Ʈ���� ��ġ�Ͽ����ϴ�!"); 
			PlaySound(_T(".\\traping.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			Invalidate(); Sleep(500);
			
			if(pDoc->ch_sp<pDoc->ch_maxsp)pDoc->ch_sp++;
			Invalidate();
			pDoc->battle_state=1;
		}
		else if(pDoc->card[number]==4&&pDoc->battle_state==0){// Avoid
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			battle[4]=_T("�̹��Ͽ� ȸ�Ǹ� �õ��մϴ�."); Invalidate(); Sleep(500);
			Invalidate();
			pDoc->battle_state=1;
		}
		else if(pDoc->card[number]==5&&pDoc->battle_state==0){// HyperSkill
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			battle[4]=_T("������ ��ų! �������� ���� SP�� ����մϴ�.");
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			int dex=rand()%(pDoc->ch_dex)+rand()%(pDoc->ch_dex)+
				rand()%(pDoc->ch_dex)+rand()%(pDoc->ch_dex)+(rand()%2)*(pDoc->ch_dex);
			int damage=((rand()%(pDoc->ch_str)+rand()%(pDoc->ch_str))/2)
				+((rand()%(pDoc->ch_str)+rand()%(pDoc->ch_str))*pDoc->ch_sp)/25+1;
            damage=(dex>pDoc->mo_dex)?damage:0;
			Invalidate(); Sleep(500);
			pDoc->ch_sp=0;
			if(damage<=0){
			battle[4]=_T("������ ��ų�� ��������!");
			PlaySound(_T(".\\fail.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else if(monster==1){
			battle[4].Format(_T("���Ͱ� ���Ͽ� %d �� �������ۿ� ���� ���ߴ�."),damage/4);
			PlaySound(_T(".\\hyper1.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
				(pDoc->mo_hp)-=(damage/4);
				if(pDoc->mo_hp<0)pDoc->mo_hp=0;
			}
			else if(monster==4&&(rand()%3)){
			 battle[4]=_T("���Ͱ� ������ ȸ���Ͽ����ϴ�.");
			 PlaySound(_T(".\\fail.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else{
				battle[4].Format(_T("������ ��ų�� %s ���� %d �� �������� �־���."),pDoc->mo_name,damage);
				PlaySound(_T(".\\hyper2.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
				(pDoc->mo_hp)-=damage;
				if(pDoc->mo_hp<0)pDoc->mo_hp=0;
			}
			Invalidate();
			pDoc->battle_state=1;
		}
	  }
		else if(number==10){//������
			pDoc->pstate=5;
			select=0;
	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(&font2);
			dc.TextOutW(20,350,_T(" �����ϼ��� ��"));
			break;
		}
		else if(number==20){
			if(pDoc->mo_num==3){	
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			battle[4]=_T("���������� ����ĥ�� �����ϴ�.");
			PlaySound(_T(".\\System2.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
				pDoc->battle_state=0;
				Invalidate();
			}
		    else {
				pDoc->pstate=0;Invalidate();
			}
			break;}//����
		else if(number==30){ //ī�� ����
			if(pDoc->ch_sp>=10){
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			battle[4]=_T("����� ī�� ������ �����Ͽ����ϴ�.");
			PlaySound(_T(".\\System2.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else{
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			battle[4]=_T("ī�帮�¿� SP�� 10�ʿ��մϴ�.");
			PlaySound(_T(".\\System2.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			Invalidate();
			pDoc->battle_state=1;
		}
	}
	Invalidate();
	if(pDoc->battle_state==1){//���� �ൿ
		srand((unsigned)time(NULL));
		Sleep(20+rand()%30);
		if(monster==0&&pDoc->battle_state==1){// Attack
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			int dex=rand()%(pDoc->mo_dex)+rand()%(pDoc->mo_dex)+rand()%(pDoc->mo_dex)
				+(rand()%2)*(pDoc->mo_dex);
			int damage=(rand()%(pDoc->mo_str)+rand()%(pDoc->mo_str))/2+1;
            damage=(dex>pDoc->ch_dex)?damage:0;
			battle[4]=_T("������ ����!"); Invalidate(); Sleep(500);
			if(damage<=0){
			battle[4]=_T("������ ������ ��������!");
			PlaySound(_T(".\\fail.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else if(pDoc->card[number]==1){
			battle[4]=_T("�÷��̾ ���Ͽ� �ҿ��� ������.");
			PlaySound(_T(".\\defence.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else if(pDoc->card[number]==4&&(rand()%3)){
			 battle[4]=_T("�÷��̾ ������ ȸ���Ͽ����ϴ�.");
			 PlaySound(_T(".\\fail.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else{
				battle[4].Format(_T("������ ����! ��ſ��� %d �� �������� �־���."),damage);
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
			battle[4]=_T("������ ����!"); Invalidate(); Sleep(500);
			if(damage<=0){
			battle[4]=_T("������ ������ ��������!");
			PlaySound(_T(".\\fail.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}

			else if(pDoc->card[number]==3){
			int chdex=rand()%(pDoc->ch_dex)+rand()%(pDoc->ch_dex)+rand()%(pDoc->ch_dex)
				+(rand()%2)*(pDoc->mo_dex);
			int chdamage=(rand()%(pDoc->ch_str)+rand()%(pDoc->ch_str))/2+1;
				battle[4].Format(_T("���Ͱ� ������ Ʈ���� �ɷȴ�. %d �� �������� �Ծ���."),chdex);
				PlaySound(_T(".\\trap.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
				(pDoc->mo_hp)-=chdex;
				if(pDoc->mo_hp<0)pDoc->mo_hp=0;
			}
			else if(pDoc->card[number]==4&&(rand()%3)){
			 battle[4]=_T("�÷��̾ ������ ȸ���Ͽ����ϴ�.");
			 PlaySound(_T(".\\fail.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else{
				battle[4].Format(_T("������ ����! ��ſ��� %d �� �������� �־���."),damage);
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
			battle[4]=_T("������ ������ ��ų!!!");
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			int dex=rand()%(pDoc->mo_dex)+rand()%(pDoc->mo_dex)+
				rand()%(pDoc->mo_dex)+rand()%(pDoc->mo_dex)+(rand()%2)*(pDoc->mo_dex);
			int damage=((rand()%(pDoc->mo_str)+rand()%(pDoc->mo_str))/2)
				+((rand()%(pDoc->mo_str)+rand()%(pDoc->mo_str))*100)/25+1;
            damage=(dex>pDoc->ch_dex)?damage:0;
			Invalidate(); Sleep(500);
			if(damage<=0){
			battle[4]=_T("������ ��ų�� ��������!");
			PlaySound(_T(".\\fail.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else if(pDoc->card[number]==1){
			battle[4].Format(_T("�÷��̾ ���Ͽ� %d �� �������ۿ� ���� ���ߴ�."),damage/4);
			PlaySound(_T(".\\hyper1.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			if(pDoc->ch_sp<pDoc->ch_maxsp)pDoc->ch_sp++;
				(pDoc->ch_hp)-=(damage/4);
				if(pDoc->ch_hp<0)pDoc->ch_hp=0;
			}
			else if(pDoc->card[number]==4&&(rand()%3)){
			 battle[4]=_T("���Ͱ� ������ ȸ���Ͽ����ϴ�.");
			 PlaySound(_T(".\\fail.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			}
			else{
				battle[4].Format(_T("������ ��ų�� �÷��̾ %d�� �������� �Ծ���."),damage);
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

	if(number==30&&!(pDoc->battle_state==2)){ //ī�� ����
			if(pDoc->ch_sp>=10){
				for(int i=0;i<6;i++)pDoc->card[i]=rand()%31/6;
				pDoc->ch_sp-=10;
			}
			pDoc->battle_state=0;
			
		}
	if(pDoc->mo_hp<=0&&!(pDoc->battle_state==2)){ //�¸�
		PlaySound(_T(".\\victory.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
		bgm=0;
		CString str;
		battle[0]=_T("�ڡڡ��������� �¸��ߴ�.�ڡڡ�");
		str.Format(_T(" %d Gold �� ȹ�� �ߴ�. "),pDoc->mo_money);
		pDoc->ch_money+=pDoc->mo_money;
		battle[1].Format(str);
		str.Format(_T(" %d �� Exp�� ȹ�� �ߴ�. "),pDoc->mo_exp);
		pDoc->ch_exp+=pDoc->mo_exp;
		battle[2].Format(str);
		battle[3]=_T("�ڡڡڡڡڡڡڡڡڡڡڡ�");
		while(pDoc->ch_exp>=pDoc->ch_maxexp){
			pDoc->ch_exp-=pDoc->ch_maxexp;
			pDoc->ch_maxexp=pDoc->ch_maxexp+(pDoc->ch_level*pDoc->ch_level)*5;
			(pDoc->ch_level)++;
			pDoc->ch_maxhp=pDoc->ch_maxhp+10+pDoc->ch_level+(pDoc->ch_str)/5;
			pDoc->ch_maxsp=pDoc->ch_maxsp+5+(pDoc->ch_level/5)+(pDoc->ch_dex)/15;
			pDoc->ch_skillpoint+=3;
			str.Format(_T("������ %d ���� ����Ͽ���. "),pDoc->ch_level);
			pDoc->ch_hp=pDoc->ch_maxhp;
			battle[3].Format(str);
		}
		battle[4]=_T("�ڡڡ� E N T E R�ڡڡ�");
		pDoc->battle_state=2;
	}
	if(pDoc->ch_hp<=0&&!(pDoc->battle_state==2)){ //�й�
		PlaySound(_T(".\\ahaha.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
		CString str;
		battle[0]=_T("�ڡڡ��������� �й��ߴ�.�ڡڡ�");
		bgm=0;
		str.Format(_T("   G A M E  O V E R "));
		pDoc->ch_money-=pDoc->mo_money;
		if(pDoc->ch_money<=0)pDoc->ch_money=0;
		battle[1].Format(str);
		battle[2]=_T("�ǽ��� �Ҿ���.");
		battle[3]=_T("�ڡڡڡڡڡڡڡڡڡڡڡ�");
		battle[4]=_T("�ڡڡ� E N T E R�ڡڡ�");
		pDoc->battle_state=3;
	}
	pDoc->card[number]=rand()%31/6;
	for(int i=0;i<3;i++)pDoc->card[i+6]=rand()%31/6;
	Invalidate();
	break;
case VK_SPACE:
case VK_RETURN:
	
if(pDoc->battle_state==2){//��������_�¸�
		pDoc->battle_state=0;
		for(int i=0;i<5;i++)battle[i]=CString(_T(""));
		pDoc->pstate=0;
		Invalidate();
	}
else if(pDoc->battle_state==3){//��������_�й�
		exit(0);
	}
	break;
 }
}
if(pDoc->pstate==4){ // ���� �޴�ȭ�� Ű���� �ν�
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
	if(shopmenu==0){// HP���� ����
		if(pDoc->ch_money>=150){
			pDoc->ch_money-=150; pDoc->hp_potion++;
			PlaySound(_T(".\\buy"), AfxGetInstanceHandle(),  SND_ASYNC);
		shop_text.Format(_T("hp������ �����߽��ϴ�"));
		}
		else{
		shop_text.Format(_T("���̺����մϴ�."));
		PlaySound(_T(".\\ahaha.wav"), AfxGetInstanceHandle(),  SND_ASYNC);}
	}
	if(shopmenu==1){// SP���� ����
		if(pDoc->ch_money>=150){
			pDoc->ch_money-=150; pDoc->mp_potion++;
			PlaySound(_T(".\\buy"), AfxGetInstanceHandle(),  SND_ASYNC);
		shop_text.Format(_T("sp������ �����߽��ϴ�"));
		}
		
		else {
			PlaySound(_T(".\\ahaha.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			shop_text.Format(_T("���̺����մϴ�."));}
	}
	if(shopmenu==2){// ��������� ����
		shop_text.Format(_T("��ǰ�� ������ �ּ���"));
	}
	if(shopmenu==3){pDoc->pstate=0;} // ���ư���
	Invalidate();
	break;
 }
}
if(pDoc->pstate==5){ // ����ȭ�� ������ ���� Ű���� �ν�
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
	if(select==0){// �������� �����ϼ���
		Invalidate(false);
	}
	if(select==1){// HP���� ���
		if(pDoc->hp_potion>0){
			PlaySound(_T(".\\potion.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			pDoc->hp_potion--; 
			pDoc->ch_hp+=150;
			if(pDoc->ch_hp>pDoc->ch_maxhp)pDoc->ch_hp=pDoc->ch_maxhp;
			
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			battle[4].Format(_T("hp������ ����߽��ϴ�"));
		pDoc->pstate=3;
		pDoc->battle_state=0;
	Invalidate(false);
	break;
		}
	}
	if(select==2){// SP���� ���
		if(pDoc->mp_potion>0){
			PlaySound(_T(".\\potion.wav"), AfxGetInstanceHandle(),  SND_ASYNC);
			pDoc->mp_potion--; 
			pDoc->ch_sp+=150;
			if(pDoc->ch_sp>pDoc->ch_maxsp)pDoc->ch_sp=pDoc->ch_maxsp;
			
			for(int i=0;i<4;i++)battle[i]=battle[i+1];
			battle[4].Format(_T("sp������ ����߽��ϴ�"));
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
	} // ���ư���
}
}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CRPGView::text_call(int index)
{
CRPGDoc* pDoc = GetDocument();
switch(index){ // ��ȭ ���� �����ͺ��̽�(?)
case 0:// NPC ���
         text_set(_T("���"),
	     _T("��� ������ �� ������?"),
	     _T("�� ���п� �� ������ ���Ҽ� �־���"),
	     _T("���� ������� ���ƿԱ���."),
		 _T("�׷��� �� ������ �ٽ� ã�ƿ� ������"),
		 _T("�巡���� ��¥ �����߸��� ���ؼ�?"));
       break;
case 1: 
         text_set(_T("���"),
	     _T("���� ���ο� ���� �ŵ쳵��"),
	     _T("���� �������� �����δ�"),
	     _T("�巡���� �Ҹ��Ű�� ������"),
		 _T("���� �̹����� ����"),
		 _T("���� �巡���� �����߸��Ŵ�..")); 
       break;
case 2: 
         text_set(_T("���"),
	     _T("������ �װ� ������"),
	     _T("����� �巡���� ����� �ʹ� ������.."),
	     _T("���� ���� ���� ����� ���ƿ�����"),
		 _T("�巡���� ���Ƿ��� ���� �ξ� ���ϴٱ�.."),
		 _T(""));
       break;
case 3: 
         text_set(_T("���"),
	     _T("���� ����.. ���� ���ϴϱ�"),
	     _T("�������� �巡���� �����߸��� ������"),
	     _T("�� �ٽ� ��� ������ �ɸ��� ���ž�.."),
		 _T(""),
		 _T("������ �� ���ƾߵ�!"));
       break;
case 4: 
         text_set(_T("���"),
	     _T("�׷�? �׷��ٸ� �Ҽ�����.."),
	     _T("�ϴ� �������� ���� �ΰ��� ���� �޶�"),
	     _T("�װ� �ٽ� �巡��� �ٰ�ʹٸ�"),
		 _T("���͸� �����鼭 �ϴ� ����Ű����.."),
		 _T("�ϴ� ���� �������̽��� ������ ����"));
       break;
case 5: 
         text_set(_T("System"),
	     _T(" [ ���� ]"),
	     _T("[1-6] : �ൿ ī�� ���"),
	     _T("  [7] : ������(���� ��) ���"),
		 _T("  [8] : ���� "),
		 _T("  [9] : �ൿ ī�� ����(�ϼҸ�)"));
       break;
case 6: 
         text_set(_T("���"),
	     _T("�׷� ����� ����.."),
	     _T("�巡���� �ﴩ���� ���� �������"),
	     _T("���� ���� ������ �ξ� ���ϴٱ�"),
		 _T("���� ������ �ʶ��"),
		 _T("����� ������ �����ž�.."));
       break;
case 10: // NPC ����
         text_set(_T("����"),
	     _T("�Ϳ�! �����!"),
	     _T("�� ������ ���ϼ̴� ����!"),
	     _T("������ �� �κ��̶�"),
		 _T("������ ����ص帱�� �����ϴ�"),
		 _T("������ �簡����"));
       break;
case 11: 
	
		 shopmenu=2; // ���� ����
		 pDoc->pstate=4;
		 Invalidate();

         text_set(_T("����"),
	     _T("���� ������ ������ �˾ƿ�?"),
	     _T("�翬�� '���' ������"),
	     _T("��ڴ��� ���� ���Ѻ�������"),
		 _T("�ƹ����� ������ ���Ѵ�ϴ�."),
		 _T(""));
       break;
case 12: 
         text_set(_T("����"),
	     _T("���Ͱ� �������� ���� ����?"),
	     _T("��� ������ ������ 1/2��"),
	     _T("�巡�￡�� �������� ��������"),
		 _T("������ ������ �׷��ʿ䰡 �����"),
		 _T(""));
       break;
case 20: // �巡�� (����) ���� ��ȭ
         text_set(_T("�巡��"),
	     _T("ũ����.. ũ����.."),
	     _T(""),
	     _T("?? �ƴ� �ʴ�!!"),
		 _T(""),
		 _T(""));
       break;
case 21: 
         text_set(_T("�巡��"),
	     _T("���� ������ Ǯ�����"),
	     _T("�� ���� ������ �༮�̱���!!"),
	     _T("ũ����!!!"),
		 _T(""),
		 _T(""));
       break;
case 22: 
         text_set(_T("���"),
	     _T("�� ������ �༮�̱�.."),
	     _T("�׳��� ���� ����־��� ���̾�!"),
	     _T("�̹����� ���� ����� �����ָ�!"),
		 _T(""),
		 _T(""));
       break;
case 23: 
         text_set(_T("�巡��"),
	     _T("������.. ���ҷӱ�"),
	     _T("�״�ÿ� ���̴�"),
	     _T("���� ������ü�� ������ �ɰ�"),
		 _T("�־��� ������ ���� ������"),
		 _T("�л�Ǿ��־���.."));
       break;
case 24: 
         text_set(_T("�巡��"),
	     _T("������ ������ �ٸ���.."),
	     _T("���� ��� ���� ���ƿ԰�"),
	     _T("�� ���� ����� �ʿ�����.."),
		 _T("�� �༮�� ���� ���ƿԴٸ�"),
		 _T("�ѳ� �ΰ��� ���ϻ�"));
       break;
case 25: 
         text_set(_T("���"),
	     _T("��!! ���� �׷���.."),
	     _T("�������� �����ε�"),
	     _T("�ʸ� �����߷ȴµ�.."),
		 _T("�׸��� �ｼ ����"),
		 _T("���� �ΰ����� �ٸ��ܰŴ�"));
       break;
case 26: 
         text_set(_T("���"),
	     _T("�ʷ� ���� �������� �ǰ�!"),
	     _T("�׷� ���� ���� ġ��!"),
	     _T("���� Ǯ���ָ�!"),
		 _T("���� ����!!"),
		 _T(""));
       break;
case 27: 
         text_set(_T("�巡��"),
	     _T("��.. 10�������� �־���.."),
	     _T("���� �����߸��� ����.."),
	     _T("��Ī [���] ��� ���ϴ� "),
		 _T("����� �༮��.."),
		 _T(""));
       break;
case 28: 
         text_set(_T("���"),
	     _T("�� �� [���]�ʹ� �ٸ���"),
	     _T("�ֳĸ�.."),
	     _T("��.."),
		 _T("�̰�����.."),
		 _T("��."));
       break;
case 29:     
         text_set(_T("���"),
	     _T("�� �� [���]�ʹ� �ٸ���"),
	     _T("�ֳĸ�.."),
	     _T("��.."),
		 _T("�̰�����.."),
		 _T("��.��"));
       break;
case 30: 
         text_set(_T("���"),
	     _T("�� �� [���]�ʹ� �ٸ���"),
	     _T("�ֳĸ�.."),
	     _T("��.."),
		 _T("�̰�����.."),
		 _T("��.��.��"));
       break;
case 31: 
       
         text_set(_T("���"),
	     _T("�� �� [���]�ʹ� �ٸ���"),
	     _T("�ֳĸ�.."),
	     _T("��.."),
		 _T("�̰�����.."),
		 _T("��.��.�� �̱� ��������.."));
       break;
case 32: 
         text_set(_T("�巡��"),
	     _T(".. ������ �����ʿ��.."),
	     _T("����.. ��ư �׳༮��"),
	     _T("�󸶳� �͹��� ���� ���翡"),
		 _T("���� �ϴ�����"),
		 _T("���� ���ݰ� ���ָ�.."));
       break;
case 33: 
         text_set(_T("�巡��"),
	     _T("�ѳ� �ΰ��� ������ �𸣸�"),
	     _T("��� ����� ������"),
	     _T("���� ����� ���ְڴ�.."),
		 _T(""),
		 _T(""));
       break;
case 34: 
	  boss=true; // �巡����� ������ ����
	  battleset();
	  Invalidate();
         text_set(_T("�巡��"),
	     _T("��.. ���ƾƾƾ�!!"),
	     _T("����.. ���� ��.."),
	     _T("�ΰ���������.."),
		 _T(""),
		 _T(""));
       break;
case 35: 
         text_set(_T("���"),
	     _T("��.. �׳༮�� �����߷�����"),
	     _T("���� �� ��������"),
	     _T("��ȭ�� ã�ƿ��ڱ�.."),
		 _T(""),
		 _T("�� ����.."));
       break;
case 36: 
         text_set(_T("�巡��"),
	     _T("����������������..."),
	     _T("���� �׷���.."),
	     _T("�ʴ� �巡�� ���迡��"),
		 _T("��õ���� �ִٴ°� �𸣴±���"),
		 _T("��������"));
       break;
case 37: 
         text_set(_T("�巡��"),
	     _T("����.. �� ��õ����"),
	     _T("���� ���� �� ���ϳ���."),
	     _T(""),
		 _T("���� ������ ������."),
		 _T(""));
       break;
case 38: 
         text_set(_T("���"),
	     _T("?? ����!! ��õ���̶��??"),
	     _T("�׷��� �赵 ���� ���߾�.."),
	     _T(""),
		 _T("�̷�����.."),
		 _T(""));
       break;
case 39: 
         text_set(_T("�巡��"),
	     _T(""),
	     _T("�Ƹ� ���� ������.."),
	     _T("���� ��õ�յ������"),
		 _T("�ʸ� ���̷� ������.."),
		 _T(""));
       break;
case 40: 
         text_set(_T("�巡��"),
	     _T("�׸���.."),
	     _T(" �����߿���.."),
	     _T("  �츮�� ����.."),
		 _T(""),
		 _T("��ڴ��� �����ô�."));
       break;
case 41: 
         text_set(_T("���"),
	     _T("��??"),
	     _T(""),
	     _T(""),
		 _T(""),
		 _T(""));
       break;
case 42: 
         text_set(_T("���"),
	     _T("��ڶ��?!!"),
	     _T("�װ� ���� ���̾�!!"),
	     _T(""),
		 _T(""),
		 _T(""));
       break;
case 43: 
         text_set(_T("�巡��"),
	     _T("��� �װ� ���ó��"),
	     _T("�༼�� �ϰ� ������"),
	     _T(""),
		 _T("���.. �״�.."),
		 _T(".. �����̴�."));
       break;
case 44: 
         text_set(_T("�巡��"),
	     _T("�ڼ��ϰ�.."),
	     _T(" �˰������"),
	     _T("�׿��Է� ������.."),
		 _T("����... ���ƾƾ�.."),
		 _T("   (�н�)"));	 
       break;
case 45: 
         text_set(_T(""),
	     _T(""),
	     _T(""),
	     _T(""),
		 _T(""),
		 _T(""));		 
		 potal(4,1,1); // �巡�￡���� ������ �����̵�
		 Invalidate();
		 pDoc->chating=0;
		 dia=0;
       break;
case 50:  // ���� ���丮
         text_set(_T("���"),
	     _T("�Ϳ�! �巡���� �����߸��ٴ�!!"),
	     _T("��� �ϳ׿�!!"),
	     _T("���� ��� �������� ����־��!!."),
		 _T(""),
		 _T(""));		 
       break;
case 51: 
         text_set(_T("���"),
	     _T("���ڽ�!! �ٸ���� ����!!"),
	     _T("�װ� ��������!!"),
	     _T(""),
		 _T("�� ���Դ�!!"),
		 _T(""));		 
       break;
case 52: 
         text_set(_T("���"),
	     _T("���.. �װ� ���� ���ΰ���?"),
	     _T("�巡���� ���� �̻��Ѹ��� �߳�?"),
	     _T("������ �巡���� �������� ���ؿ�.."),
		 _T("�׷� ���� �ȵǴ� ����"),
		 _T("������ �Ͼ���� ���ݾƿ�.."));		 
       break;
case 53: 
         text_set(_T("���"),
	     _T("�׷���.."),
	     _T("��� �����غ��� �����ȵǱ��߾�.."),
	     _T("�ǽ��ؼ� �̾���.."),
		 _T(" �� ��������"),
		 _T(" ��õ�հ� ������ �����߸��� ���ھ�!!"));		 
       break;
case 54:
         text_set(_T("���"),
	     _T("�׷�����!! ����"),
	     _T("�׷����� �̸����� ��ȭ��"),
	     _T("ã�� ���ŵ��!"),
		 _T("�׷� ���߿�����!!"),
		 _T("   ..(����)   - E N D -"));		 
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


	// ����Ʈ�� ������ ����
	pDoc->mo_name=_T("(Lv 2)���� ������"); // �������� ����
	pDoc->mo_hp=45;
	pDoc->mo_maxhp=45;
	pDoc->mo_exp=90;
	pDoc->mo_money=200;
	pDoc->mo_str=25;
	pDoc->mo_dex=15;
	pDoc->mo_xsize=91;
	pDoc->mo_ysize=65;
	pDoc->mo_num=0;

	if(pDoc->pmap==1){ // ������ ����
	pDoc->mo_name=_T("(Lv 5)���� �ͶѶ��");
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
	else if(pDoc->pmap==2){ // �������� ����
	pDoc->mo_name=_T("(Lv 8)���");
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

	if(boss&&pDoc->pmap==2){ // �巡��
	pDoc->mo_name=_T("(Lv 15)�巡��");
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
	else if(pDoc->pmap==4||pDoc->pmap==5){ // ���� ��Ʈ(Ż�� ��)
	pDoc->mo_name=_T("(Lv 20)���հ�Ʈ");
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnLButtonDown(nFlags, point);
}
