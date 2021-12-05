//Sequential file allocation:
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h> 
#define MAX 100
#define BLKSZ 10
#define MEM MAX*BLKSZ

int alloc[MAX];
int fno = 0;
int totalmem = 0;

struct FAT
{
    char fname[25];
    float fsize;
    int startblk;
}file[10];

void allocBlocks(int i,int end,int v)
{
    for (int j = file[i].startblk; j <= end ; j++)
    {
        alloc[j] = v;
    }
    for (int k = 0; k < MAX; k++)
    {
        printf("%d",alloc[k]);
    }
    printf("\n");
}

int findBlocks()
{
    int size = 0;
    for (int i = 0; i < MAX; i++)
    {
        if(alloc[i] == 0)
        {
            size += 10;
            if(size >= file[fno].fsize)
            {
                int nblk = ceil(size/BLKSZ);
                file[fno].startblk = i - nblk + 1;
                allocBlocks(fno,i,1);
                return nblk;
            }
        }
        else
        {
            size = 0;
        }
    }
    file[fno].startblk = -1;
    return -1;    
}

void createFile()
{
    if(totalmem >= MEM)
    {
        printf("Memory is full!");
        return;
    }
    printf("Enter the name of the file: ");
    scanf("%s",file[fno].fname);
    for (int i = 0; i < 10; i++)
    {
        if(strcmp(file[i].fname,file[fno].fname) == 0)
        {
            printf("File with the given name already exists! Try again...");
            return;
        }
    }
    printf("Enter the size of the file: ");
    scanf("%f",&file[fno].fsize);
    int nblk = findBlocks();
    if(nblk == -1)
    {
        printf("X Can't create the file...");
        return;
    }
    printf("File succesfully created...");
    totalmem += nblk*BLKSZ;
    ++fno;
}

void deleteFile()
{
    char name[25];
    printf("Enter the name of the file to delete: ");
    scanf("%s",name);
    for (int i = 0; i < 10; i++)
    {
        if(strcmp(file[i].fname,name) == 0)
        {
            int nblk = ceil(file[i].fsize/BLKSZ);
            int end = file[i].startblk + nblk -1;
            allocBlocks(i,end,0);
            strcpy(file[i].fname," ");
            file[i].fsize = 0;
            file[i].startblk = -1;
            printf("File deleted!");  
            return;
        }
    }
    printf("File not found...");
}

void viewFAT()
{
    printf("\t __FAT__\nFileName  StartBlockNo  FileSize\n");
    for (int i = 0; i < 10; i++) 
    {
        if(file[i].fsize != 0)
            printf(" %s\t  %d\t\t %f\n",file[i].fname,file[i].startblk+1,file[i].fsize);
    }
}

void main()
{
    int ch;
    while(1)
    {
        printf("\n\t<Sequential File Allocation>\n1.Create File\n2.Delete File\n3.View FAT\n4.Exit\n");
        printf(">>Enter a choice: ");
        scanf("%d",&ch);
        switch (ch)
        {
            case 1:
                createFile();
                break;
            case 2:
                deleteFile();
                break;
            case 3:
                viewFAT();
                break;
            case 4:
                exit(0);
                break;
            default:
                printf("Invalid option!\n");
                break;
        }
    }
}

