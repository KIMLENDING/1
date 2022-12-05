



#include "stdafx.h"
#include "ODBC2.h"
#include "ODBCSet2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CODBCSet2, CRecordset)
CODBCSet2::CODBCSet2(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ST_DE_VEHICL = L"";
	m_ST_DE_NAME = L"";
	m_ST_DE_PHONE = L"";
	m_ST_DE_INTIME = 0;
	m_ST_DE_OUTTIME = 0;
	m_ST_DE_COST = 0;

	m_nFields = 6;
	m_nDefaultType = dynaset;
}
CString CODBCSet2::GetDefaultConnect()
{
	return _T("DSN=student");//DBQ=C:\\SOURCE\\VS2019\\CHAPTER14\\student.accdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}
CString CODBCSet2::GetDefaultSQL()
{
	return _T("[Å×ÀÌºí2]");

}
void CODBCSet2::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	

	RFX_Text(pFX, _T("[ST_DE_VEHICL]"), m_ST_DE_VEHICL);
	RFX_Text(pFX, _T("[ST_DE_NAME]"), m_ST_DE_NAME);
	RFX_Text(pFX, _T("[ST_DE_PHONE]"), m_ST_DE_PHONE);
	RFX_Date(pFX, _T("[ST_DE_INTIME]"), m_ST_DE_INTIME);
	RFX_Date(pFX, _T("[ST_DE_OUTTIME]"), m_ST_DE_OUTTIME);
	RFX_Int(pFX, _T("[ST_DE_COST]"), m_ST_DE_COST);
}
#ifdef _DEBUG
void CODBCSet2::AssertValid() const
{
	CRecordset::AssertValid();
}

void CODBCSet2::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG