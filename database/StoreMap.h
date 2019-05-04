/*
 * 作者：Wh1isper at 2019-04-30
 * 说明：
 *      商户图，用于检索所有商户
 *
*/

#ifndef SOFTWARE_STOREMAP_H
#define SOFTWARE_STOREMAP_H

#include "Store.h"
#include <vector>
class StoreMap {
public:
    StoreMap();
    explicit StoreMap(unsigned int max);
    bool insert(Store &sto);  // 插入商户
    Store &getStore(int sid); // 获取商户信息并允许修改
    bool remove(int sid);     // 从商户图中删除某个商户
    bool remove(Store &sto);
    int getStoreNum();
    bool update(Store &sto);
    std::vector<Store> getStoreList();
    std::vector<int> getChangedStore();
    void setUnchanged(int sid);
    void storeChanged(int sid);
    void setStoreNum(unsigned int num);
private:
    unsigned int maxStoreNum;
    unsigned int storeNum;
    std::vector<Store> Table;
    std::vector<Store> creatTable();
    std::vector<int> ChangeStore;
    std::vector<int> creatChangeStoreTable();
    void expanTable();
    void shrinkTable();

};


#endif //SOFTWARE_STOREMAP_H
