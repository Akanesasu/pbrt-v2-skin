// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� MULTIPOLEPROFILECALCULATOR_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// MULTIPOLEPROFILECALCULATOR_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef MULTIPOLEPROFILECALCULATOR_EXPORTS
#define MULTIPOLEPROFILECALCULATOR_API __declspec(dllexport)
#else
#define MULTIPOLEPROFILECALCULATOR_API __declspec(dllimport)
#endif

// �����Ǵ� MultipoleProfileCalculator.dll ������
class MULTIPOLEPROFILECALCULATOR_API CMultipoleProfileCalculator {
public:
	CMultipoleProfileCalculator(void);
	// TODO: �ڴ�������ķ�����
};

extern MULTIPOLEPROFILECALCULATOR_API int nMultipoleProfileCalculator;

MULTIPOLEPROFILECALCULATOR_API int fnMultipoleProfileCalculator(void);
