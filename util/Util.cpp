//
// Created by 95735 on 2019/4/29 0029.
//

#include "Util.h"

StoreMap Util::readFiles() {
    std::vector<int> sidList;
    std::ifstream fin(LISTPATH, std::ifstream::in);
    std::string buffer;
    if (!fin)
        return StoreMap();
    while (!fin.eof()) {
        int tmp;
        char *x;
        fin >> buffer;
        tmp = std::stoi(buffer);
        sidList.push_back(tmp);
    }
    sidList.pop_back();
    fin.close();
    StoreMap SM(static_cast<unsigned int>(sidList.size() * 2 + 1));
    SM.setStoreNum(static_cast<unsigned int>(sidList.size() + 1));
    for (int sid:sidList) {
        Store S = readFile(sid);
        SM.update(S);
        SM.setUnchanged(S.getSid());
    }
    return SM;
}

Store Util::readFile(int sid) {
    std::string filepath;
    filepath = DATAPATH + std::to_string(sid) + ".pds";
    std::ifstream fin(filepath, std::fstream::in | std::fstream::binary);
    Store S;
    if (!fin)
        return S;
    std::string buf1, buf2;
    fin >> buf1;
    fin >> buf2;
    S = Store(buf1, buf2);
    fin >> buf1;
    S.setSid(std::stoi(buf1));
    CommodityMap CM;
    while (!fin.eof()) {
        std::string name;
        unsigned int Csid, cid, labelNum;
        float price;
        fin >> name;
        if (name.empty())
            break;
        fin >> price;
        fin >> Csid;
        fin >> cid;
        fin >> labelNum;
        std::vector<std::string> labelList(labelNum);
        for (int i = 0; i < labelNum; ++i) {
            fin >> labelList[i];
        }
        Commodity C(name, price, labelList, Csid);
        CM.insert(C);
    }
    S.setCommodityMap(CM);
    return S;
}

bool Util::saveFile(Store &S) {
    std::string filepath;
    filepath = DATAPATH + std::to_string(S.getSid()) + ".pds";
    std::ofstream fout(filepath, std::fstream::out);
    if (!fout)
        return false;
    fout << S.getName() << std::endl;
    fout << S.getPlat() << std::endl;
    fout << S.getSid() << std::endl;
    for (Commodity C:S.getComMap().getComList()) {
        fout << C.getName() << std::endl;
        fout << C.getPrice() << std::endl;
        fout << C.getSid() << std::endl;
        fout << C.getCid() << std::endl;
        fout << C.getLabel().getLabelList().size() << std::endl;
        for (const Label &L:C.getLabel().getLabelList()) {
            fout << L << std::endl;
        }
    }
    fout.close();
    return true;
}

bool Util::saveFiles(StoreMap &SM) {
    std::vector<int> changedSidList = SM.getChangedStore();
    std::vector<int> SidList(static_cast<unsigned long long int>(SM.getStoreNum()));
    unsigned int count = 0;
    for (Store S:SM.getStoreList()) {
        int curSid = S.getSid();
        if (curSid != -1) {
            SidList[count] = S.getSid();
            ++count;
            if (isChanged(changedSidList, curSid)) {
                saveFile(S);
                setUnchanged(SM, curSid);
            }
        }
        if (count == SM.getStoreNum())
            break;
    }
    return updateFileList(SidList);
}

bool Util::isChanged(const std::vector<int> &List, int curSid) {
    for (int sid:List) {
        if (curSid == sid)
            return true;
    }
    return false;
}

void Util::setUnchanged(StoreMap &SM, int curSid) {
    SM.setUnchanged(curSid);
}

bool Util::updateFileList(std::vector<int> &List) {
    std::ofstream fout(LISTPATH, std::fstream::out);
    if (!fout)
        return false;
    for (int sid:List) {
        fout << sid << std::endl;
    }
    return true;
}

UserMap Util::loadUserFiles() {
    UserMap UM;
    std::string filepath;
    filepath = USERPATH;
    std::ifstream fin(filepath, std::fstream::in);
    if (!fin)
        return UM;
    while (!fin.eof()) {
        std::string name;
        Label L;
        LabelList List;
        fin >> name;
        unsigned int labelNum;
        fin >> labelNum;
        for (int i = 0; i < labelNum; ++i) {
            fin >> L;
            List.append(L);
        }
        User U(name, List);
        UM.insert(U);
    }
    return UM;

}

bool Util::saveUserFiles(UserMap &UM) {
    for (UserMap::tableNode *Node:UM.getTable()) {
        Node = Node->Next;
        while (Node) {
            saveUser(Node->curUser);
            Node = Node->Next;
        }
    }
    return true;
}

bool Util::saveUser(User U) {
    std::string filepath;
    filepath = USERPATH;
    std::ofstream fout(filepath, std::fstream::out|std::fstream::app);
    if (!fout)
        return false;
    fout << U.getName();
    std::vector<Label> List = U.getPreferList().getLabelList();
    fout << List.size();
    for (const Label &L:List)
        fout << ' ' + L;
    fout << std::endl;
    return true;
}
