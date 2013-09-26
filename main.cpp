//#include <ORM/backends/MySql.hpp>
//orm::MySQLBdd def("root","toor","test");
//orm::MySQLBdd def("root","root","test");

#include <ORM/backends/Sqlite3.hpp>
orm::Sqlite3Bdd def("./datas/test.db");

orm::Bdd& orm::Bdd::Default = def;

/**
 * \todo ADD transaction (start transaction / commit)
 **/

#include <ORM/fields.hpp>
#include <ORM/fields/ManyToMany.hpp>
#include <ORM/models/SQLObject.hpp>

#include <iostream>


class Spell : public orm::SQLObject<Spell>
{
    public:
        Spell();
        orm::CharField<255> name;
        orm::IntegerField element;

        MAKE_STATIC_COLUMN(name,element);

};
REGISTER_AND_CONSTRUCT(Spell,"spell",name,"name",element,"element")

class Stats : public orm::SQLObject<Stats>
{
    public:
        Stats();
        orm::IntegerField pv;
        orm::IntegerField pi;
        /*orm::IntegerField intelligence;
        orm::IntegerField force;
        orm::IntegerField defence;
        orm::IntegerField vattaque;
        orm::IntegerField esquive;
        orm::IntegerField chance;
        orm::IntegerField charme;
        orm::IntegerField mouvement;*/

        MAKE_STATIC_COLUMN(pv,pi/*,intelligence,force,defence,vattaque,esquive,chance,charme,mouvement*/)
};
REGISTER_AND_CONSTRUCT(Stats,"stats",pv,"pv",pi,"pi"/*,intelligence,"int",force,"force",defence,"def",vattaque,"vatq",esquive,"esq",chance,"chance",charme,"charme",mouvement,"mouvement"*/)

class Perso : public orm::SQLObject<Perso>
{
    public:
        Perso();
        orm::CharField<255> name;
        orm::IntegerField lvl;
        orm::FK<Stats,false> stats;
        orm::FK<Stats,false> stats2;
        orm::FK<Perso,true> maitre;

        orm::ManyToMany<Perso,Spell> spells;

        MAKE_STATIC_COLUMN(name,lvl,stats,stats2,maitre)
};
//REGISTER_AND_CONSTRUCT(Perso,"perso",name,"name",lvl,"lvl",stats,"stats",stats2,"stats_tmp",maitre,"master")
M2M_REGISTER(Perso,spells,Spell,"perso_spell","perso_id","spell_id")
REGISTER(Perso,"perso",name,"name",lvl,"lvl",stats,"stats",stats2,"stats_tmp",maitre,"master")
Perso::Perso() : name(Perso::_name), lvl(Perso::_lvl), stats(Perso::_stats),stats2(Perso::_stats2), maitre(_maitre), spells(*this)
{
    name.registerAttr(*this);
    lvl.registerAttr(*this);
    stats.registerAttr(*this);
    stats2.registerAttr(*this);
    maitre.registerAttr(*this);
}

using namespace orm;
using namespace std;

int main(int argc,char* argv[])
{
    orm::Bdd::Default.connect();
    //REGISTER_BDD(Perso,orm::Bdd::Default)

   /*{ 
        auto& p1 = Perso::get(1);
        cout<<"Current perso1 "<<*p1<<endl;
        cout<<" add 1 to lvl"<<endl;
        p1->lvl = p1->lvl + 1;
        cout<<"Current perso1 "<<*p1<<endl;
        cout<<"save it"<<endl;
        cout<<"current lvl: "<<p1->lvl<<endl;
        p1->save();

        cout<<"Current perso1 "<<*p1<<endl;
        cout<<" add 2 to stats.pv"<<endl;
        p1->stats->pv += 2;
        cout<<"Current perso1 "<<*p1<<endl;
        p1->save(true);
        cout<<"Current perso1 "<<*p1<<endl;

        cout<<"delete p1->master->master"<<endl;
        p1->maitre->maitre.del(true);

        cout<<"Current perso1 "<<*p1<<endl;
    }*/

   /*{
       cout<<"All persos"<<endl;
       std::list<std::shared_ptr<Perso> > lis= Perso::all();
       for(auto u : lis)
           cout<<*u<<endl;
   }*/

   /*{
       cout<<"Create Perso"<<endl;
       Perso p2;// = new Perso;

       p2.name = "test insert";
       p2.lvl = 75;
       p2.save();

       cout<<"Change PV to +=20"<<endl;
       p2.stats->pv+= 20;
       cout<<p2<<endl;

       cout<<"save it"<<endl;
       //p2.save();

       cout<<"All persos (current="<<p2<<")"<<endl;
       std::list<std::shared_ptr<Perso> > lis= Perso::all();
       for(auto u : lis)
           cout<<*u<<endl;

    }*/
   /*{
       Perso p2;

       std::list<Cache<Perso>::type_ptr> results;
       Perso::query()\
           .filter(4,"gt",Perso::_lvl)\
           .filter(42,"gte",Perso::_lvl)\
           .exclude(4,"lt",Perso::_lvl)\
           .orderBy(Perso::_name)\
           .get(p2);

       std::cout<<p2<<std::endl;

       cout<<"All perso"<<endl;
       Perso::query().get(results);
       for(auto& perso : results)
           cout<<*perso<<endl;

       results.clear();

       cout<<"All perso where lvl < 200"<<endl;
       Perso::query().filter(200,"lt",Perso::_lvl).get(results);
       for(auto& perso : results)
           cout<<*perso<<endl;


   }*/
   /*{

       std::list<std::shared_ptr<Perso>> lis;
       Perso::query().filter(string("test"),"startswith",Perso::_name).get(lis);
       for(auto u : lis)
           cout<<*u<<endl;
   }*/


    /*{
        cout<<"Perso Cache"<<endl;
        Perso::cache.__print__();

        cout<<"Stats Cache"<<endl;
        Stats::cache.__print__();
    }*/

    /*
       const std::list<std::shared_ptr<Spell> >& spells = p1->spells.all();
       for(auto u : spells)
       cout<<*u<<endl;
       */

    /*{
       std::list<std::shared_ptr<Spell>> list;
       Spell::query().get(list);
       for(auto u : list)
           cout<<*u<<endl;
    }*/

    auto& p1 = Perso::get(1);
    std::cout<<*p1<<std::endl;

    p1->spells.query();




    Bdd::Default.disconnect();
    return 0;
};
