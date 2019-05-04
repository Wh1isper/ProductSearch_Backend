#include "UserMap.h"

UserMap::UserMap() {
    maxUserNum = 10;
    userNum = 1;
    Table = creatTable();
}

UserMap::UserMap(unsigned int max) {
    if (max < 2)
        max = 2;
    maxUserNum = max;
    userNum = 1;
    Table = creatTable();
}

bool UserMap::insert(User &user) {
    if (user.getUid() != -1)
        return false;
    int pos = 1;
    while (Table[pos].getUid() != -1)
        ++pos;

    user.setUid(pos);
    Table[pos] = user;
    if (pos == userNum)
        userNum += 1;
    if (userNum + 1 >= maxUserNum) {
        maxUserNum *= 2;
        Table.resize(maxUserNum);
    }
    return true;
}
bool UserMap::update(User &user) {
    if (user.getUid() == -1)
        return false;
    if(user.getUid() > maxUserNum-1)
        return false;
    Table[user.getUid()] = user;
    return true;
}

bool UserMap::remove(int uid) {
    if (uid > maxUserNum - 1)
        return false;
    if (Table[uid].getUid() != -1) {
        Table[uid] = User();
        userNum -= 1;
        return true;
    } else
        return false;

}

bool UserMap::remove(User &user) {
    if(user.getUid() == -1)
        return false;
    for (int i = 1; i < Table.size(); ++i) {
        if (Table[i].getUid() == user.getUid()) {
            Table[i] = User();
            userNum -= 1;
            return true;
        }
    }
    return false;
}

int UserMap::getUserNum() {
    return userNum - 1;
}

User &UserMap::getUser(int uid) {
    if (uid > uid-1)
        return Table[uid-1];
    return Table[uid];
}

std::vector<User> UserMap::creatTable() {
    return std::vector<User>(maxUserNum);
}

std::vector<User> UserMap::getUserList() {
    return std::vector<User>(Table);
}
