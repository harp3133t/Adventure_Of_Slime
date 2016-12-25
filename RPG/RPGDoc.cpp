
// RPGDoc.cpp : CRPGDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "RPG.h"
#endif

#include "RPGDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRPGDoc

IMPLEMENT_DYNCREATE(CRPGDoc, CDocument)

BEGIN_MESSAGE_MAP(CRPGDoc, CDocument)
END_MESSAGE_MAP()


// CRPGDoc 생성/소멸

CRPGDoc::CRPGDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	ch_skillpoint=0;
	battle_state=0;
	pmap=3;
	xPos=11;
	yPos=11;
	parrow=2;
	pstate=2;
	chating=0;
	srand((unsigned)time(NULL));
	for(int i=0;i<9;i++)card[i]=(rand()%5>1)?rand()%31/6:0;
	ch_hp=165;
	ch_maxhp=165;
	ch_sp=80;
	ch_maxsp=80;
	ch_exp=0;
	ch_maxexp=15;
	ch_str=35;
	ch_dex=35;
	ch_money=2500;
	hp_potion=5;
	mp_potion=5;
	ch_level=1;
	mo_name=_T("슬라임");
	mo_hp=30;
	mo_maxhp=30;
	mo_exp=50;
	mo_money=100;
	mo_str=20;
	mo_dex=10;
	mo_xsize=91;
	mo_ysize=65;
	mo_num=0;
}

CRPGDoc::~CRPGDoc()
{
}

BOOL CRPGDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CRPGDoc serialization

void CRPGDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CRPGDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CRPGDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CRPGDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CRPGDoc 진단

#ifdef _DEBUG
void CRPGDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRPGDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CRPGDoc 명령
