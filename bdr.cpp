#include "bdr.hpp"


BDRequest::BDRequest() {}
BDRequest::~BDRequest() {}

void BDRequest::testBd() {
    openBd("test.bd\0");
	void* output;
    request_insert_create("create TABLE IF NOT EXISTS temp(id integer primary key autoincrement, name varchar(32));");
    request_insert_create("INSERT INTO temp(name) VALUES ('test'),('test1'),('test2'),('test3');");

    request_select("SELECT count() FROM `temp`", callback, output);
    request_select("SELECT * FROM temp;", callback, output);

    closeBd();
}
/*
 *  opend base data with name
 */
bool BDRequest::openBd(const char* bdName) {
    int status = sqlite3_open(bdName, &bd);
    assert(status == SQLITE_OK);

    return status;
}

bool BDRequest::closeBd() {
    int status = sqlite3_close(bd);
    assert(status == SQLITE_OK);
    return status;
}

bool BDRequest::request_insert_create(const char* sqlString) {
    char* errMsg;
    int er = sqlite3_exec(bd, sqlString, nullptr, nullptr, &errMsg);
    if (er) {
        std::cerr << "error request " << sqlString << " : " << errMsg << std::endl;   //std::cout
    }

    return er;
}

int BDRequest::getLastRowId() {
    int last_id = sqlite3_last_insert_rowid(bd);
    return last_id;
}

bool BDRequest::request_select(const char* sqlString, int(*callback)(void*, int, char**, char**), void* output) {
    char* errMsg;
    int er = sqlite3_exec(bd, sqlString, callback, output, &errMsg);

    if (er != SQLITE_OK) {
        std::cerr << "error request " << sqlString << " : " << errMsg << std::endl;
    }
    assert(er == SQLITE_OK);

    return er;
}


int callback(void* outputStruct, int countRec, char** argv, char** colName) {
    //void* -- c-style
    //outputStructure allow to return back the data for processing....
    for (int i = 0; i < countRec; i++) {
        std::cout << "\t" << colName[i] << " '" << argv[i] << "'";
    }
    std::cout << std::endl;
    return 0;
}
