#include "AdminController.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

void AdminController::manageUsers(std::vector<AccountEntity>& accounts) {
    cout << "\n--- DANH SACH NGUOI DUNG ---" << endl;
    cout << left << setw(5) << "ID" << setw(15) << "Username" << setw(15) << "Role" << "Trang thai" << endl;
    cout << "---------------------------------------------" << endl;

    for (const auto& acc : accounts) {
        cout << left << setw(5) << acc.id
            << setw(15) << acc.username
            << setw(15) << acc.role
            << (acc.status ? "Hoat dong" : "Bi khoa") << endl;
    }

    int choice;
    cout << "\n1. Khoa/Mo khoa tai khoan | 0. Quay lai: ";
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    if (choice == 1) {
        int id;
        cout << "Nhap ID nguoi dung: ";
        cin >> id;
        for (auto& acc : accounts) {
            if (acc.id == id) {
                acc.status = !acc.status;
                cout << "Cap nhat trang thai thanh cong!" << endl;
                return;
            }
        }
        cout << "Khong tim thay ID!" << endl;
    }
}

bool AdminController::deleteRecipe(int recipeId, std::vector<RecipeEntity>& recipes) {
    auto it = std::remove_if(recipes.begin(), recipes.end(), [recipeId](const RecipeEntity& r) {
        return r.id == recipeId;
        });

    if (it != recipes.end()) {
        recipes.erase(it, recipes.end());
        cout << "Da xoa cong thuc ID: " << recipeId << " thanh cong." << endl;
        return true;
    }
    cout << "Khong tim thay cong thuc!" << endl;
    return false;
}

void AdminController::addCategory(std::string newCat, std::vector<std::string>& categories) {
    auto it = std::find(categories.begin(), categories.end(), newCat);
    if (it == categories.end()) {
        categories.push_back(newCat);
        cout << "Da them danh muc: " << newCat << " thanh cong." << endl;
    }
    else {
        cout << "Danh muc nay da ton tai!" << endl;
    }
}