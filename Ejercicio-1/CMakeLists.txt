# Versión de CMake, campo requerido
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(Ejercicio3)

# Definir el estandard de C++
set(CMAKE_CXX_STANDARD 20)

# Los archivos fuente todos juntos
file(GLOB SOURCES main.cpp src/*.cpp)

# Crear el ejecutable
add_executable(projectExe ${SOURCES})

# Indica los directorios de las librerías y headers
target_include_directories(projectExe PRIVATE ${CMAKE_SOURCE_DIR}/include)

#Warnings de compilación
target_compile_options(projectExe PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# Especifica la carpeta donde se creara el ejecutable
set_target_properties(projectExe PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

add_custom_target(run
    COMMAND projectExe
    DEPENDS projectExe
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

add_custom_target(cleandata
    COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_BINARY_DIR}/datapokedex.bin
    COMMENT "Borrando build/datapokedex.bin"
)
