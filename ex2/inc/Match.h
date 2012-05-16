#ifndef MATCH_H_Q4UHXBAL
#define MATCH_H_Q4UHXBAL

#include <vector>
#include <cstddef>
#include <ostream>

class Match {
public:
     Match(const size_t x, const size_t y, const size_t k):
        m_x(x),
        m_y(y),
        m_k(k){};
     virtual ~Match(){};
     friend std::ostream& operator<< (std::ostream& out , const Match& m){
        out << m.m_x << " " << m.m_y << " " << m.m_k;
        return out;
     };

private:
	size_t m_x, m_y, m_k;
};
typedef std::vector< Match > Matches;

#endif /* end of include guard: MATCH_H_Q4UHXBAL */

