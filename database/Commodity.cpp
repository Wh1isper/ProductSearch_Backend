#include "Commodity.h"

Commodity::Commodity() {
    Sid = -1;
    Name = "Unknown";
    Price = -1;
    Label = LabelList();
    Cid = -1;
}

Commodity::Commodity(const std::string &name, float price, LabelList &label, int sid) {
    Sid = sid;
    Name = name;
    Price = price;
    Label = label;
    Cid = -1;
}

Commodity::Commodity(const std::string &name, float price, int sid) {
    Sid = sid;
    Name = name;
    Price = price;
    Label = LabelList();
    Cid = -1;
}

int Commodity::getSid() {
    return Sid;
}

int Commodity::getCid() {
    return Cid;
}

void Commodity::setCid(int cid) {
    Cid = cid;
}

LabelList Commodity::getLabel() {
    return Label;
}

std::string Commodity::getName() {
    return Name;
}

float Commodity::getPrice() const {
    return Price;
}

float Commodity::getPrice(const Commodity &C) {
    return C.getPrice();
}

Commodity::Commodity(const std::string &name, float price, std::vector<std::string> &label, int sid) {
    Sid = sid;
    Name = name;
    Price = price;
    Label = LabelList(label);
    Cid = -1;
}

void Commodity::setSid(int sid) {
    Sid = sid;
}

void Commodity::addLabel(const std::string &lbl) {
    Label.append(lbl);
}

void Commodity::removeLabel(const std::string &lbl) {
    Label.remove(lbl);
}

void Commodity::addLabel(const std::vector<std::string> &lblList) {
    for (const std::string &lbl:lblList) {
        Label.append(lbl);
    }
}

void Commodity::addLabel(const LabelList &lblList) {
    Label.append(lblList);
}
