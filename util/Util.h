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
    // -----------------------------------商店文件操作函数---------------------------------------------
    StoreMap readFiles();           // 读取商店图

    bool saveFiles(StoreMap &SM);   // 存储商店图

    Store readFile(int sid);        // 读取单个商店信息

    bool saveFile(Store &S);        // 存储单个商店信息
    // -----------------------------------用户文件操作函数---------------------------------------------
    UserMap loadUserFiles();            // 加载用户文件

    bool saveUserFiles(UserMap &UM);    // 保存用户文件

    bool saveUser(const User &U);       // 保存单个用户信息
    // -----------------------------------商户用户操作函数---------------------------------------------
    UserMap loadStoreUserFiles();            // 加载用户文件

    bool saveStoreUserFiles(UserMap &UM);    // 保存用户文件

    bool saveStoreUser(const User &U);       // 保存单个用户信息

    const char *LIST_PATH = "./cache/StoreList.txt";     // 商户索引位置
    const char *DATA_PATH = "./cache/";                  // 商户存储路径
    const char *STORE_USER_PATH = "./user/StoreUserList.txt";
    const char *USER_PATH = "./user/UserFile.txt";       // 用户信息存储文件
private:
    bool isChanged(const std::vector<int> &List, int curSid);// 查询是否被标记为已修改

    void setUnchanged(StoreMap &SM, int curSid);    // 用以保存完毕后重置已修改标记

    bool updateFileList(std::vector<int> &List);    // 更新商户图索引
};


#endif //SOFTWARE_UTIL_H
