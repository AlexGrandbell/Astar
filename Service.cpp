//
// Created by AlexGrandbell on 24-11-23.
//

#include "Service.h"


//A*算法的两种估价函数比较
void Service::AStar() {
    //随机初始状态作为两种估价函数的比较
    vector<int> state = startState;

    //估价函数1
    cout << "估价函数1：" << endl;
    if (distance1(NineBlockStateDistance1(state)) == -1) {
        cout << "无解" << endl;
    }
    //估价函数2
    cout << "估价函数2：" << endl;
    if (distance2(NineBlockStateDistance2(state)) == -1) {
        cout << "无解" << endl;
    }
}

void Service::BFS() const {
    cout << "BFS：" << endl;
    class BFSNode {
    public:
        // if dir1 + dir2 == 5, then dir1 is the opposite direction of dir2
        enum Direction {
            NONE, LEFT, UP, DOWN, RIGHT
        };

        Direction FromDirection = NONE;

        // 0 is the start state
        int father{};
        int code{};

        vector<int> state;

        BFSNode() = default;

        explicit BFSNode(const vector<int> &state) : state(state) {
            FromDirection = NONE;
            father = -1;
            code = 0;
        }

        BFSNode(const vector<int> &state, Direction fromDirection, int father, int code) : state(state),
            FromDirection(fromDirection),
            father(father), code(code) {
        }

        bool operator==(const BFSNode &x) const {
            for (int i = 0; i < 9; i++) {
                if (state[i] != x.state[i]) {
                    return false;
                }
            }
            return true;
        }

        //core method
        vector<BFSNode> NextStates() {
            vector<BFSNode> nextStates;
            vector<vector<int> > st;
            //左上下右 (x,y) x is column, y is row
            vector<vector<int> > dirs = {{0, 0}, {-1, 0}, {0, -1}, {0, 1}, {1, 0}};
            int x = 0, y = 0;
            for (int i = 0; i < 3; i++) {
                vector<int> temp;
                for (int j = 0; j < 3; j++) {
                    temp.push_back(state[i * 3 + j]);
                    if (state[i * 3 + j] == 0) {
                        x = j;
                        y = i;
                    }
                }
                st.push_back(temp);
            }
            for (int i = 1; i <= 4; i++) {
                if (i + FromDirection == 5) {
                    continue;
                }
                int newX = x + dirs[i][0], newY = y + dirs[i][1];
                if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) {
                    vector<int> newState;
                    swap(st[y][x], st[newY][newX]);
                    for (int j = 0; j < 3; j++) {
                        for (int k = 0; k < 3; k++) {
                            newState.push_back(st[j][k]);
                        }
                    }
                    nextStates.emplace_back(newState, static_cast<Direction>(i), code, -1);
                    swap(st[y][x], st[newY][newX]);
                }
            }
            return nextStates;
        }
    };
    // hash function for BFSNode
    struct BFSNodeHash {
        size_t operator()(const BFSNode &x) const {
            size_t hash = 0;
            for (int i = 0; i < 9; i++) {
                hash = hash * 10 + x.state[i];
            }
            return hash;
        }
    };
    BFSNode startNode = BFSNode(startState);
    BFSNode finalNode(vector<int>{1, 2, 3, 8, 0, 4, 7, 6, 5});
    // situation that startNode is finalNode
    if (startNode == finalNode) {
        cout << "最短路径长度：" << 0 << endl;
        cout << "具体步骤：" << endl;
        for (int i = 0; i < 9; i++) {
            cout << startNode.state[i] << " ";
            if (i % 3 == 2) {
                cout << endl;
            }
        }
        return;
    }

    queue<BFSNode> qu;
    unordered_set<size_t> visited;
    visited.emplace(BFSNodeHash()(startNode));
    vector<BFSNode> states;
    states.push_back(startNode);
    stack<BFSNode> ans;
    qu.emplace(startNode);
    while (!qu.empty()) {
        auto node = qu.front();
        qu.pop();
        for (auto &nd: node.NextStates()) {
            if (nd == finalNode) {
                ans.emplace(nd);
                BFSNode tempNode = nd;
                while (tempNode.father != -1) {
                    tempNode = states[tempNode.father];
                    ans.emplace(tempNode);
                }
                cout << "最短路径长度：" << ans.size() - 1 << endl;
                cout << "具体步骤：" << endl;
                while (!ans.empty()) {
                    for (int i = 0; i < 9; i++) {
                        cout << ans.top().state[i] << " ";
                        if (i % 3 == 2) {
                            cout << endl;
                        }
                    }
                    cout << endl;
                    ans.pop();
                }
                return;
            } else {
                if (visited.contains(BFSNodeHash()(nd)))
                    continue;
                nd.code = static_cast<int>(states.size());
                visited.emplace(BFSNodeHash()(nd));
                states.push_back(nd);
                qu.emplace(nd);
            }
        }
    }
    cout << "无解" << endl;
}

//随机初始状态
void Service::GetStartState(unsigned seed) {
    srand(seed);
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
    startState = state;
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
    vector<Node *> open;
    //已经访问过的节点
    vector<Node *> close;
    //初始节点
    Node *node = new Node(state, 0, 0);
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
        Node *nodeNow = open[0];
        //如果当前状态是目标状态
        if (nodeNow->isTarget()) {
            int dp = nodeNow->depth;
            cout << "最短路径长度：" << dp << endl;
            cout << "具体步骤：" << endl;
            nodeNow->printPath();
            //释放所有节点内存
            for (Node *n: open) {
                delete n;
            }
            for (Node *n: close) {
                delete n;
            }
            return dp;
        }
        //扩展节点，如果既不在open表中也不在close表中则加入open表，否则不加入
        //四个方向都生成并判断
        if (nodeNow->canMoveUp()) {
            Node *nodeUp = new Node(nodeNow);
            nodeUp->moveUp();
            nodeUp->depth++;
            nodeUp->parent = nodeNow;
            if (find(open.begin(), open.end(), nodeUp) == open.end() && find(close.begin(), close.end(), nodeUp) ==
                close.end()) {
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
            Node *nodeDown = new Node(nodeNow);
            nodeDown->moveDown();
            nodeDown->depth++;
            nodeDown->parent = nodeNow;
            if (find(open.begin(), open.end(), nodeDown) == open.end() && find(close.begin(), close.end(), nodeDown) ==
                close.end()) {
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
            Node *nodeLeft = new Node(nodeNow);
            nodeLeft->moveLeft();
            nodeLeft->depth++;
            nodeLeft->parent = nodeNow;
            if (find(open.begin(), open.end(), nodeLeft) == open.end() && find(close.begin(), close.end(), nodeLeft) ==
                close.end()) {
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
            Node *nodeRight = new Node(nodeNow);
            nodeRight->moveRight();
            nodeRight->depth++;
            nodeRight->parent = nodeNow;
            if (find(open.begin(), open.end(), nodeRight) == open.end() && find(close.begin(), close.end(), nodeRight)
                == close.end()) {
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
        sort(open.begin(), open.end(), [](Node *a, Node *b) { return *a < *b; });
    }
    //释放所有节点内存
    for (Node *n: open) {
        delete n;
    }
    for (Node *n: close) {
        delete n;
    }
    return -1;
}
