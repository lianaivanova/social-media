cmake_minimum_required(VERSION 3.15)
project(SocialMedia)

set(CMAKE_CXX_STANDARD 14)

add_executable(SocialMedia main.cpp User.cpp User.h Graph.cpp Graph.h SocialMedia.cpp SocialMedia.h SocialMediaOperations.cpp SocialMediaOperations.h Type.h StreamServices.cpp StreamServices.h GraphOperations.cpp GraphOperations.h QuickSortImpl.h)