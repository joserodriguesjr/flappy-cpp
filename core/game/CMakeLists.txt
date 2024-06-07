idf_component_register(
                    SRCS "game.cpp"
                    INCLUDE_DIRS "." "../platform"
                    PRIV_REQUIRES pipe player score
                    REQUIRES renderer
                    )
