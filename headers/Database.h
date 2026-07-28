#pragma once
// #include "json.h"
#include "nlohmann/json.hpp"
#include "sqlite3.h"
#include <string>

namespace Database {

    struct AddParams {
        int         id;
        int         score;
        std::string name;
        std::string tag;
        std::string json_values;
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
        void InsertPlayer(std::string cmd, AddParams params);
        void InsertScore(std::string cmd, AddParams params);
        void Update(std::string cmd);
        void ReadAllData(std::string cmd);
        void GetSingleEntry(std::string cmd);

        void ToJSON(AddParams &params);

      private:
        Database() = default;

      private:
        sqlite3    *m_db = nullptr;
        char       *m_errorMessage = nullptr;
        std::string m_dbPath;
        int         m_result = 0;
    };
} // namespace Database
