#include "bds.hpp"


int callback_id(void* output, int countRec,  char** argv, char** colName) {
    int *temp = (int*)output;
	*temp = atoi(argv[0]);
	return 0;
}





BDSort::BDSort() {}
BDSort::~BDSort() {}



bool BDSort::equal(const char* str1, const char* str2){
	int len1 = strlen(str1);
	int len2 = strlen(str2);
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

int BDSort::getSortID(const char* name) {
	std::string request = "select id from Sorts where Sorts.nameSort = " + (std::string)name;
	int ID = 0;
	request_select(request.c_str(), callback_id, &ID);
	return ID;
}


int BDSort::getSizeArID(int size) {
	std::string request = "select id from SizeArs where SizeArs.sizeAr = " + std::to_string(size);
	int ID = 0;
	request_select(request.c_str(), callback_id, &ID);
	return ID;
}


int BDSort::getResSortID(int size, const char* name) {
	std::string request = "select ResSorts.id from ResSorts, SizeArs, Sorts  where ResSorts.idSizeAr = SizeArs.id and ResSorts.idSort = Sorts.id and SizeArs.sizeAr = " + std::to_string(size) + (std::string)" and Sorts.nameSort = " + (std::string)name;
	int ID = 0;
	request_select(request.c_str(), callback_id, &ID);
	return ID;
}


int BDSort::getResSortDur(int size, const char* name) {
	std::string request = "select durSort_ms from ResSorts, SizeArs, Sorts  where ResSorts.idSizeAr = SizeArs.id and ResSorts.idSort = Sorts.id and SizeArs.sizeAr = " + std::to_string(size) + (std::string)" and Sorts.nameSort = " + (std::string)name;
	int duration = 0;
	request_select(request.c_str(), callback_id, &duration);
	return duration;
}


void BDSort::select_info(int size, const char* name, int (*callback)(void*, int, char**, char**)) {
	std::string request = "select Sorts.nameSort, SizeArs.sizeAr, ResSorts.durSort_ms from ResSorts, Sorts, SizeArs where ResSorts.idSort = Sorts.id and ResSorts.idSizeAr = SizeArs.id and SizeArs.sizeAr = " + std::to_string(size) + (std::string)" and Sorts.nameSort = " + (std::string)name;
	request_select(request.c_str(), callback, nullptr);
}


void BDSort::insert_info(int size, const char* name, void (*sort)(int*, int)) {	
	int id_sort = getSortID(name);
	int id_size = getSizeArID(size);
	int dur = getResSortDur(size, name);
	int id_res = getResSortID(size, name);

	if (!id_sort) {
		std::string request_Sorts = "insert into Sorts(nameSort) VALUES (" +  (std::string)name + (std::string)")";
		request_insert_create(request_Sorts.c_str());
		int id_sort = getLastRowId();
	}

	if (!id_size) {
		std::string request_SizeArs = "insert into SizeArs(sizeAr) VALUES (" + std::to_string(size) + (std::string)")";
		request_insert_create(request_SizeArs.c_str());
		int id_size = getLastRowId();
	}
	
	double duration = time_test(sort, size) * 1000;
	
	//beside true: id_res or (id_res and dur != (int)duration))
	if (true) {
		std::string request_ResSorts = "insert into ResSorts(idSort, idSizeAr, durSort_ms) VALUES (" + std::to_string(id_sort) + (std::string)", " + std::to_string(id_size) + (std::string)", " + std::to_string((int)duration) + (std::string)")";
		request_insert_create(request_ResSorts.c_str());
	}
}


void BDSort::INSERT(int __steps, int __size, int* __sorts) {
	int size_ar = __steps;
	while (size_ar <= __size) {
		for (int i = 0; i < 6; i++) {
			if (__sorts[i] == 0) {
				insert_info(size_ar, names_sorts[i], sorts[i]);
			}
		}
		size_ar += __steps;
	}
}


void BDSort::SELECT(int __steps, int __size, int* __sorts) {
	int size_ar = __steps;
	int* output;
	while (size_ar <= __size) {
		for (int i = 0; i < 6; i++) {
			if (__sorts[i] == 0) {
				select_info(size_ar, names_sorts[i], callback);
			}
		}
		size_ar += __steps;
	}
}


void BDSort::export_data(const char* sorts_file, const char* sizeArs_file, const char* resSorts_file) {
/*	FILE *fsort = fopen(sorts_file, "w");
	std::string req = "select count() from Sorts";
	int count = 0;
	request_select(req.c_str(), callback_id, &count);
	for (int i=0; i < count + 1; i++) {
		if (i == 0) {
			std::string data = "/tID/tnameSort";
		}
		else {
			std::string data = (std::to_string);
		}
	}
	fwrite();*/
}
