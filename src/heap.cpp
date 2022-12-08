#include "heap.h"
#include <iostream>

size_t heap::root() const {
    return 0;
}
size_t heap::leftChild(size_t currentIdx) const {
    return 2 * currentIdx + 1;
}
size_t heap::rightChild(size_t currentIdx) const {
    return 2 * currentIdx + 2;
}
size_t heap::parent(size_t currentIdx) const {
    return (currentIdx - 1) / 2;
}
bool heap::hasAChild(size_t currentIdx) const {
    // returns true if it has a left child bc it's impossible to have just a right child
    return ((currentIdx * 2 + 1) < _elems.size());
}
size_t heap::maxPriorityChild(size_t currentIdx) const {
   if ((currentIdx * 2 + 2) >= _elems.size())
    {
        return currentIdx * 2 + 1;
    }

    return _elems.at(currentIdx * 2 + 1).first < _elems.at(currentIdx * 2 + 2).first ? (currentIdx * 2 + 1) : (currentIdx * 2 + 2);
}
void heap::heapifyDown(size_t currentIdx) {
    if (hasAChild(currentIdx))
    {
        size_t minChildIndex = maxPriorityChild(currentIdx);
        if (_elems.at(minChildIndex).first < _elems.at(currentIdx).first)
        {
            // swap elements until it's in correct place
            std::swap(_elems.at(currentIdx), _elems.at(minChildIndex));
            heapifyDown(minChildIndex);
        }
    }
}
void heap::heapifyUp(size_t currentIdx) {
    if (currentIdx <= root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (_elems[currentIdx].first < _elems[parentIdx].first)
    {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

heap::heap() {

}
heap::heap(const std::vector<std::pair<int, Node*>> &elems) {
    for (unsigned i = 0; i < elems.size(); i++)
    {
        _elems.push_back(elems.at(i));
        // heapifyUp(i);
    }

    for (int i = parent(_elems.size() - 1); i >= 0; i--)
    {
        // cout << "heapifying down element " << i << endl;
        heapifyDown(i);
    }  
}
std::pair<int, Node*> heap::pop() {
    if (_elems.empty())
    {
        return std::pair<int, Node*>();
    }
    else
    {
        std::pair<int, Node*> result = _elems.at(0);
        // swap last element and root
        std::swap(_elems.at(0), _elems.back());
        // remove last element
        _elems.pop_back();

        // call heapifyDown on root
        heapifyDown(0);
        return result;
    }
}
std::pair<int, Node*> heap::peek() const {
    return _elems.at(_elems.size() - 1);
}
void heap::push(const std::pair<int, Node*> &elem) {
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}
void heap::updateElem(const size_t &idx, const std::pair<int, Node*> &elem) {
    // check if it's same element
    if (elem == _elems.at(idx))
    {
        // do nothing
        return;
    }

    // if elem is bigger than current, need to heapify up
    if (elem.first < _elems.at(idx).first)
    {
        _elems.at(idx) = elem;
        heapifyUp(idx);
    }
    else
    { // otherwise heapify down
        _elems.at(idx) = elem;
        heapifyDown(idx);
    }
}
bool heap::empty() const {
    if (_elems.empty())
    {
        return true;
    }

    // if the first element (root) isn't T(), then it's not empty
    return _elems.at(0) == std::pair<int, Node*>();
}
void heap::getElems(std::vector<std::pair<int, Node*>> &heaped) {
    for (size_t i = root(); i < _elems.size(); i++)
    {
        heaped.push_back(_elems[i]);
    }
}