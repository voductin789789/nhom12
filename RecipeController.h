#pragma once
#include <vector>
#include <string>
#include "RecipeEntity.h"

class RecipeController {
public:
    // --- Các chức năng tìm kiếm và lọc (Mục 1.2.1 & 2 trong đặc tả) ---

    // Tìm kiếm công thức theo từ khóa (tên món hoặc nguyên liệu) 
    std::vector<RecipeEntity> searchByKeyword(const std::vector<RecipeEntity>& recipes, std::string keyword);

    // Lọc công thức theo danh mục (Món chính, Món chay, Á, Âu...) 
    std::vector<RecipeEntity> filterByCategory(const std::vector<RecipeEntity>& recipes, std::string category);

    // --- Các chức năng sắp xếp (Mục 1.2.1 trong đặc tả) ---

    // Sắp xếp theo mức độ yêu thích (Rating) 
    void sortByRating(std::vector<RecipeEntity>& recipes);

    // Sắp xếp theo số lượt xem (Views) 
    void sortByViews(std::vector<RecipeEntity>& recipes);

    // Sắp xếp theo thời gian đăng mới nhất 
    void sortByLatest(std::vector<RecipeEntity>& recipes);

    // --- Chức năng quản lý (Dành cho Member/Admin) ---

    // Kiểm tra tính hợp lệ của dữ liệu công thức trước khi đăng (Mục 4) 
    bool validateRecipe(const RecipeEntity& recipe);
};