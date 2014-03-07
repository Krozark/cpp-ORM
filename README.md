cpp-ORM
=========

Current build status : 
[![Build Status](https://travis-ci.org/Krozark/cpp-ORMg.png?branch=master)](https://travis-ci.org/Krozark/cpp-ORM)


A project to create a simple ORM.

You can symply create persistents objects using datas bases.

The object representation:
    Each object have to be in a separate table whith a pk colum named 'id' as autoincrement.
    each attr is a column in this table.

For the moment you have to create tables by hand.





functions
---------

* Persistant Object
 * print as json
 * save / update / load
* Foreign key
 * save / update / load
* ManyToMany
 * save / update / load / add / remove
* fiters
 * WHERE statement
 * exclude
 * order by
 * limite
* caching
* debug output (set ORM_DEBUG to ORM_DEBUG_XXX in debug.hpp)
* multi connection for a single object (select/save) [v 0.3]

Data bases supported
=====================

* MySql
* Sqlite3


Requirement
===========

* Mysql cppcon
* lib Sqlite3
* doxygen (for user doc only)

* Gcc 4.8+



TODO
====

* MAJ le cache pour fetch 2 BDD différente avec les même classe d'objets et pk identique, mais objets différents
* Clean le cache sur les objets qui ne sont plus liés en mémoires (free)


Instalation
===========

    ./build.sh
    sudo make install


Exemple
=======

You can see complet exemple in main.cpp

To build the exemple (the database is include)

    make all


```C++
 
    //#include <ORM/backends/MySql.hpp>
    //create your default database
    orm::MySqlBdd def("root","root","test");

    //#include <ORM/backends/Sqlite3.hpp>
    //orm::Sqlite3Bdd def("./datas/test.db"); //if you want to use sqlite3

    //make it as default
    orm::Bdd& orm::Bdd::Default = def;

    
    #include <ORM/fields.hpp>
    #include <ORM/models/SqlObject.hpp>
    //create you class
    class Perso : public orm::SqlObject<Perso>
    {
        public:
            Perso();
            orm::Attr<std::string> name;
            orm::Attr<int> pv;
            orm::Attr<int> lvl;
    
            MAKE_STATIC_COLUM(name,pv,lvl)
    };
    REGISTER_AND_CONSTRUCT(Perso,"perso",name,"nom",pv,"pv",lvl,"lvl")

    int main(int argc,char* argv[])
    {
        //connect to database
        orm::Bdd::Default.connect();
    
        //get perso with pk=1
        auto& p1 = Perso::get(1);
        //see it
        cout<<*p1<<endl;
        //modify it
        p1->pv +=14;
        //save it
        p1->save();


        //add one
        Perso p2;// = new Perso;
        p2.name = "test insert";
        p2.lvl = 75;
        p2.save(); //save it
        cout<<p2<<endl;

        // all
        cout<<"All persos"<<endl;
        std::list<std::shared_ptr<Perso> > lis= Perso::all();
        for(auto u : lis)
            cout<<*u<<endl;

        list.clear();
        //custom query
        Perso::query()\
            .filter(4,"gt",Perso::_lvl)\
            .filter(42,"gte",Perso::_lvl)\
            .filter("test","startswith",Perso::_name)\
            .exclude(4,"lt",Perso::_lvl)\
            .orderBy(Perso::_name)\
            .limit(42)\
            .get(lis); //get take a list<shared_ptr<T>>& or a T& as param
        for(auto u : lis)
            cout<<*u<<endl;


        orm::Bdd::Default.disconnect();
        return 0;
    }

```

Class
=====

All class are uder the orm namsspace


orm::SqlObject<T>
-----------------

Base class for persistent T class. It add all static methode / attribute to your class.

make some static method:
* std::shared_ptr\<T\> get(int pk)
* std::list\<std::shared_ptr\<T\>\> all()
* orm::QuerySet\<T\> T::query()  construct a queryset to make custom query

static member:
* Bdd* bdd_used : database where the object is contain
* std::string table : table name on the database

make member fonction:
* bool save(bool recursive=false)
* bool del(bool recursive=false)

Exemple: see main.cpp

orm::Attr\<T\>
------------

Make a T persistent in the dadabase.

You can acces to the value using:
* T value;


All operators are overloads to make a easy use of it.

orm::ManyToMany\<T,U\>
======================

T have to be the presistent class where the M2M is use, and U the persistent class.
I create a link with the 2 class, and you can acces to the U using:

accesor:
* std::list\<std::shared_ptr\<U\>\> .all()


orm::Bdd
---------

Base classe to deal with your database. Use specialize database (MySqlBdd, ...)

Constructor:
Bdd(const std::string& username,const std::string& pass,const std::string& bdd,const std::string& serveur,const std::string& port);


You can use some fonction:
* bool connect()
* bool disconnect()
* Query* query()
* Query* query(std::string&)
* Query* query(std::string&&)
* Query* preparedQuery(std::string&)
* Query* preparedQuery(std::string&&)


You can custom the default database:

    orm::MySqlBdd def("root","root","test");
    orm::Bdd& orm::Bdd::Default = def;

Macros
======

There are some macos to help.

MAKE_STATIC_COLUM(...)
----------------------

To call in your class with all persistent attrs in params. It will construct the static std::string to use (on filter ...)


REGISTER_AND_CONSTRUCT(klass,colum,[attr,colum]+)
-------------------------------------------------

Make the default constructor of your class, construct all comulm as static strings.
This macro simply call REGISTER_TABLE(klass,colum) and MAKE_CONSTRUCTOR(klass,__VA_ARGS__)


REGISTER_TABLE(klass,colum)
------------------------------

If you use REGISTER_AND_CONSTRUCT, you don't need to use it.

    template<>
    const std::string orm::SqlObject<klass>::table =colum;
    template<>
    orm::Bdd* orm::SqlObject<klass>::bdd_used = &orm::Bdd::Default;


MAKE_CONSTRUCTOR(klass[,attr,colum]+)
--------------------------------------

If you use REGISTER_AND_CONSTRUCT, you don't need to use it.

Make the default constructor for the class klass, and register all Att in params. It also call _MAKE_STRING_N to create attrs colum names as static.

     _MAKE_STRING_N(klass,NUM_ARGS(__VA_ARGS__),__VA_ARGS__)
    klass::klass(): _MAKE_ATTRS_N(NUM_ARGS(__VA_ARGS__),__VA_ARGS__)
    {
         _MAKE_REGISTER_ATTRS(NUM_ARGS(__VA_ARGS__),__VA_ARGS__)
    }


 _MAKE_STRING_N(klass,N,...)
----------------------------
If you use REGISTER_AND_CONSTRUCT, you don't need to use it.

N have to be the number of attrs (in ...)

Simply construct all string as:
    std::string klass::_attr = colum;


_MAKE_ATTRS_N(N,...)
--------------------
If you use REGISTER_AND_CONSTRUCT, you don't need to use it.

N have to be lenght of ...

simply add attr(colum) to constuctor for const initialize


_MAKE_REGISTER_ATTRS(N,...)
---------------------------------------
If you use REGISTER_AND_CONSTRUCT, you don't need to use it.

for each att in ...

    this->registerAttr(this->name);





