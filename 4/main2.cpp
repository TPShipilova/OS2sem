#include <dlfcn.h>
#include <iostream>

enum Command {
    CHANGE_FUNC = 0,
    GCF = 1,
    SORT = 2,
    EXIT = 3
};

std::istream& operator>>(std::istream& is, Command& cmd){
    int tmp;
    while (((is >> tmp) && (tmp < 0 || tmp > 3))){
        std::cout << "Invalid command" << std::endl;
    }
    cmd = static_cast<Command>(tmp);
    return is;
}

enum Algo {
    FIRST = 1,
    SECOND = 2
}; 

std::string gcf_lib_path = "./libGCF.so";
std::string sort_lib_path = "./libSort.so";

int main(){
    
    void* gcf_lib = dlopen(gcf_lib_path.c_str(), RTLD_LAZY);
    void* sort_lib = dlopen(sort_lib_path.c_str(), RTLD_LAZY);

    if (!sort_lib || !gcf_lib) {
        std::cout << "Cannot load library: " << dlerror() << '\n';
        return 1;
    }

    typedef int (*GCFType)(int, int);
    typedef int* (*SortType)(int *, int);
    
    if (!dlsym(gcf_lib, "GCF1") || !dlsym(gcf_lib, "GCF2") || 
        !dlsym(sort_lib, "bubble_sort") || !dlsym(sort_lib, "hoar_sort")) {
        std::cout << "Cannot load function: " << dlerror() << '\n';
        dlclose(gcf_lib);
        dlclose(sort_lib);
        return 1;
    }

    Command cmd = EXIT;
    Algo cur_algo = FIRST;

    GCFType GCF_alg = (GCFType)dlsym(gcf_lib, "GCF1");
    SortType Sort_alg = (SortType)dlsym(sort_lib, "bubble_sort");

    std::cout<< "Choose command: \n" << 
                    "\t0 - switch algo in lib,\n" <<  
                    "\t1 - calculate sin integral,\n" << 
                    "\t2 - calculate cos derivative,\n" << 
                    "\t3 - exit." << std::endl;
    std::cout << "===========================================" << std::endl;

    while (1){
        if (!(std::cin >> cmd)){
            std::cout << "Invalid input" << std::endl;
            break;
        }
        switch (cmd)
        {
        case CHANGE_FUNC:
            cur_algo = (cur_algo == FIRST) ? SECOND : FIRST;
            GCF_alg = (cur_algo == FIRST) ? (GCFType)dlsym(gcf_lib, "GCF1") : (GCFType)dlsym(gcf_lib, "GCF2");
            Sort_alg = (cur_algo == FIRST) ? (SortType)dlsym(sort_lib, "bubble_sort") : (SortType)dlsym(sort_lib, "hoar_sort");
            std::cout << "Algo switched to " << ((cur_algo == FIRST) ? "first" : "second") << std::endl;
            break;
        case GCF:
            int a, b;
            std::cin >> a >> b;
            std::cout << "GCF is: " << GCF_alg(a, b) << std::endl;
            break;
        case SORT:
            int n;
            std::cin >> n;
            int * arr;
            int * sorted;
            std::cout << "\nEnter an array :"; 
            for (int i = 0; i < n; ++i)
                std::cin >> arr[i];
            sorted = Sort_alg(arr,n);    
            std::cout << std::endl << "Sorted: ";
            for (size_t i = 0; i < n; ++i){
                std::cout << sorted[i] << " ";
            }
            std::cout << std::endl;
            break;
        case EXIT:
            exit(0);
        }
    }
    dlclose(gcf_lib);
    dlclose(sort_lib);
    return 0;
}
