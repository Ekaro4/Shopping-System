//
// Created by ヒヤシンス on 2023/11/13.
//

#include "customer.h"

//重载相等运算符
bool customer::operator==(const customer &o) {
    if (this->id == o.id) return true;
    return false;
}

//重载构造函数
customer::customer(const string &id, const string &password, const double &money) {
    this->id = id;
    this->money = money;
    this->password = password;
}

//获取余额
double customer::get_money() const {
    return this->money;
}

//获取ID
string customer::get_id() const {
    return this->id;
}

//获取密码
string customer::get_password() const {
    return this->password;
}

//修改密码
void customer::change_password(const string &new_password) {
    this->password = new_password;
}
//买完扣钱
void customer::cost(double cost_money) {
    this->money -= cost_money;
}

