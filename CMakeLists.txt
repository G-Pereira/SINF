cmake_minimum_required(VERSION 2.8)
project(SINF)

find_package (Threads REQUIRED)

add_executable(SINF src/main.cpp
        src/Database.cpp src/Database.h
        src/Config.cpp src/Config.h
        src/Mote.cpp src/Mote.h
        src/Sensor.cpp src/Sensor.h
        src/Room.cpp src/Room.h
        src/User.cpp src/User.h
        src/Historic.cpp src/Historic.h
        src/Actuator.cpp src/Actuator.h)

target_link_libraries (SINF m ${CMAKE_THREAD_LIBS_INIT} pq)