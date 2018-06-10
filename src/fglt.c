/* DONE (Vit1251#1#): Реализовать стек видовых матриц */
/* DONE (Vit1251#1#): Перемножение матриц через стек и т.п. */
/* TODO (Vit1251#1#): Внутренний интерфейс для переключения проекций */

#include <windows.h>
#include <malloc.h>

#include "fglt.h"

// Definition.

double dm[4][4];                     // View Matrix

struct _stack *stack=NULL;           // Transformation stack

// Translation

void _mmul1(double rm[4][4], double cc[4]);

/*
int mmul1(rm, cc)
double rm[4][4];
double cc[4];
{
	int col;
	int row;

	float tt[4];

	// Zero.
	for(row=0;row<4;row++) {
		tt[row] = 0.0f;
	}

	// Multiplay.
	for(row=0;row<4;row++) {
		float sum;
		sum=0.0f;

		for (col=0;col<4;col++) {
			// Save the summ.
			sum += rm[row][col] * cc[col];
		}

		tt[row]=sum;
	}

	// Zero.
	for(row=0;row<4;row++) {
		cc[row] = tt[row];
	}

	return 0;
}
*/

void _mmul1(rm, cc)
double rm[4][4];
double cc[4];
{
	double tt[4];
	int i;
	
	tt[0] = rm[0][0]*cc[0] + rm[0][1]*cc[1] + rm[0][2]*cc[2] + rm[0][3]*cc[3];
	tt[1] = rm[1][0]*cc[0] + rm[1][1]*cc[1] + rm[1][2]*cc[2] + rm[1][3]*cc[3];
	tt[2] = rm[2][0]*cc[0] + rm[2][1]*cc[1] + rm[2][2]*cc[2] + rm[2][3]*cc[3];
	tt[3] = rm[3][0]*cc[0] + rm[3][1]*cc[1] + rm[3][2]*cc[2] + rm[3][3]*cc[3];
	
	for(i=0; i < 4; i++) {
		cc[i] = tt[i];
	}
}

// Matrix default, math, stack and etc.

int fglLoadIdentity()
{
	dm[0][0]=1.0f; dm[0][1]=0.0f; dm[0][2]=0.0f; dm[0][3]=0.0f;
	dm[1][0]=0.0f; dm[1][1]=1.0f; dm[1][2]=0.0f; dm[1][3]=0.0f;
	dm[2][0]=0.0f; dm[2][1]=0.0f; dm[2][2]=1.0f; dm[2][3]=0.0f;
	dm[3][0]=0.0f; dm[3][1]=0.0f; dm[3][2]=0.0f; dm[3][3]=1.0f;

	return 0;
}

int fglMultMatrix()
{
	double rm[4][4];
	double mm[4][4];

	struct _stack *top=stack;

	int x,y;
	int i;

	// Load matrix.
	
	memcpy(&mm, stack->matrix, sizeof(mm));

	// Delete from stack.

	free(top->matrix);
	top=stack->next;
	free(stack);

	stack=top;
	
	// Set as zero.

	for(y=0;y<4;y++) {
		for (x=0;x<4;x++) {
			rm[y][x]=0.0f;
		}
	}

	// Multiplay.

	for(y=0;y<4;y++) {
		for (x=0;x<4;x++) {

			for(i=0;i<4;i++)
				rm[y][x] += mm[y][i] * dm[i][x];
		}
	}

	// Transfer result.

	for(y=0;y<4;y++) {
		for (x=0;x<4;x++) {
			dm[y][x]=rm[y][x];
		}
	}

	return 0;
}

// Stack

int fglLoadMatrix(tm)
long tm[4][4];
{
	struct _stack *top=NULL;

	top=malloc(sizeof(stack));
	top->matrix = malloc(sizeof(double[4][4]));
	memcpy(top->matrix, tm, sizeof(double[4][4]));
	top->next=stack;

	stack=top;

	return 0;	
}

int fglPushMatrix()
{
	struct _stack *top=NULL;

	top=malloc(sizeof(stack));
	top->matrix = malloc(sizeof(double[4][4]));
	memcpy(top->matrix, dm, sizeof(double[4][4]));
	top->next=stack;

	stack=top;

	return 0;
}

int fglPopMatrix()
{
	struct _stack *top=stack;

	if (top != NULL) {

		memcpy(dm, top->matrix, sizeof(double[4][4]));
		free(top->matrix);
		top=stack->next;
		free(stack);

		stack=top;
	} else
	MessageBox(0, "Stack is free", "Error", MB_ICONERROR|MB_OK);

	return 0;
}

// Rotate, translate and scale.

int fglRotateX(double angle)
{
	double tm[4][4];

	double ca = cosf(angle);
	double sa = sinf(angle);

	tm[0][0]=1.0f; tm[0][1]=0.0f; tm[0][2]=0.0f; tm[0][3]=0.0f;
	tm[1][0]=0.0f; tm[1][1]= ca ; tm[1][2]= sa;  tm[1][3]=0.0f;
	tm[2][0]=0.0f; tm[2][1]= -sa; tm[2][2]= ca;  tm[2][3]=0.0f;
	tm[3][0]=0.0f; tm[3][1]=0.0f; tm[3][2]=0.0f; tm[3][3]=1.0f;

	fglLoadMatrix(tm);
	fglMultMatrix();

	return 0;
}

int fglRotateY(double angle)
{
	double tm[4][4];

	double ca = cosf(angle);
	double sa = sinf(angle);

	tm[0][0]= ca ; tm[0][1]=0.0f; tm[0][2]=-sa ; tm[0][3]=0.0f;
	tm[1][0]=0.0f; tm[1][1]=1.0f; tm[1][2]=0.0f; tm[1][3]=0.0f;
	tm[2][0]= sa ; tm[2][1]=0.0f; tm[2][2]= ca ; tm[2][3]=0.0f;
	tm[3][0]=0.0f; tm[3][1]=0.0f; tm[3][2]=0.0f; tm[3][3]=1.0f;

	fglLoadMatrix(tm);
	fglMultMatrix();

	return 0;
}

int fglRotateZ(double angle)
{
	double tm[4][4];

	double ca = cosf(angle);
	double sa = sinf(angle);

	tm[0][0]= ca ; tm[0][1]= sa ; tm[0][2]=0.0f; tm[0][3]=0.0f;
	tm[1][0]=-sa ; tm[1][1]= ca ; tm[1][2]=0.0f; tm[1][3]=0.0f;
	tm[2][0]=0.0f; tm[2][1]=0.0f; tm[2][2]=1.0f; tm[2][3]=0.0f;
	tm[3][0]=0.0f; tm[3][1]=0.0f; tm[3][2]=0.0f; tm[3][3]=1.0f;

	fglLoadMatrix(tm);
	fglMultMatrix();

	return 0;
}


int fglTranslate(double dx, double dy, double dz)
{
	double tm[4][4];

	tm[0][0]=1.0f; tm[0][1]=0.0f; tm[0][2]=0.0f; tm[0][3]=dx;
	tm[1][0]=0.0f; tm[1][1]=1.0f; tm[1][2]=0.0f; tm[1][3]=dy;
	tm[2][0]=0.0f; tm[2][1]=0.0f; tm[2][2]=1.0f; tm[2][3]=dz;
	tm[3][0]=0.0f; tm[3][1]=0.0f; tm[3][2]=0.0f; tm[3][3]=1.0f;

	fglLoadMatrix(tm);
	fglMultMatrix();

	return 0;
}

int fglScale(double mx, double my, double mz)
{
	double tm[4][4];

	tm[0][0]=mx;   tm[0][1]=0.0f; tm[0][2]=0.0f; tm[0][3]=0.0f;
	tm[1][0]=0.0f; tm[1][1]=my;   tm[1][2]=0.0f; tm[1][3]=0.0f;
	tm[2][0]=0.0f; tm[2][1]=0.0f; tm[2][2]=mz;   tm[2][3]=0.0f;
	tm[3][0]=0.0f; tm[3][1]=0.0f; tm[3][2]=0.0f; tm[3][3]=1.0f;

	fglLoadMatrix(tm);
	fglMultMatrix();

	return 0;
}
