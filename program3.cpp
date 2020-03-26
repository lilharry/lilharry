#include <iostream>
#include <string>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

//recursive dp function to find longest common subsequence of two strings
//c[][] is the dp array, initialized to 0 for all zero-indexed entries and -1 for all other entries
//x and y are the input strings
//m and n are the dimensions of c
int lcs(int ** c, string x, string y, int m, int n){
    //base case
    if (m == 0 || n == 0){
        return 0;
    }

    //if character should be added to subsequence
    if (x[m] == y[n]){
        //if previous value was calculated, take it
        if (c[m][n] != -1){
            c[m][n] = c[m-1][n-1] + 1;   
        //otherwise, calculate it
        }else{
            c[m][n] = lcs(c, x, y, m - 1, n - 1) + 1;
        }
    }else{
        //if previous subproblems located in c[m-1][n] and c[m][n-1] were calculated, use max of them
        //else, calculate whichever subproblems were not calculated and store in c[][]
        if ((c[m][n-1] != -1) && (c[m-1][n] != -1)){
            c[m][n] = max(c[m-1][n], c[m][n-1]);
        }else if ((c[m][n-1] != -1) && (c[m-1][n] == -1)){
            c[m][n] = max(c[m-1][n], lcs(c, x, y, m, n - 1));
        }else if ((c[m][n-1] == -1) && (c[m-1][n] != -1)){
            c[m][n] = max(lcs(c, x, y, m - 1, n), c[m-1][n]);
        }else{ 
            c[m][n] = max(lcs(c, x, y, m - 1, n), lcs(c, x, y, m, n - 1));
        }
    }
    
    return c[m][n];
}


int main(int argc, char * argv[]){
    
    if (argc < 4){
        cout << "Usage: ./program1 filex.txt filey.txt output.txt" << endl;
        exit(1);
    }

    //start timer
    auto start = high_resolution_clock::now();
    
    //open first input file
    ifstream inFile;
    inFile.open(argv[1]);

    //open second input file
    ifstream inFile2;
    inFile2.open(argv[2]);

    //open output file
    ofstream output;
    output.open(argv[3]);

    //strings to store input
    string x;
    string y;

    inFile >> x;
    inFile2 >> y;
    inFile.close();
    inFile2.close();
    

    //create offset so string indices start at 1
    x = " " + x;
    y = " " + y;

    //variables to hold string length
    int m = x.length();
    int n = y.length();
    
    //initialize dp array
    int ** c = new int * [m];
    for (int i = 0; i < m; i++){
        c[i] = new int[n];
    }

    //set 0 indexed positions to 0, set all other positions to -1
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (i == 0 || j == 0){
                c[i][j] = 0;
            }else{
                c[i][j] = -1;
            }
        }
    }

    //call recursive dp function
    lcs(c, x, y, m-1, n-1);    

    //print longest common subsequence length
    output << c[m-1][n-1] << endl;
    
    //stop timer
    auto stop = high_resolution_clock::now();
    
    //calculate and print time elapsed
    auto duration = duration_cast<milliseconds>(stop - start);
    output << duration.count() << " ms";

}
