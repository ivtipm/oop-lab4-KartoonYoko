#ifndef RECORD_H
#define RECORD_H

#include <string>


/*
        Класс "Запись".
    Запись для класса Database. Содержит одну статическую переменную "_amount" для посчета общего количества.

*/

enum recordException {};

class record
{
    unsigned int _id;
    std::string _first_name;
    std::string _second_name;
    unsigned short _age;
public:


    void setId(const unsigned int& id);
    void setFirstName(const std::string& first);
    void setSecondName(const std::string& second);
    void setAge(const unsigned short& age);

    unsigned int getId() const;
    std::string getFirstName() const;
    std::string getSecondName() const;
    unsigned short getAge() const;

    record(unsigned int id = 1, std::string first = "FirstName", std::string second = "SecondName", unsigned short age = 1){
            setId(id);
            setFirstName(first);
            setSecondName(second);
            setAge(age);
     }


};


#endif // RECORD_H
