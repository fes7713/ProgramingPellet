#include <windows.h>
#include <string>
#include <chrono>
#include <thread>
 
//メッセージ処理
LRESULT CALLBACK WndProc(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
int WINAPI WinMain(
	HINSTANCE hInstance,      // 現在のインスタンスのハンドル
	HINSTANCE hPrevInstance,  // 以前のインスタンスのハンドル
	LPSTR lpCmdLine,          // コマンドライン
	int nCmdShow              // 表示状態
) {
	HWND hWnd;
	LPCTSTR szclassName = "WinAPITest";
	WNDCLASSEX wcex;
 
	ZeroMemory((LPVOID)&wcex, sizeof(WNDCLASSEX));
 
	//ウィンドウクラスを登録
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = 0;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szclassName;
	wcex.hIconSm = NULL;
	RegisterClassEx(&wcex);
 
	//ウィンドウ作成
	hWnd = CreateWindowEx(0, szclassName, "Title", WS_OVERLAPPEDWINDOW,
		0, 0,
		400, 300,
		NULL, NULL, hInstance, NULL);
 
 
	//ウィンドウ表示
	ShowWindow(hWnd, SW_SHOW);
 
	HDC hdc = GetDC(hWnd);
	MSG msg = {};
 
	while (true) {
		//メッセージを取得したら1(true)を返し取得しなかった場合は0(false)を返す
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				//終了メッセージが来たらゲームループから抜ける
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
 
			BYTE keys[256];
			GetKeyboardState(keys);
			if (keys[VK_LBUTTON] & 0x80) {
				std::string str = "マウスの左ボタンが押されています。";
				TextOut(hdc, 10, 10, str.c_str(), str.size());
			}
			if (keys[VK_RBUTTON] & 0x80) {
				std::string str = "マウスの右ボタンが押されています。";
				TextOut(hdc, 10, 30, str.c_str(), str.size());
			}
			if (keys[VK_MBUTTON] & 0x80) {
				std::string str = "マウスホイールが押されています。";
				TextOut(hdc, 10, 50, str.c_str(), str.size());
			}
			InvalidateRect(hWnd, NULL, TRUE);
			
 
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
 
	//解放
	ReleaseDC(hWnd, hdc);
}