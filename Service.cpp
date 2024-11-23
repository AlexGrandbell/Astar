//
// Created by AlexGrandbell on 24-11-23.
//

#include "Service.h"

//A*算法的两种估价函数比较
void Service::AStar() {
    //随机初始状态作为两种估价函数的比较
    vector<int> state = startState();

    //估价函数1
    cout << "估价函数1：" << endl;
    if ( distance1(NineBlockStateDistance1(state)) == -1) {
        cout << "无解" << endl;
    }
    //估价函数2
    cout << "估价函数2：" << endl;
    if ( distance2(NineBlockStateDistance2(state)) == -1) {
        cout << "无解" << endl;
    }
}

//估价函数1
int Service::distance1(NineBlockStateDistance1 state) {
    return distance(&state);
}

//估价函数2
int Service::distance2(NineBlockStateDistance2 state) {
    return distance(&state);
}

//多态，根据不同的估价函数选择不同的状态
int Service::distance(NineBlockState *state) {
    //优先队列
    vector<Node*> open;
    //已经访问过的节点
    vector<Node*> close;
    //初始节点
    Node* node = new Node(state, 0, 0);
    //初始状态
    open.push_back(node);
    //最大循环次数，防止无解死循环
//    const int MAX_ITERATIONS = 2000;
//    int iterations = 0;
    while (!open.empty()) {
        // 检查是否超过最大循环次数
//        if (iterations++ > MAX_ITERATIONS) {
//            cout << "陷入死循环，退出" << endl;
//            // 释放所有节点内存
//            for (Node* n : open) {
//                delete n;
//            }
//            for (Node* n : close) {
//                delete n;
//            }
//            return -1;
//        }
        //取出open表中的第一个节点
        Node* nodeNow = open[0];
        //如果当前状态是目标状态
        if(nodeNow->isTarget()){
            int dp=nodeNow->depth;
            cout << "最短路径长度：" << dp << endl;
            cout << "具体步骤：" << endl;
            nodeNow->printPath();
            //释放所有节点内存
            for (Node* n : open) {
                delete n;
            }
            for (Node* n : close) {
                delete n;
            }
            return dp;
        }
        //扩展节点，如果既不在open表中也不在close表中则加入open表，否则不加入
        //四个方向都生成并判断
        if (nodeNow->canMoveUp()) {
            Node* nodeUp = new Node(nodeNow);
            nodeUp->moveUp();
            nodeUp->depth++;
            nodeUp->parent = nodeNow;
            if (find(open.begin(), open.end(), nodeUp) == open.end() && find(close.begin(), close.end(), nodeUp) == close.end()) {
                open.push_back(nodeUp);
            } else if (find(open.begin(), open.end(), nodeUp) != open.end()) {
                //如果在open表中，判断是否需要更新
                auto it = find(open.begin(), open.end(), nodeUp);
                if ((*it)->depth > nodeUp->depth) {
                    *it = nodeUp;
                }
            } else {
                //如果在close表中，判断是否需要更新
                auto it = find(close.begin(), close.end(), nodeUp);
                if ((*it)->depth > nodeUp->depth) {
                    close.erase(it);
                    open.push_back(nodeUp);
                }

            }
        }
        if (nodeNow->canMoveDown()) {
            Node* nodeDown = new Node(nodeNow);
            nodeDown->moveDown();
            nodeDown->depth++;
            nodeDown->parent = nodeNow;
            if (find(open.begin(), open.end(), nodeDown) == open.end() && find(close.begin(), close.end(), nodeDown) == close.end()) {
                open.push_back(nodeDown);
            } else if (find(open.begin(), open.end(), nodeDown) != open.end()) {
                //如果在open表中，判断是否需要更新
                auto it = find(open.begin(), open.end(), nodeDown);
                if ((*it)->depth > nodeDown->depth) {
                    *it = nodeDown;
                }
            } else {
                //如果在close表中，判断是否需要更新
                auto it = find(close.begin(), close.end(), nodeDown);
                if ((*it)->depth > nodeDown->depth) {
                    close.erase(it);
                    open.push_back(nodeDown);
                }
            }
        }
        if (nodeNow->canMoveLeft()) {
            Node* nodeLeft = new Node(nodeNow);
            nodeLeft->moveLeft();
            nodeLeft->depth++;
            nodeLeft->parent = nodeNow;
            if (find(open.begin(), open.end(), nodeLeft) == open.end() && find(close.begin(), close.end(), nodeLeft) == close.end()) {
                open.push_back(nodeLeft);
            } else if (find(open.begin(), open.end(), nodeLeft) != open.end()) {
                //如果在open表中，判断是否需要更新
                auto it = find(open.begin(), open.end(), nodeLeft);
                if ((*it)->depth > nodeLeft->depth) {
                    *it = nodeLeft;
                }
            } else {
                //如果在close表中，判断是否需要更新
                auto it = find(close.begin(), close.end(), nodeLeft);
                if ((*it)->depth > nodeLeft->depth) {
                    close.erase(it);
                    open.push_back(nodeLeft);
                }
            }
        }
        if (nodeNow->canMoveRight()) {
            Node* nodeRight = new Node(nodeNow);
            nodeRight->moveRight();
            nodeRight->depth++;
            nodeRight->parent = nodeNow;
            if (find(open.begin(), open.end(), nodeRight) == open.end() && find(close.begin(), close.end(), nodeRight) == close.end()) {
                open.push_back(nodeRight);
            } else if (find(open.begin(), open.end(), nodeRight) != open.end()) {
                //如果在open表中，判断是否需要更新
                auto it = find(open.begin(), open.end(), nodeRight);
                if ((*it)->depth > nodeRight->depth) {
                    *it = nodeRight;
                }
            } else {
                //如果在close表中，判断是否需要更新
                auto it = find(close.begin(), close.end(), nodeRight);
                if ((*it)->depth > nodeRight->depth) {
                    close.erase(it);
                    open.push_back(nodeRight);
                }
            }
        }
        //当前节点加入close表
        close.push_back(nodeNow);
        //open表中删除当前节点
        open.erase(open.begin());
        //open表排序
        sort(open.begin(), open.end(), [](Node* a, Node* b) { return *a < *b; });
    }
    //释放所有节点内存
    for (Node* n : open) {
        delete n;
    }
    for (Node* n : close) {
        delete n;
    }
    return -1;
}

//随机初始状态
vector<int> Service::startState() {
    vector<int> state;
    //1手动经典
//    state = {2, 8, 3, 1, 6, 4, 7, 0, 5};

    //2通过答案随机反向移动几步步生成，包有解的
    vector<int> answer = {1, 2, 3, 8, 0, 4, 7, 6, 5};
    state = answer;
    for (int i = 0; i < 10; i++) {
        int index = 0;
        //循环找0
        for (int j = 0; j < 9; j++) {
            if (state[j] == 0) {
                index = j;
                break;
            }
        }
        //随机移动
        int move = rand() % 4;
        if (move == 0) {
            if (index > 2) {
                state[index] = state[index - 3];
                state[index - 3] = 0;
            }
        } else if (move == 1) {
            if (index < 6) {
                state[index] = state[index + 3];
                state[index + 3] = 0;
            }
        } else if (move == 2) {
            if (index % 3 != 0) {
                state[index] = state[index - 1];
                state[index - 1] = 0;
            }
        } else {
            if (index % 3 != 2) {
                state[index] = state[index + 1];
                state[index + 1] = 0;
            }
        }
    }

    //打印
    cout << "初始状态：" << endl;
    for (int i = 0; i < 9; i++) {
        cout << state[i] << " ";
        if (i % 3 == 2) {
            cout << endl;
        }
    }
    return state;
}