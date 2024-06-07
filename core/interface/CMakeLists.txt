idf_component_register(
                    SRCS "renderer.cpp" "inputer.cpp"
                    INCLUDE_DIRS "."
                    PRIV_REQUIRES esp32_renderer esp32_inputer
                    )
