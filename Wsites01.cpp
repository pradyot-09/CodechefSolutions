
#include <iostream>
#include<bits/stdc++.h>
#include<strings.h>
using namespace std; 
#define zap(s,u,v) for(s=u;s<=v;s++) 
 
#define BCA (26)
 
#define DO(c) ((int)c - (int)'a')
int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}
 
struct Trie
{
    struct Trie *children[BCA];
    int zum=0 ;
    bool isLeaf;
    char c ;
};
 
struct Trie *Node(int n)
{
    struct Trie *ele = NULL;
 
    ele = (struct Trie *)malloc(sizeof(struct Trie));
    ele->zum=n ;
    if (ele)
    {
        int i;
 
        ele->isLeaf = false;
 
        for (i = 0; i < BCA; i++)
            ele->children[i] = NULL;
    }
 
    return ele;
}
 
void put(struct Trie *root, const char *soft,int n)
{
    int index;
    int uv,i ;
    int g=0,g1=0;
    int dis = strlen(soft);
    string h ;
    
    struct Trie *paddi = root;
 
    for (uv = 0; uv < dis; uv++)
    {
        index = DO(soft[uv]);
        if (!paddi->children[index])
        {
                   paddi->children[index] = Node(n);
                   g=1 ;
        }          
        
           if(g1==0)
           {
                if((paddi->zum==1 && n==2) || (paddi->zum==2 && n==1))
                paddi->zum=3 ;
           }
       paddi = paddi->children[index];
        if(g==1)
        g1=1 ;
        
    }
    if(g1==0)
    {
        if((paddi->zum==1 && n==2) || (paddi->zum==2 && n==1))
        paddi->zum=3 ;
    }
    paddi->isLeaf = true;
}
 
int get(struct Trie *root, const char *soft)
{
    int index;
    int uv,q,w;
    string h ;
    int dis = strlen(soft);
    
    
    struct Trie *paddi = root;
 
    for (uv = 0; uv < dis; uv++)
    {
        index = DO(soft[uv]);
 
        if(paddi->zum==2)
        {
             return uv ;
        }
        if(uv==dis-1 && paddi->isLeaf == true)
        return uv+1 ;
        
        paddi = paddi->children[index];
    }
         if(paddi->zum==2)
        {
            return uv ;
        }
    return -1;
}
 
string lines[200005] ;
int dd[1001] ;
int main()
{
    
    char bb ;
    string das ;
    int ob,i,j,k,tuk,y=0,vampa ;
    cin>>ob ;
    for(i=0;i<1000;i++)
    dd[i]=i ;
    
    struct Trie *root = Node(0);
 
    
    
    for (i = 0; i < ob; i++)
        {
            cin>> bb ;
            cin>>das ;
            if(bb=='+')
            j=1 ;
            else
            {
                j=2 ;
                lines[y++]=das ;
            }
            put(root,das.c_str(),j);
        }
    
     std::sort(lines,lines+y);
    if(y==0)
    {
        printf("-1\n");
        return 0 ;
    }
    vampa=0;
    tuk=get(root, lines[0].c_str()) ;
    
        if(tuk==-1)
        {
            printf("-1");
            return 0 ;
        }
    
    das=lines[0].substr(0,tuk) ;
    lines[vampa++]=das ;
    for(i=1;i<y;i++)
    {
        tuk=get(root, lines[i].c_str()) ;
        if(tuk==-1)
        {
            printf("-1");
            return 0 ;
        }
        das=lines[i].substr(0,tuk) ;
        if(strcmp(das.c_str(),lines[vampa-1].c_str())!=0)
        lines[vampa++]=das ;
        
    }  
    printf("%d\n",vampa);
    for(i=0;i<vampa;i++)
        printf("%s\n",lines[i].c_str());
    return 0;
}  
