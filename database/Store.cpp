//
// Created by 95735 on 2019/4/16 0016.
//

#include "Store.h"

Store::Store() {
    Name = "Unknown";
    Plat = "Unknown";
    CmdtMap = CommodityMap();
    Sid = -1;
}

Store::Store(const std::string &name, const std::string &plat) {
    Name = name;
    Plat = plat;
    CmdtMap = CommodityMap();
    Sid = -1;
}

Store::Store(const std::string &name, const std::string &plat, CommodityMap &cmdt) {
    Name = name;
    Plat = plat;
    setCommodityMap(cmdt);
    Sid = -1;
}
Store::Store(const std::string &name, const std::string &plat, Commodity &cmdt) {
    Name = name;
    Plat = plat;
    CmdtMap = CommodityMap(cmdt);
    Sid = -1;
}

void Store::setCommodityMap(CommodityMap &cmdt) {
    CmdtMap = cmdt;
    for (Commodity &C:cmdt.getComList()) {
        C.setSid(Sid);
    }
}
void Store::addCommondity(Commodity &cmdt) {
    cmdt.setSid(Sid);
    CmdtMap.insert(cmdt);
}
int Store::getSid(Store &sto) {
    return sto.Sid;
}
int Store::getCommodityNum() {
    return CmdtMap.getComNum();
}

int Store::getSid() {
    return Sid;
}

void Store::setSid(int sid) {
    Sid = sid;
}

CommodityMap & Store::getComMap() {
    return CmdtMap;
}

std::string Store::getName() {
    return Name;
}

std::string Store::getPlat() {
    return Plat;
}

void Store::setName(const std::string &name) {
    Name = name;
}
void Store::setPlat(const std::string &plat) {
    Plat = plat;
}
