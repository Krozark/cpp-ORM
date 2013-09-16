namespace orm
{
    /*template<typename T,bool NULLABLE>
    FK<T,NULLABLE>::FK(const int& id,const std::string& colum) : FKBase<T>(id,colum,NULLABLE)
    {
    }*/

    template<typename T,bool NULLABLE>
    FK<T,NULLABLE>::FK(const std::string& colum) : FKBase<T>(colum,NULLABLE)
    {
    }
}
