#include "realtime_effecter/graphics/Window.h"

#include <cstdio>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace realtime_effecter {

Window::Window(int width, int height, const char* title)
    : m_window(nullptr)
{
    // OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!m_window)
    {
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // vsync

    InitializeGlad();
}

Window::~Window()
{
    if (m_window)
    {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(m_window);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_window);
}

void Window::GetFramebufferSize(int* width, int* height) const
{
    glfwGetFramebufferSize(m_window, width, height);
}

void Window::InitializeGlad()
{
    // GLAD init - gladLoadGL uses its own loader which works
    // more reliably on Windows than gladLoadGLLoader(glfwGetProcAddress)
    if (!gladLoadGL())
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

} // namespace realtime_effecter
