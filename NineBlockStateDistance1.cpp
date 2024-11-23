//
// Created by AlexGrandbell on 24-11-23.
//

#include "NineBlockStateDistance1.h"

//计算当前状态与目标状态的距离（估价函数1-曼哈顿距离）
//曼哈顿距离：每个数码到正确位置的距离之和
int NineBlockStateDistance1::distance() const {
    int distance = 0;
    for (int i = 0; i < 9; i++) {
        if (stateArray[i] != 0) {
            int x = i / 3;
            int y = i % 3;
            int targetX = 0;
            int targetY = 0;
            for (int j = 0; j < 9; j++) {
                if (stateArray[i] == targetState[j]) {
                    targetX = j / 3;
                    targetY = j % 3;
                    break;
                }
            }
            distance += abs(x - targetX) + abs(y - targetY);
        }
    }
    return distance;
}