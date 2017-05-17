#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <gtk/gtk.h>



#include<opencv2/opencv.hpp>

using namespace cv;


#define BUFFERLEN 2000*2000*3*4
int main (int argc, char **argv)
{
	 gtk_init (&argc, &argv);
    //Init variables
	GdkPixbuf *screenshot;
    GdkWindow *root_window;
    gint x_orig, y_orig;
    gint width, height;
	
	//Get the screenshot.
    root_window = gdk_get_default_root_window ();
    gdk_drawable_get_size (root_window, &width, &height);      
    gdk_window_get_origin (root_window, &x_orig, &y_orig);
    screenshot = gdk_pixbuf_get_from_drawable (NULL, root_window, NULL, x_orig, y_orig, 0, 0, width, height);
		 
 
	screenshot = gdk_pixbuf_get_from_drawable (NULL, root_window, NULL, x_orig, y_orig, 0, 0, width, height);
	
	
	unsigned char *buf = (unsigned char*)malloc(BUFFERLEN*sizeof(unsigned char));
	memset(buf,0 ,BUFFERLEN*sizeof(unsigned char));
	
	char windowName[] = "screenSnap";
	int n = 0;
	while(1)
	{
		n++;
		screenshot = gdk_pixbuf_get_from_drawable (NULL, root_window, NULL, x_orig, y_orig, 0, 0, width, height);
		
		int cv_width = gdk_pixbuf_get_width(screenshot);
		int cv_height = gdk_pixbuf_get_height(screenshot);
		int cv_nChannels = gdk_pixbuf_get_n_channels(screenshot);
		int cv_step = gdk_pixbuf_get_rowstride(screenshot);
		guchar *pSrcBuffer= gdk_pixbuf_get_pixels(screenshot);
		unsigned char *pDst= buf;
		unsigned char *pTemp = NULL;
		int i,j;
		
		for(i = 0; i < cv_height; ++i)
		{
			//printf("in  1-for\n");
			
			for(j = 0; j < cv_width; ++j)
			{
				//printf("cv_width = %d, cv_height = %d, n = %d, i = %d, j = %d\n",cv_width,cv_height,n,i,j);
				pTemp = (unsigned char *)pSrcBuffer+ i*cv_step +j;
				pDst[0] = pTemp[0];
				pDst[1] = pTemp[1];
				pDst[2] = pTemp[2];
				
				pDst += 3;
				pTemp += 3;
				
			}
		}
		
	
		Mat frame(cv_height,cv_width,CV_8UC3,buf);
		resize(frame,frame,cvSize(640,480),0,0,INTER_LINEAR);
		imshow(windowName,frame);
		waitKey(30);
		
		g_object_unref(screenshot);
		
	}	

}

