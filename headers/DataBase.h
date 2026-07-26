#pragma once
#include "../external/sqlite/sqlite3.h"

namespace Database {
    class Database {
      public:
        bool Initialize();
        void Destroy();

      private:
    };
} // namespace Database
