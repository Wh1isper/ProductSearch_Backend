#include "StoreMap.h"

StoreMap::StoreMap() {
    maxStoreNum = 10;
    storeNum = 1;
    Table = creatTable();
    ChangeStore = creatChangeStoreTable();
}

StoreMap::StoreMap(unsigned int max) {
    if (max < 2)
        max = 2;
    maxStoreNum = max;
    storeNum = 1;
    Table = creatTable();
    ChangeStore = creatChangeStoreTable();
}

bool StoreMap::insert(Store &sto) {
    if (sto.getSid() != -1)
        return false;
    int pos = 1;
    while (Table[pos].getSid() != -1)
        ++pos;

    sto.setSid(pos);
    storeChanged(pos);
    Table[pos] = sto;
    if (pos == storeNum)
        storeNum += 1;
    if (storeNum + 1 >= maxStoreNum)
        expanTable();
    return true;
}

bool StoreMap::update(Store &sto) {
    if (sto.getSid() == -1)
        return insert(sto);
    if (sto.getSid() > maxStoreNum - 1)
        return false;
    int sid = sto.getSid();
    Table[sid] = sto;
    storeChanged(sid);
    return true;
}

bool StoreMap::remove(int sid) {
    if (sid > maxStoreNum - 1)
        return false;
    if (Table[sid].getSid() != -1) {
        Table[sid] = Store();
        storeChanged(sid);
        storeNum -= 1;
        if (storeNum < maxStoreNum / 4)
            shrinkTable();
        return true;
    } else
        return false;

}

bool StoreMap::remove(Store &sto) {
    if (sto.getSid() == -1)
        return false;
    for (int i = 1; i < Table.size(); ++i) {
        if (Table[i].getSid() == sto.getSid()) {
            Table[i] = Store();
            storeChanged(sto.getSid());
            storeNum -= 1;
            if (storeNum < maxStoreNum / 4)
                shrinkTable();
            return true;
        }
    }
    return false;
}

int StoreMap::getStoreNum() {
    return storeNum - 1;
}

Store &StoreMap::getStore(int sid) {
    if (sid > maxStoreNum - 1)
        return Table[Table.size() - 1];
    return Table[sid];
}

std::vector<Store> StoreMap::creatTable() {
    return std::vector<Store>(maxStoreNum);
}

std::vector<Store> StoreMap::getStoreList() {
    std::vector<Store> res;
    for (Store &S:Table) {
        if (S.getSid() != -1)
            res.push_back(S);
        if (res.size() == getStoreNum())
            break;
    }
    return res;
}

std::vector<int> StoreMap::creatChangeStoreTable() {
    return std::vector<int>(maxStoreNum, 0);
}

void StoreMap::storeChanged(int sid) {
    ChangeStore[sid] = 1;
}

void StoreMap::setStoreNum(unsigned int num) {
    storeNum = num;
}

std::vector<int> StoreMap::getChangedStore() {
    std::vector<int> ret(storeNum);
    unsigned int count = 0;
    for (int i = 0; i < ChangeStore.size() - 1; ++i) {
        if (ChangeStore[i])
            ret[count++] = i;
    }
    return ret;
}

void StoreMap::setUnchanged(int sid) {
    ChangeStore[sid] = 0;
}

void StoreMap::expanTable() {
    maxStoreNum *= 2;
    Table.resize(maxStoreNum);
    ChangeStore.resize(maxStoreNum);
}

void StoreMap::shrinkTable() {
    int i = 1;
    int j = static_cast<int>(Table.size() - 1);
    while (i < j) {
        while (Table[i].getSid() != -1 && i < j)
            i++;
        while (Table[j].getSid() == -1 && i < j)
            j--;
        if (i < j) {
            Table[i] = Table[j];
            Table[j] = Store();
            Table[i].setSid(i);
            storeChanged(i);
            CommodityMap newCM;
            for (Commodity C:Table[i].getComMap().getComList()) {
                C.setSid(i);
                C.setCid(-1);
                newCM.insert(C);
            }
            Table[i].setCommodityMap(newCM);
        }
    }
}
