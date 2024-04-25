add_library(polynomial-lib STATIC polynomial.cpp polynomial.h)
add_executable(polynomial main.cpp)
target_link_libraries(polynomial polynomial-lib)