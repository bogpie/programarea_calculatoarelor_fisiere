#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
    char nume[40];
    char sex;
    float nota;
};
typedef struct student STUDENT;

void fTest(binar)
{
    //FILE * binar = fopen("binar.dat","rb");
    int n;
    fread(&n,sizeof(n),1,binar);
    printf ("\n%d\n",n);
    STUDENT v[40];
    fread(v,sizeof(STUDENT),n,binar);
    int i;
    for (i=0;i<n;++i)
    {
        printf ("%s %c %f\n",v[i].nume,v[i].sex,v[i].nota);
    }
}

void fInit(FILE * binar)
{
    int n;
    scanf ("%d",&n);
    fwrite(&n,sizeof(n),1,binar);
    STUDENT v[40];
    int i;
    for (i=0;i<n;++i)
    {
        fflush(stdin);
        printf("\nnume : ");
        gets(v[i].nume);
        fflush(stdin);
        printf("\nsexul si nota: ");
        scanf("%c%f",&v[i].sex,&v[i].nota);
    }
    fwrite(v,sizeof(STUDENT),n,binar);
    fclose(binar);
}

char * fExista(char nume[40],FILE * binar)
{
    fseek(binar,0,SEEK_SET);
    char * ptr = malloc(sizeof(char*)*10);
    int n;
    fread(&n,sizeof(n),1,binar);
    STUDENT v[40];
    fread(v,sizeof(STUDENT),n,binar);
    int i;
    for (i=0;i<n;++i)
    {
        if (!strcmp(nume,v[i].nume))
        {
            strcpy(ptr,"Exista");
            return ptr;
        }
    }
    strcpy(ptr,"Nu exista");
    return ptr;
    fclose(binar);
}

void fCount(int * adrNrBaieti, int * adrNrFete,FILE * binar)
{
    fseek(binar,0,SEEK_SET);
    int n;
    fread(&n,sizeof(n),1,binar);
    STUDENT v[40];
    fread(v,sizeof(STUDENT),n,binar);
    int i;
    float mx = -1;
    for (i=0;i<n;++i)
    {
        if (v[i].nota>mx)
        {
            mx=v[i].nota;
        }
    }
    for (i=0;i<n;++i)
    {
        if (v[i].nota==mx)
        {
            if (v[i].sex=='M')
            {
                ++*adrNrBaieti;
            }
            else ++*adrNrFete;
        }
    }
}

int main()
{
    FILE * binar = fopen("binar.dat","w+b");
    fInit(binar);
    fTest(binar);
    char nume[]={"Alpha Omega"};

    char * ptr = malloc(sizeof(char*)*10); //"nu exista"
    ptr = fExista(nume,binar);
    printf("\n%s : %s\n",nume,ptr);

    int nrBaieti=0,nrFete=0;
    fCount(&nrBaieti,&nrFete,binar);
    printf("\n%d baieti si %d fete\n",nrBaieti,nrFete);
    return 0;
    fclose(binar);
}
