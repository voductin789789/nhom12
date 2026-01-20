#pragma once
#include <string>

struct RatingEntity {
    // Các thuộc tính dựa trên Sơ đồ lớp (Class Diagram) và Đặc tả 
    int ratingID;       // Mã định danh đánh giá
    int memberID;       // ID người dùng thực hiện đánh giá
    int recipeID;       // ID công thức được đánh giá
    int score;          // Điểm đánh giá (thường từ 1-5 sao)
    std::string reviewText; // Nội dung nhận xét đi kèm (nếu có)
    std::string createdAt;  // Ngày đánh giá

    // Constructor mặc định để tránh lỗi khi khởi tạo mảng/vector
    RatingEntity() : ratingID(0), memberID(0), recipeID(0), score(0) {}

    // Constructor đầy đủ để nạp dữ liệu từ file hoặc tạo mới nhanh
    RatingEntity(int rId, int mId, int recId, int s, std::string txt, std::string date)
        : ratingID(rId), memberID(mId), recipeID(recId), score(s), reviewText(txt), createdAt(date) {
    }
};