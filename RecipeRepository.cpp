#include "RecipeRepository.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// Khởi tạo đường dẫn file
RecipeRepository::RecipeRepository(string path) : filePath(path) {}

// Đọc toàn bộ dữ liệu từ file recipes.txt (Fetch All)
void RecipeRepository::fetchAll(vector<RecipeEntity>& recipes) {
    auto safeStoi = [](const string& s, int def = 0) {
        try { return s.empty() ? def : stoi(s); }
        catch (...) { return def; }
    };
    auto safeStof = [](const string& s, float def = 0.0f) {
        try { return s.empty() ? def : stof(s); }
        catch (...) { return def; }
    };

    recipes.clear();
    ifstream file(filePath);
    string line;

    if (!file.is_open()) {
        cout << "Loi: Khong the mo file " << filePath << endl;
        return;
    }

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string id, name, cat, ing, inst, desc, img, time, diff, views, rate, auth;

        // Tách dữ liệu bằng dấu | tương ứng cấu trúc file đã tạo
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, cat, '|');
        getline(ss, ing, '|');
        getline(ss, inst, '|');
        getline(ss, time, '|');
        getline(ss, diff, '|');
        getline(ss, views, '|');
        getline(ss, rate, '|');
        getline(ss, auth, '|');

        RecipeEntity r;
        r.id = safeStoi(id);
        r.name = name;
        r.category = cat;
        r.ingredients = ing;
        r.instructions = inst;
        r.cookingTime = safeStoi(time);
        r.difficulty = diff;
        r.views = safeStoi(views);
        r.averageRating = safeStof(rate);
        r.authorID = safeStoi(auth);

        recipes.push_back(r);
    }
    file.close();
}

// Lưu một công thức mới vào cuối file (Post Recipe)
bool RecipeRepository::save(const RecipeEntity& r) {
    ofstream file(filePath, ios::app);
    if (file.is_open()) {
        file << r.id << "|" << r.name << "|" << r.category << "|"
            << r.ingredients << "|" << r.instructions << "|"
            << r.cookingTime << "|" << r.difficulty << "|"
            << r.views << "|" << r.averageRating << "|" << r.authorID << "\n";
        file.close();
        return true;
    }
    return false;
}

// Ghi đè lại toàn bộ file sau khi Update hoặc Delete (Commit)
void RecipeRepository::commit(const vector<RecipeEntity>& recipes) {
    ofstream file(filePath, ios::trunc); // Xóa hết nội dung cũ để ghi mới
    if (file.is_open()) {
        for (const auto& r : recipes) {
            file << r.id << "|" << r.name << "|" << r.category << "|"
                << r.ingredients << "|" << r.instructions << "|"
                << r.cookingTime << "|" << r.difficulty << "|"
                << r.views << "|" << r.averageRating << "|" << r.authorID << "\n";
        }
        file.close();
    }
}

// Tìm công thức theo ID
RecipeEntity* RecipeRepository::findById(vector<RecipeEntity>& recipes, int id) {
    for (auto& r : recipes) {
        if (r.id == id) return &r;
    }
    return nullptr;
}

// Cập nhật công thức đã tồn tại trong danh sách và commit ra file
bool RecipeRepository::update(const RecipeEntity& recipe, vector<RecipeEntity>& recipes) {
    for (auto& r : recipes) {
        if (r.id == recipe.id) {
            r = recipe;
            commit(recipes);
            return true;
        }
    }
    return false;
}

// Xóa công thức theo ID trong danh sách và commit ra file
bool RecipeRepository::remove(int recipeId, vector<RecipeEntity>& recipes) {
    auto it = std::remove_if(recipes.begin(), recipes.end(),
        [recipeId](const RecipeEntity& r) { return r.id == recipeId; });

    if (it == recipes.end()) return false;
    recipes.erase(it, recipes.end());
    commit(recipes);
    return true;
}