#include "RecipeUI.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

// Dọn dẹp màn hình Console
void RecipeUI::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Hiển thị Menu dựa trên vai trò (Mục I đặc tả)
void RecipeUI::displayMenu(string role) {
    cout << "\n===== WEBSITE CHIA SE CONG THUC NAU AN =====" << endl;
    cout << "Chao mung ban (" << role << ")" << endl;
    cout << "1. Xem danh sach cong thuc" << endl;
    cout << "2. Tim kiem cong thuc" << endl;
    cout << "3. Loc theo danh muc" << endl;

    if (role == "Guest") {
        cout << "4. Dang nhap" << endl;
        cout << "5. Dang ky" << endl;
    }
    else if (role == "Member") {
        cout << "4. Dang cong thuc moi" << endl;
        cout << "5. Quan ly cong thuc cua toi" << endl;
        cout << "6. Dang xuat" << endl;
    }
    else if (role == "Admin") {
        cout << "4. Quan ly nguoi dung" << endl;
        cout << "5. Quan ly danh muc" << endl;
        cout << "6. Dang xuat" << endl;
    }
    cout << "0. Thoat chuong trinh" << endl;
    cout << "============================================" << endl;
    cout << "Lua chon cua ban: ";
}

// Hiển thị danh sách tóm tắt (Mục 1.2.1)
void RecipeUI::showRecipeList(const vector<RecipeEntity>& recipes) {
    cout << "\n" << left << setw(5) << "ID" << setw(25) << "Ten mon" << setw(15) << "Danh muc" << setw(10) << "Rating" << "Luot xem" << endl;
    cout << string(65, '-') << endl;
    for (const auto& r : recipes) {
        cout << left << setw(5) << r.id
            << setw(25) << r.name
            << setw(15) << r.category
            << setw(10) << fixed << setprecision(1) << r.averageRating
            << r.views << endl;
    }
}

// Hiển thị chi tiết công thức (Mục 1.2.2)
void RecipeUI::showRecipeDetail(const RecipeEntity& r, const vector<CommentEntity>& comments) {
    clearScreen();
    cout << "===== CHI TIET CONG THUC =====" << endl;
    cout << "Ten mon: " << r.name << endl;
    cout << "Danh muc: " << r.category << " | Do kho: " << r.difficulty << endl;
    cout << "Thoi gian nau: " << r.cookingTime << " phut" << endl;
    cout << "Luot xem: " << r.views << " | Diem: " << fixed << setprecision(1) << r.averageRating << endl;
    cout << "------------------------------" << endl;
    cout << "[NGUYEN LIEU]:\n" << r.ingredients << endl;
    cout << "\n[HUONG DAN]:\n" << r.instructions << endl;
    cout << "------------------------------" << endl;

    cout << "[BINH LUAN]:" << endl;
    bool hasComment = false;
    for (const auto& c : comments) {
        if (c.recipeID == r.id) {
            cout << "- User ID " << c.userID << " (" << c.createdAt << "): " << c.content << endl;
            hasComment = true;
        }
    }
    if (!hasComment) cout << "(Chua có binh luan nao)" << endl;
}

// Nhận lựa chọn từ bàn phím
int RecipeUI::getChoice() {
    int choice;
    while (!(cin >> choice)) {
        if (cin.eof()) {
            // Không có input (ví dụ chạy không tương tác) -> thoát an toàn
            return 0;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Loi! Vui long nhap so: ";
    }
    return choice;
}

void RecipeUI::showMessage(string message) {
    cout << "\n>>> " << message << " <<<" << endl;
}

string RecipeUI::inputSearchKeyword() {
    string kw;
    cout << "Nhap tu khoa tim kiem: ";
    cin.ignore();
    getline(cin, kw);
    return kw;
}

// Thành viên nhập điểm và bình luận
void RecipeUI::inputCommentAndRating(int& score, string& content) {
    cout << "Nhap diem (1-5): ";
    while (!(cin >> score) || score < 1 || score > 5) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Diem khong hop le. Vui long nhap lai (1-5): ";
    }

    cout << "Nhap noi dung binh luan: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, content);
}

// Admin chọn hành động quản lý (generic)
int RecipeUI::inputManageAction(string targetName) {
    cout << "\n--- QUAN LY " << targetName << " ---" << endl;
    cout << "1. Them" << endl;
    cout << "2. Sua" << endl;
    cout << "3. Xoa" << endl;
    cout << "0. Quay lai" << endl;
    cout << "Lua chon cua ban: ";
    return getChoice();
}