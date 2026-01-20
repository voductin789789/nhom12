#pragma once
#include <string>
#include <vector>

struct RecipeEntity {
    // --- Các thuộc tính định danh và phân loại ---
    int id;                 // Mã định danh công thức
    std::string name;       // Tên món ăn (title) 
    std::string category;   // Danh mục: Món chính, món chay, Á, Âu... 

    // --- Nội dung chi tiết công thức (Mục 1.2.2 đặc tả) ---
    std::string ingredients;    // Danh sách nguyên liệu 
    std::string instructions;   // Các bước thực hiện chi tiết 
    std::string description;    // Ghi chú hoặc mô tả ngắn 
    std::string imagePath;      // Đường dẫn hình ảnh minh họa 

    // --- Thông số kỹ thuật và đánh giá ---
    int cookingTime;        // Thời gian nấu (phút) 
    std::string difficulty; // Mức độ khó: Dễ, Trung bình, Khó 
    int views;              // Số lượt xem 
    float averageRating;    // Điểm đánh giá trung bình 
    int authorID;           // ID của thành viên đăng bài

    // --- Constructor ---
    RecipeEntity() : id(0), cookingTime(0), views(0), averageRating(0.0f), authorID(0) {}

    RecipeEntity(int _id, std::string _name, std::string _cat, std::string _ing,
        std::string _inst, int _time, std::string _diff)
        : id(_id), name(_name), category(_cat), ingredients(_ing),
        instructions(_inst), cookingTime(_time), difficulty(_diff),
        views(0), averageRating(0.0f) {
    }
};