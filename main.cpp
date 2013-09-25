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
#include <ORM/models/SQLObject.hpp>

#include <iostream>


/*class Spell : public orm::SQLObject<Spell>
{
    public:
        Spell();
        orm::Attr<int> element;


        MAKE_STATIC_column(element);
};
REGISTER_AND_CONSTRUCT(Spell,"spell",element,"element")*/

class Stats : public orm::SQLObject<Stats>
{
    public:
        Stats();
        orm::Attr<int> pv;
        orm::Attr<int> pi;
        /*orm::Attr<int> intelligence;
          orm::Attr<int> force;
          orm::Attr<int> defence;
          orm::Attr<int> vattaque;
          orm::Attr<int> esquive;
          orm::Attr<int> chance;
          orm::Attr<int> charme;
          orm::Attr<int> mouvement;*/

        MAKE_STATIC_column(pv,pi/*,intelligence,force,defence,vattaque,esquive,chance,charme,mouvement*/)
};
REGISTER_AND_CONSTRUCT(Stats,"stats",pv,"pv",pi,"pi"/*,intelligence,"int",force,"force",defence,"def",vattaque,"vatq",esquive,"esq",chance,"chance",charme,"charme",mouvement,"mouvement"*/)

/**
* \todo ajouter à loadobjet un argument en plus : la colonne (facultatif)
*/
class Perso : public orm::SQLObject<Perso>
{
    public:
        Perso();
        orm::Attr<std::string> name;
        orm::Attr<int> lvl;
        orm::FK<Stats,false> stats;
        orm::FK<Stats,false> stats2;
        orm::FK<Perso,true> maitre;

        //orm::ManyToMany<Perso,Spell> spells;

        MAKE_STATIC_column(name,lvl,stats,stats2,maitre)
};
REGISTER_AND_CONSTRUCT(Perso,"perso",name,"name",lvl,"lvl",stats,"stats",stats2,"stats_tmp",maitre,"master")
//M2M_REGISTER(Perso,spells,Spell,"perso_spell","perso_id","spell_id")
//REGISTER(Perso,"perso",name,"name",lvl,"lvl",stats,"stats",stats2,"stats_tmp")
//Perso::Perso() : name(Perso::_name), lvl(Perso::_lvl), stats(Perso::_stats),stats2(Perso::_stats2)/*, spells(*this)*/
//{
//    name.registerAttr(*this);
//    lvl.registerAttr(*this);
//    stats.registerAttr(*this);
//    stats2.registerAttr(*this);
//}

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
   {
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


   }
   /*{

       list<Filter> filters = {
           //Filter("perso.lvl","gt",4),
           Filter("perso.name","startswith","test")
           //Filter("perso__stats.pv","gt",4)
       };
       std::list<std::shared_ptr<Perso>> lis;
       Perso::query().filter("test%","startswith",Perso::_name).get(lis);
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


    /*Bdd::Default.disconnect();

    sqlite3 * db;
    int result=sqlite3_open("./datas/test.db",&db);

    if (result != SQLITE_OK)
        std::cerr<<ROUGE<<"[ERROR] open"<<sqlite3_errstr(result)<<BLANC<<std::endl;

    sqlite3_stmt *statement;
    char query[] = "SELECT `perso`.`id` AS perso__id,\
                    `perso`.`master` AS perso__master,\
                    `perso`.`stats_tmp` AS perso__stats_tmp,\
                    `perso`.`stats` AS perso__stats,\
                    `perso`.`lvl` AS perso__lvl,\
                    `perso`.`name` AS perso__name\
                    FROM `perso` AS `perso` \
                    WHERE (`perso`.`lvl` > (?)) ";

    result = sqlite3_prepare_v2(db,query,sizeof(query)+1, &statement, NULL);
    if (result != SQLITE_OK)
        std::cerr<<ROUGE<<"[ERROR] prepare"<<sqlite3_errstr(result)<<BLANC<<std::endl;

    result = sqlite3_bind_int(statement,1,4);//,2,SQLITE_TRANSIENT);
    if (result != SQLITE_OK)
        std::cerr<<ROUGE<<"[ERROR] bind"<<sqlite3_errstr(result)<<BLANC<<std::endl;

    result = sqlite3_step(statement);
    if(result != SQLITE_ROW)
        std::cerr<<ROUGE<<"[ERROR] next"<<sqlite3_errstr(result)<<BLANC<<std::endl;

    int id = sqlite3_column_int(statement,0);
    int master = sqlite3_column_int(statement,1);
    int stats_tmp = sqlite3_column_int(statement,2);
    int stats = sqlite3_column_int(statement,3);
    int lvl = sqlite3_column_int(statement,4);
    const unsigned char* name = sqlite3_column_text(statement,5);

    std::cout<<"id:"<<id<<" master:"<<master<<" stats_tmp:"<<stats_tmp<<" stats:"<<stats<<" lvl:"<<lvl<<" name:"<<name<<std::endl;

    result = sqlite3_finalize(statement);
    if (result != SQLITE_OK)
        std::cerr<<ROUGE<<"[ERROR] finalize"<<sqlite3_errstr(result)<<BLANC<<std::endl;
       
    sqlite3_close(db);  */

    return 0;
};
