add_executable(flappyBird
    main.cpp

    objects/Bird.cpp
    objects/Pipe.cpp
    objects/PipeManager.cpp
    objects/PipePair.cpp

    states/BaseState.cpp
    states/CountdownState.cpp
    states/HighScoreState.cpp
    states/LostState.cpp
    states/MenuState.cpp
    states/PauseState.cpp
    states/PlayState.cpp
    states/StateMachine.cpp

    utils/gamefont.cpp
)

target_include_directories(flappyBird
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/libs/SFML/include
)

target_link_directories(flappyBird
    PRIVATE
        ${CMAKE_SOURCE_DIR}/libs/SFML/lib
)

target_link_libraries(flappyBird
    PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
)

add_custom_command(TARGET flappyBird
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Running flappyBird..."
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/flappyBird
    COMMAND "DYLD_LIBRARY_PATH=libs/SFML/lib ./build/src/flappyBird"
)
