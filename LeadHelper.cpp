
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <string>
using namespace std;
int Stand_num = 0;
int LifeGuard_num = 0;
void validateInput();
string chart[100][100];
int open;
int close;
vector<pair<int, int> > shifts;
vector<int> lgPerShift;
vector<string> standNames;
string times[48] = { "12:00a", "12:30a", "1:00a", "1:30a","2:00a", "2:30a", "3:00a", "3:30a","4:00a", "4:30a", "5:00a", "5:30a",
                    "6:00a", "6:30a", "7:00a", "7:30a","8:00a", "8:30a", "9:00a", "9:30a","10:00a", "10:30a", "11:00a", "11:30a",
                    "12:00p", "12:30p", "1:00p", "1:30p","2:00p", "2:30p", "3:00p", "3:30p","4:00p", "4:30p", "5:00p", "5:30p",
                    "6:00p", "6:30p", "7:00p", "7:30p","8:00p", "8:30p", "9:00p", "9:30p","10:00p", "10:30p", "11:00p", "11:30" };

void initializeChart() { //adds - to every element in chart
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            chart[i][j] = " ";
        }
    }
}


int timeIndex(string time) {
    for (int i = 0; i < 48; i++) {
        if (time == times[i]) {
            return i;
        }
    }

    return 0;
}

void setOpen(string input) { //sets the open var to the index of the matching time in array <times>
    if (input.back() == 'a') {
        for (int i = 0; i < 24; i++) {
            if (input == times[i]) {
                open = i;
                i = 24;
            }
        }
    }
    else if (input.back() == 'p') {
        for (int i = 24; i < 48; i++) {
            if (input == times[i]) {
                open = i;
                i = 48;
            }
        }
    }
    return;
}

void setClose(string input) {//sets the close var to the index of the matching time in array <times>
    if (input.back() == 'a') {
        for (int i = 0; i < 24; i++) {
            if (input == times[i]) {
                close = i;
                i = 24;
            }
        }
    }
    else if (input.back() == 'p') {
        for (int i = 24; i < 48; i++) {
            if (input == times[i]) {
                close = i;
                i = 48;
            }
        }
    }
    return;
}

void createRotation() {
    int lg_index = 0;

    for (int i = 0; i < (close - open); i++) {
        for (int j = 0; j < Stand_num; j++) {

            if (chart[lg_index][i] == "v") {
                //chart[lg_index][i] = to_string(j + 1);
                chart[lg_index][i] = standNames[j];
            }
            else {
                j--;
            }
            lg_index++;



            if (lg_index >= LifeGuard_num) {
                lg_index = 0;
            }
        }
    }
    return;
}


void printChart() {

    for (int x = open; x < close; x++) {
        cout << times[x] << "\t";
    }
    cout << endl;

    for (int i = 0; i < LifeGuard_num; i++) {
        for (int j = 0; j < (close - open); j++) {
            cout << chart[i][j] << "\t";
        }
        cout << endl;
    }
}


bool isValidTime(const string& time) {
    for (int i = 0; i < 48; i++) {
        if (times[i] == time) {
            return true;
        }
    }
    return false;
}

int getPositiveInteger(const string& prompt) {
    
    string input;
    int value;
    while (true) {
        cout << prompt;
        //getline(cin, input); // Read input as string
        cin >> input;
        // Check if input is a valid positive integer
        bool isValid = true;
        for (char c : input) {
            if (!isdigit(c)) {
                isValid = false;
                break;
            }
        }

        if (isValid && !input.empty()) {
            value = stoi(input); // Convert string to integer
            if (value > 0) {
                return value;
            }
            else {
                isValid = false; // Ensure it's positive
            }
        }

        cout << "Invalid input! Please enter a positive integer.\n";
    }
}

string getValidTime(const string& prompt) {
    string time;
    while (true) {
        cout << prompt;
        cin >> time;
        if (isValidTime(time)) {

            return time;
        }
        else {
            cout << "Invalid time! Please enter a valid time like 8:00a or 6:00p.\n";
        }
    }
}


void setShifts() {
    int n = 0;

    n = getPositiveInteger("Enter the number of shifts that you have scheduled today: ");

    for (int i = 0; i < n; i++) {
        cout << "\nEntering details for Shift " << (i + 1) << ":\n";


        int start = timeIndex(getValidTime("Enter the start time: "));
        if (start < open) { start = open; }

        int end = timeIndex(getValidTime("Enter the end time: "));
        if (end > close) { end = close; }

        int lgnum = getPositiveInteger("Enter the amount of Lifeguards that have this shift: ");

        shifts.push_back(make_pair(start, end));
        lgPerShift.push_back(lgnum);
        LifeGuard_num += lgnum;
    }


    return;
}

void putShiftinChart() {

    while (!shifts.empty()) {
        for (int i = 0; i < LifeGuard_num; i++) {
            for (int j = (shifts.front().first - open); j < (shifts.front().second - open); j++) {
                chart[i][j] = "v";
            }

            lgPerShift.front() = lgPerShift.front() - 1;
            if (lgPerShift.front() == 0) {
                shifts.erase(shifts.begin());
                lgPerShift.erase(lgPerShift.begin());
            }
        }
    }



}

void removeVs() {
    for (int i = 0; i < LifeGuard_num; i++) {
        for (int j = 0; j < (close - open); j++) {
            if (chart[i][j] == "v") {
                chart[i][j] = "-";
            }
        }
    }
}

void addBreaks() {


    for (int i = 0; i < LifeGuard_num; i++) {
        for (int j = 0; j < (close - open) - 1; j++) {
            if (chart[i][j] == "v" && chart[i][j + 1] == "v") {
                chart[i][j] = "B";
                chart[i][j + 1] = "B";
                j = close - open;
            }
        }
    }
}

void outputFile() {
    ofstream file("output.csv");


    if (!file) {
        cerr << "Error opening output file" << endl;
        return;
    }

    for (int x = open; x < close; x++) {
        file << times[x];
        if (x < close - 1) file << ",";
    }
    file << endl;

    for (int i = 0; i < LifeGuard_num; i++) {
        for (int j = 0; j < (close - open); j++) {
            file << chart[i][j];
            if (j < (close - open) - 1) file << ",";
        }
        file << endl;
    }


    file.close();
}
void getInput() {

    shifts.clear();
    lgPerShift.clear();
    setShifts();

    cout << "\nShift Schedule:\n";
    for (int i = 0; i < shifts.size(); i++) {
        cout << "Shift " << (i + 1) << ": " << shifts[i].first << " - " << shifts[i].second << "\n";
    }


    initializeChart();
    putShiftinChart();
    validateInput();
}


void validateInput() {
    int cnt = 0;
    for (int i = 0; i < (close - open); i++) {
        cnt = 0;
        for (int j = 0; j < LifeGuard_num; j++) {
            if (chart[j][i] == "v") {
                cnt++;
            }
        }

        if (cnt < Stand_num) {
            cerr << "The amount of lifeguards scheduled at " << times[i + open] << " is less than the amount of stands you have, Please try again with more lifeguards scheduled at that time" << endl << endl;
            getInput();
        }
    }
}



int main(int argc, char* argv[]) {

    string input;
    bool usingFile = false;
    Stand_num = getPositiveInteger("Enter the number of Lifeguard Stands: ");
    
    ifstream fileCheck("stands.txt");
    
    if (fileCheck.good()) {
        // check that the stand num is the same and ask if they would like to use the saved names
        
        if (getline(fileCheck, input)) {
            if (Stand_num == stoi(input)) {
                cout << "There are previously saved stand names, would you like to use them?(y/n): ";
                cin >> input;
                if (input == "y" || input == "Y") {
                    usingFile = true;
                    for (int i = 0; i < Stand_num; i++) {
                        getline(fileCheck, input);
                        standNames.push_back(input);
                    }
                    fileCheck.close();


                }
            }
        }
    }
    if(usingFile == false) { // get the stand names and save it to a file stands.txt
        ofstream outFile("stands.txt");
        outFile << Stand_num << endl;
        for (int i = 0; i < Stand_num; i++) {

            cout << "Enter the name of stand " << i + 1 << ": ";
            cin >> input;
            standNames.push_back(input);
            outFile << input << endl;

        }
        outFile.close();
    }

    





    while (true) {
        setOpen(getValidTime("Enter the pool opening time(e.g. 8:00a or 6:00p): "));
        setClose(getValidTime("Enter the pool closing time: "));
        if (open >= close) {
            cout << "Your closing time has to be atleast 30 minutes after opening time, please try again." << endl;
        }
        else {
            break;
        }
    }
    
    
    getInput();

    createRotation();
    addBreaks();


    removeVs();
    printChart();
    outputFile();

    return 0;
}
