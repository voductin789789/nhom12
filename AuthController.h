#pragma once
#include <vector>
#include <string>
#include "AccountEntity.h"

class AuthController {
private:
    std::string userFilePath;
    AccountEntity* currentUser; // Lưu trữ tài khoản đang đăng nhập hệ thống 

public:
    // Khởi tạo với đường dẫn file dữ liệu người dùng
    AuthController(std::string path);

    // --- Chức năng chính theo đặc tả ---

    // Load danh sách tài khoản từ file vào vector [cite: 33, 182]
    void loadAccounts(std::vector<AccountEntity>& accounts);

    // Xử lý đăng nhập (Use-case Login) [cite: 152, 159]
    // Kiểm tra username/email và password [cite: 157]
    bool login(std::string identifier, std::string password, std::vector<AccountEntity>& accounts);

    // Đăng xuất khỏi hệ thống (Use-case Logout) [cite: 342, 347]
    void logout();

    // Kiểm tra trạng thái đăng nhập
    bool isLoggedIn() const;

    // Lấy vai trò (role) của người dùng hiện tại (Guest, Member, Admin) 
    std::string getCurrentRole() const;

    // Lấy thông tin tài khoản đang đăng nhập
    AccountEntity* getCurrentUser() const;

    // --- Chức năng bổ sung theo sơ đồ lớp ---

    // Kiểm tra email hợp lệ (validateEmail) 
    bool validateEmail(std::string email);

    // Quên mật khẩu (Use-case Reset Password) [cite: 171, 318, 327]
    bool resetPassword(std::string email, std::vector<AccountEntity>& accounts);
};