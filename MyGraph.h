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
	afx_msg void OnPaint();	//������� - ���������� ��������� ��������� �������
public:
	size_t m_Npt;			//���������� �������� ���������� �����
	COLORREF m_colBack;		//����������� ���������� ����� �������
};

