#include "bds.hpp"
class Args {
	private:
		bool equal(const char* str1, const char* str2){
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
		bool is_param(const char* obj) {
			const char* params[6] = {"--meas", "--size", "--steps", "--sorts", "--list", "--export"};
			for (int i=0; i < 6; i++) {
				if (equal(obj, params[i]) == true) {
					return true;
				}
			}
			return false;
		}
	public:
		void run(int argc, char** argv, const char* name_bd) {
			int sorts_amount = 6;
			int __sorts [sorts_amount] = {-1, -1, -1, -1, -1, -1}; //bubble, quick, isertion, selection, merge, count
			int __size = 1000;
			int __steps = __size;
			int __meas = 0;
			int __list = 0;
			int __export = 0;
			int flag = 1;
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
					flag = 0;
					int j = i;
					while ((j+1) < argc and is_param(argv[j + 1]) == false) {
						j += 1;
					}
					sorts_amount = j - i;
					if (sorts_amount == 1 and equal(argv[i+1], "all")) {
						sorts_amount = 6;
						for (int j=0; j < 6; j++) {
							__sorts[j] = 0;
						}
					} 
					else {
						for (int l=0; l < sorts_amount; l++) {
							if (equal("bubble", argv[l+i+1])) {
								__sorts[0] = 0;
							}
							if (equal("quick", argv[l+i+1])) {
								__sorts[1] = 0;
							}
							if (equal("insertion", argv[l+i+1])) {
								__sorts[2] = 0;
							}
							if (equal("selection", argv[l+i+1])) {
								__sorts[3] = 0;
							}
							if (equal("merge", argv[l+i+1])) {
								__sorts[4] = 0;
							}
							if (equal("count", argv[l+i+1])) {
								__sorts[5] = 0;
							}
						}
					}
				}
				if (equal(argv[i], "--size")) {
					if (i+1 < argc and is_param(argv[i+1]) == false) {
						__size = atoi(argv[i+1]);
					}
				}
				if (equal(argv[i], "--steps")) {
					if (i+1 < argc and is_param(argv[i+1]) == false) {
						__steps = atoi(argv[i+1]);
					}
				}
			}
	
			BDSort bd;
			bd.openBd(name_bd);
			bd.create_tabs();
			
			if (flag) {
				for (int i = 0; i < 6; i++) {
					__sorts[i] = 0;
				}
			}
/*			
			std::cout << "__meas " << __meas << "\n__size " << __size << "\n__steps " << __steps << "\n__list " << __list << "\n__export " << __export << '\n';
			for(int i = 0; i < 6; i++) {
				std::cout << __sorts[i] << '\t';
			}
			std::cout << std::endl;*/
			if (__meas) {
				bd.INSERT(__steps, __size, &__sorts[0]);
			}
			if (__list) {
				bd.SELECT(__steps, __size, &__sorts[0]);
			}
			bd.closeBd();
		}	
};



int main(int argc, char** argv) {
	Args handle;
	handle.run(argc, argv, "main.bd");
	return 0;
}	
