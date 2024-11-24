//
// Created by AlexGrandbell on 24-11-23.
//

#ifndef ASTAR_SERVICE_H
#define ASTAR_SERVICE_H

#include "Node.h"
#include <random>
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_set>

class Service {
public:
    //A*算法的两种估价函数比较
    void eightDigital_AStarWithManhattanDistance();
    void eightDigital_AStarWithNotInPlaceDistance();
    //宽度优先搜索
    void eightDigital_BFS();
    //设置初始状态
    void GetStartState();
private:
    //随机初始状态
    vector<int> startStateNums;

    //多态，根据不同的估价函数选择不同的状态
    int eightDigitalPolymorphic(NineBlockState *state, bool useDFS= false);
};


#endif //ASTAR_SERVICE_H
