#include <ORM/MySQLBdd.hpp>
#include <ORM/MySQLQuery.hpp>

orm::MySQLBdd def("root","root","test");

orm::Bdd& orm::Bdd::Default = def;

#include "ORM/Attr.hpp"

class Perso : public orm::SQLObject<Perso>
{
    public:
        Perso() : name("name"), pv("pv"), lvl("lvl")
        {
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
    //orm::Bdd::Default = new orm::MySQLBdd("root","toor","test");
    orm::Bdd::Default.connect();

    //REGISTER_BDD(Perso,orm::Bdd::Default)

    Perso* p1 = Perso::get(1);
    cout<<*p1<<endl;

    return 0;
};
