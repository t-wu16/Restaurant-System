#ifndef OBJECT_H
#define OBJECT_H
#include "cafeteria.h"

/*
 * Object类
 * 所有类的基类
*/
class Object
{
protected:
    string my_id;       //编号
    string my_name;     //名字

public:
    //构造函数
    Object(const string &id="", const string &name="");
    //基本接口
    virtual void setId(const string &id);
    virtual void setName(const string &name);
    virtual string getId() const;
    virtual string getName() const;
    //运算符重载
    virtual bool operator <(const Object & right_item) const;

};
#endif // OBJECT_H
