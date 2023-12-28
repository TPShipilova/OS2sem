cmake_minimum_required(VERSION 3.20)
project(lab5)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab main.cpp AbstractNode.hpp ChildNodeInfo.hpp ZmqUtils.hpp Message.hpp MessageTypes.hpp MessageBuilder.hpp MessageData.hpp SpringBootApplication.hpp)
target_link_libraries(lab zmq)
target_link_libraries(lab pthread)

add_executable(server AbstractNode.hpp ChildNodeInfo.hpp ZmqUtils.hpp Message.hpp MessageTypes.hpp MessageBuilder.hpp MessageData.hpp SpringBootApplication.hpp server.cpp)

target_link_libraries(server zmq)
target_link_libraries(server pthread)