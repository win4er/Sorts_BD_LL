#include "bds.hpp"

#define VERSION_MAJOR	"1"
#define VERSION_MINOR	".09"
#define VERSION	(VERSION_MAJOR + VERSION_MINOR)

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
			const int COUNT_PARAM = 7;
			const char* params[COUNT_PARAM] = {"--meas", "--size", "--steps", "--sorts", "--list", "--export", "--ver"};
			for (int i=0; i < COUNT_PARAM; i++) {
				if (equal(obj, params[i]) == true) {
					return true;
				}
				if (!strcmp(obj, "--ver")) {
					std::cout << "\t\t--- version 1.0 ---" << std::endl;
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
					if (i+1 < argc && is_param(argv[i+1]) == false) {
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
	std::cout << "\t\tver = " << VERSION_MAJOR << VERSION_MINOR << std::endl;
	Args handle;
	handle.run(argc, argv, "sorts_info.bd");
	return 0;
}	

enum ACTION {
	meas = 1,
	list = 2,
	expor = 3,
};

class ProcessKeys {
	private :
		int action;	//list, export, version, meas, import 
		int size;
		int step;
		int sorts[6];
		int countSorts;
		void process(int, char**) {}
		char** nameSort;
	public :
		ProcessKeys(int, char**) {}
		~ProcessKeys() {}

		int getAction() const {return action;}
		int getSize() const { return size; }
		int getStep() const { return step; }
		int getCountSort() const { return countSorts; }
		const char* getSortName(int numSort) { return nameSort[numSort]; }


};

void temp(int*, int) {}

int getTimeSorts(void (*sort)(int*, int), int size) {
	int *ar = new int [size];

	//random fill
	//start time
	//sort(ar, size);
	//stop time

	delete [] ar;
	return 0;	//stop - start;
}

void showData(const LL* list) {

}

void writeFile(const LL* list) {

}

enum SortsNumber { 
	bubble = 1,
	quick = 2,
};

int test_main(int argc, char** argv) {
	const ProcessKeys infoKeys(argc, argv);

	BDSorts infoBDSorts;
	LL *temp = new LL();	//need for bd... possible to move into bd class...

	void (*sort[6])(int*, int) = {temp, temp, temp, temp, temp, temp};	//??????? simplify the call sorts function in below strings....

//only for meas....
	for (int curSize = infoKeys.getStep(); curSize <= infoKeys.getSize(); curSize += infoKeys.getStep()) {
		for (int curSort = 0; curSort < infoKeys.getCountSort(); curSort++) {
			switch(infoKeys.getAction()) {
				case ACTION::meas :
				{
					int time = getTimeSorts(sort[curSort], curSize);
					infoBdSorts.insert(curSort, curSize, time);
				}
				break;
				case ACTION::expor :
				case ACTION::list : 
				{
					infoBDSorts.getData(temp, infoKeys.getNameSort(i), curSize); 
				}
				break;
			}
		}
	}

	switch(infoKeys.getAction()) {
		case ACTION::meas :
			std::cout << "measurement is finished... data was written!!! bye bye" << std::endl;
		break;
		case ACTION::list :
			show(temp);
			infoBdSorts.getLL();
		break;

		case ACTION::expor :
			write(infoBdSorts.getLL());
		break;
	}
	//release memory

	return 0;
}

















