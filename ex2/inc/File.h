/* -*  *  *  *  *  *  *  *  *  *  *  *
*   Marcel Karsten -- 343619,
*   Patrick Lorenz -- 341922,
*   Richard Klemm -- 343635
*  *  *  *  *  *  *  *  *  *  *  *  */
#ifndef FILE_HPP_XSDLZF62
#define FILE_HPP_XSDLZF62

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string.hpp>

#include <exception>
#include <string>

class FileDoesNotExistException: public std::exception
{
  virtual const char* what() const throw() //override
  {
    return "File does not exist";
  }
};

class File
{

public:
    File (const std::string& fileName);
    virtual ~File ();
    std::string getContent();

private:
    boost::filesystem::fstream m_File;
};

#endif /* end of include guard: FILE_HPP_XSDLZF62 */

