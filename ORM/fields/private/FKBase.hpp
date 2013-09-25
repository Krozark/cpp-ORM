#ifndef ORM_FKBASE_HPP
#define ORM_FKBASE_HPP

#include <ORM/fields/private/VFK.hpp>
#include <memory>

namespace orm
{
    class Query;

    template<typename T>
    class FKBase : public VFK
    {
        public:
            FKBase(const FKBase&) = delete;

            ~FKBase(); ///< \todo --on cache counter

            virtual const SQLObjectBase& getObject(int max_depth=ORM_DEFAULT_MAX_DEPTH);
            virtual bool save(bool recursive=false);            
            virtual bool del(bool recursive=false);

            typedef T type;

            //T& operator*();
            T* operator->();

            FKBase<T>& operator=(const FKBase<T>& other);

        protected:
            //FKBase(const int& id,const std::string& colum,const bool nullable=true);//TODO ++on cache counter
            FKBase(const std::string& colum,const bool nullable=true);///< \todo ajouter au cache
            std::shared_ptr<T> value_ptr;

            virtual void print(std::ostream& output) const;
            virtual bool set(Query& query,const unsigned int& colum);
            virtual bool get(const Query& query,int& prefix,int max_depth);
            T* getObjectT_ptr(int max_depth = ORM_DEFAULT_MAX_DEPTH);

            virtual std::string makeName(const Bdd* bdd,const std::string& prefix,int max_depth) const;

            virtual void incDepth(int& depth,int max_depth) const;

    };
}

#include <ORM/fields/private/FKBase.tpl>

#endif
