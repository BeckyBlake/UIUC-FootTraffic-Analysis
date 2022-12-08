#pragma once 
#include "node.h"
#include <vector>

class heap {
public:
    heap();
    heap(const std::vector<std::pair<int, Node*>> &elems);
    std::pair<int, Node*> pop();
    std::pair<int, Node*> peek() const;
    void push(const std::pair<int, Node*> &elem);
    void updateElem(const size_t &idx, const std::pair<int, Node*> &elem);
    bool empty() const;
    void getElems(std::vector<std::pair<int, Node*>> &heaped);
    size_t root() const;

private:
    size_t leftChild(size_t currentIdx) const;
    size_t rightChild(size_t currentIdx) const;
    size_t parent(size_t currentIdx) const;
    bool hasAChild(size_t currentIdx) const;
    size_t maxPriorityChild(size_t currentIdx) const;
    void heapifyDown(size_t currentIdx);
    void heapifyUp(size_t currentIdx);

    std::vector<std::pair<int, Node*>> _elems;
};