#include <windows.h>

#include "Engine.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    Engine* engine = new Engine();

    // Create the window
    if (FAILED(engine->InitEngine(hInstance, nCmdShow)))
        return 0;

    // Main message loop
    MSG msg = { 0 };
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            switch (msg.message)
            {
                //case WM_KEYDOWN:
                //{
                //    engine->OnInput((char)msg.wParam);

                //    break;
                //}
                //case WM_LBUTTONDOWN:
                //{
                //    POINTS coordinate = MAKEPOINTS(msg.lParam);

                //    gameEngine->OnClick(coordinate.x, coordinate.y);

                //    break;
                //}
                default:
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);

                    break;
                }
            }

        }
        else
        {
            engine->Update();
            engine->Render();
        }
    }

    return (int)msg.wParam;
};


