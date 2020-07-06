/**
 * @file ch8_3.cc
 * @author Guorui Wei (313017602@qq.com)
 * @brief 程序设计题第3题：用operator+,*,/实现存储在数组中的集合的并, 交, 差
 * @version 0.1
 * @date 2020-07-05
 *
 * @copyright Copyright (c) 2020
 *
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 */

#include <algorithm>
#include <cstdlib> /* srand, rand */
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

/**
 * @brief 返回两个非降序vector集合的并集vector
 *
 * @tparam T 元素的类型
 * @param vec1 集合1
 * @param vec2 集合2
 * @return std::vector<T> 集合1和集合2的并
 */
template <class T>
std::vector<T> operator+(const std::vector<T> &vec1,
                         const std::vector<T> &vec2);

/**
 * @brief 返回两个非降序vector集合的交集vector
 *
 * @tparam T 元素的类型
 * @param vec1 集合1
 * @param vec2 集合2
 * @return std::vector<T> 集合1和集合2的交
 */
template <class T>
std::vector<T> operator*(const std::vector<T> &vec1,
                         const std::vector<T> &vec2);

/**
 * @brief 返回两个非降序vector集合的差集vector
 *
 * @tparam T 元素的类型
 * @param vec1 集合1
 * @param vec2 集合2
 * @return std::vector<T> 集合1和集合2的差
 */
template <class T>
std::vector<T> operator-(const std::vector<T> &vec1,
                         const std::vector<T> &vec2);

/**
 * @brief 测试程序
 *
 * @param argc 参数个数
 * @param argv 参数数组
 * @return int 返回值
 * @warning 要求.exe对其所在的目录有读写权限
 * @details 部分测试结果将输出到一个文本文档中
 */
int main(int argc, char const *argv[]) {
  // time
  clock_t t = clock();
  time_t rawtime;
  struct tm *timeinfo;

  // 获取文件路径，参考：http://www.cplusplus.com/reference/string/string/find_last_of/
  const std::string full_path_exec{argv[0]};
  std::string::size_type found =
      full_path_exec.find_last_of("/\\", std::string::npos);
  const std::string exec_path = full_path_exec.substr(0, found);
  const std::string exec_filename =
      full_path_exec.substr(found + 1, std::string::npos);
  const std::string data_file_name("\\ch8_3.result");

  // 打开测试数据文件
  std::string data_file_full_path{exec_path +
                                  data_file_name};  // 数据文件的绝对地址
  std::ofstream fout(data_file_full_path.c_str(), std::ios_base::app);
  if (fout.fail()) {
    std::cerr << "无写权限，测试数据文件生成失败！\n";
    system("pause");
    return false;
  }

  // output time information
  time(&rawtime);                  // Get the current calendar time
  timeinfo = localtime(&rawtime);  // Convert time_t to tm as local time
  // printf("Current local time and date: %s\n", asctime(timeinfo)); // Convert
  // tm structure to string
  std::cout << "\nCurrent local time and date: " << asctime(timeinfo) << '\n';
  fout << "\nCurrent local time and date: " << asctime(timeinfo) << '\n';

  // 开始测试
  try {
    std::vector<size_t> vec1, vec2, vec_union, vec_intersect, vec_diff;

    /* initialize random seed: */
    srand(time(NULL));

    /* generate secret number between low and high: */
    size_t low{10}, high{25}, num_of_points{16};
    size_t iSecret;
    for (size_t i = 0; i < num_of_points; ++i) {
      iSecret = low + (high - low + 1) * rand() / (RAND_MAX + 1);
      vec1.push_back(iSecret);
      iSecret = low + (high - low + 1) * rand() / (RAND_MAX + 1);
      vec2.push_back(iSecret);
    }

    // 对vec1, vec2排序，并去除重复元素
    std::vector<size_t>::iterator it;

    std::sort(vec1.begin(), vec1.end());
    it = std::unique(vec1.begin(), vec1.end());
    vec1.resize(std::distance(vec1.begin(), it));

    std::sort(vec2.begin(), vec2.end());
    it = std::unique(vec2.begin(), vec2.end());
    vec2.resize(std::distance(vec2.begin(), it));

    // 输出vec1, vec2的元素
    std::cout << "set1 has " << (vec1.size()) << " elements:\n";
    fout << "set1 has " << (vec1.size()) << " elements:\n";
    for (auto it = vec1.begin(); it != vec1.end(); ++it) {
      std::cout << *it << ", ";
      fout << *it << ", ";
    }
    std::cout << '\n';
    fout << '\n';

    std::cout << "set2 has " << (vec2.size()) << " elements:\n";
    fout << "set2 has " << (vec2.size()) << " elements:\n";
    for (auto it = vec2.begin(); it != vec2.end(); ++it) {
      std::cout << *it << ", ";
      fout << *it << ", ";
    }
    std::cout << '\n';
    fout << '\n';

    // 求并，交，差，打印结果
    vec_union = vec1 + vec2;
    std::cout << "The union has " << (vec_union.size()) << " elements:\n";
    fout << "The union has " << (vec_union.size()) << " elements:\n";
    for (auto it = vec_union.begin(); it != vec_union.end(); ++it) {
      std::cout << *it << ", ";
      fout << *it << ", ";
    }
    std::cout << '\n';
    fout << '\n';

    vec_intersect = vec1 * vec2;
    std::cout << "The intersection has " << (vec_intersect.size())
              << " elements:\n";
    fout << "The intersection has " << (vec_intersect.size()) << " elements:\n";
    for (auto it = vec_intersect.begin(); it != vec_intersect.end(); ++it) {
      std::cout << *it << ", ";
      fout << *it << ", ";
    }
    std::cout << '\n';
    fout << '\n';

    vec_diff = vec1 - vec2;
    std::cout << "The difference has " << (vec_diff.size()) << " elements:\n";
    fout << "The difference has " << (vec_diff.size()) << " elements:\n";
    for (auto it = vec_diff.begin(); it != vec_diff.end(); ++it) {
      std::cout << *it << ", ";
      fout << *it << ", ";
    }
    std::cout << '\n';
    fout << '\n';
  } catch (const std::string &e) {
    std::cerr << e << '\n';
    fout << e << '\n';
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    fout << e.what() << '\n';
  }

  // output time information
  t = clock() - t;
  // printf("\nIt took me %ld clicks (%f seconds).\n", t, ((float)t) /
  // CLOCKS_PER_SEC);
  std::cout << "\nIt took me " << t << " clicks ("
            << ((float)t) / CLOCKS_PER_SEC << " seconds).\n";
  fout << "\nIt took me " << t << " clicks (" << ((float)t) / CLOCKS_PER_SEC
       << " seconds).\n";

  // 测试结束
  fout.close();
  system("pause");
  return 0;
}  // main

template <class T>
std::vector<T> operator+(const std::vector<T> &vec1,
                         const std::vector<T> &vec2) {
  std::vector<T> vec_union(vec1.size() + vec2.size());

  /**
   * Input iterators to the initial and final positions of the first sorted
   * sequence.
   *
   * The range used is [first1,last1), which contains all the elements between
   * first1 and last1, including the element pointed by first1 but not the
   * element pointed by last1.
   */
  auto first1{vec1.begin()}, last1{vec1.end()};

  /**
   * Input iterators to the initial and final positions of the second sorted
   * sequence.
   *
   * The range used is [first2,last2).
   */
  auto first2{vec2.begin()}, last2{vec2.end()};

  /**
   * Output iterator to the initial position of the range where the resulting
   * sequence is stored.
   *
   * The pointed type shall support being assigned the value of an element from
   * the other ranges.
   */
  auto result{vec_union.begin()};

  while (true) {
    if (first1 == last1) {
      result = std::copy(first2, last2, result);
      break;
    }
    if (first2 == last2) {
      result = std::copy(first1, last1, result);
      break;
    }

    if (*first1 < *first2) {
      *result = *first1;
      ++first1;
    } else if (*first2 < *first1) {
      *result = *first2;
      ++first2;
    } else {
      *result = *first1;
      ++first1;
      ++first2;
    }
    ++result;
  }
  vec_union.resize(result - vec_union.begin());
  return vec_union;
}

template <class T>
std::vector<T> operator*(const std::vector<T> &vec1,
                         const std::vector<T> &vec2) {
  std::vector<T> vec_intersect(vec1.size());

  /**
   * Input iterators to the initial and final positions of the first sorted
   * sequence.
   *
   * The range used is [first1,last1), which contains all the elements between
   * first1 and last1, including the element pointed by first1 but not the
   * element pointed by last1.
   */
  auto first1{vec1.begin()}, last1{vec1.end()};

  /**
   * Input iterators to the initial and final positions of the second sorted
   * sequence.
   *
   * The range used is [first2,last2).
   */
  auto first2{vec2.begin()}, last2{vec2.end()};

  /**
   * Output iterator to the initial position of the range where the resulting
   * sequence is stored.
   *
   * The pointed type shall support being assigned the value of an element from
   * the other ranges.
   */
  auto result{vec_intersect.begin()};

  while (first1 != last1 && first2 != last2) {
    if (*first1 < *first2)
      ++first1;
    else if (*first2 < *first1)
      ++first2;
    else {
      *result = *first1;
      ++result;
      ++first1;
      ++first2;
    }
  }
  vec_intersect.resize(result - vec_intersect.begin());
  return vec_intersect;
}

template <class T>
std::vector<T> operator-(const std::vector<T> &vec1,
                         const std::vector<T> &vec2) {
  std::vector<T> vec_diff(vec1.size());

  /**
   * Input iterators to the initial and final positions of the first sorted
   * sequence.
   *
   * The range used is [first1,last1), which contains all the elements between
   * first1 and last1, including the element pointed by first1 but not the
   * element pointed by last1.
   */
  auto first1{vec1.begin()}, last1{vec1.end()};

  /**
   * Input iterators to the initial and final positions of the second sorted
   * sequence.
   *
   * The range used is [first2,last2).
   */
  auto first2{vec2.begin()}, last2{vec2.end()};

  /**
   * Output iterator to the initial position of the range where the resulting
   * sequence is stored.
   *
   * The pointed type shall support being assigned the value of an element from
   * the other ranges.
   */
  auto result{vec_diff.begin()};

  while (first1 != last1 && first2 != last2) {
    if (*first1 < *first2) {
      *result = *first1;
      ++result;
      ++first1;
    } else if (*first2 < *first1)
      ++first2;
    else {
      ++first1;
      ++first2;
    }
  }
  result = std::copy(first1, last1, result);
  vec_diff.resize(result - vec_diff.begin());
  return vec_diff;
}
