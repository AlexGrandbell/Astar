//
// Created by AlexGrandbell on 24-11-24.
//

#ifndef ASTAR_NINEBLOCESTATEFORBFS_H
#define ASTAR_NINEBLOCESTATEFORBFS_H

#include "NineBlockState.h"

class NineBloceStateForBFS: public NineBlockState{
public:
    //估价函数-不需要
    int distance() const override{
        return 0;
    }
    //构造函数
    NineBloceStateForBFS(vector<int> state) : NineBlockState(state) {}
    //克隆函数
    NineBloceStateForBFS* clone() const override {
        return new NineBloceStateForBFS(this->stateArray);
    }
};


#endif //ASTAR_NINEBLOCESTATEFORBFS_H
