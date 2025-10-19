
#include "geom.h"
#include "util.h"

static double min(double a,double b){ return a<b?a:b; }
static double max(double a,double b){ return a>b?a:b; }

int interRectRect(double x1,double y1,double w1,double h1,double x2,double y2,double w2,double h2)
{
    double a1=x1, b1=y1, c1=x1+w1, d1=y1+h1;
    double a2=x2, b2=y2, c2=x2+w2, d2=y2+h2;
    if(c1<a2||c2<a1) return 0;
    if(d1<b2||d2<b1) return 0;
    return 1;
}

int interCircCirc(double x1,double y1,double r1,double x2,double y2,double r2)
{
    double dx=x2-x1, dy=y2-y1;
    double dist2=dx*dx+dy*dy;
    double rr=(r1+r2)*(r1+r2);
    return dist2<=rr;
}

static double clamp(double v,double a,double b){ if(v<a) return a; if(v>b) return b; return v; }

int interRectCirc(double rx,double ry,double rw,double rh,double cx,double cy,double r)
{
    double nx=clamp(cx,rx,rx+rw);
    double ny=clamp(cy,ry,ry+rh);
    double dx=cx-nx, dy=cy-ny;
    return dx*dx+dy*dy<=r*r;
}

double comprimento(double x1,double y1,double x2,double y2)
{
    double dx=x2-x1, dy=y2-y1;
    return util_sqrt(dx*dx+dy*dy);
}

static double cross(double ax,double ay,double bx,double by){ return ax*by-ay*bx; }

int interSegSeg(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4)
{
    double d1x=x2-x1, d1y=y2-y1, d2x=x4-x3, d2y=y4-y3;
    double d=cross(d1x,d1y,d2x,d2y);
    if(util_fabs(d)<1e-9) return 0;
    double s=cross(x3-x1,y3-y1,d2x,d2y)/d;
    double t=cross(x3-x1,y3-y1,d1x,d1y)/d;
    if(s>=0&&s<=1&&t>=0&&t<=1) return 1;
    return 0;
}

double distPontoSeg(double px,double py,double x1,double y1,double x2,double y2)
{
    double vx=x2-x1, vy=y2-y1;
    double wx=px-x1, wy=py-y1;
    double c=wx*vx+wy*vy;
    if(c<=0) return util_sqrt((px-x1)*(px-x1)+(py-y1)*(py-y1));
    double b=vx*vx+vy*vy;
    if(c>=b) return util_sqrt((px-x2)*(px-x2)+(py-y2)*(py-y2));
    double t=c/b;
    double qx=x1+t*vx, qy=y1+t*vy;
    double dx=px-qx, dy=py-qy;
    return util_sqrt(dx*dx+dy*dy);
}

int interRectSeg(double rx,double ry,double rw,double rh,double x1,double y1,double x2,double y2)
{
    if(x1>=rx&&x1<=rx+rw&&y1>=ry&&y1<=ry+rh) return 1;
    if(x2>=rx&&x2<=rx+rw&&y2>=ry&&y2<=ry+rh) return 1;
    if(interSegSeg(x1,y1,x2,y2,rx,ry,rx+rw,ry)) return 1;
    if(interSegSeg(x1,y1,x2,y2,rx,ry,rx,ry+rh)) return 1;
    if(interSegSeg(x1,y1,x2,y2,rx+rw,ry,rx+rw,ry+rh)) return 1;
    if(interSegSeg(x1,y1,x2,y2,rx,ry+rh,rx+rw,ry+rh)) return 1;
    return 0;
}
