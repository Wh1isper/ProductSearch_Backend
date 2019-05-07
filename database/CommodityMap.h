/*
 * 作者：Wh1isper at 2019-04-30
 * 说明：
 *      产品图，添加在商户之下，索引所有产品
 *
*/
#ifndef SOFTWARE_COMMODITYMAP_H
#define SOFTWARE_COMMODITYMAP_H

#include "Commodity.h"
#include <vector>
class CommodityMap {
public:
    CommodityMap();
    explicit CommodityMap(unsigned int max);
    explicit CommodityMap(Commodity &cmdt);
    bool insert(Commodity & cmdt);
    Commodity &getCommodity(int cid);
    bool remove(Commodity & cmdt);
    bool remove(int cid);
    bool update(Commodity &cmdt);
    int getComNum() const ;
    std::vector<Commodity> getComList();

private:
    unsigned int maxComNum;
    unsigned int comNum;
    std::vector<Commodity> Table;
    std::vector<Commodity> creatTable();
    bool isInStoreMap(Commodity &cmdt);
    bool isInCmdtMap(Commodity &cmdt);
    void expanTable();
    void shrinkTable();

};


#endif //SOFTWARE_COMMODITYMAP_H
