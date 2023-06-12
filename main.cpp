#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <iostream>
#include <memory>

template<typename T>
class cache{
    
public:    
    cache(const T& ss, int s):m_ss(ss), m_s(s){
        m_store.resize(s);
    }

    void put(int k){
        auto itr = m_lookup.find(k);
        if (itr == m_lookup.end()){
            auto ssitr = m_ss.find(k);
            auto v = ssitr->second;
            if (m_lookup.size() == m_s){
                auto p = *m_store.begin();
                std::uninitialized_move(m_store.begin() + 1, m_store.end(), m_store.begin());
                auto k = std::get<0>(p);
                m_lookup.erase(k);
            }
           else{
                std::rotate(m_store.begin(), m_store.begin() + 1, m_store.end());
            }
            m_store.back() = std::make_tuple(k, v);
            m_lookup[k] = std::make_tuple(k, v);
        }else{
            auto v = std::get<1>(itr->second);
            auto itr = std::find(m_store.begin(), m_store.end(), std::make_tuple(k, v));
            std::uninitialized_move(itr + 1, m_store.end(), itr);
            m_store.back() = std::make_tuple(k, v);
        }
    }

    int get(int k){
        auto itr = m_lookup.find(k);
        if (itr == m_lookup.end()){
            auto ssitr = m_ss.find(k);
            auto v = ssitr->second;
            if (m_lookup.size() == m_s){
                auto p = *m_store.begin();
                std::uninitialized_move(m_store.begin() + 1, m_store.end(), m_store.begin());
                auto k = std::get<0>(p);
                m_lookup.erase(k);
            }else{
                std::rotate(m_store.begin(), m_store.begin() + 1, m_store.end());
            }
            m_store.back() = std::make_tuple(k, v);
            m_lookup[k] = std::make_tuple(k, v);

            return v;
        }else{
            auto v = std::get<1>(itr->second);
            auto itr = std::find(m_store.begin(), m_store.end(), std::make_tuple(k, v));
            std::uninitialized_move(itr + 1, m_store.end(), itr);
            m_store.back() = std::make_tuple(k, v);

            return v;
        }
    }

    int m_s;
    const T& m_ss;
    std::unordered_map<int, std::tuple<int, int>> m_lookup;
    std::vector<std::tuple<int, int>> m_store;
};

int main(){

    std::map<int, int> ss{{1, 1}, {2, 2}, {3, 3}};
    cache<std::map<int, int>> c(ss, 2);
    c.put(1);
    c.put(2);
    std::cout << "after inserting 1 and 2       ";
    for (const auto& i : c.m_store){
        std::cout << std::get<1>(i) << " ";
        // print 1 2
    }
    std::cout << "\n";
    std::cout << "after accessing 1             ";
    c.get(1);
    for (const auto& i : c.m_store){
        std::cout << std::get<1>(i) << " ";
        // print 2 1
    }
    std::cout << "\n";
    std::cout << "after inserting 3             ";
    c.put(3);
     for (const auto& i : c.m_store){
        std::cout << std::get<1>(i) << " ";
        // print 1 3
    }
    std::cout << "\n";
    c.get(2);
    std::cout << "after inserting 2             ";
      for (const auto& i : c.m_store){
        std::cout << std::get<1>(i) << " ";
        // print 3 2
    }
}
