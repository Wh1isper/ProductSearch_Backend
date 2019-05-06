/*
 * 作者：Wh1isper at 2019-04-30
 * 说明：
 *      Label2Com是倒排索引
 *      调用时，先实例化Label2Com，插入商品图，或使用intial插入商品图;
 *      使用linerSearch可以获得包含商品信息的vector
 *
*/

#ifndef SOFTWARE_LABEL2COM_H
#define SOFTWARE_LABEL2COM_H

#include "../database/CommodityMap.h"
#include "../database/StoreMap.h"
#include <vector>
#include <set>
#include <algorithm>
#include "subsets.cpp"
class Label2Com {
public:
    struct ComInfo{
        int Sid;
        int Cid;
        ComInfo();
        ComInfo(int sid,int cid);
        explicit ComInfo(Commodity &C);
        int getSid();
        int getCid();
        void SetSid(int sid);
        void SetCid(int cid);
        bool operator == (ComInfo B);
        bool operator > (ComInfo B);
        bool operator < (ComInfo B);
    };// 存放商品信息
    Label2Com();
    explicit Label2Com(unsigned int max);
    explicit Label2Com(StoreMap &SM);
    Label2Com(StoreMap SM, unsigned int max);
    bool initialTable(StoreMap &SM);
    bool insertTable(StoreMap &SMap);
    bool insertTable(Store &S);
    bool insertTable(CommodityMap &CMap);
    bool insertTable(Commodity &C);
    bool del(Commodity &C);
    bool del(CommodityMap &CMap);
    bool del(Store &S);
    bool del(StoreMap &SMap);
    bool clear();
    std::vector<ComInfo> linerSearch(const Label &lbl);// 线性搜索
    std::vector<ComInfo> linerSearch(LabelList lblList);// 精确搜索
    std::vector<std::vector<ComInfo>> multSearch(LabelList &lblList);
    std::vector<std::vector<ComInfo>> multSearch(std::vector<Label> &lblList);

private:
    unsigned int maxLabelNum;// 最大标签数
    unsigned int labelNum; // labelNum-1为当前标签数，labelNum对应着下一插入位置
    struct ComList{
        ComInfo Info;
        ComList * Next;
        ComList();
        explicit ComList(Commodity &C);
        ComInfo getInfo();
    }; // 索引链表
    struct TableNode{
        Label Lbl;
        ComList * CList;
        TableNode();
        explicit TableNode(ComList * CL);
        explicit TableNode(Label &lbl);
        explicit TableNode(Label &lbl,ComList * CL);
        bool insertCom(Commodity &C);
        bool insertCom(CommodityMap &CMap);
        Label getLabel();
        void setLabel(Label &lbl);
        std::vector<ComInfo> getComList();
    }; // 倒排索引表头TabelNode(string Label, ComInfo->ComInfo->...->ComInfo)
    std::vector<TableNode> Table; // 存放倒排索引表头
    std::vector<TableNode> creatTable();
};



#endif //SOFTWARE_LABEL2COM_H
