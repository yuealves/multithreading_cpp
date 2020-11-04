cmake_minimum_required(VERSION 3.10)
project(mutex)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/mutex)

find_package(Threads)

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

add_executable(3.lock_guard 3.0.lock_guard.cc)
target_link_libraries(3.lock_guard
    PRIVATE
        Threads::Threads
)

add_executable(3.mutex_seq_cst 3.1.mutex_seq_cst.cc)
target_link_libraries(3.mutex_seq_cst
    PRIVATE
        Threads::Threads
)

add_executable(3.test_main 3.2.test_main.cc)
target_link_libraries(3.test_main
    PRIVATE
        Threads::Threads
)

add_executable(4.unique_lock 4.unique_lock.cc)
target_link_libraries(4.unique_lock
    PRIVATE
        Threads::Threads
)

add_executable(5.shared_mutex 5.shared_mutex.cc)
target_link_libraries(5.shared_mutex
    PRIVATE
        Threads::Threads
)

add_executable(6.lock_guard_multiple_mutex 6.lock_guard_multiple_mutex.cc)
target_link_libraries(6.lock_guard_multiple_mutex
    PRIVATE
        Threads::Threads
)