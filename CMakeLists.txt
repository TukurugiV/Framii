cmake_minimum_required(VERSION 3.20)

project(realtime_effecter
  VERSION 0.1.0
  LANGUAGES C CXX
)

# ------------------------------------------------------------
# Options
# ------------------------------------------------------------
option(MYAPP_BUILD_DEMO "Build the example app executable" ON)
option(MYAPP_ENABLE_WARNINGS "Enable strict warnings for project targets" ON)
option(MYAPP_WARNINGS_AS_ERRORS "Treat warnings as errors for project targets" OFF)
option(MYAPP_INSTALL "Enable install rules" ON)

# ------------------------------------------------------------
# Global settings (keep minimal; prefer target_* APIs)
# ------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# MSVC runtime: keep default unless you have a policy. (Do not force /MT for OSS by default.)

# ------------------------------------------------------------
# Helper: apply warnings only to *our* targets, not third_party
# ------------------------------------------------------------
function(myapp_apply_warnings target_name)
  if(NOT MYAPP_ENABLE_WARNINGS)
    return()
  endif()

  if(MSVC)
    target_compile_options(${target_name} PRIVATE
      /W4
      /permissive-
      /Zc:preprocessor
      /Zc:__cplusplus
    )
    if(MYAPP_WARNINGS_AS_ERRORS)
      target_compile_options(${target_name} PRIVATE /WX)
    endif()
    # Disable noisy warnings you may want later:
    # target_compile_options(${target_name} PRIVATE /wd4100 /wd4189)
  else()
    target_compile_options(${target_name} PRIVATE
      -Wall -Wextra -Wpedantic
    )
    if(MYAPP_WARNINGS_AS_ERRORS)
      target_compile_options(${target_name} PRIVATE -Werror)
    endif()
  endif()
endfunction()

# ------------------------------------------------------------
# Dependencies (vendored / submodules)
# ------------------------------------------------------------

# GLFW (submodule)
# Ensure glfw does not build extras by default
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(third_party/glfw)

# OpenGL (Windows: opengl32)
find_package(OpenGL REQUIRED)

# GLAD (vendored source)
add_library(glad STATIC
  third_party/glad/src/glad.c
)
target_include_directories(glad PUBLIC
  third_party/glad/include
)
# glad is a dependency; don't force warnings here (leave it clean for consumers)

# ImGui (vendored via submodule)
add_library(imgui STATIC
  third_party/imgui/imgui.cpp
  third_party/imgui/imgui_demo.cpp
  third_party/imgui/imgui_draw.cpp
  third_party/imgui/imgui_tables.cpp
  third_party/imgui/imgui_widgets.cpp

  # Backends
  third_party/imgui/backends/imgui_impl_glfw.cpp
  third_party/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
  third_party/imgui
  third_party/imgui/backends
)

# ImGui backend selection + loader choice
# If you use GLAD, define IMGUI_IMPL_OPENGL_LOADER_GLAD
target_compile_definitions(imgui PUBLIC
  IMGUI_IMPL_OPENGL_LOADER_GLAD
)

target_link_libraries(imgui PUBLIC
  glfw
  glad
  OpenGL::GL
)

# ------------------------------------------------------------
# Media Foundation libraries (Windows only)
# ------------------------------------------------------------
if(WIN32)
  set(MF_LIBRARIES
    mfplat.lib
    mf.lib
    mfreadwrite.lib
    mfuuid.lib
  )
endif()

# ------------------------------------------------------------
# Media Foundation library
# ------------------------------------------------------------
if(WIN32)
  add_library(rt_media STATIC
    src/media/MediaFoundationContext.cpp
  )

  target_include_directories(rt_media PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  )

  target_link_libraries(rt_media PUBLIC
    ${MF_LIBRARIES}
  )

  target_compile_definitions(rt_media PRIVATE
    WINVER=0x0A00
    _WIN32_WINNT=0x0A00
    NOMINMAX
  )

  myapp_apply_warnings(rt_media)
endif()

# ------------------------------------------------------------
# Application framework library
# ------------------------------------------------------------
add_library(rt_app STATIC
  src/graphics/GraphicsContext.cpp
  src/graphics/Window.cpp
  src/ui/ImGuiContext.cpp
  src/app/Application.cpp
)

target_include_directories(rt_app PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(rt_app PUBLIC
  imgui
  glfw
  glad
  OpenGL::GL
)

myapp_apply_warnings(rt_app)

# ------------------------------------------------------------
# Targets
# ------------------------------------------------------------

if(MYAPP_BUILD_DEMO)
  add_executable(myapp
    src/main.cpp
  )

  target_link_libraries(myapp PRIVATE
    rt_app
    rt_media
  )

  target_include_directories(myapp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  )

  myapp_apply_warnings(myapp)

  # Nice IDE grouping (optional)
  set_target_properties(myapp PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  )
endif()

# ------------------------------------------------------------
# Install rules (basic)
# ------------------------------------------------------------
if(MYAPP_INSTALL)
  include(GNUInstallDirs)

  # Install executable
  if(TARGET myapp)
    install(TARGETS myapp
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
  endif()

  # Install public headers (if you have any)
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include")
    install(DIRECTORY include/
      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
      FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
    )
  endif()

  # (Optional) export package config later if you turn this into a library project
endif()
