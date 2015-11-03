//#include <ORM/backends/MySql.hpp>
//orm::MySqlDB def("root","toor","test");
//orm::MySqlDB def("root","root","test");

#include <ORM/backends/Sqlite3.hpp>
orm::Sqlite3DB def("./test.db");

orm::DB& orm::DB::Default = def;

#include <ORM/all.hpp>

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

        orm::ManyToMany<Perso,Spell> spells;

        MAKE_STATIC_COLUMN(name,lvl,stats,stats2,maitre)
};
M2M_REGISTER(Perso,spells,Spell,"perso_spell","perso_id","spell_id")
REGISTER(Perso,"perso",name,"name",lvl,"lvl",stats,"stats",stats2,"stats_tmp",maitre,"master")
Perso::Perso() : name(Perso::$name), lvl(Perso::$lvl), stats(Perso::$stats),stats2(Perso::$stats2), maitre($maitre), spells(*this)
{
    name.registerAttr(*this);
    lvl.registerAttr(*this);
    stats.registerAttr(*this);
    stats2.registerAttr(*this);
    maitre.registerAttr(*this);
}
//REGISTER_AND_CONSTRUCT(Perso,"perso",name,"name",lvl,"lvl",stats,"stats",stats2,"stats_tmp",maitre,"master")


class TestTypes : public orm::SqlObject<TestTypes>
{
    public:
    TestTypes();

    orm::FK<TestTypes> fk;

    orm::TextField              textField;
    orm::CharField<255>         charField;
    orm::DateTimeField          datetimeField;
    orm::AutoDateTimeField      autodatetimeField;
    orm::AutoNowDateTimeField   autonowdatetimeField;

    orm::BooleanField           booleanField;
    orm::IntegerField           integerField;
    orm::FloatField             floatField;
    orm::DoubleField            doubleField;
    orm::UnsignedIntegerField   unsignedIntegerField;


    MAKE_STATIC_COLUMN(\
                       fk,\
                       textField,\
                       charField,\
                       datetimeField,\
                       autodatetimeField,\
                       autonowdatetimeField,\
                       booleanField,\
                       integerField,\
                       floatField,\
                       doubleField,\
                       unsignedIntegerField\
                      )
};
REGISTER_AND_CONSTRUCT(TestTypes,"test_types",\
                       fk,"fk",\
                       textField,"textField",\
                       charField,"charField",\
                       datetimeField, "datetimeField",\
                       autodatetimeField, "autodatetimeField",\
                       autonowdatetimeField, "autonowdatetimeField",\
                       booleanField,"booleanField",\
                       integerField,"integerField",\
                       floatField,"floatField",\
                       doubleField,"doubleField",\
                       unsignedIntegerField,"unsignedIntegerField"\
                      )
//merge all colums
class TestMergeHeritage : public orm::SqlExtends<TestMergeHeritage,TestTypes>
{
    public:
        TestMergeHeritage();

        orm::BooleanField   b;

        MAKE_STATIC_COLUMN(b)
};
REGISTER(TestMergeHeritage,"TestMergeHeritage",b,"b");
TestMergeHeritage::TestMergeHeritage() : b(TestMergeHeritage::$b)
{
    b.registerAttr(*static_cast<orm::SqlObject<TestMergeHeritage>*>(this));
};
/*
class TestMergeHeritage2 : public orm::SqlExtends<TestMergeHeritage2,TestMergeHeritage>
{
    public:
        TestMergeHeritage2();

        orm::BooleanField   b2;

        MAKE_STATIC_COLUMN(b2)
};
REGISTER(TestMergeHeritage2,"TestMergeHeritage2",b2,"b2");
TestMergeHeritage2::TestMergeHeritage2() : b2(TestMergeHeritage2::$b2)
{
    b2.registerAttr(*static_cast<SqlObject<TestMergeHeritage2>*>(this));
};
*/

namespace a
{
    class TestNamespace : public orm::SqlObject<TestNamespace>
    {
        public:
        TestNamespace();
        orm::CharField<255> name;

        MAKE_STATIC_COLUMN(name);

    };
}
REGISTER_AND_CONSTRUCT_WITH_NAMESPACE(a,TestNamespace,"TestNamespace",name,"name")

using namespace orm;
using namespace std;

void test_Datetime()
{

    std::cout<<"======= test_Datetime ======="<<std::endl;

    std::cout<<"date tests"<<std::endl;
    std::cout<<"1 month: "<<orm::DateTimeField::month(1)
    <<"\n 2 months: "<<orm::DateTimeField::month(2)
    <<"\n 1+1 months: "<<orm::DateTimeField::month(1) + orm::DateTimeField::month(1)
    <<"\n now (since the 1900/01/01): "<<orm::DateTimeField::now()
    <<"\n now + 30 day: "<<orm::DateTimeField::now() + orm::DateTimeField::day(30)
    <<"\n 1 hour: "<<orm::DateTimeField::time(1,0,0)
    <<"\n 2 hour: "<<orm::DateTimeField::time(2,0,0)
    <<"\n 1+1 hour: "<<orm::DateTimeField::time(1,0,0) + orm::DateTimeField::time(1,0,0)
    <<"\n 1 day: "<<orm::DateTimeField::date(0,0,1)
    <<"\n 1 day + 1 hour: "<<orm::DateTimeField::normalize(orm::DateTimeField::date(0,0,1) + orm::DateTimeField::time(1,0,0))
    <<"\n 1 day + 1 now: "<<orm::DateTimeField::normalize(orm::DateTimeField::date(0,0,1) + orm::DateTimeField::now())
    <<"\n 1 day + 1 hour + 1 now: "<<orm::DateTimeField::normalize(orm::DateTimeField::date(0,0,1) + orm::DateTimeField::time(1,0,0)+orm::DateTimeField::now())
    <<std::endl;

    std::cout<<"======= END test_Datetime =======\n"<<std::endl;
}

void test_TestTypes()
{
    std::cout<<"======= test_TestTypes ======="<<std::endl;

    TestTypes::type_ptr test = TestTypes::create();

    test->textField = "this is a long text for testing";
    test->charField = "test";
    test->datetimeField = orm::DateTimeField::now();

    test->booleanField = false;
    test->integerField = 42;
    test->floatField = 4.2;
    test->doubleField = 523.89;
    test->unsignedIntegerField = -1;

    cout<<"*** Current test: "<<*test<<endl;
    test->save();
    cout<<"**** Save current\n"<<endl;

    {
        TestTypes::type_ptr test2 = TestTypes::create();
        test2->fk = test;
        test2->textField = "this is another long text for testing";
        test2->charField = "test2";
        test2->datetimeField = orm::DateTimeField::now() + orm::DateTimeField::day(36);

        test2->booleanField = true;
        test2->integerField = -42;
        test2->floatField = -4.2;
        test2->doubleField = -533.89;
        test2->unsignedIntegerField = 1689;

        cout<<"*** Current test2: "<<*test<<endl;
        test2->save();
        cout<<"*** Save current\n"<<endl;
    }


    cout<<"++++++++ get all tests with DateTimeField > now() - 1 day (should have 2 result = 1 + 2) ++++++++"<<endl;

    TestTypes::result_type lis;
       TestTypes::query()
       .filter(orm::Q<TestTypes>(orm::DateTimeField::now()-orm::DateTimeField::day(1),orm::op::gt,TestTypes::$datetimeField))
       .get(lis);


    for(auto u : lis)
    {
        cout<<*u<<endl;
    }


    TestTypes::type_ptr test3 = TestTypes::create();
    test3->charField = "test3";
    test3->datetimeField = test->datetimeField - orm::DateTimeField::day(2);

    cout<<"*** Current test3: "<<*test<<endl;
    test3->save();
    cout<<"*** Save current\n"<<endl;


    cout<<"++++++++++++ All tests with DateTimeField < now() - 2 day (with ref to value, 2 result = 1 + 3) +++++++++++"<<endl;

    lis.clear();
    TestTypes::query()
        .filter(orm::Q<TestTypes>(orm::DateTimeField::now(),orm::op::lte,TestTypes::$datetimeField))
        .get(lis);

    for(auto u : lis)
    {
        cout<<*u<<endl;
    }

    std::cout<<"======= END test_TestTypes =======\n"<<std::endl;

}

void test_TestMergeHeritage()
{
    std::cout<<"======= test_TestMergeHeritage ======="<<std::endl;
    {
        {
            cout<<"*** All TestMergeHeritage"<<endl;
            auto list = TestMergeHeritage::all();
            for(auto& i : list)
            {
                std::cout<<(*i)<<endl;
                TestTypes::type_ptr base_ptr = i;
                std::cout<<"Base : "<<*base_ptr<<std::endl;
                base_ptr->integerField += 1;
                base_ptr->save();
            }
        }


        auto test = TestMergeHeritage::create();
        cout<<"*** Current test: "<<*test<<endl;
        cout<<"*** Store some values "<<endl;

        test->b = true;
        test->integerField = 42;

        cout<<"*** Current test: "<<*test<<endl;


        cout<<"**** Save current\n"<<endl;
        test->save(true);
        cout<<"*** Current test: "<<*test<<endl;

        cout<<"**** delete current\n"<<endl;
        test->del(true);
        cout<<"*** Current test: "<<*test<<endl;



        {
            cout<<"**** filter query"<<std::endl;

            auto list = TestMergeHeritage::result_type();
            TestMergeHeritage::query().filter(
                orm::Q<TestMergeHeritage>(58,orm::op::gt,TestMergeHeritage::$base_obj_ptr,TestTypes::$integerField)
            ).get(list);
            for(auto& i : list)
            {
                std::cout<<(*i)<<endl;
            }
        }

    }

    std::cout<<"======= END test_TestMergeHeritage =======\n"<<std::endl;
}

void test_Perso()
{
    std::cout<<"======= test_Perso ======="<<std::endl;

    DB* con2 = orm::DB::Default.clone();
    con2->connect();

    auto p1 = Perso::get(1,*con2);
    cout<<"*** Current perso1 "<<*p1<<endl;
    cout<<"*** add 1 to lvl"<<endl;
    p1->lvl = p1->lvl + 1;
    cout<<"*** Current perso1 "<<*p1<<endl;
    cout<<"*** save it"<<endl;
    cout<<"*** current lvl: "<<p1->lvl<<endl;
    p1->save();

    cout<<"*** Current perso1 "<<*p1<<endl;
    cout<<"*** add 2 to stats.pv"<<endl;
    p1->stats->pv += 2;
    cout<<"*** Current perso1 "<<*p1<<endl;
    p1->save();
    cout<<"*** Current perso1 "<<*p1<<endl;

    cout<<"\n*** delete p1->master->master"<<endl;
    p1->maitre->maitre.del(true);
    cout<<"*** Current perso1 "<<*p1<<endl;

    {
        Spell::result_type lis = p1->spells.all();
        std::cout<<"\n*** All his spells (result = [])"<<std::endl;
        for(auto u : lis)
        {
            cout<<*u<<endl;
        }
    }

    std::cout<<"\n*** Create spell s1"<<std::endl;
    Spell::type_ptr s1 = Spell::create();
    s1->name = "s1";
    s1->element = 1;
    s1->save();
    cout<<*s1<<std::endl;

    std::cout<<"\n*** Create spell s2"<<std::endl;
    Spell::type_ptr s2 = Spell::create();
    s2->name = "s2";
    s2->element = 2;
    s2->save();
    cout<<*s2<<std::endl;

    {
        std::cout<<"\n*** All spells (result = [s1, s2])"<<std::endl;
        Spell::result_type lis = Spell::all();
        for(auto& u : lis)
        {
            cout<<*u<<endl;
        }
    }

    std::cout<<"\n*** Add s1 and s2 to perso1"<<std::endl;
    p1->spells.add(s1);
    p1->spells.add(s2);


    {
        std::cout<<"\n*** All his spells with name s2 (result = [s2])"<<std::endl;
        Spell::result_type lis;
        p1->spells.query()
            .filter(std::string("s2"),orm::op::exact,Spell::$name)
            .get(lis);
        for(auto& u : lis)
        {
            cout<<*u<<endl;
        }
    }



    {
        std::cout<<"\n*** All his spells (result = [s1, s2])"<<std::endl;
        Spell::result_type lis;
        lis = p1->spells.all();
        for(auto u : lis)
        {
            cout<<*u<<endl;
        }
    }

    std::cout<<"======= END test_Perso =======\n"<<std::endl;

}

void test_Perso_Master()
{
    auto perso = Perso::create();

    std::cout<<"======= test_Perso_Master ======="<<std::endl;

    {
        cout<<"*** All perso"<<endl;
        auto list = Perso::all();
        for(auto& perso : list)
        {
            std::cout<<*perso<<endl;
        }
    }

    std::cout<<"*** create a new perso (perso2)"<<std::endl;
    perso->name = "perso2";
    perso->lvl = 18;

    std::cout<<"*** create it's master (master)"<<std::endl;
    perso->maitre->name = "master"; //auto create it if nedeed
    perso->maitre->lvl = 78;

    perso->save(true); //true for recursion save (master)

    {
        cout<<"*** All perso"<<endl;
        auto list = Perso::all();
        for(auto& perso : list)
        {
            std::cout<<*perso<<endl;
        }
    }

    std::cout<<"======= END test_Perso_Master =======\n"<<std::endl;
}


int main(int argc,char* argv[])
{

    orm::DB::Default.connect();

    orm::Tables::drop();
    orm::Tables::create();

    //test_Datetime();

    //test_TestTypes();
    test_TestMergeHeritage();

    //test_Perso();
    //test_Perso_Master();


    DB::Default.disconnect();
    return 0;
};
