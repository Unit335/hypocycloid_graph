#pragma once


// CMyGraph

class CMyGraph : public CStatic
{
	DECLARE_DYNAMIC(CMyGraph)

public:
	CMyGraph();
	virtual ~CMyGraph();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();	//функция - обработчик сообщений рисования графика
public:
	size_t m_Npt;			//переменная подсчёта количества точек
	COLORREF m_colBack;		//определение переменной цвета заливки
};

