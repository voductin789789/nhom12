#include "AuthController.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>

using namespace std;

// Constructor: Khởi tạo đường dẫn file và đặt trạng thái chưa đăng nhập
AuthController::AuthController(string path) : userFilePath(path), currentUser(nullptr) {}

// Nạp danh sách tài khoản từ file users.txt vào vector
void AuthController::loadAccounts(vector<AccountEntity>& accounts) {
    auto safeStoi = [](const string& s, int def = 0) {
        try { return s.empty() ? def : stoi(s); }
        catch (...) { return def; }
    };

    accounts.clear();
    ifstream file(userFilePath);
    string line;

    if (!file.is_open()) {
        cout << "Loi: Khong the mo file " << userFilePath << endl;
        return;
    }

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string idStr, user, pass, mail, role, date, statusStr;

        // Tách dữ liệu bằng dấu |
        getline(ss, idStr, '|');
        getline(ss, user, '|');
        getline(ss, pass, '|');
        getline(ss, mail, '|');
        getline(ss, role, '|');
        getline(ss, date, '|');
        getline(ss, statusStr, '|');

        int id = safeStoi(idStr);
        bool status = (statusStr == "1");

        // Đẩy vào danh sách
        accounts.push_back(AccountEntity(id, user, pass, mail, role, date, status));
    }
    file.close();
}

// Xử lý logic đăng nhập (Mục 13.1 đặc tả)
bool AuthController::login(string identifier, string password, vector<AccountEntity>& accounts) {
    for (auto& acc : accounts) {
        // Kiểm tra username hoặc email và mật khẩu
        if ((acc.username == identifier || acc.email == identifier) && acc.password == password) {
            if (!acc.status) {
                cout << "Tai khoan cua ban dang bi khoa!" << endl;
                return false;
            }
            currentUser = &acc;
            return true;
        }
    }
    return false;
}

// Đăng xuất (Mục 14 đặc tả)
void AuthController::logout() {
    currentUser = nullptr;
    cout << "Da dang xuat khoi he thong." << endl;
}

// Kiểm tra trạng thái đã đăng nhập chưa
bool AuthController::isLoggedIn() const {
    return currentUser != nullptr;
}

// Lấy vai trò của người dùng hiện tại
string AuthController::getCurrentRole() const {
    if (currentUser == nullptr) return "Guest";
    return currentUser->role;
}

// Lấy toàn bộ thông tin tài khoản đang đăng nhập
AccountEntity* AuthController::getCurrentUser() const {
    return currentUser;
}

// Kiểm tra email hợp lệ (đơn giản, đủ dùng cho đồ án)
bool AuthController::validateEmail(string email) {
    static const regex pattern(R"(^[A-Za-z0-9._%+\-]+@[A-Za-z0-9.\-]+\.[A-Za-z]{2,}$)");
    return regex_match(email, pattern);
}

// Quên mật khẩu: đặt lại mật khẩu cho email (demo: đặt "123456" và commit về file)
bool AuthController::resetPassword(string email, vector<AccountEntity>& accounts) {
    if (!validateEmail(email)) return false;

    bool found = false;
    for (auto& acc : accounts) {
        if (acc.email == email) {
            acc.password = "123456";
            found = true;
            break;
        }
    }
    if (!found) return false;

    ofstream file(userFilePath, ios::trunc);
    if (!file.is_open()) return false;

    for (const auto& acc : accounts) {
        file << acc.id << "|" << acc.username << "|" << acc.password << "|"
            << acc.email << "|" << acc.role << "|" << acc.joinDate << "|"
            << (acc.status ? "1" : "0") << "\n";
    }
    return true;
}