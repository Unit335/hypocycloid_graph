
// MFCApplication1.h : главный файл заголовка для приложения PROJECT_NAME
//

#include "stdafx.h"
#include "stdio.h"
#pragma once
using namespace std;
#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"				// основные символы
#include "afxwin.h"
#include "atlimage.h" //for CImage
#include <vector>
#define _USE_MATH_DEFINES
#include "math.h"
#include "GraphParameters.h"
#include "MyGraph.h"


// CMFCApplication1App:
// О реализации данного класса см. MFCApplication1.cpp
//

class CMFCApplication1App : public CWinApp
{
public:
	CMFCApplication1App();

// Переопределение
	virtual BOOL InitInstance();
	GraphParameters parameters;		// структура хранения данных параметров функций

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication1App theApp;