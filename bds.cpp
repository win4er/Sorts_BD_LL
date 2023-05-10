#include "bds.hpp"


BDSort::BDSort() {}
BDSort::~BDSort() {}


int BDSort::len_str(const char* str) {
	int ind = -1;
	while (str[++ind] != '\0');
	return ind;
}


void BDSort::conc(const char* str1, const char* str2, char* str3) {
	int len1 = len_str(str1);
	int len2 = len_str(str2);
	for (int i = 0; i < len1; i++) {
		str3[i] = str1[i];
	}
	int j = 0;
	for (int i = len1; i < len1 + len2; i++) {
		str3[i] = str2[j++];
	}
	str3[len1+j] = '\0';
}


int BDSort::len_auto(double digital) {
	int len = 0;
	while (pow(10, (++len)) <= digital);
	return len;
}


void BDSort::auto_to_str(double obj, char* str){
	int object = obj;
	int length = len_auto(object);
	int digit = 0;
	int last_ind = 0;
	for (int i = 0; i < length; i++) {
		digit = object % 10;
		switch (digit) {
			case 0:
				str[length-1-i] = '0';
				break;
			case 1:
				str[length-1-i] = '1';
				break;
			case 2:
				str[length-1-i] = '2';
				break;
			case 3:
				str[length-1-i] = '3';
				break;
			case 4:
				str[length-1-i] = '4';
				break;
			case 5:
				str[length-1-i] = '5';
				break;
			case 6:
				str[length-1-i] = '6';
				break;
			case 7:
				str[length-1-i] = '7';
				break;
			case 8:
				str[length-1-i] = '8';
				break;
			case 9:
				str[length-1-i] = '9';
				break;
		}
		object /= 10;
		last_ind = i;
	}
	str[++last_ind] = '\0';
}


bool BDSort::equal(const char* str1, const char* str2){
	int len1 = len_str(str1);
	int len2 = len_str(str2);
	if (len1 == len2) {
		for (int i = 0; i < len1; i++) {
			if (str1[i] != str2[i]) {
				return false;
			}
		}
		return true;
	}
	else {
		return false;
	}
}


void BDSort::create_tabs() {
	request_insert_create("CREATE TABLE IF NOT EXISTS Sorts(id INTEGER PRIMARY KEY autoincrement unique, nameSort VARCHAR);");
	request_insert_create("CREATE TABLE IF NOT EXISTS SizeArs(id INTEGER PRIMARY KEY autoincrement unique, sizeAr integer);");
	request_insert_create("CREATE TABLE IF NOT EXISTS ResSorts(id INTEGER PRIMARY KEY autoincrement unique, idSort integer, idSizeAr integer, durSort_ms integer, foreign key  (idSort) references Sorts(id) ON DELETE cascade ON UPDATE cascade, foreign key (idSizeAr) references SizeArs(id) ON DELETE cascade ON UPDATE cascade);");
}


double BDSort::time_test(void (*sort)(int*, int), int size) {
	int* ar = new int[size];
	random_Fill_ar(ar, size, 0, 1000);

	auto start = std::chrono::high_resolution_clock::now();
	sort(ar, size);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	delete [] ar;
	return diff.count();
}


void BDSort::insert_info(int size, const char* name, void (*sort)(int*, int)) {
	const char* part1 = "insert into Sorts(nameSort) VALUES ";
	char req_name_sort [len_str(part1) + len_str(name) + 1];
	conc(part1, name, req_name_sort);
	request_insert_create(req_name_sort);

	int id_sort = getLastRowId();

	const char* part2 = "insert into SizeArs(sizeAr) VALUES (";
	char str_size [len_auto(size) + 1];
	auto_to_str(size, str_size);
	
	char part3 [len_auto(size) + len_str(part2) + 1]; 
	conc(part2, str_size, part3);

	char req_size_ar [len_str(part3) + len_str(");") + 1];
	conc(part3, ");", req_size_ar);

	request_insert_create(req_size_ar);

	int id_size_ar = getLastRowId();
	double duration = time_test(sort, size) * pow(10, 3);

	char id_sort_str [len_auto(id_sort) + 1];
	auto_to_str(id_sort, id_sort_str);

	char id_size_ar_str [len_auto(id_sort) + 1];
	auto_to_str(id_size_ar, id_size_ar_str);

	const char* part5 = "insert into ResSorts(idSort, idSizeAr, durSort_ms) VALUES (";

	char part6 [len_str(part5) + len_str(id_sort_str) + 1];
	conc(part5, id_sort_str, part6);

	char part7 [len_str(part6) + len_str(", ") + 1];
	conc(part6, ", ", part7);

	char part8 [len_str(part7) + len_str(id_size_ar_str) + 1];
	conc(part7, id_size_ar_str, part8);

	char part9 [len_str(part8) + len_str(", ") + 1];
	conc(part8, ", ", part9);

	char dur_str [len_auto(duration) + 1];
	auto_to_str(duration, dur_str);

	char part10 [len_str(part9) + len_str(dur_str) + 1];
	conc(part9, dur_str, part10);

	
	char part11 [len_str(part10) + len_str(");") + 1];
	conc(part10, ");", part11);

	request_insert_create(part11);
}


void BDSort::select_info(int size, const char* name_sort) {
	const char* part1 = "select * from ResSorts, Sorts, SizeArs where ResSorts.idSort = Sorts.id and ResSorts.idSizeAr = SizeArs.id and SizeArs.sizeAr = ";
	
	char size_str [len_auto(size) + 1];
	auto_to_str(size, size_str);

	char part2 [len_str(part1) + len_str(size_str) + 1];
	conc(part1, size_str, part2);

	const char* last_condition = " and Sorts.nameSort = ";

	char part3 [len_str(part2) + len_str(last_condition) + 1];
	conc(part2, last_condition, part3);
	
	char req_all_info [len_str(part3) + len_str(name_sort) + 1];
	conc(part3, name_sort, req_all_info);
	
	request_select(req_all_info, callback);
}


void BDSort::INSERT(int __steps, int __size, const char** __sorts, int sorts_args) {
	int size_ar = __steps;
	while (size_ar <= __size) {
		for (int i = 0; i < sorts_args; i++) {
			if (equal("bubble", __sorts[i])) {
				insert_info(size_ar, names_sql[0],  bubble_sort);
			}
			if (equal("quick", __sorts[i])) {
				insert_info(size_ar, names_sql[4],  quick_sort);
			}
			if (equal("insertion", __sorts[i])) {
				insert_info(size_ar, names_sql[2], insertion_sort);
			}
			if (equal("selection", __sorts[i])) {
				insert_info(size_ar, names_sql[1], selection_sort);
			}
			if (equal("merge", __sorts[i])) {
				insert_info(size_ar, names_sql[5], merge_sort);
			}
			if (equal("count", __sorts[i])) {
				insert_info(size_ar, names_sql[3], count_sort);
			}
		}
		size_ar += __steps;
	}
}


void BDSort::SELECT(int __steps, int __size, const char** __sorts, int sorts_args) {
	int size_ar = __steps;
	while (size_ar <= __size) {
		for (int i = 0; i < sorts_args; i++) {
			if (equal("bubble", __sorts[i])) {
				select_info(size_ar, names_sorts[0]);
			}
			if (equal("quick", __sorts[i])) {
				select_info(size_ar, names_sorts[4]);
			}
			if (equal("insertion", __sorts[i])) {
				select_info(size_ar, names_sorts[2]);
			}
			if (equal("selection", __sorts[i])) {
				select_info(size_ar, names_sorts[1]);
			}
			if (equal("merge", __sorts[i])) {
				select_info(size_ar, names_sorts[5]);
			}
			if (equal("count", __sorts[i])) {
				select_info(size_ar, names_sorts[3]);
			}
		}
		size_ar += __steps;
	}
}
