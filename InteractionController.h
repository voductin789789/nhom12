#pragma once
#include <string>
#include <vector>

#include "CommentEntity.h"
#include "RatingEntity.h"

class InteractionController {
private:
    std::string commentFilePath;
    std::string ratingFilePath;

public:
    // Khởi tạo với đường dẫn file dữ liệu
    InteractionController(std::string commentPath, std::string ratingPath);

    // --- Bình luận ---
    void loadComments(std::vector<CommentEntity>& comments);
    bool addComment(const CommentEntity& comment);

    // --- Đánh giá ---
    void loadRatings(std::vector<RatingEntity>& ratings);
    bool addRating(const RatingEntity& rating);
    float calculateAverageRating(int recipeId, const std::vector<RatingEntity>& ratings);
};

