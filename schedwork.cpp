#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool checkValid(const size_t, const size_t, DailySchedule&, const size_t, const Worker_T);

bool checkValid(const size_t maxShifts, const size_t dailyNeed, DailySchedule& sched, const size_t day, const Worker_T id){
    size_t cnt=0;
    if(day!=0){
        for(size_t i=0;i<=day;i++){
            for(size_t j=0;j<dailyNeed;j++){
                if(sched[i][j]==id){
                    if(i==day) return false;
                    cnt++;
                    if(cnt>maxShifts-1){
                        return false;
                    }
                    continue;
                }
            }
        }
    }
    return true;
}

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    if(avail.size() == sched.size() && sched[sched.size()-1][dailyNeed-1]!=INVALID_ID){
        return true;
    }
    vector<Worker_T> schedToday;
    if(sched.empty()||sched[sched.size()-1][dailyNeed-1]!=INVALID_ID){
        vector<Worker_T> temp;
        temp.resize(dailyNeed+1);
        std::fill(temp.begin(),temp.end(),INVALID_ID);
        temp[dailyNeed]=0;
        sched.push_back(temp);
    }
    size_t day=sched.size()-1;
    schedToday=sched[day];
    int i=schedToday[dailyNeed];
    for(size_t j=0;j<avail[day].size();j++){
        if(!avail[day][j]) continue;
        if(checkValid(maxShifts, dailyNeed, sched, day, j)){
            schedToday[i]=j;
            schedToday[dailyNeed]++;
            sched[day]=schedToday;
            if(schedule(avail, dailyNeed, maxShifts, sched)){
                if(i==0){
                    sched[day].pop_back();
                }
                return true;
            }else{
                schedToday[i]=INVALID_ID;
                schedToday[dailyNeed]--;
                sched[day]=schedToday;
            }
        }
    }
    if(sched[day][0]==INVALID_ID){
        sched.pop_back();
    }
    return false;
}

