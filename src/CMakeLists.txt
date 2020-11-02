cmake_minimum_required(VERSION 3.10)
project(main)

find_package(Threads)

add_executable(0.create_two_threads main/0.create_two_threads.cc)
target_link_libraries(0.create_two_threads
    PRIVATE
        Threads::Threads
)

add_executable(1.vector_of_threads main/1.vector_of_threads.cc)
target_link_libraries(1.vector_of_threads
    PRIVATE
        Threads::Threads
)

add_executable(2.functors main/2.functors.cc)
target_link_libraries(2.functors
    PRIVATE
        Threads::Threads
)

add_executable(3.lambda_threads main/3.lambda_threads.cc)
target_link_libraries(3.lambda_threads
    PRIVATE
        Threads::Threads
)

add_executable(4.async main/4.async.cc)
target_link_libraries(4.async
    PRIVATE
        Threads::Threads
)

add_executable(5.async_lambda main/5.async_lambda.cc)
target_link_libraries(5.async_lambda
    PRIVATE
        Threads::Threads
)

add_executable(6.number_of_cores main/6.number_of_cores.cc)
target_link_libraries(6.number_of_cores
    PRIVATE
        Threads::Threads
)
add_subdirectory(main/mutex)