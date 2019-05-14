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
    // -----------------------------------构造函数---------------------------------------------
    User();

    explicit User(const std::string &name);

    User(const User &user);

    User(const std::string &name, LabelList &pre);
    // -----------------------------------功能函数---------------------------------------------
    void updatePrfList(const Label &L);     // 更新用户喜好表，前插或前移插入一个标签

    void updatePrfList(const LabelList &L); // 更新用户喜好表，前插或前移多个标签

    void setLabelList(LabelList prf); // 设置用户喜好表
    // ！！谨慎调用
    void setUid(); // 设置User的Uid
    // -----------------------------------查询(get)函数---------------------------------------------
    unsigned long getUid() const; // 查询当前用户Uid

    static unsigned long getUid(User &ur); // 查询用户Uid

    static unsigned long getUid(const std::string &name); // 计算用户Uid

    std::string getName() const; // 获得当前用户名

    LabelList getPreferList() const; // 获得用户喜好列表
    // -----------------------------------哈希函数api---------------------------------------------
    unsigned long hashFun() const;

    static unsigned long hashFun(const std::string &name);
    // -----------------------------------重载函数---------------------------------------------
    bool operator==(const User &B) const;
private:
    unsigned long Uid;
    std::string Uname;
    LabelList Prefer;
};


#endif //SOFTWARE_USER_H
