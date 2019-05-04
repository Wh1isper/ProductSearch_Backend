/*
 * 作者：Wh1isper at 2019-04-30
 * 说明：
 *      Labellist是商品标签的链表
 *      直接调用方法即可
*/

#ifndef SOFTWARE_LABELLIST_H
#define SOFTWARE_LABELLIST_H

#include <string>
#include <vector>
typedef std::string Label;
class LabelList {
public:


    LabelList();
    explicit LabelList(std::vector<std::string> labelList);
    explicit LabelList(const Label &lbl);
    bool append(const Label &lbl);
    bool append(const LabelList &lst);
    bool remove(const Label &lbl);
    bool pop();
    bool clear();
    std::vector<Label> getLabelList();


private:
    struct List{
        Label Lbl;
        List * Next;
        List();
        explicit List(const List * lst);
        explicit List(const Label &lbl);
    };

    List * L;

};


#endif //SOFTWARE_LABELLIST_H
