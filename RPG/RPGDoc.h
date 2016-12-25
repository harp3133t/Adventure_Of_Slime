
// RPGDoc.h : CRPGDoc Ŭ������ �������̽�
//


#pragma once


class CRPGDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CRPGDoc();
	DECLARE_DYNCREATE(CRPGDoc)

// Ư���Դϴ�.
public:
	int ch_skillpoint; // ��ų����Ʈ
	CString mo_name;// �����̸�
	int battle_state;// ������Ȳ
	int pmap;// �����
	int xPos;// ����x��ǥ
	int yPos;// ����y��ǥ
	int parrow;// ĳ���Ͱ� �����ִ� ����
	int pstate;// ȭ�� ��� ����
	int chating;// ��ȭ ����
	int card[9];// ī�� 1~6�÷��̾�ī�� 7~9����ī��
	int ch_level;// ����
	int ch_hp;// ĳ����HP
	int ch_sp;// ĳ����SP
	int ch_maxhp;// ĳ���� �ִ� HP
	int ch_maxsp;// ĳ���� �ִ� SP
	int ch_exp;// ĳ���� ����EXP
	int ch_maxexp;// ĳ���� �ʿ�EXP
	int ch_str;// ĳ���� STR
	int ch_dex;// ĳ���� DEX
	int ch_money;// ������
	int hp_potion;// HP���� ������
	int mp_potion;// SP(MP)���� ������
	int mo_num;// ���� ����
	int mo_hp;//  ���� hp
	int mo_maxhp;//  ���� �ִ� hp
	int mo_exp;// �¸��� ��� exp
	int mo_money;// �¸��� ��� ���
	int mo_str;// ���� STR
	int mo_dex;// ���� DEX
	int mo_xsize;// ���� ���� x������
	int mo_ysize;// ���� ���� y������
// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CRPGDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
