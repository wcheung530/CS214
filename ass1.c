#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "scannerCSVsorter.h"
#include <dirent.h>


int main(int argc, char* argv[]){
	
	int colFlag = 0;
	int inDirFlag = 0;
	int outDirFlag = 0;
	char* colName = (char*)malloc(100*sizeof(char));
	char* inputDirectory = (char*)malloc(100*sizeof(char));
	char* outputDirectory = (char*)malloc(100*sizeof(char));
	char **a = argv;
	int copied1 = 0;
	int copied2 = 0;
	int copied3 =0;

	DIR *dir;
	struct dirent *sd;

	//This Opens current directory; (const char *filename)
	dir = opendir (".");  

	//Checking if Directory is valid
	if(dir == NULL){
		printf("Error, Unable to open directory.  May be invalid. \n");
		exit(1);
	}
	//This will print out all the directories including parents
	while( (sd=readdir(dir)) != NULL){
		printf(">>%s\n", sd -> d_name);
	}

	//iterate argv to check for flags and arguments

	for (a = argv ; a < argv+argc ; a++) {
	   
	        if((strcmp(*a,"-c")==0) && (colFlag == 0)){
	        	colFlag = 1;

	        	if((a+1) < (argv+argc)){
	        		if( (strcmp( *(a+1), "-d") == 0) || (strcmp( *(a+1), "-o") == 0)){
	        		//printf("error: flag raised but no column name provided\n");
	        		write(STDERROR, "error: flag raised but no column name provided\n", 50);
	        		return 0;
	        		}
	        	}
	        	else if ( (a+1) == (argv+argc)){
		        	//printf("error: flag raised but no column name provided\n");
		        	write(STDERROR, "error: flag raised but no column name provided\n", 50);
		        	return 0;
		        }
	        	
				continue;
	    	}

	    	else if((strcmp(*a,"-d")==0) && (inDirFlag == 0)){
	        	inDirFlag = 1;

	        	if((a+1) < (argv+argc)){
		        	if( (strcmp( *(a+1), "-c") == 0) || (strcmp( *(a+1), "-o") == 0)){
		        		//printf("error: flag raised but no input directory name provided\n");
		        		write(STDERROR, "error: flag raised but no input directory name provided\n", 57);
		        		
		        		return 0;
		        	}
		        }
		        else if ( (a+1) == (argv+argc)){
		        	//printf("error: flag raised but no input directory name provided\n");
		        	write(STDERROR, "error: flag raised but no input directory name provided\n", 57);
		        	
		        	return 0;
		        }

				continue;
	    	}

	    	else if((strcmp(*a,"-o")==0) && (outDirFlag == 0)){
	        	outDirFlag = 1;

	        	if((a+1) < (argv+argc)){
		        	if( (strcmp( *(a+1), "-c") == 0) || (strcmp( *(a+1), "-d") == 0)){
		        		//printf("error: flag raised but no output directory name provided\n");
		        		write(STDERROR, "error: flag raised but no output directory name provided\n" , 58);
		        		return 0;
		        	}
		        }
		        else if ( (a+1) == (argv+argc)){
		        	//printf("error: no output directory name provided\n");
		        	write(STDERROR, "error: flag raised but no output directory name provided\n" , 58);
		        	return 0;
		        }

				continue;
	    	}

	    	// END of checking flags, start of checking arguments

	    	if((colFlag == 1) && (copied1 == 0)){
	    		strcpy(colName, *a);
			copied1 = 1;
			continue;
	    	}

	    	else if((inDirFlag == 1) && (copied2 == 0)){
	    		strcpy(inputDirectory, *a);
			copied2 = 1;
			continue;
	    	}

	    	else if((outDirFlag == 1) && (copied3 == 0)){
	    		strcpy(outputDirectory, *a);
			copied3 = 1;
			continue;
	    	}
		
	}

	if( (strcmp(colName,"director_name")!=0)&&(strcmp(colName,"num_critic_for_reviews")!=0)&&(strcmp(colName,"duration")!=0)&&(strcmp(colName,"director_facebook_likes")!=0)&&(strcmp(colName,"actor_3_facebook_likes")!=0)&&(strcmp(colName,"actor_2_name")!=0)&&(strcmp(colName,"actor_1_facebook_likes")!=0)&&(strcmp(colName,"gross")!=0)&&(strcmp(colName,"genres")!=0)&&(strcmp(colName,"actor_1_name")!=0)&&(strcmp(colName,"movie_title")!=0)&&(strcmp(colName,"num_voted_users")!=0)&&(strcmp(colName,"cast_total_facebook_likes")!=0)&&(strcmp(colName,"actor_3_name")!=0)&&(strcmp(colName,"facenumber_in_poster")!=0)&&(strcmp(colName,"plot_keywords")!=0)&&(strcmp(colName,"movie_imdb_link")!=0)&&(strcmp(colName,"num_user_for_reviews")!=0)&&(strcmp(colName,"language")!=0)&&(strcmp(colName,"country")!=0)&&(strcmp(colName,"content_rating")!=0)&&(strcmp(colName,"budget")!=0)&&(strcmp(colName,"title_year")!=0)&&(strcmp(colName,"actor_2_facebook_likes")!=0)&&(strcmp(colName,"imdb_score")!=0)&&(strcmp(colName,"aspect_ratio")!=0)&&(strcmp(colName,"movie_facebook_likes")!=0) ){


		//printf("error, column name is not a valid column name\n");
		char* hi = "error, column name is not a valid column name\n";
		write(STDERROR, hi, 46);

		return 0;
	}




	if (colFlag == 0){
		char* colFlagerror = "Error: -c argument was not included\n";
		//printf("%s\n", colFlagerror);
		write(STDERROR, colFlagerror, 37);
		return 0;
	}  

	
	printf("colFlag: %d, inDirFlag: %d, outDirFlag: %d\n", colFlag, inDirFlag, outDirFlag);
	printf("Input column: %s, Input directory: %s, Output directory: %s\n", colName, inputDirectory, outputDirectory);
	free(colName);
	free(inputDirectory);
	free(outputDirectory);
	
	//close Directory
	closedir(dir);

	return 0;
	/*
	//checking for "-c <column name>" format"

	if(argc<3){
		printf("error, not enough arguments, your format is incorrect\n");
		return 0;
	}

	if(strcmp(argv[1],"-c")!=0){
		colFlag = 0;
		printf("error, your second argument is not -c\n");
		return 0;
	}

	if( (strcmp(argv[2],"director_name")!=0)&&(strcmp(argv[2],"num_critic_for_reviews")!=0)&&(strcmp(argv[2],"duration")!=0)&&(strcmp(argv[2],"director_facebook_likes")!=0)&&(strcmp(argv[2],"actor_3_facebook_likes")!=0)&&(strcmp(argv[2],"actor_2_name")!=0)&&(strcmp(argv[2],"actor_1_facebook_likes")!=0)&&(strcmp(argv[2],"gross")!=0)&&(strcmp(argv[2],"genres")!=0)&&(strcmp(argv[2],"actor_1_name")!=0)&&(strcmp(argv[2],"movie_title")!=0)&&(strcmp(argv[2],"num_voted_users")!=0)&&(strcmp(argv[2],"cast_total_facebook_likes")!=0)&&(strcmp(argv[2],"actor_3_name")!=0)&&(strcmp(argv[2],"facenumber_in_poster")!=0)&&(strcmp(argv[2],"plot_keywords")!=0)&&(strcmp(argv[2],"movie_imdb_link")!=0)&&(strcmp(argv[2],"num_user_for_reviews")!=0)&&(strcmp(argv[2],"language")!=0)&&(strcmp(argv[2],"country")!=0)&&(strcmp(argv[2],"content_rating")!=0)&&(strcmp(argv[2],"budget")!=0)&&(strcmp(argv[2],"title_year")!=0)&&(strcmp(argv[2],"actor_2_facebook_likes")!=0)&&(strcmp(argv[2],"imdb_score")!=0)&&(strcmp(argv[2],"aspect_ratio")!=0)&&(strcmp(argv[2],"movie_facebook_likes")!=0) ){
		printf("error, input valid column name\n");
		return 0;
	}

	//checking for "-d <input directory>" format

	if(strcmp(argv[3],"-d")!=0){
		inDirFlag = 0;
		printf("input directory not specified; searching current directory\n");
		
	}

	if(strcmp(argv[5], "-o" != 0)){
		outDirFlag = 0;
		printf("output directory not specified; sending results to source code directory\n");
	}
	else if()*/
}
