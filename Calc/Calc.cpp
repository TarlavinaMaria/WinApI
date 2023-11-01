#define _CRT_SECURE_NO_WARNINGS

#include<Windows.h>
#include"resource.h"

CONST CHAR g_sz_WINDOW_CLASS[] = "Calculator Class";//��� ������ ����

#define ID_EDIT  100
#define ID_BUTTON_1  101
#define ID_BUTTON_2  102
#define ID_BUTTON_3  103
#define ID_BUTTON_4  104
#define ID_BUTTON_5  105
#define ID_BUTTON_6  106
#define ID_BUTTON_7  107
#define ID_BUTTON_8  108
#define ID_BUTTON_9  109
#define ID_BUTTON_ADD    110
#define ID_BUTTON_MIN    111
#define ID_BUTTON_MUL    112
#define ID_BUTTON_DEL    113
#define ID_BUTTON_MAIN   114
#define ID_BUTTON_REM    115

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) ����������� ������ ����
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));//�������� �����

	wc.cbSize = sizeof(wc);// cb - Count Bytes(���-�� ����)
	wc.cbWndExtra = 0;// �������������� ����� ����
	wc.cbClsExtra = 0; // �������������� ����� ������ ����
	wc.style = 0;//����� ����

	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));//Sm - small
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = HBRUSH(COLOR_WINDOW + 1);

	wc.hInstance = hInstance; //hInstance - ���������� ������������ ����� ��������� � ������
	wc.lpfnWndProc = WndProc; // ��������� �� ��������� ����
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_sz_WINDOW_CLASS;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class Registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	//2) �������� ����
	INT screen_width = GetSystemMetrics(SM_CXSCREEN);
	INT screen_height = GetSystemMetrics(SM_CYSCREEN);

	INT window_width = screen_width * 1 / 4;
	INT window_height = screen_height * 1 / 4;

	INT start_x = screen_width / 4;
	INT start_y = screen_height / 4;
	HWND hwnd = CreateWindowEx
	(
		NULL, //ExStyle
		g_sz_WINDOW_CLASS,// class name
		g_sz_WINDOW_CLASS,// window name
		WS_SYSMENU,//� �������� ���� ������ ����� ����� �����
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 500,
		NULL,//Parebt window
		//---------------------------------------------------------------------------
		NULL, // hMenu - ��� �������� ���� ���� �������� �������� ID ������� ���� 
		//��� ��������� ���, ������� �������� ��������� ������� ���� hMenu ���������� ID ������� ����� ��������
  //---------------------------------------------------------------------------
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Class Registration failed", "Error", MB_OK | MB_ICONERROR);
	}
	//���������� ����
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	//3) ������ ����� ����������
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
		//int a = 0, b = 0;
		
	case WM_CREATE:
	{
		HWND hEdit = CreateWindow//����
		(
			"edit", 
			"", 
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 
			20, 20, 
			200, 20,
			hwnd, 
			(HMENU)ID_EDIT, 
			GetModuleHandle(NULL),
			NULL
		);
		HWND hbutton_1  = CreateWindow
		(
			"button", 
			"1", 
			WS_CHILD | WS_VISIBLE, 
			40, 60, 
			30, 30,
			hwnd, 
			(HMENU)ID_BUTTON_1,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hbutton_2  = CreateWindow
		(
			"button", 
			"2", 
			WS_CHILD | WS_VISIBLE, 
			80, 60, 
			30, 30,
			hwnd, 
			(HMENU)ID_BUTTON_2,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hbutton_3  = CreateWindow
		(
			"button", 
			"3", 
			WS_CHILD | WS_VISIBLE, 
			120,60, 
			30, 30,
			hwnd, 
			(HMENU)ID_BUTTON_3,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hbutton_4  = CreateWindow
		(
			"button", 
			"4", 
			WS_CHILD | WS_VISIBLE, 
			40, 100,
			30, 30,
			hwnd, 
			(HMENU)ID_BUTTON_4,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hbutton_5  = CreateWindow
		(
			"button", 
			"5", 
			WS_CHILD | WS_VISIBLE, 
			80, 100,
			30, 30,
			hwnd, 
			(HMENU)ID_BUTTON_5,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hbutton_6  = CreateWindow
		(
			"button", 
			"6", 
			WS_CHILD | WS_VISIBLE, 
			120, 100,
			30, 30,
			hwnd, 
			(HMENU)ID_BUTTON_6,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hbutton_7  = CreateWindow
		(
			"button", 
			"7", 
			WS_CHILD | WS_VISIBLE, 
			40, 140,
			30, 30,
			hwnd, 
			(HMENU)ID_BUTTON_7,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hbutton_8  = CreateWindow
		(
			"button", 
			"8", 
			WS_CHILD | WS_VISIBLE, 
			80, 140,
			30, 30,
			hwnd, 
			(HMENU)ID_BUTTON_8,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hbutton_9  = CreateWindow
		(
			"button", 
			"9", 
			WS_CHILD | WS_VISIBLE, 
			120, 140,
			30, 30,
			hwnd, 
			(HMENU)ID_BUTTON_9,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hbutton_0  = CreateWindow
		(
			"button", 
			"0", 
			WS_CHILD | WS_VISIBLE, 
			40, 180,
			30, 30,
			hwnd, 
			(HMENU)ID_BUTTON_9,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hbutton_rem  = CreateWindow//�������
		(
			"button", 
			"C", 
			WS_CHILD | WS_VISIBLE, 
			80, 180,
			30, 30,
			hwnd, 
			(HMENU)ID_BUTTON_REM,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hbutton_add  = CreateWindow//+
		(
			"button", 
			"+", 
			WS_CHILD | WS_VISIBLE, 
			160, 60,
			30, 30,
			hwnd, 
			(HMENU)ID_BUTTON_ADD,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hbutton_minus  = CreateWindow//-
		(
			"button", 
			"-", 
			WS_CHILD | WS_VISIBLE, 
			160, 100,
			30, 30,
			hwnd, 
			(HMENU)ID_BUTTON_MIN,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hbutton_nul = CreateWindow//*
		(
			"button", 
			"*", 
			WS_CHILD | WS_VISIBLE, 
			160, 140,
			30, 30,
			hwnd, 
			(HMENU)ID_BUTTON_MUL,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hbutton_del = CreateWindow//(/)
		(
			"button", 
			"/", 
			WS_CHILD | WS_VISIBLE, 
			160, 180,
			30, 30,
			hwnd, 
			(HMENU)ID_BUTTON_DEL,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hbutton_main = CreateWindow//=
		(
			"button", 
			"=", 
			WS_CHILD | WS_VISIBLE, 
			120, 180,
			30, 30,
			hwnd, 
			(HMENU)ID_BUTTON_MAIN,
			GetModuleHandle(NULL),
			NULL
		);
		
	}
	break;
	case WM_COMMAND:
		break;
	case WM_DESTROY: PostQuitMessage(0); break;
	case WM_CLOSE:   DestroyWindow(hwnd); break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return NULL;
}