#ifndef BDS_HPP
#define BDS_HPP

#include "bdr.hpp"
#include "sorts.hpp"
#include <chrono>
#include <cmath>
#include <cstring>


int callback_info(void* output, int countRec, char** argv, char** colName);

class BDSort : public BDRequest {
	private:
		sqlite3* bd;
		void (*sorts[6])(int*, int) = {bubble_sort, selection_sort, insertion_sort, count_sort, quick_sort, merge_sort};
		const char* names_sql[6] = {"('bubble_sort')", "('selection_sort')", "('insertion_sort')", "('count_sort')", "('quick_sort')", "('merge_sort')"};
		const char* names_sorts[6] = {"'bubble_sort'", "'selection_sort'", "'insertion_sort'", "'count_sort'", "'quick_sort'", "'merge_sort'"};

	public:
		BDSort();
		~BDSort();
		void conc(const char* str1, const char* str2, char* str3);
		void auto_to_str(double obj, char* str);
		int len_auto(double digital);
		bool equal(const char* str1, const char* str2);
		void create_tabs();
		double time_test(void (*sort)(int*, int), int size);
		void insert_info(int size, const char* name, void (*sort)(int*, int));
		void select_info(int size, const char* name_sort, int (*callback)(void*, int, char**, char**));
		void INSERT(int __steps, int __size, const char** __sorts, int sorts_args);
		void SELECT(int __steps, int __size, const char** __sorts, int sorts_args);
};

#endif
