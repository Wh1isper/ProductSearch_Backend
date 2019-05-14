#include <iostream>
#include "operation.h"

void Example_initial();
void Example_readAndEdit();
void Example_Search();
int main() {
    //Example_initial();
   // Example_readAndEdit();
    Example_Search();
    return 0;
}


// 调用举例1：第一次使用
void Example_initial(){
    Store S = creatStore("initial_name","initial_plat");
    StoreMap SM = creatStoreMap();
    SM.insert(S);                                           //！！注意：必须先将S添加到图中
    Commodity C = creatCommodity("Comdity_name1", 1.11, S); // 模拟生成一个商品，属于商户S
    S = addCommodity(SM, S, C,"label1");                    // 加入商品，同时添加一个标签
    std::vector<Label> labelList{"L1","L2"};                // 可选 传入列表批量添加标签
    S = addLabel(SM, S, C, labelList);
    if(saveAllchanges(SM))
        std::cout << "初始化完毕，请在./cache文件夹下查看" << std::endl;
}

// 调用举例2：新增、删除、撤销与保存
void Example_readAndEdit(){
    Util reader;
    StoreMap SM = reader.readFiles();
    int sid = 1;                                            // 假设要读取的sid为1

    Store S = SM.getStore(sid);

    Commodity C = creatCommodity("Comdity_name2", 2.22, S); // 再新建一个商品
    S = addCommodity(SM,S,C);

    S = addLabel(SM,S,C,"C2L2");                            //为商品添加标签
    S = delLabel(SM, S, 1,"L1");                            // 删除某个标签
    S = cancelAllChanges(SM,S);                             // 撤销所有操作，前提是未保存
    S = delLabel(SM, S, 1,"L1");
    if(saveAllchanges(SM))                                  // 保存
        std::cout << "不可逆保存" << std::endl;

}

// 调用举例3：倒排索引的创建与搜索
void Example_Search(){
    Util reader;
    StoreMap SM = reader.readFiles();
    Label2Com indexer(SM);                                         // 创建倒排索引

    std::vector<Commodity> singleLabelSearch = searchCmdt(indexer,SM,"Label0");

    LabelList L("Label1");L.append("Label0");L.append("Label4");L.append("Label8");

    std::vector<Commodity> accurateLabelSearch = searchCmdt_single(indexer,SM,L);
    std::vector<Commodity> multLabelSearch = searchCmdt_mult(indexer,SM,L);
    std::cout << "single search Num:" << singleLabelSearch.size() << std::endl;
    std::cout << "accurate search Num:" << accurateLabelSearch.size() << std::endl;
    std::cout << "mult search Num:" << multLabelSearch.size() << std::endl;
}