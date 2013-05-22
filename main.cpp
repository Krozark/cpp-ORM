#include <ORM/MySQLBdd.hpp>
#include <ORM/MySQLQuery.hpp>

orm::MySQLBdd def("root","toor","test");

orm::Bdd& orm::Bdd::Default = def;

class Perso : public orm::SQLObject<Perso>
{
    public:
        std::string name;
        int pv;
        int lvl;
};
REGISTER_TABLE(Perso,"perso")

int main(int argc,char* argv[])
{ 
    //orm::Bdd::Default = new orm::MySQLBdd("root","toor","test");
    orm::Bdd::Default.connect();

    //REGISTER_BDD(Perso,orm::Bdd::Default)

    Perso::get(1);

    return 0;
};
