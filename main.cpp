#include <ORM/MySQLBdd.hpp>
#include <ORM/MySQLQuery.hpp>

orm::MySQLBdd def("root","root","test");
//orm::MySQLBdd def("root","toor","test");

orm::Bdd& orm::Bdd::Default = def;

#include "ORM/Attr.hpp"
#include "ORM/FK.hpp"
#include "ORM/SQLObject.hpp"

class Perso : public orm::SQLObject<Perso>
{
    public:
        Perso();
        orm::Attr<std::string> name;
        orm::Attr<int> lvl;
        orm::FK<int> stats;

        MAKE_STATIC_COLUM(name,pv,lvl,stats)
};
REGISTER_AND_CONSTRUCT(Perso,"perso",name,"name",lvl,"lvl",stats,"stats")


using namespace orm;
using namespace std;

int main(int argc,char* argv[])
{ 
    orm::Bdd::Default.connect();

    //REGISTER_BDD(Perso,orm::Bdd::Default)

    Perso* p1 = Perso::get(1);
    cout<<"Current perso1 "<<*p1<<endl;
    cout<<" add 1 to lvl"<<endl;
    p1->lvl = p1->lvl + 1;
    cout<<"Current perso1 "<<*p1<<endl;
    cout<<"save it"<<endl;
    cout<<p1->lvl<<endl;
    p1->save();

    cout<<"All persos"<<*p1<<endl;
    std::list<Perso*> lis= Perso::all();
    for(auto u : lis)
        cout<<*u<<endl;
    for(Perso* p:lis)
        delete p;

    cout<<"Create Perso"<<endl;
    Perso p2;
    p2.name = "test insert";
    p2.lvl = 75;
    cout<<p2<<endl;

    cout<<"save it"<<endl;
    p2.save();

    cout<<"All persos current="<<p2<<endl;
    lis= Perso::all();
    for(auto u : lis)
        cout<<*u<<endl;
    for(Perso* p:lis)
        delete p;
    
    list<Filter> filters = {
        Filter(Perso::_lvl,"gt",4),
        Filter(Perso::_name,"startswith","tes")
    };

    lis = Perso::filter(filters);
    for(auto u : lis)
        cout<<*u<<endl;
    for(Perso* p:lis)
        delete p;

    cout<<"delete it"<<endl;
    p2.del();

    cout<<"All persos current current="<<p2<<endl;
    lis= Perso::all();
    for(auto u : lis)
        cout<<*u<<endl;
    for(Perso* p:lis)
        delete p;
    


    return 0;
};
