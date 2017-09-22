#include "object.h"
//构造函数
Object::Object(const std::string &id, const std::string &name) :
    my_id(id), my_name(name)
{

}

//基本接口
void Object::setId(const string &id)
{
    my_id = id;
}

void Object::setName(const string &name)
{
    my_name = name;
}

string Object::getId() const
{
    return my_id;
}

string Object::getName() const
{
    return my_name;
}

//运算符重载
bool Object::operator <(const Object & right_item) const
{
    return my_id < right_item.my_id;
}
