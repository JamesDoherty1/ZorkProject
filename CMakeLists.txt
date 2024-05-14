cmake_minimum_required(VERSION 3.5)

project(ZorkProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ZorkProject
        Player.cpp Player.h Command.cpp Command.h CommandWords.cpp CommandWords.h item.cpp item.h Parser.cpp Parser.h Room.cpp Room.h ZorkUL.cpp ZorkUL.h BoxingRoom.cpp BoxingRoom.h
        Attribute.cpp
        Attribute.h
        EntranceRoom.cpp
        EntranceRoom.h
        StartFinish.cpp
        StartFinish.h
        GameException.h
        GameException.cpp
)

include(GNUInstallDirs)
install(TARGETS ZorkProject
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)