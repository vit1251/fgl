extern BITMAP bitmap[100];

// Work with image.
//
int fglCreateImage(int id, int width, int height);
int fglDestroyImage(int id);

//
//
int GetPoint(int id, int x, int y);
int SetPoint(int id, int x, int y, COLORREF color);

//
//
int fglLoadImage(int id, char *fname);
int fglSaveImage(int id, char *fname);

// Transfering image.
//
int fglCopyImage(int dst_id, int dst_x, int dst_y, int dst_width, int dst_height, int src_id, int src_x, int src_y);
int fglCopyTransparentImage(int dst_id, int dst_x, int dst_y, int w, int h, int src_id, int src_x, int src_y, COLORREF color);
