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
    // -----------------------------------构造函数---------------------------------------------
    LabelList();

    explicit LabelList(std::vector<std::string> labelList);

    explicit LabelList(const Label &lbl);
    // -----------------------------------功能函数---------------------------------------------
    bool append(const Label &lbl);          // 后插入，插入单个标签

    bool append(const LabelList &lst);      // 后插入，连接两个列表

    bool push_ahead(const Label &lbl);      // 前插入，用以刷新用户喜好表

    bool push_ahead(const LabelList &lbl);  // 前插入，用以刷新用户喜好表

    bool remove(const Label &lbl);          // 移除某个标签

    bool pop();                             // 移除最后一个元素

    bool clear();                           // 清空表
    // -----------------------------------查询(get)函数---------------------------------------------
    std::vector<Label> getLabelList() const; // 获得标签列表


private:
    struct List {
        Label Lbl;
        List *Next;

        List();

        explicit List(const List *lst);

        explicit List(const Label &lbl);
    };

    List *L; // 带头节点的链表存储标签

};


#endif //SOFTWARE_LABELLIST_H
