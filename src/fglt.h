// Structure.

struct _stack {
	void *matrix;
	struct _stack *next;
};

// Definition.

extern double dm[4][4];                     // View Matrix

// Translation and rotation.
int fglLoadIdentity(void);
int fglPopMatrix(void);
int fglPushMatrix(void);
int fglTranslate(double dx, double dy, double dz);
int fglRotateX(double angle);
int fglRotateY(double angle);
int fglRotateZ(double angle);
int fglScale(double mx, double my, double mz);
