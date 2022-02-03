// MyGraph.cpp: ���� ����������
//


#include "stdafx.h"
#include "MFCApplication1Dlg.h"


// CMyGraph

IMPLEMENT_DYNAMIC(CMyGraph, CWnd)

CMyGraph::CMyGraph()											//����������� ������	
{
	m_Npt = 0;													//���������� ������������ �����
	m_colBack = RGB(240, 240, 240);								//� ������� RGB ��������� ������� �������� ��������� ����� ��������� �������� �� 0 �� 255 
}

CMyGraph::~CMyGraph()											//���������� ������
{
}

									
BEGIN_MESSAGE_MAP(CMyGraph, CWnd)
	ON_WM_PAINT()												//������� ��������� ���������� ���������� WM_PAINT
END_MESSAGE_MAP()



// ����������� ��������� CMyGraph

void CMyGraph::OnPaint()
{
	CPaintDC dc(this);											//device context for painting

	CRect rc;													//������ ���� CRect, ������� ��������� ������������� � ����������� ����
	GetClientRect(&rc);											//� ������� ��� ��������� �������������� ���� �������� ���������� ���������,��� ��� � ���� ������� ���������� ����
	CRgn rgn;
	rgn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);	//��������� �������� ��������� � ���� - �������� ������� �������� � ������������� ���� ������������ ������  
	dc.SelectClipRgn(&rgn);										//�������� ������ ��� ����������� �������
	CPoint pt;
	CPen pG(PS_SOLID, 3, RGB(0, 0, 0));						//������ �������� - ��� ��������� ����������� ������ �������� 3 ������� � ���������� ������  
	HGDIOBJ old = dc.SelectObject(pG);							//�������� ��������� ������ ��� ���������
	
	CMFCApplication1Dlg *pDlg = (CMFCApplication1Dlg *)AfxGetMainWnd();
	if (!pDlg)
		return;
	if (pDlg->m_control_live.GetCheck())//���� ������ ������
	{
		if (pDlg->m_control_erasing.GetCheck())
			dc.FillSolidRect(rc, m_colBack);							//������� �������� ������� ���� (�������������� rc) ��������� ������ m_colBack
		std::vector<POINT>* vec = pDlg->m_Calc.GetPoints();			//���������� ������ � m_vecPt
		if (vec->size())
		{
			std::vector<POINT>::iterator it = vec->begin();			//������� ������ (�������� ������� � �������), ��� ������������� �������� ��������� �� ������ ������� �������
			dc.MoveTo(*it);											//��������� �������� � ������ ������� 
			size_t nCur = 0;
			for (it++; it != vec->end(); it++)						//���� ��� ������������� �������� ����� 
			{
				dc.LineTo(*it);										//������ ������ (������� ���������� ����� �� �������� ��������� ��, �� �� ������� ��������� �����)
				if (nCur++ >= m_Npt)
					break;
			}
			if (m_Npt >= vec->size())								//���� ���������� ����������� ����� ��� ��������� �������� ������ �������, �������� ��������� �� ����
				AfxGetMainWnd()->SendMessage(WM_USER + 1, m_Npt, vec->size());
		}
	}
	else
		dc.FillSolidRect(rc, m_colBack);//����� ��������
	dc.SelectObject(old);										//�������� ��� ������, ������� ��� ������ � CDC ������������� ��� ��� ��������, ����� ������� ��������� �� ���������� ���������������� � ������
}
