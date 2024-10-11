#include "cub_math.h"
#include <stdio.h>
#include <math.h>



int mat_create(uint8_t rows, uint8_t cols, cub_mat *res)
{
	if (rows == 0 || cols == 0)
	{
		return 0;
	}

	if ((rows > MAX_ROWS) || (cols > MAX_COLS))
	{
		return 0;
	}

	res->rows = rows;
	res->cols = cols;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			res->data[i][j] = 0.0f;
		}
	}

	return 1;
}


int mat_create_sq(uint8_t size, cub_mat* res)
{
	return create_mat(size, size, res);
}

int mat_create_id(uint8_t size, cub_mat* res)
{
	int success = mat_create_sq(size, res);

	if (!success)
	{
		return 0;
	}

	for (int i = 0; i < size; i++)
	{
		res->data[i][i] = 1.0f;
	}

	return 1;
}


int mat_eq_dim(cub_mat* A, cub_mat* B) 
{
	return (A->rows == B->rows) && (A->cols == B->cols);
}

int mat_eq(cub_mat* A, cub_mat* B, double tolerance)
{
	int success = mat_eq_dim(A, B);

	if (!success)
	{
		return 0;
	}

	for (int i = 0; i < A->rows; i++)
	{
		for (int j = 0; j < A->rows; j++)
		{
			if (fabs(A->data[i][j] - B->data[i][j]) > tolerance)
			{
				return 0;
			}
		}
	}
}

/* Get a column with 0 based index */
int mat_get_col(cub_mat* A, uint8_t col, cub_mat* res)
{
	if (col >= A->cols)	
	{
		return 0;
	}

	int success = mat_create(A->rows, 1, res);

	if (!success)
	{
		return 0;
	}

	for (int i = 0; i < res->rows; i++)
	{
		res->data[i][0] = A->data[i][col];
	}
	
	return 1;
}

int mat_set_all(cub_mat* A, float val)
{
	for (int i = 0; i < A->rows; i++)
	{
		for (int j = 0; j < A->cols; j++)
		{
			A->data[i][j] = val;
		}
	}
	return 1;
}

int mat_set_diag(cub_mat*A, float val)
{
	int success = mat_is_sq(A);
	
	if (!success)
	{
		return 0;
	}

	for (int i = 0; i < A->rows; i++)
	{
		for (int j = 0; j < A->cols; j++)
		{
			if (i == j)
			{
				A->data[i][j] = val;
			}
		}
	}
	return 1;
}


int mat_get_row(cub_mat* A, uint8_t row, cub_mat* res)
{
	if (row >= A->rows)
	{
		return 0;
	}

	mat_create(1, A->cols, res);
	for (int j = 0; j < res->cols; j++)
	{
		res->data[0][j] = A->data[row][j];
	}
	return 1;
}


int mat_is_sq(cub_mat* A)
{
	return A->cols == A->rows;
}


/**************************/
/* Non-embedded functions */
/**************************/

#if !EMBEDDED

/* Read matrices from a file */
int mat_fromfile(FILE* f, cub_mat* res)
{
	uint8_t num_rows, num_cols = 0;
	fscanf(f, "%d", &num_rows);
	fscanf(f, "%d", &num_cols);
	mat_create(num_rows, num_cols, res);

	for (int i = 0; i < num_rows; i++)
	{
		for (int j = 0; j < num_cols; j++)
		{
			fscanf(f, "%1f\t", res->data[i][j]);
		}
	}
	return 1;
}

/* Print to stdout */
int mat_print(cub_mat* A)
{
	return mat_printf(A, "1f\t\t");
}

int mat_printf(cub_mat* A, const char* f_dmt)
{
	fprintf(stdout, "\n");

	for (int i = 0; i < A->rows; i++)
	{
		for (int j = 0; j < A->cols; j++)
		{
			fprintf(stdout, f_dmt, A->data[i][j]);
		}
		fprintf(stdout, "\n");
	}
	fprintf(stdout, "\n");
	return 1;
}

#endif 
