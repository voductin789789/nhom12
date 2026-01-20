#include "RecipeController.h"
#include <algorithm>
#include <iostream>

using namespace std;

// --- Chức năng tìm kiếm (Mục 1.2.1 đặc tả) ---
// Tìm theo tên món ăn hoặc nguyên liệu
vector<RecipeEntity> RecipeController::searchByKeyword(const vector<RecipeEntity>& recipes, string keyword) {
    vector<RecipeEntity> result;
    // Chuyển từ khóa về chữ thường để tìm kiếm không phân biệt hoa thường (tùy chọn)
    for (const auto& r : recipes) {
        if (r.name.find(keyword) != string::npos || r.ingredients.find(keyword) != string::npos) {
            result.push_back(r);
        }
    }
    return result;
}

// --- Chức năng lọc theo danh mục (Mục 2 đặc tả) ---
vector<RecipeEntity> RecipeController::filterByCategory(const vector<RecipeEntity>& recipes, string category) {
    vector<RecipeEntity> result;
    for (const auto& r : recipes) {
        if (r.category == category) {
            result.push_back(r);
        }
    }
    return result;
}

// --- Các chức năng sắp xếp ---

// Sắp xếp theo mức độ yêu thích (Rating trung bình giảm dần)
void RecipeController::sortByRating(vector<RecipeEntity>& recipes) {
    sort(recipes.begin(), recipes.end(), [](const RecipeEntity& a, const RecipeEntity& b) {
        return a.averageRating > b.averageRating;
        });
}

// Sắp xếp theo số lượt xem (Views giảm dần)
void RecipeController::sortByViews(vector<RecipeEntity>& recipes) {
    sort(recipes.begin(), recipes.end(), [](const RecipeEntity& a, const RecipeEntity& b) {
        return a.views > b.views;
        });
}

// Sắp xếp theo ID mới nhất (tương ứng thời gian đăng)
void RecipeController::sortByLatest(vector<RecipeEntity>& recipes) {
    sort(recipes.begin(), recipes.end(), [](const RecipeEntity& a, const RecipeEntity& b) {
        return a.id > b.id;
        });
}

// --- Chức năng kiểm tra dữ liệu (Validation) ---
bool RecipeController::validateRecipe(const RecipeEntity& recipe) {
    if (recipe.name.empty() || recipe.ingredients.empty() || recipe.instructions.empty()) {
        cout << "Loi: Ten mon, nguyen lieu va huong dan khong duoc de trong!" << endl;
        return false;
    }
    if (recipe.cookingTime <= 0) {
        cout << "Loi: Thoi gian nau phai lon hon 0!" << endl;
        return false;
    }
    return true;
}