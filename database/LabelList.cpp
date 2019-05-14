#include "LabelList.h"

LabelList::List::List() {
    Lbl = "";
    Next = nullptr;
}

LabelList::List::List(const Label &lbl) {
    Lbl = lbl;
    Next = nullptr;
}

LabelList::List::List(const LabelList::List *lst) {
    Lbl = lst->Lbl;
    Next = nullptr;
}

LabelList::LabelList() {
    L = new List();
}

LabelList::LabelList(const Label &lbl) {
    L = new List();
    L->Next = new List(lbl);
}

LabelList::LabelList(std::vector<std::string> labelList) {
    L = new List();
    List *pos = L;
    for (const Label &L:labelList) {
        pos->Next = new List(L);
        pos = pos->Next;
    }
}

bool LabelList::append(const Label &lbl) {
    List *Srch = L;
    while (Srch->Next) {
        Srch = Srch->Next;
        if (Srch->Lbl == lbl)
            return true;
    }

    Srch->Next = new List(lbl);
    return true;
}

bool LabelList::append(const LabelList &lst) {
    for (const Label &L:lst.getLabelList()) {
        append(L);
    }
    return true;
}

bool LabelList::remove(const Label &lbl) {
    List *tmp = L;
    List *Srch = L;
    while (Srch && Srch->Lbl != lbl) {
        tmp = Srch;
        Srch = Srch->Next;
    }
    if (tmp != Srch) {
        if (Srch) {
            tmp->Next = Srch->Next;
            delete Srch;
            return true;
        } else
            return false;
    } else
        return false;
}

bool LabelList::pop() {
    List *Srch = L;
    List *tmp = L;
    while (Srch->Next) {
        tmp = Srch;
        Srch = Srch->Next;
    }
    if (tmp != Srch) {
        delete Srch;
        tmp->Next = nullptr;
        return true;
    } else
        return false;
}


bool LabelList::clear() {
    List *Srch = L->Next;
    while (Srch->Next) {
        List *tmp = Srch;
        Srch = Srch->Next;
        delete tmp;
    }
    if (Srch != L)
        delete Srch;
    L->Next = nullptr;
    return true;
}

std::vector<Label> LabelList::getLabelList() const {
    std::vector<Label> res;
    List *Srch = L;
    while (Srch->Next) {
        Srch = Srch->Next;
        res.push_back(Srch->Lbl);
    }
    return res;
}

bool LabelList::push_ahead(const Label &lbl) {
    remove(lbl);
    List *insertList = new List(lbl);
    List *Node = L;
    while (insertList->Next)
        insertList = insertList->Next;
    insertList->Next = Node->Next;
    Node->Next = insertList;
    return true;
}

bool LabelList::push_ahead(const LabelList &lbl) {
    for (const Label &l:lbl.getLabelList()) {
        push_ahead(l);
    }
    return true;
}

