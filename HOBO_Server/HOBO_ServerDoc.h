// HOBO_ServerDoc.h : CHOBO_ServerDoc �N���X�̃C���^�[�t�F�C�X
//


#pragma once


class CHOBO_ServerDoc : public CDocument
{
protected: // �V���A��������̂ݍ쐬���܂��B
	CHOBO_ServerDoc();
	DECLARE_DYNCREATE(CHOBO_ServerDoc)

// ����
public:

// ����
public:

// �I�[�o�[���C�h
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ����
public:
	virtual ~CHOBO_ServerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	DECLARE_MESSAGE_MAP()
};


