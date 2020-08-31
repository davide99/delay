#ifndef UTILS_MAXFIXEDHEAP_H
#define UTILS_MAXFIXEDHEAP_H

//https://github.com/jimbozhang/fixed-size-priority-queue/blob/master/fixed-size-priority-queue.h

#include <vector>
#include <cstdint>
#include <functional>

namespace Utils {
    template<typename T, std::size_t maxSize, typename Compare = std::less<T>>
    class MaxFixedHeap {
    protected:
        std::vector<T> c;
        Compare cmp;

    public:
        explicit MaxFixedHeap() {
            this->c.reserve(maxSize);
        }

        typename std::vector<T>::iterator begin() {
            return this->c.begin();
        }

        typename std::vector<T>::iterator end() {
            return this->c.end();
        }

        void push(const T &x) {
            if (this->c.size() == maxSize) {
                typename std::vector<T>::iterator iterator_min = std::min_element(this->c.begin(), this->c.end(),
                                                                                  this->cmp);
                if (*iterator_min < x) {
                    *iterator_min = x;
                    std::make_heap(this->c.begin(), this->c.end(), this->cmp);
                }
            } else {
                this->c.push_back(x);
                std::make_heap(this->c.begin(), this->c.end(), this->cmp);
            }
        }

        void clear() {
            c.clear();
        }

        std::vector<T> data() {
            return c;
        }

        [[nodiscard]] inline bool empty() const {
            return c.empty();
        }

        [[nodiscard]] inline size_t size() const {
            return c.size();
        }
    };
}

#endif
