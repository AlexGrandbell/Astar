//
// Created by AlexGrandbell on 24-11-23.
//

#ifndef ASTAR_NINEBLOCKSTATEDISTANCE2_H
#define ASTAR_NINEBLOCKSTATEDISTANCE2_H

#include "NineBlockState.h"

class NineBlockStateDistance2 : public NineBlockState{
public:
    //估价函数2，输出每一步扩展节点、选择过程以及最短路径具体步骤
    int distance() const override;
    //构造函数
    NineBlockStateDistance2(vector<int> state, vector<int> targetState) : NineBlockState(state, targetState) {}
    NineBlockStateDistance2(vector<int> state) : NineBlockState(state) {}
    NineBlockStateDistance2() : NineBlockState() {}
    //克隆函数
    NineBlockStateDistance2* clone() const override {
        return new NineBlockStateDistance2(this->stateArray);
    }
};


#endif //ASTAR_NINEBLOCKSTATEDISTANCE2_H
