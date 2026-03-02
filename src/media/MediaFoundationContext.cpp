#include "realtime_effecter/media/MediaFoundationContext.h"
#include "realtime_effecter/util/HResultChecker.h"
#include <mfapi.h>
#include <stdexcept>

namespace realtime_effecter {

bool MediaFoundationContext::s_initialized = false;

void MediaFoundationContext::Initialize() {
    if (s_initialized) {
        return; // 既に初期化済み
    }

    // 1. COM初期化
    HRESULT hr = CoInitializeEx(nullptr,
                                COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (FAILED(hr) && hr != RPC_E_CHANGED_MODE) {
        throw HResultException(hr, "CoInitializeEx");
    }

    // 2. Media Foundation初期化
    CHECK_HR(MFStartup(MF_VERSION, MFSTARTUP_FULL));

    s_initialized = true;
}

void MediaFoundationContext::Shutdown() {
    if (!s_initialized) {
        return;
    }

    // 1. Media Foundationシャットダウン
    MFShutdown();

    // 2. COMシャットダウン
    CoUninitialize();

    s_initialized = false;
}

} // namespace realtime_effecter