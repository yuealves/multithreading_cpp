cmake_minimum_required(VERSION 3.10)
project(conditional_variable)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/conditional_variable)

find_package(Threads)

add_executable(0.producer_consumer_lock 0.producer_consumer_lock.cc)
target_link_libraries(0.producer_consumer_lock
    PRIVATE
        Threads::Threads
)

add_executable(1.producer_consumer_conditional_var 1.producer_consumer_conditional_var.cc)
target_link_libraries(1.producer_consumer_conditional_var
    PRIVATE
        Threads::Threads
)


add_executable(2.cv_simple_demo 2.cv_simple_demo.cc)
target_link_libraries(2.cv_simple_demo
    PRIVATE
        Threads::Threads
)