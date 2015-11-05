
#include "copy.h"

void ToClipBoard(CString &str)
{

	//定义字符型变量用来保存用户输入的数据
	HGLOBAL hClip;
	//定义一个HGLOBAL句柄变量用来指向分配的内存块
	HWND hWnd = AfxGetMainWnd()->GetSafeHwnd(); // 获取安全窗口句柄
	if (OpenClipboard(hWnd))
	{
		EmptyClipboard();                            //将剪贴板内容清空
		hClip = GlobalAlloc(GMEM_MOVEABLE, (str.GetLength() + 1)*sizeof(TCHAR));
		//在堆上分配可移动的内存块，程序返回一个内存句柄
		TCHAR* buff;                                 //定义指向字符型的指针变量
		buff = (TCHAR*)GlobalLock(hClip);
		//对分配的内存块进行加锁，将内存块句柄转化成一个指针,并将相应的引用计数器加1
		_tcscpy(buff, str);
		//将用户输入的数据复制到指针变量中，实际上就是复制到分配的内存块中
		GlobalUnlock(hClip);
		//数据写入完毕，进行解锁操作，并将引用计数器数字减1
#ifdef UNICODE
		SetClipboardData(CF_UNICODETEXT, hClip);
#else
		SetClipboardData(CF_TEXT, hClip);
#endif

		//将存放有数据的内存块放入剪贴板的资源管理中
		CloseClipboard();
		//关闭剪贴板，释放剪贴板资源的占用权
	}
}
