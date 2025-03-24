
// CalculatorDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent), m_StoredValue(0), m_Operator('\0')
{
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DISPLAY, m_EditDisplay);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CCalculatorDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_EQUAL, &CCalculatorDlg::OnBnClickedButtonEqual)

	//  숫자 버튼 개별 매핑
	ON_BN_CLICKED(IDC_BUTTON_0, &CCalculatorDlg::OnBnClickedButtonDigit0)
	ON_BN_CLICKED(IDC_BUTTON_1, &CCalculatorDlg::OnBnClickedButtonDigit1)
	ON_BN_CLICKED(IDC_BUTTON_2, &CCalculatorDlg::OnBnClickedButtonDigit2)
	ON_BN_CLICKED(IDC_BUTTON_3, &CCalculatorDlg::OnBnClickedButtonDigit3)
	ON_BN_CLICKED(IDC_BUTTON_4, &CCalculatorDlg::OnBnClickedButtonDigit4)
	ON_BN_CLICKED(IDC_BUTTON_5, &CCalculatorDlg::OnBnClickedButtonDigit5)
	ON_BN_CLICKED(IDC_BUTTON_6, &CCalculatorDlg::OnBnClickedButtonDigit6)
	ON_BN_CLICKED(IDC_BUTTON_7, &CCalculatorDlg::OnBnClickedButtonDigit7)
	ON_BN_CLICKED(IDC_BUTTON_8, &CCalculatorDlg::OnBnClickedButtonDigit8)
	ON_BN_CLICKED(IDC_BUTTON_9, &CCalculatorDlg::OnBnClickedButtonDigit9)

	ON_BN_CLICKED(IDC_BUTTON_DOT, &CCalculatorDlg::OnBnClickedButtonDot)
	ON_BN_CLICKED(IDC_BUTTON_BACKSPACE, &CCalculatorDlg::OnBnClickedButtonBackspace)
	ON_BN_CLICKED(IDC_BUTTON_SIGN, &CCalculatorDlg::OnBnClickedButtonSign)
	ON_BN_CLICKED(IDC_BUTTON_SQUARE, &CCalculatorDlg::OnBnClickedButtonSquare)

		
	//  연산자 버튼 개별 매핑
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CCalculatorDlg::OnBnClickedButtonOperator)
	ON_BN_CLICKED(IDC_BUTTON_SUB, &CCalculatorDlg::OnBnClickedButtonOperator)
	ON_BN_CLICKED(IDC_BUTTON_MUL, &CCalculatorDlg::OnBnClickedButtonOperator)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &CCalculatorDlg::OnBnClickedButtonOperator)
END_MESSAGE_MAP()

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//  큰 글꼴 설정
	m_Font.CreatePointFont(240, _T("Arial"));
	m_EditDisplay.SetFont(&m_Font);

	m_IsResultDisplayed = false;
	m_EditDisplay.SetWindowTextW(_T("0"));
	return TRUE;
}

void CCalculatorDlg::OnBnClickedButtonDigit0() { AppendDigit(0); }
void CCalculatorDlg::OnBnClickedButtonDigit1() { AppendDigit(1); }
void CCalculatorDlg::OnBnClickedButtonDigit2() { AppendDigit(2); }
void CCalculatorDlg::OnBnClickedButtonDigit3() { AppendDigit(3); }
void CCalculatorDlg::OnBnClickedButtonDigit4() { AppendDigit(4); }
void CCalculatorDlg::OnBnClickedButtonDigit5() { AppendDigit(5); }
void CCalculatorDlg::OnBnClickedButtonDigit6() { AppendDigit(6); }
void CCalculatorDlg::OnBnClickedButtonDigit7() { AppendDigit(7); }
void CCalculatorDlg::OnBnClickedButtonDigit8() { AppendDigit(8); }
void CCalculatorDlg::OnBnClickedButtonDigit9() { AppendDigit(9); }

void CCalculatorDlg::OnBnClickedButtonOperator()
{
	CWnd* pWnd = GetFocus();
	if (!pWnd) return;

	UINT nID = pWnd->GetDlgCtrlID();
	switch (nID)
	{
	case IDC_BUTTON_ADD: SetOperator('+'); break;
	case IDC_BUTTON_SUB: SetOperator('-'); break;
	case IDC_BUTTON_MUL: SetOperator('*'); break;
	case IDC_BUTTON_DIV: SetOperator('/'); break;
	}
}

void CCalculatorDlg::OnBnClickedButtonEqual() 
{
	CalculateResult(); 
	m_IsResultDisplayed = true;
}
void CCalculatorDlg::OnBnClickedButtonClear() { Clear(); }

void CCalculatorDlg::AppendDigit(int digit)
{
	// 클리어 버튼이 눌린 후 첫 입력이면 초기화
	if (m_IsResultDisplayed)
	{
		m_CurrentInput.Empty();
		m_IsResultDisplayed = false;  // 플래그 해제
	}

	if (m_CurrentInput == _T("0"))  // 첫 입력이면 0 제거
		m_CurrentInput = _T("");

	m_CurrentInput.AppendFormat(_T("%d"), digit);
	m_EditDisplay.SetWindowTextW(m_CurrentInput);
}

void CCalculatorDlg::SetOperator(char op)
{
	if (!m_CurrentInput.IsEmpty()) m_StoredValue = _ttof(m_CurrentInput);
	m_CurrentInput.Empty();
	m_Operator = op;
}

void CCalculatorDlg::CalculateResult()
{
	double secondValue = _ttof(m_CurrentInput);
	double result = 0.0;

	if (m_Operator == '+') result = m_StoredValue + secondValue;
	else if (m_Operator == '-') result = m_StoredValue - secondValue;
	else if (m_Operator == '*') result = m_StoredValue * secondValue;
	else if (m_Operator == '/' && secondValue != 0) result = m_StoredValue / secondValue;
	else
	{
		AfxMessageBox(_T("0으로 나눌 수 없습니다!"));
		return;
	}

	//  유효한 자리수만 표시하는 형식 적용
	CString resultStr;
	resultStr.Format(_T("%.10g"), result);  // 유효 숫자 10자리까지 표시 (불필요한 0 제거)

	//  결과 표시
	m_CurrentInput = resultStr;
	m_EditDisplay.SetWindowTextW(m_CurrentInput);
}

void CCalculatorDlg::Clear()
{
	// 클리어 버튼은 한번에 다 지우기
	if (!m_CurrentInput.IsEmpty())
	{
		m_CurrentInput = _T("0");
	}

	//  결과창에 업데이트
	m_EditDisplay.SetWindowTextW(m_CurrentInput);
}

void CCalculatorDlg::OnBnClickedButtonDot()
{
	//  이미 소수점이 포함되어 있으면 추가 X
	if (m_CurrentInput.Find(_T(".")) == -1)
	{
		if (m_CurrentInput.IsEmpty())
			m_CurrentInput = _T("0"); // 숫자 없이 `.` 입력 시 `0.` 으로 변환

		m_CurrentInput.Append(_T("."));
		m_EditDisplay.SetWindowTextW(m_CurrentInput);
	}
}

void CCalculatorDlg::OnBnClickedButtonBackspace()
{
	if (!m_CurrentInput.IsEmpty())
	{
		m_CurrentInput = m_CurrentInput.Left(m_CurrentInput.GetLength() - 1);
		if (m_CurrentInput.IsEmpty()) m_CurrentInput = _T("0"); // 모든 숫자 삭제 시 0으로 설정
	}
	m_EditDisplay.SetWindowTextW(m_CurrentInput);
}

void CCalculatorDlg::OnBnClickedButtonSign()
{
	if (m_CurrentInput != _T("0"))
	{
		if (m_CurrentInput[0] == '-')
			m_CurrentInput.Delete(0, 1);  // 음수 → 양수
		else
			m_CurrentInput = _T("-") + m_CurrentInput;  // 양수 → 음수

		m_EditDisplay.SetWindowTextW(m_CurrentInput);
	}
}

void CCalculatorDlg::OnBnClickedButtonSquare()
{
	double num = _ttof(m_CurrentInput);

	/*
	if (num < 0)
	{
		AfxMessageBox(_T("음수의 제곱은 계산할 수 없습니다!"));
		return;
	}
	*/

	num = num * num;

	//  유효 숫자만 남기도록 변환 
	CString resultStr;
	resultStr.Format(_T("%.10g"), num);
	
	//  결과를 화면에 표시
	m_CurrentInput = resultStr;
	m_EditDisplay.SetWindowTextW(m_CurrentInput);
}