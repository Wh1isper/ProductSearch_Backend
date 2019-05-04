#include "User.h"

User::User() {
    Uid = -1;
    Uname = "Unknown";
    Prefer = LabelList();
}

User::User(const std::string &name) {
    Uid = -1;
    Uname = name;
    Prefer = LabelList();
}


User::User(const std::string &name, LabelList &pre) {
    Uid = -1;
    Uname = name;
    Prefer = pre;
}

int User::getUid(User &user) {
    return user.Uid;
}

int User::getUid() {
    return Uid;
}

void User::setUid(int uid) {
    Uid = uid;
}