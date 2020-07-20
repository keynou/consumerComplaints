#include <iostream>     // std::istream, std::cout, fixed
#include <fstream>      // std::ifstream, std::ofstream
#include <string>
#include <unordered_map>
#include <iomanip>      // std::setprecision
#include <map>
using namespace std;

// The input file that has all the information. This file will be analyzed so that the dated complaints with a company's product
// be counted and written to the output file.
ifstream myfile("../input/complaints.csv");
//ifstream myfile("../insight_testsuite/tests/test_1/input/complaints.csv");
//ifstream myfile("../insight_testsuite/tests/your-own-test_1/input/complaints.csv");
//ifstream myfile("../insight_testsuite/tests/your-own-test_2/input/complaints.csv");
//ifstream myfile("../insight_testsuite/tests/your-own-test_3/input/complaints.csv");
// Other input file tests are (if you add them to the input folder):
/*
ifstream myfile("../input/complaints.csv");
ifstream myfile("../input/test3.csv");
ifstream myfile("../input/test4.csv");
*/

// The output file with alphabetically ordered products and year for complaints within a company will be written to the selected output using the following stream:
ofstream writeFile;

//ofstream debugFile("../output/errors.txt");

// Each time we will read the input file lines into this string.
// The line number, will indicate which line we are reading in the input file.
string line;
int lineNum;

// Initializing the header index numbers for the year, the product, and the company.
int yearInd;
int productInd;
int companyInd;
// The cells in each line of the code will be put into the following appropriate strings and the they will be put into the map of the data.
string year;
string product;
string company;

// Creating unordered_map of products. The Key to be the product name and the value to be another <Key, Value> in a different hash table. The 2nd hash
// table will have year as its Key and the number of complaints for that product and year in its Value.
std::unordered_map<std::string, unordered_map<string,int>> yearlyProdMap;  // year, product, total number C

// Creating unordered_map of products. The Key to be the product name and the Value to be another <Key, Value> in a different hash table. The 2nd hash
// table will have year as its Key and another <Key, Value> as its Value. The 3rd hash table will have the company name as its Key and the Value of the number
// of complaints against that company in the year and product indicated earlier by the 1st and 2nd hash tables.
std::unordered_map<std::string, unordered_map<string,unordered_map<string,int>>> yearlyProdCompMap;  // year, product, company, total number C

// Didn't use the struct to reorder the map. But still can use if the ordering desire changes.
// Define a comparator for the map elements when we put them in a set
// However, since the default map data structure already has an order, I can use it for further
// instructions on the possible future arrangement that will be necessary for the orders.
struct myComparator
{
    template<typename T>
	bool operator()(const T& elem1, const T& elem2) const {
		if (elem1.second > elem2.second){
            return elem1.second >= elem2.second;
        }else if (elem1.second == elem2.second){
            return elem1.first < elem2.first;
        }else{
            return false;
        }
	}
};

// I used the following struct to store the relevant data, in a neat way, to
// the final result map, i.e. "map<string , map<string , info>> resultMap"  <----info
struct info{
    int complaints4YearProd = 0;
    int companies4YearProd = 0;
    int maxComplaintsAgainstOneComp = 0;
};

// Header names for the used functions
void analyzeTheHeaderOfInputFile(); // Extracts the indexes of relevant cells: i.e. "yearInd", "productInd", "companyInd" will be determined.
void readInputFileForInd (int yearInd, int productInd, int companyInd); // Extracts the data cells from each line of the input document.
void writeReport(); // writes to the output
void transToLower(string& in); // change to lower case


// The main function to run the program and glue the functions together
int main() {
    // Open the output file
	writeFile.open("../output/report.csv");
	// Initialize the indexes to be read from the input file.
    productInd = 0;
    yearInd = 0;
    companyInd = 0;

    // Reads the first line of the input file.
    // Analyzes the header of the input file so that we know the indices that are relevant and
    // we should add to the Value of the unordered_map Keys later
    analyzeTheHeaderOfInputFile();

    // Here after we know which header indices are the ones that we should count we read the rest of the input file
    readInputFileForInd(yearInd, productInd, companyInd);
    writeReport();
    // Now that we have read the input file, we close it.
    writeFile.close();
    myfile.close();

    return 0;
}

// This function reorders the relevant data based on the criteria specified in the project to be displaced.
// The resultMap will first order the data based on its first key which is the product. The value also is
// a map that will reorder based on its key which I intended for the year. Finally the values will be
// read from the resultMap and written to the output file.
void writeReport(){
    map<string,map<string,info>> resultMap;
    int count = 0;
    int maxNum = 0;
    for (auto it = yearlyProdCompMap.begin();it!=yearlyProdCompMap.end();++it){
        for (auto jt = yearlyProdCompMap[(*it).first].begin();jt!=yearlyProdCompMap[(*it).first].end();++jt){
            count = 0;
            maxNum = 0;
            for (auto kt = yearlyProdCompMap[(*it).first][(*jt).first].begin();kt!=yearlyProdCompMap[(*it).first][(*jt).first].end();++kt){
                count += (*kt).second;
                maxNum = max(maxNum,(*kt).second);
            }
            resultMap[(*jt).first][(*it).first].complaints4YearProd = count;
            resultMap[(*jt).first][(*it).first].companies4YearProd = (*jt).second.size();
            resultMap[(*jt).first][(*it).first].maxComplaintsAgainstOneComp = maxNum;
        }
    }
    for (auto it = resultMap.begin();it!=resultMap.end();++it){
        for (auto jt = resultMap[(*it).first].begin();jt!=resultMap[(*it).first].end();++jt){
            writeFile << (*it).first << "," << (*jt).first << "," << (*jt).second.complaints4YearProd  << "," << (*jt).second.companies4YearProd << "," <<setprecision(0) << fixed << (double)(*jt).second.maxComplaintsAgainstOneComp/(*jt).second.complaints4YearProd*100 << endl;
            cout << (*it).first << "," << (*jt).first << "," << (*jt).second.complaints4YearProd  << "," << (*jt).second.companies4YearProd << "," <<setprecision(0) << fixed << (double)(*jt).second.maxComplaintsAgainstOneComp/(*jt).second.complaints4YearProd*100 << endl;
        }
    }

}

// This function will extract the index numbers that are of interest: i.e. "yearInd", "productInd", "companyInd"
void analyzeTheHeaderOfInputFile(){
    // Reading the first line of the input file to extract for the headers that are important for the analysis
    // And increment variable
    int j = 0;
    int pos;
    string token;
    if (myfile.peek() != EOF) {
        getline(myfile, line);
        while ((pos = line.find(",")) != std::string::npos) {
            token = line.substr(0, pos);

            transToLower(token);
            if (token == "date received") {
                yearInd = j;
                //cout<<"yearInd::"<<j<<endl;
            }
            if (token == "product") {
                productInd = j;
                //cout<<"productInd::"<<j<<endl;
            }
            if (token == "company") {
                companyInd = j;
                //cout<<"companyInd::"<<j<<endl;
            }
            j++;
            line.erase(0, pos + 1);
        }
    }
}


// This function reads the whole input file and extracts the data
// necessary to be analyzed for the final output.
void readInputFileForInd (int yearInd, int productInd, int companyInd){
    // If the appropriate headers existed, we start counting the occupations and states that have a certified application
    // Then the occupation name will be put into a map and the certified applications will add to its value.
    // A similar approach is taken for the states map.
    int lineNum = 0;
    string row;
    line =  "";
    int pos;
    int j = 0;
    while (myfile.peek() != EOF) { // && lineNum<300 for checking only a few lines.
        j = 0;
        row = "";
        line  = "";

        // Here I will clean each line from the breaks and glue the relevant data in one line. In an immediately later while loop, I will analyze each line.
        while (myfile.peek() != EOF && j<18){
            //cout<<"h0::"<<endl;
            while (row.size()==0){
                getline(myfile,row);
            }
            if(j<17 && (pos = row.find(",")) == std::string::npos){
                line += row;
                getline(myfile,row);
                continue;
            }
            while((pos = row.find(",")) != std::string::npos || (pos = row.find('"')) != std::string::npos){
                if (row.size()>1 && row[0]=='"'){
                    while (row.find("\",") == std::string::npos){
                        if (row.size()!=0){
                            line+=row;
                        }
                        getline(myfile,row);
                        while (row.size()==0){
                            getline(myfile,row);
                        }
                    }
                    for (int i = 1;i<(int)row.size();i++){
                        if (row[i]=='"' && row[i+1]==','){
                            line+=row.substr(0,i+2);
                            row.erase(0,i+2);
                            j++;
                            break;
                        }
                    }
                    continue;
                }
                if (row.find(",") == std::string::npos){
                    break;
                }

                line+=row.substr(0,pos+1);
                row.erase(0,pos+1);
                j++;
            }
            if (j==17 && row.size()!=0){
                line += row;
                j++;
            }
        }

        // Informative messages to the cout stream
//        cout<<endl;
//        cout<<"*---------"<<endl;
//        cout<<line<<endl;
//        cout<<"----------*"<<endl;
//        cout<<endl;

        // j is the number of extracted features from the input line, initialized index from 0. Can't be greater than 17 since there can be only 18 attributes on each line
        j = 0;
        // Now I will extract each of the 18 attributes from each line till there is no more left in the line string.
        while (line.size()) {
            // I detect the position where has ", or , as an indicator for the end of the attribute value.
            if (line[0]=='"' && j<17){
                pos = line.find("\",");
                pos++;
            }else if (j<17){
                pos = line.find(",");
            }
            // Here I will get the necessary attribute values to put into the unordered map of data for the use in the result map later.
            if (j==yearInd){
                year = line.substr(0,pos);
                int loc = 0;
                while (loc<year.size()-4 && (year[loc] <48 || year[loc+1] <48 || year[loc+2] <48 || year[loc+3] <48)){ // 48 is the ASCII number for 0. i.e. CHAR(digits) > 47 for digits={0,1,2,...}
                    loc++;
                }
                year = year.substr(loc,4);
            }
            if (j==productInd){
                product = line.substr(0,pos);
                transToLower(product);
                yearlyProdMap[year][product]++;
                //cout<<"product::"<<product<<endl;
            }
            if (j==companyInd){
                company = line.substr(0,pos);
                transToLower(company); // All names are treated as case insensitive
                yearlyProdCompMap[year][product][company]++;
                //cout<<"company::"<<company<<endl;
            }
            line.erase(0,pos+1);
            j++;
            if (j==17){
                break;
            }
        }
        // Keep track of the line number we just read from the input file.
        lineNum++;
        //cout<<lineNum<<endl;
    }
}


void transToLower(string& in){
    for (int i = 0;i<in.size();i++){
        if (in[i]>64 && in[i]<91){
            in[i] +=32;
        }
    }
}
