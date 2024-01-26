#include <stdio.h>
#include <math.h>
#include <string.h>

double selectFunction(double operand1, double operand2, char operatorParam) {
	double result;
	
	if (strcmp(&operatorParam, "*") == 0) {
		result = operand1 * operand2;
		printf("Result: %f %c %f = %f\n", operand1, operatorParam, operand2, result);
	} 
	else if (strcmp(&operatorParam, "/") == 0) {
		result = operand1 / operand2;
		printf("Result: %f %c %f = %f\n", operand1, operatorParam, operand2, result);
	} 
	else if (strcmp(&operatorParam, "+") == 0) {
		result = operand1 + operand2;
		printf("Result: %f %c %f = %f\n", operand1, operatorParam, operand2, result);
	} 
	else if (strcmp(&operatorParam, "^") == 0) {
		result = pow(operand1, operand2);
		printf("Result: %f %c %f = %f\n", operand1, operatorParam, operand2, result);
	} 
	else if (strcmp(&operatorParam, "-") == 0) {
		result = operand1 - operand2;
		printf("Result: %f %c %f = %f\n", operand1, operatorParam, operand2, result);
	}
	else if (strcmp(&operatorParam, "%") == 0) {
		result = fmod(operand1, operand2);
		printf("Result: %f %c %f = %f\n", operand1, operatorParam, operand2, result);
	}
	else {
		printf("Invalid operator: %c\n", operatorParam);//Displays an error message
	}
}

int main(int argc, char **argv) {
	double num1, num2;
	char operand;
	
	printf("| -------------------------------- CALCULATOR -------------------------------- |\nEnter a number: ");
	scanf("%lf", &num1);
	
	printf("Enter one of the following operators *, +, /, -, ^, %%:");
	scanf(" %c", &operand);
	
	printf("Enter another number: ");
	scanf("%lf", &num2);
	
	selectFunction(num1, num2, operand);
	
	return 0;
}
