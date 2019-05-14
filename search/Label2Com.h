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

class Label2Com {
public:
    struct ComInfo {
        int Sid;
        int Cid;
        // -----------------------------------构造函数---------------------------------------------
        ComInfo();

        ComInfo(int sid, int cid);

        explicit ComInfo(Commodity &C);
        // -----------------------------------功能函数---------------------------------------------
        void SetSid(int sid);

        void SetCid(int cid);
        // -----------------------------------查询函数---------------------------------------------
        int getSid() const;

        int getCid() const;
        // -----------------------------------重载函数---------------------------------------------
        // 用以调用std::set, set的实现是红黑树
        bool operator==(const ComInfo &B) const;

        ComInfo &operator=(const ComInfo &B);

        bool operator>(const ComInfo &B) const;

        bool operator<(const ComInfo &B) const;
    };// 存放商品信息
    // -----------------------------------构造函数---------------------------------------------
    Label2Com();

    explicit Label2Com(unsigned int max);

    explicit Label2Com(StoreMap &SM);

    Label2Com(StoreMap SM, unsigned int max);
    // -----------------------------------功能函数---------------------------------------------
    bool initialTable(StoreMap &SM);    // 重置并初始化倒排索引

    bool insertTable(StoreMap &SMap);       // 由商户图更新倒排索引

    bool insertTable(Store &S);             // 由商户更新倒排索引

    bool insertTable(CommodityMap &CMap);   // 由商品图更新倒排索引

    bool insertTable(Commodity &C);         // 由商品更新倒排索引

    bool del(Commodity &C);         // 删除单个商品

    bool del(CommodityMap &CMap);   // 删除商品图

    bool del(Store &S);             // 删除商户

    bool del(StoreMap &SMap);       // 商户商户图

    bool clear();                   // 清空/重置
    // -----------------------------------查询函数---------------------------------------------
    std::vector<ComInfo> singleSearch(const Label &lbl); // 单标签搜索
    std::vector<ComInfo> singleSearch(LabelList lblList); // 多标签精确搜索
    std::vector<std::vector<ComInfo>> multSearch(LabelList &lblList);           // 多标签模糊搜索
    std::vector<std::vector<ComInfo>> multSearch(std::vector<Label> &lblList);

private:
    unsigned int maxLabelNum;   // 动态表最大长度
    unsigned int labelNum;      // 动态表当前长度
    struct ComList {
        ComInfo Info;
        ComList *Next;

        ComList();

        explicit ComList(Commodity &C);

        ComInfo getInfo();
    }; // 链式存储的倒排索引结点
    struct TableNode {
        Label Lbl;
        ComList *CList;

        TableNode();

        explicit TableNode(ComList *CL);

        explicit TableNode(Label &lbl);

        explicit TableNode(Label &lbl, ComList *CL);

        bool insertCom(Commodity &C);

        bool insertCom(CommodityMap &CMap);

        Label getLabel();

        void setLabel(Label &lbl);

        std::vector<ComInfo> getComList();
    }; // 倒排索引表头TabelNode(string Label, ComInfo->ComInfo->...->ComInfo)
    std::vector<TableNode> Table; // 存放倒排索引表头
    std::vector<TableNode> creatTable();
    // -----------------------------------查询标签组合生成api---------------------------------------------
    std::vector<std::vector<int>> subsets(std::vector<int> &nums);  // 返回所有子序列，按长度排序
    void dfs(int i, std::vector<int> &nums, std::vector<int> &cur, std::vector<std::vector<int>> &res);
};
// -----------------------------------比较函数，用以上述api排序---------------------------------------------
bool cmp(const std::vector<int> &a, const std::vector<int> &b);


#endif //SOFTWARE_LABEL2COM_H
