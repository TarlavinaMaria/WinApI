#define _CRT_SECURE_NO_WARNINGS

#include<Windows.h>
#include"resource.h"

CONST CHAR g_sz_WINDOW_CLASS[] = "Calculator Class";//��� ������ ����


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
	case WM_CREATE:
	{

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
