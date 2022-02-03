// MyGraph.cpp: файл реализации
//


#include "stdafx.h"
#include "MFCApplication1Dlg.h"


// CMyGraph

IMPLEMENT_DYNAMIC(CMyGraph, CWnd)

CMyGraph::CMyGraph()											//конструктор класса	
{
	m_Npt = 0;													//количество изображенных точек
	m_colBack = RGB(240, 240, 240);								//в функции RGB параметры €ркости цветовых компонент могут принимать значени€ от 0 до 255 
}

CMyGraph::~CMyGraph()											//деструктор класса
{
}

									
BEGIN_MESSAGE_MAP(CMyGraph, CWnd)
	ON_WM_PAINT()												//функци€ рисовани€ вызываетс€ сообщением WM_PAINT
END_MESSAGE_MAP()



// обработчики сообщений CMyGraph

void CMyGraph::OnPaint()
{
	CPaintDC dc(this);											//device context for painting

	CRect rc;													//объект типа CRect, который описывает пр€моугольник в координатах окна
	GetClientRect(&rc);											//в функцию дл€ получени€ пр€моугольника окна передаем измен€емый указатель,так как в него пишутс€ координаты окна
	CRgn rgn;
	rgn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);	//установка пределов рисовани€ в окне - выбираем область размером с пр€моугольник окна графического вывода  
	dc.SelectClipRgn(&rgn);										//выбираем объект дл€ ограничени€ области
	CPoint pt;
	CPen pG(PS_SOLID, 3, RGB(0, 0, 0));						//объект карандаш - дл€ рисовани€ непрерывной линией толщиной 3 пиксел€ и фиолетовым цветом  
	HGDIOBJ old = dc.SelectObject(pG);							//выбираем созданный объект дл€ рисовани€
	
	CMFCApplication1Dlg *pDlg = (CMFCApplication1Dlg *)AfxGetMainWnd();
	if (!pDlg)
		return;
	if (pDlg->m_control_live.GetCheck())//если кнопка нажата
	{
		if (pDlg->m_control_erasing.GetCheck())
			dc.FillSolidRect(rc, m_colBack);							//функци€ выполнит заливку фона (пр€моугольника rc) указанным цветом m_colBack
		std::vector<POINT>* vec = pDlg->m_Calc.GetPoints();			//записываем данные о m_vecPt
		if (vec->size())
		{
			std::vector<POINT>::iterator it = vec->begin();			//создаем объект (итератор массива Ц вектора), ему присваиваетс€ значение указател€ на первый элемент массива
			dc.MoveTo(*it);											//переносим карандаш в начало графика 
			size_t nCur = 0;
			for (it++; it != vec->end(); it++)						//цикл дл€ осуществлени€ перебора точек 
			{
				dc.LineTo(*it);										//рисуем график (функци€ изображает линию от текущего положени€ до, но не включа€ указанную точку)
				if (nCur++ >= m_Npt)
					break;
			}
			if (m_Npt >= vec->size())								//если количество разрешенных точек дл€ рисовани€ превысит размер вектора, отправим сообщение об этом
				AfxGetMainWnd()->SendMessage(WM_USER + 1, m_Npt, vec->size());
		}
	}
	else
		dc.FillSolidRect(rc, m_colBack);//иначе заливаем
	dc.SelectObject(old);										//выбираем тот объект, который был выбран в CDC первоначально при его создании, чтобы объекты рисовани€ не оставались неосвобожденными в пам€ти
}
