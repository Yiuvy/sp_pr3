#include <windows.h>
#include <tchar.h>												 //�������������� ������������ ���� ��� ������ � �������������� ������ ������ (����� ����������� ����� ����� � ���������� ������)
#include "resource.h"

//------- Prototypes -------------------
LRESULT CALLBACK Pr2_WndProc(HWND, UINT, WPARAM, LPARAM);		 //������� ���������. ������� �������� ��� ������ ���� ����� ����� ������������� ������, ��������� � ������� ����� ������������ � ���� ����



//----- Global Variables ------------
LPCTSTR g_lpszDestroyMessage = TEXT("��������� ��������� WM_DESTROY, �� ����������� �������� � �������� ������ �����. ��������� ��������� � ����� � ����������� ���� ����������");
LPCTSTR g_lpszClassName = TEXT("sp_pr2_class");
LPCTSTR g_lpszAplicationTitle = TEXT("������� ���� ����������. ���������� ��������� �.�.");
HINSTANCE g_hInst = nullptr;//g-����������, h-���������� handler nullptr-��� � 64 � 32.


// -------��������� �������------
int APIENTRY _tWinMain
(HINSTANCE hInstance,											 /*����� ��������� ������ �������� - ���������, ������ �� ���� ����������*/
	HINSTANCE hPrevInstance,									 /*������ �� ���������. (������)������ 0.  �������� �� 16��������� wnd*/
	LPTSTR lpszCmdLine,											 /*��������� �� ��������� ������*/
	int nCmdShow)												 /*��������� ������������ ������� �� ��� �� �������� �������*/
{
	WNDCLASSEX wc;												 /*��������� �������� ������ ���� �� ��������� �������� ��������� ����������*/
	MSG msg;													 /*��������� ��� ���������*/
	HWND hWnd;													 /* ����������(�������������) ����*/
	g_hInst = hInstance;										 /*����� �������� � ���� ������ Pr2_WndProc*/
	memset(&wc, 0, sizeof(WNDCLASSEX));							 /*���������� ���������� ������ (�����, �������� �����, ������� ����� ������������, ������� ������ ��������� ����� ������) �������� ��� ���� ���� ���������*/
	wc.cbSize = sizeof(WNDCLASSEX);								 /*������ ���� ����� �� �����������(62/32)*/
	wc.lpszClassName = g_lpszClassName;							 /*��� ������*/
	wc.lpfnWndProc = Pr2_WndProc;								 /*������� ���������. � �������� �������*/
	wc.style = CS_VREDRAW | CS_HREDRAW;						     /*����� ����*/
	wc.hInstance = hInstance;									 /*������ �� �� �����, ��� ��������� ���������� ��� ����������*/
	//----�������---- ���� ���������
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)); /*(NULL - ������ ������ �� �������������, � ����� �� ������_hInstance.IDI-������������� ������ ��  ��������� ��������)*/
	wc.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
	wc.hbrBackground = CreateSolidBrush(RGB(219, 222, 199)); //��������� ����� �� �������� 5
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);										 /*������ �� ����*/ /*����� �����*/
	
	wc.cbClsExtra = 0;											 /*�� ���������� �������:*/ /*������� ������ ���.*/
	wc.cbWndExtra = 0;											 /*cb-������ � ������ */
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("������ ����������� ������ ����!"), /*��������� ���������, ����� �� ���� ��������*/
			TEXT("������"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	hWnd = CreateWindowEx(NULL,								      /*NULL - ���������� ��������� ����� ����.*/
		g_lpszClassName,										  /*��� ������ �� ������ �������� ���� ��������*/
		g_lpszAplicationTitle,									  /*����� � ��������� ����*/
		(WS_OVERLAPPED | WS_SYSMENU | WS_MAXIMIZEBOX),			  // ��� WS_MINIMIZEBOX	(������������� ������ � ����������� overlapepd)								  /*����� ����: �������������*/
		300,													  /*��������� ����*/
		200,													  /*������������ ������ �������� ����*/
		600,													  /*������ �� ���������*/
		400,													  /*������*/
		NULL,
		NULL,
		hInstance,												  /*�������� ���� � ����������*/
		NULL
	);
	if (!hWnd)
	{
		MessageBox(NULL, TEXT("���� �� �������!"),
			TEXT("������"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);									   /*���� ������� - ���������� ����. ���������� � �������, ������� ���������� ���� � ���.��� ������������� ����*/
	UpdateWindow(hWnd);											   /*���������� �������� ������� � ����*/
	////===============������ ����============
	//{
	//	HWND hWnd2 = CreateWindowEx(NULL,								      /*NULL - ���������� ��������� ����� ����.*/
	//		g_lpszClassName,										  /*��� ������ �� ������ �������� ���� ��������*/
	//		g_lpszAplicationTitle,									  /*����� � ��������� ����*/
	//		(WS_OVERLAPPED | WS_SYSMENU | WS_MAXIMIZEBOX),			  // ��� WS_MINIMIZEBOX	(������������� ������ � ����������� overlapepd)								  /*����� ����: �������������*/
	//		400,													  /*��������� ����*/
	//		250,													  /*������������ ������ �������� ����*/
	//		600,													  /*������ �� ���������*/
	//		400,													  /*������*/
	//		NULL,
	//		NULL,
	//		hInstance,												  /*�������� ���� � ����������*/
	//		NULL
	//	);
	//	if (!hWnd2)
	//	{
	//		MessageBox(NULL, TEXT("���� �� �������!"),
	//			TEXT("������"), MB_OK | MB_ICONERROR);
	//		return FALSE;
	//	}
	//	ShowWindow(hWnd2, nCmdShow);									   /*���� ������� - ���������� ����. ���������� � �������, ������� ���������� ���� � ���.��� ������������� ����*/
	//	UpdateWindow(hWnd2);
	//}

	////===============������ ����============

	while (GetMessage(&msg, NULL, 0, 0))						   /*������ ��������� �� ������� ���������*/
	{
		TranslateMessage(&msg);									   /*���������� ����� ����������� ������� �������, ����� ����������� ������� ������, ����� ��������� ����� ������ � ��� ����� ��������� ��� �������*/
		DispatchMessage(&msg);									   /*������� ������� ���������. ��� ������ �����*/
	}
	return msg.wParam;
}


// -----------������� ���������-----------

LRESULT CALLBACK Pr2_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int mId, wmEvent;
	HDC hdc;
	static HWND hButtonSave;
	static HWND hButtonAdd;
	static HWND hButtonExit;
	static HWND hEdit;
	static HWND hListBox;

#define IDC_BTN_SAVE	150					 //������������� �������� ����
#define IDC_BTN_ADD		151 
#define IDC_EDIT1		152
#define IDC_LISTBOX		153


	switch (msg)
	{
	case WM_CREATE:
	{

		if (!(hEdit = CreateWindowEx(0L,			//0L-��������� ������������ ����� ����
			L"Edit",								//L-���������, ��� ������
			L"��������",
			WS_CHILD | WS_BORDER | WS_VISIBLE,		//��������, � ������, �������
			20,										//���������� ������������ ���������� �������
			50,
			160,
			40,
			hWnd,									// ���������� ������������� ����
			(HMENU)(IDC_EDIT1),						//���������� ���� ������������
			g_hInst,								//����� �� ��������� ����������
			NULL)))
			return (-1);
		if (!(hListBox = CreateWindowEx(0L, L"ListBox", L"������", WS_CHILD | WS_BORDER | WS_VISIBLE, 200, 50, 160, 180, hWnd, (HMENU)(IDC_LISTBOX), g_hInst, NULL)))return (-1);
		if (!(hButtonSave = CreateWindowEx(0L, L"Button", L"� �����", WS_CHILD | WS_BORDER | WS_VISIBLE, 20, 240, 80, 24, hWnd, (HMENU)(IDC_BTN_SAVE), g_hInst, NULL)))return (-1);
		if (!(hButtonAdd = CreateWindowEx(0L, L"Button", L"� ������", WS_CHILD | WS_BORDER | WS_VISIBLE, 120, 240, 80, 24, hWnd, (HMENU)(IDC_BTN_ADD), g_hInst, NULL)))return (-1);
		if (!(hButtonExit = CreateWindowEx(0L, L"Button", L"�����", WS_CHILD | WS_BORDER | WS_VISIBLE, 220, 240, 80, 24, hWnd, (HMENU)(IDCANCEL), g_hInst, NULL)))return (-1);

	}
	return  0;


	case WM_COMMAND:
	{
		int wmID = LOWORD(wParam); /*������������� ��������� ��������*/
		wmEvent = HIWORD(wParam);
		static TCHAR pszTextBuff[500];

		switch (wmID)
		{
		case IDM_FILE_OPEN:
		{
			MessageBox(hWnd, TEXT("������� ������� ������� ����"), TEXT("O������ ����"), MB_OK);
		}; break;
		case IDM_FILE_CREATE:
		{
			MessageBox(hWnd, TEXT("������� ������� ������� ����"), TEXT("������� ����"), MB_OK);
		}; break;

		case IDM_HELP_ABOUT:
		{
			MessageBox(hWnd, TEXT("������� ������� ������"), TEXT("������"), MB_OK);
		}; break;

		case 	IDM_40013:
		{
			MessageBox(hWnd, TEXT("������� ������� � ���������"), TEXT("� ���������"), MB_OK);
		}; break;


		case IDCANCEL: //������ ������ "�����"
			DestroyWindow(hWnd); break;

		case IDC_BTN_SAVE:
		{

			int cch;
			cch = SendMessage(hEdit, WM_GETTEXT, (WPARAM)500, (LPARAM)pszTextBuff);	//hEdit-���������� ���� , WM_GETTEXT - �������, ��� ������� ��������. ������� �� ������ Lparam. (WPARAM)500 - ������ ������

			if (cch == 0) //���� ������� 0 �������, ��������� �� ������� ������, � ������ ���������� - ���������� �����
				MessageBox(hWnd, L"������� �����", L"������ Edit", MB_OK);
			else
			{
				TCHAR Buff1[500] = { 0 };											//����� - ��������� ������ ��� ����������� �������
				SYSTEMTIME st;														//��������� ��� ����������� ������� 
				GetLocalTime(&st);													//�������� ��� �����
				wsprintf(Buff1, TEXT("�����:%d � %d ��� %d ���\n"), st.wHour, st.wMinute, st.wSecond); //����� ������ �� �����
				lstrcat(Buff1, _TEXT("����� � ������: "));							//����������� �����
				lstrcat(Buff1, pszTextBuff);
				MessageBox(hWnd, Buff1, L"���������� ������", MB_OK);
			}
		} break;

		case IDC_BTN_ADD:
		{
			int ind;
			ind = SendMessage(hListBox, LB_ADDSTRING, (WPARAM)0, (LPARAM)pszTextBuff);//LB_ADDSTRING-��������� ������ � ������
			if (ind == LB_ERR) MessageBox(hWnd, TEXT("������ � ������"), TEXT(" "), MB_OK);

		}
		default:

			return(DefWindowProc(hWnd, msg, wParam, lParam));

		}
		break;

	}

	case WM_DESTROY:												// ���������� ������ ����������. ����������� �� �������������. ���� ����������� ��������������
	{
		//MessageBox(NULL, g_lpszDestroyMessage, TEXT("�����"), MB_OK);
		PostQuitMessage(5);
	}										// ������� WM_QUIT ����������
	break;
	default:														// ����� "����������� �� ���������"
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	} //����� switch
	return FALSE;// ��� ������ � "break"
}