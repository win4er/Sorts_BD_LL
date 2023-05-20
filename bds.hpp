#ifndef BDS_HPP
#define BDS_HPP

#include "bdr.hpp"
#include "sorts.hpp"
#include <chrono>
#include <cmath>
#include <cstring>
#include <cstdio>

int callback_id(void* output, int countRec,  char** argv, char** colName);

class BDSort : public BDRequest {
	private:
		sqlite3* bd;
		void (*sorts[6])(int*, int) = {bubble_sort, quick_sort, insertion_sort, selection_sort, merge_sort, count_sort};
		const char* names_sorts[6] = {"'bubble_sort'", "'quick_sort'", "'insertion_sort'", "'selection_sort'", "'merge_sort'", "'count_sort'"};

	public:
		BDSort();
		~BDSort();
		bool equal(const char* str1, const char* str2);
		void create_tabs();
		double time_test(void (*sort)(int*, int), int size);
		void insert_info(int size, const char* name, void (*sort)(int*, int));
		void select_info(int size, const char* name, int (*callback)(void*, int, char**, char**));
		int getSizeArID(int size);
		int getSortID(const char* name);
		int getResSortID(int size, const char* name);
		int getResSortDur(int size, const char* name);
		void INSERT(int __steps, int __size, int* __sorts);
		void SELECT(int __steps, int __size, int* __sorts);
		void export_data(const char* sorts_file, const char* sizeArs_file, const char* resSorts_file);
};

#endif
