// MFCApplication1Dlg.cpp : файл реализации
//

#include "stdafx.h"
#include "stdio.h"
#include "MFCApplication1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MY_TIMER_ID	55555// Определение счётчика таймера MY_TIMER

#include <initguid.h>												//глобальный уникальный идентификатор
DEFINE_GUID(ImageFormatBMP, 0xb96b3cab, 0x0728, 0x11d3, 0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e); //для сохранения картинки в нужный формат идентификатор выбирается из представленного списка
DEFINE_GUID(ImageFormatJPEG, 0xb96b3cae, 0x0728, 0x11d3, 0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);
DEFINE_GUID(ImageFormatPNG, 0xb96b3caf, 0x0728, 0x11d3, 0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);
DEFINE_GUID(ImageFormatGIF, 0xb96b3cb0, 0x0728, 0x11d3, 0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();// Определение окна "О программе"

// Данные диалогового окна "О программе"
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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


// диалоговое окно CMFCApplication1Dlg



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
	, m_boolean_erasing(FALSE)
	, m_edit_def_f(6.283185)
	, m_edit_def_r_outer(_T("1"))
	, m_edit_def_r_inner(_T("1"))// Определение начальных значений переменных
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);//Загрузка иконки приложения
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
	DDX_Text(pDX, IDC_EDIT3, m_edit_def_r_inner);//Определение переменных обмена данных для CheckBox, Static и управления элементами диалогового окна
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


// обработчики сообщений CMFCApplication1Dlg

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, TRUE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	m_Graph.SubclassDlgItem(IDC_MYGRAPH, this);

	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();	//создаем переменную для работы напрямую с диалогом(наследника вызываем по указателю из родителя)
	CRect rc;														//создаем объект для рисования графика
	m_Graph.GetClientRect(&rc);						
	app->parameters.xCenter = rc.CenterPoint().x;					//определяем центр окна графика для рисования
	app->parameters.yCenter = rc.CenterPoint().y;
	m_control_speed.AddString(L"x1");
	m_control_speed.AddString(L"x5");
	m_control_speed.AddString(L"x0.5");
	m_control_speed.AddString(L"x999");//добавляем строки в листбокс
	m_control_speed.SetCurSel(1);//устанавливаем начальное значение в листбокс


	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();// При нажатии на пункт "О программе" в контекстном меню открывается диалоговое окно "О программе"
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedOk()
{
	int Res = AfxMessageBox(L"Внимание !\nВы действительно хотите завершить работу программы ?", MB_YESNO, MB_ICONQUESTION);
	if (Res == IDYES)
	CDialogEx::OnOK();
}//при нажатии на кнопку закрыть, появится окно подтверждения выхода, если клиент подтвердил выход- программа закрывается

void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();	//наследника вызываем по указателю из родителя
	GraphParameters &par = app->parameters;
	par.dXRad += .017;
	m_Calc.SetParams(par);
	if (par.dXRad > 2. * M_PI + 0.17)
	{
		UpdateData();
		OnBnClickedButtonStart();
	}
	m_prCtrl.SetPos(int(par.dXRad * 180. / M_PI) % 360);			//устанавливаем движение в шкале прогресса
	if (m_Graph.m_Npt % 7 == 0)
		m_control_static_progress.SetWindowText(L"Внимание, идёт отрисовка .");
	else if (m_Graph.m_Npt % 3 == 0)
			m_control_static_progress.SetWindowText(L"Внимание, идёт отрисовка . .");
		else if (m_Graph.m_Npt % 5 == 0)
			m_control_static_progress.SetWindowText(L"Внимание, идёт отрисовка . . .");//изменение текста при шкале прогресса
	m_Graph.m_Npt++;												//увеличиваем количество изображенных точек
	m_Graph.Invalidate();
	par.nCur++;
	CDialogEx::OnTimer(nIDEvent);
}//действия на каждый момент таймера

void CMFCApplication1Dlg::OnBnClickedButtonStart()
{
	CButton *pW = (CButton *)GetDlgItem(ID_BUTTON1);					//создаем переменную для работы с кнопкой Start
	if (pW)
	{
		if (pW->GetCheck())												//если кнопка нажата
		{
			StartMyTimer();												//установим таймер
			m_Graph.m_Npt = m_Calc.GetNumPoints();						//перенос количества точек в массиве в класс графика
		}
		else
		{
			StopMyTimer();												//остановит таймера
			m_Graph.m_Npt = 0;											//обнуление количества точек
		}
	}
}//действия при нажатии на кнопку анимации

void CMFCApplication1Dlg::OnBnClickedButtonUp()						//обработчик событий нажатия кнопки Up
{
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();	//наследника вызываем по указателю из родителя
	GraphParameters par = app->parameters;							//новый параметр, имеющий тип структуры GraphParameters
	par.yCenter--;													//смещаем центр системы координат по y вверх
	m_Calc.SetParams(par);											//устанавливаем новое положение системы координат
	m_Graph.Invalidate();											//обновляем поле графика

	if (m_control_live.GetCheck())
	{
		StopMyTimer();
		StartMyTimer();
	}
}//обработка кнопки сдвига вверх

void CMFCApplication1Dlg::OnBnClickedButtonDn()						//обработчик событий нажатия кнопки Dn
{
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();	//наследника вызываем по указателю из родителя
	GraphParameters par = app->parameters;							//новый параметр, имеющий тип структуры GraphParameters
	par.yCenter++;													//смещаем центр системы координат по y вниз
	m_Calc.SetParams(par);											//устанавливаем новое положение системы координат
	m_Graph.Invalidate();											//обновляем поле графика

	if (m_control_live.GetCheck())
	{
		StopMyTimer();
		StartMyTimer();
	}
}//обработка кнопки сдвига вниз

void CMFCApplication1Dlg::OnBnClickedButtonR()						//обработчик событий нажатия кнопки R
{
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();	//наследника вызываем по указателю из родителя
	GraphParameters par = app->parameters;							//новый параметр, имеющий тип структуры GraphParameters
	par.xCenter++;													//смещаем центр системы координат по x вправо
	m_Calc.SetParams(par);											//устанавливаем новое положение системы координат
	m_Graph.Invalidate();											//обновляем поле графика

	if (m_control_live.GetCheck())
	{
		StopMyTimer();
		StartMyTimer();
	}
}//обработка кнопки сдвига вправо

void CMFCApplication1Dlg::OnBnClickedButtonL()						//обработчик событий нажатия кнопки L
{
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();	//наследника вызываем по указателю из родителя
	GraphParameters par = app->parameters;							//новый параметр, имеющий тип структуры GraphParameters
	par.xCenter--;													//смещаем центр системы координат по x влево
	m_Calc.SetParams(par);											//устанавливаем новое положение системы координат
	m_Graph.Invalidate();											//обновляем поле графика

	if (m_control_live.GetCheck())
	{
		StopMyTimer();
		StartMyTimer();
	}
}//обработка кнопки сдвига влево

void CMFCApplication1Dlg::OnBnClickedButton7()
{
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();	//наследника вызываем по указателю из родителя
	GraphParameters par = app->parameters;							//новый параметр, имеющий тип структуры GraphParameters
	CRect rc;														//создаем объект для рисования графика
	m_Graph.GetClientRect(&rc);										//получаем прямоугольник поля рисования
	par.xCenter= rc.CenterPoint().x;								//центрируем систему по х
	par.yCenter= rc.CenterPoint().y;								//центрируем систему по y 
	m_Calc.SetParams(par);											//устанавливаем новое положение системы координат
	m_Graph.Invalidate();											//обновляем поле графика

	if (m_control_live.GetCheck())
	{
		StopMyTimer();
		StartMyTimer();
	}
}//обработка кнопки центрирования

void CMFCApplication1Dlg::OnBnClickedButtonSave()
{
	CWnd *pWn = GetDlgItem(IDC_MYGRAPH);
	if (!pWn)
		return;
	CWindowDC winDC(pWn);
	CRect rc;
	pWn->GetClientRect(&rc);
	CDC memDC;														//создание общего объекта контекста устройства
	memDC.CreateCompatibleDC(&winDC);								//определяем параметры устройства 
	CBitmap bitMap;													//создаем объект картинки, кторая будет загружена в memDC
	bitMap.CreateCompatibleBitmap(&winDC, rc.Width(), rc.Height());	
	HGDIOBJ pOld = memDC.SelectObject(&bitMap);						//картинку загружаем в memDC функцией SelectObject
	memDC.FillSolidRect(&rc, RGB(0, 255, 0));						//модификация параметра копирования в функции BitBlt
	memDC.BitBlt(0, 0, rc.Width(), rc.Height(), &winDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOld);

	static TCHAR szFilter[] = _T("BMP Файлы (*.bmp)|*.bmp|")	
		_T("PNG Файлы (*.png)|*.png|GIF Файлы (*.gif)|*.gif|")		//список возможных форматов сохранения
		_T("JPG Файлы (*.jpg)|*.jpg|All Файлы (*.*)|*.*||");
	CFileDialog dlg(FALSE, _T(".bmp"), NULL, 6UL, szFilter);		//вызов стандартного диалога сохранения файлов
	if (IDOK == dlg.DoModal())										//запускаем модальный диалог вызовом (запрет всех кнопкок и полей ввода приложения, пока файл не выбран) 
	{
		CImage image;												//создаем объект класса CImage (сохранение в разные форматы )
		image.Attach(HBITMAP(bitMap));								//прикрепляем к нему картинку из объекта CBitmap
		CString strFull = dlg.GetOFN().lpstrFile;					//путь к файлу, доставаемому из диалога сохранения файлов
		HRESULT hr;													//хранение расширенного кода результата вызываемой операции (S_OK – успешно)
		if (-1 != strFull.Find(_T(".png")))							//автоматический выбор формата по имени файла (расширение в имени файла определяет нужный GUID)
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

		if (FAILED(hr))												//если вызываемая операция не была выполнена успешно
		{
			CString strErr;
			strErr.Format(L" Не удалось сохранить файл : %s, %x ", (LPCTSTR)strFull, hr);	//выведем на экран сообщение о невозможности сохранения файла
			AfxMessageBox(strErr, MB_OK | MB_ICONERROR);			//программа должна сообщить о выполнении процесса с ошибкой оператору с помощью диалога AfxMessageBox
		}
	}
}//обработка кнопки сохранить


void CMFCApplication1Dlg::OnBnClickedCheck1()
{
	UpdateData();
	CButton* rW = (CButton*)GetDlgItem(IDC_CHECK1);//присваиваем данные о кнопке переменной
	if (rW)
	{
		if (rW->GetCheck())							//если кнопка нажата, то изменяем надпись и перерисовываем	 				
		{
			rW->SetWindowText(L"Со стиранием");
			if (m_control_live.GetCheck())
			{
				StopMyTimer();
				StartMyTimer();
			}
		}
		else										//если кнопка не нажата, то изменяем надпись и перерисовываем	
		{
			rW->SetWindowText(L"Без стирания");
			if (m_control_live.GetCheck())
			{
				StopMyTimer();
				StartMyTimer();
			}
		}
	}
}//обработка кнопки стирания

void CMFCApplication1Dlg::StopMyTimer()
{
	CButton* pW = (CButton*)GetDlgItem(ID_BUTTON1);
	pW->SetWindowText(_T("Старт"));
	pW->SetCheck(0);
	m_control_static_progress.SetWindowText(L"Чтобы начать анимацию, нажмите 'Старт'");
	KillTimer(MY_TIMER_ID);
}//функция остановки таймера

void CMFCApplication1Dlg::StartMyTimer()
{
	OnCbnSelchangeCombo2();											// обновляем значение переменной скорости
	CButton* pW = (CButton*)GetDlgItem(ID_BUTTON1);
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();
	pW->SetWindowText(_T("Стоп"));
	pW->SetCheck(1);
	m_control_static_progress.SetWindowText(L"Внимание, идёт отрисовка");
	GraphParameters par = app->parameters;							//новый параметр, имеющий тип структуры GraphParameters
	par.nCur = 0;
	par.dXRad = 0.;
	m_Calc.SetParams(par);											//переносим параметры функции
	SetTimer(MY_TIMER_ID, speed, NULL);								//запускаем таймер со скоростью speed
}//функция старта таймера


void CMFCApplication1Dlg::OnEnChangeEdit1()
{
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();	//наследника вызываем по указателю из родителя
	CString strI;
	CWnd* editText = GetDlgItem(IDC_EDIT1);							//создаем переменную для работы с полем ввода
	if (editText != nullptr)
		editText->GetWindowText(strI);								//получаем текст - значение, введенное пользователем
	double val = _wtof(strI);
		app->parameters.f = val;									//запишем в переменную структуры введенное значение угла поворота обегающей окружности

		if (m_control_live.GetCheck())
		{
			StopMyTimer();
			StartMyTimer();
		}
}

void CMFCApplication1Dlg::OnEnChangeEdit2()
{
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();	//наследника вызываем по указателю из родителя
	CString strI;
	CWnd* editText = GetDlgItem(IDC_EDIT2);							//создаем переменную для работы с полем ввода
	if (editText != nullptr)
		editText->GetWindowText(strI);								//получаем текст - значение, введенное пользователем
	double val = _wtof(strI);
	app->parameters.radius_outer = val;								//запишем в переменную структуры введенное значение радиуса внутренней окружности

	if (m_control_live.GetCheck())
	{
		StopMyTimer();
		StartMyTimer();
	}
}


void CMFCApplication1Dlg::OnEnChangeEdit3()
{
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();	//наследника вызываем по указателю из родителя
	CString strI;
	CWnd* editText = GetDlgItem(IDC_EDIT3);							//создаем переменную для работы с полем ввода
	if (editText != nullptr)
		editText->GetWindowText(strI);								//получаем текст - значение, введенное пользователем
	double val = _wtof(strI);
	app->parameters.radius_inner = val;								//запишем в переменную структуры введенное значение радиуса внешней окружности

	if (m_control_live.GetCheck())
	{
		StopMyTimer();
		StartMyTimer();
	}
}

void CMFCApplication1Dlg::OnCbnSelchangeCombo2()
{
	int m_sp = m_control_speed.GetCurSel();
	if (m_sp == 0) //если выбрана скорость х0,5
		speed = 80;//скорость медленнее
	else if (m_sp == 1)//если выбрана скорость х1
		speed = 40;//скорость обычная
	else if (m_sp == 2)//если выбрана скорость х5
		speed = 8; //скорость быстрее
	else speed = 40;//иначе скорость анимации по умолчанию
	if (m_control_live.GetCheck())
	{
		StopMyTimer();
		StartMyTimer();
	}
}
