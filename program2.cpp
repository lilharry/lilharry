#include <iostream>
#include <string>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

//recursive function to determine longest common subsequence
//c[][] is the dp array that stores subproblem solutions
//x stores input 1
//y stores input 2
//m and n are the dimensions of c
int lcs(int ** c, string x, string y, int m, int n){
    //base case
    if (m == 0 || n == 0){
        return 0;
    }
    //if character should be added to subsequence
    if (x[m] == y[n]){
        //add 1 to length of lcs
        c[m][n] = lcs(c, x, y, m - 1, n - 1) + 1;
    }else{
        //find max of subproblems in c[m-1][n] and c[m][n-1]
        c[m][n] = max(lcs(c, x, y, m - 1, n), lcs(c, x, y, m, n - 1));
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
    
    //first input file
    ifstream inFile;
    inFile.open(argv[1]);

    //second input file
    ifstream inFile2;
    inFile2.open(argv[2]);

    //output file
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

    //length of strings
    int m = x.length();
    int n = y.length();

    //initialize array c[][] to store solutions of subproblems 
    int ** c = new int * [m];
    for (int i = 0; i < m; i++){
        c[i] = new int[n];
    }

    //zero 0 indexed rows/cols in c[][]
    for (int i = 0; i < m; i++){
        c[i][0] = 0;
    }
    for (int j = 0; j < n; j++){
        c[0][j] = 0;
    }
    
    //call to recursive function
    lcs(c, x, y, m-1, n-1);    

    //print solution
    output << c[m-1][n-1] << endl;
    
    //stop timer
    auto stop = high_resolution_clock::now();
    
    //calculate and print time elapsed
    auto duration = duration_cast<milliseconds>(stop - start); 
    output << duration.count() << " ms";

}
