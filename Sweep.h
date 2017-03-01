#ifndef SWEEP_H_INCLUDED
#define SWEEP_H_INCLUDED
#include<base_set.h>
#include<map>
#include<string>
#include<sstream>
#ifdef Debug
    #include<my.h>
#endif // Debug
class Sweep{
    CurrentState& cs;
    double& sys_freq; //MHz
    int& auto_io_update;
    int mode;
    double va0,va1,va2,va3,va4,va5,va6,va7;
    Reg cf2,lsp0,lsp1,rs,fs,ts,sk0,sk1;
    std::map<int,Reg*> rmap;
public:
    void enable(int i);
    void enable_fj(int i);
    void set_mode(int i);
    void set_Dwell_High(int i);
    void set_Dwell_Low(int i);
    void set_auto_drctl(int i);
    void set_drctl(int i);
    void change_value(int id,double value);
    std::map<std::string,std::string> get_info();
    Sweep(BaseSet& bs);
};
#endif // SWEEP_H_INCLUDED
