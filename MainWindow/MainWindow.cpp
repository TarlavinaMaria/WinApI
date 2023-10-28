#define _CRT_SECURE_NO_WARNINGS

#include<Windows.h>
#include<stdio.h>
#include"resource.h"


CONST CHAR g_sz_WINDOW_CLASS[] = "Mt Window Class";//��� ������ ����

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//�������� �������� ����
	//1) ����������� ������ ����
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));//�������� �����

	wc.cbSize = sizeof(wc);// cb - Count Bytes(���-�� ����)
	wc.cbWndExtra = 0;// �������������� ����� ����
	wc.cbClsExtra = 0; // �������������� ����� ������ ����
	wc.style = 0;//����� ����

	//wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_coffee));
	//wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_cuces));//Sm - small
	wc.hIcon = (HICON)LoadImage(hInstance, "macaroon.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIcon = (HICON)LoadImage(hInstance, "donut.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = HBRUSH(COLOR_WINDOW + 1);

	wc.hInstance = hInstance; //hInstance - ���������� ������������ ����� ��������� � ������
	//������� WinMain() ��������� hInstance ��� ��������� � ������� � ���� ���� ������ ������
	//� ����� ������ ������� hInstance ������ ����� �������� ��� ������ ������ GetModuleHande(NULL)
	wc.lpfnWndProc = WndProc; // ��������� �� ��������� ����
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_sz_WINDOW_CLASS;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class Registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	//2) �������� ����
	HWND hwnd = CreateWindowEx
	(
		NULL, //ExStyle
		g_sz_WINDOW_CLASS,// class name
		g_sz_WINDOW_CLASS,// window name
		WS_OVERLAPPEDWINDOW,//� �������� ���� ������ ����� ����� �����
		CW_USEDEFAULT, CW_USEDEFAULT,//Position - ��������� ���� �� ������
		CW_USEDEFAULT, CW_USEDEFAULT,// Size - ������ ����
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
		break;
	case WM_COMMAND:
		break;
	case WM_DESTROY: PostQuitMessage(0); break;
	case WM_CLOSE: DestroyWindow(hwnd); break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return NULL;
}