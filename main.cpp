#include <graphics.h>
#include <bits/stdc++.h>
#include <easyx.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

using namespace std;

char a[11][11]={				
				"         ",
				"         ",
				"         ",
				"         ",
				"         ",
				"         ",
				"         ",
				"         ",
				"         "};
				
int a2[11][11],a1[11][11];//1:0->什么也没有发生   1->be opened  2:0->什么也没有发生 1->悬停
int a3[11][11];//雷数
MOUSEMSG msg;
int e=0;
int x,y;

void output()
{
	time_t t;
	srand((unsigned) time(&t));
	IMAGE uno,uno1,o0,o1,o2,o3,o4,o5,tnt;
	loadimage(&uno,"picture\\stone.png",50,50);
	loadimage(&uno1,"picture\\stone1.png",50,50);
	loadimage(&o0,"picture\\0.png",50,50);
	loadimage(&o1,"picture\\1.png",50,50);
	loadimage(&o2,"picture\\2.png",50,50);
	loadimage(&o3,"picture\\3.png",50,50);
	loadimage(&o4,"picture\4.png",50,50);
	loadimage(&o5,"picture\\5.png",50,50);
	loadimage(&tnt,"picture\\tnt.png",50,50);
	for(int z=1;z<=10;z++)
	{
		int p=rand()%9,q=rand()%9;
		if(a[p][q]==' ')
		{
			a[p][q]='*';
		}
		else
		{
			z--;p=rand()%9,q=rand()%9;
		}
	}	
	for(int i=0;i<=8;i++)
	{
		for(int j=0;j<=8;j++)
		{			
			if(a[i][j]==' ')
			{
				int cnt=0;
				if(a[i-1][j-1]=='*')				
					cnt++;	
				if(a[i-1][j]=='*')				
					cnt++;				
				if(a[i-1][j+1]=='*')				
					cnt++;
				if(a[i][j-1]=='*')				
					cnt++;
				if(a[i][j+1]=='*')				
					cnt++;
				if(a[i+1][j-1]=='*')				
					cnt++;
				if(a[i+1][j+1]=='*')				
					cnt++;
				if(a[i+1][j]=='*')				
					cnt++;
				a3[i][j]=cnt;			
			}
		}
	}
	while(1)
	{
		for(int i=0;i<=8;i++)
		{
			for(int j=0;j<=8;j++)
			{
				int x=j*50,y=i*90;
				switch(a[i][j])
				{
					case '*':
						if(a1[i][j]==0)
						{
							if(a2[i][j]==0)
							{
								putimage(j*50,i*50,&uno);
							}
							else
							{
								putimage(j*50,i*50,&uno1);
							}
						}
						else
						{
							putimage(j*50,i*50,&tnt);
							Sleep(250);
								e=1;							
						}
						break;
					default:
						if(a1[i][j]==0)
						{
							if(a2[i][j]==0)
							{
								putimage(j*50,i*50,&uno);
							}
							else
							{
								putimage(j*50,i*50,&uno1);
							}
						}
						else
						{
							switch(a3[i][j])
							{
								case 0:putimage(j*50,i*50,&o0);break;
								case 1:putimage(j*50,i*50,&o1);break;
								case 2:putimage(j*50,i*50,&o2);break;
								case 3:putimage(j*50,i*50,&o3);break;
								case 4:putimage(j*50,i*50,&o4);break;
								case 5:putimage(j*50,i*50,&o5);break;
							}							
						}
						break;	
				}
			}
		}
	}
}

void xy()
{	
	while(1)
	{		
		msg = GetMouseMsg();
		x=msg.y/50;
		y=msg.x/50;					
		//cout<<x<<' '<<y<<'\n';
	}
}

	void tool2(int x1,int y1)
	{		
		a1[x1][y1]=1;
		if((a[x1][x1]==' '&&a3[x1][y1]!=0)||a[x1][y1]=='*')
		{
			return;
		}
		else
		{
			if(x1>8||y1>8||x1<0||y1<0)
			{
				return;
			}
			
			if(a1[x1+1][y1]==1||a[x1+1][y1]=='*'||(a[x1+1][y1]==' '&&a3[x+1][y1]!=0&&a3[x1][y1]!=0&&a[x1][y1]==' '))
			{
				if(a1[x1][y1+1]==1||a[x1][y1+1]=='*'||(a[x1][y1+1]==' '&&a3[x1][y1+1]!=0&&a3[x1][y1]!=0&&a[x1][y1]==' '))
				{
					if(a1[x1-1][y1]==1||a[x1-1][y1]=='*'||(a[x1-1][y1]==' '&&a3[x1-1][y1]!=0&&a3[x1][y1]!=0&&a[x1][y1]==' '))
					{
						if(a1[x1][y1-1]==1||a[x1][y1-1]=='*'||(a[x1][y1-1]==' '&&a3[x1][y1-1]!=0&&a3[x1][y1]!=0&&a[x1][y1]==' '))
						{
							return;
						}
						else
						{
							tool2(x1-1,y1);
						}					
					}
					else
					{
						tool2(x1-1,y1);
					}				
				}
				else
				{
					tool2(x1,y1+1);
				}
			}
			else
			{
				tool2(x1+1,y1);
			}
			
			if(a[x1+1][y1]==' '&&a1[x1+1][y1]==0)
			{
				a1[x1+1][y1]=1;
				if(a3[x1+1][y1]==0)
				{
					tool2(x1+1,y1);
				}
			}
			if(a[x1][y1+1]==' '&&a1[x1][y1+1]==0)
			{
				a1[x1][y1+1]=1;
				if(a3[x1][y1+1]==0)
				{
					tool2(x1,y1+1);
				}
			}
			if(a[x1-1][y1]==' '&&a1[x1-1][y1]==0)
			{
				a1[x1-1][y1]=1;
				if(a3[x1-1][y1]==0)
				{
					tool2(x1-1,y1);
				}
			}
			if(a[x1][y1-1]==' '&&a1[x1][y1-1]==0)
			{
				a1[x1][y1-1]=1;
				if(a3[x1][y1-1]==0)
				{
					tool2(x1,y1-1);
				}
			}		
		}
	}

void msgc()
{	
	for(int i=0;i<=8;i++)
	{
		for(int j=0;j<=8;j++)
		{
			if(a[i][j]!=' ')
			{
				if(a[i][j]=='*')
				{
					a3[i][j]=2;
				}
				else
				{
					a3[i][j]=1;
				}
			}
		}
	}
	while(1)
	{	
		a2[x][y]=1;
		for(int i=0;i<=8;i++)
		{
			for(int j=0;j<=8;j++)
			{
				if(i!=x||j!=y) 
				{
					a2[i][j]=0;
				}
			}			
		}
		
			if(msg.uMsg==WM_LBUTTONDOWN)
			{
				a1[x][y]=1;
				if(a[x][y]==' '&&a3[x][y]==0)
				{
					tool2(x,y);
				}
			}					
	}
}

	bool tool1(int i,int j)
	{
		if(a[i][j]=='*')
		{
			return true;
		}
		else
		{
			if(a1[i][j]==1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

void ifwin()
{
	bool win;
	while(1)
	{
		win=1;
		for(int i=0;i<=8;i++)
		{
			for(int j=0;j<=8;j++)
			{
				if(tool1(i,j)==false)
				{
					win=0;break;
				}
			}
			if(win==0)
			{
				break;
			}
		}
		if(win==1)
		{
			e=2;
			break;
		}
	}
	return;
}
int main()
{
	initgraph(450,450/*,SHOWCONSOLE*/);	
	thread o(output);
	o.detach();
	thread i(xy);
	i.detach();
	thread m(msgc);
	m.detach();
	thread ie(ifwin);
	ie.detach();
	/*
		SHOWCONSOLE  显示小黑窗
		NOCLOSE      no close
		NOMINIMIZE   no 最小化
		DBLCLKS      在绘图窗口中支持鼠标双击事件
	*/
	while(1)
	{
		int en=e;
		if(en==1)
		{
			closegraph();
			cout<<"you lose";	
			break;		
		}
		if(en==2)
		{
			closegraph();
			cout<<"you win";
			break;
		}
	}
	cout<<endl;
	for(int j=0;j<=8;j++)
	{
		for(int i=0;i<=8;i++)
		{
			if(a[i][j]!=' ')
			{
				cout<<a[i][j]<<' ';
			}
			else
			{
				if(a3[i][j]==0)
				{
					cout<<' '<<' ';
				}
				else
				{
					cout<<a3[i][j]<<' ';
				}
			}
		}
		cout<<endl;
	}
	return 0;
}