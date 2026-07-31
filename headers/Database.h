#pragma once
// #include "json.h"
#include "nlohmann/json.hpp"
#include "sqlite3.h"
#include <string>
#include <vector>

namespace Database {

    struct AddParams {
        static AddParams &GetParams() {
            static AddParams params;
            return params;
        }

        void SetParams(int id, int score, int lives, int x, int y, std::string name, std::string tag,
                       std::string json) {
            m_id = id;
            m_score = score;
            m_lives = lives;
            m_pos_x = x;
            m_pos_y = y;
            m_name = name;
            m_tag = tag;
            m_json_values = json;
        }

        int         m_id;
        int         m_score;
        int         m_lives;
        int         m_pos_x;
        int         m_pos_y;
        std::string m_name;
        std::string m_tag;
        std::string m_json_values;

      private:
        AddParams() = default;
    };

    class Database {
      public:
        static Database &GetDatabase() {
            static Database Database;
            return Database;
        }

        bool           Init();
        void           Destroy();

        const sqlite3 *GetDB() const {
            return m_db;
        }

        const void SetDB(sqlite3 *db) {
            m_db = db;
        }

        const char *GetErrorMessage() const {
            return m_errorMessage;
        }

        const void SetErrorMessage(char *msg) {
            m_errorMessage = msg;
        }

        const int GetResult() const {
            return m_result;
        }

        const void SetResult(const int &result) {
            m_result = result;
        }

        // Database calls
      public:
        void                     InsertPlayer(const AddParams params);
        void                     InsertScore(const AddParams params);
        void                     Update(const int score);
        std::vector<std::string> ReadAllHighScores(const int limit);
        std::string              GetSingleScore(const std::string search);
        std::string              GetSinglePlayer(const std::string search);

        void        ToJSON(AddParams &params);

      private:
        Database() = default;

      private:
        sqlite3    *m_db = nullptr;
        char       *m_errorMessage = nullptr;
        std::string m_dbPath;
        int         m_result = 0;
        std::string m_cmd;
    };
} // namespace Database
