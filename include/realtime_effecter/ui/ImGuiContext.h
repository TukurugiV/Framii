#pragma once

struct GLFWwindow;

namespace realtime_effecter {

class ImGuiContext {
public:
    // ImGuiを初期化（バックエンド含む）
    static void Initialize(GLFWwindow* window, const char* glsl_version = "#version 330");

    // ImGuiをシャットダウン
    static void Shutdown();

    // 初期化済みかチェック
    static bool IsInitialized() { return s_initialized; }

    // 新しいフレームを開始
    static void NewFrame();

    // ImGuiのレンダリングを実行
    static void Render();

private:
    ImGuiContext() = default;
    static bool s_initialized;
};

} // namespace realtime_effecter
