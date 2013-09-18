/***
* \mainpage
*
* \section welcome Welcome
* Welcome to the official CPP-ORM documentation. Here you will find a detailed
* view of all the ORM classes and functions. <br/>
*
* \section example Short example
* Here is a short example, to show you how simple it is to use CPP-ORM :
*
* \code
*
* #include <ORM/backends/MySql.hpp>
*
* orm::MySQLBdd def("root","toor","test");
* orm::Bdd& orm::Bdd::Default = def;
*
* #include <ORM/fields.hpp>
* #include <ORM/models/SQLObject.hpp>
*
* class Stats : public orm::SQLObject<Stats>
* {
*    public:
*        Stats();
*        orm::Attr<int> hp;
*        orm::Attr<int> mana;
*
*         MAKE_STATIC_COLUM(hp,mana)
* };
* REGISTER_AND_CONSTRUCT(Stats,"stats",hp,"hp",mana,"mana")
*
* class Player : public orm::SQLObject<Player>
* {
*    public:
*        Perso();
*        orm::Attr<std::string> name;
*        orm::Attr<int> lvl;
*        orm::FK<Stats,false> stats;
*        orm::FK<Stats,false> stats2;
*        orm::FK<Perso,true> master;
*
*        MAKE_STATIC_COLUM(name,lvl,stats,stats2,master)
* };
* REGISTER_AND_CONSTRUCT(Perso,"perso",name,"name",lvl,"lvl",stats,"stats",stats2,"stats_tmp",master,"master")
*
* using namespace orm;
* using namespace std;
*
* int main(int argc,char* argv[])
* {
*    orm::Bdd::Default.connect();
*    //REGISTER_BDD(Perso,orm::Bdd::Default) // optional : Bdd::Default is use by default
*
*    auto& p1 = Player::get(1); //get Player of pk = 1
*
*    cout<<"Current perso1 "<<p1<<endl;
*    cout<<" add 1 to lvl"<<endl;
*    p1.lvl += 1;
*    cout<<"Current perso1 "<<p1<<endl;
*
*    cout<<"save it"<<endl;
*    cout<<"current lvl: "<<p1.lvl<<endl;
*    p1.save();
*    cout<<"Current perso1 "<<p1<<endl;
*
*    cout<<" add 2 to stats.pv"<<endl;
*    p1.stats->pv += 2;
*    cout<<"Current perso1 "<<p1<<endl;
*    p1.save(true);
*    cout<<"Current perso1 "<<*p1<<endl;
*
*    return 0;
* }
* \endcode
**/
