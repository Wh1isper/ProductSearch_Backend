/*
 * 作者：Wh1isper at 2019-04-30
 * 说明：
 *      存储用户信息和偏好
 *      ！！注意：未经测试
*/

#ifndef SOFTWARE_USER_H
#define SOFTWARE_USER_H

#include <string>
#include "LabelList.h"
class User {
public:
    User();
    explicit User(const std::string &name);
    User(const User &user);
    User(const std::string &name, LabelList &pre);
    static unsigned long getUid(User &ur);
    static unsigned long getUid(const std::string &name) ;
    void setUid();
    unsigned long getUid() const ;
    bool operator == (const User &B) const;
    unsigned long hashFun() const ;
    static unsigned long hashFun(const std::string &name);
    std::string getName() const;
    LabelList getPreferList() const;
    void setLabelList(LabelList prf);
private:
    unsigned long Uid;
    std::string Uname;
    LabelList Prefer;
};


#endif //SOFTWARE_USER_H
