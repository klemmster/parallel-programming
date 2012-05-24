/* -*  *  *  *  *  *  *  *  *  *  *  *
*   Marcel Karsten -- 343619,
*   Patrick Lorenz -- 341922,
*   Richard Klemm -- 343635
*  *  *  *  *  *  *  *  *  *  *  *  */
#ifndef MATCH_H_Q4UHXBAL
#define MATCH_H_Q4UHXBAL

#include <vector>
#include <cstddef>
#include <ostream>
#include <sstream>
#include <string>

class Match {
public:
     Match(const size_t x, const size_t y, const size_t k):
        m_x(x),
        m_y(y),
        m_k(k){};
     virtual ~Match(){};

     static bool sortFun(const Match& a, const Match& b){
        if(a.m_x < b.m_x){
            return true;
        }else if(a.m_x > b.m_x){
            return false;
        }else if(a.m_y < b.m_y){
            return true;
        }else if(a.m_y > b.m_y){
            return false;
        }else if(a.m_k < b.m_k){
            return true;
        }else if(a.m_k > b.m_k){
            return false;
        }
        return false;

     };
     friend std::ostream& operator<< (std::ostream& out , const Match& m){
        out << m.m_x << " " << m.m_y << " " << m.m_k;
        return out;
     };

     bool operator== (const Match& rhs){
         if( (m_x == rhs.m_x) &&
             (m_y == rhs.m_y) &&
             (m_k == rhs.m_k)){
            return true;
         }
         return false;
     };

     const size_t getK() const{
         return m_k;
     };

     std::string toString() const {

	std::ostringstream out;
	out << m_x << m_y << m_k << "\n";
	return out.str();
     };

private:
	size_t m_x, m_y, m_k;
};
typedef std::vector< Match > Matches;

#endif /* end of include guard: MATCH_H_Q4UHXBAL */

