#include "Renderer.h"

#include "d2d1.h"

#include "BaseList.h"

Renderer::Renderer(HWND hwnd)
{
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);

    hWnd = hwnd;

    GetClientRect(hwnd, &drawArea);

    
    hr = pD2DFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(
            hWnd,
            D2D1::SizeU(
                drawArea.right - drawArea.left,
                drawArea.bottom - drawArea.top)
        ), &rt);

    rt->SetTransform(D2D1::Matrix3x2F::Identity());
};


Renderer::~Renderer()
{
};

void Renderer::DrawGameObject(GameObject* object)
{
    HRESULT hr;

    D2D1::ColorF color = D2D1::ColorF(object->Color, 1.0f);

    ID2D1SolidColorBrush* brush = NULL;

    hr = rt->CreateSolidColorBrush(color, &brush);


    D2D1_RECT_F test = D2D1::RectF(object->pos_x,
                                object->pos_y,
                                object->pos_x + object->Width,
                                object->pos_y + object->Height);

    D2D1_RECT_F test2 = D2D1::RectF(0.1f, 0.1f, 0.5f, 0.5f);

    rt->FillRectangle(test, brush);

    brush->Release();
};

void Renderer::RenderScene(BaseList<GameObject*>* objects)
{
    rt->BeginDraw();

    rt->Clear(D2D1::ColorF(D2D1::ColorF::CornflowerBlue));

    for (int i = 0; i < objects->Count(); i++)
    {
        GameObject* object = objects->Get(i);

        DrawGameObject(object);
    }

    HRESULT hr = rt->EndDraw();

}
