/*
 * 作者：Wh1isper at 2019-04-30
 * 说明：
 *      用户图，用于存储全部用户信息
 *      ！！注意：未经测试
*/

#ifndef SOFTWARE_USERMAP_H
#define SOFTWARE_USERMAP_H

#include "User.h"
#include <vector>

class UserMap {
public:
    struct tableNode {
        User curUser;
        tableNode *Next;

        tableNode();

        explicit tableNode(const User &user);
    };  // 利用链式存储避免冲突
    // -----------------------------------构造函数---------------------------------------------
    UserMap();

    explicit UserMap(unsigned int max);
    // -----------------------------------功能函数---------------------------------------------
    bool insert(User &user);    // 插入用户

    bool remove(const User &user);          // 直接移除用户

    bool remove(const std::string &name);   // 用过用户名移除用户

    bool updateUser(User &user); // 更新用户信息
    // -----------------------------------查询函数---------------------------------------------
    bool findUser(User &user); // 查找用户是否存在

    User &getUser(const std::string &name); // 通过用户名返回用户信息

    unsigned int getUserNum();  // 返回注册用户数量

    std::vector<tableNode *> getTable();    // 返回所有用户

private:
    unsigned int maxUserNum;    // 哈希表长
    unsigned int userNum;       // 当前用户数量

    std::vector<tableNode *> Table; // 头节点列表

    std::vector<tableNode *> creatTable();
};


#endif //SOFTWARE_USERMAP_H
