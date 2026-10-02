#ifndef DATABASE_H
#define DATABASE_H
#include <string>
#include "DynamicArray.h"
class Database {
public:
	static bool InitializeDB(const std::string& dbFilePath);
	static bool InsertFromCSV(const std::string& csvFilePath);
	static bool IsEmpty();
	static void Shutdown();
};

#endif
