//including header files
#include <stdio.h>
#include <string.h>

int main(void)
{
    //getting card number
    long long int n = 0;
    printf("number: ");
    scanf("%lld", &n);
    
    //calculating sum of digits in odd places
    long A = 10;
    long a = n%A;
    long B = 1000;
    long b = n%B;
    long z = b/100;
    long C = 100000;
    long c = n%C;
    long y = c/10000;
    long D = 10000000;
    long d = n%D;
    long x = d/1000000;
    long E = 1000000000;
    long e = n%E;
    long w = e/100000000;
    long F = 100000000000;
    long f = n%F;
    long v = f/10000000000;
    long G = 10000000000000;
    long g = n%G;
    long u = g/1000000000000;
    long H = 1000000000000000;
    long h = n%H;
    long t = h/100000000000000;
    long ops = a+z+y+x+w+v+u+t;

    //calculating sum of digits in even places as pe rule
    long I = 100;
    long II = n%I;
    long iii = II/10;
    long ii = iii*2;
    long i = (ii/10) + (ii%10);
    long J = 10000;
    long JJ = n%J;
    long jjj = JJ/1000;
    long jj = jjj*2;
    long j = (jj/10) + (jj%10);
    long K = 1000000;
    long KK = n%K;
    long kkk = KK/100000;
    long kk = kkk*2;
    long k = (kk/10) + (kk%10);
    long L = 100000000;
    long LL = n%L;
    long lll = LL/10000000;
    long ll = lll*2;
    long l = (ll/10) + (ll%10);
    long M = 10000000000;
    long MM = n%M;
    long mmm = MM/1000000000;
    long mm = mmm*2;
    long m = (mm/10) + (mm%10);
    long O = 1000000000000;
    long OO = n%O;
    long ooo = OO/100000000000;
    long oo = ooo*2;
    long o = (oo/10) + (oo%10);
    long P = 100000000000000;
    long PP = n%P;
    long ppp = PP/10000000000000;
    long pp = ppp*2;
    long p = (pp/10) + (pp%10);
    long Q = 10000000000000000;
    long QQ = n%Q;
    long qqq = QQ/1000000000000000;
    long qq = qqq*2;
    long q = (qq/10) + (qq%10);

    long eps = i+j+k+l+m+o+p+q;

    //getting sum of card acc to rules and validating card with remainder zero when divided by 10
    long sum = ops+eps;

    long s = sum%10;

    //finding wether card is valid or invalid and its name if it is valid
    if (s==0)
    {
        if (n>=340000000000000)
        {
            if (n<350000000000000)
            {
                printf("AMEX\n");
            }
        }
        if (n>=370000000000000)
        {
            if (n<=380000000000000)
            {
                printf("AMEX\n");
            }
        }
        if (n>=5100000000000000)
        {
            if (n<5600000000000000)
            {
                printf("MASTERCARD\n");
            }
        }
        if (n>=4000000000000)
        {
            if (n<5000000000000)
            {
                printf("VISA\n");
            }
        }
        if (n>=4000000000000000)
        {
            if (n<5000000000000000)
            {
                printf("VISA\n");
            }
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

