#include "Database.h"
#include "File.h"
#include <iostream>

namespace Database {
    bool checkError(int rc, sqlite3 *db, const std::string &message) {
        if (rc != SQLITE_OK && rc != SQLITE_DONE && rc != SQLITE_ROW) {
            std::cerr << "Error: " << message << " -> " << sqlite3_errmsg(db) << std::endl;
            return false;
        }
        return true;
    }

    bool Database::Init() {
        std::string str;

        this->m_dbPath = "Data/Game.db";
        SetResult(sqlite3_open(this->m_dbPath.c_str(), &this->m_db));

        if (GetResult() != SQLITE_OK) {
            std::cerr << "Failed to open database: " << sqlite3_errmsg(this->m_db) << std::endl;
            return false;
        }
        std::cout << "Database opened successfully." << std::endl;

        if (!Engine::ReadTextFile("Data/DB_Table.txt", str)) {
            std::cerr << "Failed to find DB creation file\n";
            return false;
        }

        this->m_result = sqlite3_exec(this->m_db, str.c_str(), nullptr, nullptr, &this->m_errorMessage);

        if (this->m_result != SQLITE_OK) {
            std::cerr << "SQL error during initialization: " << this->m_errorMessage << std::endl;
            sqlite3_free(this->m_errorMessage); // Free allocated memory for error message
        }

        std::cout << "Database schema initialized successfully." << std::endl;

        return true;
    }

    void Database::Destroy() {
        sqlite3_close(this->m_db);
    }

    void Database::InsertPlayer(std::string cmd, AddParams params) {
        sqlite3_stmt *stmt;

        this->m_result = sqlite3_prepare_v2(this->m_db, cmd.c_str(), -1, &stmt, nullptr);

        if (!checkError(this->m_result, this->m_db, "Failed to insert Item")) {
            return;
        }

        sqlite3_bind_int(stmt, 1, params.id);
        sqlite3_bind_text(stmt, 2, params.name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, params.json_values.c_str(), -1, SQLITE_STATIC);

        checkError(sqlite3_step(stmt), this->m_db, "Failed to step insert");

        sqlite3_finalize(stmt); // Clean up statement
    }

    void Database::InsertScore(std::string cmd, AddParams params) {
        sqlite3_stmt *stmt;

        this->m_result = sqlite3_prepare_v2(this->m_db, cmd.c_str(), -1, &stmt, nullptr);

        if (!checkError(this->m_result, this->m_db, "Failed to insert Item")) {
            return;
        }

        sqlite3_bind_text(stmt, 1, params.name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, params.score);

        checkError(sqlite3_step(stmt), this->m_db, "Failed to step insert");

        sqlite3_finalize(stmt); // Clean up statement
    }

    void Database::ToJSON(AddParams &params) {
        nlohmann::json j;
        j["tag"] = params.tag;
        j["score"] = params.score;
        params.json_values = j.dump();
    }

    void Database::Update(std::string cmd) {
        sqlite3_stmt *stmt;

        this->m_result = sqlite3_prepare_v2(this->m_db, cmd.c_str(), -1, &stmt, nullptr);

        if (!checkError(this->m_result, this->m_db, "Failed to update Item")) {
            return;
        }

        sqlite3_finalize(stmt); // Clean up statement
    }

    void Database::ReadAllData(std::string cmd) {
        sqlite3_stmt *stmt;

        this->m_result = sqlite3_prepare_v2(this->m_db, cmd.c_str(), -1, &stmt, nullptr);

        if (!checkError(this->m_result, this->m_db, "Failed to get Items")) {
            return;
        }

        sqlite3_finalize(stmt); // Clean up statement
    }

    void Database::GetSingleEntry(std::string cmd) {
        sqlite3_stmt *stmt;

        this->m_result = sqlite3_prepare_v2(this->m_db, cmd.c_str(), -1, &stmt, nullptr);

        if (!checkError(this->m_result, this->m_db, "Failed to get Entry")) {
            return;
        }

        sqlite3_finalize(stmt); // Clean up statement
    }

} // namespace Database
