#pragma once
#include <vector>
#include <string>
#include "RecipeEntity.h"

class RecipeRepository {
private:
    std::string filePath; // Đường dẫn tới file recipes.txt

public:
    // Khởi tạo với đường dẫn file
    RecipeRepository(std::string path);

    // --- Các chức năng xử lý dữ liệu (Mục 1.2 đặc tả) ---

    // Đọc tất cả công thức từ file vào danh sách (fetchAll)
    void fetchAll(std::vector<RecipeEntity>& recipes);

    // Lưu một công thức mới vào file (Phục vụ Use-case Post Recipe)
    bool save(const RecipeEntity& recipe);

    // Cập nhật công thức đã tồn tại (Phục vụ Use-case Update Recipe)
    bool update(const RecipeEntity& recipe, std::vector<RecipeEntity>& recipes);

    // Xóa công thức khỏi file (Phục vụ Use-case Delete Recipe)
    bool remove(int recipeId, std::vector<RecipeEntity>& recipes);

    // --- Các chức năng tìm kiếm nhanh ---

    // Tìm kiếm một công thức cụ thể theo ID
    RecipeEntity* findById(std::vector<RecipeEntity>& recipes, int id);

    // Đồng bộ lại toàn bộ danh sách vào file sau khi sửa/xóa
    void commit(const std::vector<RecipeEntity>& recipes);
};