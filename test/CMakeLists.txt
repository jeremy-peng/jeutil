
# threadpool test binary

set(THREADPOOL_TEST "threadpool_test")
add_executable(${THREADPOOL_TEST} test_threadpool.cpp)
target_link_libraries(${THREADPOOL_TEST}  ${PROJECT_NAME})