#include <unistd.h>
#include <string.h>
#include <iostream>

using namespace std;

#define LIKEEND -1

int main() {

    
    string error {"Строка не оканчивается на \".\" или \";\": "};
    int inputLineLen;
    while (1) {
        read(STDIN_FILENO, &inputLineLen, sizeof(inputLineLen));
        if(inputLineLen == LIKEEND) break; 

        char inputLine[inputLineLen];
        read(STDIN_FILENO, inputLine, inputLineLen);

        if (inputLine[inputLineLen - 1] == '.' || inputLine[inputLineLen - 1] == ';') {
            inputLine[inputLineLen] = '\n'; inputLineLen++;
            write(STDOUT_FILENO, inputLine, inputLineLen);
        } else { 
            for (int i = 0; i < inputLineLen; i++){ // если сразу все, то добавляется мусор
                error += inputLine[i];
            }
            error += '\0'; // без него добавляется мусор
            int errorLen = error.length();
            write(STDERR_FILENO, &errorLen, sizeof(errorLen));
            write(STDERR_FILENO, error.c_str(), error.length());
            break;
        }
    }

    return 0;
}