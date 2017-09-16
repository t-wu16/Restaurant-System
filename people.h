#ifndef PEOPLE_H
#define PEOPLE_H
#include "object.h"

/*
 * People类
 * 继承自Object类，是Customer/Cook/Waiter/Manager/Administrator的基类
*/
class People : public Object
{
protected:
    string my_password;     //密码
public:
    People(const string &id="", const string &name="", const string &password="");
    virtual void setPassword(const string &password);
    virtual string getPassword() const;
};

#endif // PEOPLE_H
