cmake_minimum_required(VERSION 3.25)
project(OP)

set(CMAKE_CXX_STANDARD 17)

add_executable(OP main.cpp customer.cpp customer.h commodity.cpp commodity.h commodity_s.cpp commodity_s.h customer_s.cpp customer_s.h information.cpp information.h shopList.cpp shopList.h
        history.cpp
        history.h)
