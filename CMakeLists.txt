#Univio Vishal Ahirwar.
#Auto Genrated C++ file by newton CLI
cmake_minimum_required(VERSION 3.1)

project(ChatServer)

set(CMAKE_CXX_STANDARD 17)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(Threads)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} ./src/main.cc ./src/util.cc)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} Threads::Threads)
