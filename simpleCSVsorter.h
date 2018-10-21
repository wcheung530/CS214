/*****
*
*	Define structures and function prototypes for your sorter
*
*
*
******/

//Suggestion: define a struct that mirrors a record (row) of the data set


//Suggestion: prototype a mergesort function



//I would like to use an array of this struct in order to sort using mergeSort
struct Node{
	//the data being compared must either be integer or string
	int intData;
	char* stringData;

	//this is the full string so we can just print it out line by line and output the file
	char* fullString;	
};
