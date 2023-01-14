#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double function_x (double x);
double chord_method (double x1, double x2, double eps, int iterations_option, int N);
double div_method (double x1, double x2, double eps, int iterations_option, int N);

int main()
{
    double x1;
    double x2;
    double eps;
    double timer;
    int choose_method;
    int choose_iterations_count;
    int N;
    time_t start;
    time_t end;
    do
    {
        printf("Choose your method\n");
        printf("1 - Chord Method\n");
        printf("2 - Half-Division Method\n");
        scanf("%d", &choose_method);
    }
    while(choose_method != 1 && choose_method != 2);
    do
    {
        printf("Count number of iterations?\n");
        printf("1 - Yes\n");
        printf("2 - No\n");
        scanf("%d", &choose_iterations_count);
        if(choose_iterations_count == 1)
        {
            do
            {
                printf("Number of allowed iterations: ");
                scanf(" %d", &N);
            }
            while(N < 1);
        }
    }
    while(choose_iterations_count != 1 && choose_iterations_count != 2);
    printf("Enter your:\n");
    while(function_x(x1) * function_x(x2) > 0)
    {
        printf("x1 - first point\n");
        scanf("%lf", &x1);
        printf("x2 - second point\n");
        scanf("%lf", &x2);
    }
    printf("error threshold\n");
    scanf("%lf", &eps);
    start = clock();
    switch(choose_method)
    {
    case 1:
        printf("xi = %lf\n", chord_method (x1, x2, eps, choose_iterations_count, N));
        break;
    case 2:
        printf("xi = %lf\n", div_method (x1, x2, eps, choose_iterations_count, N));
        break;
    }
    end = clock();
    timer = (end - start);
    if(choose_iterations_count == 2)
    {
        printf("Timer: %lfms\n", timer);
    }
    return 0;
}

double function_x(double x)
{
    return pow(x / 100 - 5 , 5) - pow(x / 50 + 10, 4) - pow(x / 25 - 15, 3) - pow(x, 2) - 10;
}

double chord_method (double x1, double x2, double eps, int choose_iterations_count, int N)
{
    double xi;
    int i = 0;
    while(fabs(function_x(xi)) > eps)
    {
        xi = (function_x(x2) * x1 - function_x(x1) * x2) / (function_x(x2) - function_x(x1));
        if (function_x(xi) * function_x(x1) > 0)
        {
            x1=xi;
        }
        else
        {
            x2=xi;
        }
        if(choose_iterations_count==1)
        {
            printf("xi = %lf\n", xi);
            i++;
            if(i>=N)
            {
                i=0;
                int choose_iterations;
                do
                {
                    printf("Iterations are done, but xi isn't done yet.\n");
                    printf("1 - Another %u iterations\n", N);
                    printf("2 - Finish after xi is found\n");
                    printf("3 - Display results and exit\n");
                    scanf("%d", &choose_iterations);
                }
                while (choose_iterations != 1 && choose_iterations != 2 && choose_iterations != 3);
                switch(choose_iterations)
                {
                case 1:
                    break;
                case 2:
                    choose_iterations_count=2;
                    break;
                case 3:
                    return xi;
                    break;
                }
            }
        }
    }
    return xi;
}

double div_method (double x1, double x2, double eps, int choose_iterations_count, int N)
{
    double xi;
    int i = 0;
    while(fabs(x2 - x1) >= eps)
    {
        xi = (x1 + x2) / 2;
        if(function_x(xi) == 0)
        {
            break;
        }
        else if(function_x(xi) * function_x(x1) > 0)
        {
            x1 = xi;
        }
        else
        {
            x2 = xi;
        }
        if(choose_iterations_count == 1)
        {
            printf("xi = %lf\n", xi);
            i++;
            if(i >= N)
            {
                i = 0;

                int choose_iterations;
                do
                {
                    printf("Iterations are done, but xi isn't done yet.\n");
                    printf("1 - Another %u iterations\n", N);
                    printf("2 - Finish after xi is found\n");
                    printf("3 - Display results and exit\n");
                    scanf("%d", &choose_iterations);
                }
                while (choose_iterations != 1 && choose_iterations != 2 && choose_iterations != 3);
                switch(choose_iterations)
                {
                case 1:
                    break;
                case 2:
                    choose_iterations_count = 2;
                    break;
                case 3:
                    return xi;
                    break;
                }
            }
        }
    }
    return xi;
}
