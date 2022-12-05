
// ODBC2View.h : CODBC2View Ŭ������ �������̽�
//

#pragma once

class CODBC2Set;

class CODBCSet2;//

class CODBC2View : public CRecordView
{
protected: // serialization������ ��������ϴ�.
	CODBC2View();
	DECLARE_DYNCREATE(CODBC2View)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_ODBC2_FORM };
#endif
	CODBC2Set* m_pSet;
	CODBCSet2* m_pSet2;
// Ư���Դϴ�.
public:
	CODBC2Doc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual CRecordset* OnGetRecordset();
	virtual CRecordset* OnGetRecordset2();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CODBC2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTestManonly();
	afx_msg void OnTestWomanonly();
	CListCtrl m_list;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CString m_Car;
	CString m_Name;
	BOOL m_elec;
	CString m_Phone;
	CTime m_Intime;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	void renew();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton4();
	CString m_Finded;
	CListCtrl m_list2;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnEnChangeEdit10();
	int m_icost;
	afx_msg void OnBnClickedButton8();
};

#ifndef _DEBUG  // ODBC2View.cpp�� ����� ����
inline CODBC2Doc* CODBC2View::GetDocument() const
   { return reinterpret_cast<CODBC2Doc*>(m_pDocument); }
#endif

