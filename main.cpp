#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <utility>
#include <functional>
#include <algorithm>
#include <iterator>

using pos = std::pair<size_t,size_t>;

namespace std {
    template<>
    struct hash<pos> {
	size_t operator()(const pos & p) const {
	    return std::hash<size_t>()(p.first)^std::hash<size_t>()(p.second);
	}
    };

    std::ostream & operator<<(std::ostream & os, const pos & p) {
        os << "(" << p.first << "," << p.second << ")";
        return os;
    }
}

class solution {
public:
    int maximalSquare(const std::vector<std::string> & matrix) {
	std::vector<std::unordered_set<pos>> squares;
	size_t i,j;
	for (i = 0; i < matrix.size(); i++) {
	    for (j = 0; j < matrix[0].size(); j++) {
		if (matrix[i][j] == '1')
                    squares.push_back(growFrom(matrix, std::make_pair(i,j)));
	    }
	}
        auto it = std::max_element(squares.begin(), squares.end(),
                                   [](const std::unordered_set<pos> & s1, const std::unordered_set<pos> & s2){
                                       return s1.size() < s2.size();
                                   });
        std::copy(it->begin(), it->end(), std::ostream_iterator<pos>(std::cout, " "));
        std::cout << std::endl;
        return it->size();
    }

private:    
    std::unordered_set<pos> growFrom(const std::vector<std::string> & matrix, const pos & topleft){
        std::unordered_set<pos> result;
        pos br = topleft;
        while (allOnes(matrix, topleft, br) && br.first < matrix.size()-1 && br.second < matrix[0].size()-1
               && allOnes(matrix, topleft, std::make_pair(br.first+1, br.second+1)))
            br = std::make_pair(br.first+1, br.second+1);
        for (size_t i = topleft.first; i <= br.first; i++)
            for (size_t j = topleft.second; j <= br.second; j++)
                result.insert(std::make_pair(i,j));
        
        return result;
    }

    bool allOnes(const std::vector<std::string> & matrix, const pos & tl, const pos & br) {
        return std::all_of(matrix.begin()+tl.first, matrix.begin()+br.first+1,
                      [&](const std::string & s){
                          return std::all_of(s.begin()+tl.second, s.begin()+br.second+1,
                                        [](char ch){
                                            return ch == '1';
                                        });
                      });
    }
    
    bool exist(const std::vector<std::unordered_set<pos>> & vec, const pos & p) {
	return std::any_of(vec.begin(), vec.end(),
			   [&](const std::unordered_set<pos> & s){
			       return s.find(p) != s.end();
			   });
    }
};

int main() {
    std::vector<std::string> matrix{
        {"10100"},
        {"10111"},
        {"11111"},
        {"10010"}
    };

    solution soln;
    int maxOnes = soln.maximalSquare(matrix);
    std::cout << "The maximal square contains " << maxOnes << " 1's." << std::endl;
}
