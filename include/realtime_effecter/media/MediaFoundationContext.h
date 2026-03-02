#pragma once
#include <Windows.h>
#include <mfapi.h>

namespace realtime_effecter {

class MediaFoundationContext {
public:
    // Media Foundationを初期化
    static void Initialize();

    // Media Foundationをシャットダウン
    static void Shutdown();

    // 初期化済みかチェック
    static bool IsInitialized() { return s_initialized; }

private:
    MediaFoundationContext() = default;
    static bool s_initialized;
};

} // namespace realtime_effecter
