#include "Engine.h"

#include "GameInfo.h"

#include "Ball.h"
#include "Paddle.h"

using namespace DirectX;

#define WINDOWHEIGHT 600
#define WINDOWWIDTH 800

Engine::Engine()
{
    gameObjects = new PointerList<GameObject*>();

    Paddle* player_1_paddle = new Paddle();
    Paddle* player_2_paddle = new Paddle();

    //Ball* ball = new Ball();


    player_1_paddle->Height = 50;
    player_1_paddle->Width = 50;

    player_1_paddle->pos_x = 100;
    player_1_paddle->pos_y = 100;

    player_1_paddle->Color = 0x0000FF;

    player_2_paddle->Height = 50;
    player_2_paddle->Width = 50;

    player_2_paddle->pos_x = 200;
    player_2_paddle->pos_y = 200;

    Player1 = player_1_paddle;
    Player2 = player_2_paddle;

    gameObjects->Add(player_1_paddle);
    gameObjects->Add(player_2_paddle);
    //gameObjects->Add(ball);

};

Engine::~Engine()
{

};

void Engine::Update()
{
    if (GetKeyState(VK_LEFT) & 0x8000)
    {
        Player1->pos_x--;
    }
    if (GetKeyState(VK_RIGHT) & 0x8000)
    {
        Player1->pos_x++;
    }
    if (GetKeyState('A') & 0x8000)
    {
        Player2->pos_x--;
    }
    if (GetKeyState('D') & 0x8000)
    {
        Player2->pos_x++;
    }

    GameStructure* context = GetGameStructure();

    for (int i = 0; i < gameObjects->Count(); i++)
    {
        gameObjects->Get(i)->Update(context);
    }

    delete(context);
};

GameStructure* Engine::GetGameStructure()
{
    GameStructure* context = new GameStructure;

    context->area_height = WINDOWHEIGHT;
    context->area_width = WINDOWWIDTH;

    context->Balls = GetSpecificObjects<Ball>();
    context->Paddles = GetSpecificObjects<Paddle>();

    return context;
};

void Engine::Render()
{
    renderer->RenderScene(gameObjects);
};

void Engine::OnInput(char input)
{
    bool handled;

    //switch (input)
    //{
    //    case VK_LEFT:
    //    {
    //        Player1->pos_x--;
    //        break;
    //    }
    //    case VK_RIGHT:
    //    {
    //        Player1->pos_x++;
    //        break;
    //    }
    //    case 'A':
    //    {
    //        Player2->pos_x--;
    //        break;
    //    }
    //    case 'D':
    //    {
    //        Player2->pos_x++;
    //        break;
    //    }
    //    default:
    //        break;
    //}


};

HRESULT Engine::InitEngine(HINSTANCE hInstance, int nCmdShow)
{
    if (FAILED(InitWindow(hInstance, nCmdShow)))
        return 0;

    if (FAILED(InitDevice()))
    {
        CleanupDevice();
        return 0;
    }

    spriteBatch = new SpriteBatch(immediateContext);

    renderer = new Renderer(hWnd);
};

HRESULT Engine::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
    // Register the window class what will be used by the 
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"PongClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
    if (!RegisterClassEx(&wcex))
        return E_FAIL;

    // Create window
    Engine::hInstance = hInstance;
    RECT rc = { 0, 0, WINDOWWIDTH, WINDOWHEIGHT };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    Engine::hWnd = CreateWindow(L"PongClass", L"Cpp-Pong", // Textual parameters
        WS_OVERLAPPEDWINDOW, // Window Style params
        CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, // Starting position
        NULL, NULL, hInstance, NULL); // Window contextual paramteters

    if (!hWnd)
        return E_FAIL;

    ShowWindow(hWnd, nCmdShow);

    return S_OK;
};

HRESULT Engine::InitDevice()
{
    HRESULT hr = S_OK;

    RECT rc;
    GetClientRect(hWnd, &rc);
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    UINT createDeviceFlags = 0;

#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };

    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };

    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    // Initiates the swap chain - The SwapChain is the collection of drawing buffers being swapped
    DXGI_SWAP_CHAIN_DESC sd; // Dx SwapChain descriptor
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;

    /* Goes through each driver type and try to init the Device and the swap chain, tries it sequentially
    * and breaks as soon as one works.
    */
    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        driverType = driverTypes[driverTypeIndex];

        hr = D3D11CreateDeviceAndSwapChain(NULL, driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
            D3D11_SDK_VERSION, &sd, &swapChain, &device, &featureLevel, &immediateContext);

        if (SUCCEEDED(hr))
            break;
    }

    if (FAILED(hr))
        return hr;

    /* Create a render target view. Gets a reference to the swapchain surface 0 and from that
    * creates the RenderTargetView
    */
    ID3D11Texture2D* pBackBuffer = NULL;
    hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    if (FAILED(hr))
        return hr;

    hr = device->CreateRenderTargetView(pBackBuffer, NULL, &renderTargetView);
    pBackBuffer->Release(); // ? Why release the backbuffer, isn't it used by the RenderTargetView ?

    if (FAILED(hr))
        return hr;

    immediateContext->OMSetRenderTargets(1, &renderTargetView, NULL);

    /* Setup the viewport
    *	The viewport is the final result of the initialisation. The Viewport is
    *  directly what we see on the screen.
    */
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    immediateContext->RSSetViewports(1, &vp);

    return S_OK;
};

void Engine::CleanupDevice()
{
    if (immediateContext) immediateContext->ClearState();

    if (renderTargetView) renderTargetView->Release();
    if (swapChain) swapChain->Release();
    if (immediateContext) immediateContext->Release();
    if (device) device->Release();
};


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
        case WM_PAINT:
        {
            hdc = BeginPaint(hWnd, &ps);

            EndPaint(hWnd, &ps);

            break;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }
        case WM_KEYDOWN:
        {
            //OnInput((char)wParam);

            break;
        }
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
};