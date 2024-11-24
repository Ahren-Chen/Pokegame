#include <iostream>
#include "utility.h"

using namespace std;

global_variable bool running = true;

#include "platform_common.h"
#include "renderer.h"
#include "game.h"

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    Renderer& renderer = Renderer::get_instance();
    LRESULT result = 0;
    
    switch (uMsg) {
        case WM_CLOSE:
        case WM_DESTROY: {
            running = false;
        } break;

        case WM_SIZE: {
            RECT rect;
            GetClientRect(hwnd, &rect);

            int width = rect.right - rect.left;
            int height = rect.bottom - rect.top;
            renderer.initialize(width, height);
        }
        default: {
            result = DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }
	return result;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Game Window";

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

    Input input = {};

    Renderer& renderer = Renderer::get_instance();

    //Game loop
    while (running) {
        //input
        MSG message;

        for (int i = 0; i < BUTTON_COUNT; i++) {
            input.buttons[i].changed = false;
        }

        while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {

            switch(message.message) {
                case WM_KEYUP:
                case WM_KEYDOWN: {
                    u32 vk_code =  (u32) message.wParam;
                    bool is_down = ((message.lParam & (1 << 31)) == 0);

#define process_button(b, vk)\
case vk: {\
    input.buttons[b].is_down = is_down;\
    input.buttons[b].changed = true;\
} break;

                    switch(vk_code) {
                        process_button(BUTTON_UP, VK_UP);
                        process_button(BUTTON_DOWN, VK_DOWN);
                        process_button(BUTTON_LEFT, VK_LEFT);
                        process_button(BUTTON_RIGHT, VK_RIGHT);
                    
                    }
                } break;
                default: {
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                }
            }
        }

        //simulate
        Simulate(&input);
        //clear_screen(0xff5500);

        renderer.draw_rectangle(0, 0, 4, 2, 0xff0000);

        //render
        StretchDIBits(hdc, 0, 0, renderer.get_width(), renderer.get_height(), 0, 0, renderer.get_width(), renderer.get_height(), renderer.get_memory(), renderer.get_bitmap_info(), DIB_RGB_COLORS, SRCCOPY);
    }
    return 0;
}