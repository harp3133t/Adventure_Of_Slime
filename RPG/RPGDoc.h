
// RPGDoc.h : CRPGDoc 클래스의 인터페이스
//


#pragma once


class CRPGDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CRPGDoc();
	DECLARE_DYNCREATE(CRPGDoc)

// 특성입니다.
public:
	int ch_skillpoint; // 스킬포인트
	CString mo_name;// 몬스터이름
	int battle_state;// 전투상황
	int pmap;// 현재맵
	int xPos;// 현재x좌표
	int yPos;// 현재y좌표
	int parrow;// 캐릭터가 보고있는 방향
	int pstate;// 화면 출력 상태
	int chating;// 대화 변수
	int card[9];// 카드 1~6플레이어카드 7~9몬스터카드
	int ch_level;// 레벨
	int ch_hp;// 캐릭터HP
	int ch_sp;// 캐릭터SP
	int ch_maxhp;// 캐릭터 최대 HP
	int ch_maxsp;// 캐릭터 최대 SP
	int ch_exp;// 캐릭터 현재EXP
	int ch_maxexp;// 캐릭터 필요EXP
	int ch_str;// 캐릭터 STR
	int ch_dex;// 캐릭터 DEX
	int ch_money;// 소지금
	int hp_potion;// HP포션 소지수
	int mp_potion;// SP(MP)포션 소지수
	int mo_num;// 몬스터 종류
	int mo_hp;//  몬스터 hp
	int mo_maxhp;//  몬스터 최대 hp
	int mo_exp;// 승리시 얻는 exp
	int mo_money;// 승리시 얻는 골드
	int mo_str;// 몬스터 STR
	int mo_dex;// 몬스터 DEX
	int mo_xsize;// 몬스터 파일 x사이즈
	int mo_ysize;// 몬스터 파일 y사이즈
// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CRPGDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
