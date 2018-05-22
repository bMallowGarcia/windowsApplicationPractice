#include <windows.h>
#include <stdlib.h>

/* Global Variables that for Window entities. */
HWND textPrompt;

HWND textInputOne;
char savedInputOne[20];
HWND textInputTwo;
char savedInputTwo[20];

HWND mathsButton;

/* Documentation for CreateWindow page: https://msdn.microsoft.com/en-us/library/windows/desktop/ms632679(v=vs.85).aspx 
   Documentation for GetWindowText page: https://msdn.microsoft.com/en-us/library/windows/desktop/ms633520(v=vs.85).aspx */

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		case WM_CREATE: // Entities code
			textPrompt = CreateWindow("STATIC","Input 2 numbers to do maths \n and dont forget to save them :)",
			WS_VISIBLE|WS_CHILD,10,10,300,35,hwnd,NULL,NULL,NULL);
			textInputOne = CreateWindow("EDIT","",WS_VISIBLE|WS_BORDER|WS_CHILD,10,50,100,20,hwnd,NULL,NULL,NULL);
			CreateWindow("BUTTON","Save Input One",WS_VISIBLE|WS_CHILD|WS_BORDER,10,75,200,50,hwnd,(HMENU)1,NULL,NULL);
			textInputTwo = CreateWindow("EDIT","",WS_VISIBLE|WS_BORDER|WS_CHILD,10,150,100,20,hwnd,NULL,NULL,NULL);
			CreateWindow("BUTTON","Save Input Two",WS_VISIBLE|WS_CHILD|WS_BORDER,10,175,200,50,hwnd,(HMENU)2,NULL,NULL);
			CreateWindow("BUTTON","Do Add!",WS_VISIBLE|WS_CHILD|WS_BORDER,10,250,100,50,hwnd,(HMENU)3,NULL,NULL);
			CreateWindow("BUTTON","Do Sub!",WS_VISIBLE|WS_CHILD|WS_BORDER,160,250,100,50,hwnd,(HMENU)4,NULL,NULL);
			CreateWindow("BUTTON","Do Mult!",WS_VISIBLE|WS_CHILD|WS_BORDER,10,350,100,50,hwnd,(HMENU)5,NULL,NULL);
			CreateWindow("BUTTON","Do Div!",WS_VISIBLE|WS_CHILD|WS_BORDER,160,350,100,50,hwnd,(HMENU)6,NULL,NULL);
			break;
			
		case WM_COMMAND: // Action code
		
			int gwtstatOne;
			char *tOne;
			int gwtstatTwo;
			char *tTwo;
			
			int addition;
			int sub;
			int mult;
			int div;
			
			char total[20];
			
			switch(LOWORD(wParam)){
				case 1:
					gwtstatOne = 0;
					tOne = &savedInputOne[0];
					gwtstatOne = GetWindowText(textInputOne,tOne,20);
					break;
					
				case 2:
					gwtstatTwo = 0;
					tTwo = &savedInputTwo[0];
					gwtstatTwo = GetWindowText(textInputTwo,tTwo,20);
					break;
				
				case 3:
					addition = atoi(savedInputOne) + atoi(savedInputTwo);
					itoa(addition,total,10);
					::MessageBeep(MB_ICONERROR);
					::MessageBox(hwnd,total, "Add maths",MB_OK);
					break;
					
				case 4:
					sub = atoi(savedInputOne) - atoi(savedInputTwo);
					itoa(sub,total,10);
					::MessageBeep(MB_ICONERROR);
					::MessageBox(hwnd,total, "Sub maths",MB_OK);
					break;
					
				case 5:
					mult = atoi(savedInputOne) * atoi(savedInputTwo);
					itoa(mult,total,10);
					::MessageBeep(MB_ICONERROR);
					::MessageBox(hwnd,total, "Mult maths",MB_OK);
					break;
				case 6:
					div = atoi(savedInputOne) / atoi(savedInputTwo);
					itoa(div,total,10);
					::MessageBeep(MB_ICONERROR);
					::MessageBox(hwnd,total, "Div maths",MB_OK);
					break;
			}
			break;		
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}

		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);

	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","simpleMaths",WS_VISIBLE|WS_SYSMENU|WS_MINIMIZEBOX,
	                      0, /* x */
	                      0, /* y */
	                      480, /* width */
	                      720, /* height */
	                      NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
