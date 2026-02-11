#ifdef maths_STATIC
#define MATHSLIB_API // 静态链接时，宏为空
#else
#ifdef MATHS_EXPORTS
#define MATHSLIB_API __declspec(dllexport)
#else
#define MATHSLIB_API __declspec(dllimport)
#endif
#endif

MATHSLIB_API int add(int a, int b);