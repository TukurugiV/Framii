#pragma once

struct GLFWwindow;

namespace realtime_effecter {

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    // Non-copyable, non-movable
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    GLFWwindow* GetHandle() const { return m_window; }
    bool ShouldClose() const;
    void SwapBuffers();
    void GetFramebufferSize(int* width, int* height) const;

private:
    GLFWwindow* m_window;

    void InitializeGlad();
};

} // namespace realtime_effecter
