cmake_minimum_required(VERSION 3.19)
project(MyTradingView LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)

qt_standard_project_setup()

include_directories(src)

# Inclure le fichier .ui directement dans qt_add_executable
qt_add_executable(MyTradingView
    WIN32 MACOSX_BUNDLE
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui   # Le chemin correct pour le fichier .ui
)

# Ne pas utiliser qt_wrap_ui ici, cela est pris en charge automatiquement par qt_add_executable

qt_add_translations(
    TARGETS MyTradingView
    TS_FILES MyTradingView_fr_FR.ts
)

target_link_libraries(MyTradingView
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS MyTradingView
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET MyTradingView
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
