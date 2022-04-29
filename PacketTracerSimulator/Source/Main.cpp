#include "Core/Application.h"

#ifdef ENGINE_DEBUG
int main()
#else
#include <Windows.h>
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
#endif // ENGINE_DEBUG
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