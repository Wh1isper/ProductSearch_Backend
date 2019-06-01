#include "operation.h"

User creatUser(const std::string &name) {
    return User(name);
}

User creatUser(const std::string &name, LabelList preList) {
    return User(name, preList);
}

User creatUser(const std::string &name, const std::string &pwd, LabelList preList) {
    return User(name, pwd, preList);
}

UserMap creatUserMap() {
    return UserMap();
}

UserMap creatUserMap(unsigned long max) {
    return UserMap(max);
}

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

StoreMap readStoreMap() {
    Util reader;
    return reader.readFiles();
}

bool saveStoreMap(StoreMap &SM) {
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

Store &delCommodity(StoreMap &SM, Store &S, Commodity &C) {
    S.getComMap().remove(C);
    SM.storeChanged(S.getSid());
    return S;
}

Store &delCommodity(StoreMap &SM, Store &S, int cid) {
    S.getComMap().remove(cid);
    SM.storeChanged(S.getSid());
    return S;
}

Store &delCommodity(StoreMap &SM, int sid, Commodity &C) {
    Store &S = SM.getStore(sid);
    return delCommodity(SM, S, C);
}

Store &delCommodity(StoreMap &SM, int sid, int cid) {
    Store &S = SM.getStore(sid);
    return delCommodity(SM, S, cid);
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

int registStore(StoreMap &SM, Store &S) {
    SM.insert(S);
    return S.getSid();
}

bool updateStore(StoreMap &SM, Store &S) {
    SM.update(S);
}

const Commodity &getCommodity(Store S, ComInfo Info) {
    return S.getComMap().getCommodity(Info.getCid());
}

const Commodity &getCommodity(StoreMap SMap, ComInfo Info) {
    return SMap.getStore(Info.getSid()).getComMap().getCommodity(Info.getCid());
}

std::vector<Commodity> searchCmdt(Label2Com &index, StoreMap &SMap, const Label &lbl) {
    std::vector<ComInfo> Info = index.singleSearch(lbl);
    std::vector<Commodity> res;
    for (const ComInfo &info:Info) {
        res.push_back(getCommodity(SMap, info));
    }
    return res;
}

std::vector<Commodity> searchCmdt_single(Label2Com &index, StoreMap &SMap, LabelList &lbl) {
    std::vector<ComInfo> Info = index.singleSearch(lbl);
    std::vector<Commodity> res;
    for (const ComInfo &info:Info) {
        res.push_back(getCommodity(SMap, info));
    }
    return res;
}

std::vector<Commodity> searchCmdt_mult(Label2Com &index, StoreMap &SMap, LabelList &lbl) {
    std::vector<std::vector<ComInfo>> InfoList = index.multSearch(lbl);
    std::vector<Commodity> res;
    for (const std::vector<ComInfo> &curList:InfoList) {
        for (const ComInfo &info:curList) {
            res.push_back(getCommodity(SMap, info));
        }
    }
    return res;
}

std::vector<Commodity> randomSearch(Label2Com &index, StoreMap &SMap, User &U) {
    LabelList List = U.getPreferList();
    std::vector<Commodity> res;
    double decracePossibility = 0.5; // 初始为概率为0.5 按0.1递减
    for (const Label &L:List.getLabelList()) {
        std::vector<ComInfo> InfoList = index.singleSearch(L);
        for (const ComInfo &info:InfoList) {
            if (rand() / double(RAND_MAX) > decracePossibility) {
                res.push_back(getCommodity(SMap, info));
                if (res.size() == 100)
                    return res;
            }
        }
        decracePossibility -= 0.1;
        if (decracePossibility < 1e10)
            break;
    }
    return res;
}

User &setPrfList(User &Usr, const LabelList &Lbl) {
    Usr.setLabelList(Lbl);
    return Usr;
}

User &updatePrfList(User &Usr, const Label &Lbl) {
    Usr.updatePrfList(Lbl);
    return Usr;
}

User &updatePrfList(User &Usr, const LabelList &Lbl) {
    Usr.updatePrfList(Lbl);
    return Usr;
}

bool updateUserMap(UserMap &UMap, User &User) {
    return UMap.updateUser(User);
}

bool saveUserMap(UserMap &UMap) {
    Util writer;
    return writer.saveUserFiles(UMap);
}

UserMap loadUserMap() {
    Util reader;
    return reader.loadUserFiles();
}

User loginUser(UserMap &UMap, const std::string &name) {
    return UMap.getUser(name);
}

bool removeUser(UserMap &UMap, const std::string &name) {
    return UMap.remove(name);
}

bool removeUser(UserMap &UMap, const User &usr) {
    return UMap.remove(usr);
}

bool registUser(UserMap &UMap, User &usr) {
    return UMap.insert(usr);
}

User &addStore(User &U, StoreMap &SM, Store &S) {
    SM.insert(S);
    U.addStore(S);
    return U;
}

User &delStore(User &U, StoreMap &SM, Store &S) {
    U.removeStore(S);
    SM.remove(S);
    return U;
}

bool updateStoreUserMap(UserMap &UMap, User &User) {
    return UMap.updateUser(User);
}

bool saveStoreUserMap(UserMap &UMap) {
    Util writer;
    return writer.saveStoreUserFiles(UMap);
}

UserMap loadStoreUserMap() {
    Util reader;
    return reader.loadStoreUserFiles();
}

User loginStoreUser(UserMap &UMap, const std::string &name) {
    return UMap.getUser(name);
}

bool removeStoreUser(UserMap &UMap, const std::string &name) {
    return UMap.remove(name);
}

bool removeStoreUser(UserMap &UMap, const User &usr) {
    return UMap.remove(usr);
}

bool registStoreUser(UserMap &UMap, User &usr) {
    return UMap.insert(usr);
}