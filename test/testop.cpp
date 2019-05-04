//
// Created by 95735 on 2019/4/30 0030.
//

#include <iostream>
#include "testop.h"

void initial(){
    Store S1,S2;
    S1 = Store();
    S2 = Store("Name2", "Plat2");
    S1.setName("Name1");
    S1.setPlat("Plat1");
    StoreMap SM(2);
    SM.update(S1);
    SM.insert(S2);

    Commodity C1,C2,C3,C4;
    C1 = Commodity("1C1Name", 1.11, S1.getSid());
    C2 = Commodity("1C2Name", 2.22, S1.getSid());
    C3 = Commodity("2C3Name", 3.33, S2.getSid());
    C4 = Commodity("2C4Nmae", 4.44, S2.getSid());


    CommodityMap CM1(2),CM2(2);
    CM1.insert(C1);
    CM1.insert(C2);
    S1.setCommodityMap(CM1);
    SM.update(S1);

    CM1.insert(C3);
    S1.setCommodityMap(CM1);
    SM.update(S1);

    // 修改商品标签
    C4.addLabel("removeTest");
    C4.removeLabel("removeTest");
    Commodity tmpC = S1.getComMap().getCommodity(1);
    tmpC.addLabel("testADD");
    CommodityMap tmpCM = S1.getComMap();
    tmpCM.update(tmpC);
    S1.setCommodityMap(tmpCM);
    SM.update(S1);
//    SM.remove(S2);
//    Util util;
//    util.saveFiles(SM);
//    StoreMap SM2;
//    SM2 = util.readFiles();
    Label2Com l2c;
    l2c.insertTable(SM);
    std::vector<ComInfo> Cif;
    Cif = l2c.linerSearch("testADD");
    std::cout<< "hello";
    return;
}