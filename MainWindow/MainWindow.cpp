#define _CRT_SECURE_NO_WARNINGS

#include<Windows.h>
#include<stdio.h>
#include"resource.h"

#define IDC_COMBO 1001
#define IDC_BUTTON_APPLY 1002
CONST CHAR* g_CURSOR[] = { "busy.ani", "Working In Background.ani", "normal.ani","move.ani"};


CONST CHAR g_sz_WINDOW_CLASS[] = "Mt Window Class";//имя класса окна

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//Создание главного окна
	//1) регистрация класса окна
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));//Обнуляем класс

	wc.cbSize = sizeof(wc);// cb - Count Bytes(кол-во байт)
	wc.cbWndExtra = 0;// Дополнительные байты окна
	wc.cbClsExtra = 0; // дополнительные байты класса окна
	wc.style = 0;//стиль окна

	//wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_coffee));
	//wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_cuces));//Sm - small
	wc.hIcon = (HICON)LoadImage(hInstance, "macaroon.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIcon = (HICON)LoadImage(hInstance, "donut.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	//wc.hCursor = (HCURSOR)LoadImage(hInstance, "cursors.ani", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hbrBackground = HBRUSH(COLOR_WINDOW + 1);

	wc.hInstance = hInstance; //hInstance - экзаемпляр исполняемого файла программы в памяти
	//функция WinMain() принимает hInstance как параметры и поэтому к нему есть прямой доступ
	//В любой другой функции hInstance всегда можно получить при помощи фунции GetModuleHande(NULL)
	wc.lpfnWndProc = WndProc; // указатель на процедуру окна
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_sz_WINDOW_CLASS;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class Registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	//2) создание окна
	HWND hwnd = CreateWindowEx
	(
		NULL, //ExStyle
		g_sz_WINDOW_CLASS,// class name
		g_sz_WINDOW_CLASS,// window name
		WS_OVERLAPPEDWINDOW,//у главного окна всегда будет такой стиль
		CW_USEDEFAULT, CW_USEDEFAULT,//Position - положение окна на экране
		CW_USEDEFAULT, CW_USEDEFAULT,// Size - размер окна
		NULL,//Parebt window
		//---------------------------------------------------------------------------
		NULL, // hMenu - для главного окна этот параметр содержит ID ресурса меню 
		      //Для дочернего она, которое является элементом другого окна hMenu передается ID ресурса этого элемента
		//---------------------------------------------------------------------------
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Class Registration failed", "Error", MB_OK | MB_ICONERROR);
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	//3) запуск цикла сообщейний
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_SIZE:
	{
		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE] = {};
		HWND hwnd = GetActiveWindow();
		RECT rect;
		GetWindowRect(hwnd, &rect);
		int windowWidth = rect.right - rect.left;
		int windowHeight = rect.bottom - rect.top;
		sprintf(sz_buffer, "Width=%d, Heigth=%d", windowWidth, windowHeight);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
	}
	case WM_CREATE:
	{
		HWND hCombo = CreateWindowEx

		(NULL,
			"ComboBox",
			"",
			WS_CHILD | WS_VISIBLE | CBN_DROPDOWN,
			10, 10,
			200, 200,
			hwnd,
			(HMENU)IDC_COMBO,
			GetModuleHandle(NULL),
			NULL
		);
		for (int i = 0; i < sizeof(g_CURSOR) / sizeof(g_CURSOR[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_CURSOR[i]);
		}
		HWND bButton = CreateWindowEx
		(
			NULL,
			"Button",
			"Apply",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			220, 10,
			100, 24,
			hwnd,
			(HMENU)IDC_BUTTON_APPLY,
			GetModuleHandle(NULL),
			NULL
		);
	}
		break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_APPLY:
		{
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
			int i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			CHAR sz_filename[_MAX_FNAME]{};
			CHAR sz_filepath[_MAX_PATH] = "Cursor\\";
			SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_filename);
			strcat(sz_filepath, sz_filename);
			//MessageBox(hwnd, sz_filename, "Info", MB_OK);
			HCURSOR hCursor = (HCURSOR)LoadImage(
				GetModuleHandle(NULL),
				sz_filepath,
				IMAGE_CURSOR,
				LR_DEFAULTSIZE, LR_DEFAULTSIZE,
				LR_LOADFROMFILE);
			//SetCursorPos(500, 200);
			SetClassLong(hwnd, GCL_HCURSOR, (LONG)hCursor);
			SetClassLong(GetDlgItem(hwnd, IDC_BUTTON_APPLY), GCL_HCURSOR, (LONG)hCursor);
			SetClassLong(GetDlgItem(hwnd, IDC_COMBO), GCL_HCURSOR, (LONG)hCursor);
			//SetCursor(hCursor);
			return FALSE;
		}
			break;
		}
	}
		break;
	case WM_DESTROY: PostQuitMessage(0); break;
	case WM_CLOSE:   DestroyWindow(hwnd); break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return NULL;
}