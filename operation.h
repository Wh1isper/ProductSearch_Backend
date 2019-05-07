/*
 * 作者：Wh1isper at 2019-04-30
 * 说明：
 *      api封装函数
 *      ！！注意：这里的函数将被重构以对应api封装
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
// 基本操作

Commodity creatCommodity(const std::string &name, float price, LabelList &label, Store &Sto);
Commodity creatCommodity(const std::string &name, float price, LabelList &label, int sid);
Commodity creatCommodity(const std::string &name, float price, int sid);
Commodity creatCommodity(const std::string &name, float price, Store &Sto);
Label creatLabel(const std::string &str);
Store creatStore(const std::string &name, const std::string &plat);
Store creatStore(const std::string &name, const std::string &plat, CommodityMap &cmdt);
Store creatStore(const std::string &name, const std::string &plat, Commodity &cmdt);
StoreMap creatStoreMap();
StoreMap creatStoreMap(unsigned int max);
CommodityMap creatCommodityMap(unsigned int max);
CommodityMap creatCommodityMap(Commodity &cmdt);
StoreMap readStoreMap();
bool saveStoreMap(StoreMap &SM);

bool isStore(Store &sto);
bool isCommodity(Commodity &cmdt);

// 商户管理操作
Store &addCommodity(StoreMap &SM, Store &S, Commodity &C);
Store &addCommodity(StoreMap &SM, int sid, Commodity &C);
Store &addCommodity(StoreMap &SM, Store &S, Commodity &C, const std::string &label);
Store &addCommodity(StoreMap &SM, int sid, Commodity &C, const std::string &label);
Store &addCommodity(StoreMap &SM, Store &S, Commodity &C, const std::vector<std::string> &lblList);
Store &addCommodity(StoreMap &SM, int sid, Commodity &C, const std::vector<std::string> &lblList);


Store &addLabel(StoreMap &SM, int sid, int cid, const std::string &label);
Store &addLabel(StoreMap &SM, int sid, Commodity &C, const std::string &label);
Store &addLabel(StoreMap &SM, Store &S, int cid, const std::string &label);
Store &addLabel(StoreMap &SM, Store &S, Commodity &C, const std::string &label);

Store &addLabel(StoreMap &SM, int sid, int cid, const std::vector<std::string> &lblList);
Store &addLabel(StoreMap &SM, int sid, Commodity &C, const std::vector<std::string> &lblList);
Store &addLabel(StoreMap &SM, Store &S, int cid, const std::vector<std::string> &lblList);
Store &addLabel(StoreMap &SM, Store &S, Commodity &C, const std::vector<std::string> &lblList);

Store &delLabel(StoreMap &SM, int sid, int cid, const std::string &label);
Store &delLabel(StoreMap &SM, int sid, Commodity &C, const std::string &label);
Store &delLabel(StoreMap &SM, Store &S, int cid, const std::string &label);
Store &delLabel(StoreMap &SM, Store &S, Commodity &C, const std::string &label);

Store cancelAllChanges(StoreMap &SM, int sid);
Store cancelAllChanges(StoreMap &SM, Store &S);
bool saveAllchanges(StoreMap &SM);
Store loadStore(StoreMap &SM, int sid);

// 商户账号操作
bool delStore(StoreMap &SM, Store &S);
bool delStore(StoreMap &SM, int sid);
int registStore(StoreMap &SM, Store &S); // 商户注册 返回sid
bool updateStore(StoreMap &SM, Store &S);// 更新商户信息

// 用户搜索操作
const Commodity &getCommodity(StoreMap SMap, ComInfo Info);
const Commodity &getCommodity(Store S, ComInfo Info);
std::vector<Commodity> searchCmdt(Label2Com index, StoreMap SMap, Label lbl);            // 单标签搜索
std::vector<Commodity> searchCmdt_single(Label2Com index, StoreMap SMap, LabelList lbl); // 精确查找，所有标签交集
std::vector<Commodity> searchCmdt_mult(Label2Com index, StoreMap SMap, LabelList lbl);   // 模糊查找

#endif //SOFTWARE_OPERATION_H