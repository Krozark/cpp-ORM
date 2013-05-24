#include <ORM/MySQLBdd.hpp>
#include <ORM/MySQLQuery.hpp>

orm::MySQLBdd def("root","root","test");

orm::Bdd& orm::Bdd::Default = def;

#include "ORM/Attr.hpp"
#include "ORM/SQLObject.hpp"

const std::string c_name = "nom";
const std::string c_pv = "pv";
const std::string c_lvl = "lvl";

class Perso : public orm::SQLObject<Perso>
{
    public:
        Perso() : name(c_name), pv(c_pv), lvl(c_lvl)
        {
            registerAttr(name);
            registerAttr(pv);
            registerAttr(lvl);
        };
        orm::Attr<std::string> name;
        orm::Attr<int> pv;
        orm::Attr<int> lvl;
};

REGISTER_TABLE(Perso,"perso")

using namespace orm;
using namespace std;

int main(int argc,char* argv[])
{ 
    orm::Bdd::Default.connect();

    //REGISTER_BDD(Perso,orm::Bdd::Default)

    Perso* p1 = Perso::get(1);
    cout<<"Current perso1 "<<*p1<<endl;
    cout<<" add 14 to pv"<<endl;
    p1->pv = p1->pv + 14;
    cout<<"Current perso1 "<<*p1<<endl;
    cout<<"save it"<<endl;
    cout<<p1->pv<<endl;
    p1->save();

    cout<<"All persos"<<*p1<<endl;
    std::list<Perso*> lis= Perso::all();
    for(auto u : lis)
        cout<<*u<<endl;

    return 0;
};
