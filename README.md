# ESP-IDF Component Integration Examples

This project demonstrates different approaches to integrate components in ESP-IDF projects using both Pure CMake and ESP-IDF's extended CMake system.

## Project Structure

```
├── components/
│   └── hello_component/
│       ├── include/
│       │   └── hello_component_h.h
│       ├── CMakeLists.txt
│       └── hello_component_src.c
├── main/
│   ├── hello_added_component/
│   │   ├── include/
│   │   │   └── hello_added_component_h.h
│   │   ├── CMakeLists.txt
│   │   └── hello_added_component_src.c
│   ├── hello_cmake/
│   │   ├── include/
│   │   │   └── hello_cmake_h.h
│   │   ├── CMakeLists.txt
│   │   └── hello_cmake_src.c
│   ├── CMakeLists.txt
│   └── main.c
├── .clangd
├── .gitignore
├── CMakeLists.txt
└── README.md
```

## Integration Approaches

### 1. ESP-IDF Component Registration (Recommended)

**Root CMakeLists.txt:**

```cmake
cmake_minimum_required(VERSION 3.5)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# Register additional component directories
set(EXTRA_COMPONENT_DIRS 
    main/hello_added_component
)

project(idf-component-cmake)
```

**Component CMakeLists.txt (IDF Style):**

```cmake
idf_component_register(
    SRCS "hello_component_src.c"   # Source files
    INCLUDE_DIRS "include"         # Public header directories
    REQUIRES ""                    # Component dependencies
)
```

**Main Component CMakeLists.txt (IDF Style):**

```cmake
idf_component_register(
    SRCS "main.c"
    INCLUDE_DIRS ""
    PRIV_REQUIRES 
        hello_component
        hello_added_component
)

# Or using optional requires with CONFIG_ conditionals
idf_component_optional_requires(hello_component)
idf_component_optional_requires(hello_added_component)
```

### 2. Pure CMake Approach (Not Recommended for IDF)

**Component CMakeLists.txt (Pure CMake):**

```cmake
add_library(hello_cmake_lib STATIC hello_cmake_src.c)
target_include_directories(hello_cmake_lib PUBLIC "include")
```

**Main Component CMakeLists.txt (Pure CMake):**

```cmake
add_subdirectory(hello_cmake)
target_link_libraries(${COMPONENT_LIB} PUBLIC hello_cmake_lib)
```

## Key Differences

### ESP-IDF CMake Approach (Recommended)

- **Component Discovery**: Automatic component discovery and registration
- **Dependency Management**: Built-in dependency resolution with REQUIRES and PRIV_REQUIRES
- **Configuration Integration**: Seamless integration with Kconfig system
- **Conditional Inclusion**: Support for `idf_component_optional_requires()` with CONFIG_ macros
- **Build Optimization**: IDF-aware build optimizations and resource management

### Pure CMake Approach

- **Manual Management**: Requires explicit `add_subdirectory()` calls
- **Limited Integration**: Doesn't leverage IDF's component system fully
- **Maintenance Overhead**: More manual configuration needed
- **Not Recommended**: ESP-IDF documentation advises against using `add_subdirectory()` for components

## Best Practices

- **Use IDF Component System**: Prefer `idf_component_register()` over Pure CMake approaches
- **Proper Dependency Declaration**: Use REQUIRES for public dependencies and PRIV_REQUIRES for private ones
- **Conditional Components**: Use `idf_component_optional_requires()` for optional components with `#ifdef CONFIG_*` guards
- **Header Management**: Declare public headers in INCLUDE_DIRS for proper inclusion
- **Component Isolation**: Keep components self-contained with clear interfaces

## Building the Project

```bash
# Set up ESP-IDF environment
source $IDF_PATH/export.sh

# Configure project
idf.py set-target <target>  # esp32, esp32s2, etc.

# Build and flash
idf.py build
idf.py flash monitor
```

## Conditional Component Inclusion Example

```c
#include <stdio.h>
#include "hello_component_h.h"
#include "hello_added_component_h.h"
#include "hello_cmake_h.h"

void app_main(void)
{
    #ifdef CONFIG_HELLO_COMPONENT_ENABLE
    hello_component_call();
    #endif
    
    #ifdef CONFIG_HELLO_ADDED_COMPONENT_ENABLE
    hello_added_component_call();
    #endif
    
    hello_cmake_call();  // Always included (Pure CMake approach)
}
```

This project demonstrates the flexibility of ESP-IDF's component system while showing the recommended practices for component integration in ESP32 projects.