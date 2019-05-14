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
    struct tableNode{
        User curUser;
        tableNode * Next;
        tableNode();
        explicit tableNode(const User & user);
    };
    UserMap();
    explicit UserMap(unsigned int max);
    bool insert(User &user);
    User & getUser(const std::string &name);
    bool remove(const User &user);
    bool remove(const std::string &name);
    unsigned int getUserNum();
    bool updateUser(User &user);
    bool updatePrfLabel(User &user, LabelList prfL);
    bool findUser(User &user);

    std::vector<tableNode*> getTable();

private:
    unsigned int maxUserNum;
    unsigned int userNum;


    std::vector<tableNode*> Table;
    std::vector<tableNode*> creatTable();
};


#endif //SOFTWARE_USERMAP_H
