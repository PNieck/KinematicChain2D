#include <simulation/window.hpp>

int main() {
    Window window(600, 400, "Kinematic chain simulation");

    window.RunMessageLoop();

    return 0;
}
