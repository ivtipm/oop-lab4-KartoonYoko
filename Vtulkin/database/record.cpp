#include "record.h"


    void record::setId(const unsigned int& id){ this->_id = id;  }
    void record::setFirstName(const std::string& first){ this->_first_name = first; }
    void record::setSecondName(const std::string& second){ this->_second_name = second; }
    void record::setAge(const unsigned short& age){ this->_age = age; }

    unsigned int record::getId()const { return this->_id; }
    std::string record::getFirstName() const { return this->_first_name; }
    std::string record::getSecondName() const { return this->_second_name; }
    unsigned short record::getAge() const { return this->_age; }




