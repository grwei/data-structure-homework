/**
 * @file Set.h
 * @author Guorui Wei (313017602@qq.com)
 * @brief 集合结构
 * @version 0.1
 * @date 2020-07-04
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 */

#ifndef INCLUDE_SET_H_
#define INCLUDE_SET_H_

#include <utility>

/**
 * @brief 集合
 * 
 */
namespace Set
{
    template <class Key_T, class Other_T = Key_T>
    struct Set
    {
        // Member variables
        Key_T key_;     ///c 键值
        Other_T other_; ///c 其他值

        // Member functions
        /**
         * @brief Construct a new Set object
         * 
         * @param key 键值
         * @param other 其他值
         */
        explicit Set(const Key_T &key, const Other_T &other = Other_T{}) : key_{key}, other_{other} {}

        // Non-member function overloads
        /**
         * @brief operator<
         * 
         * @param lhs lhs
         * @param rhs rhs
         * @return true <
         * @return false >=
         */
        friend bool operator<(const Set &lhs, const Set &rhs) { return lhs.key_ < rhs.key_; }

        /**
         * @brief operator>
         * 
         * @param lhs lhs
         * @param rhs rhs
         * @return true >
         * @return false <=
         */
        friend bool operator>(const Set &lhs, const Set &rhs) { return lhs.key_ > rhs.key_; }

        /**
         * @brief operator<=
         * 
         * @param lhs lhs
         * @param rhs rhs
         * @return true <=
         * @return false >
         */
        friend bool operator<=(const Set &lhs, const Set &rhs) { return lhs.key_ <= rhs.key_; }

        /**
         * @brief operator>=
         * 
         * @param lhs lhs
         * @param rhs rhs
         * @return true >=
         * @return false <
         */
        friend bool operator>=(const Set &lhs, const Set &rhs) { return lhs.key_ >= rhs.key_; }

        /**
         * @brief operator==
         * 
         * @param lhs lhs
         * @param rhs rhs
         * @return true ==
         * @return false !
         */
        friend bool operator==(const Set &lhs, const Set &rhs) { return lhs.key_ == rhs.key_; }

        /**
         * @brief operator!=
         * 
         * @param lhs lhs
         * @param rhs rhs
         * @return true !=
         * @return false ==
         */
        friend bool operator!=(const Set &lhs, const Set &rhs) { return lhs.key_ != rhs.key_; }
    };
} // namespace Set

#endif /* INCLUDE_SET_H_ */
