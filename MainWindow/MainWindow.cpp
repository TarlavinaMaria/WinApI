#define _CRT_SECURE_NO_WARNINGS

#include<Windows.h>
#include<stdio.h>
#include<string>
#include<vector>
#include"resource.h"

#define IDC_COMBO 1001
#define IDC_BUTTON_APPLY 1002
CONST CHAR* g_CURSOR[] = { "busy.ani", "Working In Background.ani", "normal.ani","move.ani"};


CONST CHAR g_sz_WINDOW_CLASS[] = "Mt Window Class";//��� ������ ����


std::vector<std::string> LoadCurcorsFromDir(const std::string& directory);
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	/*
	HINSTANCE - ��������� ������������ ����� ��������� � ����������� ������.
	���� ����� ���������� � *.exe-����� ��� ����� ������� ����� hInstance.
	hInstance ������ ����� �������� ��� ������ ������� GetModuleHandle(NULL).

	hPrevInst - ���������� ��������� ���������. ���� �������� ����� �� ������������.

	lpCmdLine - ��������� ������ �� ������� ����������� ���������. 
	����� ��� ��������� ������ ��������� ����� �������� � ���� ��� URL. 

	LPSTR - lp - Long Pointer

	nCmdShow - ����� ���������� ����� �������� � ����� �������� � ������ �����, ��������� �� ���� �����
	n - number
	*/

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
	//wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	//wc.hCursor = (HCURSOR)LoadImage(hInstance, "cursors.ani", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
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
	INT screen_width = GetSystemMetrics(SM_CXSCREEN);
	INT screen_height = GetSystemMetrics(SM_CYSCREEN);
	//CHAR sz_msg[MAX_PATH]{};
	//sprintf(sz_msg, "Resolution: %ix%i", screen_width, screen_height);
	//MessageBox(NULL, sz_msg, "Screen resolution", MB_OK);
	INT window_width = screen_width * 3 / 4;
	INT window_height = screen_height * 3 / 4;

	INT start_x = screen_width / 8;
	INT start_y = screen_height / 8;
	HWND hwnd = CreateWindowEx
	(
		NULL, //ExStyle
		g_sz_WINDOW_CLASS,// class name
		g_sz_WINDOW_CLASS,// window name
		WS_OVERLAPPEDWINDOW,//� �������� ���� ������ ����� ����� �����
		start_x, start_y,//Position - ��������� ���� �� ������
		window_width, window_height,// Size - ������ ����
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
	case WM_MOVE://
	{
		RECT rect;
		GetWindowRect(hwnd, &rect);
		CHAR sz_message[MAX_PATH];
		sprintf(sz_message, "%s - Position: %ix%i, Size: %ix%i", g_sz_WINDOW_CLASS, 
			rect.left, rect.top, 
			rect.right - rect.left, rect.bottom - rect.top);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_message);

	}
	break;
	case WM_CREATE:
	{
		HWND hCombo = CreateWindowEx

		(NULL,
			"ComboBox",
			"",
			WS_CHILD | WS_VISIBLE | CBN_DROPDOWN | WS_VSCROLL,
			10, 10,
			200, 200,
			hwnd,
			(HMENU)IDC_COMBO,
			GetModuleHandle(NULL),
			NULL
		);
		/*for (int i = 0; i < sizeof(g_CURSOR) / sizeof(g_CURSOR[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_CURSOR[i]);
		}*/
		std::vector<std::string> cursors = LoadCurcorsFromDir("Cursor\\*");
		for (int i = 0; i < cursors.size(); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)cursors[i].c_str());
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
			//������ ������ ��� ����, ������--------------------------------------------
			SetClassLong(hwnd, GCL_HCURSOR, (LONG)hCursor);
			SetClassLong(GetDlgItem(hwnd, IDC_BUTTON_APPLY), GCL_HCURSOR, (LONG)hCursor);
			SetClassLong(GetDlgItem(hwnd, IDC_COMBO), GCL_HCURSOR, (LONG)hCursor);
			//--------------------------------------------------------------------------
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
std::vector<std::string> LoadCurcorsFromDir(const std::string& directory)
{
	std::vector<std::string> files;
	WIN32_FIND_DATA data;

	for (
		HANDLE hFind = FindFirstFile(directory.c_str(), &data);
		FindNextFile(hFind, &data);
		)
	{
		//const char* std::string::c_str() ���������� �� ������ ���������� � ������� std::string
		if(
			strcmp(strrchr(data.cFileName, '.'), ".cur") == 0 ||
			strcmp(strrchr(data.cFileName, '.'), ".ani") == 0
			)
			files.push_back(data.cFileName);
	}

	return files;
}