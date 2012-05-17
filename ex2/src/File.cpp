#include "File.h"
#include <stdio.h>

using namespace boost::filesystem3;

File::File(const std::string& fileName){
    //  "/=" is the append path operator
    path filePath = current_path() /=path("data") /= path(fileName);
    if(exists(filePath)) {
        m_File.open(filePath);
    }else{
        throw FileDoesNotExistException();
    }
}

File::~File(){
    m_File.close();
}

std::string File::getContent(){
     std::string result;
     std::string tmp;
     while(std::getline(m_File, tmp)){
        result.append(tmp);
     }
     //Get rid of leading and trailing zeros
     boost::trim(result);
     return result;
}
