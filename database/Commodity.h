/*
 * 作者：Wh1isper at 2019-04-30
 * 说明：
 *      产品，包括产品名字、标签、价格和所属的商户
 *
*/
#ifndef SOFTWARE_COMMODITY_H
#define SOFTWARE_COMMODITY_H

#include "LabelList.h"
#include <string>

class Commodity {
public:
    // -----------------------------------构造函数---------------------------------------------
    Commodity();

    Commodity(const std::string &name, float price, std::vector<std::string> &label, int sid);

    Commodity(const std::string &name, float price, LabelList &label, int sid);

    Commodity(const std::string &name, float price, int sid);
    // -----------------------------------功能函数---------------------------------------------
    // 添加标签
    void addLabel(const Label &lbl); // 传入单个标签

    void addLabel(const std::vector<Label> &lblList); // 传入标签列表

    void addLabel(const LabelList &lblList); // 传入标签列表

    void removeLabel(const Label &lbl); // 移除标签

    // ！！谨慎调用
    void setCid(int cid); // 设置商品id
    // ！！谨慎调用
    void setSid(int sid); // 设置商品对应的商户id
    // -----------------------------------查询(get)函数---------------------------------------------
    int getSid(); // 获得商品对应的商户id

    int getCid(); // 获得商品id

    std::string getName(); // 获得商品名称

    LabelList getLabel(); // 获得商品标签列表

    float getPrice() const;// 获得商品价格

    static float getPrice(const Commodity &C);

private:
    std::string Name;   // 存放商品名
    LabelList Label;    // 商品标签列表
    float Price;        // 商品价格
    int Sid;            // 商品对应商户id
    int Cid;            // 商品自身id
};


#endif //SOFTWARE_COMMODITY_H
