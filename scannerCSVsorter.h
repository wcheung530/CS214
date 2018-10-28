#define STDERROR 2



//I would like to use an array of this struct in order to sort using mergeSort
struct Node{
	//the data being compared must either be integer or string
	int intData;
	char* stringData;

	//this is the full string so we can just print it out line by line and output the file
	char* fullString;	
};
void mergeStr(struct Node *arr,int start,int middle,int end, struct Node *temp1, struct Node *temp2){
        int arraySize1 = middle-start+1;
        int arraySize2 = end-middle;

        int i;
        for(i=0; i<arraySize1;i++){
                strcpy(temp1[i].stringData,arr[start+i].stringData);
                strcpy(temp1[i].fullString,arr[start+i].fullString);
        }

        int j;
        for(j=0; j<arraySize2;j++){
                strcpy(temp2[j].stringData,arr[middle+1+j].stringData);
		strcpy(temp2[j].fullString,arr[middle+1+j].fullString);
        }


        i=0; j=0;
        int k=start;

        while(i<arraySize1 && j<arraySize2){
                if(strcmp(temp1[i].stringData,temp2[j].stringData) < 0){
                	strcpy(arr[k].stringData,temp1[i].stringData);
			strcpy(arr[k].fullString,temp1[i].fullString);
	                i++;
                }
                else{
                	strcpy(arr[k].stringData,temp2[j].stringData);
			strcpy(arr[k].fullString,temp2[j].fullString);
                    j++;
                }
                k++;
        }

        while(i<arraySize1){
                strcpy(arr[k].stringData,temp1[i].stringData);
		strcpy(arr[k].fullString,temp1[i].fullString);
                i++;k++;
        }

	while(j<arraySize2){
		strcpy(arr[k].stringData,temp2[j].stringData);
		strcpy(arr[k].fullString,temp2[j].fullString);
		j++;k++;
	}

}

void mergesortStr(struct Node *arr, int start, int end,struct Node *temp1, struct Node *temp2){
        if(start<end){
                int middle = (start+end)/2;

                mergesortStr(arr,start,middle,temp1,temp2);
                mergesortStr(arr,middle+1,end,temp1,temp2);
                mergeStr(arr,start,middle,end,temp1,temp2);
        }
}



//merge sort for integers
void mergeInt(struct Node *arr,int start,int middle,int end, struct Node *temp1, struct Node *temp2){
        int arraySize1 = middle-start+1;
        int arraySize2 = end-middle;

        int i;
        for(i=0; i<arraySize1;i++){
                temp1[i].intData = arr[start+i].intData;
                strcpy(temp1[i].fullString,arr[start+i].fullString);
        }
        int j;
        for(j=0; j<arraySize2;j++){
                temp2[j].intData = arr[middle+1+j].intData;
		strcpy(temp2[j].fullString,arr[middle+1+j].fullString);
        }


        i=0; j=0;
        int k=start;

        while(i<arraySize1 && j<arraySize2){
                if(temp1[i].intData<temp2[j].intData){
                        arr[k].intData = temp1[i].intData;
			strcpy(arr[k].fullString,temp1[i].fullString);
                        i++;
                }
                else{
                        arr[k].intData = temp2[j].intData;
			strcpy(arr[k].fullString,temp2[j].fullString);
                        j++;
                }
                k++;
        }

        while(i<arraySize1){
                arr[k].intData=temp1[i].intData;
		strcpy(arr[k].fullString,temp1[i].fullString);
                i++;k++;
        }

	while(j<arraySize2){
		arr[k].intData=temp2[j].intData;
		strcpy(arr[k].fullString,temp2[j].fullString);
		j++;k++;
	}

}

void mergesortInt(struct Node *arr, int start, int end,struct Node *temp1, struct Node *temp2){
        if(start<end){
                int middle = (start+end)/2;

                mergesortInt(arr,start,middle,temp1,temp2);
                mergesortInt(arr,middle+1,end,temp1,temp2);
                mergeInt(arr,start,middle,end,temp1,temp2);
        }
}

char* formatOutput(char* inputfile, char* inputColumn, char* outputDir){
	///////formatting output to "<inputfile>-sorted-<inputColumn>.csv"

	char* outputfile = (char*)malloc(1000*sizeof(char));
	char* cat0 = (char*)malloc(100*sizeof(char));
	char* cat1 = (char*)malloc(100*sizeof(char));
	char* cat2 = (char*)malloc(100*sizeof(char));
	char* cat3 = (char*)malloc(100*sizeof(char));
	char* cat4 = (char*)malloc(100*sizeof(char));
	char* cat5 = (char*)malloc(100*sizeof(char));
	char* cat6 = (char*)malloc(100*sizeof(char));

	//making copies of inputfile and inputcolumn
	char* tempinputfile = (char*)malloc(100*sizeof(char));
	char* tempinputColumn = (char*)malloc(100*sizeof(char));
	char* tempoutputDir = (char*)malloc(100*sizeof(char));
	strcpy(tempinputfile, inputfile);
	strcpy(tempinputColumn, inputColumn);
	strcpy(tempoutputDir, outputDir);
	
	//concatenating all the strings together
	//strcpy(cat0, "");
	strcpy(cat1, tempoutputDir);
	//cat1 = strcat(cat0, tempoutputDir);
	cat2 = strcat(cat1, "/");
	
			//trimming ".csv" off the tempinputfile name
			char *ptr;
			ptr = strstr(tempinputfile, ".csv");
			if (ptr != NULL) {
		    	*ptr = '\0';
			}

	cat3 = strcat(cat2, tempinputfile);
	cat4 = strcat(cat3, "-sorted-");
	cat5 = strcat(cat4, tempinputColumn);
	cat6 = strcat(cat5, ".csv");
	strcpy(outputfile, cat6);

	printf("%s\n", outputfile);
	return outputfile;
}

//this function returns 0 if a file is a valid csv file and returns -1 if invalid file
int checkcsv(char* inputfile){

	if(strstr(inputfile, ".csv") == NULL){
		fprintf(stderr,"Not a csv file, ignore and skip this one\n");
		return -1;
	}
	//read the file for the first time to check for valid columns

	FILE* myFile0 = fopen(inputfile, "r");

	int lineNum = 0; ////used to check each line of a file
	char *line = NULL;
	size_t line_size;
	int i= 0; //for loop increment int
	int j = 0;
	int res1 = 0; //counts number of occurrences of a character in first line
	int res2 = 0; //counts number of occurrences of a character in all the following lines
	char* tmp;
	char* tmp2;
	int ignoreComma = 0; //int for counting number of ' " ' in a line. this is for the case that theres a comma in a field

	while( getline(&line, &line_size, myFile0 ) != -1 ){		
		if(lineNum == 0){
			
			tmp = line; //temp ptr to line buffer of the very first line
			//printf("%s\n", tmp);

			//checks if the csv file has all the required columns. Otherwise report bad csv file
			if( (strstr(tmp,"color")==NULL)||(strstr(tmp,"director_name")==NULL)||(strstr(tmp,"num_critic_for_reviews")==NULL)||(strstr(tmp,"duration")==NULL)||(strstr(tmp,"director_facebook_likes")==NULL)||(strstr(tmp,"actor_3_facebook_likes")==NULL)||(strstr(tmp,"actor_2_name")==NULL)||(strstr(tmp,"actor_1_facebook_likes")==NULL)||(strstr(tmp,"gross")==NULL)||(strstr(tmp,"genres")==NULL)||(strstr(tmp,"actor_1_name")==NULL)||(strstr(tmp,"movie_title")==NULL)||(strstr(tmp,"num_voted_users")==NULL)||(strstr(tmp,"cast_total_facebook_likes")==NULL)||(strstr(tmp,"actor_3_name")==NULL)||(strstr(tmp,"facenumber_in_poster")==NULL)||(strstr(tmp,"plot_keywords")==NULL)||(strstr(tmp,"movie_imdb_link")==NULL)||(strstr(tmp,"num_user_for_reviews")==NULL)||(strstr(tmp,"language")==NULL)||(strstr(tmp,"country")==NULL)||(strstr(tmp,"content_rating")==NULL)||(strstr(tmp,"budget")==NULL)||(strstr(tmp,"title_year")==NULL)||(strstr(tmp,"actor_2_facebook_likes")==NULL)||(strstr(tmp,"imdb_score")==NULL)||(strstr(tmp,"aspect_ratio")==NULL)||(strstr(tmp,"movie_facebook_likes")==NULL) ){
				fprintf(stderr,"error, bad csv file, this file does not have all the required columns\n");
				return -1;
			}
			for(i = 0; i<strlen(tmp); i++){

				if (tmp[i] == ',') {
        		res1++;         
        		}
			}
			//printf("comma count for the first line : %d\n", res1);

  		
  			lineNum++;
		}

		else if(lineNum > 0){
			tmp2 = line; //temp ptr to line buffer of the 2nd line
			//fprintf(stderr,"%s\n", tmp2);
			for(j = 0; j<strlen(tmp2); j++){

				if(tmp2[j] == '"'){
					ignoreComma++;
				}

				if ((tmp2[j] == ',') && (ignoreComma % 2 == 0)) {
        		res2++;          	
        		}

			}
			lineNum++;

			//printf("comma count for line %d: %d\n", lineNum, res2);
  		
  			if(res1 == res2){
  				//printf("same number of commas LETS GET THIS FUKIN BREAD\n");
  				
  				res2 = 0;
  				tmp2 = NULL; 	//reset values of tmp2 and res2

  				continue;
  			}
  			else if ( res1 != res2 ){
  				fprintf(stderr,"the columns are messed up, don't use this csv file\n");
  				pclose(myFile0);
  				return -1;
  			}  			  			
		}

		else {
			lineNum++;
		}
	}
	pclose(myFile0);
	return 0;
}

//handles the sorting of an input file. Returns 0 on sucess, and -1 for failure
int csvfilehandler(char* inputfile, char* inputColumn, char* outputDir){
	
	//printf("%s\n", inputColumn );

	int checkcsv1 = checkcsv(inputfile);
	if(checkcsv1 == -1){
		fprintf(stderr, "inputfile is not a valid csv file\n");
		return -1;
	}
	
	//must be a valid columnName from the movie_metadata
	
	if( (strcmp(inputColumn,"color")!=0) && (strcmp(inputColumn,"director_name")!=0)&&(strcmp(inputColumn,"num_critic_for_reviews")!=0)&&(strcmp(inputColumn,"duration")!=0)&&(strcmp(inputColumn,"director_facebook_likes")!=0)&&(strcmp(inputColumn,"actor_3_facebook_likes")!=0)&&(strcmp(inputColumn,"actor_2_name")!=0)&&(strcmp(inputColumn,"actor_1_facebook_likes")!=0)&&(strcmp(inputColumn,"gross")!=0)&&(strcmp(inputColumn,"genres")!=0)&&(strcmp(inputColumn,"actor_1_name")!=0)&&(strcmp(inputColumn,"movie_title")!=0)&&(strcmp(inputColumn,"num_voted_users")!=0)&&(strcmp(inputColumn,"cast_total_facebook_likes")!=0)&&(strcmp(inputColumn,"actor_3_name")!=0)&&(strcmp(inputColumn,"facenumber_in_poster")!=0)&&(strcmp(inputColumn,"plot_keywords")!=0)&&(strcmp(inputColumn,"movie_imdb_link")!=0)&&(strcmp(inputColumn,"num_user_for_reviews")!=0)&&(strcmp(inputColumn,"language")!=0)&&(strcmp(inputColumn,"country")!=0)&&(strcmp(inputColumn,"content_rating")!=0)&&(strcmp(inputColumn,"budget")!=0)&&(strcmp(inputColumn,"title_year")!=0)&&(strcmp(inputColumn,"actor_2_facebook_likes")!=0)&&(strcmp(inputColumn,"imdb_score")!=0)&&(strcmp(inputColumn,"aspect_ratio")!=0)&&(strcmp(inputColumn,"movie_facebook_likes")!=0) ){
		//fprintf(stderr, "printing inputColumn: %s\n", inputColumn );

		fprintf(stderr, "error, your third argument is not a valid &&&&& column name\n");
		return -1;
	}

	//is column we are sorting int? this int is 0 if false, 1 if true
	int isInt=0;

	if((strcmp(inputColumn,"num_critic_for_reviews")==0)||(strcmp(inputColumn,"duration")==0)||(strcmp(inputColumn,"director_facebook_likes")==0)||(strcmp(inputColumn,"actor_3_facebook_likes")==0)||(strcmp(inputColumn,"actor_1_facebook_likes")==0)||(strcmp(inputColumn,"gross")==0)||(strcmp(inputColumn,"num_voted_users")==0)||(strcmp(inputColumn,"cast_total_facebook_likes")==0)||(strcmp(inputColumn,"facenumber_in_poster")==0)||(strcmp(inputColumn,"num_user_for_reviews")==0)||(strcmp(inputColumn,"budget")==0)||(strcmp(inputColumn,"title_year")==0)||(strcmp(inputColumn,"actor_2_facebook_likes")==0)||(strcmp(inputColumn,"imdb_score")==0)||(strcmp(inputColumn,"aspect_ratio")==0)||(strcmp(inputColumn,"movie_facebook_likes")==0)){
		isInt = 1;
	}

	FILE *myFile;
	
	myFile = fopen(inputfile, "r");

        if(myFile == NULL){
                fprintf(stderr,"Failed to open and read the file.\n");
		return -1;
        }

	int c;

	//this buf String will hold the whole row
	int bufSize = 64;
	char* buf = (char *)malloc(bufSize*sizeof(char));
	int temp = bufSize;

	//this String only holds the desired data from column being compared
	char* compareC = (char *)malloc(bufSize*sizeof(char));
	//int y is indexing for compareC
	int y=0;	

	int charIndex = 0;

	//counts number of commas in current line
	int commaCount=0;

	//keeps count of line number in original file
	int lineCount=0;
	
	//tells how many commas have passed until it htis the field that wants to be sorted
	int commaColSort=-1;


	//array of Nodes so that list can be sorted
	struct Node* myArray = malloc(1024*1024*sizeof(struct Node));
	

	//this one only exists to stop if statement from running
	int tempbreak = 0;

	//counts total chars to be able to realloc
	int totalChar=0;	

	//this int will be the conditional to tell stringData to take in ',' if its part of the value being compared
	int takeComma = 0;
	

	//read to end of file
	while((c=fgetc(myFile))!=EOF){

		
		if(totalChar<bufSize){
			buf[charIndex] = c;
		}

		if(totalChar == bufSize){
			char *hold = realloc(buf, 2*bufSize);
			if(hold == NULL){
				fprintf(stderr,"realloc() error: memory was not correctly allocated\n");
				return -1;
			}
			buf=hold;
			bufSize*=2;

			buf[charIndex]=c;
		}

		//this set of conditionals finds how many commas passes before the matched column is found
		if((lineCount==0)&&((c==',')||(c=='\n'))){
			
			//columnName found, store # commas we must parse before getting the wanted field
			if((strstr(buf,inputColumn)!=NULL)&&(tempbreak==0)){
				commaColSort = commaCount;
				tempbreak = 1;
			}

			if(c==','){
				++commaCount;
			}
			
			//columnName we are sorting cannot be found
			if((strstr(buf,inputColumn)==NULL)&&(c=='\n')){
				fprintf(stderr,"The indicated column can not be found, please put valid column name\n");
				return -1;
			}
		}

		//this is for the condition where we have " " for values with commas in them
	        if(c=='"'){
                        if(takeComma==0){
        	                takeComma=1;
                        }
                        else{
                                takeComma=0;
                        }
	        }

		//past the 1st line, check whats in the selected column and store that data
		if(lineCount>0){

			//if we passed correct number of commas, we can start passing in this part of string
			if(commaColSort == commaCount){
				if((c!=' ')&&(c!='\n')){

					if(y==temp){
						char *hold2 = realloc(compareC, 2*temp);
						if(hold2 == NULL){
							fprintf(stderr,"realloc() error: memory was not correctly allocated\n");
							return -1;
						}
						compareC = hold2;
						temp*=2;
					}
					if(c!='"'){
						compareC[y] = c;
						y++;
					}
				}
				//this situation takes care of the last column field
				if(c=='\n'){
					compareC[y]='\0';
				}
			}


			//we have passed the portion where we want to compare, so stop passing string in
			if(commaColSort<commaCount){
				compareC[y-1] = '\0';
			}

			if((c==',')&&(takeComma==0)){
				++commaCount;
			}

		}



		++totalChar;
		++charIndex;

		//end of the line, completes the string with \0 and stores the whole string
		if(c=='\n'){
			--charIndex;
			buf[charIndex]='\0';
		
			myArray[lineCount].fullString = malloc(charIndex*sizeof(struct Node));
			strcpy(myArray[lineCount].fullString,buf);
			
			//if column being compared is chars
			if(isInt==0){
				myArray[lineCount].stringData = malloc(charIndex*sizeof(struct Node));
				strcpy(myArray[lineCount].stringData,compareC);
			}

			//if column being compared is int, need to trim whats being compared
			if(isInt==1){
				myArray[lineCount].intData = atoi(compareC);
			}

			charIndex=0;

			//printf("Current line:%i; stored portion:%s; whole line:%s\n",lineCount,compareC,myArray[lineCount].fullString);
			//printf("Current line:%i; stored portion:%i; whole line:%s\n",lineCount,myArray[lineCount].intData,myArray[lineCount].fullString);

			++lineCount;
			commaCount = 0;
			tempbreak=0;
			y=0;
		}

	}
        struct Node* temp1=malloc(lineCount*sizeof(struct Node));
        struct Node* temp2=malloc(lineCount*sizeof(struct Node));
	
	int j;
	for(j=0;j<lineCount;j++){
		temp1[j].fullString = malloc(bufSize*sizeof(struct Node));
		temp2[j].fullString = malloc(bufSize*sizeof(struct Node));
	}


	free(buf);
	free(compareC);

	if(isInt==1){
		mergesortInt(myArray,1,lineCount-1,temp1,temp2);
	}

	if(isInt==0){
		int f;
		for(f=0;f<lineCount;f++){
			temp1[f].stringData = malloc(bufSize*sizeof(struct Node));
			temp2[f].stringData = malloc(bufSize*sizeof(struct Node));
		}
		mergesortStr(myArray,1,lineCount-1,temp1,temp2);
	}

	
	//creating sorted file in given output directory
	
	FILE* output = fopen(formatOutput(inputfile, inputColumn, outputDir), "w");
	if(output == NULL){
		printf("Error: output directory does not exist\n ");
		return -2;
	}
	
	fprintf(output,"%s\n",myArray[0].fullString);

	int z;
	for(z=1;z<lineCount;z++){
		//printf("%i\n",myArray[z].intData);
		//printf("%s\n",myArray[z].stringData);
		fprintf(output,"%s\n",myArray[z].fullString);
	}

	
	free(temp1);
	free(temp2);

	
	pclose(output);
	pclose(myFile);
	
	

	return 0;
}

