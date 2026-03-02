cmake_minimum_required(VERSION 4.0)
project(projekatCLAV)

set(CMAKE_CXX_STANDARD 26)

add_executable(projekatCLAV src/main.cpp
        src/core/CLI.h
        src/core/CLI.cpp
        src/core/Registry.h
        src/core/Registry.cpp
        src/utils/Logger.h
        src/utils/Logger.cpp
        src/utils/Parser.h
        src/utils/Parser.cpp
        src/interfaces/Command.h
        src/commands/Echo.h
        src/commands/Echo.cpp
        src/commands/Time.cpp
        src/commands/Time.h
        src/commands/Date.cpp
        src/commands/Date.h
        src/commands/Touch.cpp
        src/commands/Touch.h
        src/commands/Remove.cpp
        src/commands/Remove.h
        src/commands/WordCount.cpp
        src/commands/WordCount.h
        src/interfaces/BinaryCommand.h
        src/utils/Exception.h
        src/utils/Reader.cpp
        src/utils/Reader.h
)
