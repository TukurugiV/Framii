#pragma once
#include <Windows.h>
#include <stdexcept>
#include <string>

namespace realtime_effecter {

class HResultException : public std::runtime_error {
public:
    HResultException(HRESULT hr, const char* operation)
        : std::runtime_error(FormatError(hr, operation))
        , m_hr(hr)
    {}

    HRESULT GetHResult() const { return m_hr; }

private:
    HRESULT m_hr;

    static std::string FormatError(HRESULT hr, const char* operation) {
        char buffer[512];
        snprintf(buffer, sizeof(buffer),
                 "HRESULT error 0x%08X in: %s", hr, operation);
        return std::string(buffer);
    }
};

// HRESULTチェック用マクロ
#define CHECK_HR(expr) \
    do { \
        HRESULT __hr = (expr); \
        if (FAILED(__hr)) { \
            throw realtime_effecter::HResultException(__hr, #expr); \
        } \
    } while(0)

} // namespace realtime_effecter
