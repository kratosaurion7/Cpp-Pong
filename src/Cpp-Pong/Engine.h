#pragma once

#include <Windows.h>

// DirectXTKIncludes
#include <d3d11_1.h>
#include <D3DX11.h>

#include <DirectXMath.h>

#include "Resource.h"

#include "CommonStates.h"
#include "DDSTextureLoader.h"
#include "Effects.h"
#include "GeometricPrimitive.h"
#include "Model.h"
#include "PrimitiveBatch.h"
#include "ScreenGrab.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "VertexTypes.h"

#include "PointerList.h"
#include "GameObject.h"
#include "Renderer.h"

class GameStructure;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

class Engine
{
public:
    Engine();
    ~Engine();

    HRESULT InitEngine(HINSTANCE hInstance, int nCmdShow);

    void Update();
    void Render();

    void OnInput(char input);

    ID3D11Device* GetDevice();

    PointerList<GameObject*>* gameObjects = NULL;

    template<class T>
    BaseList<T*>* GetSpecificObjects()
    {
        BaseList<T*>* list = new BaseList<T*>();

        std::list<GameObject*>::iterator iter = gameObjects->GetContainer()->begin();

        while (iter != gameObjects->GetContainer()->end())
        {
            GameObject* object = (*iter);

            T* derived = dynamic_cast<T*>(object);

            if (derived)
            {
                list->Add(derived);
            }

            iter++;
        }

        return list;
    };

private:
    HINSTANCE   hInstance = NULL;
    HWND        hWnd = NULL;

    D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_NULL;
    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

    ID3D11Device* device = NULL;

    ID3D11DeviceContext* immediateContext = NULL;
    IDXGISwapChain*      swapChain = NULL;
    ID3D11RenderTargetView* renderTargetView = NULL;

    DirectX::SpriteBatch *spriteBatch = NULL;

    HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
    HRESULT InitDevice();
    void CleanupDevice();

    GameStructure* GetGameStructure();

    Renderer* renderer = NULL;

    GameObject* Player1 = NULL;
    GameObject* Player2 = NULL;
};