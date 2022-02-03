#pragma once

struct	GraphParameters				//��������� �������� ���������� �������, �������� ���������������, ���������� �����, ������ ����������� �����, ��������� ���� ���������� � ������������� �������
{
public:
	double radius_inner;				//������ ����������(���������) ����������
	double radius_outer;				//������ �������(���������) ����������
	double f;							//���� �������� ��������� ����������
	double Scale;						//��������� ������� - ��� ������ � ���� �������
	double xMax;						//������������ ������ �������� x
	size_t nPoints;						//���������� ����� � �������
	size_t nCur;						//����� ����������� �����
	int yCenter;						//����� ������� �� ���������� y
	int xCenter;						//����� ������� �� ���������� x
	double dXRad;						//��������� ���� �������� �� �������
};

class CHypocycloidFun : public CWinThread					//����� � ��������� �������� Calc, � ������� ����� ����������� ������ ����� �������
{
public:
	CHypocycloidFun();				//����������� ������
	~CHypocycloidFun();				//���������� ������
public:
	double X;						//��������� ���������� ��� ������� ��������� ����� �� X
	double Y;						//��������� ���������� ��� ������� ��������� ����� �� Y
public:
	bool Calc(double f, double radius_outer, double radius_inner);	//������� ������� ����� � ������������ X,Y.
																	//� �� ���������� �������� �������� ��������� � ��������� �����������, � ����� ���� �������� ��������� ����������
};

class CHypocycloidCalc : public CWinThread					//����� �������� ��������� ������� �������, ����� ��� ���������������, �����.
										//����� � ��� ������������ ���������� ������� ����� ������� � ����������� ���������� �� ���������� � ���� ����� ������ ����������� ��������� 
{
public:
	CHypocycloidCalc();					//����������� ������
	~CHypocycloidCalc();				//���������� ������
protected:
	bool Scale(CPoint & pt, double ScaleX, double ScaleY, double f, double radius_outer, double radius_inner); //������� ������� ��������� ��������� ����� ������� ��� ���������������
	bool Shift(CPoint & pt);			//������� ������� ��������� ��������� ����� ������� ��� �� ������
public:
	bool Calculate();					//������� � ��������� ���������� ��� ���������� ������� �� �������
	bool CalcContinuosly();				//������� � ��������� ���������� ��� ������������� ���������� �������
	vector<POINT> *GetPoints();			//������� �������� ������� ��������� ����� � ����� ��������� �������
	bool SetParams(GraphParameters &par);//������� �������� ������ � ������� �� ���������� � ����� ��������
	int GetNumPoints();					//������� ���������� ������ ������� � ������������ ����� �������
	vector<POINT> m_vecPt;				//������ ��������� �����
};