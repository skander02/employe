#include "connexion.h"

connexion::connexion()
{

}
bool connexion::create_cnx(){

    bool test=false;
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("SmartAMB");
       db.setUserName("system ");
       db.setPassword("youssef");
    if(db.open())
        test=true;
    return test;
}

void connexion::close_cnx(){db.close();}
