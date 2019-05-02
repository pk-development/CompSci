// Liang-Barsky function by Daniel White @ http://www.skytopia.com/project/articles/compsci/clipping.html
// This function inputs 8 numbers, and outputs 4 new numbers (plus a boolean value to say whether the clipped line is drawn at all).
//
#include <iostream>
#include <math.h>

bool LiangBarsky (double xmin, double xmax, double ymin, double ymax,   // Define the x/y clipping values for the border.
                  double x1, double y1, double x2, double y2,                 // Define the start and end points of the line.
                  double &x0clip, double &y0clip, double &x1clip, double &y1clip)         // The output values, so declare these outside.
{
    
    double t0 = 0.0;    double t1 = 1.0;
    double xdelta = x2-x1;
    double ydelta = y2-y1;
    double p,q,r;

    for(int edge=0; edge<4; edge++) {   // Traverse through left, right, bottom, top edges.
        if (edge==0) {  p = -xdelta;    q =  x1 - xmin;  }
        if (edge==1) {  p = xdelta;     q =  xmax-x1; }
        if (edge==2) {  p = -ydelta;    q =  y1 - ymin;}
        if (edge==3) {  p = ydelta;     q =  ymax - y1; }   
        r = q/p;
        if(p==0 && q<0) return false;   // Don't draw line at all. (parallel line outside)

        if(p<0) {
            if(r>t1) return false;         // Don't draw line at all.
            else if(r>t0) t0=r;            // Line is clipped!
        } else if(p>0) {
            if(r<t0) return false;      // Don't draw line at all.
            else if(r<t1) t1=r;         // Line is clipped!
        }
    }

    x0clip = x1 + t0*xdelta;
    y0clip = y1 + t0*ydelta;
    x1clip = x1 + t1*xdelta;
    y1clip = y1 + t1*ydelta;

    return true;        // (clipped) line is drawn
}

int main(int argc , char** argv) {
	double x1,y1,x2,y2;
	
	double xx1 = atof(argv[1]);
	double yy1 = atof(argv[2]);
	double xx2 = atof(argv[3]);
	double yy2 = atof(argv[4]);
	
	double xmin = atof(argv[5]);
	double xmax = atof(argv[6]);
	double ymin = atof(argv[7]);
	double ymax = atof(argv[8]);
	
	LiangBarsky(xmin, xmax, ymin, ymax,
	xx1, yy1, xx2, yy2, 
	x1, y1, x2, y2);
	
	std::cout << "(" << round(x1) << "," << round(y1) << ")" << ": (" << round(x2) << "," << round(y2) << ")" << std::endl;
	return 0;
}
