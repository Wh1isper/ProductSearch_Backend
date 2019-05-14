/*
 * 作者：Wh1isper at 2019-04-30
 * 说明：
 *      商户，用于存储商户信息、产品图
 *
*/

#ifndef SOFTWARE_STORE_H
#define SOFTWARE_STORE_H

#include <string>
#include "CommodityMap.h"

class Store {
public:
    // -----------------------------------构造函数---------------------------------------------
    Store();

    Store(const std::string &name, const std::string &plat);

    Store(const std::string &name, const std::string &plat, CommodityMap &cmdt);

    Store(const std::string &name, const std::string &plat, Commodity &cmdt);
    // -----------------------------------功能函数---------------------------------------------
    void setName(const std::string &name);      // 设置商店名

    void setPlat(const std::string &plat);      // 设置平台名

    void addCommondity(Commodity &cmdt);        // 添加商品，建议使用operation.h中的api

    // ！！谨慎调用
    void setCommodityMap(CommodityMap &cmdt);   // 设置商品图，可用于初始化
    // ！！谨慎调用
    void setSid(int sid);                       // 设置商店sid，同时会更改对应商店商品中的sid
    // -----------------------------------查询(get)函数---------------------------------------------
    CommodityMap &getComMap();      // 获得商品图，可被修改

    int getCommodityNum() const;    // 获得商品数量

    int getSid() const;             // 获得商户sid

    static int getSid(Store &sto);  // 获得商户sid

    std::string getName() const;    // 获得商品名

    std::string getPlat() const;    // 获得平台名

private:
    std::string Name;       // 存储商户名
    std::string Plat;       // 存储商户平台
    CommodityMap CmdtMap;   // 存储商户对应商品图
    int Sid;                // 当前商户对应id

};


#endif //SOFTWARE_STORE_H
