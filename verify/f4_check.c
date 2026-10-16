#include <stdio.h>
#include <stdlib.h>

/* Independent verifier: f4_check <N> <file>
   File = string of '0'/'1', one char per value 1..N (extra chars ignored).
   Prints number of monochromatic in-range 4-cubes. Exit 1 if any. */

static unsigned char col[200000];

int main(int argc,char**argv){
    int N=atoi(argv[1]);
    FILE*fp=fopen(argv[2],"r");
    if(!fp){fprintf(stderr,"no file\n");return 2;}
    int ch,i=0;
    while((ch=fgetc(fp))!=EOF){ if(ch=='0'||ch=='1'){ col[++i]=ch-'0'; if(i>=N) break; } }
    fclose(fp);
    if(i<N){fprintf(stderr,"colouring too short: have %d need %d\n",i,N);return 2;}
    long long bad=0; int ra=0,rb=0,rc=0,rd=0;
    for(int a=1;a<=N;a++)
    for(int b=a+1;b<=N;b++)
    for(int c=b+1;c<=N;c++){
        if(a+b+2*c+1>N) break;
        for(int d=c+1;d<=N;d++){
            int s=a+b+c+d; if(s>N) break;
            int lo=0, hi=1;
            #define CHK(x) do{ if(col[x]) lo=1; else hi=1; }while(0)
            CHK(a);CHK(b);CHK(c);CHK(d);
            CHK(a+b);CHK(a+c);CHK(a+d);
            CHK(b+c);CHK(b+d);CHK(c+d);
            CHK(a+b+c);CHK(a+b+d);CHK(a+c+d);CHK(b+c+d);
            CHK(s);
            if(!(lo&&hi)){ if(!bad){ra=a;rb=b;rc=c;rd=d;} bad++; }
        }
    }
    printf("N=%d mono_cubes=%lld", N, bad);
    if(bad) printf(" first=(%d,%d,%d,%d)",ra,rb,rc,rd);
    printf("\n");
    return bad?1:0;
}
