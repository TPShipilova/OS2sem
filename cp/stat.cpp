#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct UserData {
    string username;
    int first_number;
    int second_number;
};

int main(int argc, char** argv) {
    string filename = "statistics.txt";
    string username = argv[1];
    int number_to_change = stoi(argv[2]);

    vector<UserData> user_data_list;

    ifstream file_in(filename);
    if (!file_in.is_open()) {
        cout << "Failed to open the file for reading." << endl;
        return 1;
    }

    bool found_user = false;
    UserData user_data;

    while (file_in >> user_data.username >> user_data.first_number >> user_data.second_number) {
        if (user_data.username == username) {
            found_user = true;
            break;
        }
        user_data_list.push_back(user_data);
    }

    file_in.close();

    if (!found_user) {
        user_data.first_number = 0;
        user_data.second_number = 0;
        user_data_list.push_back(user_data);
    }

    if (number_to_change == 1) {
        user_data_list.back().first_number += 1;
    } else if (number_to_change == 2) {
        user_data_list.back().second_number += 1;
    } else {
        cout << "Invalid number to change." << endl;
        return 1;
    }

    ofstream file_out(filename);
    if (!file_out.is_open()) {
        cout << "Failed to open the file for writing." << endl;
        return 1;
    }

    for (const auto& data : user_data_list) {
        file_out << data.username << " " << data.first_number << " " << data.second_number << endl;
    }

    file_out.close();
    return EXIT_SUCCESS;
    return 0;
}
