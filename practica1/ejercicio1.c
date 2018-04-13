#include <stdio.h>

int g=65, z=4;

int f(int *x, int y){
	static int c=5;
	//printf("*x = %i , y = %i \n", *x, y );
	//printf("*(x+1) = %i\n",*(x+1));
	return *(x+1)+y+(c++);
}

int main(void)
{
	int a[5] = {1,2,3,4,5};
	/*printf("%p\n",a);
	printf("%p\n",a+1);
	printf("%p\n",a+2);
	printf("%p\n",a+3);
	printf("%p\n",a+4);
	printf("%p\n",a+5);
	printf("SOn iguales =,%i\n",(a==&(a[0])));
	printf("%s\n","-----------");*/
	//int r = f(a,a[0]) + f(&g, a[g]);
	int r =  f(&g, a[g]);
	printf("r = %d\n",r);
	return r;
}
