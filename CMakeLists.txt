cmake_minimum_required(VERSION 3.24)
project(TP1)

set(CMAKE_CXX_STANDARD 17)

add_executable(TP1 main.cpp blur.cpp test_couleur.cpp test_grey.cpp seuil3parties.cpp histo.cpp seuilCouleur.cpp)
