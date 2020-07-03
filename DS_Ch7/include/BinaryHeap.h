/**
 * @file BinaryHeap.h
 * @author Guorui Wei (313017602@qq.com)
 * @brief 优先级队列的接口和实现
 * @version 0.1
 * @date 2020-07-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef INCLUDE_BINARYHEAP_H_
#define INCLUDE_BINARYHEAP_H_
#include "seqList.h"

namespace Priority_queue
{

    template <typename Comparable>
    class BinaryHeap
    {
    private:
        /**
        * @brief Number of elements in heap
        * 
        */
        size_t current_size_;

        /**
        * @brief The heap array
        * 
        * @details 数据范围[1, current_size]
        */
        List::seqList<Comparable> array_;

        /**
        * @brief Establish heap order property from an arbitrary
        * arrangement of items. 
        * Run in linear time.
        */
        void buildHeap();

        /**
        * @brief Internal method to percolate down in the heap.
        * 
        * @param hole the index at which the percolate begins.
        */
        void percolateDown(size_t hole);

    public:
        /**
        * @brief Construct a new Binary Heap object
        * 
        * @param capacity 容器的初始容量.
        * 
        * @details 数据范围array[1] ~ array[capacity]
        */
        explicit BinaryHeap(size_t capacity = 100);

        /**
        * @brief Construct a new Binary Heap object
        * 
        * @param items 容器的初值来源
        */
        explicit BinaryHeap(const List::seqList<Comparable> &items);

        /**
        * @brief Destroy the Binary Heap object
        * 
        */
        ~BinaryHeap() = default;

        /**
        * @brief 判队空
        * 
        * @return true 空
        * @return false 非空
        */
        bool empty() const;

        /**
        * @brief 返回队头元素值
        * 
        * @return const Comparable& 队头元素（最小）
        */
        const Comparable &top() const;

        /**
        * @brief 队头元素出队
        * 
        */
        void pop();

        /**
         * @brief 队头元素出队，保存在minItem指向的空间中
         * 
         * @param minItem 指向元素类型的指针
         */
        void pop(Comparable *minItem);

        /**
        * @brief 将x入队
        * 
        * @param x 新元素
        */
        void push(const Comparable &x);

        /**
        * @brief 清空队列
        * 
        */
        void clear();
    };

    template <typename Comparable>
    BinaryHeap<Comparable>::BinaryHeap(size_t capacity)
        : current_size_{0}, array_(capacity + 1)
    {
    }

    template <typename Comparable>
    bool BinaryHeap<Comparable>::empty() const
    {
        return !current_size_;
    }

    template <typename Comparable>
    const Comparable &BinaryHeap<Comparable>::top() const
    {
        return array_[1];
    }

    template <typename Comparable>
    void BinaryHeap<Comparable>::push(const Comparable &x)
    {
        size_t hole = ++current_size_;
        array_.push_back(Comparable{}); // 建立hole结点. 可能触发doubleSpace

        // 向上过滤（最小堆）
        // 若x比hole（候选位置）的parent小，则hole上滤一层
        while (hole > 1 && x < array_[hole / 2])
        {
            array_[hole] = array_[hole / 2];
            hole /= 2;
        }
        array_[hole] = x;
    }

    template <typename Comparable>
    BinaryHeap<Comparable>::BinaryHeap(const List::seqList<Comparable> &items)
        : current_size_{items.size()}, array_(items.size() + 11)
    {
        for (size_t i = 0; i < items.size(); ++i)
        {
            array_[i + 1] = items[i];
            array_.resize(items.size() + 1);
        }
        buildHeap();
    }

    template <typename Comparable>
    void BinaryHeap<Comparable>::buildHeap()
    {
        for (size_t i = current_size_ / 2; i > 0; --i)
        {
            percolateDown(i);
        }
    }

    template <typename Comparable>
    void BinaryHeap<Comparable>::percolateDown(size_t hole)
    {
        auto tmp = std::move(array_[hole]);
        size_t child;

        for (; hole * 2 <= current_size_; hole = child)
        {
            // 选出候选位置的最小child
            child = hole * 2;
            if (child < current_size_ && array_[child + 1] < array_[child])
            {
                ++child;
            }
            // 检查是否违反堆性质，若是则下滤一层
            if (tmp > array_[child])
            {
                array_[hole] = std::move(array_[child]);
                continue;
            }
            break;
        }
        array_[hole] = std::move(tmp);
    }

    template <typename Comparable>
    void BinaryHeap<Comparable>::pop()
    {
        array_[1] = std::move(array_[current_size_--]);
        array_.pop_back();
        percolateDown(1);
    }

    template <typename Comparable>
    void BinaryHeap<Comparable>::pop(Comparable *minItem)
    {
        *minItem = std::move(array_[1]);
        array_[1] = std::move(array_[current_size_--]);
        array_.pop_back();
        percolateDown(1);
    }

    template <typename Comparable>
    void BinaryHeap<Comparable>::clear()
    {
        array_.clear();
        current_size_ = 0;
    }

} // namespace Priority_queue

#endif /* INCLUDE_BINARYHEAP_H_ */
