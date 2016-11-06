/*
 * db.h
 *
 *  Created on: Nov 5, 2016
 *      Author: yan
 */

#ifndef DB_H_
#define DB_H_

#define MAX_RENTERS 5
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
class renter
{
public:
     renter(int _userid, int _sval);
private:
    int m_userId;
    int m_userSchedVal;
};

renter::renter(int _userid, int _sval)
{
    m_userId = _userid;
    m_userSchedVal = _sval;
}

class product
{
public:
    product(string _name, int _prodid, int _rate, int _maxRent);
    void newRenter(int _userid, int _sval);

    int m_currRenters;
    int getProdCount();
    void init();
    
private:
    string m_prodName;
    int m_prodId;
    int m_prodRate;
    int m_maxRentTime;
    renter *rentersArr[MAX_RENTERS];
};

int product::getProdCount()
{
    return m_currRenters;
}

product::product(string _name, int _prodid, int _rate, int _maxRent)
{
    m_prodName = _name;
    m_prodId = _prodid;
    m_prodRate = _rate;
    m_maxRentTime = _maxRent;
    m_currRenters = 0;
    init();
}

void product::newRenter(int _userid, int _sval)
{
     if(m_currRenters < MAX_RENTERS)
    {
       rentersArr[m_currRenters] = new renter(_userid, _sval);
       m_currRenters++;
    }
    
    else
    {
        return; //too many users in product
    }
}

void product::init()
{
    memset(rentersArr, 0, sizeof(rentersArr));
}


class db{
public:
    void newProd(string _name, int _prodid, int _rate, int _maxRent);
    
    void newUser(string _name, int _userid, string _pass);
    void newRent(int _prodid, int _userid, int _sval);

    int getProdCount();
    void init();
    int userUnikey();
    int getUserCount();
    int getRentsCount();

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


void db::newRent(int _prodid, int _userid, int _sval)

{
    if(_prodid <= getProdCount())
    {
        prodArr[_prodid]->newRenter(_userid, _sval);
        m_userArr[_userid]->updateProd(_prodid);
        m_rentsCnt++;
    }
    
    else{
        return; //_prodid bigger than num of products.
    }
}

int db::userUnikey()
{
    //unique key for every user
    return m_userUnikey++;
}

#endif /* DB_H_ */
