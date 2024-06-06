# idf_component_register(SRCS "main.c"
#                     INCLUDE_DIRS ".")
idf_component_register(SRCS "main.cpp" "core/source/scenario/scenario.cpp" "core/source/game/game.cpp" "core/source/pipe/pipe.cpp" "core/source/player/player.cpp" "core/source/score/score.cpp" "core/source/sprite/sprite.cpp"
                    # PRIV_REQUIRES spi_flash
                    INCLUDE_DIRS "." "./core/source" "../platform"
                    )
