#include<stdio.h>
#include<string.h>
#include<math.h>

int main()
{
    int i,j,k,m,n,cl;
    char a[10],c[100];

    printf("Enter the polynomial:\n");
    scanf("%s",a);
    printf("\nEnter the CRC frame:\n");
    scanf("%s",c); 

    m=strlen(a);
    cl=strlen(c);

    for(i=0;i<m;i++) /* To eliminate first zeros in polynomial*/
    {
        if(a[i]=='1')
        { m=m-i; break; }
    }
    
    for(k=0;k<m;k++) /* To Adjust the polynomial */
    a[k]=a[k+i];
    n=cl-m+1;

    for(i=0;i<n;i++) /* To check polynomial remainder is zero or not */ 
    if(c[i]=='1')
    {
        for(j=i,k=0;k<m;k++,j++) if(a[k]==c[j])
        c[j]='0';
        else c[j]='1';
    }

    for(i=0;i<cl;i++) /* To copy original data in c[] */
    if(c[i]=='1')
    {
        printf("\nError detetcted");
        break;
    }

    if(i==cl)
    printf("\nNo error detetcted");
    //getch(); 
    return 0;    
}