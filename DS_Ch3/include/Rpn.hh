/**
 * @file Rpn.hh
 * @author Guorui Wei (313017602@qq.com)
 * @brief 后缀表达式类
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __RPN_HH__
#define __RPN_HH__

#include "List.h"
#include "Stack.hh"
#include <cctype>
#include <cmath>
#include <cstdio>
#include <exception>
#include <iostream>
#include <string>
#include <utility>

/**
 * @brief RPN 名字空间
 * 
 */
namespace RPN
{

const int buf_size = 80; ///< 项的最大长度 = buf_size - 1

enum struct notationType ///< 表达式类型
{
    Infix,  ///< 中缀表达式
    Postfix ///< 后缀表达式
};

/**
 * @brief 异常类
 * 
 */
class RpnException : public std::exception
{
public:
    /**
     * @brief Constructor.
     * \param text - The text of the exception.
     * \param id - The text identifying the argument source.
     * \param td - Text describing the type of ArgException it is.
     * of the exception.
     */
    RpnException(const std::string &text = "undefined exception",
                 const std::string &id = "undefined",
                 const std::string &td = "Generic ArgException")
        : std::exception(),
          _errorText(text),
          _argId(id),
          _typeDescription(td) {}

    /**
     * @brief Destroy the Rpn Exception object
     * 
     */
    virtual ~RpnException() noexcept {}

    /**
     * @brief Returns the error text.
     * 
     * @return std::string 
     */
    std::string error() const { return (_errorText); }

    /**
     * @brief Returns the argument id.
     * 
     * @return std::string 
     */
    std::string argId() const
    {
        if (_argId == "undefined")
            return " ";
        else
            return ("Argument: " + _argId);
    }

    /**
     * @brief Returns the arg id and error text.
     */
    const char *what() const noexcept
    {
        static std::string ex;
        ex = _argId + " -- " + _errorText;
        return ex.c_str();
    }

    /**
     * @ brief Returns the type of the exception.  
     * 
     * Used to explain and distinguish
     * between different child exceptions.
     */
    std::string typeDescription() const { return _typeDescription; }

private:
    /**
     * @brief The text of the exception message.
     */
    std::string _errorText;

    /**
     * @brief The argument related to this exception.
     */
    std::string _argId;

    /**
     * @brief Describes the type of the exception.  
     * 
     * Used to distinguish
     * between different child exceptions.
     */
    std::string _typeDescription;
};

class Rpn_t
{
private:
    struct Item ///< 后缀式的元素: 操作数, 操作符
    {
        enum class Item_type ///< 项的类型
        {
            Operand, ///< 操作数
            Operator ///< 操作符
        };

        enum class Operator_type : int8_t ///< 操作符类型
        {
            /**
             * @detail priority = 算术右移4位(得0 ~ 7, -1). 0: 未定义; -1: NAO; 1 ~ 7: 一般运算符, 7为最高优先级
             * 
             */

            NAO = (int8_t)0xFF, ///< Not an operator(lowest priority): 0xFF
            Add = 0x10,         ///< lowest(but NAO) priority: 0x01
            Sub = 0x11,
            Mul = 0x20,
            Div = 0x21,
            Exp = 0x30,    ///< highest priority: 0x07
            Oparen = 0x01, ///< undefine priority : 0x00
            Cparen = 0x02
        };

        Item_type item_type;         ///< 项的类型
        Operator_type operator_type; ///< 操作符类型
        double operand_val = NAN;    ///< 操作数的值(为操作符时, 无效)

        /**
         * @brief Construct a new Item object
         * 
         * @param item_type 
         * @param operator_type 
         * @param operand_val 
         */
        Item(Item_type item_type, Operator_type operator_type, double operand_val = NAN)
            : item_type(item_type), operator_type(operator_type), operand_val(operand_val) {}

        /**
         * @brief Construct a new Item object
         * 
         * @detail 构造一个操作数item
         * @param operand_val 
         */
        explicit Item(double operand_val)
            : item_type(Item_type::Operand), operator_type(Operator_type::NAO), operand_val(operand_val) {}

        /**
         * @brief Construct a new Item object
         * 
         * 构造一个操作符item(默认构造函数)
         * @param op 
         */
        explicit Item(Operator_type op = Operator_type::NAO)
            : item_type(Item_type::Operator), operator_type(op), operand_val(NAN) {}

        /**
         * @brief Item内嵌类的工具函数
         * 
         * 运算符优先级lhs < rhs. NAO(非法运算符)的优先级为最低
         * 
         * @param rhs 
         * @return true 
         * @return false 
         */
        bool hasLoPriThan(const Item &rhs) const;

        /**
         * @brief 是操作符
         * 
         * @return true 是操作符
         * @return false 不是操作符
         */
        bool isOperator() const { return item_type == Item_type::Operator; }

        /**
         * @brief 是操作数
         * 
         * @return true 是操作数
         * @return false 非操作数
         */
        bool isOperand() const { return item_type == Item_type::Operand; }

        /**
         * @brief 是NAO? 
         * @note 操作数不是NAO
         * 
         * @return true 
         * @return false 
         */
        bool isNAO() const { return isOperator() && operator_type == Operator_type::NAO; }

        /**
         * @brief 获得一个NAO(非法操作符)
         * 
         * @return Item 
         */
        static Item nao() { return Item(Item_type::Operator, Operator_type::NAO, NAN); }

        /**
         * @brief 获取优先级. 
         * @note有效: -1(NAO), 0(未定义), 1~7(一般运算符)
         * 
         * @return int8_t 
         */
        int8_t priority() const { return static_cast<int8_t>(operator_type) >> 4; }

        /**
         * @brief 执行一次运算. 
         * @note 一元运算符, arg2或arg3为NAO.
         * 
         * @param op 
         * @param opL 
         * @param opR 
         * @return Item 
         */
        static Item excOp(const Item &op, const Item &opL = nao(), const Item &opR = nao());

        /**
         * @brief 二元加法的优先级(同减法)
         * 
         */
        static const int8_t priOfAdd = static_cast<int8_t>(Operator_type::Add) >> 4;

        /**
         * @brief 二元乘法的优先级(同除法)
         * 
         */
        static const int8_t priOfMul = static_cast<int8_t>(Operator_type::Mul) >> 4;

        /**
         * @brief operator==
         * 
         * @param lhs 
         * @param rhs 
         * @return true 
         * @return false 
         */
        friend bool operator==(const Item &lhs, const Item &rhs); // 授予operator==()访问Item的私有成员的权限
    };

    /**
     * @brief operator==
     * 
     * @param lhs 
     * @param rhs 
     * @return true 
     * @return false 
     */
    friend bool operator==(const Item &lhs, const Item &rhs); // 授予operator==()访问Rpn_t类的私有内嵌类Item的权限

private:
    /**
     * @brief 存储后缀表达式的双链表
     * 
     */
    List::dLinkList<Item> itemList;

    /**
     * @brief 存储后缀形式的字符串 
     */
    std::string postfixStr;

    /**
     * @brief Rpn类的工具函数
     * 
     * 从string首解析一个项(操作符/操作数)
     * 
     * @param _ch 
     * @param _EndPtr 
     * @return Item 
     */
    Item stoItem(const char *_ch, const char **_EndPtr = nullptr) const;

    /**
     * @brief 获取表示项(操作符/操作数)的string
     * 
     * @param Op 
     * @return std::string 
     */
    std::string itemToStr(const Item &Op) const;

    /**
     * @brief 用string中的表达式创建一个list
     * 
     * @param exprStr 
     * @return List::dLinkList<Item> 
     */
    List::dLinkList<Item> exprStrToList(const std::string &exprStr) const;

    /**
     * @brief 用一个中缀list创建一个后缀list
     * 
     * @param infixList 
     * @return List::dLinkList<Item> 
     */
    List::dLinkList<Item> infixListToPostfixList(const List::dLinkList<Item> &infixList) const;

    /**
     * @brief 获取表示itemList的string
     * 
     * @param itemList 
     * @return std::string 
     */
    std::string itemListToStr(const List::dLinkList<Item> &itemList) const;

public:
    /**
     * @brief Construct a new Rpn_t object
     * 
     * @param expr_str 
     * @param exprType 
     */
    explicit Rpn_t(const std::string &expr_str = "0.0", notationType exprType = notationType::Infix);

    /**
     * @brief Destroy the Rpn_t object
     * 
     */
    ~Rpn_t() = default;

    /**
     * @brief 计算(后缀)表达式的值
     * 
     * @return double 
     */
    double calcVal() const;

    /**
     * @brief 获取后缀形式的string
     * 
     * @return std::string 
     */
    std::string postfix() const;

    /**
     * @brief 设置Rpn_t类对象的值
     * 
     * @param expr_str 
     * @param _type 
     * @return Rpn_t& 
     */
    Rpn_t &assign(const std::string &expr_str, notationType _type = notationType::Infix);
};

Rpn_t::Rpn_t(const std::string &expStr, notationType expType)
{
    if (expStr.empty())
        throw(RpnException("Empty string!\n"));

    // arg1是后缀式
    if (expType == notationType::Postfix)
    {
        itemList = std::move(exprStrToList(expStr));
        postfixStr = itemListToStr(itemList);

        return;
    }

    // arg1是中缀式
    List::dLinkList<Item> infixList = std::move(exprStrToList(expStr)); // 创建中缀list
    itemList = std::move(infixListToPostfixList(infixList));            // 转为后缀list
    postfixStr = std::move(itemListToStr(itemList));                    // 创建后缀表达式的string
}

// 设置Rpn_t类对象的值
Rpn_t &Rpn_t::assign(const std::string &expStr, notationType expType)
{
    if (expStr.empty())
        throw(RpnException("Empty string!\n"));

    itemList.clear();

    // arg1是后缀式
    if (expType == notationType::Postfix)
    {
        itemList = std::move(exprStrToList(expStr));
        postfixStr = itemListToStr(itemList);

        return *this;
    }

    // arg1是中缀式
    List::dLinkList<Item> infixList = std::move(exprStrToList(expStr)); // 创建中缀list
    itemList = std::move(infixListToPostfixList(infixList));            // 转为后缀list
    postfixStr = std::move(itemListToStr(itemList));

    return *this;
}

// 获取后缀形式的string
std::string Rpn_t::postfix() const
{
    return postfixStr;
}

// 从string首解析一个项(操作符/操作数). 非0时, 使_EndPtr指向合法项的下一字符
Rpn_t::Item Rpn_t::stoItem(const char *ch, const char **_EndPtr) const
{
    while (*ch)
    {
        // 跳过前面所有空格
        if (isspace(*ch))
        {
            ++ch;
            continue;
        }

        // 处理非数字（操作符）. (暂假定所有操作符都只有一个字符)
        if (!isdigit(*ch))
        {
            if (_EndPtr)
                *_EndPtr = ch + 1;

            switch (*ch)
            {
            case '+':
                return Item(Item::Item_type::Operator, Item::Operator_type::Add, NAN);
                break;
            case '-':
                return Item(Item::Item_type::Operator, Item::Operator_type::Sub, NAN);
                break;
            case '*':
                return Item(Item::Item_type::Operator, Item::Operator_type::Mul, NAN);
                break;
            case '/':
                return Item(Item::Item_type::Operator, Item::Operator_type::Div, NAN);
                break;
            case '^':
                return Item(Item::Item_type::Operator, Item::Operator_type::Exp, NAN);
                break;
            case '(':
                return Item(Item::Item_type::Operator, Item::Operator_type::Oparen, NAN);
                break;
            case ')':
                return Item(Item::Item_type::Operator, Item::Operator_type::Cparen, NAN);
                break;
            default:
                return Item(Item::Item_type::Operator, Item::Operator_type::NAO, NAN);
                break;
            } // switch (*ch)

        } // if (!isdigit(*ch))

        // 处理操作数
        char *pEnd; // 将指向首数字的下一字符
        double operandValue = strtod(ch, &pEnd);

        if (_EndPtr)
            *_EndPtr = pEnd;

        return Item{Item::Item_type::Operand, Item::Operator_type::NAO, operandValue};

    } //while (!*ch)

    if (_EndPtr)
        *_EndPtr = ch;

    return Item(Item::Item_type::Operator, Item::Operator_type::NAO, NAN);
}

// 用string中的表达式创建一个list
List::dLinkList<Rpn_t::Item> Rpn_t::exprStrToList(const std::string &exprStr) const
{
    const char *expr_cstr = exprStr.c_str();
    List::dLinkList<Rpn_t::Item> itemList;

    while (*expr_cstr)
        itemList.push_back(std::move(stoItem(expr_cstr, &expr_cstr)));

    // 若最后一个有效字符后有空白字符, 将导致一个多余的NAO进入itemList.
    if (itemList.back().isNAO())
        itemList.pop_back();

    return itemList;
}

// 用一个中缀list创建一个后缀list
List::dLinkList<Rpn_t::Item> Rpn_t::infixListToPostfixList(const List::dLinkList<Item> &infixList) const
{
    Stack::linkStack<Item> opStack;    // 暂存运算符的栈
    List::dLinkList<Item> postfixList; // 后缀运算符list

    // 初始化. NAO(优先级最低)进栈
    opStack.push(Item::nao());

    // 读中缀list
    for (auto i = infixList.begin(); i != infixList.end(); ++i)
    {
        // 操作数直接输出
        if ((*i).isOperand())
        {
            postfixList.push_back(*i);
            continue;
        }

        // 开始处理操作符
        if ((*i).isNAO()) // 禁止非法操作符
            throw(RpnException("Invalid expr!\n"));

        // 读到开括号, 进栈
        if ((*i).operator_type == Item::Operator_type::Oparen)
        {
            opStack.push((*i));
            continue;
        }

        // 读到闭括号, opStack退栈直到遇到开括号
        if ((*i).operator_type == Item::Operator_type::Cparen)
        {
            Item _topItem = opStack.top();
            while (_topItem.operator_type != Item::Operator_type::Oparen)
            {
                opStack.pop();
                postfixList.push_back(_topItem);
                _topItem = opStack.top();
            }
            opStack.pop(); // 开括号退栈, 但不加入后缀list
            continue;
        }

        // 读到乘方运算符(右结合, 暂为最高优先级), 进栈
        if ((*i).operator_type == Item::Operator_type::Exp)
        {
            opStack.push(*i);
            continue;
        }

        // 读到加减乘除(左结合), 则退栈直到栈顶操作符优先级较低或遇到开括号, 然后进栈
        auto _pri = (*i).priority();
        if (_pri >= Item::priOfAdd && _pri <= Item::priOfMul)
        {
            Item _topItem = opStack.top();

            // 当栈顶不是(开)括号(优先级0)或栈底标志NAO(优先级-1), 且栈顶优先级不低于当前运算符, 退栈
            while (_topItem.priority() > 0 && !_topItem.hasLoPriThan((*i)))
            {
                opStack.pop();
                postfixList.push_back(_topItem);
                _topItem = opStack.top();
            }

            // 当前运算符进栈
            opStack.push((*i));
            continue;
        } // if (_pri >= Item::priOfAdd && _pri <= Item::priOfMul)

    } // for (auto i = infixList.begin(); i != infixList.end(); ++i)

    // 退栈至栈空(NAO不要进itemlist)
    while (!opStack.top().isNAO())
        postfixList.push_back(opStack.pop());

    return postfixList;
}

// 计算(后缀)表达式的值
double Rpn_t::calcVal() const
{
    double result;                  // 表达式计算结果
    Stack::seqStack<Item> rpnStack; // 存储后缀表达式item的栈

    for (auto i = itemList.begin(); i != itemList.end(); ++i)
    {
        // 读到操作数, 进栈
        if ((*i).isOperand())
        {
            rpnStack.push(*i);
            continue;
        }

        // 读到操作符, 退栈取操作数, 然后将计算结果进栈
        if ((*i).isNAO()) // 禁止非法操作符
            throw(RpnException("Invalid expr!\n"));

        if (rpnStack.isEmpty())
            throw(RpnException("Invalid expr!\n"));
        Item opR = rpnStack.pop();

        if (rpnStack.isEmpty())
            throw(RpnException("Invalid expr!\n"));
        Item opL = rpnStack.pop();

        rpnStack.push(Item::excOp(*i, opL, opR));
    }

    // 读完表达式后, 栈中应只有1个元素, 此为表达式的值
    result = (rpnStack.pop().operand_val);

    // 若栈非空, 则为非法表达式
    if (!rpnStack.isEmpty())
        throw(RpnException("Invalid expr!\n"));

    return result;
}

// 获取表示itemList的string
std::string Rpn_t::itemListToStr(const List::dLinkList<Item> &itemList) const
{
    std::string exprStr;

    for (auto i = itemList.begin(); i != itemList.end(); ++i)
    {
        exprStr += itemToStr(*i).append(" ");
    }

    return exprStr;
}

// 获取表示项(操作符/操作数)的string
std::string Rpn_t::itemToStr(const Item &Op) const
{
    if (Op.item_type == Item::Item_type::Operand)
    {
        char buf[buf_size];

        int numOfCh = snprintf(buf, buf_size, "%.15g", Op.operand_val);
        if (numOfCh > 0 && numOfCh < buf_size)
            return buf;

        throw(RpnException("Number is too long!\n"));
    }

    switch (Op.operator_type)
    {
    case Item::Operator_type::Add:
        return "+";
        break;
    case Item::Operator_type::Cparen:
        return ")";
        break;
    case Item::Operator_type::Div:
        return "/";
        break;
    case Item::Operator_type::Exp:
        return "^";
        break;
    case Item::Operator_type::Mul:
        return "*";
        break;
    case Item::Operator_type::Oparen:
        return "(";
        break;
    case Item::Operator_type::Sub:
        return "-";
        break;
    default:
        return "#";
        break;
    }

    throw(RpnException("What's wrong with your code???\n"));
}

// 运算符优先级lhs < rhs. NAO(非法运算符)的优先级为最低
bool Rpn_t::Item::hasLoPriThan(const Item &rhs) const
{
    // 若非操作符, 恒false
    if (rhs.item_type != Item_type::Operator)
        return false;

    // 获取优先级
    int8_t pri_lhs = priority();
    int8_t pri_rhs = rhs.priority();

    if (!pri_lhs || !pri_rhs) // undefined priority
        return false;

    return pri_lhs < pri_rhs;
}

// 执行运算. 一元运算符, arg2或arg3为NAO.
Rpn_t::Item Rpn_t::Item::excOp(const Item &op, const Item &opL, const Item &opR)
{
    if (!op.isOperator() || op.isNAO())
        throw(RpnException("Arg1 should be a valid operator!\n"));

    switch (op.operator_type)
    {
    case Operator_type::Add:
        if (!opL.isOperand() || !opR.isOperand())
            throw(RpnException("Invalid operand!\n"));
        return Item(opL.operand_val + opR.operand_val);
        break;
    case Operator_type::Div:
        if (!opL.isOperand() || !opR.isOperand())
            throw(RpnException("Invalid operand!\n"));
        return Item(opL.operand_val / opR.operand_val);
        break;
    case Operator_type::Exp:
        if (!opL.isOperand() || !opR.isOperand())
            throw(RpnException("Invalid operand!\n"));
        return Item(pow(opL.operand_val, opR.operand_val));
        break;
    case Operator_type::Mul:
        if (!opL.isOperand() || !opR.isOperand())
            throw(RpnException("Invalid operand!\n"));
        return Item(opL.operand_val * opR.operand_val);
        break;
    case Operator_type::Sub:
        if (!opL.isOperand() || !opR.isOperand())
            throw(RpnException("Invalid operand!\n"));
        return Item(opL.operand_val - opR.operand_val);
        break;
    default:
        throw(RpnException("Invalid operator!\n"));
        break;
    }
}

bool operator==(const Rpn_t::Item &lhs, const Rpn_t::Item &rhs)
{
    if (lhs.item_type != rhs.item_type)
        return false;
    if (lhs.operator_type != rhs.operator_type)
        return false;
    return lhs.operand_val == rhs.operand_val;
}

} // namespace RPN

#endif // __RPN_HH__
