
#ifndef GEOM_H
#define GEOM_H
int interRectRect(double x1,double y1,double w1,double h1,double x2,double y2,double w2,double h2);
int interCircCirc(double x1,double y1,double r1,double x2,double y2,double r2);
int interRectCirc(double rx,double ry,double rw,double rh,double cx,double cy,double r);
int interSegSeg(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4);
int interRectSeg(double rx,double ry,double rw,double rh,double x1,double y1,double x2,double y2);
double distPontoSeg(double px,double py,double x1,double y1,double x2,double y2);
double comprimento(double x1,double y1,double x2,double y2);
#endif
