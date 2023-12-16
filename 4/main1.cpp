#include <iostream>
#include "GCF/GCF.hpp"
#include "Sort/sort.hpp"

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

enum Function {
    FIRST = 1,
    SECOND = 2
}; 

int main(){
    
    Command cmd = EXIT;
    Function func = FIRST;

    std::cout<< "Choose command: \n" << 
                    "\t0 - switch func in lib,\n" <<  
                    "\t1 - find greatest common fraction,\n" << 
                    "\t2 - sort an array,\n" << 
                    "\t3 - exit." << std::endl;
    std::cout << std::endl;

    while (1){
        if (!(std::cin >> cmd)){
            std::cout << "Invalid input" << std::endl;
            break;
        }
        switch (cmd)
        {
        case CHANGE_FUNC:
            func = (func == FIRST) ? SECOND : FIRST;
            std::cout << "Function switched to " << ((func == FIRST) ? "first" : "second") 
                    << std::endl;
            break;
        case GCF:
            int a, b;
            std::cin >> a >> b;
            switch (func)
            {
            case FIRST:
                std::cout << GCF1(a, b) << std::endl;
                break;
            case SECOND:
                std::cout << GCF2(a, b) << std::endl;
                break;
            }
            break;
        case SORT:
            int n;
            std::cin >> n;
            int * arr;
            int * sorted;
            std::cout << "\nEnter an array :"; 
            for (int i = 0; i < n; ++i)
                std::cin >> arr[i];
            switch (func)
            {
            case FIRST:
                sorted = bubble_sort(arr, n);
                break;
            case SECOND:
                sorted = bubble_sort(arr, n);
                break;
            }
            std::cout << std::endl;
            for (size_t i = 0; i < n; ++i){
                std::cout << sorted[i] << " ";
            }
            std::cout << std::endl;
            break;
        case EXIT:
            exit(0);
        }
    }
    return 0;
}
