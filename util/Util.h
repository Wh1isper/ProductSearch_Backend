//
// Created by 95735 on 2019/4/29 0029.
//

#ifndef SOFTWARE_UTIL_H
#define SOFTWARE_UTIL_H

#include "../database/StoreMap.h"
#include "../database/UserMap.h"
#include <fstream>
#include <vector>
#include <string>
#include <string.h>

class Util {
public:
    // -----------------------------------商户文件操作函数---------------------------------------------
    StoreMap readFiles();           // 读取商户图

    bool saveFiles(StoreMap &SM);   // 存储商户图

    Store readFile(int sid);        // 读取单个商户信息

    bool saveFile(Store &S);        // 存储单个商户信息
    // -----------------------------------用户文件操作函数---------------------------------------------
    UserMap loadUserFiles();        // 加载用户文件

    bool saveUserFiles(UserMap &UM);    // 保存用户文件

    bool saveUser(User U);              // 保存单个用户信息

    const char *LISTPATH = "./cache/StoreList.txt";     // 商户索引位置
    const char *DATAPATH = "./cache/";                  // 商户存储路径
    const char *USERLISTPATH = "./user/userList.txt";
    const char *USERPATH = "./user/userFile.txt";       // 用户信息存储文件
private:
    bool isChanged(const std::vector<int> &List, int curSid);// 查询是否被标记为已修改

    void setUnchanged(StoreMap &SM, int curSid);    // 用以保存完毕后重置已修改标记

    bool updateFileList(std::vector<int> &List);    // 更新商户图索引

};


#endif //SOFTWARE_UTIL_H
