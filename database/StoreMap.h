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
    // -----------------------------------构造函数---------------------------------------------
    StoreMap();

    explicit StoreMap(unsigned int max);
    // -----------------------------------功能函数---------------------------------------------
    bool insert(Store &sto);  // 插入商户

    Store &getStore(int sid); // 获取商户信息，可被修改

    bool remove(int sid);     // 从商户图中删除某个商户

    bool remove(Store &sto);  // 从商户图中删除某个商户

    bool update(Store &sto);  // 根据商户更新商户图
    // -----------------------------------存取api函数---------------------------------------------
    // ！！谨慎调用，这部分函数用于Util.h调用
    void setUnchanged(int sid);         // 取消/恢复操作
    void storeChanged(int sid);         // 记录被修改的商户
    void setStoreNum(unsigned int num); // 设置商户图大小
    // -----------------------------------功能函数---------------------------------------------
    int getStoreNum();                  // 获得商店数目

    std::vector<Store> getStoreList();  // 获得商店列表

    std::vector<int> getChangedStore(); // 获得被修改的商户的索引

private:
    unsigned int maxStoreNum;           // 动态表最大长度
    unsigned int storeNum;              // 动态表当前长度
    std::vector<Store> Table;           // 动态表存储商户

    std::vector<Store> creatTable();

    std::vector<int> ChangeStore;       // 用于索引被修改的商户

    std::vector<int> creatChangeStoreTable(); // 初始化动态表

    void expanTable();              // 动态表扩张

    void shrinkTable();             // 动态表收缩

};


#endif //SOFTWARE_STOREMAP_H
