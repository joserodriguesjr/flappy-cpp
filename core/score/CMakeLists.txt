idf_component_register(
                    SRCS "score.cpp"
                    INCLUDE_DIRS "." "../platform"
                    PRIV_REQUIRES cstdio
                    REQUIRES renderer
                    )
