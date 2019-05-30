/* Project2.cpp
 * Santhosh Saravanan
 * EE312, Spring 2019
 * Project 2, Matrix Multiplication
 */
 // matrix-multiplication <Project2.cpp>
 // EE 312 Project 2 submission by
 // <Santhosh Saravanan>
 // <sks3648>
 // Slip days used: <0>
 // Spring 2019
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "MatrixMultiply.h"

void multiplyMatrices(
	double a[],
	const uint32_t a_rows,
	const uint32_t a_cols,
	double b[],
	const uint32_t b_cols,
	double c[]) {
	/* https://en.wikipedia.org/wiki/Row-_and_column-major_order  */
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < a_rows)
	{
		while (j < b_cols)
		{
			c[i * b_cols + j] = 0;
			while (k < a_cols)
			{
				c[i* b_cols + j] += a[i* a_cols + k] * b[k* b_cols + j];
				k++;
			}
			k = 0;
			j++;
		}
		j = 0;
		i++;	
	}
}

double** multiplyMatricesPtr(
	double** a,
	const uint32_t a_rows,
	const uint32_t a_cols,
	double** b,
	const uint32_t b_cols) {
	double**resultingMatrix;
	int i = 0;
	int j = 0;
	int k = 0;
	resultingMatrix = (double**)malloc(a_rows * sizeof(double*));
	for (int i = 0; i < a_rows; i++)
	{
		resultingMatrix[i] = (double*)malloc(b_cols * sizeof(double));
	}
	for (int i = 0; i < a_rows; i++)
	{
		for (int j = 0; j < b_cols; j++)
		{
			resultingMatrix[i][j] = 0;
			for (int k = 0; k < a_cols; k++)
			{
				resultingMatrix[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return resultingMatrix;
}

// https://en.wikipedia.org/wiki/Transpose
double** transposeMatrix(
	double** a,
	const uint32_t a_rows,
	const uint32_t a_cols) {
	double** doda;
	int i = 0;
	int j = 0;
	doda = (double**)malloc(a_cols * sizeof(double*));
	for (int i = 0; i < a_cols; i++)
	{
		doda[i] = (double*)malloc(a_rows * sizeof(double));
	}
	for (int i = 0; i < a_rows; i++)
	{
		for (int j = 0; j < a_cols; j++)
		{
			doda[j][i] = a[i][j];
		}
	}
	return doda;
}
