cmake_minimum_required(VERSION 3.19)
project(MyTradingView LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets PrintSupport LinguistTools Network Charts)

qt_standard_project_setup()

include_directories(src external/qcustomplot)

qt_add_executable(MyTradingView
    WIN32 MACOSX_BUNDLE
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui
    src/chart/chartmanager.h src/chart/chartmanager.cpp

    src/api/apiclient.h src/api/apiclient.cpp
    src/data/ohlcdata.h src/data/ohlcdata.cpp
    src/data/SymbolsLists.h src/data/SymbolsLists.cpp
    src/data/Symbol.h src/data/Symbol.cpp
    src/data/filemanager.h src/data/filemanager.cpp
    src/chart/CustomChartView.h src/chart/CustomChartView.cpp

)

qt_add_translations(
    TARGETS MyTradingView
    TS_FILES MyTradingView_fr_FR.ts
)

target_link_libraries(MyTradingView
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::PrintSupport
        Qt::Network
        Qt::Charts
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
