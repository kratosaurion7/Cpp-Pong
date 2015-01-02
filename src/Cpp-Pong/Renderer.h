#pragma once

#include "d2d1.h"

#include "BaseList.h"

#include "GameObject.h"


class Renderer
{
public:
    Renderer(HWND hwnd);
    ~Renderer();

    void DrawGameObject(GameObject* object);

    void RenderScene(BaseList<GameObject*>* objects);

private:
    HWND        hWnd = NULL;
    ID2D1Factory* pD2DFactory = NULL;

    RECT drawArea;

    ID2D1HwndRenderTarget* rt = NULL;
};

