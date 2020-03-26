#include <iostream>
#include <string>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

//Recursive function that stores the longest common subsequence into reference variable string & lcs 
//b is the 2d directional array
//x is the string to be printed
//m and n indicate size of b
//lcs is the variable that stores the longest common subsequence
void printLCS(int ** b, string x, int m, int n, string & lcs){
    //base case
    if (m == 0 || n == 0){
        return;
    }

    //in b[][] directional array,
    //3 indicates up left diagonal,
    //2 indicates up,
    //1 indicates left
    if (b[m][n] == 3){
        printLCS(b,x,m-1,n-1, lcs);
        lcs += x[m];
    }
    else if (b[m][n] == 2){
        printLCS(b,x,m-1,n, lcs);
    }
    else{
        printLCS(b,x,m,n-1, lcs);
    }
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
    
    //initialize dp arrays c[][] and b[][]
    int ** c = new int * [m];
    for (int i = 0; i < m; i++){
        c[i] = new int[n];
    }
    int ** b = new int * [m];
    for (int i = 0; i < m; i++){
        b[i] = new int[n];
    }

    //zero 0 indexed rows/cols in c[][]
    for (int i = 0; i < m; i++){
        c[i][0] = 0;
    }
    for (int j = 0; j < n; j++){
        c[0][j] = 0;
    }
    
    //go through c[][] and solve subproblems from bottom up
    for (int i = 1; i < m; i++){
        for (int j = 1; j < n; j++){
            //if character belongs in LCS, add one to length
            //document direction in b
            if (x[i] == y[j]){
                c[i][j] = c[i-1][j-1] + 1;
                b[i][j] = 3; //up left
            }
            //else, determine which subproblem to use based on greater
            //and document direction
            else if (c[i-1][j] >= c[i][j-1]){
                c[i][j] = c[i-1][j];
                b[i][j] = 2; //up
            } 
            else{
                c[i][j] = c[i][j-1];
                b[i][j] = 1; //left
            }
        }
    }


    //if input size is less than 10, print matrix
    if (m <= 10 && n <= 10){
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                output << c[i][j] << " ";
            }
            output << endl;
        }
        string lcs = "";
        printLCS(b, x, m-1, n-1, lcs);
        output << lcs;
        output << endl;
    }
    //if input size is greater than 10, print length of lcs
    else{
        output << c[m-1][n-1] << endl;
    }

    //stop timer
    auto stop = high_resolution_clock::now();
    
    //calculate and print time elapsed
    auto duration = duration_cast<milliseconds>(stop - start);
    output << duration.count() << " ms";

}
