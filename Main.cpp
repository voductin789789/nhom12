#include <iostream>
#include <vector>
#include <string>
#include "AccountEntity.h"
#include "RecipeEntity.h"
#include "CommentEntity.h"
#include "RatingEntity.h"
#include "AuthController.h"
#include "RecipeController.h"
#include "RecipeRepository.h"
#include "InteractionController.h"
#include "AdminController.h"
#include "RecipeUI.h"

using namespace std;

int main() {
    // 1. Khởi tạo các đường dẫn file
    string userFile = "users.txt";
    string recipeFile = "recipes.txt";
    string commentFile = "comments.txt";
    string ratingFile = "ratings.txt";

    // 2. Khởi tạo các đối tượng điều khiển
    AuthController auth(userFile);
    RecipeRepository repo(recipeFile);
    RecipeController recipeCtrl;
    InteractionController interCtrl(commentFile, ratingFile);
    AdminController adminCtrl;
    RecipeUI ui;

    // 3. Khai báo danh sách dữ liệu trong bộ nhớ
    vector<AccountEntity> accounts;
    vector<RecipeEntity> recipes;
    vector<CommentEntity> comments;
    vector<RatingEntity> ratings;

    // 4. Nạp dữ liệu ban đầu
    auth.loadAccounts(accounts);
    repo.fetchAll(recipes);
    interCtrl.loadComments(comments);
    interCtrl.loadRatings(ratings);

    bool running = true;
    while (running) {
        ui.clearScreen();
        string role = auth.getCurrentRole();
        ui.displayMenu(role);

        int choice = ui.getChoice();

        switch (choice) {
        case 1: { // Xem danh sách công thức
            ui.showRecipeList(recipes);
            cout << "\nNhap ID de xem chi tiet (0 de quay lai): ";
            int id = ui.getChoice();
            if (id > 0) {
                RecipeEntity* r = repo.findById(recipes, id);
                if (r) {
                    r->views++; // Tang luot xem (Muc 1.2.1)
                    ui.showRecipeDetail(*r, comments);

                    // Neu la Member, cho phep Binh luan/Danh gia
                    if (role == "Member") {
                        cout << "\n1. Binh luan & Danh gia | 0. Thoat: ";
                        if (ui.getChoice() == 1) {
                            int score; string content;
                            ui.inputCommentAndRating(score, content);
                            // Logic them vao file (Rut gon)
                            ui.showMessage("Cam on ban da danh gia!");
                        }
                    }
                }
                else ui.showMessage("Khong tim thay ID!");
            }
            break;
        }
        case 2: { // Tim kiem
            string kw = ui.inputSearchKeyword();
            auto results = recipeCtrl.searchByKeyword(recipes, kw);
            ui.showRecipeList(results);
            system("pause");
            break;
        }
        case 4: { // Login hoặc Chức năng riêng
            if (role == "Guest") {
                string u, p;
                cout << "Username/Email: "; cin >> u;
                cout << "Password: "; cin >> p;
                if (auth.login(u, p, accounts)) ui.showMessage("Dang nhap thanh cong!");
                else ui.showMessage("Sai thong tin hoac tai khoan bi khoa!");
            }
            else if (role == "Admin") {
                adminCtrl.manageUsers(accounts);
            }
            break;
        }
        case 6: { // Logout
            if (role != "Guest") auth.logout();
            break;
        }
        case 0:
            running = false;
            break;
        default:
            ui.showMessage("Lua chon khong hop le!");
        }
        if (choice != 0) {
            cout << "\nNhan phim bat ky de tiep tuc...";
            system("pause > nul");
        }
    }

    // Luu lai du lieu truoc khi thoat
    repo.commit(recipes);
    return 0;
}