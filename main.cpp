#include <fstream>
#include <string>
#include <unistd.h> //usleep()
#include <sys/stat.h> //exists()
#include <iostream>
#include <vector>
#include <algorithm> //reverse()

using namespace std;

const string inputfile = "server1/file.txt";
const string outputfile = "server2/file.txt";
const string pattern = "ZZ.ZZ.ZZ";
const unsigned int interval = 1000000; //1 second = 1000000 microseconds

bool check_pattern(string);
void remove_line(fstream&, unsigned int);
bool write_output(vector<string>&);

inline bool exists(const string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

int main() {
    string temp;
    vector<string> output;
    fstream fs(inputfile, ios::in | ios::out);
    bool status; //for availability of destination file
    while (fs >> temp) {
        remove_line(fs, temp.length()); //replacing current line with SPACE characters
        if (check_pattern(temp) == true) { //checking for pattern match
            //reading next line and reversing it
            fs >> temp;
            reverse(temp.begin(), temp.end());
            output.push_back(temp);
            remove_line(fs, temp.length());
        }
        if (output.size() > 0) { //check if there is any data to write
            status = write_output(output);
        }
        usleep(interval);
    }
    fs.close();
    while (output.size() > 0) { //check if there is any left data to write
        write_output(output);
        if (status == false) { //if destination is not available - sleep
            usleep(interval);
        }
    }
    //remove all content(spaces) from input file
    ofstream ofs;
    ofs.open(inputfile, ios::out | ios::trunc); 
    ofs.close();
    return 0;
}

bool check_pattern(string temp) {
    size_t pos = temp.find(pattern);
    if (pos != string::npos) { 
        if (temp.length() - pattern.length() != pos) { //checking if pattern is not at the end of text
            return true;
        }         
    }
    return false;
}

void remove_line(fstream& fs, unsigned int length) {
    fs.seekg(static_cast<unsigned int>(fs.tellp()) - length);
    for (unsigned int i=0; i<length; i++) {
        fs << ' ';
    }
}

bool write_output(vector<string>& output) {
    if (exists(outputfile)) {
        ofstream ofs;
        ofs.open(outputfile, fstream::out | fstream::app);
        while (output.size() > 0) {
            if (ofs.is_open()) {
                ofs << output.at(0) << endl;
                output.erase(output.begin()+0); //deleting first element of vector
            }
            else {
                //cout << "DESTINATION IS UNAVAILABLE!" << endl;
                return false;
            }
        }
        ofs.close();
    }
    else {
        //cout << "DESTINATION IS UNAVAILABLE!" << endl;
        return false;
    }
    return true;   
}