# Versión de CMake, campo requerido
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(Ejercicio3)

# Definir el estandard de C++
set(CMAKE_CXX_STANDARD 20)

# Los archivos fuente todos juntos
file(GLOB SOURCES main.cpp)

# Crear el ejecutable
add_executable(projectExe ${SOURCES})

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