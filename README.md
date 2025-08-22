if using ESP IDF CMake ecosystem (extension of Pure CMake), it is recommended not to use add_subdirectory()

`main/CMakeLists.txt` Pure CMake version

```
add_subdirectory(hello_me)
target_link_libraries(${COMPONENT_LIB} PUBLIC hello_me)
```

`main/CMakeLists.txt` IDF version

```
idf_component_register(
    SRCS 
        "main.cpp"
    INCLUDE_DIRS 
        ""
    PRIV_REQUIRES 
        hello_me
)
```

or

```
idf_component_optional_requires(hello_me)
```

using the second IDF way, we can still use #if conditionals from CONFIG_

`main/hello_me/CMakeLists.txt` Pure CMake version

```
add_library(hello_me STATIC src/hello_me.c)
target_include_directories(hello_me PUBLIC "include")
```

`main/hello_me/CMakeLists.txt` IDF version

```
idf_component_register(
    SRCS "src/hello_me.c"           # Source files
    INCLUDE_DIRS "include"          # Public header directories
    REQUIRES ""                     # Dependencies (empty for now)
)
```