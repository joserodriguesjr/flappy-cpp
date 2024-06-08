# TODO: use espressif component structure (not working rn)

idf_component_register(
                    SRCS "main.cpp" 
                    "../core/game/game.cpp"
                    "../core/pipe/pipe.cpp"
                    "../core/player/player.cpp"
                    "../core/scenario/scenario.cpp"
                    "../core/score/score.cpp"
                    "../core/sprite/sprite.cpp"
                    "../core/interface/renderer.cpp"
                    "../core/interface/inputer.cpp"
                    INCLUDE_DIRS "../core" "../platform"
                    )
