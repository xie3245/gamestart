cmake_minimum_required(VERSION 3.16)
project(Slurpwave LANGUAGES C CXX)

# Default build type for single-config generators (Ninja/Make)
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release;RelWithDebInfo;MinSizeRel")
endif()

# Put binaries in build/<config>  (works for single- and multi-config)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>")

# Dependencies (as you had)
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_ttf EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_mixer EXCLUDE_FROM_ALL)

# Game target
add_executable(Slurpwave
  main.cpp sidebar.cpp renderer.cpp globals.cpp sound.cpp ui.cpp
  ramenCooking.cpp customer.cpp res.cpp
)
target_compile_features(Slurpwave PUBLIC cxx_std_20)
target_link_libraries(Slurpwave PRIVATE SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf SDL3_mixer::SDL3_mixer SDL3::SDL3 -static)

# Copy assets next to the built binary (per-config safe)
add_custom_command(TARGET Slurpwave POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          "${CMAKE_SOURCE_DIR}/assets"
          "$<TARGET_FILE_DIR:Slurpwave>/assets"
)

# ---- Build-type specific opts ----
if(MSVC)
  # Compile: size/speed tuned, no debug checks in release
  target_compile_options(Slurpwave PRIVATE
    "$<$<CONFIG:Debug>:/Zi;/Od;/DDEBUG>"
    "$<$<CONFIG:RelWithDebInfo>:/O2;/Zi;/DNDEBUG>"
    "$<$<CONFIG:Release>:/O2;/DNDEBUG;/Gy>"         # /Gy = function-level linking
    "$<$<CONFIG:MinSizeRel>:/O1;/DNDEBUG;/Gy>"      # smallest exe
  )
  # Link: fold and remove unused code
  target_link_options(Slurpwave PRIVATE
    "$<$<CONFIG:Release>:/OPT:REF;/OPT:ICF>"
    "$<$<CONFIG:MinSizeRel>:/OPT:REF;/OPT:ICF>"
  )
else()
  # GCC/Clang
  target_compile_options(Slurpwave PRIVATE
    "$<$<CONFIG:Debug>:-O0;-g;-DDEBUG>"
    "$<$<CONFIG:RelWithDebInfo>:-O2;-g;-DNDEBUG>"
    "$<$<CONFIG:Release>:-O2;-DNDEBUG;-ffunction-sections;-fdata-sections>"
    "$<$<CONFIG:MinSizeRel>:-Os;-DNDEBUG;-ffunction-sections;-fdata-sections>"
  )
  target_link_options(Slurpwave PRIVATE
    "$<$<CONFIG:Release>:-Wl,--gc-sections;-s>"
    "$<$<CONFIG:MinSizeRel>:-Wl,--gc-sections;-s>"
  )
endif()

# Link-Time Optimization (IPO/LTO) for smaller & faster Release builds
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported OUTPUT ipo_msg)
if(ipo_supported)
  set_property(TARGET Slurpwave PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
  set_property(TARGET Slurpwave PROPERTY INTERPROCEDURAL_OPTIMIZATION_MINSIZEREL TRUE)
endif()
