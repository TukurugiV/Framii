#include "realtime_effecter/app/Application.h"

#include <cstdio>
#include <stdexcept>

int main()
{
    try
    {
        realtime_effecter::Application app(1280, 720, "ImGui + OpenGL (Windows)");
        app.Run();
        return 0;
    }
    catch (const std::exception& e)
    {
        std::fprintf(stderr, "Error: %s\n", e.what());
        return 1;
    }
}
