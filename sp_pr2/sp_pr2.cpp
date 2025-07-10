#include <windows.h>
#include <tchar.h>												 //Дополнительный заголовочный файл для работы с универсальными типами данных (Чтобы формировать макро текст и символьные строки)
//------- Prototypes -------------------
LRESULT CALLBACK Pr2_WndProc(HWND, UINT, WPARAM, LPARAM);		 //оконная процедура. Система вызывает для нашего окна когда будут формироваться событи, сообщения и которые будут отправляться в наше окно

//----- Global Variables ------------
LPCTSTR g_lpszDestroyMessage = TEXT("Поступило сообщение WM_DESTROY, из обработчика которого и выполнен данный вывод. Сообщение поступило в связи с разрушением окна приложения");
LPCTSTR g_lpszClassName = TEXT("sp_pr2_class");
LPCTSTR g_lpszAplicationTitle = TEXT("Главное окно приложения. Програмист Макаревич В.В.");

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
	memset(&wc, 0, sizeof(WNDCLASSEX));							 /*Установить содержимое памяти (адрес, значение байта, который будет заполнителем, сколько байтов заполнить этими нулями) Обнулили все поля этой стркутуры*/
	wc.cbSize = sizeof(WNDCLASSEX);								 /*Размер типа завит от разрядности(62/32)*/
	wc.lpszClassName = g_lpszClassName;							 /*Имя класса*/
	wc.lpfnWndProc = Pr2_WndProc;								 /*Оконная процедура. её вызывает система*/
	wc.style = CS_VREDRAW | CS_HREDRAW;						     /*Стили окна*/
	wc.hInstance = hInstance;									 /*ссылка на то место, где находится програмный код приложения*/
	//----Ресурсы---- Надо загружать
	wc.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION)); /*(NULL - ресурс берётся из родительского, а чтобы из нашего_hInstance.IDI-идентификатор значка из  системных ресурсов)*/
	wc.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
	wc.hbrBackground = CreateSolidBrush(RGB(0, 127, 0)); //изменение цвета по варианту 5
	wc.lpszMenuName = NULL;										 /*ссылка на меню*/
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
		WS_OVERLAPPEDWINDOW,									  /*Стили окна: Перекрываемое*/
		0,														  /*Положение окна*/
		0,													      /*Относительно левого верхнего угла*/
		CW_USEDEFAULT,											  /*ширина по умолчанию*/
		CW_USEDEFAULT,											  /*высота*/
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
	while (GetMessage(&msg, NULL, 0, 0))						   /*Читать сообщение из очереди сообщений*/
	{
		TranslateMessage(&msg);									   /*Определяет какая установлена кодовая таблица, какая виртуальная клавиша нажата, какое состояние горяч клавиш и тем самым формирует код символа*/
		DispatchMessage(&msg);									   /*Вызвать оконную процедуру. Сам узнает какую*/
	}
	return msg.wParam; /**/
}


// -----------Оконная процедура-----------

LRESULT CALLBACK Pr2_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	case WM_CREATE:
	{
		MessageBox(hWnd, TEXT("Выполняется обработка WM_CREATE"), TEXT("Информация"), MB_OK | MB_ICONINFORMATION);
		return 0; // Успешное создание окна
		//return -1;
	}
	break;

	case WM_LBUTTONDOWN:
	{
		LPCTSTR mesText = TEXT("Обработка сообщения WM_LBUTTONDOWN, которое посылается в окно при щелчке левой кнопки мыши"); /*LPCTSTR-указатель на строку. Инициализируем(При объявлении)*/
		HDC hDc; /*Переменная для контекста вывод*/
		hDc = GetDC(hWnd);
		/*Отрисовка в заданном месте*/
		TextOut(hDc, 50, 200, mesText, lstrlen(mesText));

		/*Отрисовка в месте нажатия*/
	  // Получаем координаты клика
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		TextOut(hDc, x, y, mesText, lstrlen(mesText));

		ReleaseDC(hWnd, hDc);
		return 0;
	}
	break;


	/*Замените TextOut на вывод с использованием функции DrawText*/
/*	case WM_LBUTTONDOWN:
	{
		LPCTSTR mesText = TEXT("Обработка сообщения WM_LBUTTONDOWN");
		HDC hDc = GetDC(hWnd);
		// Определяем область для текста (например, 200x50 пикселей)
		RECT rect;
		rect.left = 50;
		rect.top = 200;
		rect.right = rect.left + 300;
		rect.bottom = rect.top + 50;

		// Используем DrawText для вывода текста внутри области
		DrawText(hDc, mesText, lstrlen(mesText), &rect, DT_LEFT | DT_TOP | DT_WORDBREAK);
		
		// Получаем координаты клика
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		// Обновляем ту же область (или другую) по координатам клика
		RECT clickRect;
		clickRect.left = x;
		clickRect.top = y;
		clickRect.right = x + 300;
		clickRect.bottom = y + 50;

		DrawText(hDc, mesText, lstrlen(mesText), &clickRect, DT_LEFT | DT_TOP | DT_WORDBREAK);

		ReleaseDC(hWnd, hDc);
	}
	break;*/

	case WM_PAINT:													// Вывод при обновлении окна (Сохраняет в список недействительных областей)
		//Нужна отрисовка окна по новой после прикрытия, закрытия
	{
		HDC hDC;
		PAINTSTRUCT ps;
		LPCTSTR mesText = TEXT("Обработка сообщения WM_PAINT. Это соообщение окно получает после того, как оно было закрыто другим окном и затем открыто.");
		hDC = BeginPaint(hWnd, &ps);							    // Получение контекста для обновления окна (Виртуальное устройство отрисовки окна) только в wm_Paint
		TextOut(hDC, 20, 100, mesText, lstrlen(mesText));			// Вывод в контекст
		EndPaint(hWnd, &ps);
	}							// Завершение обновления окна
	break;
	case WM_DESTROY:												// Завершение работы приложения. Поумолчанию не обрабатывется. Надо прописывать самостоятельно
	{
		MessageBox(NULL, g_lpszDestroyMessage, TEXT("Выход"), MB_OK);
		//PostQuitMessage(5);
	}										// Посылка WM_QUIT приложению
	break;
	default:														// Вызов "Обработчика по умолчанию"
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return FALSE;// Для ветвей с "break"
}