/*
 * 作者：Wh1isper at 2019-04-30
 * 说明：
 *      api封装函数
*/

#ifndef SOFTWARE_OPERATION_H
#define SOFTWARE_OPERATION_H

#include "database/CommodityMap.h"
#include "database/StoreMap.h"
#include "database/UserMap.h"
#include "search/Label2Com.h"
#include "util/Util.h"

typedef Label2Com::ComInfo ComInfo;
typedef std::string Label;

// -----------------------------------基本的类操作---------------------------------------------
// 创建用户
User creatUser(const std::string &name);

User creatUser(const std::string &name, LabelList preList);

User creatUser(const std::string &name, const std::string &pwd, LabelList preList);

// 创建用户图，可选max为分配的哈希表长度
UserMap creatUserMap();

UserMap creatUserMap(unsigned long max);

// 创建商品，可选是否直接定义标签
Commodity creatCommodity(const std::string &name, float price, LabelList &label, Store &Sto);

Commodity creatCommodity(const std::string &name, float price, LabelList &label, int sid);

Commodity creatCommodity(const std::string &name, float price, int sid);

Commodity creatCommodity(const std::string &name, float price, Store &Sto);

// 创建标签
Label creatLabel(const std::string &str);

// 创建商户，可选是否直接定义商品
Store creatStore(const std::string &name, const std::string &plat);

Store creatStore(const std::string &name, const std::string &plat, CommodityMap &cmdt);

Store creatStore(const std::string &name, const std::string &plat, Commodity &cmdt);

// 创建商户图，可选max为动态表最大长度
StoreMap creatStoreMap();

StoreMap creatStoreMap(unsigned int max);

CommodityMap creatCommodityMap(unsigned int max);

CommodityMap creatCommodityMap(Commodity &cmdt);

// 存取封装
StoreMap readStoreMap();

bool saveStoreMap(StoreMap &SM);

// 判断函数
bool isStore(Store &sto);

bool isCommodity(Commodity &cmdt);

// -----------------------------------商户管理操作---------------------------------------------
// 增加商品
Store &addCommodity(StoreMap &SM, Store &S, Commodity &C);

Store &addCommodity(StoreMap &SM, int sid, Commodity &C);

Store &addCommodity(StoreMap &SM, Store &S, Commodity &C, const std::string &label);

Store &addCommodity(StoreMap &SM, int sid, Commodity &C, const std::string &label);

Store &addCommodity(StoreMap &SM, Store &S, Commodity &C, const std::vector<std::string> &lblList);

Store &addCommodity(StoreMap &SM, int sid, Commodity &C, const std::vector<std::string> &lblList);
// 删除商品
Store &delCommodity(StoreMap &SM, Store &S, Commodity &C);

Store &delCommodity(StoreMap &SM, Store &S, int cid);

Store &delCommodity(StoreMap &SM, int sid, Commodity &C);

Store &delCommodity(StoreMap &SM, int sid, int cid);

// 为商品增加标签
Store &addLabel(StoreMap &SM, int sid, int cid, const std::string &label);

Store &addLabel(StoreMap &SM, int sid, Commodity &C, const std::string &label);

Store &addLabel(StoreMap &SM, Store &S, int cid, const std::string &label);

Store &addLabel(StoreMap &SM, Store &S, Commodity &C, const std::string &label);

Store &addLabel(StoreMap &SM, int sid, int cid, const std::vector<std::string> &lblList);

Store &addLabel(StoreMap &SM, int sid, Commodity &C, const std::vector<std::string> &lblList);

Store &addLabel(StoreMap &SM, Store &S, int cid, const std::vector<std::string> &lblList);

Store &addLabel(StoreMap &SM, Store &S, Commodity &C, const std::vector<std::string> &lblList);

// 删除商品标签
Store &delLabel(StoreMap &SM, int sid, int cid, const std::string &label);

Store &delLabel(StoreMap &SM, int sid, Commodity &C, const std::string &label);

Store &delLabel(StoreMap &SM, Store &S, int cid, const std::string &label);

Store &delLabel(StoreMap &SM, Store &S, Commodity &C, const std::string &label);

// 取消更改
Store cancelAllChanges(StoreMap &SM, int sid);

Store cancelAllChanges(StoreMap &SM, Store &S);
// 保存更改
bool saveAllchanges(StoreMap &SM);
// 加载商户图并返回某个商户
Store loadStore(StoreMap &SM, int sid);

// -----------------------------------商店操作---------------------------------------------
// 商店创建 返回sid
int registStore(StoreMap &SM, Store &S);

// 删除商店
bool delStore(StoreMap &SM, Store &S);

bool delStore(StoreMap &SM, int sid);

// 更新商店信息
bool updateStore(StoreMap &SM, Store &S);

// -----------------------------------商户用户操作---------------------------------------------

// 新建商店
User addStore(User &UM,StoreMap &SM, Store &S);

// 删除商店
User delStore(User &UM,StoreMap &SM, Store &S);

// 更新用户图
bool updateStoreUserMap(UserMap &UMap, User &User);

// 保存用户图
bool saveStoreUserMap(UserMap &UMap);

UserMap loadStoreUserMap();

// 用户登入成功，返回用户信息
User loginStoreUser(UserMap &UMap, const std::string &name);

// 用户注册
bool registStoreUser(UserMap &UMap, User &usr);

// 用户销号
bool removeStoreUser(UserMap &UMap, const std::string &name);

bool removeStoreUser(UserMap &UMap, const User &usr);

// -----------------------------普通用户搜索、注册、登入、销号操作------------------------------
// 由商品检索信息获得商品
const Commodity &getCommodity(StoreMap SMap, ComInfo Info);

const Commodity &getCommodity(Store S, ComInfo Info);

// 单标签搜索
std::vector<Commodity> searchCmdt(Label2Com &index, StoreMap &SMap, const Label &lbl);

// 精确查找，所有标签交集
std::vector<Commodity> searchCmdt_single(Label2Com &index, StoreMap &SMap, LabelList &lbl);

// 模糊查找
std::vector<Commodity> searchCmdt_mult(Label2Com &index, StoreMap &SMap, LabelList &lbl);

// 设置用户喜好表
User &setPrfList(User &Usr, const LabelList &Lbl);

// 更新用户喜好表
User &updatePrfList(User &Usr, const Label &Lbl);

User &updatePrfList(User &Usr, const LabelList &Lbl);

// 更新用户图
bool updateUserMap(UserMap &UMap, User &User);

// 保存用户图
bool saveUserMap(UserMap &UMap);

// 加载用户图

UserMap loadUserMap();

// 用户登入成功，返回用户信息
User loginUser(UserMap &UMap, const std::string &name);

// 用户注册
bool registUser(UserMap &UMap, User &usr);

// 用户销号
bool removeUser(UserMap &UMap, const std::string &name);

bool removeUser(UserMap &UMap, const User &usr);

#endif //SOFTWARE_OPERATION_H