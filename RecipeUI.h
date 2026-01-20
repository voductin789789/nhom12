#pragma once
#include <vector>
#include <string>
#include "RecipeEntity.h"
#include "CommentEntity.h"

class RecipeUI {
public:
    // --- Hiển thị Menu (Mục I đặc tả) ---

    // Hiển thị menu chính dựa trên vai trò người dùng (Guest, Member, Admin)
    void displayMenu(std::string role);

    // --- Chức năng Xem & Tìm kiếm (Mục 1.2 đặc tả) ---

    // Hiển thị danh sách tóm tắt các công thức (ID, Tên, Đánh giá, Lượt xem)
    void showRecipeList(const std::vector<RecipeEntity>& recipes);

    // Hiển thị chi tiết một công thức: Nguyên liệu, các bước, thời gian... (Mục 1.2.2)
    void showRecipeDetail(const RecipeEntity& recipe, const std::vector<CommentEntity>& comments);

    // --- Chức năng Tương tác & Quản lý (Mục 3, 4, 9, 12 đặc tả) ---

    // Giao diện để người dùng nhập từ khóa tìm kiếm
    std::string inputSearchKeyword();

    // Giao diện để Thành viên nhập nội dung bình luận và điểm đánh giá
    void inputCommentAndRating(int& score, std::string& content);

    // Giao diện để Admin quản lý người dùng hoặc xóa công thức
    int inputManageAction(std::string targetName);

    // --- Tiện ích giao diện ---

    // Lấy lựa chọn số từ người dùng
    int getChoice();

    // Hiển thị các thông báo lỗi hoặc thành công (Mục 13.2.2)
    void showMessage(std::string message);

    // Dọn dẹp màn hình Console
    void clearScreen();
};