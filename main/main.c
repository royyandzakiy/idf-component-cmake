#include <stdio.h>
#include "hello_component_h.h"
#include "hello_added_component_h.h"
#include "hello_cmake_h.h"

void app_main(void)
{
    hello_component_call();
    hello_added_component_call();
    hello_cmake_call();
}