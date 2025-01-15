#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

void clear() {	//一个跨平台的清屏方案
#ifdef _WIN32
	system("cls");//Win系统用cls
#else
	system("clear");//类UNIX系统用clear
#endif
}

void sleep_s(int i) { //等待
	//这里不命名为sleep，因为sleep可能在类UNIX系统有定义
	this_thread::sleep_for(chrono::seconds(i));
}


void stop() { //退出系统
	cout << endl << endl << "ATM自助系统即将退出，欢迎再次使用！" << endl;
	sleep_s(1);
	cout << "请记得取走您的卡片，将于2秒后退出系统...";
	sleep_s(2);
	exit(0);
}

void welcome() {
	cout << endl << endl;
	cout << "    ————————————————————————————————————————" << endl;
	cout << "   |  db   d8b   db   d88888b   db         .o88b.    .d88b.    .88b  d88.   d88888b  |" << endl;
	cout << "   |  88   I8I   88   88'       88        d8P  Y8   .8P  Y8.   88'YbdP`88   88'      |" << endl;
	cout << "   |  88   I8I   88   88ooooo   88        8P        88    88   88  88  88   88ooooo  |" << endl;
	cout << "   |  Y8   I8I   88   88~~~~~   88        8b        88    88   88  88  88   88~~~~~  |" << endl;
	cout << "   |  `8b d8'8b d8'   88.       88booo.   Y8b  d8   `8b  d8'   88  88  88   88.      |" << endl;
	cout << "   |   `8b8' `8d8'    Y88888P   Y88888P    `Y88P'    `Y88P'    YP  YP  YP   Y88888P  |" << endl;
	cout << "   |                                                                                 |" << endl;
	cout << "    ————————————————————————————————————————" << endl << endl;

}

void menu() {
	cout << endl << endl;
	cout << "    ———————————— " << endl;
	cout << "   |  1.查询余额  4.转账    |" << endl;
	cout << "   |  2.存款      5.修改密码|" << endl;
	cout << "   |  3.取款      0.退卡    |" << endl;
	cout << "    ————————————" << endl << endl;
	cout << endl << endl << "请输入数字执行对应操作：";
}

void back_menu(int n) { //n秒后返回菜单提示语
	cout << endl << n << "秒后返回菜单...";
	sleep_s(n);
}

class CX {
private:
	string name, num, pwd;
	long long int bal;
	int limit;
	string situation;


	bool is_successful;//改密码用的
public:
	string final_date;
	string id;
	CX(string idid) { //初始化用户账户
		id = idid;
	}

	void load_account() { //加载账户信息
		ifstream ifst("data\\" + id + ".txt"); //卡号.txt
		string usel;
		string id_load;

		ifst >> usel >> id_load; //卡号
		ifst >> usel >> name; //名字
		ifst >> usel >> num; //身份证
		ifst >> usel >> pwd; //密码
		ifst >> usel >> bal; //余额
		ifst >> usel >> limit; //日限额
		ifst >> usel >> situation; //冻结了吗
		ifst >> usel >> final_date; //最后操作日期

		if (id_load != id) {
			clear();
			cerr << endl << endl << "此卡数据异常。请前往柜台进行操作！";
			sleep_s(1);
			stop();
		}


	}

	bool is_blocked() { //冻了吗
		return situation == "blocked";
	}

	string getname() {
		return name;
	}

	string getpwd() {
		return pwd;
	}
	string getnum() {
		return num;
	}
	long long int getbal() {
		return bal;
	}

	int getlimit() {
		return limit;
	}

	void chg_limit(int n) {
		limit = n ;
	}

	void show_bal() {
		cout << endl << endl << "您当前的账户余额为：" << bal << endl;
		cout << "您今日取款限额剩余：" << limit;
		cout << endl << endl << "按任意键返回菜单...";

		getch();

	}

	void save() {
		string filename = "data\\" + id + ".txt";
		ofstream ofs(filename, ios::trunc); //清空原文件

		if (!ofs) { // 检查文件是否打开成功
			cerr << "系统保存数据发生错误！请报告工作人员！" << endl;
			sleep_s(1);
			stop();
		}

// 按指定格式写入

		ofs << "账号 " << id << endl;
		ofs << "姓名 " << name << endl;
		ofs << "身份证 " << num << endl;
		ofs << "密码 " << pwd << endl;
		ofs << "余额 " << bal << endl;
		ofs << "限额 " << limit << endl;
		ofs << "状况 " << situation << endl;
		ofs << "最后操作日 " << final_date << endl;

		ofs.close();
	}

	void block() { //锁卡
		situation = "blocked";
		save();
	}

	void unlock() { //解卡
		situation = "ok";
		save();
	}

	void chg_bal(long long int x) {
		bal = x;
	}

	bool is_100n(int n) { //100倍数
		return n % 100 == 0;
	}

	void deposit() { //存款
		long long int sav;//防止数额过大
		for (int k = 0; k <= 3; k++) {
			if (k == 3) {
				cout << endl << "您的次数已经用尽。";
				back_menu(3);
				break;
			}
			cout << endl << endl << "请输入您要存款的金额，输入0返回菜单：";
			cin >> sav;
			if (sav > 1000000) {
				cout << endl << "存款数额过大，请到本行柜台操作！";
				sleep_s(1);
				back_menu(2);
				break;
			} else if (sav > 0 && is_100n(sav)) {//这里认为ATM都只能存百元大钞而零钱一般不可
				bal += sav;
				save();
				cout << endl << "存款成功！您本次存款" << sav << "元。" ;
				back_menu(3);
				break;
			} else if (is_100n(sav) == false) {
				cout << endl << "存款数额应该是100的整数倍！您还有" << 2 - k << "次机会。";
			} else if (sav == 0) {
				back_menu(1);
				break;
			}
			//这里默认ATM上没有负号故暂时不考虑负数情况
		}
	}

	void withdrawal() {//取款
		long long int get;
		for (int k = 0; k <= 3; k++) {
			if (k == 3) {
				cout << endl << "您的次数已经用尽。";
				back_menu(3);
				break;
			}
			cout << endl << endl << "请输入您要取款的金额（单笔限额2000元），输入0返回菜单：";
			cin >> get;
			if (get > bal) {
				cout << endl << "您的余额不足！您的余额仅剩" << bal << "元。您还有" << 2 - k << "次机会。";
			} else if (get > limit) {
				cout << endl << "您的限额不足！您的限额仅剩" << limit << "元。您还有" << 2 - k << "次机会。";
			} else if (get > 2000) {
				cout << endl << "超出单笔限额1000元！您还有" << 2 - k << "次机会。";
			} else if (get > 0 && is_100n(get) && get <= limit && get <= bal) { //这里认为ATM都只能取百元大钞而零钱一般不可，此行条件与前文重复为了安全考虑
				bal -= get;
				limit -= get;
				save();
				cout << endl << "取款成功！您本次取款" << get << "元。请取出您的钞票。" ;
				back_menu(3);
				break;
			} else if (is_100n(get) == false) {
				cout << endl << "取款数额应该是100的整数倍！您还有" << 2 - k << "次机会。";
			} else if (get == 0) {
				back_menu(1);
				break;
			}
			//这里默认ATM上没有负号故暂时不考虑负数情况
		}
	}

	void chg_pwd() { //改密
		string pwd_temp_chg, pwd_temp_chg_check;
		bool is_right;
		for (int k = 0; k <= 3; k++) {
			if (k != 0 && k < 3) {
				cout << endl << "两次密码输入不一致！请重新设置。" << endl << "您还有" << 3 - k << "次机会。";
			} else if (k == 3) {
				cout << "您的次数已用尽。修改密码失败！";
				break;
				is_successful = false;
			}
			cout << endl << "请输入您的新密码：";
			for (int s = 0; s <= 2; s++) {
				cin >> pwd_temp_chg;
				if (pwd_temp_chg.length() != 6 && s < 2) {
					cout << endl << "您输入的不是六位数字密码！您还有" << 2 - s << "次机会。" << endl << "请重新输入：";
				} else if (pwd_temp_chg.length() != 6 && s == 2) {
					cout << endl << "您的次数已用尽。修改密码失败！";
					is_right = false;
				} else {
					is_right = true;
					break;
				}
			}

			if (is_right == false) {
				is_successful = false;
				break;
			}

			cout << "请再次输入您的新密码：";
			cin >> pwd_temp_chg_check;

			if (pwd_temp_chg == pwd_temp_chg_check) {
				if (pwd_temp_chg != pwd) {
					pwd = pwd_temp_chg;
					save();
					cout << endl << "密码重设成功！";
					is_successful = true;
					break;
				} else {
					cout << endl << "安全起见，设置的密码不能和原来的密码一致！" << endl;
					k = -1; //重设失败次数
				}
			}
		}
	}

	void reset_pwd() { //冻结时重置密码，
		string numm = "";
		cout << endl << "请输入您的身份证号，X以“00”代替：";
		for (int j = 0; j <= 2; j++) {
			cin >> numm;
			if (numm.length() == 19 && numm[17] == '0' && numm[18] == '0') { //考虑ATM机只能输入数字的情况
				numm = numm.substr(0, 17) + "X";

			}

			if (numm != num) {
				if (j < 2) {
					cout << endl << "身份证号码不匹配！" << (numm.length() != 18 ? "（提示：您输入的不是合法的18位身份证号码）" : "") << endl;
					cout << "您还有" << 2 - j << "次机会。" << endl << endl << "请输入正确的身份证号：";
				} else {
					cout << endl << "您的次数已用尽。";
					stop();
				}
			} else {
				break;
			}
		}
		cout << endl << "身份证号码正确！" << endl;
		chg_pwd();
		if (is_successful == false) {
			stop();
		} else if (is_successful) {
			unlock();
			cout << "2秒后进入操作界面...";
			sleep_s(2);
		}
	}
};

int main() {
	string id_temp = "0";
	string  pwd_temp = "0";
	string date_temp = "0";
	int n;//操作输入用
	bool is_male = true;

	welcome();
	cout << "欢迎使用ATM系统！" << endl << endl;
	cout << "请输入您的卡号，输入0退出程序：";
	string filename = "0";
	for (int i = 0; i <= 2; i++) {
		cin >> id_temp;
		if (id_temp == "0") {
			clear();
			stop();
		}
		filename = "data\\" + id_temp + ".txt";
		ifstream file(filename);
		if (file.is_open() == false) {
			if (i < 2) {
				cout << endl << "卡号不存在哦！请输入正确的卡号！" << (id_temp.length() != 19 ? "（提示：您输入的不是19位数字卡号）" : "") << endl;
				cout << "您还有" << 2 - i << "次机会。" << endl << endl << "请输入正确的卡号:";
			} else {
				cout << endl << "您的次数已用尽。";
				stop();
			}

		} else {
			break;
		}
	}

	CX cus(id_temp);

	cus.load_account();
	if (cus.is_blocked()) { //检测到冻结时
		int opre = 0;
		cout << endl << "此卡已被冻结！是否立即解冻？" << endl << endl << "1：解冻" << endl << "其他数字：退出系统" << endl << endl << "请输入：";
		cin >> opre;
		if (opre == 1) {
			cus.reset_pwd();    //改密成功+完成登录
			goto login_success;
		} else {
			clear();
			stop();
		}
	}
	if ((cus.getnum()[16] - '0') == 0 || (cus.getnum()[16] - '0') % 2 == 0) {
		is_male = false;   //身份证号码判断性别
	}
	cout << endl << "您的卡号：" << cus.id << endl << "请输入密码,输入0退出程序：";
	for (int j = 0; j <= 2; j++) {
		cin >> pwd_temp;
		if (pwd_temp == "0") {
			clear();
			stop();
		}
		if (pwd_temp != cus.getpwd()) {
			if (j < 2) {
				cout << endl << "密码错误！" << ((pwd_temp.length() != 6) ? "（提示：您输入的不是6位数字密码）" : "") << endl;
				cout << "您还有" << 2 - j << "次机会，再输错" << 2 - j << "次后您的卡会被冻结。" << endl << endl << "请输入正确的密码：";
			} else {
				int opr;
				cus.block();
				cout << endl << "您的次数已用尽！您的卡已被冻结。" << endl << "是否需要重置密码并解冻？" ;
				cout << endl << endl << "1:需要" << endl << "其他数字:退出系统" << endl << endl << "请输入：";
				cin >> opr;
				if (opr == 1) {
					cus.reset_pwd();    //改密+跳出循环完成登录
					break;
				} else {
					clear();
					stop();
				}
			}
		} else {
			cout << endl << "密码正确！2秒后进入操作界面...";    //密码正确跳出循环
			sleep_s(2);
			break;
		}
	}





login_success://前面有goto用到


	clear();

	//从以下开始为主要功能，与登录没有关联
	time_t now = time(0);
	tm *today = localtime(&now);
	date_temp = to_string(1900 + today->tm_year) + "-" + to_string(1 + today->tm_mon) + "-" + to_string(today->tm_mday); //今日日期字符串

	if (date_temp != cus.final_date) { //校验日期重置限额
		cus.chg_limit(5000);
		cus.final_date = date_temp;
		cus.save();
	}

	while (1) {
		clear();
		cout << endl << endl << "欢迎您，" << cus.getname() << (is_male ? "先生" : "女士") << "！";
		menu();
		cin >> n;
		clear();
		switch (n) {
			case 0:
				stop();
			case 1:
				cus.show_bal();
				break;
			case 2:
				cus.deposit();
				break;
			case 3:
				cus.withdrawal();
				break;
			case 4: {
				string trans_id_temp, trans_id_temp_check;
				string filename_2 = "0";
				bool is_right_2 = false;
				bool is_passed = false;
				cout << endl << endl << "请确认后输入您转账的目标银行卡号，输入0返回菜单：";
				for (int i = 0; i <= 2; i++) {
					cin >> trans_id_temp;
					if (trans_id_temp == "0") {
						back_menu(1);
						break;
					}
					filename_2 = "data\\" + trans_id_temp + ".txt";
					ifstream file(filename_2);
					if (file.is_open() == false) {
						if (i < 2) {
							cout << endl << "卡号不存在哦！请输入正确的卡号！" << (id_temp.length() != 19 ? "（提示：您输入的不是19位数字卡号）" : "") << endl;
							cout << "您还有" << 2 - i << "次机会。" << endl << endl << "请输入正确的目标银行卡号,输入0返回菜单:";
						} else {
							cout << endl << "您的次数已用尽。";
							back_menu(3);
							break;

						}

					} else {
						is_right_2 = true;
						break;
					}


				}

				if (is_right_2) {
					for (int i = 0; i <= 3; i++) {
						if (i == 3) {
							cout << "您的次数已用尽。";
							back_menu(3);
							break;
						}
						cout << "请再次输入您转账的目标银行卡号，输入0返回菜单：";
						cin >> trans_id_temp_check;
						if (trans_id_temp_check == "0") {
							back_menu(1);
							break;
						} else if (trans_id_temp_check != trans_id_temp && i < 2) {
							cout << endl << "两次输入卡号不一致。您还有" << 2 - i << "次机会。";
						} else if (trans_id_temp_check == trans_id_temp) {
							is_passed = true;
							break;
						}

					}
				}

				if (is_passed) {
					long long int exc = 0;
					for (int k = 0; k <= 3; k++) {
						if (k == 3) {
							cout << endl << "您的次数已经用尽。";
							back_menu(3);
							break;
						}
						cout << endl << endl << "请输入您要转账的金额，输入0返回菜单：";
						cin >> exc;
						if (exc > 1000000 && exc <= cus.getbal()) {
							cout << endl << "转账数额过大，请到本行柜台操作！";
							sleep_s(1);
							back_menu(2);
							break;
						} else if (exc > cus.getbal()) {
							cout << endl << "您的余额不足！您的余额仅剩" << cus.getbal() << "元。您还有" << 2 - k << "次机会。";
						} else if (exc > 0 && exc <= cus.getbal()) {//此行条件与前文重复为了安全考虑
							CX cus2(trans_id_temp_check);
							cus2.load_account();
							cus2.chg_bal(cus2.getbal() + exc);
							cus.chg_bal(cus.getbal() - exc);
							cus.save();
							cus2.save();
							cout << endl << "取款成功！您本次转账" << exc << "元。" ;
							back_menu(3);
							break;
						} else if (exc == 0) {
							back_menu(1);
							break;
						}
					}

				}
				break;
			}
			case 5:
				cus.chg_pwd();
				back_menu(3);
				break;



		}
	}




}







