
#ifndef UTIL_H
#define UTIL_H
int util_strlen(const char* s);
int util_strcmp(const char* a, const char* b);
void util_copy(char* dst, const char* src, int maxn);
void util_join3(char* dst, const char* a, const char* b, const char* c, int maxn);
void util_ensure_dir(const char* path);
int util_max(int a, int b);
double util_fabs(double x);
double util_sqrt(double x);
double util_atof(const char* s);
int util_atoi(const char* s);
int util_snprintf(char* dst, int maxn, const char* fmt, double v);
#endif
