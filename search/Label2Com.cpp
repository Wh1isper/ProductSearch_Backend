#include "Label2Com.h"

Label2Com::Label2Com() {
    maxLabelNum = 10;
    labelNum = 1;
    Table = creatTable();
}

Label2Com::Label2Com(unsigned int max) {
    if (max < 20)
        max = 5;
    maxLabelNum = max;
    labelNum = 1;
    Table = creatTable();
}

Label2Com::Label2Com(StoreMap &SM) {
    maxLabelNum = 10;
    labelNum = 1;
    Table = creatTable();
    initialTable(SM);
}

Label2Com::Label2Com(StoreMap SM, unsigned int max) {
    if (max < 20)
        max = 5;
    maxLabelNum = max;
    labelNum = 1;
    Table = creatTable();
    initialTable(SM);
}

bool Label2Com::initialTable(StoreMap &SM) {
    return insertTable(SM);
}

Label2Com::ComInfo::ComInfo() {
    Cid = -1;
    Sid = -1;
}

Label2Com::ComInfo::ComInfo(Commodity &C) {
    Cid = C.getCid();
    Sid = C.getSid();
}

Label2Com::ComInfo::ComInfo(int sid, int cid) {
    Cid = cid;
    Sid = sid;
}

int Label2Com::ComInfo::getSid() const {
    return Sid;
}

int Label2Com::ComInfo::getCid() const {
    return Cid;
}

void Label2Com::ComInfo::SetCid(int cid) {
    Cid = cid;
}

void Label2Com::ComInfo::SetSid(int sid){
    Sid = sid;
}

bool Label2Com::ComInfo::operator==(const Label2Com::ComInfo &B) const {
    return (this->getSid() == B.getSid()) && (this->getCid() == B.getCid());
}

Label2Com::ComInfo& Label2Com::ComInfo::operator=(const Label2Com::ComInfo &B){
    this->Cid = B.getCid();
    this->Sid = B.getSid();
    return *this;
}

bool Label2Com::ComInfo::operator>(const Label2Com::ComInfo &B) const {
    return this->getSid() > B.getSid() ? true : this->getSid() == B.getSid() ? this->getCid() > B.getCid() : false;
}

bool Label2Com::ComInfo::operator<(const Label2Com::ComInfo &B) const {
    return this->getSid() < B.getSid() ? true : this->getSid() == B.getSid() ? this->getCid() < B.getCid() : false;
}

Label2Com::ComList::ComList() {
    Info = ComInfo();
    Next = nullptr;
}

Label2Com::ComList::ComList(Commodity &C) {
    Info = ComInfo(C);
    Next = nullptr;
}

Label2Com::TableNode::TableNode() {
    Lbl = "";
    CList = new ComList;
}

Label2Com::TableNode::TableNode(Label &lbl) {
    Lbl = lbl;
    CList = new ComList;
}

Label2Com::TableNode::TableNode(Label2Com::ComList *CL) {
    Lbl = "";
    CList = CL;
}

Label2Com::TableNode::TableNode(Label &lbl, Label2Com::ComList *CL) {
    Lbl = lbl;
    CList = CL;
}

bool Label2Com::TableNode::insertCom(Commodity &C) {
    ComList *temp = CList;
    while (temp->Next) {
        ComInfo info(C);
        if (temp->getInfo() == info)
            return false;
        temp = temp->Next;
    }
    temp->Next = new ComList(C);
    return true;
}

bool Label2Com::TableNode::insertCom(CommodityMap &CMap) {
    for (Commodity C:CMap.getComList()) {
        insertCom(C);
    }
    return true;
}

Label Label2Com::TableNode::getLabel() {
    return Lbl;
}

void Label2Com::TableNode::setLabel(Label &lbl) {
    Lbl = lbl;
}

Label2Com::ComInfo Label2Com::ComList::getInfo() {
    return Info;
}

std::vector<Label2Com::ComInfo> Label2Com::TableNode::getComList() {
    std::vector<Label2Com::ComInfo> res;
    ComList *temp = CList->Next;
    while (temp) {
        res.push_back(temp->getInfo());
        temp = temp->Next;
    }
    return res;
}


std::vector<Label2Com::TableNode> Label2Com::creatTable() {
    return std::vector<Label2Com::TableNode>(maxLabelNum);
}

bool Label2Com::insertTable(StoreMap &SMap) {
    for (Store S:SMap.getStoreList()) {
        insertTable(S);
    }
    return true;
}

bool Label2Com::insertTable(Store &S) {
    CommodityMap CM = S.getComMap();
    return insertTable(CM);
}

bool Label2Com::insertTable(CommodityMap &CMap) {
    for (Commodity C:CMap.getComList())
        insertTable(C);
    return true;
}

bool Label2Com::insertTable(Commodity &C) {
    for (Label L:C.getLabel().getLabelList()) {
        bool find = false;
        for (TableNode Node:Table) {
            if (Node.getLabel() == L) {
                Node.insertCom(C);
                find = true;
                break;
            }
        }
        if (!find) {
            TableNode diffSet(L);
            diffSet.insertCom(C);
            Table[labelNum] = diffSet;
            ++labelNum;
            if (labelNum + 1 > maxLabelNum) {
                maxLabelNum *= 2;
                Table.resize(maxLabelNum);
            }
        }
    }
    return true;
}

bool Label2Com::del(Commodity &C) {
    ComInfo des(C);
    for (const Label &L:C.getLabel().getLabelList()) {
        for (TableNode Node:Table)
            if (Node.getLabel() == L) {
                ComList *pos = Node.CList->Next;
                ComList *temp = Node.CList;
                while (pos) {
                    ComInfo info = pos->getInfo();
                    if (info == des) {
                        temp->Next = pos->Next;
                        delete pos;
                        break;
                    }
                    temp = pos;
                    pos = pos->Next;
                }
            }
    }
    return true;
}

bool Label2Com::del(CommodityMap &CMap) {
    for (Commodity C:CMap.getComList()) {
        if (!del(C))
            return false;
    }
    return true;
}

bool Label2Com::del(Store &S) {
    CommodityMap CM = S.getComMap();
    return del(CM);
}

bool Label2Com::del(StoreMap &SMap) {
    for (Store S:SMap.getStoreList()) {
        if (!del(S))
            return false;
    }
    return true;
}

std::vector<Label2Com::ComInfo> Label2Com::singleSearch(const Label &lbl) {
    std::vector<Label2Com::ComInfo> res;
    for (TableNode TNode:Table) {
        if (lbl == TNode.getLabel())
            return TNode.getComList();
    }
    return res;
}

std::vector<Label2Com::ComInfo> Label2Com::singleSearch(LabelList lblList) {
    return multSearch(lblList)[0];
}

bool Label2Com::clear() {
    maxLabelNum = 10;
    labelNum = 1;
    Table = creatTable();
    return true;
}

std::vector<std::vector<Label2Com::ComInfo>> Label2Com::multSearch(LabelList &lblList) {
    std::vector<std::vector<Label2Com::ComInfo>> searchResult;
    std::vector<Label2Com::ComInfo> diffSetResult;
    std::vector<std::set<ComInfo>> totSet;
    std::vector<Label> labelList = lblList.getLabelList();
    for (const Label &L:labelList) {
        diffSetResult = singleSearch(L);
        std::set<ComInfo> diffSetSet;
        for (const ComInfo &info:diffSetResult) {
            diffSetSet.insert(info);
        }
        totSet.push_back(diffSetSet);
    }
    if (!totSet.empty()) {
        std::vector<int> nums;
        for (int i = 0; i < totSet.size(); ++i) {
            nums.push_back(i);
        }
        std::vector<std::vector<int>> sequence = subsets(nums);
        std::set<ComInfo> usedSet;
        sort(sequence.begin(), sequence.end(), cmp);
        for (const std::vector<int> &list:sequence) {
            std::set<ComInfo> curSet;
            for (int i:list) {
                if(curSet.empty())
                    curSet.insert(totSet[i].begin(), totSet[i].end());
                else
                {
                    std::set<ComInfo> uniSet;
                    std::set_intersection(totSet[i].begin(), totSet[i].end(),curSet.begin(),curSet.end(),
                            std::inserter(uniSet,uniSet.begin()));
                    curSet.clear();
                    curSet.insert(uniSet.begin(),uniSet.end());
                }
            }
            std::set<ComInfo> diffSet;
            std::set_difference(curSet.begin(),curSet.end(),usedSet.begin(),usedSet.end(),
                    std::inserter(diffSet,diffSet.begin()));
            usedSet.insert(diffSet.begin(),diffSet.end());
            std::vector<Label2Com::ComInfo> curRes;
            for (ComInfo info:diffSet) {
                curRes.push_back(info);
            }
            searchResult.push_back(curRes);
        }
        searchResult.pop_back();
    }
    return searchResult;
}

std::vector<std::vector<Label2Com::ComInfo>> Label2Com::multSearch(std::vector<Label> &lblList) {
    LabelList list(lblList);
    return multSearch(list);
}

void Label2Com::dfs(int i, std::vector<int> &nums, std::vector<int> &cur, std::vector<std::vector<int>> &res) {
    res.emplace_back(cur);
    if (i >= nums.size())
        return;
    for (int j = i; j < nums.size(); ++j) {
        cur.push_back(nums[j]);
        dfs(j + 1, nums, cur, res);
        cur.pop_back();
    }
}

bool cmp(const std::vector<int> &a, const std::vector<int> &b) {
    return a.size() > b.size();
}

std::vector<std::vector<int>> Label2Com::subsets(std::vector<int> &nums) {
    std::vector<std::vector<int>> res;
    std::vector<int> cur;
    dfs(0, nums, cur, res);
    return res;
}
