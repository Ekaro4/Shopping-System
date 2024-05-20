//
// Created by ヒヤシンス on 2023/11/13.
//

#include "information.h"

//初始化
bool Information::Init() {
    //初始化商品信息
    bool flag1 = (this->com_s).init();
    //初始化顾客信息
    bool flag2 = (this->cus_s).init();
    if (flag1 && flag2) {
        return true;
    } else return false;
}

//保存信息
bool Information::save() {
    if (com_s.save() && cus_s.save()) return true;
        //保存失败
    else return false;
}

void Information::menu() {
    int order = -1;
    while (true) {
        cout << "欢迎来到主菜单!!" << endl;
        cout << "请问您要做什么:" << endl;
        cout << "1.浏览商品" << endl;
        cout << "2.登录账户" << endl;
        cout << "3.注册用户" << endl;
        cout << "4.退出系统" << endl;
        cin >> order;
        //x用来记录一些操作的执行与否
        int x;
        //y与x作用相同
        string y;
        //选择执行
        if (order == 1) {
            //打印商品信息列表
            this->com_s.print();
        } else if (order == 2) {
            //登录账户
            if (curr_user_type != -1 && curr_user_id != "null") {
                cout << "已经登录了 " << curr_user_id << " 账户" << endl;
                cout << "禁止重复登录!" << endl;
            }
            cout << "请输入账户名和密码,用空格分开:" << endl;
            x = login();
            //顾客登录成功
            if (x == 1) {
                cus_menu();
            }
                //管理员登录成功
            else if (x == 2) {
                admin_menu();
            }
                //密码错误
            else if (x == 0) {

            }
                //无该用户
            else {
                cout << "请问您是否要注册新用户?(y/n)" << endl;
                cin >> y;
                if (y == "y") {
                    sign();
                }
            }
        } else if (order == 3) {
            //注册用户
            sign();
            break;
        } else if (order == 4) {
            //保存用户信息与商品信息
            cout << "确认退出系统?(y/n)" << endl;
            cin >> y;
            //退出
            if (y == "y") {
                if (!save()) {
                    cout << "保存信息失败!!" << endl;
                    exit(-1);
                }
                cout << "感谢使用本系统!" << endl;
                exit(0);
            }
                //其他输入则不退出
            else {
                cout << "已取消退出!" << endl;
            }
        } else {
            cout << "非法输入!" << endl;
            //清除错误状态
            cin.clear();
            //忽略剩下的输入
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

//登录账户
int Information::login() {

    string id;
    string password;
    cin >> id >> password;
    //用户名为管理员用户名
    if (id == admin_id) {
        if (password == admin_password) {
            cout << "登录成功!" << endl;
            cout << "您当前登录的是管理员账户!" << endl;
            curr_user_id = id;
            curr_user_type = 2;
            //管理员返回2
            return 2;
        } else {
            //密码错误返回0
            cout << "密码错误!" << endl;
            return 0;
        }
    }
        //查找是否为顾客
    else if (this->cus_s.find(id)) {
        //匹配密码
        if (this->cus_s.get_password(id) == password) {
            cout << "登录成功!" << endl;
            cout << "您当前登录的是 " << id << " 用户" << endl;
            if (this->event_discount()) {
                cout << "当前有" << this->event << "活动!" << endl;
                cout << "全场商品 " << this->event_dis * 10 << "折!" << endl;
            }
            curr_user_type = 1;
            curr_user_id = id;
            //计算折扣情况
            coupon_discount();
            //初始化历史记录与购物车
            this->sL.init(curr_user_id);
            this->history.init(curr_user_id);
            //用户返回1
            return 1;
        }
            //密码错误
        else {
            cout << "密码错误!" << endl;
            //密码错误返回0
            return 0;
        }
    } else {
        cout << "登录失败!" << endl;
        cout << "未找到该用户" << endl;
        //无该用户返回-1
        return -1;
    }
}

//注册账户
bool Information::sign() {
    string id;
    string password;
    cout << "请输入用户名和密码,用空格分开" << endl;
    cin >> id >> password;
    if (id == admin_id) {
        cout << "不能与管理员同名!" << endl;
        return false;
    }
    //临时变量
    customer cur_cus(id, password, 0);
    if (cus_s.add(cur_cus)) {
        //添加信息成功
        cout << "注册成功!" << endl;
        cout << "是否立即登录?(y/n)" << endl;
        string s;
        cin >> s;
        if (s == "y") {
            curr_user_id = id;
            curr_user_type = 1;
            cout << "登录成功!" << endl;
            cout << "您当前使用的是 " << id << " 用户" << endl;
            cus_menu();
        }
        return true;
    } else {
        cout << "注册失败!" << endl;
        return false;
    }
}

//登出账户
bool Information::log_out() {
    if (curr_user_id == "null" && curr_user_type == -1) {
        cout << "当前未登录任何账户!" << endl;
        return false;
    }
    curr_user_id = "null";
    curr_user_type = -1;
    //情况信息
    sL.clear();
    if (curr_user_id == "null" && curr_user_type == -1) {
        //确认退出
        return true;
    } else return false;
}

//购买商品
void Information::Buy() {
    //未登录
    if (curr_user_id == "null" && curr_user_type == -1) {
        cout << "当前未登录任何账户!" << endl;
        cout << "请登录后再进行购买!" << endl;
        return;
    }
        //已登录
    else {
        if (curr_user_id == admin_id) {
            cout << "管理员还用买东西?!" << endl;
            cout << "零元购!" << endl;
            return;
        }
        //获取用户对象
        customer &cur_cus = this->cus_s.get_cus(curr_user_id);
        cout << "请输入要购买的商品名称:" << endl;
        //商品名称
        string id;
        cin >> id;
        if (!this->com_s.find(id)) {
            //未找到对应商品
            cout << "未找到商品!" << endl;
        } else {
            //获取商品对象
            commodity &cur_com = this->com_s.get_com(id);
            //商品有存货
            if (cur_com.get_number() <= 0) {
                cout << "购买失败!" << endl;
                cout << "商品已售完!" << endl;
            }
                //卖完啦！
            else {
                cout << "请输入要购买的数量:" << endl;
                int number;
                cin >> number;
                if (number * cur_com.get_price() * event_dis <= cur_cus.get_money()) {
                    //钱管够！
                    cur_cus.cost(number * cur_com.get_price() * event_dis);
                    cur_com.sold(number);
                    //添加历史信息
                    string time = convertLocalTimeToBeijingTime();
                    vector<commodity> temp;
                    temp.emplace_back(cur_com.get_id(), -1, number);
                    history.insert(time, temp);
                    history.save();
                    history.init(curr_user_id);
                    cout << "购买成功!" << endl;
                } else {
                    //没钱 (╥_╥)
                    cout << "购买失败!" << endl;
                    cout << "余额不足!" << endl;
                }
            }
        }
    }
}

//用户菜单
void Information::cus_menu() {
    int order = -1;
    while (true) {
        cout << "请问您要做什么:" << endl;
        cout << "1.浏览商品" << endl;
        cout << "2.查找商品" << endl;
        cout << "3.购物" << endl;
        cout << "4.进入购物车" << endl;
        cout << "5.查看购物历史" << endl;
        cout << "6.管理个人信息" << endl;
        cout << "7.退出登录" << endl;
        cout << "8.退出系统" << endl;
        cin >> order;
        //记录操作
        string y;
        //选择执行
        if (order == 1) {
            //打印商品信息列表
            this->com_s.print();
        } else if (order == 2) {
            cout << "请选择查询方式:" << endl;
            cout << "1.精确查找(准确的名称)" << endl;
            cout << "2.关键词查找" << endl;
            int x;
            cin >> x;
            if (x == 1) {
                cout << "请输入名称:" << endl;
                string id;
                cin >> id;
                if (this->com_s.find(id)) {
                    commodity cur = this->com_s.get_com(id);
                    cout << cur.get_id() << " 单价:" << cur.get_price() << " 剩余数量:" << cur.get_number() << endl;
                } else {
                    cout << "未找到该商品!" << endl;
                    //清除错误状态
                    cin.clear();
                    //忽略剩下的输入
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                }
            } else if (x == 2) {
                cout << "请输入关键词:" << endl;
                string key;
                cin >> key;
                commodity temp = this->com_s.search_by_key(key);
                cout << temp.get_id() << " 单价: " << temp.get_price() << " 存货: " << temp.get_number() << endl;
            } else {
                cout << "非法输入!" << endl;
                //清除错误状态
                cin.clear();
                //忽略剩下的输入
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            }
        } else if (order == 3) {
            //购物
            Buy();
        } else if (order == 4) {
            //购物车
            shopListMenu();
        } else if (order == 5) {
            //查看历史记录
            cout << "请输入要查看的时间点,格式为'年份.月份.日期.小时:分钟'" << endl;
            string time_;
            cin >> time_;
            history.print(time_);
        } else if (order == 6) {
            //管理个人信息
            cus_inf_menu();
        } else if (order == 7) {
            cout << "确定要退出登录吗?(y/n)" << endl;
            cin >> y;
            //退出登录
            if (y == "y") {
                //成功退出
                if (log_out()) {
                    cout << "退出登录成功!" << endl;
                    menu();
                    break;
                }
                    //退出失败
                else {
                    cout << "退出登录失败!" << endl;
                }
            }
                //其他输入则继续下一轮
            else {
                cout << "已取消退出登录!" << endl;
            }
        } else if (order == 8) {
            //保存用户信息与商品信息
            cout << "确认退出系统?(y/n)" << endl;
            cin >> y;
            //退出
            if (y == "y") {
                if (!save()) {
                    cout << "保存信息失败!!" << endl;
                    exit(-1);
                }
                cout << "感谢使用本系统!" << endl;
                exit(0);
            }
                //其他输入则不退出
            else {
                cout << "取消成功!" << endl;
            }
        } else {
            cout << "非法输入!" << endl;
            //清除错误状态
            cin.clear();
            //忽略剩下的输入
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

//管理员菜单
void Information::admin_menu() {
    int order = -1;
    while (true) {
        cout << curr_user_id << " 管理员,欢迎来到 OP 系统" << endl;
        cout << "1.浏览商品信息" << endl;
        cout << "2.浏览用户信息" << endl;
        cout << "3.添加商品信息" << endl;
        cout << "4.添加用户信息" << endl;
        cout << "5.删除商品信息" << endl;
        cout << "6.删除用户信息" << endl;
        cout << "7.修改商品信息" << endl;
        cout << "8.退出登录" << endl;
        cout << "9.退出系统" << endl;
        cin >> order;
        //记录操作
        string y;
        //选择执行
        //浏览商品信息
        if (order == 1) {
            //打印商品信息列表
            this->com_s.print();
        }
            //浏览用户信息
        else if (order == 2) {
            this->cus_s.print();
        }
            //添加商品信息
        else if (order == 3) {
            cout << "请输入商品ID与单价" << endl;
            string id;
            double price;
            int num;
            cin >> id >> price;
            cout << "请输入库存量:" << endl;
            cin >> num;
            commodity temp(id, price, num);
            this->com_s.add(temp);
            cout << "添加成功!" << endl;
        }
            //添加用户信息
        else if (order == 4) {
            cout << "请输入用户ID与密码" << endl;
            string id;
            string password;
            cin >> id >> password;
            //临时变量
            customer temp(id, password, 0);
            //添加信息
            this->cus_s.add(temp);
            cout << "添加成功!" << endl;
        }
            //删除商品信息
        else if (order == 5) {
            cout << "请输入商品ID" << endl;
            string id;
            cin >> id;
            this->com_s.com_delete(id);
        }
            //删除用户信息
        else if (order == 6) {
            cout << "请输入用户ID:" << endl;
            string id;
            cin >> id;
            this->cus_s.cus_delete(id);
        }
            //修改商品信息
        else if (order == 7) {
            com_inf_modify();
        }
            //退出登录
        else if (order == 8) {
            cout << "确定要退出登录吗?(y/n)" << endl;
            cin >> y;
            //退出登录
            if (y == "y") {
                //成功退出
                if (log_out()) {
                    cout << "退出登录成功!" << endl;
                    menu();
                    //结束循环
                    break;
                }
                    //退出失败
                else {
                    cout << "退出登录失败!" << endl;
                }
            }
                //其他输入则继续下一轮
            else {
                cout << "已取消退出登录!" << endl;
            }
        } else if (order == 9) {
            //保存用户信息与商品信息
            cout << "确认退出系统?(y/n)" << endl;
            cin >> y;
            //退出
            if (y == "y") {
                if (!save()) {
                    cout << "保存信息失败!!" << endl;
                    exit(-1);
                }
                cout << "感谢使用本系统!" << endl;
                exit(0);
            }
                //其他输入则不退出
            else {
                cout << "取消成功!" << endl;
            }
        } else {
            cout << "非法输入!" << endl;
            //清除错误状态
            cin.clear();
            //忽略剩下的输入
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
        //保存
        this->save();
        this->Init();
    }
}

//用户个人信息管理菜单
void Information::cus_inf_menu() {
    int order = -1;
    while (true) {
        cout << "欢迎来到个人信息管理界面!!" << endl;
        cout << "请问您要做什么:" << endl;
        cout << "1.更改账户名" << endl;
        cout << "2.更改密码" << endl;
        cout << "3.返回上级菜单" << endl;
        cin >> order;
        //x用来记录一些操作的执行与否
        int x;
        //y与x作用相同
        string y;
        //选择执行
        if (order == 1) {
            //更改账户名
            cout << "请输入新的账户名:" << endl;
            string new_id;
            cin >> new_id;
            if (this->cus_s.find(new_id)) {
                cout << "修改失败!" << endl;
                cout << "此用户名已经被使用!" << endl;
            } else {
                //修改系统中储存的账户名
                this->cus_s.change_id(curr_user_id, new_id);
                //修改当前账户名
                this->curr_user_id = new_id;
                cout << "修改账户名成功!" << endl;
            }
        } else if (order == 2) {
            //修改密码
            cout << "请输入新的密码:" << endl;
            string new_password;
            cin >> new_password;
            this->cus_s.get_cus(curr_user_id).change_password(new_password);
            cout << "修改密码成功!" << endl;
        } else if (order == 3) {
            //返回上级
            break;
        } else {
            cout << "非法输入!" << endl;
            //清除错误状态
            cin.clear();
            //忽略剩下的输入
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
        //保存
        this->save();
        this->Init();
    }
}

//修改商品信息
void Information::com_inf_modify() {
    cout << "请输入要修改的商品ID:" << endl;
    string id;
    cin >> id;
    if (!this->com_s.find(id)) {
        cout << "未找到 " << id << " 商品" << endl;
    } else {
        cout << "请输入你要修改的信息:" << endl;
        cout << "1.ID" << endl << "2.单价" << endl << "3.存货量" << endl;
        int x;
        cin >> x;
        if (x == 1) {
            //ID
            cout << "请输入新的ID" << endl;
            string new_id;
            cin >> new_id;
            this->com_s.change_id(id, new_id);
        } else if (x == 2) {
            //价格
            cout << "请输入新的单价:" << endl;
            double new_price;
            cin >> new_price;
            this->com_s.change_price(id, new_price);
        } else if (x == 3) {
            //数量
            cout << "请输入新的存货量" << endl;
            int new_number;
            cin >> new_number;
            this->com_s.change_number(id, new_number);
        } else {
            //default
            cout << "非法输入!" << endl;
            return;
        }
        cout << "修改成功!" << endl;
    }
}

//购物车菜单
void Information::shopListMenu() {
    int order = -1;
    while (true) {
        cout << "欢迎来到购物车菜单!" << endl;
        cout << "请问您要做什么:" << endl;
        cout << "1.查看当前购物车信息" << endl;
        cout << "2.添加商品" << endl;
        cout << "3.删除商品" << endl;
        cout << "4.修改商品购买数量" << endl;
        cout << "5.总价" << endl;
        cout << "6.结算" << endl;
        cout << "7.返回上级菜单" << endl;
        cin >> order;
        //x用来记录一些操作的执行与否
        int x;
        //y与x作用相同
        string y;
        //选择执行
        if (order == 1) {
            //查看当前购物车信息
            this->sL.print();
        } else if (order == 2) {
            cout << "请输入要添加的商品名称:" << endl;
            //商品名称
            string id;
            cin >> id;
            if (!this->com_s.find(id)) {
                cout << "未找到商品!" << endl;
            } else if (sL.find(id)) {
                cout << "购物车已经有该商品!" << endl;
            } else {
                //获取商品对象
                commodity cur_com = this->com_s.get_com(id);
                //商品没存货
                if (cur_com.get_number() <= 0) {
                    cout << "添加失败!" << endl;
                    cout << "商品已售完!" << endl;
                } else {
                    cout << "请输入数量:" << endl;
                    int number;
                    cin >> number;
                    if (number > cur_com.get_number()) {
                        //商品存量不足
                        cout << "存货不够" << endl;
                    } else {
                        //添加至购物车
                        cur_com.change_number(number);
                        sL + (cur_com);
                        cout << "添加成功!" << endl;
                        //保存信息
                        sL.save(curr_user_id);
                        sL.init(curr_user_id);
                    }
                }
            }
        } else if (order == 3) {
            //删除购物车商品
            cout << "请输入要删除的商品名称:" << endl;
            string id;
            cin >> id;
            if (!this->sL.find(id)) {
                cout << "未找到商品!" << endl;
            } else {
                //删除
                sL.Delete(id);
                sL.save(curr_user_id);
                sL.init(curr_user_id);
                cout << "删除成功!" << endl;

            }
        } else if (order == 4) {
            //修改购物车商品数量
            cout << "请输入要修改的商品名称:" << endl;
            string id;
            cin >> id;
            cout << "请输入新的数量:" << endl;
            int number;
            cin >> number;
            if (!this->sL.find(id)) {
                cout << "未找到商品!" << endl;
            } else {
                //获取引用
                //修改数量
                sL.get_com(id).change_number(number);
                sL.save(curr_user_id);
                sL.init(curr_user_id);
                cout << "修改成功!" << endl;
            }
        } else if (order == 5) {
            //计算总价
            cout << "总价为: " << this->sL.sum() << endl;
        } else if (order == 6) {
            //结算
            //计算原总价
            double sum_price = sL.check_out_sum_price();
            //计算折扣信息
            sum_price = this->coupon_check(sum_price);
            sum_price = this->event_check(sum_price);
            if (cus_s.get_cus(curr_user_id).get_money() < sum_price) {
                cout << "钱不够!" << endl;
            } else {
                //钱够
                cout << "确定购买?" << endl;
                cin >> y;
                if (y == "y") {
                    //扣钱
                    cus_s.get_cus(curr_user_id).cost(sum_price);
                    //结算
                    checked();
                    cout << "购买成功!" << endl;
                    cout << "共花费: " << sum_price << "元" << endl;
                    //保存
                    sL.save(curr_user_id);
                    sL.init(curr_user_id);
                } else {
                    cout << "取消成功!" << endl;
                }
            }
        } else if (order == 7) {
            //返回上级
            break;
        } else {
            cout << "非法输入!" << endl;
            //清除错误状态
            cin.clear();
            //忽略剩下的输入
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

//优惠券相关的总价计算
double Information::coupon_check(double x) {
    double sum_price = x;
    customer &cur = this->cus_s.get_cus(curr_user_id);
    cout << "请输入是否要使用优惠券(y/n):" << endl;
    string temp;
    cin >> temp;
    if (temp == "y") {
        //使用优惠券
        if (this->curr_user_type == 1 && coupon_id != "null") {
            cout << "请输入优惠券id:" << endl;
            string cur_discount_id;
            cin >> cur_discount_id;
            if (cur_discount_id == coupon_id) {
                //确认优惠券信息正确
                sum_price = sum_price * coupon_dis;
                this->coupon_id = "null";
                return sum_price;
            } else {
                cout << "优惠券信息不正确!" << endl;
                return sum_price;
            }
        } else {
            cout << "您当前无可用的优惠券!" << endl;
            return sum_price;
        }
    } else {
        return sum_price;
    }
}

//优惠券发放
void Information::coupon_discount() {
    //计算优惠券信息
    string coupon_id = generateCouponCode();
    if (curr_user_type == 1 && coupon_id != "null") {
        //确认发放
        this->coupon_id = generateCouponCode();
        cout << "您本次登录获得了一个优惠券(8折)!" << endl;
        cout << "ID为: " << coupon_id << endl;
        cout << "退出登录即作废!" << endl;
    } else {
        return;
    }
}

//生成优惠券码
string Information::generateCouponCode() {
    //根据时间生成优惠券码
    srand(time(nullptr));
    if (rand() % 2 == 0) {
        //确认发放
        const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        std::string couponCode;
        for (int i = 0; i < 6; ++i)
            couponCode += characters[rand() % characters.size()];
        return couponCode;
    } else {
        //不发放
        return "null";
    }

}

//结算完成改数量
void Information::checked() {
    vector<commodity> temp;
    //时间信息
    string time = convertLocalTimeToBeijingTime();
    for (auto t: sL.number) {
        auto it = sL.m.begin();
        advance(it, t - 1);
        this->com_s.get_com(it->get_id()).sold(it->get_number());
        temp.push_back(commodity(it->get_id(), it->get_price(), it->get_number()));
        it->sold(it->get_number());
    }
    //插入历史记录
    history.insert(time, temp);
    auto it = sL.m.begin();
    //清除购物车信息
    for (it = sL.m.begin(); it != sL.m.end();) {
        if (it->get_number() == 0) {
            it = sL.m.erase(it);
        } else {
            it++;
        }
    }
    //保存
    history.save();
    history.init(curr_user_id);
    sL.number.clear();
    save();
    Init();
}

//活动
bool Information::event_discount() {
    this->event_dis = 0.9;
    this->event = "WINTER";
    return true;
}

//计算活动折扣
double Information::event_check(double x) {
    return x * this->event_dis;
}

//格式化记录时间信息
string Information::convertLocalTimeToBeijingTime() {
    std::time_t currentTime = std::time(nullptr);
    std::tm localTime = *std::localtime(&currentTime);
    const int timeZoneOffset = -1; // 北京时间为UTC+8
    // 使用 std::mktime 将 tm 结构转换为 time_t
    time_t localTimestamp = std::mktime(const_cast<std::tm *>(&localTime));
    // 计算北京时间的 time_t
    time_t beijingTimestamp = localTimestamp + timeZoneOffset * 3600;
    // 将北京时间的 time_t 转换为 tm 结构
    std::tm beijingTime = *std::localtime(&beijingTimestamp);
    // 格式化时间为字符串并返回
    std::ostringstream formattedTime;
    formattedTime << std::put_time(&beijingTime, "%Y.%m.%d.%H:%M");
    return formattedTime.str();
}

