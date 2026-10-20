cmake_minimum_required(VERSION 3.21)
project(SmartClickCorrector VERSION 1.0.0)

# Busca el SDK de Geode en tu sistema
find_package(Geode REQUIRED)

# Define tu mod y los archivos de código fuente que usará
add_geode_mod(SmartClickCorrector
    main.cpp
)
