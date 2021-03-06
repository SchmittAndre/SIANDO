#include "stdafx.h"

#include "Window.h"
#include "Game.h"

// Entrypoint for the Application

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    GLWindow window(hInstance, _T("TextVenturer"));
    try
    {
        Game game(window);
        window.start(game);
    }
    catch (...)
    {
        window.showException(false);
    }
    return 0;
}