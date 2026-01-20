#pragma once
#include <string>
#include <vector>

#include "AccountEntity.h"
#include "RecipeEntity.h"

class AdminController {
public:
    // Quản lý người dùng (khóa/mở khóa)
    void manageUsers(std::vector<AccountEntity>& accounts);

    // Xóa công thức theo ID (xóa trong danh sách đang có)
    bool deleteRecipe(int recipeId, std::vector<RecipeEntity>& recipes);

    // Thêm danh mục mới (thêm vào danh sách đang có)
    void addCategory(std::string newCat, std::vector<std::string>& categories);
};

