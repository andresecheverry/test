cmake_minimum_required(VERSION 3.3)
project(ClassProject)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
  Addition.cpp
  Calculator_Prompt.cpp
  classify_expressions.cpp
  displayHelp.cpp
  sh_yard.cpp
  Token.cpp
  interpretNegatives.cpp
  Expression.cpp
  Expression_math_add.cpp
  Expression_math_multiply.cpp
  IntegerFactorization.cpp
  Multiplication.cpp
  Process_Expresion.cpp
  SimpleExpresion.cpp
  )

add_executable(Calculator ${SOURCE_FILES})
