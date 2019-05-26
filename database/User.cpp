#include "User.h"

User::User() {
    Uname = "Unknown";
    Prefer = LabelList();
    Uid = 0;
    password = encode("123456");
}

User::User(const std::string &name) {
    Uname = name;
    Prefer = LabelList();
    setUid();
    password = encode("123456");
}

User::User(const std::string &name, LabelList &pre) {
    Uname = name;
    Prefer = pre;
    setUid();
    password = encode("123456");
}

User::User(const std::string &name,const std::string &pwd) {
    Uname = name;
    Prefer = LabelList();
    setUid();
    password = encode(pwd);
}

User::User(const std::string &name, const std::string &pwd, LabelList &pre) {
    Uname = name;
    Prefer = pre;
    setUid();
    password = encode(pwd);
}

User::User(const std::string &name, const std::string &pwd, LabelList &pre, bool loadFromFiles) {
    Uname = name;
    Prefer = pre;
    setUid();
    password = pwd;
}

unsigned long User::getUid(User &user) {
    return user.Uid;
}

unsigned long User::getUid() const {
    return Uid;
}

unsigned long User::getUid(const std::string &name) {
    return name == "Unknown" ? 0 : hashFun(name);
}

void User::setUid() {
    Uid = hashFun();
}

unsigned long User::hashFun() const {
    unsigned long res = 0;
    for (char s:Uname) {
        res += int(s);
    }
    return res;
}

unsigned long User::hashFun(const std::string &name) {
    unsigned long res = 0;
    for (char s:name) {
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

void User::updatePrfList(const Label &L) {
    Prefer.push_ahead(L);
}

void User::updatePrfList(const LabelList &L) {
    Prefer.push_ahead(L);
}

void User::setLabelList(LabelList prf) {
    Prefer = prf;
}

void User::setPassword(const std::string &pwd) {
    password = encode(pwd);
}

std::string User::getPassword() const{
    return decode(password);
}

std::string User::encode(std::string input) {
    return input;
}

std::string User::decode(std::string input) {
    return input;
}

std::string User::getUndecodePassword() const {
    return password;
}

bool User::passwordCheck(const std::string &pwdInput) const{
    return password == encode(password);
}

bool User::undecodePasswordCheck(const std::string &pwdInput) const{
    return password == pwdInput;
}

std::vector<int> User::getStoreList() const {
    std::vector<int> res;
    for (const Label &L:Prefer.getLabelList()){
        res.push_back(std::stoi(L));
    }
    return res;
}

void User::addStore(int sid) {
    Prefer.push_ahead(std::to_string(sid));
}

void User::addStore(const Store &sto) {
    Prefer.push_ahead(std::to_string(sto.getSid()));
}

void User::removeStore(int sid) {
    Prefer.remove(std::to_string(sid));
}

void User::removeStore(const Store &sto) {
    Prefer.remove(std::to_string(sto.getSid()));
}