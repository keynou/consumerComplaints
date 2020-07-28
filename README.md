# About the Author of This Repo
* Name: Keyvan Noury
* Email address: keyvan.nou@gmail.com

# Table of Contents
1. [Problem](README.md#problem)
2. [Task](README.md#task)
3. [Input Dataset](README.md#input-dataset)
4. [Instructions](README.md#instructions)
5. [Output](README.md#output)


# Problem
The consumer financial protection bureau (CFPB)'s <a href="https://cfpb.github.io/api/ccdb/fields.html" rel="nofollow">link</a> has provided the complaints information related to financial products for each company in the years of 2019 and part of 2020.
 
In this project I analyzed a huge file with the best pracitces that knew in data engineering with a c++ program (i.e. I used the proper data structure and algorithms in c++ w/o using outside libraries).

The anlaysis is particularly looking for the following output results
(each line in the output file lists the following fields in the following order):
* product (name should be written in all lowercase)
* year
* total number of complaints received for that product and year
* total number of companies receiving at least one complaint for that product and year
* highest percentage (rounded to the nearest whole number) of total complaints filed against one company for that product and year. Use standard rounding conventions (i.e., Any percentage between 0.5% and 1%, inclusive, should round to 1% and anything less than 0.5% should round to 0%)


# Task
As a data engineer, I want to analyze the data, specifically, calculate two metrics: 
1) **Number of complaints for a specific year and product** and 2) **Number of companies for a specific year and product**.
Then we are tasked to find the percentage portion of the company that has the most number of the complaints for that product and year.

# Input Dataset
**Note:** I assumed the data can have alternative columns (attributes). 
So I analyzed the column names prior to make decisions on extracting the relevant information from the attributes.
Also, the inputs have a lot of problems, including breaks and double quotes here and there that makes it difficult for the program to know where each attribute starts.
One more problem is that a company name can have different addresses. For the purposes of this project, I assumed if the company name is the same, then the two companies are actually the same.

# Instructions
*** The objective is to analyze the input file of complaints and create a list of alphabetically sorted products in a sorted list of years and show the statistics of the number of 
of complaints and number of companies and the highest percentage of the complaints that belongs to a company.

# Output 
The program creates 1 output file in the folder of ../output:
* `report.csv`: The file that includes the alphabetically sorted products in a sorted list of years and show the statistics of the number of 
of complaints and number of companies and the highest percentage of the complaints that belongs to a company.

Each line holds one record and each field on each line is separated by a semicolon (,).

Each line of the `report.csv` file contains these fields in this order:
1. __`product`__:  product (name should are written in all lowercase)
2. __`year`__: The year that the complaint was received for.
3. total number of complaints received for that product and year.
4. total number of companies receiving at least one complaint for that product and year.
5. highest percentage (rounded to the nearest whole number) of total complaints filed against one company for that product and year.

Percentages are rounded off to no decimal place. For instance, 1.54% is rounded to 2%, and 1.09% is rounded to 1%. 
Note that, the percent sign, i.e. "%", is NOT shown in the output file.

Solution safisfies the following requirements:
* Repo follows the required repo directory structure
* `run.sh` script works as is in our environment and correct results are generated.
* The code is well-commented
* `README.md` contains Problem, Approach and Run instructions sections

I used `C++` to code for the given problem and task.
a link of my Github repo with my source code was sent to the insight website.


## Repo directory structure
The directory structure for my repo looks like this:
```
insight_DE__consumerComplaints~$

		├── README.md
		├── run.sh
		├── src
		│   └── consumer_complaints.cpp
		├── input
		│   └── complaints.csv
		├── output
		|   └── report.csv
		├── insight_testsuite
			└── tests
				└── test_1
				|   ├── input
				|   │   └── complaints.csv
				|   |__ output
				|   │   └── report.csv
				├── my-own-test_1
				|	├── input
				|	│   └── complaints.csv
				|	|── output
				|		└── report.csv
				├── my-own-test_2
				|	├── input
				|	│   └── complaints.csv
				|	|── output
				|		└── report.csv
				├── my-own-test_3
				|	├── input
				|	│   └── complaints.csv
				|	|── output
				|		└── report.csv
```
The content of `src` does not need to be a single file called `consumer_complaints.cpp`. But here I used that as my program's name.

## Testing directory structure and output format

To make sure that the code has the correct directory structure and the format of the output files are correct, there is a test script called `run.sh` in the `insight_testsuite` folder.
In the run command it is indicated that I want to use STL of ```c++11``` while compiling the program. The ./run.sh is as follows:
```
cd ./src
g++  -std=c++11 consumer_complaints.cpp -o main
./main
```

The test files are stored in `.csv` format under the `insight_testsuite/tests` folder. Each test has a separate folder with an `input` folder and `complaints.csv` file and an `output` folder with the two requested output files.

You can run the test with the following command from within the `insight_testsuite` folder:

    insight_DE__consumerComplaints~$ ./run.sh 

On a failed test, the output of `run.sh` looks like this:

    [FAIL]: test_1
    [Sun Mar 29 16:28:01 PDT 2020] 0 of 1 tests passed

On success:

    [PASS]: test_1
    [Sun Mar 29 16:25:57 PDT 2020] 1 of 1 tests passed

