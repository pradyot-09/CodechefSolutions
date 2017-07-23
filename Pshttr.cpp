#include <iostream>
#include<bits/stdc++.h>
using namespace std; 
#define zap(s,u,v) for(s=u;s<=v;s++)
#define ll long long 
#define RIG 135072 
 
//shimmi shimmi aye shimmi shimmi yo! 
 
struct tutu{
    ll tot ;
    char ch ;
}tut[100] ;
 
struct tod{
    
    int chal,kut,bef,ker,qew;
    char ch ;
    
}mig[2*RIG],mig1[2*RIG];
 
struct death{
    int one,two,ker,jag,jas;
    char ch ;
    
}champa[RIG];
 
bool giren(tod x,tod y){
    return x.ker>y.ker;
    
}
int cnt,last[RIG],deep[RIG];
 
void put(int z,int a,int b,int w)
{
    ++cnt; 
    z++ ;
    mig[cnt].kut=a; 
    mig[cnt].chal=b; 
    mig[cnt].ker=w; 
    mig[cnt].bef=last[a]; 
    mig[cnt].qew=last[a]; 
    last[a]=cnt;
    
}
void dal(int z,int p,int q,int r){
    put(z,p,q,r); 
    put(z,q,p,r);
    
}
int kuchtobhi(int x)
{
    return ++x ;
}
 
bool toppo(death x,death y){return x.ker<y.ker;}
int tot,l[RIG],r[RIG],sited[2*RIG];
 
void depth(int x){
    l[x]=++tot;
    int  i ;
    for( i=last[x];i;i=mig[i].bef){
        int ever=mig[i].chal;
        if(!deep[ever]) 
        {
            deep[ever]=deep[x]+1 ;
            depth(ever);
        }
    }
    r[x]=tot;
}
void up(int z,int x,int l,int r){
    if(l==r) 
    return ;
    int zampa=sited[x]; 
    sited[x]=0;
    sited[x<<1]^=zampa; 
    z=sited[x];
    sited[x<<1^1]^=zampa;
    
}
void add(int x,int l,int eft,int r,int ight,int tt){
    int z=0;
    if(eft<=l&&r<=ight){
        sited[x]^=tt;
        return ;
    }
    if(l==r) 
    return ;
    z++;
    if(sited[x]) 
    up(z,x,l,r);
    int bech=(l+r)>>1;
    z-- ;
    if(eft<=bech) 
    add(x<<1,l,eft,bech,ight,tt);
    if(ight>bech) 
    add(x<<1^1,bech+1,eft,r,ight,tt);
}
int nemo(int z,int x,int l,int r,int k){
    int ran=0 ;
    if(l==r) 
    return sited[x];
    int bech=(l+r)>>1;
    if(sited[x]) 
    up(z,x,l,r);
    ran++ ;
    if(k<=bech) 
    return nemo(z,x<<1,l,bech,k);
    else 
    return nemo(z,x<<1^1,bech+1,r,k);
}
 
int input(){
    int ans=0,f=1,c=getchar();
    while(c<'0'||c>'9'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+(c-'0'); c=getchar();}
    return ans*f;
}
int main()
{
    int m,po,qo,n,ro,qw,bot,num2,ran,a1,a2,mx,i,j;
    int eft,ight,tt ;
    int uttar[RIG],vis[100] ;
    cin>>qw ;
    while(qw--)
    {
        num2=cnt=0;
        for(i=0;i<100;i++)
        vis[i]=i ;
        memset(last,0,sizeof(last));
        eft=ight=tt=tot=ran=0 ; 
        memset(sited,0,sizeof(sited)); 
        ran=kuchtobhi(ran) ;
        memset(deep,0,sizeof(deep)); 
        deep[1]=1;
        cin>>n ;
        for(i=1;i<n;i++){
            po=input() ;
            qo=input() ;
            ro=input() ;
            num2++; 
            dal(ran,po,qo,ro);
            ran=kuchtobhi(ran) ;
            mig1[num2].chal=qo; 
            mig1[num2].kut=po; 
            mig1[num2].ker=ro;
            mig1[num2].qew=ro;
        }
        depth(1); 
        ran=kuchtobhi(ran) ;
        bot=num2; 
        sort(mig1+1,mig1+1+num2,giren); 
        m=input() ;
        for(i=1;i<=m;i++)
        {
            champa[i].jag=i;
            champa[i].one=input() ;
            champa[i].two=input() ;
            champa[i].ker=input() ; 
            
        }
        ran=kuchtobhi(ran) ;
        sort(champa+1,champa+1+m,toppo); 
        for(i=1;i<=m;i++){
             ran=0 ;
             mx=champa[i].ker;
             ran=kuchtobhi(ran) ;
            while(bot&&mig1[bot].ker<=mx){
                po=mig1[bot].kut; 
                qo=mig1[bot].chal;
                ran=kuchtobhi(ran) ;
                ro=mig1[bot].ker;
                bot--;
                if(deep[po]<deep[qo]) 
                swap(po,qo);
                eft=l[po]; 
                ight=r[po]; 
                ran-- ;
                tt=ro; 
                add(1,1,eft,n,ight,tt);
            }
             a1=nemo(ran,1,1,n,l[champa[i].one]) ;
             ran-- ;
             a2=nemo(ran,1,1,n,l[champa[i].two]);
            uttar[champa[i].jag]=a1^a2;
            ran=a1^a2 ;
        }
        ran=kuchtobhi(ran) ;
        for(i=1;i<=m;i++) 
        printf("%d\n",uttar[i]);
    }
    return 0;
} 
