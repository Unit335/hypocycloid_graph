
// MFCApplication1.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#include "stdafx.h"
#include "stdio.h"
#pragma once
using namespace std;
#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"				// �������� �������
#include "afxwin.h"
#include "atlimage.h" //for CImage
#include <vector>
#define _USE_MATH_DEFINES
#include "math.h"
#include "GraphParameters.h"
#include "MyGraph.h"


// CMFCApplication1App:
// � ���������� ������� ������ ��. MFCApplication1.cpp
//

class CMFCApplication1App : public CWinApp
{
public:
	CMFCApplication1App();

// ���������������
	virtual BOOL InitInstance();
	GraphParameters parameters;		// ��������� �������� ������ ���������� �������

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication1App theApp;