//
// Created by AlexGrandbell on 24-11-23.
//

#ifndef ASTAR_NINEBLOCKSTATE_H
#define ASTAR_NINEBLOCKSTATE_H
#include <iostream>
#include <vector>

using namespace std;

//一个九宫格，空以0代替
//虚类
class NineBlockState {
public:
    //9个数字的状态数组vector
    vector<int> stateArray;

    //空格位置
    int x, y;
    //目标状态
    vector<int> targetState;
    vector<int> defaultTargetState = {1, 2, 3, 8, 0, 4, 7, 6, 5};//修改这个为默认的最终状态
    vector<int> defaultStartState = {2, 8, 3, 1, 6, 4, 7, 0, 5};//修改这个为默认的初始状态

    //打印当、设置前状态
    void printState();

    //移动空格
    bool canMoveUp();
    void moveUp();
    bool canMoveDown();
    void moveDown();
    bool canMoveLeft();
    void moveLeft();
    bool canMoveRight();
    void moveRight();

    //虚函数，计算当前状态与目标状态的距离（估价函数）
    virtual int distance() const = 0;
    virtual NineBlockState* clone() const = 0;

    //判断是否到达目标状态
    bool isTarget();

    //构造函数,需要传入一个状态
    NineBlockState(vector<int> state,vector<int> targetState);
    NineBlockState(vector<int> state);
    NineBlockState();

    //重载等号运算符，需要数组完全一样
    bool operator==(const NineBlockState &b) const {
        return stateArray == b.stateArray;
    }
};

#endif //ASTAR_NINEBLOCKSTATE_H
