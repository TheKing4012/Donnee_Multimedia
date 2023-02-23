cmake_minimum_required(VERSION 3.24)
project(TP1)

set(CMAKE_CXX_STANDARD 17)

add_executable(TP1 main.cpp blur.cpp TP1/test_couleur.cpp TP4/test_grey.cpp TP1/seuil3parties.cpp TP1/histo.cpp TP1/seuilCouleur.cpp TP5/RGBtoY.c)
