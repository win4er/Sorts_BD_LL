#include "bds.hpp"

int len_str(const char* str) {
	int ind = -1;
	while (str[++ind] != '\0');
	return ind;
}

void conc(const char* str1, const char* str2, char* str3) {
	int len1 = len_str(str1);
	int len2 = len_str(str2);
	for (int i = 0; i < len1; i++) {
		str3[i] = str1[i];
	}
	int j = 0;
	for (int i = len1; i < len1 + len2; i++) {
		str3[i] = str2[j++];
	}
	str3[len1 + j] = '\0';
}

bool equal(const char* str1, const char* str2){
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

int str_to_int(const char* str) {
	int integer = 0;
	int len = len_str(str);
	for (int i = 0; i < len; i++) {
		switch (str[len-i-1]) {
			case '0':
				integer += 0;
				break;
			case '1':
				integer += 1 * pow(10, i);
				break;
			case '2':
				integer += 2 * pow(10, i);
				break;
			case '3':
				integer += 3 * pow(10, i);
				break;
			case '4':
				integer += 4 * pow(10, i);
				break;
			case '5':
				integer += 5 * pow(10, i);
				break;
			case '6':
				integer += 6 * pow(10, i);
				break;
			case '7':
				integer += 7 * pow(10, i);
				break;
			case '8':
				integer += 8 * pow(10, i);
				break;
			case '9':
				integer += 9 * pow(10, i);
				break;
			default:
				std::cerr << "int=0, string is wrong"  << std::endl;
		}
	}
	return integer;
}


bool is_param(const char* obj) {
	const char* params[6] = {"--meas", "--size", "--steps", "--sorts", "--list", "--export"};
	for (int i=0; i < 6; i++) {
		if (equal(obj, params[i]) == true) {
			return true;
		}
	}
	return false;
}


int main(int argc, char** argv) {
	int sorts_args = 6;
	const char* __sorts [sorts_args] = {"bubble", "quick", "insertion", "selection", "merge", "count"};
	int __size = 1000;
	bool flag_steps = true;
	int __steps = __size;
	int __meas = 0;
	int __list = 0;
	int __export = 0;
	for (int i = 1; i < argc; i++) {
		if (equal(argv[i], "--meas")) {
			__meas = 1;
		}
		if (equal(argv[i], "--list")) {
			__list = 1;
		}
		if (equal(argv[i], "--export")) {
			__export = 1;
		}
		if (equal(argv[i], "--sorts")) {
			int j = i;
			while ((j+1) < argc and is_param(argv[j + 1]) == false) {
				j += 1;
			}
			sorts_args = j - i;
			if (not(sorts_args == 1 and equal(argv[i+sorts_args], "all"))){
				for (int j=0; j < sorts_args; j++) {
					__sorts[j] = argv[i+j+1];
				}
			}
			else {
				sorts_args = 6;
			}
		}
		if (equal(argv[i], "--size")) {	
			int j = i;
			while ((j+1) < argc and is_param(argv[j + 1]) == false) {
				j += 1;
			}
			int size_args = j - i;
			if (size_args != 1) {
				std::cerr << "warning: --size=1000" << std::endl;
			} 
			else {
				__size = str_to_int(argv[i+1]);
				if (__size == 0) {
					std::cerr << "warning: --size=1000" << std::endl;
					__size = 1000;
				}
			}
		}
		if (equal(argv[i], "--steps")) {
			flag_steps = false;
			int j = i;
			while ((j+1) < argc and is_param(argv[j + 1]) == false) {
				j += 1;
			}
			int steps_args = j - i;
			if (steps_args != 1) {
				std::cerr << "warning: --steps=--size" << std::endl;
				__steps = __size;
			} 
			else {
				__steps = str_to_int(argv[i+1]);
				if (__steps == 0) {
					std::cerr << "warning: --steps=--size" << std::endl;
					__steps = __size;
				}
			}
		}
	}

	if (flag_steps) {
		__steps = __size;
	}

	
	
	BDSort bd;
	bd.openBd("main.bd");
	bd.create_tabs();
	if (__meas) {
		bd.INSERT(__steps, __size, __sorts, sorts_args);
	}
	if (__list) {
		bd.SELECT(__steps, __size, __sorts, sorts_args);
	}
	bd.closeBd();
	return 0;
}	
