//
// Created by AlexGrandbell on 24-11-23.
//

#include "NineBlockState.h"

void NineBlockState::printState() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << stateArray[i * 3 + j] << " ";
        }
        cout << endl;
    }
}

bool NineBlockState::canMoveUp() {
    return x > 0;
}

void NineBlockState::moveUp() {
    if (canMoveUp()) {
        int temp = stateArray[x * 3 + y];
        stateArray[x * 3 + y] = stateArray[(x - 1) * 3 + y];
        stateArray[(x - 1) * 3 + y] = temp;
        x--;
    }
}

bool NineBlockState::canMoveDown() {
    return x < 2;
}

void NineBlockState::moveDown() {
    if (canMoveDown()) {
        int temp = stateArray[x * 3 + y];
        stateArray[x * 3 + y] = stateArray[x * 3 + (y + 3)];
        stateArray[x * 3 + (y + 3)] = temp;
        x++;
    }
}

bool NineBlockState::canMoveLeft() {
    return y > 0;
}

void NineBlockState::moveLeft() {
    if (canMoveLeft()) {
        int temp = stateArray[x * 3 + y];
        stateArray[x * 3 + y] = stateArray[x * 3 + (y - 1)];
        stateArray[x * 3 + (y - 1)] = temp;
        y--;
    }
}

bool NineBlockState::canMoveRight() {
    return y < 2;
}

void NineBlockState::moveRight() {
    if (canMoveRight()) {
        int temp = stateArray[x * 3 + y];
        stateArray[x * 3 + y] = stateArray[x * 3 + (y + 1)];
        stateArray[x * 3 + (y + 1)] = temp;
        y++;
    }
}

//8数码问题绕一圈算正确位置
bool NineBlockState::isTarget() {
    return stateArray == targetState;
}

NineBlockState::NineBlockState(vector<int> state1, vector<int> targetState1) {
    stateArray=state1;
    for (int i = 0; i < 9; i++) {
        if (stateArray[i] == 0) {
            x = i / 3;
            y = i % 3;
            break;
        }
    }
    targetState=targetState1;
}

NineBlockState::NineBlockState(vector<int> state1) {
    stateArray=state1;
    for (int i = 0; i < 9; i++) {
        if (stateArray[i] == 0) {
            x = i / 3;
            y = i % 3;
            break;
        }
    }
    targetState=defaultTargetState;
}

NineBlockState::NineBlockState() {
    stateArray=defaultStartState;
    for (int i = 0; i < 9; i++) {
        if (stateArray[i] == 0) {
            x = i / 3;
            y = i % 3;
            break;
        }
    }
    targetState=defaultTargetState;
}