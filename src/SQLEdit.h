#if !defined(AFX_SQLEDIT_H__BA012C00_5E40_492F_999A_87EEB7D778FB__INCLUDED_)
#define AFX_SQLEDIT_H__BA012C00_5E40_492F_999A_87EEB7D778FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SQLEdit.h : ヘッダー ファイル
//
#define USE_RICHEDIT	0
#if USE_RICHEDIT
#include "RichEditCtrlEx.h"
#else
#include "EditEx.h"
#endif
#include "AoutCmpWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CSQLEdit ウィンドウ
/*
static const CString strReserve[]{
	"SELECT", 
	"DISTINCT", 
	"FROM", 
	"WHERE", 
	"GROUP", 
	"ORDER", 
	"BY",
	"UNION", 
	"INSERT", 
	"INTO", 
	"AS", 
	"LEFT", 
	"RIGHT",
	"JOIN", 
	"DELETE", 
	"TRANCATE", 
	"CREATE", 
	"DATABASE", 
	"TABLE",
	"ALTER",
	"DROP",
	"UPDATE",
	"VALUES",
};
*/

#if AOUT_CMP
typedef struct tagSQLKey{
	LPCTSTR pszPrimary;
	LPCTSTR pszSubKey;
	BOOL bLeft;
}SQLKey, *PSQLKey;

#define SQLSERVER_ONLY	1
#define ORACLE_ONLY		0
#define OTHER_ONLY		0

static PICKDATA arrPickData_ore[] ={
	{"SET TRANSACTION READ ONLY ",				"SET TRANSACTION READ ONLY"},
	{"SET TRANSACTION READ WRITE ",				"SET TRANSACTION READ WRITE"},
	{"COMMIT",									"COMMIT"},
	{"COMMIT WORK",								"COMMIT WORK"},
	{"ROLLBACK",								"ROLLBACK"},
	{"ROLLBACK WORK",							"ROLLBACK WORK"},
	{"ALTER TABLE ADD",							"ALTER TABLE <table> ADD <column>"										},
	{"ALTER TABLE ADD CONSTRAINT",				"ALTER TABLE <table> ADD CONSTRAINT <column>"							},
	{"ALTER TABLE DROP ()",						"ALTER TABLE <table> DROP( <column> )"									},
	{"ALTER TABLE MODIFY",						"ALTER TABLE <table> MODIFY <column>"									},
	{"CREATE TABLE ",							"CREATE TABLE <table>"													},
	{"DROP TABLE ",								"DROP TABLE <table>"									},
	{"TRUNCATE TABLE ",							"TRUNCATE TABLE <table>"								},

	{"CREATE FUNCTION RETURN IS ",				"CREATE FUNCTION <name> RETURN <type> IS <statement>"					},
	{"CREATE FUNCTION RETURN AS ",				"CREATE FUNCTION <name> RETURN <type> AS <statement>"					},
	{"CREATE OR REPLACE FUNCTION RETURN IS",	"CREATE OR REPLACE FUNCTION <name> RETURN <type> IS <statement> "		},
	{"CREATE OR REPLACE FUNCTION RETURN AS",	"CREATE OR REPLACE FUNCTION <name> RETURN <type> AS <statement> "		},
	{"DROP FUNCTION ",							"DROP FUNCTION <name>"									},
	{"CREATE INDEX ",							"CREATE INDEX <index>"													},
	{"CREATE UNIQUE INDEX ",					"CREATE UNIQUE INDEX <index>"							},
	{"DROP INDEX ",								"DROP INDEX <index>"									},

	{"CREATE PROCEDURE AS",						"CREATE PROCEDURE <name> AS <statement>"								},
	{"CREATE OR REPLACE PROCEDURE IS",			"CREATE OR REPLACE PROCEDURE IS <name> <statement>"						},
	{"DROP PROCEDURE ",							"DROP PROCEDURE <name>"									},

	{"CREATE TRIGGER ON ",						"CREATE TRIGGER <name> ON <table>"										},
	{"DROP TRIGGER ",							"DROP TRIGGER <name>"									},
	{"CREATE OR REPLACE VIEW AS",				"CREATE OR REPLACE VIEW <view> AS"										},
	{"CREATE VIEW AS",							"CREATE VIEW <view> AS"									},
	{"DROP VIEW ",								"DROP VIEW <VIEW>"										},

	{"CREATE SEQUENCE ",						"CREATE SEQUENCE <name option>"							},
	{"DROP SEQUENCE ",							"DROP SEQUENCE <name>"									},

	{"CREATE USER IDENTIFIRD BY ",				"CREATE USER <name> IDENTIFIRD BY <pass>"							},
	{"DROP USER CASCADE ",						"DROP USER <name> CASCADE"									},
	{"DROP USER ",								"DROP USER <name>"									},

	{"CREATE SYNONYM FOR ",						"CREATE SYNONYM <name> FOR <name>"						},
	{"DROP SYNONYM ",							"DROP SYNONYM <name>"									},

	{"CREATE DATABASE LINK  CONNECT TO  IDENTIFIELD BY  USING",	"CREATE DATABASE LINK <db_name> CONNECT TO <user> IDENTIFILED BY <pass> USING <\'connect_string\'>"							},
	{"DROP DATABASE LINK ",						"DROP DATABASE LINK <db_name>"},

	{"DELETE ",									"DELETE <table>"										},

	{"INNER JOIN ON ",							"INNER JOIN <table> ON <condition(s)>"					},
	{"INSERT VALUES()",							"INSERT <table> VALUES <value(s)>"						},
	{"INSERT INTO VALUES()",					"INSERT INTO <table> VALUES <value(s)>"					},
	
	{"UPDATE SET ",								"UPDATE <table> SET <column=value,...>"					},

	{"JOIN ON ",								"JOIN <table> ON <condition(s)>"						},
	{"LEFT JOIN ON ",							"LEFT JOIN <table> ON <condition(s)>"					},
	{"RIGHT JOIN ON ",							"RIGHT JOIN <table> ON <condition(s)>"					},

	{"GROUP BY ",								"GROUP BY <column(s)>"									},
	{"ORDER BY ",								"ORDER BY <column(s)>"									},
	{"ORDER BY ASC ",							"ORDER BY <column(s)> ASC"								},
	{"ORDER BY DESC ",							"ORDER BY <column(s)> DESC"								},

	{"SELECT ",									"SELECT <colum(s)>"										},
	{"SELECT * ",								"SELECT *"												},
	{"SELECT DISTINCT ",						"SELECT DISTINCT <colum(s)>"							},
	{"SELECT DISTINCT *",						"SELECT DISTINCT *"										},
	{"FROM ",									"FROM <table_name(s)>"									},
	{"UNION ",									"UNION <sql syntax>"									},
	{"WHERE ",									"WHERE <condition(s)>"									},
	{"EXISTS ",									"EXISTS <sql syntax>"									},

	{"GRANT ALL  TO ",							"GRANT ALL TO <user>"									},
	{"GRANT ALL  TO   WITH GRANT OPTION",		"GRANT ALL TO <user> WITH GRANT OPTION"					},
	{"GRANT  TO ",								"GRANT <privilage> TO <user>"							},
	{"GRANT  TO   WITH GRANT OPTION",			"GRANT <privilage> TO <user> WITH GRANT OPTION"			},

	{"REVOKE  FROM ",							"REVOKE <privilage> FROM <user>"						},
	{"REVOKE ON  FROM ",						"REVOKE <privilage> ON <object> FROM <user>"			},

	{"RENAME  TO ",								"RENAME <original> TO <changed>"						},

	{"ALL ()",									" 式 比較演算子 ALL (サブクエリー)"},
	{"AND ",									" 式 AND 式"},
	{"ANY ()",									" 式 比較演算子 ANY (サブクエリー)"},
	{"BETWEEN AND ",							" 式 BETWEEN 式 AND 式"},
	{"EXISTS ()",								"EXISTS (サブクエリー)"},

	{"IN ()",									"式 IN (式,...)"},
	{"LIKE ",									"式 LIKE 文字列式"},
	{"NOT ",									"NOT 式"},
	{"OR ",										"式 OR 式"},
	{"SOME ()",									"比較演算子 SOME (サブクエリー)"},

	{"IS NULL",									"式 IS NULL"},

	{"AVG( )",									"AVG(n)"},
	{"AVG(DISTINCT )",							"AVG(DISTINCT n)"},
	{"AVG(ALL )",								"AVG(ALL n)"},

	{"COUNT( )",								"COUNT(n)"},
	{"COUNT(DISTINCT )",						"COUNT(DISTINCT n)"},
	{"COUNT(ALL )",								"COUNT(ALL n)"},
	{"GROUPING( )",								"GROUPING(column_name)"},

	{"STDDEV( )",								"STDDEV(n)"},

	{"SUM( )",									"SUM(n)"},
	{"SUM(DISTINCT )",							"SUM(DISTINCT n)"},
	{"SUM(ALL )",								"SUM(ALL n)"},
	{"VARIANCE( )",								"VARIANCE(n)"},

	{"ASCII( )",								"ASCII(c)"},
	{"CHR( )",									"CHR(n)"},
	{"CONCAT( )",								"CONCAT(s,t)"},
	{"INSTR( )",								"INSTR(s,t[,n[,m]])"},
	{"LENGTH( )",								"LENGTH(s)"},
	{"LOWER( )",								"LOWER(s)"},
	{"LPAD( )",									"LPAD(s,l,t)"},
	{"LTRIM( )",								"LTRIM(s)"},
	{"REPLACE( )",								"REPLACE(s,t,n)"},
	{"RPAD( )",									"RPAD(s,l,t)"},
	{"RTRIM( )",								"RTRIM(s)"},
	{"SUBSTR( )",								"SUBSTR(s,n,m)"},
	{"TRIM( )",									"TRIM(s)"},
	{"TRIM(LEADING )",							"TRIM(LEADING s)"},
	{"TRIM(TRAILING )",							"TRIM(TRAILING s)"},
	{"TRIM(BOTH )",								"TRIM(BOTH s)"},
	{"TRIM( FROM )",							"TRIM(c FROM s)"},
	{"TRIM(LEADING FROM )",						"TRIM(LEADING c FROM s)"},
	{"TRIM(TRAILING FROM )",					"TRIM(TRAILING c FROM s)"},
	{"TRIM(BOTH FROM )",						"TRIM(BOTH c FROM s)"},
	{"UPPER( )",								"UPPER(s)"},
	
	{"ADD_MONTHS( )",							"ADD_MONTHS(d,n)"},
	{"MONTHS_BETWEEN( )",						"MONTHS_BETWEEN(d,e)"},
	{"SYSDATE",									"SYSDATE"},

	{"CAST( AS )",								"CAST(e AS t)"},
	{"DECODE( )",								"DECODE(式[,式])"},
	{"NVL( )",									"NVL(n,e)"},
	{"TO_CHAR( )",								"TO_CHAR(e[,f])"},
	{"TO_DATE( )",								"TO_DATE(e[,f])"},
	{"TO_NUMBER( )",							"TO_NUMBER(e)"},

	{"ABS( )",									"ABS(n)"},
	{"ACOS( )",									"ACOS(n)"},
	{"ASIN( )",									"ASIN(n)"},
	{"ATAN( )",									"ATAN(n)"},
	{"CEIL( )",									"CEIL(n)"},
	{"COS( )",									"COS(n)"},
	{"EXP( )",									"EXP(n)"},
	{"FLOOR( )",								"FLOOR(n)"},
	{"LOG( )",									"LOG(e,n)"},
	{"MOD( )",									"MOD(n,m)"},
	{"POWER( )",								"POWER(n,m)"},
	{"ROUND( )",								"ROUND(n[,m])"},
	{"ROUND( )",								"ROUND(d[,f])"},
	{"SIGN( )",									"SIGN(n)"},
	{"SIN( )",									"SIN(n)"},
	{"SQRT( )",									"SQRT(n)"},
	{"TAN( )",									"TAN(n)"},
	{"TRUNC( )",								"TRUNC(n[,m])"},
	{"TRUNC( )",								"TRUNC(d[,f])"},
};

static PICKDATA arrPickData_sql[] ={
	{"BEGIN TRAN",								"BEGIN TRAN "},
	{"BEGIN TRAN SECTION",						"BEGIN TRAN SECTION "},
	{"COMMIT TRAN",								"COMMIT TRAN"},
	{"COMMIT TRAN ",							"COMMIT TRAN SECTION "},
	{"ROLLBACK TRAN",							"ROLLBACK TRAN"},
	{"ROLLBACK TRAN ",							"ROLLBACK TRAN SECTION "},
	{"ALTER TABLE ADD",							"ALTER TABLE <table> ADD <column>"										},
	{"ALTER TABLE ADD CONSTRAINT",				"ALTER TABLE <table> ADD CONSTRAINT <column>"							},
	{"ALTER TABLE DROP CONSTRAINT",				"ALTER TABLE <table> DROP CONSTRAINT <column>"							},
	{"ALTER TABLE DROP COLUMN",					"ALTER TABLE <table> DROP COLUMN <column>"								},
	{"CREATE TABLE ",							"CREATE TABLE <table>"													},
	{"DROP TABLE ",								"DROP TABLE <table>"									},
	{"TRUNCATE TABLE ",							"TRUNCATE TABLE <table>"								},


	{"CREATE INDEX ",							"CREATE INDEX <index>"													},
	{"CREATE UNIQUE INDEX ",					"CREATE UNIQUE INDEX <index>"							},
	{"DROP INDEX ",								"DROP INDEX <table.index>"									},

	{"CREATE PROCEDURE AS",						"CREATE PROCEDURE <name> AS <statement>"								},
	{"CREATE PROCEDURE WITH AS",				"CREATE PROCEDURE <name> WITH <option> AS <statement>"					},
	{"DROP PROCEDURE ",							"DROP PROCEDURE <name>"									},

	{"CREATE TRIGGER ON FOR AS ",				"CREATE TRIGGER <name> ON <table> FOR <event> AS <statement>"			},
	{"DROP TRIGGER ",							"DROP TRIGGER <name>"									},
	
	{"CREATE VIEW AS",							"CREATE VIEW <view> AS"									},
	{"DROP VIEW ",								"DROP VIEW <VIEW>"										},

	{"DELETE ",									"DELETE <table>"										},

	{"INNER JOIN ON ",							"INNER JOIN <table> ON <condition(s)>"					},
	{"INSERT VALUES()",							"INSERT <table> VALUES <value(s)>"						},
	{"INSERT INTO VALUES()",					"INSERT INTO <table> VALUES <value(s)>"					},
	
	{"UPDATE SET ",								"UPDATE <table> SET <column=value,...>"					},

	{"JOIN ON ",								"JOIN <table> ON <condition(s)>"						},
	{"LEFT JOIN ON ",							"LEFT JOIN <table> ON <condition(s)>"					},
	{"RIGHT JOIN ON ",							"RIGHT JOIN <table> ON <condition(s)>"					},

	{"GROUP BY ",								"GROUP BY <column(s)>"									},
	{"ORDER BY ",								"ORDER BY <column(s)>"									},
	{"ORDER BY ASC ",							"ORDER BY <column(s)> ASC"								},
	{"ORDER BY DESC ",							"ORDER BY <column(s)> DESC"								},

	{"SELECT ",									"SELECT <colum(s)>"										},
	{"SELECT * ",								"SELECT *"												},
	{"SELECT DISTINCT ",						"SELECT DISTINCT <colum(s)>"							},
	{"SELECT DISTINCT *",						"SELECT DISTINCT *"										},
	{"FROM ",									"FROM <table_name(s)>"									},
	{"UNION ",									"UNION <sql syntax>"									},
	{"WHERE ",									"WHERE <condition(s)>"									},
	{"EXISTS ",									"EXISTS <sql syntax>"									},

	{"sp_addlogin ",							"sp_addlogin <loginname,...>"									},
	{"sp_droplogin ",							"sp_droplogin <loginname>"									},

	{"sp_grantdbaccess ",						"sp_grantdbaccess <loginname>"							},
	{"sp_revokedbaccess ",						"sp_revokedbaccess <loginname>"							},

	{"GRANT ALL  TO ",							"GRANT ALL TO <user>"									},
	{"GRANT ALL  TO   WITH GRANT OPTION",		"GRANT ALL TO <user> WITH GRANT OPTION"					},
	{"GRANT  TO ",								"GRANT <privilage> TO <user>"							},
	{"GRANT  TO   WITH GRANT OPTION",			"GRANT <privilage> TO <user> WITH GRANT OPTION"			},

	{"REVOKE  FROM ",							"REVOKE <privilage> FROM <user>"						},
	{"REVOKE ON  FROM ",						"REVOKE <privilage> ON <object> FROM <user>"			},

	{"sp_rename ",								"sp_rename <original,changed>"							},

	{"ALL ()",									" 式 比較演算子 ALL (サブクエリー)"},
	{"AND ",									" 式 AND 式"},
	{"ANY ()",									" 式 比較演算子 ANY (サブクエリー)"},
	{"BETWEEN AND ",							" 式 BETWEEN 式 AND 式"},
	{"EXISTS ()",								"EXISTS (サブクエリー)"},

	{"IN ()",									"式 IN (式,...)"},
	{"LIKE ",									"式 LIKE 文字列式"},
	{"NOT ",									"NOT 式"},
	{"OR ",										"式 OR 式"},
	{"SOME ()",									"比較演算子 SOME (サブクエリー)"},

	{"IS NULL",									"式 IS NULL"},
	{"CASE WHEN THEN END",						"CASE 式 WHEN 式 THEN 式 ... END"},
	{"CASE WHEN THEN END",						"CASE WHEN 式 THEN 式 ... END"},
	{"CASE WHEN THEN ELSE END",					"CASE 式 WHEN 式 THEN 式 ...ELSE 式 END"},
	{"CASE WHEN THEN ELSE END",					"CASE WHEN 式 THEN 式 ... ELSE 式 END"},

	{"AVG( )",									"AVG(n)"},
	{"AVG(DISTINCT )",							"AVG(DISTINCT n)"},
	{"AVG(ALL )",								"AVG(ALL n)"},

	{"COUNT( )",								"COUNT(n)"},
	{"COUNT(DISTINCT )",						"COUNT(DISTINCT n)"},
	{"COUNT(ALL )",								"COUNT(ALL n)"},
	{"GROUPING( )",								"GROUPING(column_name)"},
	{"MAX( )",									"MAX(式)"},
	{"MIN( )",									"MIN(式)"},

	{"STDEV( )",								"STDEV(n)"},
	{"STDEVP( )",								"STDEVP(n)"},

	{"SUM( )",									"SUM(n)"},
	{"SUM(DISTINCT )",							"SUM(DISTINCT n)"},
	{"SUM(ALL )",								"SUM(ALL n)"},
	{"VAR( )",									"VAR(n)"},
	{"VARP( )",									"VARP(n)"},

	{"ASCII( )",								"ASCII(c)"},
	{"CHAR( )",									"CHAR(n)"},
	{"CHARINDEX( )",							"CHARINDEX(s,t[n])"},
	{"LEFT( )",									"LEFT(s, n)"},
	{"LEN( )",									"LEN(s)"},
	{"LTRIM( )",								"LTRIM(s)"},
	{"NCHAR( )",								"NCHAR(n)"},
	{"REPLACE( )",								"REPLACE(s,t,n)"},
	{"REPLICATE( )",							"REPLICATE(s,n)"},
	{"REVERSE( )",								"REVERSE(s)"},
	{"RIGHT( )",								"RIGHT(s,n)"},
	{"RTRIM( )",								"RTRIM(s)"},
	{"SPACE( )",								"SPACE(s)"},
	{"STR( )",									"STR(n[,l[,d]])"},
	{"STUFF( )",								"STUFF(s,f,l,t)"},
	{"SUBSTRING( )",							"SUBSTRING(s,n,m)"},
	{"UNICODE( )",								"UNICODE(c)"},
	{"UPPER( )",								"UPPER(s)"},
	{"DATEADD( )",								"DATEADD(p,n,d)"},
	{"DATEDIFF( )",								"DATEDIFF(p,d,e)"},
	{"DATENAME( )",								"DATENAME(p,d)"},
	{"DATEPART( )",								"DATEPART(p,d)"},
	{"DAY( )",									"DAY(d)"},
	{"GETDATE()",								"GETDATE()"},
	{"MONTH( )",								"MONTH(d)"},
	{"YEAR( )",									"YEAR(d)"},

	{"CAST( AS )",								"CAST(e AS t)"},
	{"CONVERT( )",								"CONVERT(t,e[,s])"},
	{"ISNULL( )",								"ISNULL(n,e)"},

	{"ABS( )",									"ABS(n)"},
	{"ACOS( )",									"ACOS(n)"},
	{"ASIN( )",									"ASIN(n)"},
	{"ATAN( )",									"ATAN(n)"},
	{"CELING( )",								"CELING(n)"},
	{"COS( )",									"COS(n)"},
	{"COT( )",									"COT(n)"},
	{"DEGRESS( )",								"DEGRESS(n)"},
	{"EXP( )",									"EXP(n)"},
	{"FLOOR( )",								"FLOOR(n)"},
	{"LOG( )",									"LOG(n)"},
	{"LOG10( )",								"LOG10(n)"},
	{"PO()",									"PI()"},
	{"POWER( )",								"POWER(n,m)"},
	{"RADIANS( )",								"RADIANS(n)"},
	{"RAND()",									"RAND()"},
	{"RAND( )",									"RAND(s)"},
	{"ROUND( )",								"ROUND(n,m[,t])"},
	{"SIGN( )",									"SIGN(n)"},
	{"SIN( )",									"SIN(n)"},
	{"SQUARE( )",								"SQUARE(n)"},
	{"SQRT( )",									"SQRT(n)"},
	{"TAN( )",									"TAN(n)"},
} ;
#endif

#if USE_RICHEDIT
class CSQLEdit : public CRichEditCtrlEx{
#else
class CSQLEdit : public CEditEx{
#endif
	
// コンストラクション
public:
	CSQLEdit();

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSQLEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	BOOL ShowAoutCompWnd();
	BOOL m_bRunSQL;
	LPCTSTR GetFileName();
	BOOL SaveSQL(BOOL bSaveAs);
	BOOL OpenSQL(LPCTSTR pszFileName);
	virtual ~CSQLEdit();
	void OnUpdateEditCopy(CCmdUI* pCmdUI);
	void OnUpdateEditCut(CCmdUI* pCmdUI);
	void OnUpdateEditPaste(CCmdUI* pCmdUI);
	void OnUpdateEditUndo(CCmdUI* pCmdUI);

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CSQLEdit)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSqlrun();
	afx_msg void OnSqlfairing();
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnEditUndo();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnAllselect();
	afx_msg void OnUpdateAllselect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSqlrun(CCmdUI* pCmdUI);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	CString m_strFileName;
	HACCEL m_acl;
#if AOUT_CMP
	CAoutCmpWnd m_objAutCmpWnd;
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SQLEDIT_H__BA012C00_5E40_492F_999A_87EEB7D778FB__INCLUDED_)
