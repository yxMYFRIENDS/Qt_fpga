#ifndef __MY_H__
#define __MY_H__
#include <iostream>
#include <set>
#include <typeinfo>
#include <stdio.h>
#include <time.h>
#include <map>
#include <algorithm>
#include <stack>
#include <queue>
#include <string>
#include <sstream>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#define TO_STRING(x) TO_STRING2(x)
#define TO_STRING2(x) printf(#x)
#define st(x) do{ x } while (__LINE__ == -1)
#define CHS(x,y) CHS2(x,y)
#define CHS2(x,y) x##y
#define COUNT_PARMS2(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_,...) _
#define COUNT_PARMS(...) COUNT_PARMS2(__VA_ARGS__,10,9,8,7,6,5,4,3,2,1)
#define PFV_1(_1) cout<<" "#_1"="<<_1
#define PFV_2(_1,...) st(PFV_1(_1);PFV_1(__VA_ARGS__);)
#define PFV_3(_1,...) st(PFV_1(_1);PFV_2(__VA_ARGS__);)
#define PFV_4(_1,...) st(PFV_1(_1);PFV_3(__VA_ARGS__);)
#define PFV_5(_1,...) st(PFV_1(_1);PFV_4(__VA_ARGS__);)
#define PFV_6(_1,...) st(PFV_1(_1);PFV_5(__VA_ARGS__);)
#define pf(...) st( printf("line:%d ",__LINE__);\
                    CHS(PFV_,COUNT_PARMS(__VA_ARGS__))(__VA_ARGS__);\
                    cout<<endl;)
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
template<typename T1,typename T2>
ostream& operator<<(ostream& os,const pair<T1,T2> &p)
{
    os<<"("<<p.first<<","<<p.second<<")";
    return os;
}
template<typename T>
ostream& operator<<(ostream& os,const vector<T> &v)
{
    os<<"[";
    for(auto it=v.begin();it!=v.end();++it){
        os<<*it;
        if(it+1!=v.end())
            os<<',';
    }
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream& os,const vector<vector<T> > &v)
{
    os<<"[\n";
    for(auto it=v.begin();it!=v.end();++it)
        os<<"  "<<*it<<'\n';
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream& os,const vector<vector<vector<T> > > &v)
{
    os<<"[\n";
    for(int i=0;i<v.size();++i){
        os<<"  [\n";
        for(int j=0;j<v[0].size();++j)
            os<<"    "<<v[i][j]<<"\n";
        os<<"  ]\n";
    }
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream& os,const set<T> &s)
{
    os<<"{";
    auto tmp = s.begin();
    for(auto it=s.begin();it!=s.end();it=tmp){
        os<<*it;
        tmp = it;
        ++tmp;
        if(tmp!=s.end())
            os<<",";
        else
            os<<"}";
    }
    return os;
}
template<typename T>
ostream& operator<<(ostream& os,const unordered_set<T> &s)
{
    os<<"{";
    auto tmp = s.begin();
    for(auto it=s.begin();it!=s.end();it=tmp){
        os<<*it;
        tmp = it;
        ++tmp;
        if(tmp!=s.end())
            os<<",";
        else
            os<<"}";
    }
    return os;
}
template<typename T1,typename T2>
ostream& operator<<(ostream& os,const map<T1,T2> &m)
{
    os<<"{";
    auto tmp = m.begin();
    for(auto it=m.begin();it!=m.end();it=tmp){
        os<<it->first<<"=>"<<it->second;
        tmp = it;
        ++tmp;
        if(tmp!=m.end())
            os<<",";
        else
            os<<"}";
    }
    return os;
}
template<typename T1,typename T2>
ostream& operator<<(ostream& os,const unordered_map<T1,T2> &m)
{
    os<<"{";
    auto tmp = m.begin();
    for(auto it=m.begin();it!=m.end();it=tmp){
        os<<it->first<<"=>"<<it->second;
        tmp = it;
        ++tmp;
        if(tmp!=m.end())
            os<<",";
        else
            os<<"}";
    }
    return os;
}
#endif // __MY_H__
