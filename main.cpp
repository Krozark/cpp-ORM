//#include <ORM/backends/MySql.hpp>
//orm::MySQLBdd def("root","toor","test");
//orm::MySQLBdd def("root","root","test");

#include <ORM/backends/Sqlite3.hpp>
orm::Sqlite3Bdd def("./datas/test.db");

orm::Bdd& orm::Bdd::Default = def;

#include <ORM/fields.hpp>
#include <ORM/models/SQLObject.hpp>

#include <iostream>


/*class Spell : public orm::SQLObject<Spell>
{
    public:
        Spell();
        orm::Attr<int> element;


        MAKE_STATIC_COLUM(element);
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

        MAKE_STATIC_COLUM(pv,pi/*,intelligence,force,defence,vattaque,esquive,chance,charme,mouvement*/)
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

        MAKE_STATIC_COLUM(name,lvl,stats,stats2,maitre)
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
    //orm::Bdd::Default.connect();
    //REGISTER_BDD(Perso,orm::Bdd::Default)

    /*
   { 
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
    }
    */

    /*
   {
       cout<<"All persos"<<endl;
       std::list<std::shared_ptr<Perso> > lis= Perso::all();
       for(auto u : lis)
       cout<<*u<<endl;
   }
    */

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
       //auto& p1 = Perso::get(1);
       Perso p2;

       std::list<Cache<Perso>::type_ptr> results;
       //QuerySet<Perso> queryset = Perso::query();
       //queryset.filter(4,"gt",Perso::_maitre,Perso::_lvl).filter(42,"exact",Perso::_lvl).exclude(4,"lt",Perso::_lvl).orderBy(Perso::_name).limit(10).get(p2);

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
   /*    {

       list<Filter> filters = {
       Filter(Perso::_lvl,"gt",4),
       Filter(Perso::_name,"startswith","tes"),
       Filter(Stats::_pv,"gt",4)
       };
       std::list<std::shared_ptr<Perso> > lis= Perso::filter(filters);
       for(auto u : lis)
       cout<<*u<<endl;
       }



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

    ///SQLITE3 tests
    sqlite3 * dbConn; // store db connextion
    // open db
    int result=sqlite3_open("./datas/test.db",&dbConn);

    if (result != SQLITE_OK)
    {
        std::cerr<<"Failed to open database "<<sqlite3_errstr(result)<<std::endl;
        sqlite3_close(dbConn) ;
    }

    /*
     * Prepare statement
     */    
    sqlite3_stmt *statement;
    char query[] = "SELECT id,name,lvl,stats,stats_tmp,master FROM perso;";

    result = sqlite3_prepare_v2(dbConn,query, sizeof(query)+1, &statement, NULL);
    if (result != SQLITE_OK) {
        std::cerr<<"Failed to prepare database "<<sqlite3_errstr(result)<<std::endl;
        sqlite3_close(dbConn) ;
    }


    /*
     * Get data
     */
    
    int id;
    std::string name;
    int lvl;
    int stats;
    int stats_tmp;
    int master;


    while((result = sqlite3_step (statement)) == SQLITE_ROW) // can read data
    {
            id = sqlite3_column_int(statement,0);
            name = (const char*)sqlite3_column_text(statement,1);
            lvl = sqlite3_column_int(statement,2);
            stats = sqlite3_column_int(statement,3);
            stats_tmp = sqlite3_column_int(statement,4);
            master = sqlite3_column_int(statement,5);

            std::cout<<"pk:"<<id<<", name:"<<name<<", lvl:"<<lvl<<", stats:"<<stats<<", stats_tmp"<<stats_tmp<<", master:"<<master<<std::endl;

    }

    result = sqlite3_close(dbConn);// free db and close
    while(result != SQLITE_OK)
    {
        std::cerr<<"Failed to close database "<<sqlite3_errstr(result)<<std::endl;
        result = sqlite3_close(dbConn);

    }

    return 0;
};
