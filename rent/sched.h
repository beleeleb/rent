//
//  sched.h
//  rent
//
//  Created by gali zorea on 05/11/2016.
//  Copyright © 2016 gali zorea. All rights reserved.
//

#ifndef sched_h
#define sched_h

class sched{
public:
    void init();
    bool setTime(int _day, int _hour, unsigned long _sval[]);
    void printSched();
    
    unsigned long printSval();
private:
    unsigned long m_schedBitArr[2];
};


void sched::init()
{
    memset(&m_schedBitArr, 0, sizeof(m_schedBitArr));
}


bool sched::setTime(int _day, int _hour, unsigned long _sval[])//day 1-7, hour 1-12
{
    int index = 0;
    _day -= 1;  //for UI purposes only
    _hour -= 1;
    index = _day * 12 + _hour;
    if(index <= 83)
    {
        if(index >= 64)
        {
            m_schedBitArr[1] |= 1UL << (index - 64);    //UL stands for (unsigned long) because 1 is int by default
        }
        
        else
        {
            m_schedBitArr[0] |= 1UL << index;
        }
        
        _sval[0] =m_schedBitArr[0];
        
        _sval[1] =m_schedBitArr[1];
        return true; //set succeeded
    }
    
    else
    {
        return false; //day and hour more than 84 (7 * 12)
    }
}

void sched::printSched()
{
    int i_day = 0;
    int j_hour = 0;
    int index = 0;
    
    cout << "\t\t";
    
    for(j_hour = 1; j_hour < 10; j_hour++)
    {
        cout << "-" << j_hour << "-";
    }
    
    for(; j_hour < 13; j_hour++)
    {
        cout  << j_hour << "-";
    }
    cout << endl;

    j_hour = 0;
    for (i_day = 0; i_day < 7; i_day++)
    {
        index = i_day * 12;
        
        cout << "day " << i_day + 1 << ":\t";
        for(j_hour = 0; j_hour < 12; j_hour++)
        {
            index += j_hour;
            
            if(index >= 64)
            {
                if(m_schedBitArr[1] & 1UL << (index - 64))
                {
                    cout << "|*|" ;
                }
                
                else{
                    cout << "| |" ;
                }
            }
            
            else
            {
                if(m_schedBitArr[0] & (1UL << index))
                {
                    cout << "|*|" ;
                }
            
                else
                {
                    cout << "| |" ;
                }
            }
            
            index = i_day * 12;

        }
        
        cout << endl;

        
        
    }
}


#endif /* sched_h */
