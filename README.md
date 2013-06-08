cpp-ORM
=======

A project to create a simple ORM.

You can symply create persistents objects using datas bases.

The object representation:
    Each object have to be in a separate table whith a pk colum named 'id' as autoincrement.
    each attre is a colum in this table.

Data bases supported
=====================

* MySql


Requirement
===========

* Mysql cppcon


Class
=====

All class are uder the orm namsspace


orm::SQLObject<T>
-----------------

Base class for persistent T class. It add all static methode / attribute to your class.

make some static method:
* T* get(int pk)
* std::list\<T*\> all()
* std::list\<T*\> filter(const std::string& colum,const std::string& ope,const U& value);
* std::list\<T*\> filter(const Filter& filter);
* std::list\<T*\> filter(const std::list<Filter>& filters);

static member:
* Bdd* bdd_used : database where the object is contain
* std::string table : table name on the database

make member fonction:
* bool save(bool force=false)
* bool del() 


Exemple: see main.cpp

orm::Attr\<T\>
------------

Make a T persistent in the dadabase.

You can acces to the value using:
* T value;


All operators are overloads to make a easy use of it.

orm::VAttr
----------

Base class for Attr. you don't need to use it directly


orm::Filter
-----------

Construct a filter to make a query (where clause). Constructor 

template<typename T>
Filter(const std::string& colum,const std::string& ope, const T& value);


orm::Query
----------
Base classe for query.

Use to creat query in the database. You can use subclasse to make custom query, but it is not need. Create the using the ::Query of a Bdd.


orm::Bdd
---------

Base classe to deal with your database. Use specialize database (MySQLBdd, ...)

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

    orm::MySQLBdd def("root","root","test");
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
    const std::string orm::SQLObject<klass>::table =colum;
    template<>
    orm::Bdd* orm::SQLObject<klass>::bdd_used = &orm::Bdd::Default;


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



Exemple
=======

You can see complet exemple in main.cpp

    //create your default database
    orm::MySQLBdd def("root","root","test");
    //make it as default
    orm::Bdd& orm::Bdd::Default = def;
    
    //create you class
    class Perso : public orm::SQLObject<Perso>
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
        Perso* p1 = Perso::get(1);
        //see it
        cout<<*p1<<endl;
        //modify it
        p1->pv +=14;
        //save it
        p1->save();
    
        //don't forget to delete it
        delete p1;
    
        return 0;
    }


