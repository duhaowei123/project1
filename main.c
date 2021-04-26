#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFINITY 30000    /* ����һ��Ȩֵ�����ֵ */
#define MAX_VERTEX_NUM 20 /* ͼ����󶥵��� */
typedef struct
{int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; /* �ڽӾ��� */
 int vexnum,arcnum;                /* ͼ�ĵ�ǰ����ͱ��� */
}Graph;
typedef struct
{int adjvex;  /* ĳ�������ѹ���õĲ����������Ķ���֮��Ȩֵ��С�Ķ��� */
 int lowcost; /* ĳ�������ѹ���õĲ����������Ķ���֮�����СȨֵ */
}ClosEdge[MAX_VERTEX_NUM]; /* ������ķ�㷨����С������ʱ�ĸ������� */
void CreateGraph(Graph *G)
{/* �����ڽӾ���ṹ��ͼG */
 int i,j;
 int start,end,weight;
 printf("������ͼ�Ķ���ͻ���(���Ÿ���):");
 scanf("%d,%d",&G->vexnum,&G->arcnum); /* ����ͼ�Ķ������ͱ��� */
 for(i=1;i<=G->vexnum;i++)
    for(j=1;j<=G->vexnum;j++)
      G->arcs[i][j]=INFINITY; /* ��ʼ���ڽӾ��� */
 printf("���붥�����Ȩֵ����ʽ������1,����2,Ȩֵ\n");
 for(i=1;i<=G->arcnum;i++)
   {printf("�������%d�����������˵㼰Ȩֵ(���Ÿ���):",i);
	 scanf("%d,%d,%d",&start,&end,&weight); /* ����ߵ������յ㼰Ȩֵ */
    G->arcs[start][end]=weight;
    G->arcs[end][start]=weight;
   }
}
int minimum(ClosEdge cl,int vnum)
{/* �ڸ�������cl[vnum]��ѡ��Ȩֵ��С�Ķ��㣬��������λ�� */
 int i;
 int w,p;
 w=INFINITY;
 for(i=1;i<=vnum;i++)
  if(cl[i].lowcost!=0&&cl[i].lowcost<w)
     {w=cl[i].lowcost;p=i;}
 return p;
}
void MiniSpanTree_PRIM(Graph *G,int u)
{/* �ӵ�u�������������ͼG����С������ */
 ClosEdge closedge;
 int i,j,k,n=0,a=0;
 printf("��С����������:\n");
 for(j=1;j<=G->vexnum;j++) /* ���������ʼ�� */
   if(j!=u)
     {closedge[j].adjvex=u;
      closedge[j].lowcost=G->arcs[u][j];
     }
 closedge[u].lowcost=0; /* ��ʼ��U={u} */
 for(i=1;i<G->vexnum;i++) /* ѡ�������G->vexnum-1������ */
   {k=minimum(closedge,G->vexnum); /* �������������һ������ */
    printf("<%d--%d>  %d\n",closedge[k].adjvex,k,closedge[k].lowcost); /* ����������ı߼���Ȩֵ */
	n=n+closedge[k].lowcost;
    closedge[k].lowcost=0;   /* ��k���㲢��U�� */
    for(j=1;j<=G->vexnum;j++) /* �¶��㲢��U���޸ĸ�������*/
      if(G->arcs[k][j]<closedge[j].lowcost)
    {closedge[j].adjvex=k;
     closedge[j].lowcost=G->arcs[k][j];
    }
	}a=a+n;printf("��СȨֵΪ:%d\n",a);
}
void example()
{
/* ------------------�����˵---------------------------- */
 printf("��������ʾ����ͼ����С������������\n");
 printf("��������ͼ�Ķ������ͻ���\n��ʽ��������������������:4,4\n");
 printf("�������������(��β,��ͷ)�ͻ���Ȩֵ��\n");
 printf("��ʽ:����1,����2,Ȩֵ������\n1,2,1\n1,3,2\n2,4,3\n3,4,4\n");
 printf("���򽫻ṹ���ͼ����С������������\n");
 printf("����ʾ����С��������\n<1--2>  1\n<1--3>  2\n<2--4>  3\n��СȨֵΪ:6\n");
 printf("�����ѡ��:");
 /* ------------------------------------------------------ */
}
void put()
{Graph G;  /* �����ڽӾ���ṹ��ͼ */
 char j='y';
 int u;
 while(j!='N'&&j!='n')
  {
	 CreateGraph(&G);       /* �����ڽӾ���ṹ��ͼ */
	 while(j!='N'&&j!='n')
	 {
       printf("����һ���㿪ʼ:");
       scanf("%d",&u);  /* ��������ķ�㷨�е���ʼ���� */
       MiniSpanTree_PRIM(&G,u); /* ����ķ�㷨����С������ */
	   printf("Ҫ�����ӱ�ĵ���й�����С������������?(Y/N)");
	   fflush(stdin);   /*���������*/
       scanf("%c",&j);
	 }
       printf("��С����������������ϣ�����������?(Y/N)");
       fflush(stdin);   /*���������*/
       scanf("%c",&j);
	   if(j=='N'||j=='n')  printf("�����ѡ��:");
   }
}
void main()
{
	int k,i=0;
    printf("*************����ķ�㷨ʵ����С������***************\n");
	printf("            1.������С����������\n");
	printf("            2.�鿴����ʾ��\n");
	printf("            3.�˳�ϵͳ\n");
	printf("*****************************************************\n");
    printf("��ѡ��:");
	for(;k!=-1;)
	{
	   switch(scanf("%d",&k),k)
	   {
	    case 1:put();break;
        case 2:example();break;
	    case 3:printf("ллʹ��!\n");exit(0);
        default:printf("��������!\n�����ѡ��:");
	   }
	}
}

