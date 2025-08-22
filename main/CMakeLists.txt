idf_component_register(
    SRCS 
        "main.c"
    INCLUDE_DIRS 
        ""
)

# idf_component_optional_requires(hello_component)
# idf_component_optional_requires(hello_added_component)

# ---------------------------

# add_subdirectory(hello_cmake)
# target_link_libraries(${COMPONENT_LIB} PUBLIC hello_cmake)