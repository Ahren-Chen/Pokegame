#include <iostream>
#include <windows.h>
#include "utility.cpp"

using namespace std;

global_variable bool running = true;

struct Render_State {
    int height, width;
    void* memory;

    BITMAPINFO bitmap_info;
};

global_variable Render_State render_state;

#include "renderer.cpp"


LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    LRESULT result = 0;

    switch (uMsg) {
        case WM_CLOSE:
        case WM_DESTROY: {
            running = false;
        } break;

        case WM_SIZE: {
            RECT rect;
            GetClientRect(hwnd, &rect);
            render_state.width = rect.right - rect.left;
            render_state.height = rect.bottom - rect.top;

            int size = render_state.width * render_state.height * sizeof(u32);

            if (render_state.memory) VirtualFree(render_state.memory, 0, MEM_RELEASE);
            render_state.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
            

            render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader);
            render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
            render_state.bitmap_info.bmiHeader.biHeight = render_state.height;
            render_state.bitmap_info.bmiHeader.biPlanes = 1;
            render_state.bitmap_info.bmiHeader.biBitCount = 32;
            render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;
        }
        default: {
            result = DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }
	return result;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Window";

	WNDCLASSW wc = { };

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = window_callback;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	RegisterClassW(&wc);

	//Create window
    HWND window = CreateWindowExW(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Pokemon",    // Window text
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (window == NULL)
    {
        return 1;
    }

    ShowWindow(window, nShowCmd);

    HDC hdc = GetDC(window);

    //Game loop
    while (running) {
        //input
        MSG message;
        while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        clear_screen(0xff5500);
        draw_rectangle(0, 0, 4, 2, 0xff0000);

        //render
        StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
    }
    return 0;
}