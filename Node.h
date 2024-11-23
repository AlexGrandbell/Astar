//
// Created by AlexGrandbell on 24-11-23.
//

#ifndef ASTAR_NODE_H
#define ASTAR_NODE_H

#include "NineBlockStateDistance1.h"
#include "NineBlockStateDistance2.h"

//树节点,使用虚类NineBlockState作为节点的状态，实现时使用其两个子类
class Node {
public:
    //节点的状态
    NineBlockState *state;

//    //重载赋值运算符
//    Node& operator=(const Node& other) {
////        if (this == &other) {
////            return *this;
////        }
////        delete this->state;
//        this->state = other.state->clone();
//        this->depth = other.depth;
//        this->parent = other.parent;
//        return *this;
//    }
    //父节点
    Node *parent;
    //深度
    int depth;

    //当前价值f=g+h
    int f() const{
        return depth + state->distance();
    }
    //构造函数
    Node(NineBlockState *state, Node *parent, int depth) : state(state), parent(parent), depth(depth) {}
    //构造函数
    Node(Node* other) {
        //执行深拷贝
        this->state = other->state->clone();
        this->depth = other->depth;
        this->parent = other->parent;
    }
    //默认构造函数
    Node() = default;
//    //析构函数
//    ~Node() {
//        delete state;
//    }
    //重载小于号运算符，用于优先队列排序
    bool operator<(const Node &b) const {
        return f() < b.f();
    }
    //重载等号运算符，需要数组完全一样
    bool operator==(const Node &b) const{
        return this->state->stateArray == b.state->stateArray;
    }

    //是否是目标状态
    bool isTarget() const {
        return state->isTarget();
    }
    //输出当前状态
    void printState() const {
        state->printState();
    }
    //移动空格
    void moveUp() {
        state->moveUp();
    }
    void moveDown() {
        state->moveDown();
    }
    void moveLeft() {
        state->moveLeft();
    }
    void moveRight() {
        state->moveRight();
    }
    //判断是否可以移动
    bool canMoveUp() {
        return state->canMoveUp();
    }
    bool canMoveDown() {
        return state->canMoveDown();
    }
    bool canMoveLeft() {
        return state->canMoveLeft();
    }
    bool canMoveRight() {
        return state->canMoveRight();
    }

    //打印路径
    void printPath() {
        if (parent != nullptr) {
            parent->printPath();
        }
        printState();
        cout << endl;
    }
};


#endif //ASTAR_NODE_H
