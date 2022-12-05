#pragma once
class CODBCSet2 : public CRecordset
{
public:
	CODBCSet2(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CODBCSet2)

	// �ʵ�/�Ű� ���� ������

	// �Ʒ��� ���ڿ� ����(���� ���)�� �����ͺ��̽� �ʵ��� ���� ������ ������
	// ��Ÿ���ϴ�(CStringA: ANSI ������ ����, CStringW: �����ڵ� ������ ����).
	// �̰��� ODBC ����̹����� ���ʿ��� ��ȯ�� ������ �� ������ �մϴ�.  // ���� ��� �̵� ����� CString �������� ��ȯ�� �� ������
	// �׷� ��� ODBC ����̹����� ��� �ʿ��� ��ȯ�� �����մϴ�.
	// (����: �����ڵ�� �̵� ��ȯ�� ��� �����Ϸ���  ODBC ����̹�
	// ���� 3.5 �̻��� ����ؾ� �մϴ�).

	CStringW	m_ST_DE_VEHICL;
	CStringW	m_ST_DE_NAME;
	CStringW	m_ST_DE_PHONE;
	CTime	m_ST_DE_INTIME;
	CTime	m_ST_DE_OUTTIME;
	INT		m_ST_DE_COST;


	// ������
		// �����翡�� ������ ���� �Լ� ������
public:
	virtual CString GetDefaultConnect();	// �⺻ ���� ���ڿ�

	virtual CString GetDefaultSQL(); 	// ���ڵ� ������ �⺻ SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX ����

// ����
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

