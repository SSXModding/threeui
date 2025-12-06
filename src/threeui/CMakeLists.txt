# The abi version
set(THREEUI_ABI_VERSION 1)

add_library(threeui SHARED
    utils/hashname.cpp

    # C ABI - changing anything here in a incompatible way
    # will require a bump of the above THREEUI_ABI_VERSION variable
    capi/inifini.cpp
    capi/hashname.cpp
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

target_link_libraries(threeui PUBLIC
    mco::base
    mco::io
)

# TODO: Install //include/threeui when installing