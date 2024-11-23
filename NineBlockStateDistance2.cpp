//
// Created by AlexGrandbell on 24-11-23.
//

#include "NineBlockStateDistance2.h"


//计算当前状态与目标状态的距离（估价函数2-不在位的数码个数）
int NineBlockStateDistance2::distance() const {
    int distance = 0;
    for (int i = 0; i < 9; i++) {
        if (stateArray[i] != targetState[i]) {
            distance++;
        }
    }
    return distance;
}
