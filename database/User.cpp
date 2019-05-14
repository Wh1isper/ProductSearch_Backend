#include "User.h"

User::User() {
    Uname = "Unknown";
    Prefer = LabelList();
    Uid = 0;
}

User::User(const std::string &name) {
    Uname = name;
    Prefer = LabelList();
    setUid();
}


User::User(const std::string &name, LabelList &pre) {
    Uname = name;
    Prefer = pre;
    setUid();
}

unsigned long User::getUid(User &user) {
    return user.Uid;
}

unsigned long User::getUid() const {
    return Uid;
}

unsigned long User::getUid(const std::string &name) {
    return name == "Unknown"?0:hashFun(name);
}

void User::setUid() {
    Uid = hashFun();
}

unsigned long User::hashFun() const {
    unsigned long res = 0;
    for (char s:Uname){
        res += int(s);
    }
    return res;
}

unsigned long User::hashFun(const std::string &name){
    unsigned long res = 0;
    for (char s:name){
        res += int(s);
    }
    return res;
}

User::User(const User &user) {
    Uname = user.Uname;
    Uid = user.Uid;
    Prefer = user.Prefer;
}

bool User::operator==(const User &B) const {
    return Uname == B.Uname;
}

std::string User::getName() const {
    return Uname;
}

LabelList User::getPreferList() const {
    return Prefer;
}

void User::setLabelList(LabelList prf) {
    Prefer = prf;
}


