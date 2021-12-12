set(headers
    src/qrbits.h
    src/qrcode.h
    src/qrencode.h
)

set(sources
    src/frame.c
    src/qrcode.cpp
    src/qrencode.c
)

set(dependencies
    esp-gui-lib
    TFT_eSPI
)

idf_component_register(
    INCLUDE_DIRS
        src
    SRCS
        ${headers}
        ${sources}
    REQUIRES
        ${dependencies}
)

target_compile_options(${COMPONENT_TARGET}
    PRIVATE
        -fstack-reuse=all
        -fstack-protector-all
        -Wno-unused-function
        -Wno-deprecated-declarations
        -Wno-missing-field-initializers
        -Wno-parentheses
)
