#include "realtime_effecter/graphics/GraphicsContext.h"

#include <cstdio>
#include <stdexcept>

#include <GLFW/glfw3.h>

namespace realtime_effecter {

bool GraphicsContext::s_initialized = false;

void GraphicsContext::GlfwErrorCallback(int error, const char* description)
{
    std::fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void GraphicsContext::Initialize()
{
    if (s_initialized)
        return;

    glfwSetErrorCallback(GlfwErrorCallback);
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    s_initialized = true;
}

void GraphicsContext::Shutdown()
{
    if (!s_initialized)
        return;

    glfwTerminate();
    s_initialized = false;
}

} // namespace realtime_effecter
