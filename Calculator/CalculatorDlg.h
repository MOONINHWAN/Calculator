
// CalculatorDlg.h: 헤더 파일
//
#pragma once
#include "afxwin.h"

class CCalculatorDlg : public CDialogEx
{
public:
	CCalculatorDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	CFont m_Font;  // 큰 글씨 폰트
	CEdit m_EditDisplay;   // 결과 표시창
	CString m_CurrentInput; // 현재 입력된 숫자
	double m_StoredValue;   // 저장된 값 (이전 숫자)
	char m_Operator;        // 현재 연산자

	void AppendDigit(int digit);
	void SetOperator(char op);
	void CalculateResult();
	void Clear();
	
	bool m_IsResultDisplayed;

public:
	afx_msg void OnBnClickedButtonDigit0();
	afx_msg void OnBnClickedButtonDigit1();
	afx_msg void OnBnClickedButtonDigit2();
	afx_msg void OnBnClickedButtonDigit3();
	afx_msg void OnBnClickedButtonDigit4();
	afx_msg void OnBnClickedButtonDigit5();
	afx_msg void OnBnClickedButtonDigit6();
	afx_msg void OnBnClickedButtonDigit7();
	afx_msg void OnBnClickedButtonDigit8();
	afx_msg void OnBnClickedButtonDigit9();

	afx_msg void OnBnClickedButtonOperator();
	afx_msg void OnBnClickedButtonEqual();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonDot();
	afx_msg void OnBnClickedButtonBackspace();
	afx_msg void OnBnClickedButtonSign();
	afx_msg void OnBnClickedButtonSquare();
	

};
