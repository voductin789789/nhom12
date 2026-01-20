#pragma once
#include <string>

struct CommentEntity {
    // Thuộc tính chính xác theo Sơ đồ lớp (Class Diagram)
    int commentID;      // Mã định danh bình luận 
    int userID;         // ID của người dùng viết bình luận 
    int recipeID;       // ID của công thức được bình luận 
    std::string content; // Nội dung bình luận 
    std::string createdAt; // Thời gian tạo bình luận (DateTime) 

    // Constructor mặc định
    CommentEntity() : commentID(0), userID(0), recipeID(0) {}

    // Constructor đầy đủ để khởi tạo nhanh khi nạp dữ liệu hoặc tạo mới
    CommentEntity(int cId, int uId, int rId, std::string txt, std::string date)
        : commentID(cId), userID(uId), recipeID(rId), content(txt), createdAt(date) {
    }
};