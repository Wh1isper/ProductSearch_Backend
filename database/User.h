/*
 * 作者：Wh1isper at 2019-04-30
 * 说明：
 *      存储用户信息和偏好
 *
*/

#ifndef SOFTWARE_USER_H
#define SOFTWARE_USER_H

#include <string>
#include "LabelList.h"
#include "Store.h"

class User {
public:
    // -----------------------------------构造函数---------------------------------------------
    // 默认密码为123456
    User();

    explicit User(const std::string &name);

    User(const User &user);

    User(const std::string &name, LabelList &pre);

    User(const std::string &name, const std::string &pwd);

    User(const std::string &name, const std::string &pwd,LabelList &pre);

    User(const std::string &name, const std::string &pwd,LabelList &pre, bool loadFromFiles); // 从文件中读取时使用的构造函数
    // -----------------------------------功能函数---------------------------------------------
    void updatePrfList(const Label &L);     // 更新用户喜好表，前插或前移插入一个标签

    void updatePrfList(const LabelList &L); // 更新用户喜好表，前插或前移多个标签

    void addStore(int sid);   // 新增商户商店，在StoreMap.insert()之后使用

    void addStore(const Store &sto);

    void removeStore(int sid); // 删除商户商店，在StoreMap.remove()之前使用

    void removeStore(const Store &sto);

    void setLabelList(LabelList prf); // 设置用户喜好表

    bool passwordCheck(const std::string &pwdInput) const; // 用于检测用户输入密码是否正确，输入未加密的密码，返回bool

    bool undecodePasswordCheck(const std::string &pwdInput) const;// 用于检测用户输入密码是否正确，输入加密的密码，返回bool
    // ！！谨慎调用
    void setUid(); // 根据哈希函数重设User的Uid

    void setPassword(const std::string &pwd); // 重置密码时使用，输入未被加密的密码，更改用户原密码为加密后的密码
    // -----------------------------------查询(get)函数---------------------------------------------
    unsigned long getUid() const; // 查询当前用户Uid

    static unsigned long getUid(User &ur); // 查询用户Uid

    static unsigned long getUid(const std::string &name); // 计算用户Uid

    std::string getUndecodePassword() const; // 返回未被解密的密码，用于存储在文件中

    std::string getPassword() const;// 返回解密后的用户密码

    std::string getName() const; // 获得当前用户名

    LabelList getPreferList() const; // 获得用户喜好列表

    std::vector<int> getStoreList() const;
    // -----------------------------------哈希函数api---------------------------------------------
    unsigned long hashFun() const;

    static unsigned long hashFun(const std::string &name);
    // -----------------------------------重载函数---------------------------------------------
    bool operator==(const User &B) const;
    // -----------------------------------加密解密api------------------------------------------
    static std::string encode(std::string input);

    static std::string decode(std::string input);
private:
    unsigned long Uid{};
    std::string Uname;
    std::string password;
    LabelList Prefer;
    // LabelList
    // 对于用户：代表喜好标签列表
    // 对于商户：代表拥有的商店sid，可用于在StoreMap中查询
};


#endif //SOFTWARE_USER_H
