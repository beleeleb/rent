//
//  main.cpp
//  rent
//
//  Created by gali zorea on 03/11/2016.
//  Copyright © 2016 gali zorea. All rights reserved.
//
#include <iostream>
#include "db.h"
#include "sched.h"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    db mydb;
    //sched mysched;
    mydb.init();

    mydb.newProd("bike",0, 2, 2); //product name, product id, hourly rate, max hours to rate
    mydb.newProd("book",1, 4, 2);
    mydb.newProd("shoe",2, 5, 2);
    
    cout << "products: " << mydb.getProdCount()<< endl;


    mydb.newUser("yan1", mydb.userUnikey(), "1234"); // user name, user unique generated id, user password
    mydb.newUser("yan2", mydb.userUnikey(), "4567");
    mydb.newUser("yan3", mydb.userUnikey(), "5678");
    mydb.newUser("yan4", mydb.userUnikey(), "6789");
    
    cout << "users: " << mydb.getUserCount()<< endl;
    
 
    //unsigned long sval[2] = {0};
    //mysched.init();
    //setTime(1, 1, sval); //
    //setTime(4,3, sval);
    //setTime(6, 11, sval);
    mydb.newRent(0, 4, 3, 1); //product id, rental day(1-7), rental time (1-12), user id
    mydb.newRent(0, 6, 11, 2);
    mydb.newRent(0, 5, 5, 2);

    
    mydb.newRent(1, 5, 5, 3);
    mydb.newRent(2, 5, 5, 1);
    mydb.newRent(1, 5, 5, 0);
    
    cout << "products: " << mydb.getProdCount()<< endl;
    cout << "rents: " << mydb.getRentsCount()<< endl;
    
    mydb.printProdReservation(0); //print products reservations table according to
    mydb.printProdReservation(1);
    mydb.printProdReservation(2);
    return 0;
}
