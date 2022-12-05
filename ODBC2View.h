
// ODBC2View.h : CODBC2View 클래스의 인터페이스
//

#pragma once

class CODBC2Set;

class CODBCSet2;//

class CODBC2View : public CRecordView
{
protected: // serialization에서만 만들어집니다.
	CODBC2View();
	DECLARE_DYNCREATE(CODBC2View)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_ODBC2_FORM };
#endif
	CODBC2Set* m_pSet;
	CODBCSet2* m_pSet2;
// 특성입니다.
public:
	CODBC2Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual CRecordset* OnGetRecordset();
	virtual CRecordset* OnGetRecordset2();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CODBC2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // ODBC2View.cpp의 디버그 버전
inline CODBC2Doc* CODBC2View::GetDocument() const
   { return reinterpret_cast<CODBC2Doc*>(m_pDocument); }
#endif

