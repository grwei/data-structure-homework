/****************************************************
 * @file TreeException.hh
 * @author Guorui Wei (313017602@qq.com)
 * @brief 树的异常类
 * @version 0.1
 * @date 2020-04-19
 * 
 * @copyright Copyright (c) 2020
 * 
 * See the file LICENSE in the top directory of this distribution for
 * more information.
 * 
 ****************************************************/

#ifndef INCLUDE_TREEEXCEPTION_HH_
#define INCLUDE_TREEEXCEPTION_HH_

#include <exception>
#include <string>

namespace Tree
{

/**
 * A simple class that defines and Tree exception.  Should be caught
 * whenever a Tree is created and used.
 */
class TreeException : public std::exception
{
public:
    /**
     * Constructor.
     * \param text - The text of the exception.
     * \param id - The text identifying the argument source.
     * \param td - Text describing the type of ArgException it is.
     * of the exception.
     */
    TreeException(const std::string &text = "undefined exception",
                  const std::string &id = "undefined",
                  const std::string &td = "Generic ArgException")
        : std::exception(),
          _errorText(text),
          _argId(id),
          _typeDescription(td) {}

    /**
     * Destructor.
     */
    virtual ~TreeException() noexcept {}

    /**
     * Returns the error text.
     */
    std::string error() const { return (_errorText); }

    /**
     * Returns the argument id.
     */
    std::string argId() const
    {
        if (_argId == "undefined")
            return " ";
        else
            return ("Argument: " + _argId);
    }

    /**
     * Returns the arg id and error text.
     */
    const char *what() const noexcept
    {
        static std::string ex;
        ex = _argId + " -- " + _errorText;
        return ex.c_str();
    }

    /**
     * Returns the type of the exception.  Used to explain and distinguish
     * between different child exceptions.
     */
    std::string typeDescription() const { return _typeDescription; }

private:
    /**
     * The text of the exception message.
     */
    std::string _errorText;

    /**
     * The argument related to this exception.
     */
    std::string _argId;

    /**
     * Describes the type of the exception.  Used to distinguish
     * between different child exceptions.
     */
    std::string _typeDescription;
};
} // namespace Tree

#endif /* INCLUDE_TREEEXCEPTION_HH_ */
