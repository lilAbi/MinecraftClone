
#include "core/application.h"
#include <ranges>
#include <iostream>


int main() {
    core::Application application;
    application.Init();
    application.Run();

    return 0;
}
