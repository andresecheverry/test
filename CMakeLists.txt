cmake_minimum_required(VERSION 3.3)
project(ClassProject)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
  Calculator_Prompt.cpp
  sh_yard.cpp
  Token.cpp
  interpretNegatives.cpp
  )

set(INCLUDE_FILES
  Token.h
  )

add_executable(ShuntingYard ${SOURCE_FILES})
