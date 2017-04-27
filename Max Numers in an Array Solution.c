#include <stdio.h>

/*Write a C function that takes an array of integers and the length of that array (which can be anything from 3 to 100) as input and returns the largest 3 values in the array.
Then, write a unit test function that exercises the above function.
*/

void printArray(int *nums,int length)	{
	int i;
	for(i=0;i<length;i++)	{
		if(i<length-1)	{
			printf("%d ",nums[i]);
		}	else	{
			printf("%d",nums[i]);
		}
	}
}

void sort(int *toSort, int length)	{
	int i,j;
	for(i=length-1;i>=0;i--)	{
		for(j=1;j<=i;j++)	{
			if(toSort[j-1]<toSort[j])	{
				int tmp=toSort[j-1];
				toSort[j-1]=toSort[j];
				toSort[j]=tmp;
			}
		}
	}
}

int findThreeMax(int *nums, int length, int *bigThree, int numToFind, int maxInts)	{
	int i,j;
	int lessThanThree=0;
	int moreThanHundred=0;
	int errorCode=0;
	
	//If an array is passed with less than 3 integers, add in zeros to make it 3 integers, and return error code 1
	if(length<numToFind)	{
		printf("ERROR: Only %d integers in array. Array will be padded with zeroes until it has 3 integers.\n",length);
		lessThanThree=1;
		errorCode=1;
		for(i=0;i<length;i++)	{
			bigThree[i]=nums[i];
		}
		for(i=numToFind-1;i>length-1;i--)	{
			bigThree[i]=0;
		}
		sort(bigThree,numToFind);
		return errorCode;
	}
	
	//If an array is passed with more than 100 integers, print an error message and return zeroes and error code 2
	if(length>maxInts)	{
		moreThanHundred=1;
		errorCode=2;
		printf("ERROR: More than 100 integers in array. Max is 100 integers. Output defaults to \"0 0 0\".\n");
		for(i=0;i<numToFind;i++)	{
			bigThree[i]=0;
		}
		return errorCode;
	}

	//Initialize bigThree with the first three values in nums, sorted with the greatest in position 0
	for(i=0;i<numToFind;i++)	{
		bigThree[i]=nums[i];
	}
	sort(bigThree,numToFind);
	
	//Go through the rest of the items, and add then to the array, sorted	
	for(i=numToFind;i<length;i++)	{
		if(nums[i]>bigThree[numToFind-1])	{
			bigThree[numToFind-1]=nums[i];
			sort(bigThree,numToFind);
		}
	}
	return errorCode;
}

//This function carries out all the work for testing and formatting the output
int printTestInfo(int length, int *array, int testNum, int *expected, int numToFind, int maxInts,int expectedFail)	{
	int i;
	int largest[numToFind];
	int errorCode=0;
	
	//Write the array to be parsed to the console
	printf("\n%d: Testing array of length %d with values of {",testNum,length);
	printArray(array,length);
	printf("}\n");
	
	//Write the expected output to the console
	printf("Expected output is \"");
	printArray(expected,numToFind);
	printf("\"\n");
	
	//Process the array and output the biggest three numbers in it
	errorCode=findThreeMax(array,length,largest,numToFind,maxInts);
	printf("Result %d: ",testNum);
	printArray(largest,numToFind);
	printf("\n");
	
	//Check to make sure that the right error code was returned from the function
	//Return an error if the wrong error code was returned
	if(errorCode!=expectedFail)	{
		printf("TEST FAILED, wrong error code\n");
		errorCode=3;
		return errorCode;
	}
	
	//If the right error code was returned, we can now check to make sure the biggest three numers were found as expected
	errorCode=0;
	for(i=0;i<numToFind;i++)	{
		if(expected[i]!=largest[i])	{
			printf("TEST FAILED, max ints not found\n");
			errorCode=3;
		}
	}
	
	//If the right error code was returned and the biggest three numbers were found, the test passed
	if(errorCode!=3)	{
		printf("TEST PASSED\n");
	}
	return errorCode;
}

int main()	{
	int numToFind=3;
	int maxInts=100;
	
	//Test 3 dissimilar items
	int failed1=0;
	int array1[]={0,-1,1};
	int expectedArray[]={1,0,-1};
	if(printTestInfo(sizeof(array1)/sizeof(array1[0]),array1,1,expectedArray,numToFind,maxInts,failed1))	{
		printf("\nFAILED TEST\n");
		return 1;
	}
	
	//Test just 3 items, all the same
	int array2[]={0,0,0};
	int failed2=0;
	expectedArray[0]=0;
	expectedArray[1]=0;
	expectedArray[2]=0;
	if(printTestInfo(sizeof(array2)/sizeof(array2[0]),array2,2,expectedArray,numToFind,maxInts,failed2))	{
		printf("\nFAILED TEST\n");
		return 1;
	}
	
	//Test 3 items of the same value, followed by one less than the rest
	int array3[]={-1,-1,-1,-2};
	int failed3=0;
	expectedArray[0]=-1;
	expectedArray[1]=-1;
	expectedArray[2]=-1;
	if(printTestInfo(sizeof(array3)/sizeof(array3[0]),array3,3,expectedArray,numToFind,maxInts,failed3))	{
		printf("\nFAILED TEST\n");
		return 1;
	}
	
	//Test a long string of numbers, with high numbers replacing numbers in the bigThree array
	int array4[]={0,-10,40,1,1,1,1,34,100,10000,-60};
	int failed4=0;
	expectedArray[0]=10000;
	expectedArray[1]=100;
	expectedArray[2]=40;
	if(printTestInfo(sizeof(array4)/sizeof(array4[0]),array4,4,expectedArray,numToFind,maxInts,failed4))	{
		printf("\nFAILED TEST\n");
		return 1;
	}
	
	//Test a decreasing string of numbers
	int array5[]={5,4,3,2,1,0,-1,-2,-3};
	int failed5=0;
	expectedArray[0]=5;
	expectedArray[1]=4;
	expectedArray[2]=3;
	if(printTestInfo(sizeof(array5)/sizeof(array5[0]),array5,5,expectedArray,numToFind,maxInts,failed5))	{
		printf("\nFAILED TEST\n");
		return 1;
	}
	
	//Test an increasting string of numbers
	int array6[]={-2,-1,0,1,2,3,4};
	int failed6=0;
	expectedArray[0]=4;
	expectedArray[1]=3;
	expectedArray[2]=2;
	if(printTestInfo(sizeof(array6)/sizeof(array6[0]),array6,6,expectedArray,numToFind,maxInts,failed6))	{
		printf("\nFAILED TEST\n");
		return 1;
	}
	
	//Test an array of 2 with the first smallest
	int array7[]={10,20};
	int failed7=1;
	expectedArray[0]=20;
	expectedArray[1]=10;
	expectedArray[2]=0;
	if(printTestInfo(sizeof(array7)/sizeof(array7[0]),array7,7,expectedArray,numToFind,maxInts,failed7))	{
		printf("\nFAILED TEST\n");
		return 1;
	}
	
	//Test an array of 2 with the first largest
	int array8[]={-1,-2};
	int failed8=1;
	expectedArray[0]=0;
	expectedArray[1]=-1;
	expectedArray[2]=-2;
	if(printTestInfo(sizeof(array8)/sizeof(array8[0]),array8,8,expectedArray,numToFind,maxInts,failed8))	{
		printf("\nFAILED TEST\n");
		return 1;
	}
	
	//Test an array of 1
	int array9[]={-9};
	int failed9=1;
	expectedArray[0]=0;
	expectedArray[1]=0;
	expectedArray[2]=-9;
	if(printTestInfo(sizeof(array9)/sizeof(array9[0]),array9,9,expectedArray,numToFind,maxInts,failed9))	{
		printf("\nFAILED TEST\n");
		return 1;
	}
	
	//Test an array of 0
	int array10[]={};
	int failed10=1;
	expectedArray[0]=0;
	expectedArray[1]=0;
	expectedArray[2]=0;
	if(printTestInfo(sizeof(array10)/sizeof(array10[0]),array10,10,expectedArray,numToFind,maxInts,failed10))	{
		printf("\nFAILED TEST\n");
		return 1;
	}
	
	//Test an array greater than the limit
	int array11[]={1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1};
	int failed11=2;
	expectedArray[0]=0;
	expectedArray[1]=0;
	expectedArray[2]=0;
	if(printTestInfo(sizeof(array11)/sizeof(array11[0]),array11,11,expectedArray,numToFind,maxInts,failed11))	{
		printf("\nFAILED TEST\n");
		return 1;
	}
	
	printf("\nPASSED ALL TESTS\n");
	return 0;
}