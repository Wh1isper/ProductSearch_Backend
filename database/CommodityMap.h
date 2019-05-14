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
    // -----------------------------------构造函数---------------------------------------------
    CommodityMap();

    explicit CommodityMap(unsigned int max);

    explicit CommodityMap(Commodity &cmdt);
    // -----------------------------------功能函数---------------------------------------------
    bool insert(Commodity &cmdt); // 插入商品

    bool remove(Commodity &cmdt); // 移除商品

    bool remove(int cid);         // 根据cid移除商品

    bool update(Commodity &cmdt); // 更新商品信息
    // -----------------------------------查询(get)函数---------------------------------------------
    Commodity &getCommodity(int cid);    // 根据cid查询商品

    int getComNum() const;               // 获得当前商品数量

    std::vector<Commodity> getComList(); // 获得当前商品列表

private:
    unsigned int maxComNum;         // 动态表最大长度
    unsigned int comNum;            // 动态表当前长度
    std::vector<Commodity> Table;   // 动态表

    std::vector<Commodity> creatTable(); // 创建动态表

    void expanTable(); // 扩展动态表

    void shrinkTable(); // 收缩动态表

    bool isInStoreMap(Commodity &cmdt);

    bool isInCmdtMap(Commodity &cmdt);

};


#endif //SOFTWARE_COMMODITYMAP_H
