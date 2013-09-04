#include <ORM/backends/MySql.hpp>

orm::MySQLBdd def("root","toor","test");
//orm::MySQLBdd def("root","toor","test");

orm::Bdd& orm::Bdd::Default = def;

#include <ORM/fields/Attr.hpp>
#include <ORM/fields/FK.hpp>
#include <ORM/fields/ManyToMany.hpp>
#include <ORM/models/SQLObject.hpp>


class Spell : public orm::SQLObject<Spell>
{
    public:
        Spell();
        orm::Attr<int> element;


        MAKE_STATIC_COLUM(element);
};
REGISTER_AND_CONSTRUCT(Spell,"spell",element,"element")

class Stats : public orm::SQLObject<Stats>
{
    public:
        Stats();
        orm::Attr<int> pv;
        orm::Attr<int> pi;
        orm::Attr<int> intel;
        orm::Attr<int> force;
        orm::Attr<int> def;
        orm::Attr<int> vatq;
        orm::Attr<int> esq;
        orm::Attr<int> chance;
        orm::Attr<int> charme;
        orm::Attr<int> mouvement;

        MAKE_STATIC_COLUM(pv,pi,intel,force,def,vatq,esq,chance,charme,mouvement)
};
REGISTER_AND_CONSTRUCT(Stats,"stats",pv,"pv",pi,"pi",intel,"int",force,"force",def,"def",vatq,"vatq",esq,"esq",chance,"chance",charme,"charme",mouvement,"mouvement")

//TODO ajouter à loadobjet un argument en plus : la colonne (facultatif)
class Perso : public orm::SQLObject<Perso>
{
    public:
        Perso();
        orm::Attr<std::string> name;
        orm::Attr<int> lvl;
        orm::FK<Stats> stats;
        //orm::FK<Stats> stats2;

        //orm::ManyToMany<Perso,Spell> spells;

        MAKE_STATIC_COLUM(name,lvl,stats/*,stats2*/)
};
//REGISTER_AND_CONSTRUCT(Perso,"perso",name,"name",lvl,"lvl",stats,"stats")
//M2M_REGISTER(Perso,spells,Spell,"perso_spell","perso_id","spell_id")
REGISTER(Perso,"perso",name,"name",lvl,"lvl",stats,"stats"/*,stats2,"stats_tmp"*/)
Perso::Perso() : name(Perso::_name), lvl(Perso::_lvl), stats(Perso::_stats)/*, stats2(Perso::_stats2)*//*, spells(*this)*/
{
    name.registerAttr(*this);
    lvl.registerAttr(*this);
    stats.registerAttr(*this);
    //stats2.registerAttr(*this);
}

using namespace orm;
using namespace std;

int main(int argc,char* argv[])
{ 
    orm::Bdd::Default.connect();
    //REGISTER_BDD(Perso,orm::Bdd::Default)
    
    auto& p1 = Perso::get(1);
    cout<<"Current perso1 "<<*p1<<endl;
    cout<<" add 1 to lvl"<<endl;
    p1->lvl = p1->lvl + 1;
    cout<<"Current perso1 "<<*p1<<endl;
    cout<<"save it"<<endl;
    cout<<"current lvl: "<<p1->lvl<<endl;
    p1->save();


    cout<<"All persos"<<endl;
    std::list<std::shared_ptr<Perso> > lis= Perso::all();
    for(auto u : lis)
        cout<<*u<<endl;

    /*

    cout<<"Create Perso"<<endl;
    Perso p2;

    p2.name = "test insert";
    p2.lvl = 75;
    p2.save(true);

    cout<<"Change PV to +=20"<<endl;
    p2.stats->pv+= 20;
    cout<<p2<<endl;

    cout<<"save it"<<endl;
    p2.save(true);

    cout<<"All persos current="<<p2<<endl;
    lis= Perso::all();
    for(auto u : lis)
        cout<<*u<<endl;

    {

        std::list<std::shared_ptr<Perso> > lis= Perso::filter(Filter(Perso::_lvl,"gt",4));
        for(auto u : lis)
            cout<<*u<<endl;
    }
    {

        list<Filter> filters = {
            Filter(Perso::_lvl,"gt",4),
            Filter(Perso::_name,"startswith","tes"),
            Filter(Stats::_pv,"gt",4)
        };
        std::list<std::shared_ptr<Perso> > lis= Perso::filter(filters);
        for(auto u : lis)
            cout<<*u<<endl;
    }
    
    
    cout<<"delete it"<<endl;
    p2.del();

    cout<<"All persos current current="<<p2<<endl;
    lis= Perso::all();
    for(auto u : lis)
        cout<<*u<<endl;

    cout<<"Perso Cache"<<endl;
    Perso::cache.__print__();

    cout<<"Stats Cache"<<endl;
    Stats::cache.__print__();
    */
    /*
    const std::list<std::shared_ptr<Spell> >& spells = p1->spells.all();
    for(auto u : spells)
        cout<<*u<<endl;
    */
    

    return 0;
};
