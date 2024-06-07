idf_component_register(
                    SRCS "pipe.cpp"
                    INCLUDE_DIRS "." "../platform"
                    PRIV_REQUIRES game player score
                    REQUIRES renderer
                    )
