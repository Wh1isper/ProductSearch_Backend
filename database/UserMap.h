/*
 * 作者：Wh1isper at 2019-04-30
 * 说明：
 *      用户图，用于存储全部用户信息
 *      ！！注意：尚未开工
*/

#ifndef SOFTWARE_USERMAP_H
#define SOFTWARE_USERMAP_H

#include "User.h"
#include <vector>

class UserMap {
public:
    UserMap();
    explicit UserMap(unsigned int max);
    bool insert(User &user);
    User & getUser(int uid);
    bool remove(int uid);
    bool remove(User &user);
    int getUserNum();
    bool update(User &user);
    std::vector<User> getUserList();
    
private:
    unsigned int maxUserNum;
    unsigned int userNum;
    std::vector<User> Table;
    std::vector<User> creatTable();
};


#endif //SOFTWARE_USERMAP_H
