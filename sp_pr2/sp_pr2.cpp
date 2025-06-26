#include <windows.h>
#include <tchar.h>												 //�������������� ������������ ���� ��� ������ � �������������� ������ ������ (����� ����������� ����� ����� � ���������� ������)
//------- Prototypes -------------------
LRESULT CALLBACK Pr2_WndProc(HWND, UINT, WPARAM, LPARAM);		 //������� ���������. ������� �������� ��� ������ ���� ����� ����� ������������� ������, ��������� � ������� ����� ������������ � ���� ����

//----- Global Variables ------------
LPCTSTR g_lpszDestroyMessage = TEXT("��������� ��������� WM_DESTROY, �� ����������� �������� � �������� ������ �����. ��������� ��������� � ����� � ����������� ���� ����������");
LPCTSTR g_lpszClassName = TEXT("sp_pr2_class");
LPCTSTR g_lpszAplicationTitle = TEXT("������� ���� ����������. ���������� ��������� �.�.");

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
	memset(&wc, 0, sizeof(WNDCLASSEX));							 /*���������� ���������� ������ (�����, �������� �����, ������� ����� ������������, ������� ������ ��������� ����� ������) �������� ��� ���� ���� ���������*/
	wc.cbSize = sizeof(WNDCLASSEX);								 /*������ ���� ����� �� �����������(62/32)*/
	wc.lpszClassName = g_lpszClassName;							 /*��� ������*/
	wc.lpfnWndProc = Pr2_WndProc;								 /*������� ���������. � �������� �������*/
	wc.style = CS_VREDRAW | CS_HREDRAW;						     /*����� ����*/
	wc.hInstance = hInstance;									 /*������ �� �� �����, ��� ��������� ���������� ��� ����������*/
	//----�������---- ���� ���������
	wc.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION)); /*(NULL - ������ ������ �� �������������, � ����� �� ������_hInstance.IDI-������������� ������ ��  ��������� ��������)*/
	wc.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
	wc.hbrBackground = CreateSolidBrush(RGB(0, 127, 0)); //��������� ����� �� �������� 5
	wc.lpszMenuName = NULL;										 /*������ �� ����*/
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
		WS_OVERLAPPEDWINDOW,									  /*����� ����: �������������*/
		0,														  /*��������� ����*/
		0,													      /*������������ ������ �������� ����*/
		CW_USEDEFAULT,											  /*������ �� ���������*/
		CW_USEDEFAULT,											  /*������*/
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
	while (GetMessage(&msg, NULL, 0, 0))						   /*������ ��������� �� ������� ���������*/
	{
		TranslateMessage(&msg);									   /*���������� ����� ����������� ������� �������, ����� ����������� ������� ������, ����� ��������� ����� ������ � ��� ����� ��������� ��� �������*/
		DispatchMessage(&msg);									   /*������� ������� ���������. ��� ������ �����*/
	}
	return msg.wParam; /**/
}


// -----------������� ���������-----------

LRESULT CALLBACK Pr2_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	case WM_CREATE:
	{
		MessageBox(hWnd, TEXT("����������� ��������� WM_CREATE"), TEXT("����������"), MB_OK | MB_ICONINFORMATION);
		return 0; // �������� �������� ����
		//return -1;
	}
	break;

	case WM_LBUTTONDOWN:
	{
		LPCTSTR mesText = TEXT("��������� ��������� WM_LBUTTONDOWN, ������� ���������� � ���� ��� ������ ����� ������ ����"); /*LPCTSTR-��������� �� ������. ��������������(��� ����������)*/
		HDC hDc; /*���������� ��� ��������� �����*/
		hDc = GetDC(hWnd);
		/*��������� � �������� �����*/
		TextOut(hDc, 50, 200, mesText, lstrlen(mesText));

		/*��������� � ����� �������*/
	  // �������� ���������� �����
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		TextOut(hDc, x, y, mesText, lstrlen(mesText));

		ReleaseDC(hWnd, hDc);
		return 0;
	}
	break;


	/*�������� TextOut �� ����� � �������������� ������� DrawText*/
/*	case WM_LBUTTONDOWN:
	{
		LPCTSTR mesText = TEXT("��������� ��������� WM_LBUTTONDOWN");
		HDC hDc = GetDC(hWnd);
		// ���������� ������� ��� ������ (��������, 200x50 ��������)
		RECT rect;
		rect.left = 50;
		rect.top = 200;
		rect.right = rect.left + 300;
		rect.bottom = rect.top + 50;

		// ���������� DrawText ��� ������ ������ ������ �������
		DrawText(hDc, mesText, lstrlen(mesText), &rect, DT_LEFT | DT_TOP | DT_WORDBREAK);
		
		// �������� ���������� �����
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		// ��������� �� �� ������� (��� ������) �� ����������� �����
		RECT clickRect;
		clickRect.left = x;
		clickRect.top = y;
		clickRect.right = x + 300;
		clickRect.bottom = y + 50;

		DrawText(hDc, mesText, lstrlen(mesText), &clickRect, DT_LEFT | DT_TOP | DT_WORDBREAK);

		ReleaseDC(hWnd, hDc);
	}
	break;*/

	case WM_PAINT:													// ����� ��� ���������� ���� (��������� � ������ ���������������� ��������)
		//����� ��������� ���� �� ����� ����� ���������, ��������
	{
		HDC hDC;
		PAINTSTRUCT ps;
		LPCTSTR mesText = TEXT("��������� ��������� WM_PAINT. ��� ���������� ���� �������� ����� ����, ��� ��� ���� ������� ������ ����� � ����� �������.");
		hDC = BeginPaint(hWnd, &ps);							    // ��������� ��������� ��� ���������� ���� (����������� ���������� ��������� ����) ������ � wm_Paint
		TextOut(hDC, 20, 100, mesText, lstrlen(mesText));			// ����� � ��������
		EndPaint(hWnd, &ps);
	}							// ���������� ���������� ����
	break;
	case WM_DESTROY:												// ���������� ������ ����������. ����������� �� �������������. ���� ����������� ��������������
	{
		MessageBox(NULL, g_lpszDestroyMessage, TEXT("�����"), MB_OK);
		//PostQuitMessage(5);
	}										// ������� WM_QUIT ����������
	break;
	default:														// ����� "����������� �� ���������"
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return FALSE;// ��� ������ � "break"
}