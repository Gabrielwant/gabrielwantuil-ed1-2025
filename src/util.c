
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h>
#endif

int util_strlen(const char* s){ int n=0; if(!s) return 0; while(s[n]!='\0') n++; return n; }
int util_strcmp(const char* a, const char* b){ int i=0; if(!a&&!b) return 0; if(!a) return -1; if(!b) return 1; while(a[i]&&b[i]){ if(a[i]!=b[i]) return (unsigned char)a[i]-(unsigned char)b[i]; i++; } if(a[i]==b[i]) return 0; return a[i]=='\0'?-1:1; }
void util_copy(char* dst, const char* src, int maxn){ int i=0; if(!dst) return; if(!src){ dst[0]='\0'; return; } while(src[i] && i<maxn){ dst[i]=src[i]; i++; } dst[i]='\0'; }
void util_join3(char* dst, const char* a, const char* b, const char* c, int maxn){ int i=0,j=0; if(!dst) return; if(a){ while(a[j]&&i<maxn){ dst[i++]=a[j++]; } } j=0; if(i<maxn&&b){ while(b[j]&&i<maxn){ dst[i++]=b[j++]; } } j=0; if(i<maxn&&c){ while(c[j]&&i<maxn){ dst[i++]=c[j++]; } } if(i>maxn) i=maxn; dst[i]='\0'; }
void util_ensure_dir(const char* path) {
    if(!path) return;
#ifdef _WIN32
    _mkdir(path);
#else
    mkdir(path, 0777);
#endif
}
int util_max(int a,int b){ return a>b?a:b; }
double util_fabs(double x){ return x<0?-x:x; }
double util_sqrt(double x){ double r=x; if(x<=0) return 0; double z=1; for(int i=0;i<40;i++){ z=0.5*(z+x/z); } return z; }
double util_atof(const char* s){ int i=0,sg=1; double v=0,dec=0,fac=1; if(!s) return 0; if(s[0]=='-'){ sg=-1; i++; } while(s[i]>='0'&&s[i]<='9'){ v=v*10+(s[i]-'0'); i++; } if(s[i]=='.'){ i++; while(s[i]>='0'&&s[i]<='9'){ fac*=10; dec=dec*10+(s[i]-'0'); i++; } } return sg*(v+dec/fac); }
int util_atoi(const char* s){ int i=0,sg=1,v=0; if(!s) return 0; if(s[0]=='-'){ sg=-1; i++; } while(s[i]>='0'&&s[i]<='9'){ v=v*10+(s[i]-'0'); i++; } return sg*v; }
int util_snprintf(char* dst,int maxn,const char* fmt,double v){ return snprintf(dst,maxn,fmt,v); }
