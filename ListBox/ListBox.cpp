#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include"resource.h"

CONST CHAR* g_sz_VALUES[] = { "Haas, Jonathan", "Pai, Jyothi","Hanif, Kerim", "Anderberg, Michael", "Raposo, Rui" };


BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:// Инициализация диалогового окна
	{
		HWND hList = GetDlgItem(hwnd, IDC_LIST);
		for (int i = 0; i < sizeof(g_sz_VALUES) / sizeof(g_sz_VALUES[0]); i++)
		{
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)g_sz_VALUES[i]);
		}
	}
	break;
	case WM_COMMAND:// Обработчик команд
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hList = GetDlgItem(hwnd, IDC_LIST);
			int i = SendMessage(hList, LB_GETCURSEL, 0, 0);
			SendMessage(hList, LB_GETTEXT, i, (LPARAM)sz_buffer);
			CHAR sz_message[SIZE]{};
			sprintf(sz_message, "Вы выбрали элемент № %i, со значение \"%s\"", i, sz_buffer);
			MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
		}
		break;
		case IDC_LIST_WRITE://поле добавления текста
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			HWND hList = GetDlgItem(hwnd, IDC_LIST_WRITE);
			SendMessage(hList, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
		}
		break;
		case IDC_ADD:
		{
			//1)Создаем буфер чтения
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			//2) Получаем обработчик текстового поля 
			HWND hAdd_list = GetDlgItem(hwnd, IDC_LIST_WRITE);
			HWND hList = GetDlgItem(hwnd, IDC_LIST);
			//3) Читаем текст из текствого поля 
			SendMessage(hAdd_list, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			//4) Загружем содержимое тектсовго буфера в поле
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
		}
		break;
		case IDC_DEL:
		{
			HWND hList = GetDlgItem(hwnd, IDC_LIST);
			LRESULT item = SendMessage(hList, LB_GETCURSEL, 0, 0);
			SendMessage(hList, LB_DELETESTRING, (WPARAM)item, 0);
		}
			break;
		case IDCANCEL:EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:EndDialog(hwnd, 0);
	}
	return FALSE;
}