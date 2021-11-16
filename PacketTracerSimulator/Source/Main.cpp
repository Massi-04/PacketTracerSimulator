#include "Core/Application.h"

#ifdef ENGINE_DEBUG
#define MAIN int main()
#else
#include <Windows.h>
#define MAIN int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
#endif // ENGINE_DEBUG

MAIN
{
    Application& app = GetApplication(); 
    if (!app.Init())
    {
        LOG("[Error:] unable to initialize engine");
        return -1;
    }
    app.Run();
    app.Shutdown();
}