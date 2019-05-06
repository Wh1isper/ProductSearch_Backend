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
    Label2Com searcher(SM);                                         // ������������
    std::vector<ComInfo> CifList = searcher.linerSearch("Label2");  // �����������б�
    LabelList L("Label1");
    L.append("Label2");
    std::vector<std::vector<ComInfo>> multiList = searcher.multSearch(L);
    for (ComInfo Cif:CifList) {
        //Commodity C = searchCommodity(SM, Cif);                   // ���ÿ����Ʒ����Ʒ����ʱ������λ�ȡ
    }
    int i=0;// ����β��Դ����� �㽫�ῴ��class0Ϊlabel1��label2��ͬ�̱���Ʒ����class1��class2Ϊlabel1��label2��Ʒ��
    for (std::vector<ComInfo> searchResult:multiList){
        std::vector<ComInfo> curList = searchResult;
        std::cout<< "class "<< i << "  ,find:"<< curList.size()<<std::endl;
        ++i;
    }
}