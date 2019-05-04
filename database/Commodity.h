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
    Commodity();
    Commodity(const std::string &name, float price, std::vector<std::string> &label, int sid);
    Commodity(const std::string &name, float price, LabelList &label, int sid);
    Commodity(const std::string &name, float price, int sid);
    void addLabel(const Label &lbl);
    void addLabel(const std::vector<Label> &lblList);
    void removeLabel(const Label &lbl);
    int getSid();
    int getCid();
    std::string getName();
    LabelList getLabel();
    float getPrice();
    void setCid(int cid);
    void setSid(int sid);
private:
    std::string Name;
    LabelList Label;
    float Price;
    int Sid;
    int Cid;
};


#endif //SOFTWARE_COMMODITY_H
