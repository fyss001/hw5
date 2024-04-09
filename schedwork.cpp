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
bool checkValid(const size_t, DailySchedule&, const size_t, const Worker_T);

bool checkValid(const size_t maxShifts, DailySchedule& sched, const size_t day, const Worker_T id){
    size_t cnt=0;
    if(day!=0){
        for(size_t i=0;i<day;i++){
            for(size_t j=0;j<sched[i].size();j++){
                if(sched[i][j]==id){
                    cnt++;
                    if(cnt>maxShifts-1){
                        return false;
                    }
                    continue;
                }
            }
        }
    }
    for(size_t j=0;j<sched[day].size();j++){
        if(sched[day][j]==INVALID_ID) break;
        if(sched[day][j]==id) return false;
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
    vector<Worker_T> availToday;
    vector<Worker_T> schedToday;
    if(sched.empty()||sched[sched.size()-1][dailyNeed-1]!=INVALID_ID){
        vector<Worker_T> temp;
        temp.resize(dailyNeed);
        std::fill(temp.begin(),temp.end(),INVALID_ID);
        sched.push_back(temp);
    }
    size_t day=sched.size()-1;
    schedToday=sched[day];    
    for(size_t i=0;i<avail[day].size();i++){
        if(avail[day][i]) availToday.push_back(i);
    }
    if(dailyNeed>availToday.size()){
        if(sched[day][0]==INVALID_ID){
            sched.pop_back();
        }
        return false;
    }
    for(size_t i=0;i<dailyNeed;i++){
        if(schedToday[i]==INVALID_ID){
            for(size_t j=0;j<availToday.size();j++){
                if(checkValid(maxShifts, sched, day, availToday[j])){
                    schedToday[i]=availToday[j];
                    sched[day]=schedToday;
                    if(schedule(avail, dailyNeed, maxShifts, sched)){
                        return true;
                    }else{
                        schedToday[i]=INVALID_ID;
                        sched[day]=schedToday;
                    }
                }
            }
            break;
        }
    }
    if(sched[day][0]==INVALID_ID){
        sched.pop_back();
    }
    return false;
}

