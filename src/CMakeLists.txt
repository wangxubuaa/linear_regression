cmake_minimum_required(VERSION 3.10)
PROJECT(STLEncrption)
set(CMAKE_CXX_STANDARD 11)

if (UNIX AND NOT APPLE)
    set (LINUX TRUE)

endif()

# Find VTK.
#set (VTK_DIR "/Users/Ryan/Documents/Packages/VTK-8.1.1/VTK-build/")

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

# Find ITK.
#set (ITK_DIR "/Users/Ryan/Documents/Packages/InsightToolkit-4.13.1/ITK-build/lib")
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

# Vtk-dicom add by slj
find_package(DICOM QUIET)
if(DICOM_FOUND)
    include(${DICOM_USE_FILE})
endif()
set(VTK_DICOM_LIBRARIES vtkDICOM)

# Find OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Find OpenGL
find_package( OpenGL REQUIRED )
include_directories( ${OPENGL_INCLUDE_DIRS} )

# Instruct CMake to run moc, rcc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(QT_CMAKE_DIR /Users/Ryan/Documents/Packages/Qt5.11.2/5.11.2/gcc_64/include/cmake)
#list(APPEND CMAKE_MODULE_PATH ${QT_CMAKE_DIR}/Qt5)
#list(APPEND CMAKE_MODULE_PATH ${QT_CMAKE_DIR}/Qt5Xml)
#list(APPEND CMAKE_MODULE_PATH ${QT_CMAKE_DIR}/Qt5Core)
if (LINUX)
    MESSAGE(STATUS "detected as linux!")
    set(CMAKE_FRAMEWORK_PATH  ${CMAKE_FRAMEWORK_PATH} "/Users/Ryan/Documents/Packages/Qt5.11.2/5.11.2/gcc_64/lib/cmake")
    MESSAGE(${CMAKE_FRAMEWORK_PATH})
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/Users/Ryan/Documents/Packages/Qt5.11.2/5.11.2/gcc_64/lib/cmake")
    MESSAGE(${CMAKE_PREFIX_PATH})
    find_package(Qt5Widgets REQUIRED QUIET PATHS /Users/Ryan/Documents/Packages/Qt5.11.2/5.11.2/gcc_64/include)
    find_package(Qt5Core PATHS /Users/Ryan/Documents/Packages/Qt5.11.2/5.11.2/gcc_64/include)
    find_package(Qt5Gui PATHS /Users/Ryan//Documents/Packages/Qt5.11.2/5.11.2/gcc_64/include)
    find_package(Qt5Sql PATHS /Users/Ryan/Documents/Packages/Qt5.11.2/5.11.2/gcc_64/include)
    find_package(Qt5Xml PATHS /Users/Ryan/Documents/Packages/Qt5.11.2/5.11.2/gcc_64/include)
    find_package(Qt5Xml REQUIRED)
    find_package(Qt5PrintSupport REQUIRED)
    #find_package(Qt5OpenGL PATHS /home/lwv/Documents/AIPlanner/Packages/Qt5.11.2/5.11.2/gcc_64/include)
    #find_package(Qt5Declarative PATHS /home/lwv/Documents/AIPlanner/Packages/Qt5.11.2/5.11.2/gcc_64/include)
    #find_package(Qt5MacExtras PATHS /home/lwv/Documents/AIPlanner/Packages/Qt5.11.2/5.11.2/gcc_64/include)

else()
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/Users/Ryan/Documents/Packages/Qt5.11.2/5.11.2/clang_64/lib/cmake")
    find_package(Qt5Widgets REQUIRED QUIET)
    find_package(Qt5Core)
    find_package(Qt5Gui)
    find_package(Qt5Sql)
    find_package(Qt5Xml)
    find_package(Qt5PrintSupport REQUIRED)
    #find_package(Qt5OpenGL)
    #find_package(Qt5Declarative)
    #find_package(Qt5MacExtras)
endif()


include_directories( ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/ui ${Qt5Xml_INCLUDE_DIRS} ${Qt5PrintSupport_INCLUDE_DIRS})
#[[
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/ui cppPythonInterface/python/include)
add_subdirectory(cppPythonInterface)
]]

file(GLOB UI_FILES **/*.ui ui/InfoWindows/*.ui ui/login/*.ui)
file(GLOB QT_WRAP **/*.h ui/InfoWindows/*.h ui/login/*.h)
file(GLOB CPP_FILES **/*.cpp ui/InfoWindows/*.cpp ui/login/*.cpp)

qt5_wrap_ui(UISrcs ${UI_FILES})

#add_executable(STLEncrption ${CPP_FILES} ${UISrcs} ${QT_WRAP})

add_library(STLEncrptionLib ${CPP_FILES} ${UISrcs} ${QT_WRAP})

target_link_libraries(STLEncrptionLib ${VTK_LIBRARIES} ${ITK_LIBRARIES} ${OpenCV_LIBS} ${OPENGL_LIBRARIES} ${VTK_DICOM_LIBRARIES} ${Qt5Xml_LIBRARIES} ${Qt5PrintSupport_LIBRARIES})
add_executable(STLEncrption MACOSX_BUNDLE main.cpp)
qt5_use_modules(STLEncrption Core Gui Widgets Xml PrintSupport)

#target_link_libraries(STLEncrption ${Glue} ${VTK_LIBRARIES}${ITK_LIBRARIES})
add_dependencies(STLEncrption STLEncrptionLib)
#add_dependencies(STLEncrption cppPythonLib)
#target_link_libraries(STLEncrption STLEncrptionLib cppPythonLib)
target_link_libraries(STLEncrption STLEncrptionLib)
