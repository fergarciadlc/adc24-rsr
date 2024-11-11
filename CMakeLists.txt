# Minimum CMake version for compatibility with JUCE
cmake_minimum_required(VERSION 3.21)

# Plugin name and version
file(READ "plugin.cfg" CONFIG_CONTENT)

# Using regular expressions to extract values without newline characters
string(REGEX MATCH "PLUGIN_NAME=([^\n]*)" _ ${CONFIG_CONTENT})
set(PROJECT_NAME ${CMAKE_MATCH_1})

string(REGEX MATCH "VERSION=([^\n]*)" _ ${CONFIG_CONTENT})
set(CURRENT_VERSION ${CMAKE_MATCH_1})

string(REGEX MATCH "CODE=([^\n]*)" _ ${CONFIG_CONTENT})
set(CURRENT_PLUGIN_CODE ${CMAKE_MATCH_1})

message(STATUS "Plugin Name: ${PROJECT_NAME}")
message(STATUS "Version: ${CURRENT_VERSION}")
message(STATUS "Plugin Code: ${CURRENT_PLUGIN_CODE}")

# Plugin formats: Change or add formats as needed (VST3, AU, Standalone, etc.)
set(FORMATS VST3 AU)

# JUCE Fetch from GitHub
include(FetchContent)
FetchContent_Declare(JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG origin/master
)
FetchContent_MakeAvailable(JUCE)

# JUCE-specific configuration: Plugin properties
juce_add_plugin(${PROJECT_NAME}
    COMPANY_NAME "Ear Candy Technologies"
    VERSION ${CURRENT_VERSION}
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE ECTS
    PLUGIN_CODE TZ01
    FORMATS "${FORMATS}"
    PRODUCT_NAME "${PROJECT_NAME}"
    PLUGIN_CODE "${CURRENT_PLUGIN_CODE}"
)

# Platform-specific settings for macOS (adjust deployment target and architecture as needed)
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE STRING "Minimum macOS version" FORCE)
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
endif()

# Define the source files for the plugin
set(SourceFiles
    Source/PluginEditor.cpp
    Source/PluginEditor.h
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
)

target_sources(${PROJECT_NAME} PRIVATE ${SourceFiles})
juce_generate_juce_header(${PROJECT_NAME})

# Set the C++ standard
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Link JUCE modules to the project
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_plugin_client
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_core
    juce::juce_data_structures
    juce::juce_dsp
    juce::juce_events
    juce::juce_graphics
    juce::juce_gui_basics
    juce::juce_gui_extra
)

# Optional: organize source files in IDEs
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Source PREFIX "Source" FILES ${SourceFiles})

# Set platform-specific compile definitions
if(MSVC)
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE
        JUCE_VST3_CAN_REPLACE_VST2=0
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE
        JUCE_VST3_CAN_REPLACE_VST2=0
    )
endif()
