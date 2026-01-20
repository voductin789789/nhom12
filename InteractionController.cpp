#include "InteractionController.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

// Constructor: Khởi tạo với đường dẫn file dữ liệu
InteractionController::InteractionController(string commentPath, string ratingPath)
    : commentFilePath(commentPath), ratingFilePath(ratingPath) {
}

// --- Xử lý Bình luận (Mục 3 đặc tả) ---

void InteractionController::loadComments(vector<CommentEntity>& comments) {
    auto safeStoi = [](const string& s, int def = 0) {
        try { return s.empty() ? def : stoi(s); }
        catch (...) { return def; }
    };

    comments.clear();
    ifstream file(commentFilePath);
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string cId, uId, rId, content, date;
        getline(ss, cId, '|');
        getline(ss, uId, '|');
        getline(ss, rId, '|');
        getline(ss, content, '|');
        getline(ss, date, '|');
        comments.push_back(CommentEntity(safeStoi(cId), safeStoi(uId), safeStoi(rId), content, date));
    }
    file.close();
}

bool InteractionController::addComment(const CommentEntity& comment) {
    ofstream file(commentFilePath, ios::app); // Ghi đè vào cuối file
    if (file.is_open()) {
        file << comment.commentID << "|" << comment.userID << "|"
            << comment.recipeID << "|" << comment.content << "|"
            << comment.createdAt << "\n";
        file.close();
        return true;
    }
    return false;
}

// --- Xử lý Đánh giá (Mục 3 đặc tả) ---

void InteractionController::loadRatings(vector<RatingEntity>& ratings) {
    auto safeStoi = [](const string& s, int def = 0) {
        try { return s.empty() ? def : stoi(s); }
        catch (...) { return def; }
    };

    ratings.clear();
    ifstream file(ratingFilePath);
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string rtId, mId, recId, score, txt, date;
        getline(ss, rtId, '|');
        getline(ss, mId, '|');
        getline(ss, recId, '|');
        getline(ss, score, '|');
        getline(ss, txt, '|');
        getline(ss, date, '|');
        ratings.push_back(RatingEntity(safeStoi(rtId), safeStoi(mId), safeStoi(recId), safeStoi(score), txt, date));
    }
    file.close();
}

// Tính điểm trung bình cho một món ăn để hiển thị (Mục 1.2.1)
float InteractionController::calculateAverageRating(int recipeId, const vector<RatingEntity>& ratings) {
    float sum = 0;
    int count = 0;
    for (const auto& r : ratings) {
        if (r.recipeID == recipeId) {
            sum += r.score;
            count++;
        }
    }
    return (count == 0) ? 0.0f : (sum / count);
}

bool InteractionController::addRating(const RatingEntity& rating) {
    ofstream file(ratingFilePath, ios::app);
    if (file.is_open()) {
        file << rating.ratingID << "|" << rating.memberID << "|"
            << rating.recipeID << "|" << rating.score << "|"
            << rating.reviewText << "|" << rating.createdAt << "\n";
        file.close();
        return true;
    }
    return false;
}