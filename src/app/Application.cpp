#include "realtime_effecter/app/Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "realtime_effecter/graphics/GraphicsContext.h"
#include "realtime_effecter/graphics/Window.h"
#include "realtime_effecter/ui/ImGuiContext.h"

namespace realtime_effecter {

Application::Application(int width, int height, const char* title)
{
    Initialize(width, height, title);
}

Application::~Application()
{
    Shutdown();
}

void Application::Initialize(int width, int height, const char* title)
{
    // 初期化シーケンス
    GraphicsContext::Initialize();
    m_window = std::make_unique<Window>(width, height, title);
    ImGuiContext::Initialize(m_window->GetHandle());
}

void Application::Shutdown()
{
    // 逆順でクリーンアップ
    ImGuiContext::Shutdown();
    m_window.reset(); // Window destructor
    GraphicsContext::Shutdown();
}

void Application::Run()
{
    MainLoop();
}

void Application::MainLoop()
{
    while (!m_window->ShouldClose())
    {
        glfwPollEvents();

        ImGuiContext::NewFrame();

        // カスタムUI/ロジック
        OnUpdate();

        // カスタムレンダリング
        OnRender();

        // ImGui描画
        ImGuiContext::Render();

        m_window->SwapBuffers();
    }
}

void Application::OnUpdate()
{
    // デフォルト実装：元のmain.cppのHelloウィンドウ
    ImGui::Begin("Hello");
    ImGui::Text("ImGui + OpenGL on Windows");
    ImGui::End();
}

void Application::OnRender()
{
    // デフォルト実装：ビューポート設定とクリア
    int display_w, display_h;
    m_window->GetFramebufferSize(&display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

} // namespace realtime_effecter
