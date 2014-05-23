#ifndef ORM_ATTR_HPP
#define ORM_ATTR_HPP

#include <ostream>
#include <utility>
#include <string>

#include <ORM/fields/private/VAttr.hpp>

namespace orm
{
    class Query;

    /**
     * \brief Store a value ass database row
     **/
    template<typename T>
    class Attr : public VAttr
    {
        public:
            /**
             * \brief Make a Attr
             *
             * \param value value to store
             * \param column Column in bdd
             **/
            Attr(const T& value,const std::string& column);

            /**
             * \brief Make a Attr
             *
             * \param column Column in bdd
             **/
            Attr(const std::string& column);

            Attr(const Attr&) = delete;

            typedef T type; ///< type of stored object
            T value; ///< value stored
            
            /**
             * \brief assignement operator
             *
             * \param v value to copy
             *
             * \return value
             **/
            template<typename U> T& operator=(const U& v){value=v;modify=true;return value;};

            /**
             * \brief assignement operator
             *
             * \param v value to copy
             *
             * \return *this
             **/
            Attr<T>& operator=(const Attr<T>& v) {value=v.value;modify=true;return*this;};
            
            /**
             * \brief addition operator
             *
             * \param v value to add
             *
             * \return value+v
             **/
            template<typename U> auto operator+(const U& v) -> decltype(value+v) const {return value+v;};

            /**
             * \brief sub operator
             *
             * \param v value to sub
             *
             * \return value-v
             **/
            template<typename U> auto operator-(const U& v) -> decltype(value-v) const {return value-v;};

            /**
             * \brief  multiply operator
             *
             * \param v value to multiply by
             *
             * \return value*v
             **/
            template<typename U> auto operator*(const U& v) -> decltype(value*v) const {return value*v;};

            /**
             * \brief div operator
             BEGIN IONS
TITLE=Locus:1.1.1.1070.2 File:"2014_09_I.Caldelari_S1flag.wiff" (id=8725724319402990)
PEPMASS=449.862396 21480.9
CHARGE=3+
RTINSECONDS=395.0
102.055000 53.3  1+
107.049400 56.0  1+
110.072000 540.0  1+
116.016300 45.0  1+
119.073300 45.0  1+
129.103200 49.0  1+
130.087100 35.3  1+
133.042300 199.0  1+
136.075600 229.0  1+
138.066200 27.3  1+
147.112800 53.0  1+
155.088000 22.0  1+
156.077500 67.0  1+
195.087900 35.4  1+
199.066300 32.3  1+
202.083600 42.0  1+
205.101300 26.0  1+
207.087200 61.0  1+
211.118800 36.3  1+
217.957700 22.0  1+
221.106600 22.0  1+
222.088500 37.5  1+
223.108100 52.0  1+
224.116300 29.0  1+
231.972700 73.0  1+
234.098200 63.8  1+
235.082700 149.1  1+
239.115300 175.0  1+
248.114000 32.0  1+
248.150500 44.0  1+
249.120500 30.3  1+
252.110500 554.0  1+
253.092700 28.6  1+
257.125400 37.0  1+
262.086500 68.1  1+
265.122800 23.0  1+
266.161800 210.0  1+
268.910400 21.0  1+
270.116200 28.0  1+
274.126500 34.0  1+
278.956200 36.3  1+
279.126700 51.0  1+
284.172400 274.0  1+
286.097600 21.3  1+
286.915500 27.3  1+
288.132700 32.5  1+
290.080200 80.0  1+
291.120900 288.0  1+
293.127400 94.9  1+
301.639100 54.0  1+
302.130300 71.0  1+
303.121700 136.0  1+
310.152600 83.3  1+
321.132000 175.0  1+
321.984600 85.0  1+
322.983000 951.0  1+
328.162600 30.1  1+
332.158800 25.0  1+
339.143500 398.0  1+
347.139600 41.1  1+
359.158000 36.5  1+
361.120400 65.0  1+
365.149200 46.3  1+
367.210800 50.0  1+
373.167900 110.0  1+
375.177900 46.0  1+
377.177300 36.0  1+
385.221900 225.0  1+
391.127400 30.6  1+
393.190200 84.0  1+
395.182800 28.8  1+
401.163400 34.3  1+
403.181100 51.0  1+
411.195700 44.0  1+
413.817600 54.0  1+
414.686900 28.0  1+
421.184200 91.1  1+
423.694900 51.0  1+
431.164700 26.0  1+
431.830700 49.0  1+
435.188000 29.3  1+
437.856600 28.0  1+
438.249100 110.0  1+
439.194300 136.3  1+
443.864800 140.0  1+
448.186600 26.0  1+
448.435300 115.0  1+
449.527200 69.5  1+
449.689800 25.0  1+
449.865700 6561.0  1+
450.197900 211.3  1+
456.191100 34.0  1+
456.259200 543.3  1+
456.259700 48.0  2+
462.164900 33.0  1+
466.188400 50.5  1+
472.194800 26.4  1+
474.211500 142.0  2+
474.213300 139.0  1+
479.200300 29.3  1+
484.197500 263.0  1+
502.205500 536.0  1+
503.212800 15.0  1+
505.229300 20.8  1+
519.212800 17.3  1+
531.254300 24.0  1+
536.195900 28.0  1+
540.232000 21.3  1+
541.239900 20.9  1+
542.211700 18.7  1+
548.744300 36.0  1+
549.278400 61.0  1+
550.206500 17.1  1+
553.224900 25.0  1+
554.202000 24.1  1+
557.244200 22.0  1+
558.238700 19.0  1+
559.232200 55.0  1+
567.289100 232.0  1+
568.213700 46.0  1+
571.229300 42.0  1+
575.260100 56.3  1+
581.215700 56.0  1+
585.239300 394.0  1+
585.301200 560.0  1+
586.232300 40.0  1+
592.230700 22.3  1+
599.223600 78.0  1+
601.240300 38.0  1+
602.262600 38.0  1+
603.254800 318.0  1+
605.762500 82.0  1+
610.248700 58.1  1+
617.234700 80.0  1+
617.273000 25.7  2+
620.277900 63.0  1+
628.243800 16.0  1+
637.276800 29.0  1+
654.261300 42.0  1+
654.263500 96.0  2+
672.276900 116.0  1+
682.272300 25.3  1+
700.277600 17.0  1+
709.303500 59.0  1+
717.292100 10.0  1+
718.287600 13.0  1+
719.258200 22.0  1+
726.292100 11.0  1+
727.324600 148.0  1+
728.307100 41.9  1+
735.305000 18.0  1+
737.316200 7.0  1+
744.316600 8.0  1+
745.333100 532.0  1+
746.278600 25.7  1+
755.320600 12.3  1+
763.287000 126.0  1+
793.329500 6.0  1+
810.358100 7.3  1+
828.377000 43.3  1+
838.332900 6.0  1+
846.381400 182.0  1+
847.365000 6.0  1+
864.334400 15.0  1+
874.313800 19.3  1+
892.330900 75.0  1+
935.415400 4.3  1+
945.384500 9.0  1+
963.360400 22.0  1+
968.371900 6.3  1+
984.362400 6.0  1+
991.439400 6.5  1+
1009.443900 33.0  1+
1010.395300 5.0  1+
1019.406700 5.0  1+
1020.388700 7.0  1+
1028.376800 6.0  1+
1036.403300 4.0  1+
1046.412400 26.0  1+
1064.416300 30.0  1+
1082.417500 6.0  1+
1106.456100 5.0  1+
1165.460800 12.7  2+
1192.510000 23.2  2+
2253.273700 50.0  5+
END IONS
*
             * \param v value to div by
             *
             * \return value/v
             **/
            template<typename U> auto operator/(const U& v) -> decltype(value/v) const {return value/v;};

            /**
             * \brief mod operator
             *
             * \param v value to mod by
             *
             * \return v%value
             **/
            template<typename U> auto operator%(const U& v) -> decltype(value%v) const {return value%v;};

            /**
             * \brief post increment operator
             *
             * \return *this
             **/
            Attr<T>& operator++(){++value;modify=true;return *this;};

            /**
             * \brief pre increment operator
             *
             * \return *this
             **/
            Attr<T>& operator++(int){value++;modify=true;return*this;};

            /**
             * \brief post deincrement operator
             *
             * \return *this
             **/
            Attr<T>& operator--(){--value;modify=true;return*this;};

            /**
             * \brief pre deincrement operator
             *
             * \return *this
             **/
            Attr<T>& operator--(int){value--;modify=true;return*this;};
            
            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value == v
             **/
            template<typename U> auto operator==(const U& v) -> decltype(value==v) const {return value==v;};

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value != v
             **/
            template<typename U> auto operator!=(const U& v) -> decltype(value!=v)  const {return value!=v;};

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value > v
             **/
            template<typename U> auto operator>(const U& v) -> decltype(value>v) const {return value>v;};

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value < v
             **/
            template<typename U> auto operator<(const U& v) -> decltype(value<v) const {return value<v;};

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value >= v
             **/
            template<typename U> auto operator>=(const U& v) -> decltype(value>=v)  const {return value>=v;};
            
            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value <= v
             **/
            template<typename U> auto operator<=(const U& v) -> decltype(value<=v)  const {return value<=v;};

            /**
             * \brief negation operator
             *
             * \return !value
             **/
            bool operator!()const {return !value;};


            /**
             * \brief addition operator
             *
             * \param v value to add
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator+=(const U& v) {value+=v;modify=true;return*this;};

            /**
             * \brief sub operator
             *
             * \param v value to sub
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator-=(const U& v) {value-=v;modify=true;return*this;};

            /**
             * \brief multiply operator
             *
             * \param v value to multiply
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator*=(const U& v) {value*=v;modify=true;return*this;};

            /**
             * \brief div operator
             *
             * \param v value to div
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator/=(const U& v) {value/=v;modify=true;return*this;};
            
            /**
             * \brief mod operator
             *
             * \param v value to mod
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator%=(const U& v) {value%=v;modify=true;return*this;};

            /**
             * \brief cast operator
             *
             * \cast this in value
             **/
            //operator T() {return value;};

            /**
             * \brief cast operator
             *
             * \cast this in value
             **/
            operator T()const {return value;};
            
            /**
             * \brief addition operator
             *
             * \param v value to add
             *
             * \return value+v.value
             **/
            T operator+(const Attr<T>& v) const {return value+v.value;};

            /**
             * \brief sub operator
             *
             * \param v value to sub
             *
             * \return value-v.value
             **/
            T operator-(const Attr<T>& v) const {return value-v.value;};

            /**
             * \brief multiply operator
             *
             * \param v value to multiply
             *
             * \return value*v.value
             **/
            T operator*(const Attr<T>& v) const {return value*v.value;};

            /**
             * \brief div operator
             *
             * \param v value to div
             *
             * \return value/v.value
             **/
            T operator/(const Attr<T>& v) const {return value/v.value;};

            /**
             * \brief mod operator
             *
             * \param v value to mod
             *
             * \return value%v.value
             **/
            T operator%(const Attr<T>& v) const {return value%v.value;};

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value == v.value
             **/
            template<typename U> bool operator==(const Attr<U>& v)const {return value==v.value;};

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value != v.value
             **/
            template<typename U> bool operator!=(const Attr<U>& v)const {return value!=v.value;};

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value > v.value
             **/
            template<typename U> bool operator>(const Attr<U>& v)const {return value>v.value;};

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value < v.value
             **/
            template<typename U> bool operator<(const Attr<U>& v)const {return value<v.value;};

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value >= v.value
             **/
            template<typename U> bool operator>=(const Attr<U>& v)const {return value>=v.value;};

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value <= v.value
             **/
            template<typename U> bool operator<=(const Attr<U>& v)const {return value<=v.value;};

            /**
             * \brief addition operator
             *
             * \param v value to add
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator+=(const Attr<U>& v) {value+=v.value;modify=true;return*this;};

            /**
             * \brief sub operator
             *
             * \param v value to sub
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator-=(const Attr<U>& v) {value-=v.value;modify=true;return*this;};

            /**
             * \brief multiply operator
             *
             * \param v value to multiply
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator*=(const Attr<U>& v) {value*=v.value;modify=true;return*this;};

            /**
             * \brief div operator
             *
             * \param v value to div
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator/=(const Attr<U>& v) {value/=v.value;modify=true;return*this;};

            /**
             * \brief mod operator
             *
             * \param v value to mod
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator%=(const Attr<U>& v) {value%=v.value;modify=true;return*this;};

            /**
             * \brief print the stored value
             *
             * \param output print in this stream
             *
             * \return output
             **/
            virtual std::ostream& print_value(std::ostream& output)const;

        protected:
            /**
             * \brief print the stored value
             *
             * \param output print in this stream
             **/
            virtual void print(std::ostream& output) const;

            /**
             * \brief Set the value in the query (use for dispatch
             *
             * \param query Query to set in
             * \param column culum number to set
             *
             * \return false if fail
             */
            virtual bool set(Query& query,const unsigned int& column);

            /**
             * \brief Extract the value from the query row
             *
             * \param query executed query
             * \param prefix column number to get
             * \param max_depth max depth of construction recurtion
             *
             * \return false if fail
             **/
            virtual bool get(const Query& query,int& prefix,int max_depth);

    };

    // define more common type
    using PositiveIntegerField = Attr<unsigned int>;
    using BigIntegerField = Attr<long long int>;
    using BigDoubleField = Attr<long double>;

    /*
      'CommaSeparatedIntegerField':   
      'DateField':                    
      'DateTimeField':                
      'DecimalField':                 
      'FileField':                    
      'FilePathField':                
      'IPAddressField':               
      'GenericIPAddressField':        
      'NullBooleanField':             
      'OneToOneField':                
      'PositiveSmallIntegerField':    
      'SlugField':                    
      'SmallIntegerField':            
      'TimeField':
        CompressedTextField : blob
      */

};
#include <ORM/fields/private/Attr.tpl>

#endif
