#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFINITY 30000    /* 定义一个权值的最大值 */
#define MAX_VERTEX_NUM 20 /* 图的最大顶点数 */
typedef struct
{int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; /* 邻接矩阵 */
 int vexnum,arcnum;                /* 图的当前顶点和边数 */
}Graph;
typedef struct
{int adjvex;  /* 某顶点与已构造好的部分生成树的顶点之间权值最小的顶点 */
 int lowcost; /* 某顶点与已构造好的部分生成树的顶点之间的最小权值 */
}ClosEdge[MAX_VERTEX_NUM]; /* 用普里姆算法求最小生成树时的辅助数组 */
void CreateGraph(Graph *G)
{/* 构造邻接矩阵结构的图G */
 int i,j;
 int start,end,weight;
 printf("请输入图的顶点和弧数(逗号隔开):");
 scanf("%d,%d",&G->vexnum,&G->arcnum); /* 输入图的顶点数和边数 */
 for(i=1;i<=G->vexnum;i++)
    for(j=1;j<=G->vexnum;j++)
      G->arcs[i][j]=INFINITY; /* 初始化邻接矩阵 */
 printf("输入顶点和其权值，格式：顶点1,顶点2,权值\n");
 for(i=1;i<=G->arcnum;i++)
   {printf("请输入第%d条弧的两个端点及权值(逗号隔开):",i);
	 scanf("%d,%d,%d",&start,&end,&weight); /* 输入边的起点和终点及权值 */
    G->arcs[start][end]=weight;
    G->arcs[end][start]=weight;
   }
}
int minimum(ClosEdge cl,int vnum)
{/* 在辅助数组cl[vnum]中选择权值最小的顶点，并返回其位置 */
 int i;
 int w,p;
 w=INFINITY;
 for(i=1;i<=vnum;i++)
  if(cl[i].lowcost!=0&&cl[i].lowcost<w)
     {w=cl[i].lowcost;p=i;}
 return p;
}
void MiniSpanTree_PRIM(Graph *G,int u)
{/* 从第u个顶点出发构造图G的最小生成树 */
 ClosEdge closedge;
 int i,j,k,n=0,a=0;
 printf("最小代价生成树:\n");
 for(j=1;j<=G->vexnum;j++) /* 辅助数组初始化 */
   if(j!=u)
     {closedge[j].adjvex=u;
      closedge[j].lowcost=G->arcs[u][j];
     }
 closedge[u].lowcost=0; /* 初始，U={u} */
 for(i=1;i<G->vexnum;i++) /* 选择其余的G->vexnum-1个顶点 */
   {k=minimum(closedge,G->vexnum); /* 求出生成树的下一个顶点 */
    printf("<%d--%d>  %d\n",closedge[k].adjvex,k,closedge[k].lowcost); /* 输出生成树的边及其权值 */
	n=n+closedge[k].lowcost;
    closedge[k].lowcost=0;   /* 第k顶点并入U集 */
    for(j=1;j<=G->vexnum;j++) /* 新顶点并入U后，修改辅助数组*/
      if(G->arcs[k][j]<closedge[j].lowcost)
    {closedge[j].adjvex=k;
     closedge[j].lowcost=G->arcs[k][j];
    }
	}a=a+n;printf("最小权值为:%d\n",a);
}
void example()
{
/* ------------------程序解说---------------------------- */
 printf("本程序将演示构造图的最小代价生成树。\n");
 printf("首先输入图的顶点数和弧数\n格式：顶点数，弧数；例如:4,4\n");
 printf("接着输入各条弧(弧尾,弧头)和弧的权值。\n");
 printf("格式:顶点1,顶点2,权值；例如\n1,2,1\n1,3,2\n2,4,3\n3,4,4\n");
 printf("程序将会构造该图的最小代价生成树。\n");
 printf("并显示该最小生成树。\n<1--2>  1\n<1--3>  2\n<2--4>  3\n最小权值为:6\n");
 printf("请继续选择:");
 /* ------------------------------------------------------ */
}
void put()
{Graph G;  /* 采用邻接矩阵结构的图 */
 char j='y';
 int u;
 while(j!='N'&&j!='n')
  {
	 CreateGraph(&G);       /* 生成邻接矩阵结构的图 */
	 while(j!='N'&&j!='n')
	 {
       printf("从哪一顶点开始:");
       scanf("%d",&u);  /* 输入普里姆算法中的起始顶点 */
       MiniSpanTree_PRIM(&G,u); /* 普里姆算法求最小生成树 */
	   printf("要继续从别的点进行构造最小代价生成树吗?(Y/N)");
	   fflush(stdin);   /*清除缓冲区*/
       scanf("%c",&j);
	 }
       printf("最小代价生成树构造完毕，继续进行吗?(Y/N)");
       fflush(stdin);   /*清除缓冲区*/
       scanf("%c",&j);
	   if(j=='N'||j=='n')  printf("请继续选择:");
   }
}
void main()
{
	int k,i=0;
    printf("*************普里姆算法实现最小生成树***************\n");
	printf("            1.构造最小代价生成树\n");
	printf("            2.查看帮助示例\n");
	printf("            3.退出系统\n");
	printf("*****************************************************\n");
    printf("请选择:");
	for(;k!=-1;)
	{
	   switch(scanf("%d",&k),k)
	   {
	    case 1:put();break;
        case 2:example();break;
	    case 3:printf("谢谢使用!\n");exit(0);
        default:printf("输入有误!\n请继续选择:");
	   }
	}
}

