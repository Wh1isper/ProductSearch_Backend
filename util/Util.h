//
// Created by 95735 on 2019/4/29 0029.
//

#ifndef SOFTWARE_UTIL_H
#define SOFTWARE_UTIL_H

#include "../database/StoreMap.h"
#include <fstream>
#include <vector>
#include <string>
#include <string.h>

class Util {
public:
    StoreMap readFiles();
    bool saveFiles(StoreMap &SM);
    Store readFile(int sid);
    bool saveFile(Store &S);
    const char * LISTPATH = "./cache/StoreList.txt";
    const char * DATAPATH = "./cache/";
private:
    bool isChanged(const std::vector<int> &List, int curSid);
    void setUnchanged(StoreMap &SM, int curSid);
    bool updateFileList(std::vector<int> &List);



};


#endif //SOFTWARE_UTIL_H
