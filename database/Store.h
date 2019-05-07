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
    Store();
    Store(const std::string &name, const std::string &plat);
    Store(const std::string &name, const std::string &plat, CommodityMap &cmdt);
    Store(const std::string &name, const std::string &plat, Commodity &cmdt);
    void setCommodityMap(CommodityMap &cmdt);
    void addCommondity(Commodity &cmdt);
    static int getSid(Store &sto);
    CommodityMap & getComMap();
    int getCommodityNum() const ;
    int getSid() const ;
    void setSid(int sid);
    std::string getName() const;
    std::string getPlat() const;
    void setName(const std::string &name);
    void setPlat(const std::string &plat);

private:
    std::string Name;
    std::string Plat;
    CommodityMap CmdtMap;
    int Sid;

};


#endif //SOFTWARE_STORE_H
