#pragma once
#include <string>
#include <iostream>

class ServerObject {
	private:
		int num_;
		bool truthy_;
		std::string myStr_;
	public:
		ServerObject(int num, bool truthy, std::string myStr) {
			num_ = num;
			truthy_ = truthy;
			myStr_ = myStr;
		}

		void setNum(int a) {
			num_ = a;
		}
		void setTruthy(bool b) {
			truthy_ = b;
		}
		void setStr(std::string newStr) {
			myStr_ = newStr;
		}

		const int getNum() {
			return num_;
		}

		const bool getTruthy() {
			return truthy_;
		}

		const std::string getMyStr() {
			return myStr_;
		}

		void foo() {
			std::cout << "I am called from the client." << std::endl;
		}

		std::string serialize_attributes() {
			std::string attributes = "";
			try {
				attributes += "NUM:" + std::to_string(getNum()) + "|TRUTHY:" + std::to_string(getTruthy()) + "|MYSTR:" + getMyStr();
			}
			catch (std::exception& e) {
				attributes = "ERROR";
			}
			return attributes;
		}
};