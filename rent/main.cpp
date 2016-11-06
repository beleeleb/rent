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
    sched mysched;
    mydb.init();
    cout << "products: " << mydb.getProdCount()<< endl;

    mydb.newProd("bike",0, 2, 2); //name, prodid, rate, maxhour
    mydb.newProd("book",1, 4, 2); //name, prodid, rate, maxhour
    mydb.newProd("shoe",2, 5, 2); //name, prodid, rate, maxhour

    mydb.newUser("yan1", mydb.userUnikey(), "1234");
    mydb.newUser("yan2", mydb.userUnikey(), "4567");
    mydb.newUser("yan3", mydb.userUnikey(), "5678");
    mydb.newUser("yan4", mydb.userUnikey(), "6789");
    cout << "users: " << mydb.getUserCount()<< endl;
    
    mydb.newRent(0, 1, 5); //prodid, useid, sval
    mydb.newRent(0, 2, 3);
    mydb.newRent(1, 1, 2);
    mydb.newRent(2, 0, 1);
    
    cout << "products: " << mydb.getProdCount()<< endl;
    cout << "rents: " << mydb.getRentsCount()<< endl;

    mysched.init();
    mysched.setTime(1, 1);
    mysched.setTime(4,3);
    mysched.setTime(6, 11);
    
    mysched.printSched();
    return 0;
}
