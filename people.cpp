#include "people.h"

//构造函数
People::People(const string &id, const string &name, const string &password) :
    Object(id, name), my_password(password)
{
}

//基本接口
void People::setPassword(const std::string &password)
{
    my_password = password;
}

string People::getPassword() const
{
    return my_password;
}
