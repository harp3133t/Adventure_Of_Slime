
// RPGDoc.cpp : CRPGDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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


// CRPGDoc ����/�Ҹ�

CRPGDoc::CRPGDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
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
	mo_name=_T("������");
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

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CRPGDoc serialization

void CRPGDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CRPGDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
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

// �˻� ó���⸦ �����մϴ�.
void CRPGDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CRPGDoc ����

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


// CRPGDoc ���
