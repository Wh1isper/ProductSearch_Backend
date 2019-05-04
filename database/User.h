/*
 * 作者：Wh1isper at 2019-04-30
 * 说明：
 *      存储用户信息和偏好
 *      ！！注意：尚未开工
*/

#ifndef SOFTWARE_USER_H
#define SOFTWARE_USER_H

#include <string>
#include "LabelList.h"
class User {
public:
    User();
    User(const std::string &name);
    User(const std::string &name, LabelList &pre);
    static int getUid(User &ur);
    int getUid();
    void setUid(int uid);
private:
    int Uid;
    std::string Uname;
    LabelList Prefer;
};


#endif //SOFTWARE_USER_H
