// ddz.h : ddz DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CddzApp
// �йش���ʵ�ֵ���Ϣ������� ddz.cpp
//

class CddzApp : public CWinApp
{
public:
	CddzApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
