
// ODBC2View.cpp : CODBC2View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
//	"����"); // lpszFacename

IMPLEMENT_DYNCREATE(CODBC2View, CRecordView)

BEGIN_MESSAGE_MAP(CODBC2View, CRecordView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CRecordView::OnFilePrintPreview)
	ON_COMMAND(ID_TEST_MANONLY, &CODBC2View::OnTestManonly)
	ON_COMMAND(ID_TEST_WOMANONLY, &CODBC2View::OnTestWomanonly)//==========
	ON_BN_CLICKED(IDC_BUTTON1, &CODBC2View::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CODBC2View::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CODBC2View::OnBnClickedButton3)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CODBC2View::OnClickList1)// �̰ɷ� ������ ����Ʈ ��Ʈ�ѿ� ����Ʈ��Ʈ��1 ���� �����Ѱ� �����
	ON_BN_CLICKED(IDC_BUTTON5, &CODBC2View::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CODBC2View::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CODBC2View::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CODBC2View::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CODBC2View::OnBnClickedButton8)
END_MESSAGE_MAP()

// CODBC2View ����/�Ҹ�

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
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CODBC2View::~CODBC2View()
{
}

void CODBC2View::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);


	//���� ����Ʈ ��Ʈ�� // ���⼭ ����Ʈ ��Ʈ��1���� ������ ���ڵ� ǥ������
	DDX_Text(pDX, IDC_EDIT1, m_pSet->m_ST_CAR);
	DDX_Text(pDX, IDC_EDIT2, m_pSet->m_ST_NAME);
	DDX_Text(pDX, IDC_EDIT3, m_pSet->m_ST_ELEC);
	DDX_Text(pDX, IDC_EDIT4, m_pSet->m_ST_PHONE);


	//���� ����Ʈ ��Ʈ�� ���̺�1�� �ҷ���
	DDX_Control(pDX, IDC_LIST1, m_list);

	//������ ����Ʈ ��Ʈ��// ���⼭ ���� �Է�
	DDX_Text(pDX, IDC_EDIT5, m_Car);
	DDX_Text(pDX, IDC_EDIT6, m_Name);
	DDX_Text(pDX, IDC_EDIT7, m_elec);
	DDX_Text(pDX, IDC_EDIT8, m_Phone);
	DDX_Text(pDX, IDC_EDIT9, m_Finded);

	//������ ����Ʈ ��Ʈ�� ���̺�2�� �ҷ���
	DDX_Control(pDX, IDC_LIST2, m_list2);

	//�Ѽ��Աݾ� ǥ��
	DDX_Text(pDX, IDC_EDIT10, m_icost);
}

BOOL CODBC2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CRecordView::PreCreateWindow(cs);

}

void CODBC2View::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_ODBC2Set;
	m_pSet2 = &GetDocument()->m_ODBCSet2;
	CRecordView::OnInitialUpdate();
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES | LVS_EX_TRACKSELECT);
	//���� ǥ�� üũ�ڽ� ǥ�� ���콺�� �������� Ŭ������ �ʾƵ� ���콺������ ��� �ڵ����� ����
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);

	m_list.InsertColumn(0, _T("������ȣ"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(1, _T("�̸�"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(2, _T("������ ��/��"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(3, _T("��ȭ��ȣ"), LVCFMT_LEFT, 100); 
	m_list.InsertColumn(4, _T("���� �ð�"), LVCFMT_LEFT, 200);


	//
	m_list2.SetExtendedStyle(m_list2.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES | LVS_EX_TRACKSELECT);
	//���� ǥ�� üũ�ڽ� ǥ�� ���콺�� �������� Ŭ������ �ʾƵ� ���콺������ ��� �ڵ����� ����
	m_list2.SetExtendedStyle(m_list2.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);

	m_list2.InsertColumn(0, _T("������ȣ"), LVCFMT_LEFT, 100);
	m_list2.InsertColumn(1, _T("�̸�"), LVCFMT_LEFT, 70);
	m_list2.InsertColumn(2, _T("��ȭ��ȣ"), LVCFMT_LEFT, 100);
	m_list2.InsertColumn(3, _T("���� �ð�"), LVCFMT_LEFT, 140);
	m_list2.InsertColumn(4, _T("���� �ð�"), LVCFMT_LEFT, 140);
	m_list2.InsertColumn(5, _T("���"), LVCFMT_LEFT, 100);

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
		_T("����")); // lpszFacename
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


// CODBC2View �μ�

BOOL CODBC2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);

}

void CODBC2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CODBC2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CODBC2View ����

#ifdef _DEBUG
void CODBC2View::AssertValid() const
{
	CRecordView::AssertValid();
}

void CODBC2View::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CODBC2Doc* CODBC2View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CODBC2Doc)));
	return (CODBC2Doc*)m_pDocument;
}
#endif //_DEBUG


/** CODBC2View �����ͺ��̽� ����*/
CRecordset* CODBC2View::OnGetRecordset()
{
	return m_pSet;
}

CRecordset* CODBC2View::OnGetRecordset2()
{
	return m_pSet2;
}




// CODBC2View �޽��� ó����

//�̰� �����ϸ� ��
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


//����â�� �Է�â���� ���� ����
/*�������� ��κ��� �ٲ������ �ٽ��ѹ� Ȯ���Ͽ� �߸� �����ϴ°��� �����ϱ� ����*/

/**���� ���� �� ����*/
int count = 0;//(��������)

/**���̺�1,2 �����ͺ��̽� �ҷ����� (����) */
void CODBC2View::OnBnClickedButton1()//�����ͺ��̽� �ҷ� ���� 

{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	renew();//���̺�1 (�Լ�����)
	OnBnClickedButton6();//���̺�2 (��ư����)��ư ��Ȱ��ȭ �ص�(�����ϸ� �Ⱥ���) 
}

/**�߰�*/
void CODBC2View::OnBnClickedButton2()//������ �߰�
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CTime tmCur = CTime::GetCurrentTime();//�ð� ���
	if (count == 10) {
		AfxMessageBox(_T("�������� 10�ڸ��� ��� ä���� ���� �Դϴ�."));
		return;
	}
	UpdateData(TRUE);//��Ʈ���� ���� ������ ����
	m_pSet->AddNew();//�߰�
	m_pSet->m_ST_CAR = m_Car;
	m_pSet->m_ST_NAME = m_Name;
	m_pSet->m_ST_ELEC = m_elec;
	m_pSet->m_ST_PHONE = m_Phone;
	m_pSet->m_ST_INTIME = tmCur;
	m_pSet->Update();
	UpdateData(FALSE);//������ ���� ��Ʈ�ѿ� ǥ��
	AfxMessageBox(_T("�����Ͱ� �߰��Ǿ����ϴ�."));
	renew();// ���̺�1, ����Ʈ ��Ʈ��1 ����
}

/**����*/
int cost;//��� (��������)
CTime time1=0;//�����ð� (��������)
void CODBC2View::OnBnClickedButton3()//����
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	time1 = m_pSet->m_ST_INTIME;//�����ð�
	CTime tmCur = CTime::GetCurrentTime();//�ð� ���
	CTimeSpan sTime = tmCur - m_pSet->m_ST_INTIME;//�� �����ð� ��� (����ð� - �����ð�) 
	
	CString csTime;
	csTime.Format(_T("%d�� %d�� %d�� %d��"), sTime.GetDays(), sTime.GetHours(), sTime.GetMinutes(),sTime.GetSeconds());
	
	int a=0;//��� ���


	if (m_pSet->m_ST_ELEC == TRUE) {
		a = ((sTime.GetDays() * 86400) + (sTime.GetHours() * 3600) + (sTime.GetMinutes() * 60) + (sTime.GetSeconds() * 1))*0.7;
		AfxMessageBox(_T("������ �Դϴ�. ����� 30% ���� �˴ϴ�. "));
	}else
		a = (sTime.GetDays() * 86400)+(sTime.GetHours()*3600)+(sTime.GetMinutes()*60)+(sTime.GetSeconds()*1);
	
	CString at;
	at.Format(_T("%d"), a);//AfxMessageBox�� ����ϱ����� CString���·�  �ٲٱ�

	// cost = _ttoi(at);//���CString���� int ������ �ٲٱ�
	cost = a;//320�����̶� �����ǹ� a�� int���̰� at�� CString���� _ttoi�� ���� CString�� int�� �ٲ� �� ����
	

	if (m_pSet->IsEOF())//���ڵ� ��ġ�� �������� ���
	{
		m_pSet->Delete();//����
		m_pSet->MovePrev();//������ ��ĭ �̵�
	}

	else if (m_pSet->IsBOF())//���ڵ� ��ġ�� ó���� ���
	{
		
		m_pSet->Delete();//����
		m_pSet->MoveNext();//�������� ��ĭ �̵�
	}

	else//������ ��ġ
	{
		m_pSet->Delete();//����
		m_pSet->MoveNext();//�������� ��ĭ �̵�
	}
	
	AfxMessageBox(_T("���� �ð���") + csTime +_T("�Դϴ�."));
	AfxMessageBox(_T("�����") + at + _T("�� �Դϴ�."));

	m_pSet->Requery(); //���ڵ� ������ �ٽ� ����(���� ��ħ) ������ �߱⶧���� ����ϴ� �޼���
	UpdateData(FALSE);//������ ���� ��Ʈ�ѷ� ����
	renew(); //���̺�1, ����Ʈ ��Ʈ��1 ����
	OnBnClickedButton7();//���̺�2�� ���� ������ ����
	OnBnClickedButton6();//���̺�2 ����Ʈ ��Ʈ��2 ���� 
}

/**����Ʈ ��Ʈ�ѿ��� ������ ���ڵ� ����Ʈ��Ʈ�ѿ� �ݿ�*/
void CODBC2View::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult)//����Ʈ ��Ʈ�ѿ��� ������ �� ����Ʈ ��Ʈ�ѿ� �ֱ�
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(true);
	int clickindex = m_list.GetSelectionMark();//����Ʈ ��Ʈ�ѿ��� ������ �ε��� ����
	
	
	m_pSet->MoveFirst();//ó������ �̵�
	//����Ʈ ��Ʈ���� ���� �Է� ����Ʈ ��Ʈ��(������)�� ����
	if (clickindex >= 0) {
		m_Car = m_list.GetItemText(clickindex, 0);//��
		m_Name = m_list.GetItemText(clickindex, 1);//�̸�
		CString b = m_list.GetItemText(clickindex, 2);//������ ��/��
		if ("1" == b){///**(��/����)*/
			m_elec = TRUE;//������
		}
		else m_elec = FALSE;//������ �ƴ�
		m_Phone = m_list.GetItemText(clickindex, 3);//��ȭ��ȣ

		
		while(m_pSet->m_ST_CAR!=m_Car) {//������ ������ m_pSet�� ����Ű�� �ϵ��� �����̱�
			m_pSet->MoveNext();
		}//Ŀ�� �̵�(���ڵ� �̵�)
		UpdateData(FALSE);
	} 
	else
		AfxMessageBox(_T("Please Select item"));

	renew();//���̺� 1 ����

	*pResult = 0;
}

/**�˻�*/
void CODBC2View::OnBnClickedButton4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_pSet->MoveFirst();
	
	while (m_pSet->m_ST_CAR != m_Finded) {//�Է��� ����ȣ�� ������ ����
		m_pSet->MoveNext();
		if (m_pSet->IsEOF()) { 
			AfxMessageBox(_T("��ġ�ϴ� ������ �����ϴ�.")); 
			m_pSet->MoveFirst(); 
			break; 
		}
	}//Ŀ�� �̵� (���ڵ� �̵�)

	//�˻��� �� ����â ����Ʈ��Ʈ�ѿ� (����) �־��ֱ�
	m_Car = m_pSet->m_ST_CAR;
	m_Name = m_pSet->m_ST_NAME;
	m_elec = m_pSet->m_ST_ELEC;
	m_Phone = m_pSet->m_ST_PHONE;
	UpdateData(FALSE);
}

/**����*/
void CODBC2View::OnBnClickedButton5()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_pSet->Edit();//������ ���ڵ� ���� 
	m_pSet->m_ST_CAR = m_Car;
	m_pSet->m_ST_NAME = m_Name;
	m_pSet->m_ST_ELEC = m_elec;
	m_pSet->m_ST_PHONE = m_Phone;
	m_pSet->Update();
	
	UpdateData(FALSE);
	renew();
	
}

/**���̺�1 ����*/
void CODBC2View::renew(){//������ ���̽� ����Ʈ ��Ʈ�� ����
	m_list.DeleteAllItems();//�ٽ� �ҷ����� ���� ����Ʈ�� �ִ� ���� �����
	CDatabase db;

	//������ ���̽� ��ü ���� �� ����
	db.OpenEx(_T("DSN=student"), 0);  

	//���ڵ�� ��ü ����, ������ �ҽ����� ������ ���ڵ� ������ ��Ÿ���ϴ�.
	CRecordset rs(&db);
	rs.Open(CRecordset::dynaset, _T("SELECT * FROM [���̺�1]"));

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

/**���̺�2 ����*/
void CODBC2View::OnBnClickedButton6()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_list2.DeleteAllItems();
	CDatabase db;

	db.OpenEx(_T("DSN=student"), 0);  

	CRecordset rs(&db);
	rs.Open(CRecordset::dynaset, _T("SELECT * FROM [���̺�2]"));

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

/**���� ���̺�2�� ����*/
void CODBC2View::OnBnClickedButton7()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_pSet2->Open();//���̺�2 ����
	CTime tmCur = CTime::GetCurrentTime();//�ð� ���
	

	UpdateData(TRUE);
	m_pSet2->MoveFirst();
	m_pSet2->AddNew();//������ �߰�
	
	m_pSet2->m_ST_DE_VEHICL = m_Car;//����ȣ
	m_pSet2->m_ST_DE_NAME = m_Name;//�̸�
	m_pSet2->m_ST_DE_PHONE = m_Phone;//��ȭ��ȣ
	m_pSet2->m_ST_DE_INTIME = time1;//�����ð�
	m_pSet2->m_ST_DE_OUTTIME = tmCur;//�����ð�
	m_pSet2->m_ST_DE_COST = cost;//���
	
	m_pSet2->Update();
	UpdateData(FALSE);
	AfxMessageBox(_T("�����Ͱ� �߰��Ǿ����ϴ�."));
	m_pSet2->Close();//���̺�2 �ݱ�
}


/**�� ���� �ݾ�*/
void CODBC2View::OnBnClickedButton8()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_icost = 0;

	m_pSet2->Open();//���̺�2�� ����
	UpdateData(TRUE);
	m_icost = 0;
	m_pSet2->MoveFirst();//���̺�2�� ó�� ���ڵ�� �̵�
	while (!m_pSet2->IsEOF()) {//���̺�2�� ����������
		m_icost = m_icost + m_pSet2->m_ST_DE_COST;//m_icost�� ó������ ������ ��ݱ��� ���ϱ�
		m_pSet2->MoveNext();
	}
	UpdateData(FALSE);
	m_pSet2->Close();//���̺�2 �ݱ�
}

/*�߰� �� ���
���� ���� �̹��� �����
*/
/*ppt�� ���� ���(�켱����)
	1.OnBnClickedButton2() �߰�,
	2.OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) ����Ʈ ��Ʈ�ѿ��� ������ ���ڵ� ����Ʈ��Ʈ�ѿ� �ݿ�
	3.OnBnClickedButton3() ����
	4.OnBnClickedButton4() �˻�
	5.OnBnClickedButton8() �� ���� �ݾ�
	6.OnBnClickedButton7() ���� ���̺�2�� ����(1�� �߰��� ����� ����)
	7.OnBnClickedButton1()=renew()+OnBnClickedButton6()// ���� �߿��ϰ� ���� �ȵ�
*/