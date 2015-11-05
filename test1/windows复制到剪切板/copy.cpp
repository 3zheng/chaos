
#include "copy.h"

void ToClipBoard(CString &str)
{

	//�����ַ��ͱ������������û����������
	HGLOBAL hClip;
	//����һ��HGLOBAL�����������ָ�������ڴ��
	HWND hWnd = AfxGetMainWnd()->GetSafeHwnd(); // ��ȡ��ȫ���ھ��
	if (OpenClipboard(hWnd))
	{
		EmptyClipboard();                            //���������������
		hClip = GlobalAlloc(GMEM_MOVEABLE, (str.GetLength() + 1)*sizeof(TCHAR));
		//�ڶ��Ϸ�����ƶ����ڴ�飬���򷵻�һ���ڴ���
		TCHAR* buff;                                 //����ָ���ַ��͵�ָ�����
		buff = (TCHAR*)GlobalLock(hClip);
		//�Է�����ڴ����м��������ڴ����ת����һ��ָ��,������Ӧ�����ü�������1
		_tcscpy(buff, str);
		//���û���������ݸ��Ƶ�ָ������У�ʵ���Ͼ��Ǹ��Ƶ�������ڴ����
		GlobalUnlock(hClip);
		//����д����ϣ����н����������������ü��������ּ�1
#ifdef UNICODE
		SetClipboardData(CF_UNICODETEXT, hClip);
#else
		SetClipboardData(CF_TEXT, hClip);
#endif

		//����������ݵ��ڴ�������������Դ������
		CloseClipboard();
		//�رռ����壬�ͷż�������Դ��ռ��Ȩ
	}
}
