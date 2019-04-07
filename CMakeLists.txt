cmake_minimum_required(VERSION 3.10)
project(table_reader)
set(CMAKE_CXX_STANDARD 11)


set (PROJECT_VERSION_MAJOR 0)
set (PROJECT_VERSION_MINOR 1)

set(ADAPTIVE_THRESHOLD_BLOCK_SIZE       15)
set(ADAPTIVE_THRESHOLD_CONSTANT         -2)
set(POOL_SIZE                           5)
set(BUFFER_CAPACITY                     3)
set(RESIZE_MAX_AREA                     50000)
set(PERCENT_CONFIDENCE_THRESHOLD        5.0)

add_definitions(
        -DADAPTIVE_THRESHOLD_BLOCK_SIZE=${ADAPTIVE_THRESHOLD_BLOCK_SIZE}
        -DADAPTIVE_THRESHOLD_CONSTANT=${ADAPTIVE_THRESHOLD_CONSTANT}
        -DPOOL_SIZE=${POOL_SIZE}
        -DBUFFER_CAPACITY=${BUFFER_CAPACITY}
        -DRESIZE_MAX_AREA=${RESIZE_MAX_AREA}
        -DPERCENT_CONFIDENCE_THRESHOLD=${PERCENT_CONFIDENCE_THRESHOLD}
)

add_executable(table-reader
        src/main.cpp
        src/line_detection/mask.h
        src/generate_table.cpp
        src/generate_table.h
        src/line_detection/image.cpp
        src/line_detection/image.h
        src/line_detection/mask.h
        src/line_detection/mask.cpp
        src/ocr/ocr.cpp
        src/ocr/ocr.h)

set(Tesseract_LIBRARIES tesseract)
set(Leptonica_LIBRARIES lept)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS}, src/line_detection src/ocr)
target_link_libraries( table-reader
        ${Tesseract_LIBRARIES}
        ${Leptonica_LIBRARIES}
        ${OpenCV_LIBS})
