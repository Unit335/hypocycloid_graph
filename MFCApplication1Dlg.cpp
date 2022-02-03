// MFCApplication1Dlg.cpp : ���� ����������
//

#include "stdafx.h"
#include "stdio.h"
#include "MFCApplication1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MY_TIMER_ID	55555// ����������� �������� ������� MY_TIMER

#include <initguid.h>												//���������� ���������� �������������
DEFINE_GUID(ImageFormatBMP, 0xb96b3cab, 0x0728, 0x11d3, 0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e); //��� ���������� �������� � ������ ������ ������������� ���������� �� ��������������� ������
DEFINE_GUID(ImageFormatJPEG, 0xb96b3cae, 0x0728, 0x11d3, 0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);
DEFINE_GUID(ImageFormatPNG, 0xb96b3caf, 0x0728, 0x11d3, 0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);
DEFINE_GUID(ImageFormatGIF, 0xb96b3cb0, 0x0728, 0x11d3, 0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);


// ���������� ���� CAboutDlg ������������ ��� �������� �������� � ����������

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();// ����������� ���� "� ���������"

// ������ ����������� ���� "� ���������"
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

// ����������
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedCombo1();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CAboutDlg::OnStnClickedCombo1()
{
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_STN_CLICKED(IDC_COMBO1, &CAboutDlg::OnStnClickedCombo1)
END_MESSAGE_MAP()


// ���������� ���� CMFCApplication1Dlg



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
	, m_boolean_erasing(FALSE)
	, m_edit_def_f(6.283185)
	, m_edit_def_r_outer(_T("1"))
	, m_edit_def_r_inner(_T("1"))// ����������� ��������� �������� ����������
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);//�������� ������ ����������
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, Input_field);
	DDX_Control(pDX, IDC_PROGRESS1, m_prCtrl);
	DDX_Control(pDX, IDC_CHECK1, m_control_erasing);
	DDX_Check(pDX, IDC_CHECK1, m_boolean_erasing);
	DDX_Control(pDX, ID_BUTTON1, m_control_live);
	DDX_Control(pDX, IDC_PROGRESS, m_control_static_progress);
	DDX_Text(pDX, IDC_EDIT1, m_edit_def_f);
	DDV_MinMaxDouble(pDX, m_edit_def_f, 6.283185, DBL_MAX);
	DDX_Control(pDX, IDC_COMBO2, m_control_speed);
	DDX_Text(pDX, IDC_EDIT2, m_edit_def_r_outer);
	DDX_Text(pDX, IDC_EDIT3, m_edit_def_r_inner);//����������� ���������� ������ ������ ��� CheckBox, Static � ���������� ���������� ����������� ����
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CMFCApplication1Dlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCApplication1Dlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CMFCApplication1Dlg::OnEnChangeEdit3)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CMFCApplication1Dlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(ID_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_CHECK1, &CMFCApplication1Dlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButtonDn)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication1Dlg::OnBnClickedButtonL)
	ON_BN_CLICKED(IDC_BUTTON_5, &CMFCApplication1Dlg::OnBnClickedButtonR)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCApplication1Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication1Dlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ����������� ��������� CMFCApplication1Dlg

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���������� ������ "� ���������..." � ��������� ����.

	// IDM_ABOUTBOX ������ ���� � �������� ��������� �������.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ������ ������ ��� ����� ����������� ����.  ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, TRUE);		// ������ ������

	// TODO: �������� �������������� �������������

	m_Graph.SubclassDlgItem(IDC_MYGRAPH, this);

	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();	//������� ���������� ��� ������ �������� � ��������(���������� �������� �� ��������� �� ��������)
	CRect rc;														//������� ������ ��� ��������� �������
	m_Graph.GetClientRect(&rc);						
	app->parameters.xCenter = rc.CenterPoint().x;					//���������� ����� ���� ������� ��� ���������
	app->parameters.yCenter = rc.CenterPoint().y;
	m_control_speed.AddString(L"x1");
	m_control_speed.AddString(L"x5");
	m_control_speed.AddString(L"x0.5");
	m_control_speed.AddString(L"x999");//��������� ������ � ��������
	m_control_speed.SetCurSel(1);//������������� ��������� �������� � ��������


	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();// ��� ������� �� ����� "� ���������" � ����������� ���� ����������� ���������� ���� "� ���������"
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������.  ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �������� ���������� ��� ���������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ������������ ������ �� ������ ����������� ��������������
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ��������� ������
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ������� �������� ��� ������� ��� ��������� ����������� ������� ��� �����������
//  ���������� ����.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedOk()
{
	int Res = AfxMessageBox(L"�������� !\n�� ������������� ������ ��������� ������ ��������� ?", MB_YESNO, MB_ICONQUESTION);
	if (Res == IDYES)
	CDialogEx::OnOK();
}//��� ������� �� ������ �������, �������� ���� ������������� ������, ���� ������ ���������� �����- ��������� �����������

void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();	//���������� �������� �� ��������� �� ��������
	GraphParameters &par = app->parameters;
	par.dXRad += .017;
	m_Calc.SetParams(par);
	if (par.dXRad > 2. * M_PI + 0.17)
	{
		UpdateData();
		OnBnClickedButtonStart();
	}
	m_prCtrl.SetPos(int(par.dXRad * 180. / M_PI) % 360);			//������������� �������� � ����� ���������
	if (m_Graph.m_Npt % 7 == 0)
		m_control_static_progress.SetWindowText(L"��������, ��� ��������� .");
	else if (m_Graph.m_Npt % 3 == 0)
			m_control_static_progress.SetWindowText(L"��������, ��� ��������� . .");
		else if (m_Graph.m_Npt % 5 == 0)
			m_control_static_progress.SetWindowText(L"��������, ��� ��������� . . .");//��������� ������ ��� ����� ���������
	m_Graph.m_Npt++;												//����������� ���������� ������������ �����
	m_Graph.Invalidate();
	par.nCur++;
	CDialogEx::OnTimer(nIDEvent);
}//�������� �� ������ ������ �������

void CMFCApplication1Dlg::OnBnClickedButtonStart()
{
	CButton *pW = (CButton *)GetDlgItem(ID_BUTTON1);					//������� ���������� ��� ������ � ������� Start
	if (pW)
	{
		if (pW->GetCheck())												//���� ������ ������
		{
			StartMyTimer();												//��������� ������
			m_Graph.m_Npt = m_Calc.GetNumPoints();						//������� ���������� ����� � ������� � ����� �������
		}
		else
		{
			StopMyTimer();												//��������� �������
			m_Graph.m_Npt = 0;											//��������� ���������� �����
		}
	}
}//�������� ��� ������� �� ������ ��������

void CMFCApplication1Dlg::OnBnClickedButtonUp()						//���������� ������� ������� ������ Up
{
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();	//���������� �������� �� ��������� �� ��������
	GraphParameters par = app->parameters;							//����� ��������, ������� ��� ��������� GraphParameters
	par.yCenter--;													//������� ����� ������� ��������� �� y �����
	m_Calc.SetParams(par);											//������������� ����� ��������� ������� ���������
	m_Graph.Invalidate();											//��������� ���� �������

	if (m_control_live.GetCheck())
	{
		StopMyTimer();
		StartMyTimer();
	}
}//��������� ������ ������ �����

void CMFCApplication1Dlg::OnBnClickedButtonDn()						//���������� ������� ������� ������ Dn
{
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();	//���������� �������� �� ��������� �� ��������
	GraphParameters par = app->parameters;							//����� ��������, ������� ��� ��������� GraphParameters
	par.yCenter++;													//������� ����� ������� ��������� �� y ����
	m_Calc.SetParams(par);											//������������� ����� ��������� ������� ���������
	m_Graph.Invalidate();											//��������� ���� �������

	if (m_control_live.GetCheck())
	{
		StopMyTimer();
		StartMyTimer();
	}
}//��������� ������ ������ ����

void CMFCApplication1Dlg::OnBnClickedButtonR()						//���������� ������� ������� ������ R
{
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();	//���������� �������� �� ��������� �� ��������
	GraphParameters par = app->parameters;							//����� ��������, ������� ��� ��������� GraphParameters
	par.xCenter++;													//������� ����� ������� ��������� �� x ������
	m_Calc.SetParams(par);											//������������� ����� ��������� ������� ���������
	m_Graph.Invalidate();											//��������� ���� �������

	if (m_control_live.GetCheck())
	{
		StopMyTimer();
		StartMyTimer();
	}
}//��������� ������ ������ ������

void CMFCApplication1Dlg::OnBnClickedButtonL()						//���������� ������� ������� ������ L
{
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();	//���������� �������� �� ��������� �� ��������
	GraphParameters par = app->parameters;							//����� ��������, ������� ��� ��������� GraphParameters
	par.xCenter--;													//������� ����� ������� ��������� �� x �����
	m_Calc.SetParams(par);											//������������� ����� ��������� ������� ���������
	m_Graph.Invalidate();											//��������� ���� �������

	if (m_control_live.GetCheck())
	{
		StopMyTimer();
		StartMyTimer();
	}
}//��������� ������ ������ �����

void CMFCApplication1Dlg::OnBnClickedButton7()
{
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();	//���������� �������� �� ��������� �� ��������
	GraphParameters par = app->parameters;							//����� ��������, ������� ��� ��������� GraphParameters
	CRect rc;														//������� ������ ��� ��������� �������
	m_Graph.GetClientRect(&rc);										//�������� ������������� ���� ���������
	par.xCenter= rc.CenterPoint().x;								//���������� ������� �� �
	par.yCenter= rc.CenterPoint().y;								//���������� ������� �� y 
	m_Calc.SetParams(par);											//������������� ����� ��������� ������� ���������
	m_Graph.Invalidate();											//��������� ���� �������

	if (m_control_live.GetCheck())
	{
		StopMyTimer();
		StartMyTimer();
	}
}//��������� ������ �������������

void CMFCApplication1Dlg::OnBnClickedButtonSave()
{
	CWnd *pWn = GetDlgItem(IDC_MYGRAPH);
	if (!pWn)
		return;
	CWindowDC winDC(pWn);
	CRect rc;
	pWn->GetClientRect(&rc);
	CDC memDC;														//�������� ������ ������� ��������� ����������
	memDC.CreateCompatibleDC(&winDC);								//���������� ��������� ���������� 
	CBitmap bitMap;													//������� ������ ��������, ������ ����� ��������� � memDC
	bitMap.CreateCompatibleBitmap(&winDC, rc.Width(), rc.Height());	
	HGDIOBJ pOld = memDC.SelectObject(&bitMap);						//�������� ��������� � memDC �������� SelectObject
	memDC.FillSolidRect(&rc, RGB(0, 255, 0));						//����������� ��������� ����������� � ������� BitBlt
	memDC.BitBlt(0, 0, rc.Width(), rc.Height(), &winDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOld);

	static TCHAR szFilter[] = _T("BMP ����� (*.bmp)|*.bmp|")	
		_T("PNG ����� (*.png)|*.png|GIF ����� (*.gif)|*.gif|")		//������ ��������� �������� ����������
		_T("JPG ����� (*.jpg)|*.jpg|All ����� (*.*)|*.*||");
	CFileDialog dlg(FALSE, _T(".bmp"), NULL, 6UL, szFilter);		//����� ������������ ������� ���������� ������
	if (IDOK == dlg.DoModal())										//��������� ��������� ������ ������� (������ ���� ������� � ����� ����� ����������, ���� ���� �� ������) 
	{
		CImage image;												//������� ������ ������ CImage (���������� � ������ ������� )
		image.Attach(HBITMAP(bitMap));								//����������� � ���� �������� �� ������� CBitmap
		CString strFull = dlg.GetOFN().lpstrFile;					//���� � �����, ������������ �� ������� ���������� ������
		HRESULT hr;													//�������� ������������ ���� ���������� ���������� �������� (S_OK � �������)
		if (-1 != strFull.Find(_T(".png")))							//�������������� ����� ������� �� ����� ����� (���������� � ����� ����� ���������� ������ GUID)
			hr = image.Save(strFull, ImageFormatPNG);
		else if (-1 != strFull.Find(_T(".jpg")))
			hr = image.Save(strFull, ImageFormatJPEG);
		else if (-1 != strFull.Find(_T(".gif")))
			hr = image.Save(strFull, ImageFormatGIF);
		else if (-1 != strFull.Find(_T(".bmp")))
			hr = image.Save(strFull, ImageFormatBMP);
		else
		{
			strFull += _T(".bmp");
			hr = image.Save(strFull, ImageFormatBMP);
		}

		if (FAILED(hr))												//���� ���������� �������� �� ���� ��������� �������
		{
			CString strErr;
			strErr.Format(L" �� ������� ��������� ���� : %s, %x ", (LPCTSTR)strFull, hr);	//������� �� ����� ��������� � ������������� ���������� �����
			AfxMessageBox(strErr, MB_OK | MB_ICONERROR);			//��������� ������ �������� � ���������� �������� � ������� ��������� � ������� ������� AfxMessageBox
		}
	}
}//��������� ������ ���������


void CMFCApplication1Dlg::OnBnClickedCheck1()
{
	UpdateData();
	CButton* rW = (CButton*)GetDlgItem(IDC_CHECK1);//����������� ������ � ������ ����������
	if (rW)
	{
		if (rW->GetCheck())							//���� ������ ������, �� �������� ������� � ��������������	 				
		{
			rW->SetWindowText(L"�� ���������");
			if (m_control_live.GetCheck())
			{
				StopMyTimer();
				StartMyTimer();
			}
		}
		else										//���� ������ �� ������, �� �������� ������� � ��������������	
		{
			rW->SetWindowText(L"��� ��������");
			if (m_control_live.GetCheck())
			{
				StopMyTimer();
				StartMyTimer();
			}
		}
	}
}//��������� ������ ��������

void CMFCApplication1Dlg::StopMyTimer()
{
	CButton* pW = (CButton*)GetDlgItem(ID_BUTTON1);
	pW->SetWindowText(_T("�����"));
	pW->SetCheck(0);
	m_control_static_progress.SetWindowText(L"����� ������ ��������, ������� '�����'");
	KillTimer(MY_TIMER_ID);
}//������� ��������� �������

void CMFCApplication1Dlg::StartMyTimer()
{
	OnCbnSelchangeCombo2();											// ��������� �������� ���������� ��������
	CButton* pW = (CButton*)GetDlgItem(ID_BUTTON1);
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();
	pW->SetWindowText(_T("����"));
	pW->SetCheck(1);
	m_control_static_progress.SetWindowText(L"��������, ��� ���������");
	GraphParameters par = app->parameters;							//����� ��������, ������� ��� ��������� GraphParameters
	par.nCur = 0;
	par.dXRad = 0.;
	m_Calc.SetParams(par);											//��������� ��������� �������
	SetTimer(MY_TIMER_ID, speed, NULL);								//��������� ������ �� ��������� speed
}//������� ������ �������


void CMFCApplication1Dlg::OnEnChangeEdit1()
{
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();	//���������� �������� �� ��������� �� ��������
	CString strI;
	CWnd* editText = GetDlgItem(IDC_EDIT1);							//������� ���������� ��� ������ � ����� �����
	if (editText != nullptr)
		editText->GetWindowText(strI);								//�������� ����� - ��������, ��������� �������������
	double val = _wtof(strI);
		app->parameters.f = val;									//������� � ���������� ��������� ��������� �������� ���� �������� ��������� ����������

		if (m_control_live.GetCheck())
		{
			StopMyTimer();
			StartMyTimer();
		}
}

void CMFCApplication1Dlg::OnEnChangeEdit2()
{
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();	//���������� �������� �� ��������� �� ��������
	CString strI;
	CWnd* editText = GetDlgItem(IDC_EDIT2);							//������� ���������� ��� ������ � ����� �����
	if (editText != nullptr)
		editText->GetWindowText(strI);								//�������� ����� - ��������, ��������� �������������
	double val = _wtof(strI);
	app->parameters.radius_outer = val;								//������� � ���������� ��������� ��������� �������� ������� ���������� ����������

	if (m_control_live.GetCheck())
	{
		StopMyTimer();
		StartMyTimer();
	}
}


void CMFCApplication1Dlg::OnEnChangeEdit3()
{
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();	//���������� �������� �� ��������� �� ��������
	CString strI;
	CWnd* editText = GetDlgItem(IDC_EDIT3);							//������� ���������� ��� ������ � ����� �����
	if (editText != nullptr)
		editText->GetWindowText(strI);								//�������� ����� - ��������, ��������� �������������
	double val = _wtof(strI);
	app->parameters.radius_inner = val;								//������� � ���������� ��������� ��������� �������� ������� ������� ����������

	if (m_control_live.GetCheck())
	{
		StopMyTimer();
		StartMyTimer();
	}
}

void CMFCApplication1Dlg::OnCbnSelchangeCombo2()
{
	int m_sp = m_control_speed.GetCurSel();
	if (m_sp == 0) //���� ������� �������� �0,5
		speed = 80;//�������� ���������
	else if (m_sp == 1)//���� ������� �������� �1
		speed = 40;//�������� �������
	else if (m_sp == 2)//���� ������� �������� �5
		speed = 8; //�������� �������
	else speed = 40;//����� �������� �������� �� ���������
	if (m_control_live.GetCheck())
	{
		StopMyTimer();
		StartMyTimer();
	}
}
