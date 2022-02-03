
// MFCApplication1Dlg.h : ���� ���������
//

#pragma once
#include "MFCApplication1.h"


// ���������� ���� CMFCApplication1Dlg
class CMFCApplication1Dlg : public CDialogEx
{
// ��������
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;// ���������� ������ �������� ������ ���������

	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();// ���������� ������������� ����������� ����
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam),
				OnPaint();// ������� ��������� ����
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CHypocycloidCalc m_Calc;// ���������� ���������� ������ �������� ��������� ��� �������� ������ � ��� ������������
	CMyGraph m_Graph;// ���������� ������ ��������� ������� �������
	afx_msg void OnEnChangeEdit1(),
		OnEnChangeEdit2(),
		OnEnChangeEdit3(), // ������� ��� ��������� ����� ������
		OnTimer(UINT_PTR nIDEvent), // ������� ��������� �������
		OnBnClickedOk(),  // ������� ��������� �������� ������� �� ������ ��
		OnBnClickedButtonUp(), 
		OnBnClickedButtonDn(),
		OnBnClickedButtonR(),
		OnBnClickedButtonL(),
		OnBnClickedButton7(),//������� ��������� ������ ������
		OnBnClickedButtonSave(), //������� ��������� ������ ���������
		OnBnClickedButtonStart(),//������� ��������� ������ �����/����
		OnBnClickedCheck1(),//������� ��������� ������ ��������
		OnCbnSelchangeCombo2();//������� ��������� ���������
	void StopMyTimer(),// ����������� ������� ��������� �������
		StartMyTimer();// ����������� ������� ������� �������
	CProgressCtrl m_prCtrl;			//���������� ��� ������ � ��������� ���������� Progress Control
	CEdit Input_field;				//���� �����
	CButton m_control_erasing,
			m_control_live;			// ���������� ��� ��������� ������ �������� � �������� ��������
	BOOL m_boolean_erasing; // ���������� ������ BOOL ������ �������� �������
	CStatic m_control_static_progress;//���������� ��� ��������� ������ ��� ����� ���������
	CComboBox m_control_speed;//���������� ��� ��������� ���������
	UINT speed = 40;//���������� ��� ������ �������� ��������
	CString m_edit_def_r_outer,
		m_edit_def_r_inner;
	double m_edit_def_f;//���������� �������� ������ ����� �����
};
