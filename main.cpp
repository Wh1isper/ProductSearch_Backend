#include <iostream>
#include "operation.h"
#include "test/testop.h"
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
    Label2Com searcher(SM);                                         // 创建倒排索引
    std::vector<ComInfo> CifList = searcher.linerSearch("Label2");  // 获得搜索结果列表
    LabelList L("Label1");
    L.append("Label2");
    std::vector<std::vector<ComInfo>> multiList = searcher.multSearch(L);
    for (ComInfo Cif:CifList) {
        //Commodity C = searchCommodity(SM, Cif);                   // 获得每个商品，商品过多时请分批次获取
    }
    int i=0;// 在这段测试代码中 你将会看到class0为label1、label2共同商标商品数，class1、class2为label1、label2商品数
    for (std::vector<ComInfo> searchResult:multiList){
        std::vector<ComInfo> curList = searchResult;
        std::cout<< "class "<< i << "  ,find:"<< curList.size()<<std::endl;
        ++i;
    }
}