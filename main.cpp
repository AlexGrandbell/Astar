#include <iostream>
#include "Service.h"

using namespace std;

int main() {
    Service service;
    service.GetStartState();
    service.eightDigital_AStarWithManhattanDistance();
    service.eightDigital_AStarWithNotInPlaceDistance();
    service.eightDigital_BFS();
    return 0;
}
