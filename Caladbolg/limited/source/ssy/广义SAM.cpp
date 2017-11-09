#include<iostream>
#include<cstring>
using namespace std; 
const int MaxPoint=1010101;
struct Suffix_AutoMachine{
	int son[MaxPoint][27],pre[MaxPoint],step[MaxPoint],right[MaxPoint],root,num;
	int NewNode(int stp)
	{
		num++;
		memset(son[num],0,sizeof(son[num]));
		pre[num]=0;
		step[num]=stp;
		return num;
	}
	Suffix_AutoMachine()
	{
		num=0;
		root=NewNode(0);
	}
	int push_back(int ch,int p)
	{
		int np=NewNode(step[p]+1);
		right[np]=1; 
		step[np]=step[p]+1;
		while(p&&!son[p][ch])
		{
			son[p][ch]=np;
			p=pre[p];
		}
		if(!p)
			pre[np]=root;
		else
		{
			int q=son[p][ch];
			if(step[q]==step[p]+1)
				pre[np]=q;
			else
			{
				int nq=NewNode(step[p]+1);
				memcpy(son[nq],son[q],sizeof(son[q]));
				step[nq]=step[p]+1;
				pre[nq]=pre[q];
				pre[q]=pre[np]=nq;
				while(p&&son[p][ch]==q)
				{
					son[p][ch]=nq;
					p=pre[p];
				}
			}
		}
		return np;
	}
};
int main()
{
	
	return 0;
}
