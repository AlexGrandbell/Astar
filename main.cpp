#include <iostream>
#include "Service.h"

using namespace std;

int main() {
    Service service;
    service.GetStartState(static_cast<unsigned>(time(nullptr)));
    service.AStar();
    service.BFS();
    return 0;
}
