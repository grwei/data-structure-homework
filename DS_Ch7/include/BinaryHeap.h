/**
 * @file BinaryHeap.h
 * @author Guorui Wei (313017602@qq.com)
 * @brief 优先级队列的接口和实现
 * @version 0.1
 * @date 2020-07-03
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 */

#ifndef INCLUDE_BINARYHEAP_H_
#define INCLUDE_BINARYHEAP_H_
#include "seqList.h"

/**
 * @brief 队列
 * 
 */
namespace Queue
{
    /**
     * @brief Priority queue
     * 
     * Priority queues are a type of container adaptors, specifically designed such that its first element is always the greatest of the elements it contains, according to some strict weak ordering criterion.\
     * This context is similar to a heap, where elements can be inserted at any moment, and only the max heap element can be retrieved (the one at the top in the priority queue).
     * 
     * @tparam Comparable Type of the elements.\
     * Aliased as member type priority_queue::value_type.
     * 
     * @tparam std::less<Comparable> A binary predicate that takes two elements (of type T) as arguments and returns a bool.\
     * The expression comp(a,b), where comp is an object of this type and a and b are elements in the container, shall return true if a is considered to go before b in the strict weak ordering the function defines.\
     * The priority_queue uses this function to maintain the elements sorted in a way that preserves heap properties (i.e., that the element popped is the last according to this strict weak ordering).\
     * This can be a function pointer or a function object, and defaults to less<T>, which returns the same as applying the less-than operator (a<b).\
     * 即：comp(a, b)返回true，当且仅当b的优先级高于a. 故若comp为less，则为最大堆. 
     */
    template <typename Comparable, class Compare = std::less<Comparable>>
    class BinaryHeap
    {
        // Member types
    public:
        typedef size_t size_type;      ///< an unsigned integral type
        typedef Comparable value_type; ///< Type of the elements
        typedef value_type &reference;
        typedef const value_type &const_reference;

        // Data members
    protected:
        /**
        * @brief Number of elements in heap
        * 
        */
        size_type current_size_;

        /**
        * @brief The heap array
        * 
        * @details 数据范围[1, current_size]
        */
        List::seqList<value_type> array_;

        /**
         * @brief function object of type Compare
         * 
         * A binary predicate that takes two elements (of type T) as arguments and returns a bool.\
         * The expression comp(a,b), where comp is an object of this type and a and b are elements in the container, shall return true if a is considered to go before b in the strict weak ordering the function defines.\
         * The priority_queue uses this function to maintain the elements sorted in a way that preserves heap properties (i.e., that the element popped is the last according to this strict weak ordering).\
         * This can be a function pointer or a function object, and defaults to less<T>, which returns the same as applying the less-than operator (a<b).
         * 
         */
        static constexpr Compare comp = Compare{};

        // Member functions
    protected:
        /**
        * @brief Establish heap order property from an arbitrary
        * arrangement of items. 
        * 
        * @note Run in linear time.
        */
        void buildHeap();

        /**
        * @brief Internal method to percolate down in the heap.
        * 
        * @param hole the index at which the percolate begins.
        */
        void percolateDown(size_type hole);

        /**
        * @brief Internal method to percolate up in the heap.
        * 
        * @param hole the index at which the percolate begins.
        */
        void percolateUp(size_type hole);

    public:
        /**
        * @brief Construct a new Binary Heap object
        * 
        * @param capacity 容器的初始容量.
        * @param comp 函数对象（二元谓词）
        * 
        * @details 数据范围array[1] ~ array[capacity]
        */
        explicit BinaryHeap(size_type capacity = 100, const Compare &comp = Compare{});

        /**
        * @brief Construct a new Binary Heap object
        * 
        * @param items 容器的初值来源
        * @param comp 函数对象（二元谓词）
        */
        explicit BinaryHeap(const List::seqList<value_type> &items, const Compare &comp = Compare{});

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
        const_reference top() const;

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
        void push(const_reference x);

        /**
        * @brief 清空队列
        * 
        */
        void clear();

        /**
         * @brief Return size
         * 
         * Returns the number of elements in the priority_queue.\
         * This member function effectively calls member size of the underlying container object.
         * 
         * @return size_type The number of elements in the underlying container.\
         * Member type size_type is an unsigned integral type.
         */
        size_type size() const;

        /**
         * @brief 将二叉堆中元素顺序输出. 
         * 
         * @param out 输出流对象，可以是std::cout，或fout等.
         */
        void print_heap(std::ostream &out) const
        {
            for (size_type i = 1; i <= current_size_; ++i)
                out << array_[i] << ", ";
            out << std::endl;
        }

        /**
         * @brief 将二叉堆中元素顺序插到输出流对象out中. 
         * 
         * @param out 输出流对象，可以是std::cout，或fout等.
         * @param heap 二叉堆对象
         * @return std::ostream& 实参输出流对象的引用
         */
        friend std::ostream &operator<<(std::ostream &out, const BinaryHeap &heap)
        {
            heap.print_heap(out);
            return out;
        }
    };

    template <typename Comparable, class Compare>
    BinaryHeap<Comparable, Compare>::BinaryHeap(size_type capacity, const Compare &_comp)
        : current_size_{0}, array_(capacity + 1)
    {
    }

    template <typename Comparable, class Compare>
    bool BinaryHeap<Comparable, Compare>::empty() const
    {
        return !current_size_;
    }

    template <typename Comparable, class Compare>
    typename BinaryHeap<Comparable, Compare>::const_reference BinaryHeap<Comparable, Compare>::top() const
    {
        return array_[1];
    }

    template <typename Comparable, class Compare>
    void BinaryHeap<Comparable, Compare>::push(const_reference x)
    {
        size_type hole = ++current_size_;
        array_.push_back(Comparable{}); // 在堆尾建立hole结点, 作为初始候选位置。可能触发doubleSpace

        // 向上过滤
        // 若x置于hole（候选位置）中会破坏堆性质，则hole上滤一层
        while (hole > 1 && comp(array_[hole / 2], x))
        {
            array_[hole] = array_[hole / 2];
            hole /= 2;
        }
        array_[hole] = x;
    }

    template <typename Comparable, class Compare>
    BinaryHeap<Comparable, Compare>::BinaryHeap(const List::seqList<Comparable> &items, const Compare &_comp)
        : current_size_{items.size()}, array_(items.size() + 11)
    {
        for (size_type i = 0; i < items.size(); ++i)
        {
            array_[i + 1] = items[i];
            array_.resize(items.size() + 1);
        }
        buildHeap();
    }

    template <typename Comparable, class Compare>
    void BinaryHeap<Comparable, Compare>::buildHeap()
    {
        for (size_type i = current_size_ / 2; i > 0; --i)
        {
            percolateDown(i);
        }
    }

    template <typename Comparable, class Compare>
    void BinaryHeap<Comparable, Compare>::percolateDown(size_type hole)
    {
        auto tmp = std::move(array_[hole]);
        size_type child;

        for (; hole * 2 <= current_size_; hole = child)
        {
            // 选出候选位置的优先级最高的child
            child = hole * 2;
            if (child < current_size_ && comp(array_[child], array_[child + 1]))
            {
                ++child;
            }
            // 检查是否违反堆性质，若是则下滤一层
            if (comp(tmp, array_[child]))
            {
                array_[hole] = std::move(array_[child]);
                continue;
            }
            break;
        }
        array_[hole] = std::move(tmp);
    }

    template <typename Comparable, class Compare>
    void BinaryHeap<Comparable, Compare>::percolateUp(size_type hole)
    {
        value_type tmp = std::move(array_[hole]);

        // 向上过滤
        // 若x置于hole（候选位置）中会破坏堆性质，则hole上滤一层
        while (hole > 1 && comp(array_[hole / 2], tmp))
        {
            array_[hole] = std::move(array_[hole / 2]);
            hole /= 2;
        }
        array_[hole] = std::move(tmp);
    }

    template <typename Comparable, class Compare>
    void BinaryHeap<Comparable, Compare>::pop()
    {
        array_[1] = std::move(array_[current_size_--]);
        array_.pop_back();
        percolateDown(1);
    }

    template <typename Comparable, class Compare>
    void BinaryHeap<Comparable, Compare>::pop(Comparable *minItem)
    {
        *minItem = std::move(array_[1]);
        array_[1] = std::move(array_[current_size_--]);
        array_.pop_back();
        percolateDown(1);
    }

    template <typename Comparable, class Compare>
    void BinaryHeap<Comparable, Compare>::clear()
    {
        array_.clear();
        current_size_ = 0;
    }

    template <typename Comparable, class Compare>
    typename BinaryHeap<Comparable, Compare>::size_type BinaryHeap<Comparable, Compare>::size() const
    {
        return array_.size();
    }

} // namespace Queue

#endif /* INCLUDE_BINARYHEAP_H_ */
