//#include <ORM/backends/MySql.hpp>
//orm::MySqlDB def("root","toor","test");
//orm::MySqlDB def("root","root","test");

#include <ORM/backends/Sqlite3.hpp>
orm::Sqlite3DB def("./test.db");

orm::DB& orm::DB::Default = def;

/**
 * \todo ADD transaction (start transaction / commit)
 **/

#include <ORM/fields.hpp>
#include <ORM/fields/ManyToMany.hpp>
#include <ORM/models/SqlObject.hpp>
#include <ORM/backends/op.hpp>

#include <iostream>


class Spell : public orm::SqlObject<Spell>
{
    public:
        Spell();
        orm::CharField<255> name;
        orm::IntegerField element;

        MAKE_STATIC_COLUMN(name,element);

};
REGISTER_AND_CONSTRUCT(Spell,"spell",name,"name",element,"element")

class Stats : public orm::SqlObject<Stats>
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

class Perso : public orm::SqlObject<Perso>
{
    public:
        Perso();
        orm::CharField<255> name;
        orm::IntegerField lvl;
        orm::FK<Stats,false> stats;
        orm::FK<Stats,false> stats2;
        orm::FK<Perso,true> maitre;

        //orm::ManyToMany<Perso,Spell> spells;

        MAKE_STATIC_COLUMN(name,lvl,stats,stats2,maitre)
};
//REGISTER_AND_CONSTRUCT(Perso,"perso",name,"name",lvl,"lvl",stats,"stats",stats2,"stats_tmp",maitre,"master")
/*M2M_REGISTER(Perso,spells,Spell,"perso_spell","perso_id","spell_id")
REGISTER(Perso,"perso",name,"name",lvl,"lvl",stats,"stats",stats2,"stats_tmp",maitre,"master")
Perso::Perso() : name(Perso::_name), lvl(Perso::_lvl), stats(Perso::_stats),stats2(Perso::_stats2), maitre(_maitre), spells(*this)
{
    name.registerAttr(*this);
    lvl.registerAttr(*this);
    stats.registerAttr(*this);
    stats2.registerAttr(*this);
    maitre.registerAttr(*this);
}*/
REGISTER_AND_CONSTRUCT(Perso,"perso",name,"name",lvl,"lvl",stats,"stats",stats2,"stats_tmp",maitre,"master")


class TestTypes : public orm::SqlObject<TestTypes>
{
    public:
    TestTypes();

    orm::FK<TestTypes> fk;

    orm::BooleanField   booleanField;
    orm::CharField<255> charField;
    orm::DateTimeField  datetimeField;
    orm::IntegerField   integerField;
    orm::FloatField     floatField;
    orm::DoubleField    doubleField;
    orm::TextField      textField;


    MAKE_STATIC_COLUMN(\
                       fk,\
                       booleanField,\
                       charField,\
                       datetimeField,\
                       integerField,\
                       floatField,\
                       doubleField,\
                       textField\
                      )
};
REGISTER_AND_CONSTRUCT(TestTypes,"test_types",\
                       fk,"fk",\
                       booleanField,"booleanField",\
                       charField,"charField",\
                       datetimeField, "datetimeField",\
                       integerField,"integerField",\
                       floatField,"floatField",\
                       doubleField,"doubleField",\
                       textField,"textField"\
                      )
//merge all colums
class TestMergeHeritage : public TestTypes
{
    public:
        //TestMergeHeritage();

        //orm::BooleanField   b;

        //MAKE_STATIC_COLUMN(b)
};
//REGISTER_AND_CONSTRUCT(TestMergeHeritage,"TestMergeHeritage",b,"b")
REGISTER_TABLE(TestMergeHeritage,"TestMergeHeritage")

using namespace orm;
using namespace std;

int main(int argc,char* argv[])
{
    orm::DB::Default.connect();
    //REGISTER_DB(Perso,orm::DB::Default)
    
    DB* con2 = orm::DB::Default.clone();
    con2->connect();

    //TestTypes::drop();
    //TestTypes::create();
    //TestTypes::clear();

    orm::Tables::drop();
    orm::Tables::create();


    {
        TestTypes test;
        test.booleanField = false;
        test.charField = "test";
        //test.datetimeField = "";
        test.integerField = 42;
        test.floatField = 4.2;
        test.doubleField = 4.2;
        test.textField = "this is a long text for testing";

        cout<<"Current test"<<test<<endl;
        test.save();
        cout<<"Save current"<<endl;
    }
    std::cout<<"=============="<<std::endl;
    { 
        auto p1 = Perso::get(1,*con2);
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
        p1->save();
        cout<<"Current perso1 "<<*p1<<endl;

        cout<<"delete p1->master->master"<<endl;
        p1->maitre->maitre.del(true);

        cout<<"Current perso1 "<<*p1<<endl;
    }
    std::cout<<"=============="<<std::endl;

   {
       cout<<"All persos"<<endl;
       std::list<Cache<Perso>::type_ptr> lis= Perso::all();
       for(auto u : lis)
       {
            cout<<*u<<endl;
       }
   }
    std::cout<<"=============="<<std::endl;

   {
       cout<<"Create Perso"<<endl;
       Perso p2;// = new Perso;

       p2.name = "test insert";
       p2.lvl = 75;
       p2.save();

       cout<<"Change PV to +=20"<<endl;
       p2.stats->pv+= 20;
       cout<<p2<<endl;

       cout<<"save it"<<endl;
       p2.save();

       cout<<"All persos (current="<<p2<<")"<<endl;
       std::list<std::shared_ptr<Perso> > lis= Perso::all();
       for(auto u : lis)
       {
            cout<<*u<<endl;
       }

   }
    std::cout<<"=============="<<std::endl;
   {
       Perso p2;


       Perso::query()
           .filter(Q<Perso>(4,orm::op::gt,Perso::_lvl)
                   and Q<Perso>(42,orm::op::gte,Perso::_lvl)
                   and not Q<Perso>(4,orm::op::lt,Perso::_lvl)
                  )
           .orderBy(Perso::_name)
           .get(p2);
       std::cout<<p2<<std::endl;

       
      // Chained way for same result
      // Perso::query()
      //  .filter(4,orm::op::gt,Perso::_lvl)
      //  .filter(42,orm::op::gte,Perso::_lvl)
      //  .exclude(4,orm::op::lt,Perso::_lvl)
      //  .orderBy(Perso::_name)
      //  .get(p2);
      // 


       std::list<Cache<Perso>::type_ptr> results;
       /*Perso p;// = new Perso;
       p.name="test";
       p.maitre->name="test master";
       p.maitre->lvl = 5;
       p.save();

       std::cout<<p<<std::endl;
    
       Perso::query()
           .filter(4,orm::op::gt,Perso::_maitre,Perso::_lvl)
           .orderBy(Perso::_name)
           .get(results);
       for(auto& perso : results)
           cout<<*perso<<endl;


       results.clear();*/

       cout<<"All perso"<<endl;
       Perso::query().get(results);
       for(auto& perso : results)
       {
           cout<<perso.get()<<std::endl;
           std::cout<<*perso<<endl;
       }

       results.clear();

       cout<<"All perso where lvl < 200"<<endl;
       Perso::query().filter(200,orm::op::lt,Perso::_lvl).get(results);
       for(auto& perso : results)
       {
           cout<<perso.get()<<std::endl;
           std::cout<<*perso<<endl;
       }


   }
    std::cout<<"=============="<<std::endl;
   {

       std::list<std::shared_ptr<Perso>> lis;
       Perso::query().filter(string("test"),orm::op::startswith,Perso::_name).get(lis);
       for(auto u : lis)
           cout<<*u<<endl;
   }

    std::cout<<"=============="<<std::endl;


   /*{ 
       auto& p1 = Perso::get(1);
       const std::list<std::shared_ptr<Spell> >& spells = p1->spells.all();
       for(auto u : spells)
           cout<<*u<<endl;
   }
       
    std::cout<<"=============="<<std::endl;

    {
       std::list<std::shared_ptr<Spell>> list;
       Spell::query().get(list);
       for(auto u : list)
           cout<<*u<<endl;
    }

    std::cout<<"=============="<<std::endl;
    {
        auto& p1 = Perso::get(1);
        std::cout<<"perso pk=1:\n"<<*p1<<std::endl;

        auto& stats = Stats::get(1);
        p1->stats = stats;

        std::list<std::shared_ptr<Spell>> list;
        p1->spells.query()\
            .filter(2,"exact",Spell::_element)\
            .get(list);

        cout<<"sorts d'element == 2"<<endl;
        for(auto u : list)
            cout<<*u<<endl;

        cout<<"sorts du perso"<<endl;
        for(auto u : p1->spells.all())
            cout<<*u<<endl;

        auto& sort = Spell::get(1);
        cout<<"sort pk = 1.\n"<<*sort<<endl;

        p1->spells.add(sort);
        p1->spells.remove(sort);

    }*/

    std::cout<<"=============="<<std::endl;


    DB::Default.disconnect();
    return 0;
};
