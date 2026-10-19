#include "Database.h"
#include "sqlite3.h"
#include <string>
#include <fstream>
#include <sstream>

static sqlite3* courseDB = nullptr;

std::vector<std::string> ParseCSVRow(const std::string& row) {
	bool isQuoted = false;
	std::vector<std::string> allRowStrings;
	std::string rowString;

	for (int i = 0; i < row.size(); i++) {
		char rowChar = row[i];

		if (rowChar == '"') {
			if (isQuoted && i + 1 < row.size() && row[i + 1] == '"') {
				rowString += '"';
				i++;
			}
			else {
				isQuoted = !isQuoted;
			}
		}
		else if (rowChar == ',' && !isQuoted) {
			allRowStrings.push_back(rowString);
			rowString.clear();
		}
		else {
			rowString += rowChar;
		}
	}

	allRowStrings.push_back(rowString);

	return allRowStrings;


}
bool Database::InitializeDB(const std::string& dbFilePath) {
	if (sqlite3_open(dbFilePath.c_str(), &courseDB) != SQLITE_OK) { // if db cannot be opened.
		sqlite3_close(courseDB); 
		courseDB = nullptr;
		return false;
	}

	const char* createCourses = "CREATE TABLE IF NOT EXISTS courses (course_number TEXT PRIMARY KEY, course_name TEXT NOT NULL);";
	const char* createPrerequisites = "CREATE TABLE IF NOT EXISTS prerequisites (course_number TEXT NOT NULL, prerequisite TEXT NOT NULL, PRIMARY KEY (course_number, prerequisite));";

	char* error = nullptr;

	if (sqlite3_exec(courseDB, createCourses, nullptr, nullptr, &error) != SQLITE_OK || sqlite3_exec(courseDB, createPrerequisites, nullptr, nullptr, &error) != SQLITE_OK) {
		sqlite3_free(error); // frees memory block.
		sqlite3_close(courseDB);
		courseDB = nullptr;
		return false;
	}
	
	return true;

}

bool Database::InsertFromCSV(const std::string& csvFilePath) {
	std::ifstream fileIn(csvFilePath);
	
	if (!fileIn) {
		return false;
	}
	
	sqlite3_exec(courseDB, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr);
	const char* courseSQL = "INSERT INTO courses VALUES (?, ?);";
	const char* prereqSQL = "INSERT INTO prerequisites VALUES (?, ?);";

	sqlite3_stmt* courseSTMT = nullptr;
	sqlite3_stmt* prereqSTMT = nullptr;

	sqlite3_prepare_v2(courseDB, courseSQL, -1, &courseSTMT, nullptr);
	sqlite3_prepare_v2(courseDB, prereqSQL, -1, &prereqSTMT, nullptr);

	/* read each line of the file and find each element separated by ',' on said line. These will then be inserted into the DB */
	for (std::string line; getline(fileIn, line);) {
		std::vector<std::string> row = ParseCSVRow(line);

		if (row.size() < 2) {
			continue;
		}

		sqlite3_bind_text(courseSTMT, 1, row[0].c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(courseSTMT, 2, row[1].c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_step(courseSTMT);
		sqlite3_reset(courseSTMT);


		// if the row contains prereqs, then this will be ran.
		if (row.size() > 2) {
			for (int i = 2; i < row.size(); i++) {
				if (!row[i].empty()) {
					sqlite3_bind_text(prereqSTMT, 1, row[0].c_str(), -1, SQLITE_TRANSIENT);
					sqlite3_bind_text(prereqSTMT, 2, row[i].c_str(), -1, SQLITE_TRANSIENT);
					sqlite3_step(prereqSTMT);
					sqlite3_reset(prereqSTMT);
				}
			}
		}
	}

	sqlite3_finalize(courseSTMT);
	sqlite3_finalize(prereqSTMT);
	sqlite3_exec(courseDB, "COMMIT;", nullptr, nullptr, nullptr);

	return true;
}

bool Database::LoadAllCourseNumbers(DynamicArray& courseArray) {
	if (courseDB == nullptr) {
		return false;
	}

	const char* loadSQL = "SELECT course_number FROM courses;";
	sqlite3_stmt* loadSTMT = nullptr;

	if (sqlite3_prepare_v2(courseDB, loadSQL, -1, &loadSTMT, nullptr) != SQLITE_OK) {
		return false;
	}

	while (sqlite3_step(loadSTMT) == SQLITE_ROW) {
		courseArray.Insert((const char*) sqlite3_column_text(loadSTMT,0));
	}

	sqlite3_finalize(loadSTMT);
	return true;
}

std::string Database::GetAllCourses()
{
	if (courseDB == nullptr) {
		return "ERROR. Database is null.";
	}
	
	const char* loadSQL = "SELECT course_number, course_name FROM courses ORDER BY course_number;";
	sqlite3_stmt* loadSTMT = nullptr;

	if (sqlite3_prepare_v2(courseDB, loadSQL, -1, &loadSTMT, nullptr) != SQLITE_OK) {
		return "ERROR. Statement could not be prepared.";
	}

	std::string courseOutput;
	while (sqlite3_step(loadSTMT) == SQLITE_ROW) {
		const unsigned char* courseNumber = sqlite3_column_text(loadSTMT, 0);
		const unsigned char* courseName = sqlite3_column_text(loadSTMT, 1);
		courseOutput += (const char*) courseNumber;
		courseOutput += ": ";
		courseOutput += (const char*) courseName;
		courseOutput += "\n\n";
	}
	
	sqlite3_finalize(loadSTMT);
	return courseOutput;
}

std::string Database::GetCoursePrereqs(const std::string& courseNumber) {
	if (courseDB == nullptr) {
		return "ERROR. Database is null.";
	}

	const char* loadSQL = "SELECT course_number, course_name FROM courses WHERE course_number COLLATE NOCASE = ?";
	sqlite3_stmt* loadSTMT = nullptr;

	if (sqlite3_prepare_v2(courseDB, loadSQL, -1, &loadSTMT, nullptr) != SQLITE_OK) {
		return "ERROR. course name load statement could not be prepared.";
	}

	sqlite3_bind_text(loadSTMT, 1, courseNumber.c_str(), -1, SQLITE_TRANSIENT);

	std::string output;
	if (sqlite3_step(loadSTMT) == SQLITE_ROW) {
		const unsigned char* number = sqlite3_column_text(loadSTMT, 0);
		const unsigned char* name = sqlite3_column_text(loadSTMT, 1);
		
		output += (const char*) number;
		output += ": ";
		output += (const char*) name;
		output += "\n\n";
	}

	sqlite3_finalize(loadSTMT);

	const char* loadPRSQL = "SELECT p.prerequisite FROM courses c LEFT JOIN prerequisites p ON p.course_number = c.course_number WHERE c.course_number COLLATE NOCASE = ?";
	sqlite3_stmt* loadPRSTMT = nullptr;

	if (sqlite3_prepare_v2(courseDB, loadPRSQL, -1, &loadPRSTMT, nullptr) != SQLITE_OK) {
		return "ERROR. prerequisite load statement could not be prepared.";
	}

	sqlite3_bind_text(loadPRSTMT, 1, courseNumber.c_str(), -1, SQLITE_TRANSIENT);

	output += "PREREQUISITES: \n";

	while (sqlite3_step(loadPRSTMT) == SQLITE_ROW) {
		const unsigned char* prereq = sqlite3_column_text(loadPRSTMT, 0);
		if (prereq == NULL) {
			output += "none. \n";
		}
		else {
			output += (const char*) prereq;
			output += "\n";
		}
	}

	sqlite3_finalize(loadPRSTMT);
	return output;
}

bool Database::InsertCourse(const std::string& courseNumber, const std::string& courseName, const std::vector<std::string>& prereqs)
{
	if (courseDB == nullptr) {
		return false;
	}
	
	char* errMsg = nullptr;
	if (sqlite3_exec(courseDB, "BEGIN TRANSACTION;", nullptr, nullptr, &errMsg) != SQLITE_OK) {
		sqlite3_free(errMsg);
		return false;
	}

	sqlite3_stmt* courseStmt = nullptr;
	if (sqlite3_prepare_v2(courseDB, "INSERT INTO courses VALUES (?, ?);", -1, &courseStmt, nullptr) != SQLITE_OK) {
		sqlite3_exec(courseDB, "ROLLBACK;", nullptr, nullptr, nullptr);
		return false;
	}

	sqlite3_bind_text(courseStmt, 1, courseNumber.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(courseStmt, 2, courseName.c_str(), -1, SQLITE_TRANSIENT);

	if (sqlite3_step(courseStmt) != SQLITE_DONE) {
		sqlite3_finalize(courseStmt);
		sqlite3_exec(courseDB, "ROLLBACK;", nullptr, nullptr, nullptr);
		return false;
	}
	sqlite3_finalize(courseStmt);

	if (!prereqs.empty()) {
		sqlite3_stmt* prereqStmt = nullptr;
		if (sqlite3_prepare_v2(courseDB, "INSERT INTO prerequisites (course_number, prerequisite_number) VALUES (?, ?);", -1, &prereqStmt, nullptr) != SQLITE_OK) {
			sqlite3_exec(courseDB, "ROLLBACK;", nullptr, nullptr, nullptr);
			return false;
		}
		
		for (const std::string& prereq : prereqs) {
			sqlite3_bind_text(prereqStmt, 1, courseNumber.c_str(), -1, SQLITE_TRANSIENT);
			sqlite3_bind_text(prereqStmt, 2, prereq.c_str(), -1, SQLITE_TRANSIENT);

			if (sqlite3_step(prereqStmt) != SQLITE_DONE) {
				sqlite3_finalize(prereqStmt);
				sqlite3_exec(courseDB, "ROLLBACK;", nullptr, nullptr, nullptr);
				return false;
			}
			sqlite3_reset(prereqStmt);
		}
		sqlite3_finalize(prereqStmt);
	}
	if (sqlite3_exec(courseDB, "COMMIT;", nullptr, nullptr, &errMsg) != SQLITE_OK) {
		sqlite3_free(errMsg);
		sqlite3_exec(courseDB, "ROLLBACK;", nullptr, nullptr, nullptr);
		return false;
	}
	return true;
}

bool Database::IsEmpty() {
	const char* sqlCheck = "SELECT COUNT(*) FROM courses;";
	sqlite3_stmt* stmtCheck = nullptr;

	// even if we cannot open the db, treat it as empty.
	if (sqlite3_prepare_v2(courseDB, sqlCheck, -1, &stmtCheck, nullptr) != SQLITE_OK) {
		return true;
	}

	int count = 0;
	if (sqlite3_step(stmtCheck) == SQLITE_ROW) {
		count = sqlite3_column_int(stmtCheck, 0);
	}

	sqlite3_finalize(stmtCheck);
	return count == 0;
}

void Database::Shutdown() {
	sqlite3_close(courseDB);
	courseDB = nullptr;
}

