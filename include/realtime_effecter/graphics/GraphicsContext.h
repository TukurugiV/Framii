#pragma once

namespace realtime_effecter {

class GraphicsContext {
public:
    // GLFWライブラリを初期化
    static void Initialize();

    // GLFWライブラリをシャットダウン
    static void Shutdown();

    // 初期化済みかチェック
    static bool IsInitialized() { return s_initialized; }

private:
    GraphicsContext() = default;
    static bool s_initialized;

    static void GlfwErrorCallback(int error, const char* description);
};

} // namespace realtime_effecter
