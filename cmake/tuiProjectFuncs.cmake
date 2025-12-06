
function(threeuiTarget target)
    mco_target(${target})
    target_include_directories(${target} PUBLIC ${PROJECT_SOURCE_DIR}/include)
endfunction()

# Declares a simple unit test target.
function(threeuiSimpleTest target_name)
    add_executable(${target_name}
        ${target_name}.cpp
    )

    target_link_libraries(${target_name} PRIVATE
        mco::nounit
    )

    bmx2_target(${target_name})
    mco_nounit_add_test(${target_name})
endfunction()
