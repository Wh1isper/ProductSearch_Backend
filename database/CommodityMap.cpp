#include "CommodityMap.h"

CommodityMap::CommodityMap() {
    maxComNum = 5;
    comNum = 1;
    Table = creatTable();
}

CommodityMap::CommodityMap(unsigned int max) {
    if(max < 2)
        max = 2;
    maxComNum = max;
    comNum = 1;
    Table = creatTable();
}
CommodityMap::CommodityMap(Commodity &cmdt) {
    maxComNum = 5;
    comNum = 1;
    Table = creatTable();
    this->insert(cmdt);
}

bool CommodityMap::insert(Commodity &cmdt) {
    if (!isInStoreMap(cmdt)) // 无商户
        return false;
    if(isInCmdtMap(cmdt))  // 已分类
        return false;
    int pos = 1;
    while (Table[pos].getCid() != -1)
        ++pos;

    cmdt.setCid(pos);
    Table[pos] = cmdt;
    if (pos == comNum)
        comNum += 1;
    if (comNum + 1 >= maxComNum)
        expanTable();
    return true;
}

Commodity &CommodityMap::getCommodity(int cid) {
    if (cid > maxComNum-1)
        return Table[0];
    return Table[cid];
}


int CommodityMap::getComNum() {
    return comNum-1;
}
bool CommodityMap::remove(int cid) {
    if (cid > maxComNum - 1)
        return false;
    if (Table[cid].getCid() != -1) {
        Table[cid] = Commodity();
        comNum -= 1;
        return true;
    } else
        return false;

}

bool CommodityMap::remove(Commodity & cmdt) {
    if(!isInStoreMap(cmdt))
        return false;
    for (int i = 1; i < Table.size(); ++i) {
        if (Table[i].getSid() == cmdt.getSid()) {
            Table[i] = Commodity();
            comNum -= 1;
            if (comNum < maxComNum/4)
                shrinkTable();
            return true;
        }
    }
    return false;
}

std::vector<Commodity> CommodityMap::getComList() {
    std::vector<Commodity> res;
    for(Commodity C:Table){
        if(C.getCid() != -1)
            res.push_back(C);
        if(res.size() == getComNum())
            break;
    }
    return res;
}

std::vector<Commodity> CommodityMap::creatTable() {
    return std::vector<Commodity>(maxComNum);
}

bool CommodityMap::isInCmdtMap(Commodity &cmdt) {
    return cmdt.getCid() != -1;
}

bool CommodityMap::isInStoreMap(Commodity &cmdt) {
    return cmdt.getSid() != -1;
}

bool CommodityMap::update(Commodity &cmdt) {
    if (cmdt.getCid() == -1)
        return insert(cmdt);
    if(cmdt.getCid() > maxComNum-1)
        return false;
    int cid = cmdt.getCid();
    Table[cid] = cmdt;
    return true;
}


void CommodityMap::expanTable() {
    maxComNum *= 2;
    Table.resize(maxComNum);
}

void CommodityMap::shrinkTable() {
    int i = 1;
    int j = static_cast<int>(Table.size() - 1);
    while(i<j){
        while (Table[i].getCid() != -1 && i<j)
            i++;
        while (Table[j].getCid() == -1 && i<j)
            j--;
        if(i<j){
            Table[i] = Table[j];
            Table[j] = Commodity();
            Table[i].setCid(i);
        }
    }
}
