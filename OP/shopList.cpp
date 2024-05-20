//
// Created by ヒヤシンス on 2023/11/25.
//

#include "shopList.h"

//添加商品
void shopList::operator+(commodity &com) {
    this->m.push_back(com);
}

//查询购物车信息
void shopList::print() {
    cout << "当前购物车中商品信息如下:" << endl;
    for (auto &it: m) {
        cout << it.get_id() << " 单价:" << it.get_price() << " 数量:" << it.get_number() << endl;
    }
}

//清空
void shopList::clear() {
    this->m.clear();
}

//查询
bool shopList::find(const string &id) {
    for (auto &it: m) {
        if (it.get_id() == id) {
            return true;
        }
    }
    return false;
}

//获取
commodity &shopList::get_com(const string &id) {
    for (auto &it: m) {
        if (it.get_id() == id) {
            return it;
        }
    }
}

//删除
void shopList::Delete(const string &id) {
    this->m.remove(this->get_com(id));
}

//求总价
double shopList::sum() {
    double sum_price = 0;
    for (auto &it: m) {
        sum_price += it.get_price() * it.get_number();
    }
    return sum_price;
}

//结算获取总价格
double shopList::check_out_sum_price() {
    cout << "请输入要购买的商品序号:（空格间隔,0结束)" << endl;
    int x = 0;
    double sum_price = 0;
    cin >> x;
    //将商品序号添加
    while (x) {
        number.push_back(x);
        cin >> x;
    }
    //计算总价格
    for (auto t: number) {
        auto it = m.begin();
        advance(it, t - 1);
        sum_price += it->get_price() * it->get_number();
    }
    //返回总价格
    return sum_price;
}

//保存
bool shopList::save(const string &customer_id) {
    //输入流
    fstream in("../Information/shopList.csv");
    if (!in.is_open()) {
        cout << "打开购物车信息失败" << endl;
        return false;
    }
    //输出流至临时文件
    ofstream out("../Information/temp.csv");
    if (!out.is_open()) {
        cout << "打开临时文件失败" << endl;
        return false;
    }
    //记录shopList.csv是否存在旧的信息
    bool flag = false;
    //存储临时变量
    string line;
    string cus_id;
    string com_id;
    double com_price;
    int com_num;
    string token;
    //读入
    while (getline(in, line)) {
        istringstream iss(line);
        getline(iss, token, ',');
        cus_id = token;
        out << cus_id;
        if (cus_id == customer_id) {
            for (const auto &it: m) {
                out << "," << it.get_id() << "," << it.get_price() << "," << it.get_number();
            }
            flag = true;
            out << endl;
        } else {
            while (getline(iss, token, ',')) {
//                id
                com_id = token;
                getline(iss, token, ',');
                //价格
                com_price = stod(token);
                getline(iss, token, ',');
                //数量
                com_num = stoi(token);
                out << "," << com_id << "," << com_price << "," << com_num;
            }
            out << endl;
        }

    }
    //无对应用户信息
    if (!flag) {
        out << customer_id;
        for (const auto &it: m) {
            out << "," << it.get_id() << "," << it.get_price() << "," << it.get_number();
        }
        out << endl;
    }
    //关闭流
    in.close();
    out.close();
    // 删除原文件，并将临时文件重命名为原文件
    if (remove("../Information/shopList.csv") != 0) {
        cout << "删除失败" << endl;
        return false;
    }
    //重命名
    if (rename("../Information/temp.csv", "../Information/shopList.csv") != 0) {
        cout << "重命名失败" << endl;
        return false;
    }
    return true;
}

//初始化
bool shopList::init(const string &customer_id) {
    ifstream in;
    in.open("../Information/shopList.csv", ios::in);
    if (!in.is_open()) {
        cout << "打开购物车信息失败" << endl;
        return false;
    } else {
        //清空信息
        m.clear();
        //存储临时信息
        string cus_id;
        string line;
        string token;
        //读入
        while (getline(in, line)) {
            //字符串流
            istringstream iss(line);
            getline(iss, cus_id, ',');
            if (cus_id == customer_id) {
                string com_id;
                int com_num = 0;
                double com_price = 0;
                while (getline(iss, token, ',')) {
                    com_id = token;
                    getline(iss, token, ',');
                    com_price = stod(token);
                    getline(iss, token, ',');
                    com_num = stoi(token);
                    commodity c(com_id, com_price, com_num);
                    m.push_back(c);
                }
                break;
            }
        }
    }
    in.close();
    return true;
}

