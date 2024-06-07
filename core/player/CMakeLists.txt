idf_component_register(
                    SRCS "player.cpp"
                    INCLUDE_DIRS "." "../platform"
                    PRIV_REQUIRES game scenario sprite
                    REQUIRES renderer inputer
                    )
