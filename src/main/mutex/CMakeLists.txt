cmake_minimum_required(VERSION 3.10)
project(mutex)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/mutex)

find_package(Threads)

add_executable(0.test_main 0.test_main.cc)
target_link_libraries(0.test_main
    PRIVATE
        Threads::Threads
)

add_executable(0.race_condition 0.race_condition.cc)
target_link_libraries(0.race_condition
    PRIVATE
        Threads::Threads
)

add_executable(1.no_lock 1.no_lock.cc)
target_link_libraries(1.no_lock
    PRIVATE
        Threads::Threads
)

add_executable(2.lock_unlock 2.lock_unlock.cc)
target_link_libraries(2.lock_unlock
    PRIVATE
        Threads::Threads
)