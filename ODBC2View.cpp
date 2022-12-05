
// ODBC2View.cpp : CODBC2View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ODBC2.h"
#endif

#include "ODBCSet2.h"
#include "ODBC2Set.h"
#include "ODBC2Doc.h"
#include "ODBC2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CODBC2View
CFont m_font;
//m_font.CreateFont(100, // nHeight
//	80, // nWidth
//	0, // nEscapement
//	0, // nOrientation
//	1, // nWeight
//	0, // bItalic
//	0, // bUnderline 
//	0, // cStrikeOut 
//	0, // nCharSet
//	OUT_DEFAULT_PRECIS, // nOutPrecision 
//	0,                              // nClipPrecision 
//	DEFAULT_QUALITY,       // nQuality
//	DEFAULT_PITCH | FF_DONTCARE,  // nPitchAndFamily 
//	"굴림"); // lpszFacename

IMPLEMENT_DYNCREATE(CODBC2View, CRecordView)

BEGIN_MESSAGE_MAP(CODBC2View, CRecordView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CRecordView::OnFilePrintPreview)
	ON_COMMAND(ID_TEST_MANONLY, &CODBC2View::OnTestManonly)
	ON_COMMAND(ID_TEST_WOMANONLY, &CODBC2View::OnTestWomanonly)//==========
	ON_BN_CLICKED(IDC_BUTTON1, &CODBC2View::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CODBC2View::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CODBC2View::OnBnClickedButton3)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CODBC2View::OnClickList1)// 이걸로 오른쪽 에디트 컨트롤에 리스트컨트롤1 에서 선택한거 띄워줌
	ON_BN_CLICKED(IDC_BUTTON5, &CODBC2View::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CODBC2View::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CODBC2View::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CODBC2View::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CODBC2View::OnBnClickedButton8)
END_MESSAGE_MAP()

// CODBC2View 생성/소멸

CODBC2View::CODBC2View()
	: CRecordView(IDD_ODBC2_FORM)
	, m_Car(_T(""))
	, m_Name(_T(""))
	, m_elec(TRUE)
	, m_Phone(_T(""))
	, m_Intime(0)
	, m_Finded(_T(""))
	, m_icost(0)

{
	m_pSet = NULL;
	m_pSet2 = NULL;
	// TODO: 여기에 생성 코드를 추가합니다.

}

CODBC2View::~CODBC2View()
{
}

void CODBC2View::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);


	//왼쪽 에디트 컨트롤 // 여기서 리스트 컨트롤1에서 선택한 레코드 표시해줌
	DDX_Text(pDX, IDC_EDIT1, m_pSet->m_ST_CAR);
	DDX_Text(pDX, IDC_EDIT2, m_pSet->m_ST_NAME);
	DDX_Text(pDX, IDC_EDIT3, m_pSet->m_ST_ELEC);
	DDX_Text(pDX, IDC_EDIT4, m_pSet->m_ST_PHONE);


	//왼쪽 리스트 컨트롤 테이블1을 불러옴
	DDX_Control(pDX, IDC_LIST1, m_list);

	//오른쪽 에디트 컨트롤// 여기서 정보 입력
	DDX_Text(pDX, IDC_EDIT5, m_Car);
	DDX_Text(pDX, IDC_EDIT6, m_Name);
	DDX_Text(pDX, IDC_EDIT7, m_elec);
	DDX_Text(pDX, IDC_EDIT8, m_Phone);
	DDX_Text(pDX, IDC_EDIT9, m_Finded);

	//오른쪽 리스트 컨트롤 테이블2를 불러옴
	DDX_Control(pDX, IDC_LIST2, m_list2);

	//총수입금액 표시
	DDX_Text(pDX, IDC_EDIT10, m_icost);
}

BOOL CODBC2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CRecordView::PreCreateWindow(cs);

}

void CODBC2View::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_ODBC2Set;
	m_pSet2 = &GetDocument()->m_ODBCSet2;
	CRecordView::OnInitialUpdate();
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES | LVS_EX_TRACKSELECT);
	//격자 표시 체크박스 표시 마우스로 아이템을 클릭하지 않아도 마우스를갖다 대면 자동으로 선택
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);

	m_list.InsertColumn(0, _T("차량번호"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(1, _T("이름"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(2, _T("전기차 유/무"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(3, _T("전화번호"), LVCFMT_LEFT, 100); 
	m_list.InsertColumn(4, _T("입차 시간"), LVCFMT_LEFT, 200);


	//
	m_list2.SetExtendedStyle(m_list2.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES | LVS_EX_TRACKSELECT);
	//격자 표시 체크박스 표시 마우스로 아이템을 클릭하지 않아도 마우스를갖다 대면 자동으로 선택
	m_list2.SetExtendedStyle(m_list2.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);

	m_list2.InsertColumn(0, _T("차량번호"), LVCFMT_LEFT, 100);
	m_list2.InsertColumn(1, _T("이름"), LVCFMT_LEFT, 70);
	m_list2.InsertColumn(2, _T("전화번호"), LVCFMT_LEFT, 100);
	m_list2.InsertColumn(3, _T("입차 시간"), LVCFMT_LEFT, 140);
	m_list2.InsertColumn(4, _T("퇴차 시간"), LVCFMT_LEFT, 140);
	m_list2.InsertColumn(5, _T("요금"), LVCFMT_LEFT, 100);

	m_font.CreateFont(20, // nHeight
		10, // nWidth
		0, // nEscapement
		0, // nOrientation
		3000, // nWeight
		0, // bItalic
		0, // bUnderline 
		0, // cStrikeOut 
		0, // nCharSet
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		0,                              // nClipPrecision 
		DEFAULT_QUALITY,       // nQuality
		DEFAULT_PITCH | FF_DONTCARE,  // nPitchAndFamily 
		_T("굴림")); // lpszFacename
	GetDlgItem(IDC_STATIC1)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC2)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC3)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC4)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC5)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC8)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC10)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC9)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC11)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC7)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC6)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC12)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC13)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC14)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT10)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT1)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT2)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT3)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT4)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT5)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT6)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT7)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT8)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT9)->SetFont(&m_font); 
	GetDlgItem(IDC_BUTTON2)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON3)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON4)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON5)->SetFont(&m_font);

}


// CODBC2View 인쇄

BOOL CODBC2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);

}

void CODBC2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CODBC2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CODBC2View 진단

#ifdef _DEBUG
void CODBC2View::AssertValid() const
{
	CRecordView::AssertValid();
}

void CODBC2View::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CODBC2Doc* CODBC2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CODBC2Doc)));
	return (CODBC2Doc*)m_pDocument;
}
#endif //_DEBUG


/** CODBC2View 데이터베이스 지원*/
CRecordset* CODBC2View::OnGetRecordset()
{
	return m_pSet;
}

CRecordset* CODBC2View::OnGetRecordset2()
{
	return m_pSet2;
}




// CODBC2View 메시지 처리기

//이건 무시하면 됨
void CODBC2View::OnTestManonly()
{
	m_pSet->m_strFilter = _T("ST_MAN = TRUE");
	m_pSet->Requery();
	UpdateData(FALSE);
}
void CODBC2View::OnTestWomanonly()
{
	m_pSet->m_strFilter = _T("ST_MAN = FALSE");
	m_pSet->Requery();
	UpdateData(FALSE);
}


//선택창과 입력창으로 나눈 이유
/*수정전에 어떤부분이 바뀌었는지 다시한번 확인하여 잘못 수정하는것을 방지하기 위해*/

/**주차 차량 수 세기*/
int count = 0;//(전역변수)

/**테이블1,2 데이터베이스 불러오기 (갱신) */
void CODBC2View::OnBnClickedButton1()//데이터베이스 불러 오기 

{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	renew();//테이블1 (함수형태)
	OnBnClickedButton6();//테이블2 (버튼형태)버튼 비활성화 해둠(실행하면 안보임) 
}

/**추가*/
void CODBC2View::OnBnClickedButton2()//데이터 추가
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CTime tmCur = CTime::GetCurrentTime();//시간 얻기
	if (count == 10) {
		AfxMessageBox(_T("주차공간 10자리가 모두 채워진 상태 입니다."));
		return;
	}
	UpdateData(TRUE);//컨트롤의 값을 변수로 전송
	m_pSet->AddNew();//추가
	m_pSet->m_ST_CAR = m_Car;
	m_pSet->m_ST_NAME = m_Name;
	m_pSet->m_ST_ELEC = m_elec;
	m_pSet->m_ST_PHONE = m_Phone;
	m_pSet->m_ST_INTIME = tmCur;
	m_pSet->Update();
	UpdateData(FALSE);//변수의 값을 컨트롤에 표시
	AfxMessageBox(_T("데이터가 추가되었습니다."));
	renew();// 테이블1, 리스트 컨트롤1 갱신
}

/**삭제*/
int cost;//요금 (전역변수)
CTime time1=0;//입차시간 (전역번수)
void CODBC2View::OnBnClickedButton3()//삭제
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	time1 = m_pSet->m_ST_INTIME;//입차시간
	CTime tmCur = CTime::GetCurrentTime();//시간 얻기
	CTimeSpan sTime = tmCur - m_pSet->m_ST_INTIME;//총 주차시간 얻기 (현재시간 - 입차시간) 
	
	CString csTime;
	csTime.Format(_T("%d일 %d시 %d분 %d초"), sTime.GetDays(), sTime.GetHours(), sTime.GetMinutes(),sTime.GetSeconds());
	
	int a=0;//요금 계산


	if (m_pSet->m_ST_ELEC == TRUE) {
		a = ((sTime.GetDays() * 86400) + (sTime.GetHours() * 3600) + (sTime.GetMinutes() * 60) + (sTime.GetSeconds() * 1))*0.7;
		AfxMessageBox(_T("전기차 입니다. 요금이 30% 할인 됩니다. "));
	}else
		a = (sTime.GetDays() * 86400)+(sTime.GetHours()*3600)+(sTime.GetMinutes()*60)+(sTime.GetSeconds()*1);
	
	CString at;
	at.Format(_T("%d"), a);//AfxMessageBox에 출력하기위해 CString형태로  바꾸기

	// cost = _ttoi(at);//요금CString형을 int 형으로 바꾸기
	cost = a;//320번줄이랑 같은의미 a는 int형이고 at는 CString형임 _ttoi를 쓰면 CString를 int로 바꿀 수 있음
	

	if (m_pSet->IsEOF())//레코드 위치가 마지막일 경우
	{
		m_pSet->Delete();//삭제
		m_pSet->MovePrev();//앞으로 한칸 이동
	}

	else if (m_pSet->IsBOF())//레코드 위치가 처음일 경우
	{
		
		m_pSet->Delete();//삭제
		m_pSet->MoveNext();//다음으로 한칸 이동
	}

	else//나머지 위치
	{
		m_pSet->Delete();//삭제
		m_pSet->MoveNext();//다음으로 한칸 이동
	}
	
	AfxMessageBox(_T("주차 시간은") + csTime +_T("입니다."));
	AfxMessageBox(_T("요금은") + at + _T("원 입니다."));

	m_pSet->Requery(); //레코드 집합을 다시 빌드(새로 고침) 삭제를 했기때문에 사용하는 메서드
	UpdateData(FALSE);//변수의 값을 컨트롤로 전송
	renew(); //테이블1, 리스트 컨트롤1 갱신
	OnBnClickedButton7();//테이블2에 삭제 데이터 저장
	OnBnClickedButton6();//테이블2 리스트 컨트롤2 갱신 
}

/**리스트 컨트롤에서 선택한 레코드 에디트컨트롤에 반영*/
void CODBC2View::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult)//리스트 컨트롤에서 선택한 값 에디트 컨트롤에 넣기
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	int clickindex = m_list.GetSelectionMark();//리스트 컨트롤에서 선택한 인덱스 저장
	
	
	m_pSet->MoveFirst();//처음으로 이동
	//리스트 컨트롤의 값을 입력 에디트 컨트롤(오른쪽)에 띄우기
	if (clickindex >= 0) {
		m_Car = m_list.GetItemText(clickindex, 0);//차
		m_Name = m_list.GetItemText(clickindex, 1);//이름
		CString b = m_list.GetItemText(clickindex, 2);//전기차 유/무
		if ("1" == b){///**(참/거짓)*/
			m_elec = TRUE;//전기차
		}
		else m_elec = FALSE;//전기차 아님
		m_Phone = m_list.GetItemText(clickindex, 3);//전화번호

		
		while(m_pSet->m_ST_CAR!=m_Car) {//선택한 값으로 m_pSet이 가르키게 하도록 움직이기
			m_pSet->MoveNext();
		}//커서 이동(레코드 이동)
		UpdateData(FALSE);
	} 
	else
		AfxMessageBox(_T("Please Select item"));

	renew();//테이블 1 갱신

	*pResult = 0;
}

/**검색*/
void CODBC2View::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_pSet->MoveFirst();
	
	while (m_pSet->m_ST_CAR != m_Finded) {//입력한 차번호가 같을때 멈춤
		m_pSet->MoveNext();
		if (m_pSet->IsEOF()) { 
			AfxMessageBox(_T("일치하는 차량이 없습니다.")); 
			m_pSet->MoveFirst(); 
			break; 
		}
	}//커서 이동 (레코드 이동)

	//검색한 값 선택창 에디트컨트롤에 (왼쪽) 넣어주기
	m_Car = m_pSet->m_ST_CAR;
	m_Name = m_pSet->m_ST_NAME;
	m_elec = m_pSet->m_ST_ELEC;
	m_Phone = m_pSet->m_ST_PHONE;
	UpdateData(FALSE);
}

/**수정*/
void CODBC2View::OnBnClickedButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_pSet->Edit();//선택한 레코드 수정 
	m_pSet->m_ST_CAR = m_Car;
	m_pSet->m_ST_NAME = m_Name;
	m_pSet->m_ST_ELEC = m_elec;
	m_pSet->m_ST_PHONE = m_Phone;
	m_pSet->Update();
	
	UpdateData(FALSE);
	renew();
	
}

/**테이블1 갱신*/
void CODBC2View::renew(){//데이터 베이스 리스트 컨트롤 갱신
	m_list.DeleteAllItems();//다시 불러오기 위해 리스트에 있는 내용 지우기
	CDatabase db;

	//데이터 베이스 객체 선언 및 연결
	db.OpenEx(_T("DSN=student"), 0);  

	//레코드셋 객체 생성, 데이터 소스에서 선택한 레코드 집합을 나타냅니다.
	CRecordset rs(&db);
	rs.Open(CRecordset::dynaset, _T("SELECT * FROM [테이블1]"));

	CString str;

	int i = 0;

	while (!rs.IsEOF())
	{

		rs.GetFieldValue(short(0), str);
		m_list.InsertItem(i, str);

		rs.GetFieldValue(short(1), str);
		m_list.SetItemText(i, 1, str);

		rs.GetFieldValue(short(2), str);
		m_list.SetItemText(i, 2, str);

		rs.GetFieldValue(short(3), str);
		m_list.SetItemText(i, 3, str);

		rs.GetFieldValue(short(4), str);
		m_list.SetItemText(i, 4, str);

		rs.MoveNext(); 

		i++;

	}
	count = i;
	rs.Close();
	db.Close();
}

/**테이블2 갱신*/
void CODBC2View::OnBnClickedButton6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_list2.DeleteAllItems();
	CDatabase db;

	db.OpenEx(_T("DSN=student"), 0);  

	CRecordset rs(&db);
	rs.Open(CRecordset::dynaset, _T("SELECT * FROM [테이블2]"));

	CString str;

	int i = 0;

	while (!rs.IsEOF())
		
	{

		rs.GetFieldValue(short(0), str);
		m_list2.InsertItem(i, str);

		rs.GetFieldValue(short(1), str);
		m_list2.SetItemText(i, 1, str);

		rs.GetFieldValue(short(2), str);
		m_list2.SetItemText(i, 2, str);

		rs.GetFieldValue(short(3), str);
		m_list2.SetItemText(i, 3, str);

		rs.GetFieldValue(short(4), str);
		m_list2.SetItemText(i, 4, str);

		rs.GetFieldValue(short(5), str);
		m_list2.SetItemText(i, 5, str);

		rs.MoveNext(); 

		i++;

	}

	rs.Close();
	db.Close();
	OnBnClickedButton8();
}

/**퇴차 테이블2에 저장*/
void CODBC2View::OnBnClickedButton7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pSet2->Open();//테이블2 열기
	CTime tmCur = CTime::GetCurrentTime();//시간 얻기
	

	UpdateData(TRUE);
	m_pSet2->MoveFirst();
	m_pSet2->AddNew();//데이터 추가
	
	m_pSet2->m_ST_DE_VEHICL = m_Car;//차번호
	m_pSet2->m_ST_DE_NAME = m_Name;//이름
	m_pSet2->m_ST_DE_PHONE = m_Phone;//전화번호
	m_pSet2->m_ST_DE_INTIME = time1;//입차시간
	m_pSet2->m_ST_DE_OUTTIME = tmCur;//출차시간
	m_pSet2->m_ST_DE_COST = cost;//요금
	
	m_pSet2->Update();
	UpdateData(FALSE);
	AfxMessageBox(_T("데이터가 추가되었습니다."));
	m_pSet2->Close();//테이블2 닫기
}


/**총 수입 금액*/
void CODBC2View::OnBnClickedButton8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_icost = 0;

	m_pSet2->Open();//테이블2를 열기
	UpdateData(TRUE);
	m_icost = 0;
	m_pSet2->MoveFirst();//테이블2의 처름 레코드로 이동
	while (!m_pSet2->IsEOF()) {//테이블2의 마지막까지
		m_icost = m_icost + m_pSet2->m_ST_DE_COST;//m_icost에 처음부터 마지막 요금까지 더하기
		m_pSet2->MoveNext();
	}
	UpdateData(FALSE);
	m_pSet2->Close();//테이블2 닫기
}

/*추가 할 기능
주차 공간 이미지 만들기
*/
/*ppt에 넣을 기능(우선순위)
	1.OnBnClickedButton2() 추가,
	2.OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 리스트 컨트롤에서 선택한 레코드 에디트컨트롤에 반영
	3.OnBnClickedButton3() 삭제
	4.OnBnClickedButton4() 검색
	5.OnBnClickedButton8() 총 수입 금액
	6.OnBnClickedButton7() 퇴차 테이블2에 저장(1번 추가랑 비슷한 내용)
	7.OnBnClickedButton1()=renew()+OnBnClickedButton6()// 딱히 중요하게 생각 안됨
*/