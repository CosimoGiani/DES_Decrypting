cmake_minimum_required(VERSION 3.17)
project(DES_Decrypting)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
find_package(OpenSSL REQUIRED)

set(SOURCE_FILES main.cpp Decrypter.h Decrypter.cpp Utils.h Utils.cpp)
add_executable(DES_Decrypting ${SOURCE_FILES})
target_link_libraries(DES_Decrypting -lcrypt -lcrypto)