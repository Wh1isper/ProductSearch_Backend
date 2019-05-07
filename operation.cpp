#include "operation.h"

Commodity creatCommodity(const std::string &name, float price, LabelList &label, Store &Sto) {
    return Commodity(name, price, label, Sto.getSid());
}

Commodity creatCommodity(const std::string &name, float price, LabelList &label, int sid) {
    return Commodity(name, price, label, sid);
}

Commodity creatCommodity(const std::string &name, float price, int sid) {
    return Commodity(name, price, sid);
}

Commodity creatCommodity(const std::string &name, float price, Store &Sto) {
    return Commodity(name, price, Sto.getSid());
}

Label creatLabel(const std::string &str) {
    return Label(str);
}

Store creatStore(const std::string &name, const std::string &plat) {
    return Store(name, plat);
}

Store creatStore(const std::string &name, const std::string &plat, CommodityMap &cmdt) {
    return Store(name, plat, cmdt);
}

Store creatStore(const std::string &name, const std::string &plat, Commodity &cmdt) {
    return Store(name, plat, cmdt);
}

StoreMap creatStoreMap() {
    return StoreMap();
}

StoreMap creatStoreMap(unsigned int max) {
    return StoreMap(max);
}

CommodityMap creatCommodityMap(unsigned int max) {
    return CommodityMap(max);
}

CommodityMap creatCommodityMap(Commodity &cmdt) {
    return CommodityMap(cmdt);
}

StoreMap readStoreMap(){
    Util reader;
    return reader.readFiles();
}

bool saveStoreMap(StoreMap &SM){
    Util writer;
    return writer.saveFiles(SM);
}

bool isStore(Store &sto) {
    return sto.getSid() != -1;
}

bool isCommodity(Commodity &cmdt) {
    return cmdt.getSid() != -1;
}


Store &addCommodity(StoreMap &SM, Store &S, Commodity &C) {
    return addCommodity(SM, S.getSid(), C);
}

Store &addCommodity(StoreMap &SM, int sid, Commodity &C, const std::string &label) {
    C.addLabel(label);
    return addCommodity(SM, sid, C);
}

Store &addCommodity(StoreMap &SM, int sid, Commodity &C, const std::vector<std::string> &lblList) {
    C.addLabel(lblList);
    return addCommodity(SM, sid, C);
}

Store &addCommodity(StoreMap &SM, Store &S, Commodity &C, const std::string &label) {
    C.addLabel(label);
    return addCommodity(SM, S, C);
}

Store &addCommodity(StoreMap &SM, Store &S, Commodity &C, const std::vector<std::string> &lblList) {
    C.addLabel(lblList);
    return addCommodity(SM, S, C);
}

Store &addCommodity(StoreMap &SM, int sid, Commodity &C) {
    Store &S = SM.getStore(sid);
    if (S.getComMap().insert(C))
        SM.storeChanged(sid);
    return S;
}

Store &addLabel(StoreMap &SM, int sid, int cid, const std::string &label) {
    Commodity &C = SM.getStore(sid).getComMap().getCommodity(cid);
    C.addLabel(label);
    if (isCommodity(C))
        SM.storeChanged(sid);
    return SM.getStore(sid);
}

Store &addLabel(StoreMap &SM, int sid, Commodity &C, const std::string &label) {
    return addLabel(SM, sid, C.getCid(), label);
}

Store &addLabel(StoreMap &SM, Store &S, int cid, const std::string &label) {
    return addLabel(SM, S.getSid(), cid, label);
}

Store &addLabel(StoreMap &SM, Store &S, Commodity &C, const std::string &label) {
    return addLabel(SM, S.getSid(), C.getCid(), label);
}

Store &addLabel(StoreMap &SM, int sid, int cid, const std::vector<std::string> &lblList) {
    Commodity &C = SM.getStore(sid).getComMap().getCommodity(cid);
    C.addLabel(lblList);
    if (isCommodity(C))
        SM.storeChanged(sid);
    return SM.getStore(sid);
}

Store &addLabel(StoreMap &SM, int sid, Commodity &C, const std::vector<std::string> &lblList) {
    return addLabel(SM, sid, C.getCid(), lblList);
}

Store &addLabel(StoreMap &SM, Store &S, int cid, const std::vector<std::string> &lblList) {
    return addLabel(SM, S.getSid(), cid, lblList);
}

Store &addLabel(StoreMap &SM, Store &S, Commodity &C, const std::vector<std::string> &lblList) {
    return addLabel(SM, S.getSid(), C.getCid(), lblList);
}

Store &delLabel(StoreMap &SM, int sid, int cid, const std::string &label) {
    Commodity &C = SM.getStore(sid).getComMap().getCommodity(cid);
    C.removeLabel(label);
    if (isCommodity(C))
        SM.storeChanged(sid);
    return SM.getStore(sid);
}

Store &delLabel(StoreMap &SM, int sid, Commodity &C, const std::string &label) {
    return delLabel(SM, sid, C.getCid(), label);
}

Store &delLabel(StoreMap &SM, Store &S, int cid, const std::string &label) {
    return delLabel(SM, S.getSid(), cid, label);
}

Store &delLabel(StoreMap &SM, Store &S, Commodity &C, const std::string &label) {
    return delLabel(SM, S.getSid(), C.getCid(), label);
}

Store cancelAllChanges(StoreMap &SM, int sid) {
    Util reader;
    Store S = reader.readFile(sid);
    SM.update(S);
    SM.setUnchanged(sid);
    return S;
}

Store cancelAllChanges(StoreMap &SM, Store &S) {
    Util reader;
    S = reader.readFile(S.getSid());
    SM.update(S);
    SM.setUnchanged(S.getSid());
    return S;
}

bool saveAllchanges(StoreMap &SM) {
    Util writer;
    return writer.saveFiles(SM);
}

Store loadStore(StoreMap &SM, int sid) {
    Util reader;
    SM = reader.readFiles();
    return SM.getStore(sid);
}

bool delStore(StoreMap &SM, Store &S) {
    return SM.remove(S);
}

bool delStore(StoreMap &SM, int sid) {
    return SM.remove(sid);
}

const Commodity &getCommodity(Store S, ComInfo Info) {
        return S.getComMap().getCommodity(Info.getCid());
}

const Commodity &getCommodity(StoreMap SMap, ComInfo Info) {
    return SMap.getStore(Info.getSid()).getComMap().getCommodity(Info.getCid());
}

std::vector<Commodity> searchCmdt(Label2Com index, StoreMap SMap, Label lbl){
    std::vector<ComInfo> Info = index.singleSearch(lbl);
    std::vector<Commodity> res;
    for (const ComInfo &info:Info){
        res.push_back(getCommodity(SMap,info));
    }
    return res;
}
std::vector<Commodity> searchCmdt_single(Label2Com index, StoreMap SMap, LabelList lbl){
    std::vector<ComInfo> Info = index.singleSearch(lbl);
    std::vector<Commodity> res;
    for (const ComInfo &info:Info){
        res.push_back(getCommodity(SMap,info));
    }
    return res;
}
std::vector<Commodity> searchCmdt_mult(Label2Com index, StoreMap SMap, LabelList lbl){
    std::vector<std::vector<ComInfo>> InfoList = index.multSearch(lbl);
    std::vector<Commodity> res;
    for (const std::vector<ComInfo> &curList:InfoList){
        for (const ComInfo &info:curList) {
            res.push_back(getCommodity(SMap,info));
        }
    }
    return res;
}