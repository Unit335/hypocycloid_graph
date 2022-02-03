
// MFCApplication1Dlg.h : файл заголовка
//

#pragma once
#include "MFCApplication1.h"


// диалоговое окно CMFCApplication1Dlg
class CMFCApplication1Dlg : public CDialogEx
{
// Создание
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;// переменная класса хранения иконки программы

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();// переменная инициализации диалогового окна
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam),
				OnPaint();// функция отрисовки окна
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CHypocycloidCalc m_Calc;// объявление переменной класса расчётов координат для движения данных в эту подпрограмму
	CMyGraph m_Graph;// переменная класса отрисовки графика функции
	afx_msg void OnEnChangeEdit1(),
		OnEnChangeEdit2(),
		OnEnChangeEdit3(), // функции для обработки ввода текста
		OnTimer(UINT_PTR nIDEvent), // функция настройки таймера
		OnBnClickedOk(),  // функция настройки действия нажатия на кнопку ОК
		OnBnClickedButtonUp(), 
		OnBnClickedButtonDn(),
		OnBnClickedButtonR(),
		OnBnClickedButtonL(),
		OnBnClickedButton7(),//функции обработки кнопок сдвига
		OnBnClickedButtonSave(), //функция обработки кнопки сохранить
		OnBnClickedButtonStart(),//функция обработки кнопки старт/стоп
		OnBnClickedCheck1(),//функция обработки кнопки стирания
		OnCbnSelchangeCombo2();//функция обработки листбокса
	void StopMyTimer(),// собственная функция остановки таймера
		StartMyTimer();// собственная функция запуска таймера
	CProgressCtrl m_prCtrl;			//переменная для работы с элементом управления Progress Control
	CEdit Input_field;				//поле ввода
	CButton m_control_erasing,
			m_control_live;			// переменные для настройки кнопок анимации и стирания графиков
	BOOL m_boolean_erasing; // переменныя класса BOOL кнопки стирания графика
	CStatic m_control_static_progress;//переменная для настройки текста при шкале прогресса
	CComboBox m_control_speed;//переменная для настройки листбокса
	UINT speed = 40;//переменная для выбора скорости анимации
	CString m_edit_def_r_outer,
		m_edit_def_r_inner;
	double m_edit_def_f;//переменные хранения данных полей ввода
};
