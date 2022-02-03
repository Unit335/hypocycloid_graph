#include "stdafx.h"
#include "afxdialogex.h"
#include "MFCApplication1Dlg.h"

CHypocycloidFun::CHypocycloidFun()
{
	X = 0.;
	Y = 0.;
}

CHypocycloidFun::~CHypocycloidFun()
{
}

bool CHypocycloidFun::Calc(double f, double radius_outer, double radius_inner)	//функция расчета координат точек графика
{
	double k = radius_inner / radius_outer;									
	X = radius_outer*(k - 1) *(cos(f)+cos((k - 1) * f) / (k - 1));				//параметрические уравнения эпициклоиды
	Y = radius_outer*(k - 1) *(sin(f)-sin((k - 1) * f) / (k - 1));
	return true;
}

CHypocycloidCalc::CHypocycloidCalc()
{
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();				//наследника вызываем по указателю из родителя
	app->parameters.radius_inner = 1.;											//укажем начальные значения, необходимые для корректного построения графика
	app->parameters.radius_outer = 1.;
	app->parameters.f = 2. * M_PI;
	app->parameters.Scale = 10.;
	app->parameters.xMax = 2.* M_PI;
	app->parameters.nPoints = 720;
	app->parameters.nCur = 0;
	app->parameters.yCenter = 20;
	app->parameters.xCenter = 20;
	app->parameters.dXRad = 0.;
}

CHypocycloidCalc::~CHypocycloidCalc()
{
}

bool CHypocycloidCalc::Scale(CPoint & pt, double ScaleX, double ScaleY, double f, double radius_outer, double radius_inner)
{
	CHypocycloidFun fn;
	if (fn.Calc( f, radius_outer, radius_inner))
	{
		pt.x = (int)floor(ScaleX * fn.X);										//формулы для масштабирования координат на экране 
		pt.y = -(int)floor(ScaleY * fn.Y);
		return true;
	}
	return false;
}

bool CHypocycloidCalc::Shift(CPoint & pt)
{
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();				//наследника вызываем по указателю из родителя
	pt.Offset(app->parameters.xCenter, app->parameters.yCenter);				//установка положения сдвига центра системы координат
	return true;
}

bool CHypocycloidCalc::Calculate()
{
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();				//наследника вызываем по указателю из родителя
	for (size_t ni = 0; ni < app->parameters.nPoints; ni++)						 
	{
		CPoint pt;
		app->parameters.f += 0.017;												//в цикле при повороте обегающей окружности угол ее поворота изменяется на 1 радиан
		if (Scale(pt, app->parameters.Scale, app->parameters.Scale, app->parameters.f, app->parameters.radius_outer, app->parameters.radius_inner))
		{

			if (Shift(pt))
				m_vecPt.push_back(POINT(pt));									//в вектор m_vecPt запишем рассчитанные точки
		}
	}
	return m_vecPt.size() > 0;
}

bool CHypocycloidCalc::CalcContinuosly()
{
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();				//наследника вызываем по указателю из родителя
	CPoint pt;
	app->parameters.f += 0.017;												//в цикле при повороте обегающей окружности угол ее поворота изменяется на 1 радиан
	if (Scale(pt, app->parameters.Scale, app->parameters.Scale, app->parameters.f, app->parameters.radius_outer, app->parameters.radius_inner))
	{

		if (Shift(pt))
			m_vecPt.push_back(POINT(pt));									//в вектор m_vecPt запишем рассчитанные точки
	}
	return m_vecPt.size() > 0;
}

vector<POINT>* CHypocycloidCalc::GetPoints()								//функция получения точек графика
{
	return &m_vecPt;															//возвращает указатель на вектор с точками
}

bool CHypocycloidCalc::SetParams(GraphParameters & par)
{
	CMFCApplication1App* app = (CMFCApplication1App*)AfxGetApp();				//наследника вызываем по указателю из родителя
	CMFCApplication1Dlg* dlg = (CMFCApplication1Dlg*)AfxGetMainWnd();
	app->parameters = par;
	if (dlg->m_control_speed.GetCurSel() == 3) //если выбрана быстрейшая скорость, то вызываем функцию расчёта полной гипоциклоиды
	{
		if (app->parameters.nCur == 0)
			m_vecPt.clear();//предварительно очищаем вектор
		Calculate();
	}
	else //если скорость любая, кроме быстрейшей, то рассчитываем точки по таймеру
	if (app->parameters.nCur <= app->parameters.nPoints)
	{
		if (app->parameters.nCur == 0)
			m_vecPt.clear();															//предварительно очищаем вектор для записи в него точек
		CalcContinuosly();
	}															//вызываем функцию расчета точек графика по таймеру
	return true;
}

int CHypocycloidCalc::GetNumPoints()												//функция получения поличества точек
{
	return m_vecPt.size();;														//возвращает размер вектора с уже записанными точками
}