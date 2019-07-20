// DBToolDoc.h : CDBToolDoc クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTOOLDOC_H__8D99B843_2038_493C_BD36_BB08B6267A42__INCLUDED_)
#define AFX_DBTOOLDOC_H__8D99B843_2038_493C_BD36_BB08B6267A42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDBToolDoc : public CDocument{
protected: // シリアライズ機能のみから作成します。
	CDBToolDoc();
	DECLARE_DYNCREATE(CDBToolDoc)

// アトリビュート
public:

// オペレーション
public:

//オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDBToolDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CDBToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CDBToolDoc)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DBTOOLDOC_H__8D99B843_2038_493C_BD36_BB08B6267A42__INCLUDED_)
