#include "realtime_effecter/ui/ImGuiContext.h"

#include <stdexcept>

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace realtime_effecter {

bool ImGuiContext::s_initialized = false;

void ImGuiContext::Initialize(GLFWwindow* window, const char* glsl_version)
{
    if (s_initialized)
        return;

    if (!window)
    {
        throw std::runtime_error("Window must not be null for ImGui initialization");
    }

    // ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    // Backend init
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    s_initialized = true;
}

void ImGuiContext::Shutdown()
{
    if (!s_initialized)
        return;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    s_initialized = false;
}

void ImGuiContext::NewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiContext::Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

} // namespace realtime_effecter
