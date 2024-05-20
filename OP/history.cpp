//
// Created by ヒヤシンス on 2023/12/11.
//

#include <algorithm>
#include "history.h"

bool history::init(const string &customer_id) {
    //载入用户id
    this->name = customer_id;
    //清除初始化
    this->m.clear();
    //输入流
    ifstream in("../Information/history.csv", ios::in);
    if (!in.is_open()) {
        //没打开
        return false;
    }
    //存储信息
    string cus_id;
    string line;
    string token;
    //分行读入
    while (getline(in, line)) {
        istringstream iss(line);
        //id
        getline(iss, cus_id, ',');
        if (cus_id == customer_id) {
            //找到对应用户
            while (getline(iss, token, ',')) {
                //临时变量
                vector<commodity> v;
                //时间
                string time;
                string com_id;
                string num;
                string price;
                istringstream i(token);
                getline(i, time, '-');
                while (getline(i, token, '-')) {
                    istringstream t(token);
                    while (getline(t, com_id, '*')) {
                        getline(t, price, '*');
                        getline(t, num, '-');
                    }
                    int number = stoi(num);
                    double prices = stod(price);
                    commodity com(com_id, prices, number);
                    v.push_back(com);
                }
                //插入对应历史信息
                this->m.insert(pair<string, vector<commodity>>(time, v));
            }
        }
    }
    return true;
}


//打印历史信息
void history::print(const string &time_) {
    cout << "您" << time_ << "时间内的购物历史如下:" << endl;
    double sum = 0;
    if (m.count(time_) == 0) {
        cout << "当前时间历史为空" << endl;
    } else {
        cout << "历史如下:" << endl;
        for (auto it: m[time_]) {
            //打印输出
            cout << it.get_id() << "*" << it.get_price() << '*' << it.get_number() << endl;
            sum += it.get_price() * it.get_number();
        }
    }
    cout << "总价格:" << sum << endl;
}

//插入历史记录
void history::insert(const string &time, vector<commodity> v) {
    if (this->m.count(time) == 0) {
        //没有旧记录
        this->m.insert(pair<string, vector<commodity>>(time, v));
    } else {
        for (const auto &it: v) {
            //存在旧记录
            this->m[time].push_back(it);
        }
    }
}

//保存
void history::save() {
    //temp临时变量
    //统一格式化输出
    string temp = "";
    temp += name;
    temp += ",";
    for (auto it: m) {
        temp += it.first;
        temp += "-";
        for (auto com: it.second) {
            temp += com.get_id();
            temp += "*";
            temp += to_string(com.get_number());
            temp += "*";
            temp += to_string(com.get_price());
            temp += "-";
        }
        temp += ",";
    }
    //更改一整行的数据
    modifyCSVLine("../Information/history.csv", name, temp);
}

//更改csv文件中的一行
void history::modifyCSVLine(const std::string &filename, const std::string &targetName, const std::string &newContent) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }

    inputFile.close();

    auto it = std::find_if(lines.begin(), lines.end(), [&](const std::string &str) {
        return str.find(targetName) != std::string::npos;
    });

    if (it != lines.end()) {
        // 替换整行
        *it = newContent;

        std::ofstream outputFile(filename);
        if (!outputFile.is_open()) {
            std::cerr << "Error opening file for writing: " << filename << std::endl;
            return;
        }
        for (const auto &updatedLine: lines) {
            outputFile << updatedLine << '\n';
        }
        outputFile.close();
        std::cout << "Line modified successfully.\n";
    } else {
        std::cout << "Line not found.\n";
    }
}