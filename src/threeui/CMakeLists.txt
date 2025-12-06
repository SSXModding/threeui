# The abi version
set(THREEUI_ABI_VERSION 0)

add_library(threeui SHARED
    dummy.cpp
)

threeuiTarget(threeui)

# config
configure_file(
    threeui_config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/threeui/threeui_config.h
)

target_include_directories(threeui PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

# Set the .so version based on the version of the ABI
# in theory that means any C ABI breaks will be immediately noticable
set_target_properties(threeui PROPERTIES
    SO_VERSION ${THREEUI_ABI_VERSION}
)

# TODO: Install //include/threeui when installing