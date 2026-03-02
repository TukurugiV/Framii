#pragma once

#include <memory>

namespace realtime_effecter {

class Window;

class Application {
public:
    Application(int width = 1280, int height = 720, const char* title = "ImGui + OpenGL (Windows)");
    ~Application();

    // Non-copyable, non-movable
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void Run();

protected:
    // カスタムUI/ロジックをオーバーライド可能
    virtual void OnUpdate();

    // カスタムレンダリングをオーバーライド可能
    virtual void OnRender();

private:
    std::unique_ptr<Window> m_window;

    void Initialize(int width, int height, const char* title);
    void Shutdown();
    void MainLoop();
};

} // namespace realtime_effecter
