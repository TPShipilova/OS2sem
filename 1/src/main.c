#include <iostream> 
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "isPipeEmpty.h" 

using namespace std;

pid_t create_process() {
    pid_t pid = fork();
    if (-1 == pid)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    return pid;
}


int main(){
    string filename;
    cout << "Введите имя файла: \n";
    cin >> filename;

    int fileFd = open(filename.c_str(), O_CREAT | O_WRONLY, 0777); //0777 - да вредно, но это же лаба
    if (fileFd == -1){
        cerr << "can't open file: " << filename;
        exit(EXIT_FAILURE);
    }

    int pipe1[2], pipe2[2];
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1){
        cerr << "fail pipe()";
        exit(EXIT_FAILURE);
    } 
    
    pid_t childPid = create_process();

    if (childPid == 0) { // child process 
        close(pipe1[1]);
        close(pipe2[0]);
        dup2(pipe1[0], STDIN_FILENO);
        dup2(pipe2[1], STDERR_FILENO);
        dup2(fileFd, STDOUT_FILENO);

        execl("./child", "./child", NULL); // exec child process
        
        close(pipe1[0]);
        close(pipe2[1]);
        close(fileFd);
        cout << "can't exec child process";
        exit(-1);

        
    } else { // parent process
        close(pipe1[0]);
        close(pipe2[1]);
        
        cin.ignore(); //для \n, который остался после введения имени файла 
        bool childErr = false;

        string inputLine;
        int inputLineLen = 0;
        while (getline(cin, inputLine)){
            if(false == isPipeEmpty(pipe2[0])) { 
                childErr = true;
                break;
            }
            inputLineLen = inputLine.length();
            write(pipe1[1], &inputLineLen, sizeof(inputLineLen));
            write(pipe1[1], inputLine.c_str(), inputLine.length());
        }
        if (!childErr){
            int likeEnd = -1;
            write(pipe1[1], &likeEnd, sizeof(likeEnd));
        }

        wait(NULL);
        int errorLen = 0; 
        if(read(pipe2[0], &errorLen, sizeof(errorLen)) > 0){
            char error[errorLen];
            read(pipe2[0], error, errorLen);
            cout << error << endl;
        }

        close(pipe1[1]);
        close(pipe2[0]);
    }
    close(fileFd);
    return 0;
}