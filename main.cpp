#include <iostream>
#include <vector>
#include <string>
#include <unorder_set>
#include <utility>
#include <functional>
#include <algorithm>

using pos = std::pair<size_t,size_t>;

namespace std {
    template<>
    struct hash<pos> {
	size_t operator()(const pos & p) {
	    return std::hash<size_t>()(p.first)^std::hash<size_t>()(p.second);
	}
    };
}

class solution {
public:
    int maximalSquare(const std::vector<std::string> & matrix) {
	std::vector<std::unordered_set<pos>> squares;
	size_t i,j;
	for (i = 0; i < matrix.size(); i++) {
	    for (j = 0; j < matrix[0].size(); j++) {
		
	    }
	}
    }

private:
    bool exist(const std::vector<std::unordered_set<pos>> & vec, const pos & p) {
	return std::any_of(vec.begin(), vec.end(),
			   [&](const std::unordered_set<pos> & s){
			       return s.find(p) != s.end();
			   });
    }
};
