// MultipoleProfileCalculator.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "MultipoleProfileCalculator.h"


// ���ǵ���������һ��ʾ��
MULTIPOLEPROFILECALCULATOR_API int nMultipoleProfileCalculator=0;

// ���ǵ���������һ��ʾ����
MULTIPOLEPROFILECALCULATOR_API int fnMultipoleProfileCalculator(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� MultipoleProfileCalculator.h
CMultipoleProfileCalculator::CMultipoleProfileCalculator()
{
	return;
}
