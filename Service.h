//
// Created by AlexGrandbell on 24-11-23.
//

#ifndef ASTAR_SERVICE_H
#define ASTAR_SERVICE_H

#include "NineBlockStateDistance1.h"
#include "NineBlockStateDistance2.h"
#include "Node.h"
//优先队列
#include <random>
#include <algorithm>

class Service {
public:
    //A*算法的两种估价函数比较
    static void AStar();
    //宽度优先搜索
    static void BFS();
private:
    //估价函数1
    static int distance1(NineBlockStateDistance1 state);
    //估价函数2
    static int distance2(NineBlockStateDistance2 state);
    //多态，根据不同的估价函数选择不同的状态
    static int distance(NineBlockState *state);
    //随机初始状态
    static vector<int> startState();
};


#endif //ASTAR_SERVICE_H
