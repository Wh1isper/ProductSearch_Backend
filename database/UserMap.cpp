#include "UserMap.h"

UserMap::UserMap() {
    maxUserNum = 100000000;
    userNum = 0;
    Table = creatTable();
}

UserMap::UserMap(unsigned int max) {
    maxUserNum = max < 100000000 ? 100000000 : max;
    userNum = 0;
    Table = creatTable();
}

std::vector<UserMap::tableNode *> UserMap::creatTable() {
    return std::vector<tableNode *>(maxUserNum);
}

bool UserMap::insert(User &user) {
    unsigned long pos = user.getUid();
    if (!pos)
        return false;
    if(!Table[pos])
        Table[pos] = new tableNode();
    tableNode *Node = Table[pos];
    while (Node->Next) {
        if (Node->curUser == user)
            return false;
        Node = Node->Next;
    }
    if (Node->curUser == user)
        return false;
    else
        Node->Next = new tableNode(user);
    ++userNum;
    return true;
}

bool UserMap::findUser(User &user) {
    unsigned long pos = user.getUid();
    if (!pos)
        return false;
    tableNode *Node = Table[pos];
    while (Node) {
        if (Node->curUser == user)
            return true;
        else
            Node = Node->Next;
    }
    return false;
}

UserMap::tableNode::tableNode() {
    curUser = User();
    Next = nullptr;
}

UserMap::tableNode::tableNode(const User &user) {
    curUser = user;
    Next = nullptr;
}

User &UserMap::getUser(const std::string &name) {
    unsigned long pos = User::getUid(name);
    if (!pos)
        return Table[0]->curUser;
    tableNode *Node = Table[pos]->Next;
    while (Node) {
        if (Node->curUser.getName() == name)
            return Node->curUser;
        else
            Node = Node->Next;
    }
    return Table[0]->curUser;
}

bool UserMap::remove(const User &user) {
    unsigned long pos = user.getUid();
    if (!pos || !userNum)
        return false;
    tableNode *CurNode = Table[pos]->Next;
    tableNode *LastNode = Table[pos];
    while (CurNode) {
        if (CurNode->curUser == user) {
            LastNode->Next = CurNode->Next;
            --userNum;
            return true;
        } else {
            LastNode = CurNode;
            CurNode = CurNode->Next;
        }
    }
    return false;
}

bool UserMap::remove(const std::string &name) {
    unsigned long pos = User::getUid(name);
    if (!pos || !userNum)
        return false;
    tableNode *CurNode = Table[pos]->Next;
    tableNode *LastNode = Table[pos];
    while (CurNode) {
        if (CurNode->curUser.getName() == name) {
            LastNode->Next = CurNode->Next;
            --userNum;
            return true;
        } else {
            LastNode = CurNode;
            CurNode = CurNode->Next;
        }
    }
    return false;
}

unsigned int UserMap::getUserNum() {
    return userNum;
}

bool UserMap::updateUser(User &user) {
    unsigned long pos = user.getUid();
    if (!pos || !userNum)
        return false;
    tableNode *CurNode = Table[pos]->Next;
    tableNode *LastNode = Table[pos];
    while (CurNode) {
        if (CurNode->curUser == user) {
            CurNode->curUser = user;
            return true;
        } else {
            LastNode = CurNode;
            CurNode = CurNode->Next;
        }
    }
    return false;
}

std::vector<UserMap::tableNode *> UserMap::getTable() {
    return Table;
}
