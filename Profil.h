#ifndef PROFIL_H_INCLUDED
#define PROFIL_H_INCLUDED
#include<base_set.h>
#ifdef Debug
#include<my.h>
#endif // Debug
class Profil{
    double& sys_freq;
    int& auto_io_update;
    CurrentState& cs;
    Reg profiles[8][2];
    Reg cf2;
    int valid_profil;
public:
    void enable(int i); // i= 0,1
    void select_profile(int i); //i=0-7
    void change_profile(int type,double value); //type=0-2,
    int get_enable();
    int get_select();
    std::vector<std::vector<double> > get_profiles();
    Profil(BaseSet& bs);
};
#endif // PROFIL_H_INCLUDED
