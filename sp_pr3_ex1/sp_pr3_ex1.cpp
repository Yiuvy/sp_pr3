#include <windows.h>
#include <tchar.h>												 //Дополнительный заголовочный файл для работы с универсальными типами данных (Чтобы формировать макро текст и символьные строки)
#include "resource.h"

//------- Prototypes -------------------
LRESULT CALLBACK Pr2_WndProc(HWND, UINT, WPARAM, LPARAM);		 //оконная процедура. Система вызывает для нашего окна когда будут формироваться событи, сообщения и которые будут отправляться в наше окно



//----- Global Variables ------------
LPCTSTR g_lpszDestroyMessage = TEXT("Поступило сообщение WM_DESTROY, из обработчика которого и выполнен данный вывод. Сообщение поступило в связи с разрушением окна приложения");
LPCTSTR g_lpszClassName = TEXT("sp_pr2_class");
LPCTSTR g_lpszAplicationTitle = TEXT("Главное окно приложения. Програмист Макаревич В.В.");
HINSTANCE g_hInst = nullptr;//g-глобальная, h-дескриптор handler nullptr-для и 64 и 32.


// -------Стартовая функция------
int APIENTRY _tWinMain
(HINSTANCE hInstance,											 /*хэндл косвенная ссылка наобъект - Экземпляр, ссылка на само приложение*/
	HINSTANCE hPrevInstance,									 /*Ссылка на экземпляр. (модуль)Всегда 0.  рудимент от 16разрадной wnd*/
	LPTSTR lpszCmdLine,											 /*указатель на командную строку*/
	int nCmdShow)												 /*Пожелание родительский процесс на вид на дочерний процесс*/
{
	WNDCLASSEX wc;												 /*Структура описания класса окна на основании которого создаются экземпляры*/
	MSG msg;													 /*Структура для сообщения*/
	HWND hWnd;													 /* дескриптор(Идентификатор) окна*/
	g_hInst = hInstance;										 /*Чтобы передать в нашу функцю Pr2_WndProc*/
	memset(&wc, 0, sizeof(WNDCLASSEX));							 /*Установить содержимое памяти (адрес, значение байта, который будет заполнителем, сколько байтов заполнить этими нулями) Обнулили все поля этой стркутуры*/
	wc.cbSize = sizeof(WNDCLASSEX);								 /*Размер типа завит от разрядности(62/32)*/
	wc.lpszClassName = g_lpszClassName;							 /*Имя класса*/
	wc.lpfnWndProc = Pr2_WndProc;								 /*Оконная процедура. её вызывает система*/
	wc.style = CS_VREDRAW | CS_HREDRAW;						     /*Стили окна*/
	wc.hInstance = hInstance;									 /*ссылка на то место, где находится програмный код приложения*/
	//----Ресурсы---- Надо загружать
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)); /*(NULL - ресурс берётся из родительского, а чтобы из нашего_hInstance.IDI-идентификатор значка из  системных ресурсов)*/
	wc.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
	wc.hbrBackground = CreateSolidBrush(RGB(219, 222, 199)); //изменение цвета по варианту 5
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);										 /*ссылка на меню*/ /*Через класс*/
	
	wc.cbClsExtra = 0;											 /*По Венгерской нотации:*/ /*Область памяти доп.*/
	wc.cbWndExtra = 0;											 /*cb-размер в байтах */
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("Ошибка регистрации класса окна!"), /*Сообщение модпльное, нужно на него ответить*/
			TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	hWnd = CreateWindowEx(NULL,								      /*NULL - расширеные параметры стиля окна.*/
		g_lpszClassName,										  /*Имя класса на основе которого окно создаётся*/
		g_lpszAplicationTitle,									  /*Текст в заголовке окна*/
		(WS_OVERLAPPED | WS_SYSMENU | WS_MAXIMIZEBOX),			  // без WS_MINIMIZEBOX	(Автоматически входит в определение overlapepd)								  /*Стили окна: Перекрываемое*/
		300,													  /*Положение окна*/
		200,													  /*Относительно левого верхнего угла*/
		600,													  /*ширина по умолчанию*/
		400,													  /*высота*/
		NULL,
		NULL,
		hInstance,												  /*привязка окна к экземпляру*/
		NULL
	);
	if (!hWnd)
	{
		MessageBox(NULL, TEXT("Окно не создано!"),
			TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);									   /*Если успешно - отобразить окно. обращаемся к системе, передаём дескриптер окна и вид.Вид родительского окна*/
	UpdateWindow(hWnd);											   /*Требование обновить рисунок в окне*/
	////===============второе окно============
	//{
	//	HWND hWnd2 = CreateWindowEx(NULL,								      /*NULL - расширеные параметры стиля окна.*/
	//		g_lpszClassName,										  /*Имя класса на основе которого окно создаётся*/
	//		g_lpszAplicationTitle,									  /*Текст в заголовке окна*/
	//		(WS_OVERLAPPED | WS_SYSMENU | WS_MAXIMIZEBOX),			  // без WS_MINIMIZEBOX	(Автоматически входит в определение overlapepd)								  /*Стили окна: Перекрываемое*/
	//		400,													  /*Положение окна*/
	//		250,													  /*Относительно левого верхнего угла*/
	//		600,													  /*ширина по умолчанию*/
	//		400,													  /*высота*/
	//		NULL,
	//		NULL,
	//		hInstance,												  /*привязка окна к экземпляру*/
	//		NULL
	//	);
	//	if (!hWnd2)
	//	{
	//		MessageBox(NULL, TEXT("Окно не создано!"),
	//			TEXT("Ошибка"), MB_OK | MB_ICONERROR);
	//		return FALSE;
	//	}
	//	ShowWindow(hWnd2, nCmdShow);									   /*Если успешно - отобразить окно. обращаемся к системе, передаём дескриптер окна и вид.Вид родительского окна*/
	//	UpdateWindow(hWnd2);
	//}

	////===============второе окно============

	while (GetMessage(&msg, NULL, 0, 0))						   /*Читать сообщение из очереди сообщений*/
	{
		TranslateMessage(&msg);									   /*Определяет какая установлена кодовая таблица, какая виртуальная клавиша нажата, какое состояние горяч клавиш и тем самым формирует код символа*/
		DispatchMessage(&msg);									   /*Вызвать оконную процедуру. Сам узнает какую*/
	}
	return msg.wParam;
}


// -----------Оконная процедура-----------

LRESULT CALLBACK Pr2_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int mId, wmEvent;
	HDC hdc;
	static HWND hButtonSave;
	static HWND hButtonAdd;
	static HWND hButtonExit;
	static HWND hEdit;
	static HWND hListBox;

#define IDC_BTN_SAVE	150					 //Идентификатор дочерних окон
#define IDC_BTN_ADD		151 
#define IDC_EDIT1		152
#define IDC_LISTBOX		153


	switch (msg)
	{
	case WM_CREATE:
	{

		if (!(hEdit = CreateWindowEx(0L,			//0L-Константа расширенного стиля окна
			L"Edit",								//L-указатель, что юникод
			L"Редактор",
			WS_CHILD | WS_BORDER | WS_VISIBLE,		//дочерний, с рамкой, видимый
			20,										//координаты относительно клиентской области
			50,
			160,
			40,
			hWnd,									// дескриптор родительского окна
			(HMENU)(IDC_EDIT1),						//Дексриптор меню идентифкатор
			g_hInst,								//ссыла на экземпляр приложения
			NULL)))
			return (-1);
		if (!(hListBox = CreateWindowEx(0L, L"ListBox", L"Список", WS_CHILD | WS_BORDER | WS_VISIBLE, 200, 50, 160, 180, hWnd, (HMENU)(IDC_LISTBOX), g_hInst, NULL)))return (-1);
		if (!(hButtonSave = CreateWindowEx(0L, L"Button", L"В буфер", WS_CHILD | WS_BORDER | WS_VISIBLE, 20, 240, 80, 24, hWnd, (HMENU)(IDC_BTN_SAVE), g_hInst, NULL)))return (-1);
		if (!(hButtonAdd = CreateWindowEx(0L, L"Button", L"В список", WS_CHILD | WS_BORDER | WS_VISIBLE, 120, 240, 80, 24, hWnd, (HMENU)(IDC_BTN_ADD), g_hInst, NULL)))return (-1);
		if (!(hButtonExit = CreateWindowEx(0L, L"Button", L"Выход", WS_CHILD | WS_BORDER | WS_VISIBLE, 220, 240, 80, 24, hWnd, (HMENU)(IDCANCEL), g_hInst, NULL)))return (-1);

	}
	return  0;


	case WM_COMMAND:
	{
		int wmID = LOWORD(wParam); /*Идентификатор дочернего элемента*/
		wmEvent = HIWORD(wParam);
		static TCHAR pszTextBuff[500];

		switch (wmID)
		{
		case IDM_FILE_OPEN:
		{
			MessageBox(hWnd, TEXT("Выбрана команда открыть файл"), TEXT("Oткрыть файл"), MB_OK);
		}; break;
		case IDM_FILE_CREATE:
		{
			MessageBox(hWnd, TEXT("Выбрана команда создать файл"), TEXT("Создать файл"), MB_OK);
		}; break;

		case IDM_HELP_ABOUT:
		{
			MessageBox(hWnd, TEXT("Выбрана команда Помощи"), TEXT("Помощь"), MB_OK);
		}; break;

		case 	IDM_40013:
		{
			MessageBox(hWnd, TEXT("Выбрана команда О программе"), TEXT("О программе"), MB_OK);
		}; break;


		case IDCANCEL: //нажата кнопка "выход"
			DestroyWindow(hWnd); break;

		case IDC_BTN_SAVE:
		{

			int cch;
			cch = SendMessage(hEdit, WM_GETTEXT, (WPARAM)500, (LPARAM)pszTextBuff);	//hEdit-дескриптор окна , WM_GETTEXT - событие, что сделает редкатор. Вернуть по адресу Lparam. (WPARAM)500 - размер буфера

			if (cch == 0) //Если вернуло 0 символо, проверяем на наличие строки, в случае отсутствия - уведомляем юзера
				MessageBox(hWnd, L"Введите текст", L"Читаем Edit", MB_OK);
			else
			{
				TCHAR Buff1[500] = { 0 };											//буфер - формируем строку для отображения времени
				SYSTEMTIME st;														//структура для отображения времени 
				GetLocalTime(&st);													//получеам это время
				wsprintf(Buff1, TEXT("Время:%d ч %d мин %d сек\n"), st.wHour, st.wMinute, st.wSecond); //вывод текста на экран
				lstrcat(Buff1, _TEXT("Текст в памяти: "));							//объединение строк
				lstrcat(Buff1, pszTextBuff);
				MessageBox(hWnd, Buff1, L"Содержимое буфера", MB_OK);
			}
		} break;

		case IDC_BTN_ADD:
		{
			int ind;
			ind = SendMessage(hListBox, LB_ADDSTRING, (WPARAM)0, (LPARAM)pszTextBuff);//LB_ADDSTRING-добавляет строку в список
			if (ind == LB_ERR) MessageBox(hWnd, TEXT("Ошибка в списке"), TEXT(" "), MB_OK);

		}
		default:

			return(DefWindowProc(hWnd, msg, wParam, lParam));

		}
		break;

	}

	case WM_DESTROY:												// Завершение работы приложения. Поумолчанию не обрабатывется. Надо прописывать самостоятельно
	{
		//MessageBox(NULL, g_lpszDestroyMessage, TEXT("Выход"), MB_OK);
		PostQuitMessage(5);
	}										// Посылка WM_QUIT приложению
	break;
	default:														// Вызов "Обработчика по умолчанию"
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	} //конец switch
	return FALSE;// Для ветвей с "break"
}