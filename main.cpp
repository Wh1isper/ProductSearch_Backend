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


// ���þ���1����һ��ʹ��
void Example_initial(){
    Store S = creatStore("initial_name","initial_plat");
    StoreMap SM = creatStoreMap();
    SM.insert(S);                                           //����ע�⣺�����Ƚ�S��ӵ�ͼ��
    Commodity C = creatCommodity("Comdity_name1", 1.11, S); // ģ������һ����Ʒ�������̻�S
    S = addCommodity(SM, S, C,"label1");                    // ������Ʒ��ͬʱ���һ����ǩ
    std::vector<Label> labelList{"L1","L2"};                // ��ѡ �����б�������ӱ�ǩ
    S = addLabel(SM, S, C, labelList);
    if(saveAllchanges(SM))
        std::cout << "��ʼ����ϣ�����./cache�ļ����²鿴" << std::endl;
}

// ���þ���2��������ɾ���������뱣��
void Example_readAndEdit(){
    Util reader;
    StoreMap SM = reader.readFiles();
    int sid = 1;                                            // ����Ҫ��ȡ��sidΪ1

    Store S = SM.getStore(sid);

    Commodity C = creatCommodity("Comdity_name2", 2.22, S); // ���½�һ����Ʒ
    S = addCommodity(SM,S,C);

    S = addLabel(SM,S,C,"C2L2");                            //Ϊ��Ʒ��ӱ�ǩ
    S = delLabel(SM, S, 1,"L1");                            // ɾ��ĳ����ǩ
    S = cancelAllChanges(SM,S);                             // �������в�����ǰ����δ����
    S = delLabel(SM, S, 1,"L1");
    if(saveAllchanges(SM))                                  // ����
        std::cout << "�����汣��" << std::endl;

}

// ���þ���3�����������Ĵ���������
void Example_Search(){
    Util reader;
    StoreMap SM = reader.readFiles();
    Label2Com indexer(SM);                                         // ������������

    std::vector<Commodity> singleLabelSearch = searchCmdt(indexer,SM,"Label0");

    LabelList L("Label1");L.append("Label0");L.append("Label4");L.append("Label8");

    std::vector<Commodity> accurateLabelSearch = searchCmdt_single(indexer,SM,L);
    std::vector<Commodity> multLabelSearch = searchCmdt_mult(indexer,SM,L);
    std::cout << "single search Num:" << singleLabelSearch.size() << std::endl;
    std::cout << "accurate search Num:" << accurateLabelSearch.size() << std::endl;
    std::cout << "mult search Num:" << multLabelSearch.size() << std::endl;
}