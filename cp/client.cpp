#include <signal.h>
#include <sys/wait.h>
#include "utils.hpp"
#include "GameManager.hpp"
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
    int pipe[2] = {stoi(argv[1]), stoi(argv[2])};

    bool is_server = false;
    role_t role = (role_t)is_server;

    string cmd = "";

    while(cmd != "play") {
        cout << "> ";
        cin >> cmd;
        if(cmd == "leaderboard") {
            string stat = "statistics.txt";
            ifstream fin(stat);
            string line;
            while(getline(fin, line)){
                fin >> line;
                cout << line << endl;
                }
            fin.close();
        }
        else print_help();
    }

    string player_name;
    cout << "Enter your name: ";
    cin >> player_name;

    string filename;
    cout << "Enter your field schema filename: ";
    cin >> filename;

    GameManager manager(filename.c_str(), player_name);

    // write(pipe[WRITE], READY_MSG, 2);

    char* msg = new char[2];

    system("clear");
    manager.print();

    while(read(pipe[READ], msg, 2)) {
        system("clear");
        manager.print();

        cout << ((role == ROLE_ATTACK) ? "You are attacker now!" : "You are defending now!");

        string smsg {msg};

        if(smsg == STOP_MSG)
            break;

        if(role == ROLE_DEFEND) {
            size_t x = stoul(smsg.substr(0, 1));
            size_t y = stoul(smsg.substr(1, 2));
            shot_t res = manager.recieve_attack(x, y);

            if(res == SHOT_HIT) {
                if(manager.check_defeat()) {
                    write(pipe[WRITE], CAPITULATION_MSG, 2);
                    execl("./stat", "./stat", player_name.c_str(), "2", "0", NULL);
                    break;
                }
                write(pipe[WRITE], HIT_REPLY_MSG, 2);
            }
            else {
                write(pipe[WRITE], MISS_REPLY_MSG, 2);
                role = ROLE_ATTACK;
                continue;
            }
        }
        else {
            cout << "Enter coordinates to shot: ";
            int x, y;
            cin >> x >> y;
            msg[0] = char('0' + x);
            msg[1] = char('0' + y);
            write(pipe[WRITE], msg, 2);

            read(pipe[READ], msg, 2);
            string r {msg};
            if(r == HIT_REPLY_MSG)
                manager.set_shot_result(x, y, SHOT_HIT);
            else {
                manager.set_shot_result(x, y, SHOT_MISS);
                role = ROLE_DEFEND;
            }
        }
    }

    if(is_server)
        wait(NULL);

    delete[] msg;
    close(pipe[WRITE]);
    close(pipe[READ]);
    execl("./stat", "./stat", player_name.c_str(), "1", "0", NULL);
    return EXIT_SUCCESS;
}
