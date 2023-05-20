#ifndef BDR_HPP
#define BDR_HPP

#include <iostream>
#include <string>
#include <assert.h>

#include "sqlite3.h"

int callback(void* outputStruct, int countRec, char** argv, char** colName);

class BDRequest {
	private:
		sqlite3 *bd;
	public:
		BDRequest();
		virtual ~BDRequest() = 0;
		void testBd();
		bool openBd(const char* bdName);
		bool closeBd();
		bool request_insert_create(const char* sqlString);
		int getLastRowId();
		bool request_select(const char* sqlSting, int (*callback)(void*, int, char**, char**), void* output);
};

#endif 
