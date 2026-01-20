#pragma once
#include <string>

struct AccountEntity {
    // Thuộc tính từ lớp Account trong sơ đồ 
    std::string username;
    std::string password;
    std::string email;
    bool status; // true: hoạt động, false: bị khóa 

    // Thuộc tính bổ sung cho Member/Admin để định danh 
    int id;             // Tương ứng với memberID trong sơ đồ
    std::string role;   // Phân loại: "Admin" hoặc "Member" [cite: 408]
    std::string joinDate; // Ngày tham gia hệ thống

    // Constructor mặc định
    AccountEntity() : id(0), status(true) {}

    // Constructor đầy đủ để nạp dữ liệu từ file
    AccountEntity(int _id, std::string _user, std::string _pass, std::string _email, std::string _role, std::string _date, bool _status)
        : id(_id), username(_user), password(_pass), email(_email), role(_role), joinDate(_date), status(_status) {
    }
};