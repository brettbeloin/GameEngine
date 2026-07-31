#include "Database.h"
#include "Engine.h"
#include "File.h"
#include "Text.h"
#include <iostream>
#include <string>

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
        if (checkError(sqlite3_close(m_db), m_db, "Failed to Destroy database")) {
            return;
        }
    }

    void Database::InsertPlayer(const AddParams params) {
        sqlite3_stmt *stmt;

        m_cmd = "INSERT INTO PLAYER (id, player_name, player_data) VALUES (?,?,?) ON CONFLICT(id) DO NOTHING;";

        m_result = sqlite3_prepare_v2(m_db, m_cmd.c_str(), -1, &stmt, nullptr);

        if (!checkError(m_result, m_db, "Failed to insert Player")) {
            return;
        }

        sqlite3_bind_int(stmt, 1, params.m_id);
        sqlite3_bind_text(stmt, 2, params.m_name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, params.m_json_values.c_str(), -1, SQLITE_STATIC);

        checkError(sqlite3_step(stmt), m_db, "Failed to step insert");

        sqlite3_finalize(stmt); // Clean up statement
    }

    void Database::InsertScore(const AddParams params) {
        sqlite3_stmt *stmt;
        m_cmd = "INSERT INTO HIGH_SCORE (player_name, score) VALUES (?,?);";

        m_result = sqlite3_prepare_v2(m_db, m_cmd.c_str(), -1, &stmt, nullptr);

        if (!checkError(m_result, m_db, "Failed to insert Score")) {
            return;
        }

        sqlite3_bind_text(stmt, 1, params.m_name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, params.m_score);

        checkError(sqlite3_step(stmt), m_db, "Failed to step insert");

        sqlite3_finalize(stmt); // Clean up statement
    }

    void Database::ToJSON(AddParams &params) {
        nlohmann::json j;
        j["tag"] = params.m_tag;
        j["score"] = params.m_score;
        params.m_json_values = j.dump();
    }

    void Database::Update(const int score) {
        sqlite3_stmt  *stmt;
        nlohmann::json j;

        AddParams::GetParams().m_score = score;
        ToJSON(AddParams::GetParams());

        m_cmd = "UPDATE PLAYER SET player_data = ? WHERE id = ?";
        m_result = sqlite3_prepare_v2(m_db, m_cmd.c_str(), -1, &stmt, nullptr);

        if (!checkError(m_result, m_db, "Failed to update Item")) {
            return;
        }

        sqlite3_bind_text(stmt, 1, AddParams::GetParams().m_json_values.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, AddParams::GetParams().m_id);

        checkError(sqlite3_step(stmt), m_db, "Unable to update Player score");

        sqlite3_finalize(stmt); // Clean up statement
    }

    std::string Database::ReadAllHighScores(const int limit) {
        std::string   queryResult;
        sqlite3_stmt *stmt;

        m_cmd = "SELECT player_name, score FROM HIGH_SCORE LIMIT " + std::to_string(limit) + ";";

        m_result = sqlite3_prepare_v2(m_db, m_cmd.c_str(), -1, &stmt, nullptr);

        if (!checkError(m_result, m_db, "Failed to get Items")) {
            return "bad data";
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char *temp = sqlite3_column_text(stmt, 0);
            int                  score = sqlite3_column_int(stmt, 1);

            queryResult =
                "Player: " + std::string(reinterpret_cast<const char *>(temp)) + " : Score " + std::to_string(score);
        }

        sqlite3_finalize(stmt); // Clean up statement

        return queryResult;
    }

    std::string Database::GetSingleScore(const std::string search) {
        std::string   queryResult = "";
        sqlite3_stmt *stmt;

        m_cmd = "SELECT player_name, score FROM HIGH_SCORE WHERE player_name = ?;";
        m_result = sqlite3_prepare_v2(m_db, m_cmd.c_str(), -1, &stmt, nullptr);

        if (!checkError(m_result, m_db, "Failed to get " + search + "'s score")) {
            return "bad data";
        }

        int bind_rc = sqlite3_bind_text(stmt, 1, search.c_str(), -1, SQLITE_STATIC);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char *temp = sqlite3_column_text(stmt, 0);
            int                  score = sqlite3_column_int(stmt, 1);

            queryResult =
                "Player: " + std::string(reinterpret_cast<const char *>(temp)) + " : Score " + std::to_string(score);
        }

        sqlite3_finalize(stmt); // Clean up statement

        return queryResult;
    }

    std::string Database::GetSinglePlayer(const std::string search) {
        std::string   queryResult = "";
        sqlite3_stmt *stmt;

        m_cmd = "SELECT player_data FROM PLAYER WHERE player_name = ?;";
        m_result = sqlite3_prepare_v2(m_db, m_cmd.c_str(), -1, &stmt, nullptr);

        if (!checkError(m_result, m_db, "Failed to get " + search)) {
            return "No Player";
        }

        sqlite3_bind_text(stmt, 1, search.c_str(), -1, SQLITE_STATIC);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char *obj = sqlite3_column_text(stmt, 0);

            queryResult = std::string(reinterpret_cast<const char *>(obj));
        }

        sqlite3_finalize(stmt); // Clean up statement

        return queryResult;
    }

} // namespace Database
