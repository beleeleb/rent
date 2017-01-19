/*
 * db.h
 *
 *  Created on: Nov 5, 2016
 *      Author: yan
 */

#ifndef DB_H_
#define DB_H_

#define MAX_RESERVATIONS 5
#define MAX_USERS 15
#define MAX_PRODUCTS 3


using namespace std;

class user{
public:
    user(string _name, int _userid, string _pass);
    bool updateProd(int _prodid);
private:
    string m_userName;
    int m_userId;
    string m_userPass;
    int m_prodids[MAX_PRODUCTS] = {0};
    int m_personalProdCnt;
};

user::user(string _name, int _userid, string _pass)
{
    m_userName = _name;
    m_userId = _userid;
    m_userPass = _pass;
    m_personalProdCnt = 0;
}

bool user::updateProd(int _prodid)
{
    if(m_personalProdCnt < MAX_PRODUCTS)
    {
        m_prodids[m_personalProdCnt] = _prodid;
        m_personalProdCnt++;
        return true;
    }
    
    else
    {
        return false;
    }
}
class reservation
{
public:
     reservation(int _day, int _hour, int _userid);//day 1-7, hour 1-12
     unsigned long* getSchedVal();
private:
    int m_userId;
    unsigned long m_userSchedVal[2] = {0};
};

unsigned long* reservation::getSchedVal()
{
    return m_userSchedVal;
}
reservation::reservation(int _day, int _hour, int _userid)//day 1-7, hour 1-12
{
    int index = 0;
    _day -= 1;  //for UI purposes only
    _hour -= 1;
    index = _day * 12 + _hour;
    if(index <= 83)
    {
        if(index >= 64)
        {
            m_userSchedVal[1] |= 1UL << (index - 64);    //UL stands for (unsigned long) because 1 is int by default
        }
        
        else
        {
            m_userSchedVal[0] |= 1UL << index;
        }
        
        m_userId = _userid;
        return; //set succeeded
    }
    
    else
    {
        return; //day and hour more than 84 (7 * 12)
    }
}


class product
{
public:
    product(string _name, int _prodid, int _rate, int _maxRent);
    bool newRenter(int _day, int _hour, int _userid);

    int m_currReservers;
    int getProdCount();
    void init();
    void sumOfReservers();
    void printSched(unsigned long _sval[]);
    bool checkIfFree(int _day, int _hour);
    
private:
    string m_prodName;
    int m_prodId;
    int m_prodRate;
    int m_maxRentTime;
    reservation *reservesArr[MAX_RESERVATIONS];
};

int product::getProdCount()
{
    return m_currReservers;
}

void product::sumOfReservers()
{
    int i;
    unsigned long sum[2] = {0};
    unsigned long* temp = NULL;
    for (i = 0; i< m_currReservers; i++)
    {
        temp = reservesArr[i]->getSchedVal();
        sum[0] |= temp[0];
        sum[1] |= temp[1];
    }
    
    cout << "\n\t\t\t" << m_prodName << endl;
    printSched(sum);
}

void product::printSched(unsigned long _sval[])
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
                if(_sval[1] & 1UL << (index - 64))
                {
                    cout << "|*|" ;
                }
                
                else{
                    cout << "| |" ;
                }
            }
            
            else
            {
                if(_sval[0] & (1UL << index))
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


product::product(string _name, int _prodid, int _rate, int _maxRent)
{
    m_prodName = _name;
    m_prodId = _prodid;
    m_prodRate = _rate;
    m_maxRentTime = _maxRent;
    m_currReservers = 0;
    init();
}

bool product::checkIfFree(int _day, int _hour)
{
    int i;
    unsigned long sum[2] = {0};
    unsigned long* temp = NULL;
    _day -= 1;
    _hour -= 1;
    for (i = 0; i< m_currReservers; i++)
    {
        temp = reservesArr[i]->getSchedVal();
        sum[0] |= temp[0];
        sum[1] |= temp[1];
    }

    int index = _day * 12 + _hour;
    
    if(index <= 83)
    {
        if(index >= 64)
        {
            if(sum[1] & 1UL << (index - 64))
            {
                cout << "day or hour are occuiped!" << endl;

                return false;
            }
        }
        
        else
        {
            if(sum[0] & 1UL << index)
            {
                cout << "day or hour are occuiped!" << endl;
                return false;
            }
        }
    
    cout << "day and hour picked are free :)" << endl;
    return true;
        
    }
    
cout << "day or hour out of scope!" << endl;
 return false;
 
}

bool product::newRenter(int _day, int _hour, int _userid)
{
     if(m_currReservers < MAX_RESERVATIONS && checkIfFree(_day, _hour))
    {
       
       reservesArr[m_currReservers] = new reservation( _day,  _hour,  _userid);
       m_currReservers++;
        return true;
    }
    
    else
    {
        return false; //too many users in product
    }
}

void product::init()
{
    memset(reservesArr, 0, sizeof(reservesArr));
}


class db{
public:
    void newProd(string _name, int _prodid, int _rate, int _maxRent);
    
    void newUser(string _name, int _userid, string _pass);
    void newRent(int _prodid, int _day, int _hour, int _userid);
    //bool setTime(int _day, int _hour, int _prodid, int _userid); //day 1-7, hour 1-12

    int getProdCount();
    void init();
    int userUnikey();
    int getUserCount();
    int getRentsCount();
    void printProdReservation(int _prodid);

private:
    product *prodArr[MAX_PRODUCTS];
    static int m_prodCnt;
    static int m_userCnt;
    static int m_rentsCnt;
    static int m_userUnikey;
    user *m_userArr[MAX_USERS];
};

int db::m_prodCnt = 0;
int db::m_userCnt = 0;
int db::m_rentsCnt = 0;
int db::m_userUnikey = 0;
void db::init()
{
    memset(prodArr, 0, sizeof(prodArr));
}

void db::printProdReservation(int _prodid)
{
    prodArr[_prodid]->sumOfReservers();
}


int db::getProdCount()
{
    return m_prodCnt;
}

int db::getUserCount()
{
    return m_userCnt;
}

int db::getRentsCount()
{
    return m_rentsCnt;
}


void db::newProd(string _name, int _prodid, int _rate, int _maxRent)
{
    prodArr[m_prodCnt] = new product( _name,  _prodid,  _rate,  _maxRent);
    m_prodCnt++;
}

void db::newUser(string _name, int _userid, string _pass)
{
    m_userArr[m_userCnt] = new user( _name, _userid,  _pass);
    m_userCnt++;
}


void db::newRent(int _prodid, int _day, int _hour, int _userid)

{
    if(_prodid <= getProdCount())
    {
        if(prodArr[_prodid]->newRenter( _day,  _hour,  _userid))
        {
            m_userArr[_userid]->updateProd(_prodid);
            m_rentsCnt++;
        }
        
    }
    
    else
    {
        return; //_prodid bigger than num of products.
    }
}

int db::userUnikey()
{
    //unique key for every user
    return m_userUnikey++;
}

#endif /* DB_H_ */
