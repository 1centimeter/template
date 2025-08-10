#include<bits/stdc++.h>
#include<bits/extc++.h>
#define INF64 (long long)0x7f7f7f7f7f7f7f7f
#define inf64 (long long)0x3f3f3f3f3f3f3f3f
#define INF32 (int)0x7f7f7f7f
#define inf32 (int)0x3f3f3f3f
#define _inf32 (int)0xc0c0c0c0
#define _INF32 (int)0x80808080
#define _inf64 (long long)0xc0c0c0c0c0c0c0c0
#define _INF64 (long long)0x8080808080808080
#define N 500010
namespace std{
    inline int mex(int maxl,int mexl,int maxr,int mexr){
        return maxl<maxr?max(maxl,mexr):maxl==maxr?max(mexl,mexr):max(mexl,maxr);
    }
    inline int mun(int minl,int munl,int minr,int munr){
        return minl<minr?min(munl,minr):minl==minr?min(munl,munr):min(minl,munr);
    }
}
using namespace std;
using namespace __gnu_pbds;
int n,m,op,l,r,v;
int a[N];
inline int in(){
    int sum=0,f=0,c=getchar();
    while(c<48||57<c)f=(c==45?1:0),c=getchar();
    while(48<=c&&c<=57)sum=(sum<<3)+(sum<<1)+c-48,c=getchar();
    return f?(~sum)+1:sum;
}
struct jsjsegmenttree{
    struct node{
        int len;
        long long sum;
        int pmaxadd,pminadd,add;//对普通值的tag:"历史"最大 / "历史"最小 / 现值
        int pmaxaddmax,pminaddmax,addmax;//对最大值的tag:"历史"最大 / "历史"最小 / 现值
        int pmaxaddmin,pminaddmin,addmin;//对最小值的tag:"历史"最大 / "历史"最小 / 现值
        int nummax,nummin;
        int pmax,max,mex,pmin,min,mun;
        inline void mer(node nl,node nr){
            sum=nl.sum+nr.sum;
            pmax=std::max(nl.pmax,nr.pmax);
            pmin=std::min(nl.pmin,nr.pmin);
            max=std::max(nl.max,nr.max);
            min=std::min(nl.min,nr.min);
            mex=std::mex(nl.max,nl.mex,nr.max,nr.mex);
            mun=std::mun(nl.min,nl.mun,nr.min,nr.mun);
            nummax=(nl.max==nr.max?nl.nummax+nr.nummax:(nl.max==max?nl.nummax:nr.nummax));
            nummin=(nl.min==nr.min?nl.nummin+nr.nummin:(nl.min==min?nl.nummin:nr.nummin));
        }
        void out(){
            printf("%d %lld add:%lld/%lld/%lld %lld/%lld/%lld %lld/%lld/%lld num:%d %d val:%lld/%lld/%lld %lld/%lld/%lld",
            len,sum,pmaxadd,pminadd,add,pmaxaddmax,pminaddmax,addmax,pmaxaddmin,pminaddmin,addmin,nummax,nummin,pmax,max,mex,pmin,min,mun);
        }
    }t[N<<2];
    void pd(int num){
        if((t[num].pmaxadd||t[num].pminadd||t[num].add||t[num].pmaxaddmax||t[num].pminaddmax||t[num].addmax||t[num].pmaxaddmin||t[num].pminaddmin||t[num].addmin)==0)return;
        if(t[num].len==1){
            t[num].pmaxadd=t[num].pminadd=t[num].add=t[num].pmaxaddmax=t[num].pminaddmax=t[num].addmax=t[num].pmaxaddmin=t[num].pminaddmin=t[num].addmin=0;
            return;
        }
        for(int s=0;s<2;s++){
            int numl=num<<1|s;
            bool bmax=(t[numl].max==t[num].max-t[num].addmax),bmin=(t[numl].min==t[num].min-t[num].addmin);
            t[numl].pmaxadd=max(t[numl].pmaxadd,t[numl].add+t[num].pmaxadd);
            t[numl].pminadd=min(t[numl].pminadd,t[numl].add+t[num].pminadd);
            t[numl].add+=t[num].add;
            if(t[numl].max==t[numl].min){
                t[numl].sum+=(bmax?(long long)t[numl].len*t[num].addmax:(bmin?(long long)t[numl].len*t[num].addmin:(long long)t[numl].len*t[num].add));
                t[numl].pmaxaddmax=max(t[numl].pmaxaddmax,t[numl].addmax+(bmax?t[num].pmaxaddmax:(bmin?t[num].pmaxaddmin:t[num].pmaxadd)));
                t[numl].pminaddmax=min(t[numl].pminaddmax,t[numl].addmax+(bmax?t[num].pminaddmax:(bmin?t[num].pminaddmin:t[num].pminadd)));
                t[numl].addmax+=(bmax?t[num].addmax:(bmin?t[num].addmin:t[num].add));
                t[numl].pmaxaddmin=max(t[numl].pmaxaddmin,t[numl].addmin+(bmax?t[num].pmaxaddmax:(bmin?t[num].pmaxaddmin:t[num].pmaxadd)));
                t[numl].pminaddmin=min(t[numl].pminaddmin,t[numl].addmin+(bmax?t[num].pminaddmax:(bmin?t[num].pminaddmin:t[num].pminadd)));
                t[numl].addmin+=(bmax?t[num].addmax:(bmin?t[num].addmin:t[num].add));
                if(t[numl].mex!=_INF32)t[numl].mex+=t[num].add;
                if(t[numl].mun!=INF32)t[numl].mun+=t[num].add;
                t[numl].pmax=max(t[numl].pmax,t[numl].max+(bmax?t[num].pmaxaddmax:(bmin?t[num].pmaxaddmin:t[num].pmaxadd)));
                t[numl].max+=(bmax?t[num].addmax:(bmin?t[num].addmin:t[num].add));
                t[numl].pmin=min(t[numl].pmin,t[numl].min+(bmax?t[num].pminaddmax:(bmin?t[num].pminaddmin:t[num].pminadd)));
                t[numl].min+=(bmax?t[num].addmax:(bmin?t[num].addmin:t[num].add));
            }else{
                t[numl].sum+=(long long)(t[numl].len-(bmax?t[numl].nummax:0)-(bmin?t[numl].nummin:0))*t[num].add+(bmax?(long long)t[numl].nummax*t[num].addmax:0)+(bmin?(long long)t[numl].nummin*t[num].addmin:0);
                t[numl].pmaxaddmax=max(t[numl].pmaxaddmax,t[numl].addmax+(bmax?t[num].pmaxaddmax:t[num].pmaxadd));
                t[numl].pminaddmax=min(t[numl].pminaddmax,t[numl].addmax+(bmax?t[num].pminaddmax:t[num].pminadd));
                t[numl].addmax+=(bmax?t[num].addmax:t[num].add);
                t[numl].pmaxaddmin=max(t[numl].pmaxaddmin,t[numl].addmin+(bmin?t[num].pmaxaddmin:t[num].pmaxadd));
                t[numl].pminaddmin=min(t[numl].pminaddmin,t[numl].addmin+(bmin?t[num].pminaddmin:t[num].pminadd));
                t[numl].addmin+=(bmin?t[num].addmin:t[num].add);
                if(t[numl].mex!=_INF32)t[numl].mex+=((t[numl].mex==t[numl].min && bmin)?t[num].addmin:t[num].add);
                if(t[numl].mun!=INF32)t[numl].mun+=((t[numl].mun==t[ numl].max && bmax)?t[num].addmax:t[num].add);
                t[numl].pmax=max(t[numl].pmax,t[numl].max+(bmax?t[num].pmaxaddmax:t[num].pmaxadd));
                t[numl].max+=(bmax?t[num].addmax:t[num].add);
                t[numl].pmin=min(t[numl].pmin,t[numl].min+(bmin?t[num].pminaddmin:t[num].pminadd));
                t[numl].min+=(bmin?t[num].addmin:t[num].add);
            }
        }
        t[num].pmaxadd=t[num].pminadd=t[num].add=t[num].pmaxaddmax=t[num].pminaddmax=t[num].addmax=t[num].pmaxaddmin=t[num].pminaddmin=t[num].addmin=0;
    }
    void pu(int num){
        if(t[num].len==1)return;
        t[num].mer(t[num<<1],t[num<<1|1]);
    }
    void bui(int num,int l,int r){
        t[num].len=r-l+1;
        if(l==r){
            t[num].sum=t[num].pmax=t[num].max=t[num].pmin=t[num].min=a[l];
            t[num].pmaxadd=t[num].pminadd=t[num].add=t[num].pmaxaddmax=t[num].pminaddmax=t[num].addmax=t[num].pmaxaddmin=t[num].pminaddmin=t[num].addmin=0;
            t[num].nummax=t[num].nummin=1;
            t[num].mex=_INF32;
            t[num].mun=INF32;
            return;
        }
        int mid=l+r>>1;
        bui(num<<1,l,mid);
        bui(num<<1|1,mid+1,r);
        pu(num);
    }
    void mdfadd(int num,int l,int r,int x,int y,int v){//区间加
        pd(num);
        int mid=l+r>>1;
        if(l==x && r==y){
            t[num].sum+=(long long)t[num].len*v;
            t[num].add+=v;
            t[num].pmaxadd=max(t[num].pmaxadd,t[num].add);
            t[num].pminadd=min(t[num].pminadd,t[num].add);
            t[num].addmax+=v;
            t[num].addmin+=v;
            t[num].pmaxaddmax=max(t[num].pmaxaddmax,t[num].addmax);
            t[num].pminaddmax=min(t[num].pminaddmax,t[num].addmax);
            t[num].pmaxaddmin=max(t[num].pmaxaddmin,t[num].addmin);
            t[num].pminaddmin=min(t[num].pminaddmin,t[num].addmin);
            t[num].max+=v;
            t[num].min+=v;
            t[num].pmax=max(t[num].pmax,t[num].max);
            t[num].pmin=min(t[num].pmin,t[num].min);
            if(t[num].mex!=_INF32)t[num].mex+=v;
            if(t[num].mun!=INF32)t[num].mun+=v;
            return;
        }
        if(x<=mid)mdfadd(num<<1,l,mid,x,min(y,mid),v);
        if(mid+1<=y)mdfadd(num<<1|1,mid+1,r,max(x,mid+1),y,v);
        pu(num);
    }
    void mdfmax(int num,int l,int r,int x,int y,int v){//区间取max
        pd(num);
        int mid=l+r>>1;
        if(l==x && r==y){
            if(t[num].min<v){
                if(v<t[num].mun){
                    if(t[num].min==t[num].max){
                        t[num].addmax+=v-t[num].max;
                        t[num].pmaxaddmax=max(t[num].pmaxaddmax,t[num].addmax);
                        t[num].max=v;
                        t[num].pmax=max(t[num].pmax,t[num].max);
                    }else if(t[num].min==t[num].mex){
                        t[num].mex=v;
                    }
                    t[num].sum+=(long long)t[num].nummin*(v-t[num].min);
                    t[num].addmin+=v-t[num].min;
                    t[num].pmaxaddmin=max(t[num].pmaxaddmin,t[num].addmin);
                    t[num].min=v;
                }else{
                    mdfmax(num<<1,l,mid,l,mid,v);
                    mdfmax(num<<1|1,mid+1,r,mid+1,r,v);
                    pu(num);
                }
            }
            return;
        }
        if(x<=mid)mdfmax(num<<1,l,mid,x,min(y,mid),v);
        if(mid+1<=y)mdfmax(num<<1|1,mid+1,r,max(x,mid+1),y,v);
        pu(num);
    }
    void mdfmin(int num,int l,int r,int x,int y,int v){//区间取min
        pd(num);
        int mid=l+r>>1;
        if(l==x && r==y){
            if(v<t[num].max){
                if(t[num].mex<v){
                    if(t[num].max==t[num].min){
                        t[num].addmin+=v-t[num].min;
                        t[num].pminaddmin=min(t[num].pminaddmin,t[num].addmin);
                        t[num].min=v;
                        t[num].pmin=min(t[num].pmin,t[num].min);
                    }else if(t[num].max==t[num].mun){
                        t[num].mun=v;
                    }
                    t[num].sum+=(long long)t[num].nummax*(v-t[num].max);
                    t[num].addmax+=v-t[num].max;
                    t[num].pminaddmax=min(t[num].pminaddmax,t[num].addmax);
                    t[num].max=v;
                }else{
                    mdfmin(num<<1,l,mid,l,mid,v);
                    mdfmin(num<<1|1,mid+1,r,mid+1,r,v);
                    pu(num);
                }
            }
            return;
        }
        if(x<=mid)mdfmin(num<<1,l,mid,x,min(y,mid),v);
        if(mid+1<=y)mdfmin(num<<1|1,mid+1,r,max(x,mid+1),y,v);
        pu(num);
    }
    long long qrysum(int num,int l,int r,int x,int y){//区间求和
        pd(num);
        if(l==x && r==y)return t[num].sum;
        int mid=l+r>>1;
        if(y<=mid)return qrysum(num<<1,l,mid,x,y);
        if(mid+1<=x)return qrysum(num<<1|1,mid+1,r,x,y);
        return qrysum(num<<1,l,mid,x,mid)+qrysum(num<<1|1,mid+1,r,mid+1,y);
    }
    int qrypmax(int num,int l,int r,int x,int y){//区间求历史max
        pd(num);
        if(l==x && r==y)return t[num].pmax;
        int mid=l+r>>1;
        if(y<=mid)return qrypmax(num<<1,l,mid,x,y);
        if(mid+1<=x)return qrypmax(num<<1|1,mid+1,r,x,y);
        return max(qrypmax(num<<1,l,mid,x,mid),qrypmax(num<<1|1,mid+1,r,mid+1,y));
    }
    int qrymax(int num,int l,int r,int x,int y){//区间求max
        pd(num);
        if(l==x && r==y)return t[num].max;
        int mid=l+r>>1;
        if(y<=mid)return qrymax(num<<1,l,mid,x,y);
        if(mid+1<=x)return qrymax(num<<1|1,mid+1,r,x,y);
        return max(qrymax(num<<1,l,mid,x,mid),qrymax(num<<1|1,mid+1,r,mid+1,y));
    }
    int qrypmin(int num,int l,int r,int x,int y){//区间求历史min
        pd(num);
        if(l==x && r==y)return t[num].pmin;
        int mid=l+r>>1;
        if(y<=mid)return qrypmin(num<<1,l,mid,x,y);
        if(mid+1<=x)return qrypmin(num<<1|1,mid+1,r,x,y);
        return min(qrypmin(num<<1,l,mid,x,mid),qrypmin(num<<1|1,mid+1,r,mid+1,y));
    }
    int qrymin(int num,int l,int r,int x,int y){//区间求min
        pd(num);
        if(l==x && r==y)return t[num].min;
        int mid=l+r>>1;
        if(y<=mid)return qrymin(num<<1,l,mid,x,y);
        if(mid+1<=x)return qrymin(num<<1|1,mid+1,r,x,y);
        return min(qrymin(num<<1,l,mid,x,mid),qrymin(num<<1|1,mid+1,r,mid+1,y));
    }
}sgt;
int main(){
    
}