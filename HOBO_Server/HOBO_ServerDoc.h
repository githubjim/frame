// HOBO_ServerDoc.h : CHOBO_ServerDoc クラスのインターフェイス
//


#pragma once


class CHOBO_ServerDoc : public CDocument
{
protected: // シリアル化からのみ作成します。
	CHOBO_ServerDoc();
	DECLARE_DYNCREATE(CHOBO_ServerDoc)

// 属性
public:

// 操作
public:

// オーバーライド
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 実装
public:
	virtual ~CHOBO_ServerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
};


