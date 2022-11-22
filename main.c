#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

#define eps 0.0001

unsigned int method_select(void);
double fun(double x);//функція
void print_result(double a, double b, unsigned int n, double I);// інтеграл
double left_rectangle(double a, double b, unsigned int n);//ліві прямокутники
double right_rectangle(double a, double b, unsigned int n);//праві прямокутники
double trapezoid(double a, double b, unsigned int n);//трапеції
double simpson(double a, double b, unsigned int n);//сімсон

int main()
{
  unsigned int num_of_method;
  double a, b, I, I1, I2;
  unsigned int n, N=0;

  printf("\n\n Введіть нижню границю:" );
  scanf("%lf", &a);
  printf("\n\n Введіть верхню границю:" );
  scanf("%lf", &b);
  printf("\n\n Введіть кількість проміжків:" );
  scanf("%d", &n);

  num_of_method = method_select();

  if (num_of_method ==1){
        I=left_rectangle(a, b, n);
        print_result(a,b,n,I);
        do{
          N=N+2;
          I1=left_rectangle(a, b, N);
          I2=left_rectangle(a, b, N+2);
        }
        while( fabs(I1-I2) > eps );

        printf("\n N=%u, I1(N)=%lf", N, I1);

 }else if (num_of_method ==2){
        I=right_rectangle(a, b, n);
        print_result(a,b,n,I);
        do{
          N=N+2;
          I1=right_rectangle(a, b, N);
          I2=right_rectangle(a, b, N+2);
        }
        while( fabs(I1-I2) > eps );

        printf("\n N=%u, I1(N)=%lf", N, I1);

  }else if (num_of_method ==3){
        I=trapezoid(a, b, n);
        print_result(a,b,n,I);
        do{
          N=N+2;
          I1=trapezoid(a, b, N);
          I2=trapezoid(a, b, N+2);
        }
        while( fabs(I1-I2) > eps );

        printf("\n N=%u, I1(N)=%lf", N, I1);
  }
  else{
        I=simpson(a,b,n);
        print_result(a,b,n,I);
        do{
         N=N+2;
         I1 = simpson(a, b, N);
         I2 = simpson(a, b, N+2);
        }
        while( fabs(I2-I1) > eps );
        printf("\nN= %u I(N)= %lf", N, I1);
  }
    return 0;
}

//***************************************************

unsigned int method_select(void)
{
   unsigned int temp;

    printf("\n\n Введіть ваш метод:\n1 - ліві \n2 - праві \n3 - трапеція \n4 - сімпсона\n");
    scanf("%u", &temp);

   while( temp < 1 || temp > 4 ){

    printf("\n Помилка. Введіть коректне значення:");
    scanf("%u", &temp);
  }
   return temp;
}

//***************************************************

double fun(double x){//обрахунок функції

  double y;
  y=pow(2,x)+pow(x,2);
  return y;
}

//***************************************************

double left_rectangle(double a, double b, unsigned int n){

  double h;//приріст
  unsigned int k;
  double x;
  double sum = 0;

  h = ( b-a )/n;
  x = a;
  for(k = 0; k <= n-1; k++){

    sum = sum + fun(x);
    x = x + h;
  }
  return sum * h;
}

//***************************************************

double right_rectangle(double a, double b, unsigned int n){

    double h;
    unsigned int k;
    double x;
    double sum = 0;

    h=(b-a)/n;
    x=a+h;
    for(k=0; k<=n; k++){

        sum = sum + fun(x);
        x = x + h;
    }
    return sum * h;
}

//***************************************************

double trapezoid(double a, double b, unsigned int n){

    double sum = 0, x = 0, h;
    unsigned int k;
    h=(b-a)/n;
    x=a+h;
    for(k=0; k<=(n-1); k++){
        sum += (fun(x) + fun(x+h))/2;
        x+=h;
    }
    return sum * h;

}

//***************************************************

double simpson(double a, double b, unsigned int n){

    double sum1 = 0, sum2 = 0, h=0;
    unsigned int k;
    h=(b-a)/n;
    for(k=0; k<(n-1); k++){
        if(k%2==0){
            sum1 += fun(a + h*k);
        }else {
            sum2 += fun(a + h*k);
        }
    }
    return (fun(a)+fun(b) + 4*sum1 + 2*sum2)*h/3;

}

//***************************************************

void print_result(double a, double b, unsigned int n, double I){

  system("cls");

  printf("\n\n ********************************");
  printf("\n *            Result            *");
  printf("\n ********************************");

  printf("\n a=%.2lf b=%.2lf n=%u I=%.6lf", a, b, n, I);

}

