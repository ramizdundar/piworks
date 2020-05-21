#include <iostream> 
#include <vector>
#include <limits>
#include <algorithm>
#include <fstream>
#include <sstream>
  
using namespace std;

//negative infinity
int ninf = numeric_limits<int>::min();

bool isPrime(int n);
vector<vector<int>> read(string path);

int main() { 
    vector<vector<int>> data = read("data3.txt");

    int height = data.size();

    for (int i = 2; i < height; i++) {
        for (int j = 0; j < data[i].size(); j++) {
            
            int &e = data[i][j];

            if(isPrime(e)) {
                e = ninf;
                continue;
            }

            int r = data[i-1][j];
            int l = data[i-1][j-1];

            if (j == 0)
                e += r;
            else if (j == data[i].size()-1)
                e += l;
            else
                e += max(r, l);
        }
    }

    int maxpath = ninf;
    for (int i = 0; i < data[height-1].size(); i++) {
        if(data[height-1][i] > maxpath)
            maxpath = data[height-1][i];
    }

    if(isPrime(data[0][0]))
        maxpath = ninf;
    else
        maxpath += data[0][0];

    cout << "maximum path is: " << maxpath << endl;
    
    return 0;
}

bool isPrime(int n) {

    if (n == 1) 
        return false;
    
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

vector<vector<int>> read(string path) {
    ifstream inFile;
    inFile.open(path);
    vector<vector<int>> data;

    int e;
    string line;
    vector<int> level;

    while (getline(inFile, line)) {
        istringstream is(line);
        while(is >> e) {
            level.push_back(e);
        }
        data.push_back(level);
        level.clear();
    }

    return data;
}