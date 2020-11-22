#include "list.hpp"
#include "map.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "vector.hpp"
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#define cns std
#define vector_test(name, prelude, sc)                 \
    do {                                               \
        std::stringstream fts, stds;                   \
        std::vector<int> stda;                         \
        ft::vector<int> fta;                           \
        {                                              \
            std::stringstream& output = stds;          \
            (void)output;                              \
            typedef std::vector<int> vtype;            \
            vtype& a = stda;                           \
            (void)a;                                   \
            typedef std::vector<int> vtype;            \
            prelude;                                   \
        }                                              \
        {                                              \
            std::stringstream& output = fts;           \
            (void)output;                              \
            typedef ft::vector<int> vtype;             \
            vtype& a = fta;                            \
            (void)a;                                   \
            prelude;                                   \
        }                                              \
        if (sc) {                                      \
            evaluate_vector_t2(fta, fts, sc);          \
            evaluate_vector_t2(stda, stds, sc);        \
        } else {                                       \
            evaluate_vector_t1(fta, fts, sc);          \
            evaluate_vector_t1(stda, stds, sc);        \
        }                                              \
        std::string ss = stds.str();                   \
        std::string fs = fts.str();                    \
        if (ss != fs) {                                \
            std::cout << "[KO] " << name << std::endl; \
            std::cout << "std:\n"                      \
                      << ss << "\nft:\n"               \
                      << fs << std::endl;              \
        } else {                                       \
            std::cout << "[OK] " << name << std::endl; \
        }                                              \
    } while (0)

#define list_test(name, prelude)                       \
    do {                                               \
        std::stringstream fts, stds;                   \
        std::list<int> stda;                           \
        ft::list<int> fta;                             \
        {                                              \
            std::stringstream& output = stds;          \
            (void)output;                              \
            typedef std::list<int> vtype;              \
            vtype& a = stda;                           \
            (void)a;                                   \
            prelude;                                   \
        }                                              \
        {                                              \
            std::stringstream& output = fts;           \
            (void)output;                              \
            typedef ft::list<int> vtype;               \
            vtype& a = fta;                            \
            (void)a;                                   \
            prelude;                                   \
        }                                              \
        evaluate_list_t1(fta, fts);                    \
        evaluate_list_t1(stda, stds);                  \
        std::string ss = stds.str();                   \
        std::string fs = fts.str();                    \
        if (ss != fs) {                                \
            std::cout << "[KO] " << name << std::endl; \
            std::cout << "std:\n"                      \
                      << ss << "\nft:\n"               \
                      << fs << std::endl;              \
        } else {                                       \
            std::cout << "[OK] " << name << std::endl; \
        }                                              \
    } while (0)

#define map_test(name, prelude)                        \
    do {                                               \
        std::stringstream fts, stds;                   \
        std::map<int, std::string> stda;               \
        ft::map<int, std::string> fta;                 \
        {                                              \
            std::stringstream& output = stds;          \
            (void)output;                              \
            typedef std::map<int, std::string> vtype;  \
            vtype& a = stda;                           \
            (void)a;                                   \
            prelude;                                   \
        }                                              \
        {                                              \
            std::stringstream& output = fts;           \
            (void)output;                              \
            typedef ft::map<int, std::string> vtype;   \
            vtype& a = fta;                            \
            (void)a;                                   \
            prelude;                                   \
        }                                              \
        evaluate_map_t1(fta, fts);                     \
        evaluate_map_t1(stda, stds);                   \
        std::string ss = stds.str();                   \
        std::string fs = fts.str();                    \
        if (ss != fs) {                                \
            std::cout << "[KO] " << name << std::endl; \
            std::cout << "std:\n"                      \
                      << ss << "\nft:\n"               \
                      << fs << std::endl;              \
        } else {                                       \
            std::cout << "[OK] " << name << std::endl; \
        }                                              \
    } while (0)

template <typename Vt>
void evaluate_vector(Vt& a, std::ostream& stream, bool sc)
{
    Vt const& ac = a;
    if (!a.empty()) {
        stream << a.front() << ' ' << a.back() << ' ';
    }
    stream << a.size() << ' ';
    if (sc) {
        stream
            << a.capacity() << ' ';
    }
    stream << a.empty()
           << '\n';
    stream << "n ";
    for (size_t idx = 0; idx < a.size(); idx += 1) {
        stream << a[idx] << ' ';
    }
    stream << "\ni ";
    for (typename Vt::iterator it = a.begin(); it != a.end(); it += 1) {
        stream << *it << ' ';
    }
    stream << "\nc ";
    for (typename Vt::const_iterator it = ac.begin(); it != ac.end(); it += 1) {
        stream << *it << ' ';
    }
    stream << "\nr ";
    for (typename Vt::reverse_iterator it = a.rbegin(); it != a.rend(); it += 1) {
        stream << *it << ' ';
    }
    stream << "\nc ";
    for (typename Vt::const_reverse_iterator it = ac.rbegin(); it != ac.rend(); it += 1) {
        stream << *it << ' ';
    }
    stream << '\n';
}

template <typename Vt>
void evaluate_vector_t1(Vt& a, std::ostream& stream, bool sc)
{
    Vt b(a);
    Vt c;
    c.push_back(1);
    c = a;
    typename Vt::iterator ___it = b.begin();
    typename Vt::const_iterator ___cit = ___it;
    (void)___cit;
    evaluate_vector(a, stream, sc);
    evaluate_vector(b, stream, sc);
    evaluate_vector(c, stream, sc);
}

template <typename Vt>
void evaluate_vector_t2(Vt& a, std::ostream& stream, bool sc)
{
    evaluate_vector(a, stream, sc);
}

template <typename Vt>
void evaluate_list(Vt& a, std::ostream& stream)
{
    Vt const& ac = a;
    if (!a.empty()) {
        stream << a.front() << ' ' << a.back() << ' ';
    }
    stream << a.size() << ' ';
    stream << a.empty()
           << '\n';
    stream << "\ni ";
    for (typename Vt::iterator it = a.begin(); it != a.end(); it++) {
        stream << *it << ' ';
    }
    stream << "\nc ";
    for (typename Vt::const_iterator it = ac.begin(); it != ac.end(); it++) {
        stream << *it << ' ';
    }
    stream << "\nr ";
    for (typename Vt::reverse_iterator it = a.rbegin(); it != a.rend(); it++) {
        stream << *it << ' ';
    }
    stream << "\nc ";
    for (typename Vt::const_reverse_iterator it = ac.rbegin(); it != ac.rend(); it++) {
        stream << *it << ' ';
    }
    stream << '\n';
}

template <typename Vt>
void evaluate_list_t1(Vt& a, std::ostream& stream)
{
    Vt b(a);
    Vt c;
    c.push_back(1);
    c = a;
    typename Vt::iterator ___it = b.begin();
    typename Vt::reverse_iterator ___rit = b.rbegin();
    typename Vt::const_iterator ___cit = ___it;
    typename Vt::const_reverse_iterator ___crit = ___rit;
    (void)___cit;
    (void)___crit;
    evaluate_list(a, stream);
    evaluate_list(b, stream);
    evaluate_list(c, stream);
}

template <typename Vt>
void evaluate_map(Vt& a, std::ostream& stream)
{
    Vt const& ac = a;
    stream << a.size() << ' ';
    stream << a.empty()
           << '\n';
    stream << "\ni ";
    for (typename Vt::iterator it = a.begin(); it != a.end(); it++) {
        stream << '(' << it->first << ", " << it->second << ") ";
    }
    stream << "\nc ";
    for (typename Vt::const_iterator it = ac.begin(); it != ac.end(); it++) {
        stream << '(' << it->first << ", " << it->second << ") ";
    }
    stream << "\nr ";
    for (typename Vt::reverse_iterator it = a.rbegin(); it != a.rend(); it++) {
        stream << '(' << it->first << ", " << it->second << ") ";
    }
    stream << "\nc ";
    for (typename Vt::const_reverse_iterator it = ac.rbegin(); it != ac.rend(); it++) {
        stream << '(' << it->first << ", " << it->second << ") ";
    }
    stream << '\n';
}

template <typename Vt>
void evaluate_map_t1(Vt& a, std::ostream& stream)
{
    Vt b(a);
    Vt c;
    c.insert(typename Vt::value_type(1, "heck"));
    c = a;
    typename Vt::iterator ___it = b.begin();
    typename Vt::reverse_iterator ___rit = b.rbegin();
    typename Vt::const_iterator ___cit = ___it;
    typename Vt::const_reverse_iterator ___crit = ___rit;
    (void)___cit;
    (void)___crit;
    evaluate_map(a, stream);
    evaluate_map(b, stream);
    evaluate_map(c, stream);
}

int vector_tests()
{
    vector_test(
        "empty",
        {}, false);
    vector_test(
        "single",
        {
            a.push_back(1);
        },
        false);
    vector_test(
        "double",
        {
            a.push_back(1);
            a.push_back(2);
        },
        false);
    vector_test(
        "triple",
        {
            a.push_back(1);
            a.push_back(2);
            a.push_back(3);
        },
        false);
    vector_test(
        "one_popped",
        {
            a.push_back(1);
            a.push_back(2);
            a.push_back(3);
            a.pop_back();
            a.push_back(4);
        },
        false);
    vector_test(
        "last_popped",
        {
            a.push_back(1);
            a.push_back(2);
            a.push_back(3);
            a.push_back(4);
            a.pop_back();
        },
        false);
    vector_test(
        "auto_10",
        {
            for (size_t idx = 0; idx < 10; idx += 1) {
                a.push_back(idx);
            }
        },
        false);
    vector_test(
        "clear",
        {
            a.push_back(1);
            a.push_back(2);
            a.push_back(3);
            a.push_back(4);
            a.push_back(5);
            a.clear();
        },
        false);
    vector_test(
        "resize16", {
            a.resize(16);
        },
        true);
    vector_test(
        "resize4", {
            a.resize(4);
        },
        true);
    vector_test(
        "reserve16", {
            a.reserve(16);
        },
        true);
    vector_test(
        "reserve4", {
            a.reserve(4);
        },
        true);
    vector_test(
        "doublereserve", {
            a.reserve(16);
            a.reserve(16);
        },
        true);
    vector_test(
        "index",
        {
            a.push_back(1);
            if (a[0] != 1) {
                throw std::runtime_error("a[0] != 1");
            }
            a[0] = 2;
            if (a[0] != 2) {
                throw std::runtime_error("a[0] != 2");
            }
        },
        false);
    vector_test(
        "indexmb",
        {
            a.push_back(1);
            a.push_back(2);
            a.push_back(3);
            a.push_back(4);
            if (a[0] != 1) {
                throw std::runtime_error("a[0] != 1");
            }
            a[0] = 123;
            if (a[0] != 123) {
                throw std::runtime_error("a[0] != 2");
            }
            if (a[1] != 2) {
                throw std::runtime_error("a[1] != 2");
            }
            a[1] = 123;
            if (a[1] != 123) {
                throw std::runtime_error("a[1] != 123");
            }
            if (a[2] != 3) {
                throw std::runtime_error("a[2] != 3");
            }
            a[2] = 123;
            if (a[2] != 123) {
                throw std::runtime_error("a[2] != 123");
            }
            if (a[3] != 4) {
                throw std::runtime_error("a[3] != 3");
            }
            a[3] = 123;
            if (a[3] != 123) {
                throw std::runtime_error("a[3] != 123");
            }
        },
        false);
    vector_test(
        "at_valid", {
            a.push_back(42);
            try {
                if (a.at(0) != 42) {
                    throw std::runtime_error("a.at(0) != 42");
                }
            } catch (...) {
                throw;
            }
        },
        false);
    vector_test(
        "at_invalid", {
            a.push_back(42);
            try {
                (void)a.at(1);
                throw std::runtime_error("a.at(1) was successful");
            } catch (std::out_of_range const&) {
            } catch (...) {
                throw;
            }
        },
        false);
    vector_test(
        "assign range into empty vector",
        {
            ft::vector<int> ftb;
            ftb.push_back(1);
            ftb.push_back(2);
            ftb.push_back(3);
            ftb.push_back(4);
            a.assign(ftb.begin(), ftb.end());
        },
        false);
    vector_test(
        "assign range into filled vector",
        {
            ft::vector<int> ftb;
            ftb.push_back(1);
            ftb.push_back(2);
            ftb.push_back(3);
            ftb.push_back(4);
            a.push_back(5);
            a.push_back(6);
            a.push_back(7);
            a.push_back(8);
            a.assign(ftb.begin(), ftb.end());
        },
        false);
    vector_test(
        "assign fill into empty vector",
        {
            a.assign(10, 123);
        },
        false);
    vector_test(
        "insert-at begin into empty vector",
        {
            a.insert(a.begin(), 4242);
        },
        false);
    vector_test(
        "insert-at end into empty vector",
        {
            a.insert(a.end(), 4242);
        },
        false);
    vector_test(
        "insert-at begin into filled(1) vector",
        {
            a.push_back(1);
            a.insert(a.begin(), 4242);
        },
        false);
    vector_test(
        "insert-at end into filled(1) vector",
        {
            a.push_back(1);
            a.insert(a.end(), 4242);
        },
        false);
    vector_test(
        "insert-at begin into filled(3) vector",
        {
            a.push_back(123);
            a.push_back(456);
            a.push_back(789);
            a.insert(a.begin(), 4242);
        },
        false);
    vector_test(
        "insert-at end into filled(3) vector",
        {
            a.push_back(123);
            a.push_back(456);
            a.push_back(789);
            a.insert(a.end(), 4242);
        },
        false);
    vector_test(
        "insert-at 1 into filled(3) vector",
        {
            a.push_back(123);
            a.push_back(456);
            a.push_back(789);
            a.insert(a.begin() + 1, 4242);
        },
        false);
    vector_test(
        "insert-at 2 into filled(3) vector",
        {
            a.push_back(123);
            a.push_back(456);
            a.push_back(789);
            a.insert(a.begin() + 2, 4242);
        },
        false);
    vector_test(
        "erase single begin, filled(1) vector",
        {
            a.push_back(123);
            a.erase(a.begin());
        },
        false);
    vector_test(
        "erase single begin, filled(2) vector",
        {
            a.push_back(123);
            a.push_back(456);
            a.erase(a.begin());
        },
        false);
    vector_test(
        "erase single begin, filled(3) vector",
        {
            a.push_back(123);
            a.push_back(456);
            a.push_back(789);
            a.erase(a.begin());
        },
        false);
    vector_test(
        "erase single begin, filled(4) vector",
        {
            a.push_back(123);
            a.push_back(456);
            a.push_back(789);
            a.push_back(987);
            a.erase(a.begin());
        },
        false);
    vector_test(
        "erase single at(1), filled(4) vector",
        {
            a.push_back(123);
            a.push_back(456);
            a.push_back(789);
            a.push_back(987);
            a.erase(a.begin() + 1);
        },
        false);
    vector_test(
        "erase single at(2), filled(4) vector",
        {
            a.push_back(123);
            a.push_back(456);
            a.push_back(789);
            a.push_back(987);
            a.erase(a.begin() + 2);
        },
        false);
    vector_test(
        "erase single at(3), filled(4) vector",
        {
            a.push_back(123);
            a.push_back(456);
            a.push_back(789);
            a.push_back(987);
            a.erase(a.begin() + 3);
        },
        false);
    vector_test(
        "erase range entire, filled(1) vector",
        {
            a.push_back(12);
            a.erase(a.begin(), a.end());
        },
        false);
    vector_test(
        "erase range entire, filled(2) vector",
        {
            a.push_back(12);
            a.push_back(23);
            a.erase(a.begin(), a.end());
        },
        false);
    vector_test(
        "erase range entire, filled(3) vector",
        {
            a.push_back(12);
            a.push_back(23);
            a.push_back(34);
            a.erase(a.begin(), a.end());
        },
        false);
    vector_test(
        "erase range entire, filled(4) vector",
        {
            a.push_back(12);
            a.push_back(23);
            a.push_back(34);
            a.push_back(45);
            a.erase(a.begin(), a.end());
        },
        false);
    vector_test(
        "erase range +1,+2, filled(4) vector",
        {
            a.push_back(12);
            a.push_back(23);
            a.push_back(34);
            a.push_back(45);
            a.erase(a.begin() + 1, a.begin() + 2);
        },
        false);
    vector_test(
        "erase range begin,+2, filled(4) vector",
        {
            a.push_back(12);
            a.push_back(23);
            a.push_back(34);
            a.push_back(45);
            a.erase(a.begin(), a.begin() + 2);
        },
        false);
    vector_test(
        "erase range +1,end, filled(4) vector",
        {
            a.push_back(12);
            a.push_back(23);
            a.push_back(34);
            a.push_back(45);
            a.erase(a.begin() + 1, a.end());
        },
        false);
    vector_test(
        "swap filled",
        {
            vtype somevec;
            somevec.push_back(1);
            somevec.push_back(2);
            somevec.push_back(3);
            a.swap(somevec);
        },
        false);
    vector_test(
        "swap empty",
        {
            vtype somevec;
            a.push_back(1);
            a.push_back(2);
            a.push_back(3);
            a.swap(somevec);
        },
        false);
    vector_test(
        "compare eqv eq",
        {
            vtype somevec;
            somevec.push_back(123);
            somevec.push_back(456);
            a.push_back(123);
            a.push_back(456);
            output << (a == somevec);
        },
        false);
    vector_test(
        "compare eqv neq",
        {
            vtype somevec;
            somevec.push_back(123);
            somevec.push_back(456);
            a.push_back(123);
            a.push_back(456);
            output << (a != somevec);
        },
        false);
    vector_test(
        "compare eqv lt",
        {
            vtype somevec;
            somevec.push_back(123);
            somevec.push_back(456);
            a.push_back(123);
            a.push_back(456);
            output << (a < somevec);
        },
        false);
    vector_test(
        "compare eqv gt",
        {
            vtype somevec;
            somevec.push_back(123);
            somevec.push_back(456);
            a.push_back(123);
            a.push_back(456);
            output << (a > somevec);
        },
        false);
    vector_test(
        "compare eqv lte",
        {
            vtype somevec;
            somevec.push_back(123);
            somevec.push_back(456);
            a.push_back(123);
            a.push_back(456);
            output << (a <= somevec);
        },
        false);
    vector_test(
        "compare eqv gte",
        {
            vtype somevec;
            somevec.push_back(123);
            somevec.push_back(456);
            a.push_back(123);
            a.push_back(456);
            output << (a >= somevec);
        },
        false);
    vector_test(
        "compare neqv eq",
        {
            vtype somevec;
            somevec.push_back(123);
            somevec.push_back(456);
            a.push_back(123);
            output << (a == somevec);
        },
        false);
    vector_test(
        "compare neqv neq",
        {
            vtype somevec;
            somevec.push_back(123);
            somevec.push_back(456);
            a.push_back(123);
            output << (a != somevec);
        },
        false);
    vector_test(
        "compare neqv lt",
        {
            vtype somevec;
            somevec.push_back(123);
            somevec.push_back(456);
            a.push_back(123);
            output << (a < somevec);
        },
        false);
    vector_test(
        "compare neqv gt",
        {
            vtype somevec;
            somevec.push_back(123);
            somevec.push_back(456);
            a.push_back(123);
            output << (a > somevec);
        },
        false);
    vector_test(
        "compare neqv lte",
        {
            vtype somevec;
            somevec.push_back(123);
            somevec.push_back(456);
            a.push_back(123);
            output << (a <= somevec);
        },
        false);
    vector_test(
        "compare neqv gte",
        {
            vtype somevec;
            somevec.push_back(123);
            somevec.push_back(456);
            a.push_back(123);
            output << (a >= somevec);
        },
        false);
    return 0;
}

bool gt_four(int x) { return x > 4; }
bool eq_zero(int x) { return x == 0; }
bool add_ten(int x, int y) { return (x + 10) == y; }
bool eq_bin(int x, int y) { return x == y; }
bool lt_bin(int x, int y) { return x < y; }

void list_tests()
{
    list_test("empty", {});
    list_test("some back",
        {
            a.push_back(1);
            a.push_back(2);
            a.push_back(3);
        });
    list_test("some front",
        {
            a.push_front(1);
            a.push_front(2);
            a.push_front(3);
        });
    list_test("reclear front",
        {
            a.push_front(1);
            a.push_front(2);
            a.push_front(3);
            a.clear();
            a.push_back(2);
            a.push_front(1);
            a.push_back(3);
        });

    list_test("double clear", {
        a.clear();
        a.clear();
    });
    list_test("single insert begin", { a.insert(a.begin(), 1); });
    list_test("single insert end", { a.insert(a.end(), 1); });
    list_test("single insert mid", { a.push_back(3); a.push_back(2); a.insert(--a.end(), 1); });
    list_test("insert range begin",
        {
            vtype x;
            x.push_back(1);
            x.push_back(2);
            x.push_back(3);
            x.push_back(4);
            a.insert(a.begin(), x.begin(), x.end());
        });
    list_test("insert range end",
        {
            vtype x;
            x.push_back(1);
            x.push_back(2);
            x.push_back(3);
            x.push_back(4);
            a.insert(a.end(), x.begin(), x.end());
        });
    list_test("filled insert range begin",
        {
            vtype x;
            x.push_back(1);
            x.push_back(2);
            x.push_back(3);
            x.push_back(4);
            a.push_back(100);
            a.push_front(200);
            a.insert(a.begin(), x.begin(), x.end());
        });
    list_test("filled insert range end",
        {
            vtype x;
            x.push_back(1);
            x.push_back(2);
            x.push_back(3);
            x.push_back(4);
            a.push_back(100);
            a.push_back(200);
            a.insert(a.end(), x.begin(), x.end());
        });
    list_test("filled insert range -1",
        {
            vtype x;
            x.push_back(1);
            x.push_back(2);
            x.push_back(3);
            x.push_back(4);
            a.push_back(100);
            a.push_back(200);
            vtype::iterator it = a.end();
            --it;
            a.insert(it, x.begin(), x.end());
        });
    list_test("insert fill begin",
        {
            a.insert(a.begin(), 42, 10);
        });
    list_test("insert fill end",
        {
            a.insert(a.end(), 42, 10);
        });
    list_test("insert fill -1", {
        a.push_back(1);
        a.push_back(2);
        a.insert(--a.end(), 42, 10);
    });
    list_test("assign range",
        {
            vtype x;
            x.push_back(1);
            x.push_back(2);
            x.push_back(3);
            x.push_back(4);
            a.push_back(100);
            a.push_back(200);
            a.assign(x.begin(), x.end());
        });
    list_test("assign range0",
        {
            vtype x;
            x.push_back(1);
            x.push_back(2);
            x.push_back(3);
            x.push_back(4);
            a.push_back(100);
            a.push_back(200);
            a.assign(x.begin(), x.end());
        });
    list_test("assign fill",
        {
            vtype x;
            x.push_back(1);
            x.push_back(2);
            x.push_back(3);
            x.push_back(4);
            a.push_back(100);
            a.push_back(200);
            a.assign(10, 42);
        });
    list_test("assign fill0",
        {
            vtype x;
            x.push_back(1);
            x.push_back(2);
            x.push_back(3);
            x.push_back(4);
            a.push_back(100);
            a.push_back(200);
            a.assign(0, 42);
        });
    list_test("swap empty1",
        {
            vtype x;
            x.push_back(1);
            x.push_back(2);
            x.push_back(3);
            x.push_back(4);
            a.swap(x);
        });
    list_test("swap empty2",
        {
            vtype x;
            a.push_back(100);
            a.push_back(200);
            a.swap(x);
        });
    list_test("swap emptyall",
        {
            vtype x;
            a.swap(x);
        });
    list_test("swap filled",
        {
            vtype x;
            x.push_back(1);
            x.push_back(2);
            x.push_back(3);
            x.push_back(4);
            a.push_back(100);
            a.push_back(200);
            a.swap(x);
        });
    list_test("resize 0->0", {
        a.resize(0);
    });
    list_test("resize 0->1", {
        a.resize(1);
    });
    list_test("resize 0->10", {
        a.resize(10);
    });
    list_test("resize 1->0", {
        a.push_back(1);
        a.resize(0);
    });
    list_test("resize 1->1", {
        a.push_back(1);
        a.resize(1);
    });
    list_test("resize 1->10", {
        a.push_back(1);
        a.resize(10);
    });
    list_test("splice entire",
        {
            vtype x;
            x.push_back(1);
            x.push_back(2);
            x.push_back(3);
            x.push_back(4);
            a.push_back(100);
            a.push_back(200);
            a.splice(a.begin(), x);
        });
    list_test("splice single",
        {
            vtype x;
            x.push_back(1);
            x.push_back(2);
            x.push_back(3);
            x.push_back(4);
            a.push_back(100);
            a.push_back(200);
            a.splice(a.begin(), x, x.begin());
        });
    list_test("splice range",
        {
            vtype x;
            x.push_back(1);
            x.push_back(2);
            x.push_back(3);
            x.push_back(4);
            a.push_back(100);
            a.push_back(200);
            a.splice(a.begin(), x, ++x.begin(), --x.end());
        });
    list_test("remove 4",
        {
            a.push_back(1);
            a.push_back(2);
            a.push_back(3);
            a.push_back(1);
            a.push_back(4);
            a.push_back(5);
            a.push_back(4);
            a.push_back(5);
            a.push_back(1);
            a.remove(4);
        });
    list_test("remove 4, 1",
        {
            a.push_back(1);
            a.push_back(2);
            a.push_back(3);
            a.push_back(1);
            a.push_back(4);
            a.push_back(5);
            a.push_back(4);
            a.push_back(5);
            a.push_back(1);
            a.remove(4);
            a.remove(1);
        });
    list_test("remove Bad",
        {
            a.push_back(1);
            a.push_back(2);
            a.push_back(3);
            a.push_back(1);
            a.push_back(4);
            a.push_back(5);
            a.push_back(4);
            a.push_back(5);
            a.push_back(1);
            a.remove(6);
        });
    list_test("remove_if eqz",
        {
            a.push_back(0);
            a.push_back(2);
            a.push_back(3);
            a.push_back(0);
            a.push_back(4);
            a.push_back(5);
            a.push_back(4);
            a.push_back(5);
            a.push_back(0);
            a.remove_if(eq_zero);
        });
    list_test("remove_if bad",
        {
            a.push_back(1);
            a.push_back(2);
            a.push_back(3);
            a.push_back(1);
            a.push_back(4);
            a.push_back(5);
            a.push_back(4);
            a.push_back(5);
            a.push_back(1);
            a.remove_if(eq_zero);
        });
    list_test("remove_if gtf",
        {
            a.push_back(1);
            a.push_back(2);
            a.push_back(3);
            a.push_back(6);
            a.push_back(4);
            a.push_back(5);
            a.push_back(4);
            a.push_back(5);
            a.push_back(1);
            a.remove_if(gt_four);
        });
    list_test("unique",
        {
            a.push_back(1);
            a.push_back(2);
            a.push_back(3);
            a.push_back(3);
            a.push_back(4);
            a.push_back(3);
            a.push_back(4);
            a.push_back(5);
            a.push_back(6);
            a.unique();
        });
    list_test("unique empty", { a.unique(); });
    list_test("unique nochange", {
        a.push_back(1);
        a.push_back(2);
        a.push_back(3);
        a.unique();
    });
    list_test("unique if p10",
        {
            a.push_back(10);
            a.push_back(20);
            a.push_back(30);
            a.push_back(40);
            a.push_back(50);
            a.push_back(50);
            a.push_back(50);
            a.push_back(60);
            a.unique(add_ten);
        });
    list_test("unique if eq",
        {
            a.push_back(10);
            a.push_back(20);
            a.push_back(30);
            a.push_back(40);
            a.push_back(50);
            a.push_back(50);
            a.push_back(50);
            a.push_back(60);
            a.unique(eq_bin);
        });
    list_test("merge test",
        {
            vtype h;
            h.push_back(1);
            h.push_back(3);
            h.push_back(5);
            h.push_back(7);
            a.push_back(2);
            a.push_back(4);
            a.push_back(6);
            a.push_back(8);
            a.merge(h);
        });
    list_test("merge comp test",
        {
            vtype h;
            h.push_back(1);
            h.push_back(3);
            h.push_back(5);
            h.push_back(7);
            a.push_back(2);
            a.push_back(4);
            a.push_back(6);
            a.push_back(8);
            a.merge(h, lt_bin);
        });
    list_test("sort test",
        {
            a.push_back(2);
            a.push_back(10);
            a.push_back(17);
            a.push_back(6);
            a.push_back(13);
            a.push_back(11);
            a.push_back(3);
            a.push_back(1);
            a.push_back(7);
            a.push_back(9);
            a.push_back(5);
            a.push_back(16);
            a.push_back(14);
            a.push_back(8);
            a.push_back(12);
            a.push_back(4);
            a.push_back(15);
            a.sort();
        });
    list_test("sort test emptylist",
        {
            a.sort();
        });
    list_test("sort test listsize1",
        {
            a.push_back(1);
            a.sort();
        });
    list_test("sort test listsize2 unsorted",
        {
            a.push_back(2);
            a.push_back(1);
            a.sort();
        });
    list_test("sort test listsize2 sorted",
        {
            a.push_back(1);
            a.push_back(2);
            a.sort();
        });
    list_test("sort comp test",
        {
            a.push_back(2);
            a.push_back(10);
            a.push_back(17);
            a.push_back(6);
            a.push_back(13);
            a.push_back(11);
            a.push_back(3);
            a.push_back(1);
            a.push_back(7);
            a.push_back(9);
            a.push_back(5);
            a.push_back(16);
            a.push_back(14);
            a.push_back(8);
            a.push_back(12);
            a.push_back(4);
            a.push_back(15);
            a.sort(lt_bin);
        });
    list_test("sort comptest emptylist",
        {
            a.sort(lt_bin);
        });
    list_test("sort comptest listsize1",
        {
            a.push_back(1);
            a.sort(lt_bin);
        });
    list_test("sort comptest listsize2 unsorted",
        {
            a.push_back(2);
            a.push_back(1);
            a.sort(lt_bin);
        });
    list_test("sort comp test listsize2 sorted",
        {
            a.push_back(1);
            a.push_back(2);
            a.sort(lt_bin);
        });
    list_test("reverse big",
        {
            a.push_back(2);
            a.push_back(10);
            a.push_back(17);
            a.push_back(6);
            a.push_back(13);
            a.push_back(11);
            a.push_back(3);
            a.push_back(1);
            a.push_back(7);
            a.push_back(9);
            a.push_back(5);
            a.push_back(16);
            a.push_back(14);
            a.push_back(8);
            a.push_back(12);
            a.push_back(4);
            a.push_back(15);
            a.reverse();
        });
    list_test("reverse 3",
        {
            a.push_back(2);
            a.push_back(10);
            a.push_back(17);
            a.reverse();
        });
    list_test("reverse 2",
        {
            a.push_back(2);
            a.push_back(10);
            a.reverse();
        });
    list_test("reverse 1",
        {
            a.push_back(2);
            a.reverse();
        });
    list_test("reverse 0",
        {
            a.reverse();
        });
}

void map_tests()
{
    map_test(
        "empty",
        {});
    map_test(
        "insert se",
        {
            a.insert(vtype::value_type(0, "zero"));
        });
    map_test(
        "insert se three",
        {
            a.insert(vtype::value_type(3, "three"));
            a.insert(vtype::value_type(2, "two"));
            a.insert(vtype::value_type(1, "one"));
        });
    map_test(
        "insert se five",
        {
            a.insert(vtype::value_type(3, "three"));
            a.insert(vtype::value_type(2, "two"));
            a.insert(vtype::value_type(5, "five"));
            a.insert(vtype::value_type(1, "one"));
            a.insert(vtype::value_type(4, "four"));
        });
    map_test(
        "insert se five + repeat",
        {
            output << a.insert(vtype::value_type(3, "three cold")).second
                   << a.insert(vtype::value_type(2, "two cold")).second
                   << a.insert(vtype::value_type(5, "five cold")).second
                   << a.insert(vtype::value_type(1, "one cold")).second
                   << a.insert(vtype::value_type(4, "four cold")).second
                   << a.insert(vtype::value_type(3, "three slate")).second
                   << a.insert(vtype::value_type(2, "two slate")).second
                   << a.insert(vtype::value_type(5, "five slate")).second
                   << a.insert(vtype::value_type(1, "one slate")).second
                   << a.insert(vtype::value_type(4, "four slate")).second;
        });
    map_test(
        "insert wh begin",
        {
            a.insert(a.begin(), vtype::value_type(0, "zero"));
        });
    map_test(
        "insert wh begin three",
        {
            a.insert(a.begin(), vtype::value_type(3, "three"));
            a.insert(a.begin(), vtype::value_type(2, "two"));
            a.insert(a.begin(), vtype::value_type(1, "one"));
        });
    map_test(
        "insert wh begin five",
        {
            a.insert(a.begin(), vtype::value_type(3, "three"));
            a.insert(a.begin(), vtype::value_type(2, "two"));
            a.insert(a.begin(), vtype::value_type(5, "five"));
            a.insert(a.begin(), vtype::value_type(1, "one"));
            a.insert(a.begin(), vtype::value_type(4, "four"));
        });
    map_test(
        "insert wh begin five replace",
        {
            a.insert(a.begin(), vtype::value_type(3, "three cold"));
            a.insert(a.begin(), vtype::value_type(2, "two cold"));
            a.insert(a.begin(), vtype::value_type(5, "five cold"));
            a.insert(a.begin(), vtype::value_type(1, "one cold"));
            a.insert(a.begin(), vtype::value_type(4, "four cold"));
            a.insert(a.begin(), vtype::value_type(3, "three slate"));
            a.insert(a.begin(), vtype::value_type(2, "two slate"));
            a.insert(a.begin(), vtype::value_type(5, "five slate"));
            a.insert(a.begin(), vtype::value_type(1, "one slate"));
            a.insert(a.begin(), vtype::value_type(4, "four slate"));
        });
    map_test(
        "insert wh end",
        {
            a.insert(a.end(), vtype::value_type(0, "zero"));
        });
    map_test(
        "insert wh end three",
        {
            a.insert(a.end(), vtype::value_type(3, "three"));
            a.insert(a.end(), vtype::value_type(2, "two"));
            a.insert(a.end(), vtype::value_type(1, "one"));
        });
    map_test(
        "insert wh end five",
        {
            a.insert(a.end(), vtype::value_type(3, "three"));
            a.insert(a.end(), vtype::value_type(2, "two"));
            a.insert(a.end(), vtype::value_type(5, "five"));
            a.insert(a.end(), vtype::value_type(1, "one"));
            a.insert(a.end(), vtype::value_type(4, "four"));
        });
    map_test(
        "insert wh end five replace",
        {
            a.insert(a.end(), vtype::value_type(3, "three cold"));
            a.insert(a.end(), vtype::value_type(2, "two cold"));
            a.insert(a.end(), vtype::value_type(5, "five cold"));
            a.insert(a.end(), vtype::value_type(1, "one cold"));
            a.insert(a.end(), vtype::value_type(4, "four cold"));
            a.insert(a.end(), vtype::value_type(3, "three slate"));
            a.insert(a.end(), vtype::value_type(2, "two slate"));
            a.insert(a.end(), vtype::value_type(5, "five slate"));
            a.insert(a.end(), vtype::value_type(1, "one slate"));
            a.insert(a.end(), vtype::value_type(4, "four slate"));
        });
    map_test(
        "insert range",
        {
            vtype b;
            b.insert(vtype::value_type(3, "three"));
            b.insert(vtype::value_type(2, "two"));
            b.insert(vtype::value_type(5, "five"));
            b.insert(vtype::value_type(1, "one"));
            b.insert(vtype::value_type(4, "four"));

            a.insert(b.begin(), b.end());
        });
    map_test("find test",
        {
            a.insert(vtype::value_type(1, "hello"));
            a.insert(vtype::value_type(2, "hello"));
            a.insert(vtype::value_type(3, "hello"));
            a.insert(vtype::value_type(4, "hello"));
            vtype::iterator x = a.find(3);
            vtype::const_iterator xc = a.find(2);
            output << x->first << ", " << xc->first;
        });
    map_test("operator[]",
        {
            a[0] = "hello";
            a[1] = "world";
            a[2] = "how";
            a[0] = "are";
            a[1] = "you";
        });
    map_test("lowerbound test empty",
        {
            a.lower_bound(4);
        });
    map_test("lowerbound test",
        {
            a.insert(vtype::value_type(3, "three"));
            a.insert(vtype::value_type(2, "two"));
            a.insert(vtype::value_type(5, "five"));
            a.insert(vtype::value_type(1, "one"));
            a.insert(vtype::value_type(4, "four"));
            a.insert(vtype::value_type(13, "1three"));
            a.insert(vtype::value_type(12, "1two"));
            a.insert(vtype::value_type(15, "1five"));
            a.insert(vtype::value_type(11, "1one"));
            a.insert(vtype::value_type(14, "1four"));
            output << a.lower_bound(4)->first
                   << a.lower_bound(5)->first
                   << a.lower_bound(10)->first
                   << a.lower_bound(12)->first
                   << (a.lower_bound(100) == a.end());
        });
    map_test("upperbound test empty",
        {
            a.upper_bound(4);
        });
    map_test("upperbound test",
        {
            a.insert(vtype::value_type(3, "three"));
            a.insert(vtype::value_type(2, "two"));
            a.insert(vtype::value_type(5, "five"));
            a.insert(vtype::value_type(1, "one"));
            a.insert(vtype::value_type(4, "four"));
            a.insert(vtype::value_type(13, "1three"));
            a.insert(vtype::value_type(12, "1two"));
            a.insert(vtype::value_type(15, "1five"));
            a.insert(vtype::value_type(11, "1one"));
            a.insert(vtype::value_type(14, "1four"));
            output << a.upper_bound(4)->first
                   << a.upper_bound(5)->first
                   << a.upper_bound(10)->first
                   << a.upper_bound(12)->first
                   << (a.upper_bound(100) == a.end());
        });
    map_test("equal_range test empty",
        {
            a.equal_range(4);
        });
    map_test("equal_range test",
        {
            a.insert(vtype::value_type(3, "three"));
            a.insert(vtype::value_type(2, "two"));
            a.insert(vtype::value_type(5, "five"));
            a.insert(vtype::value_type(1, "one"));
            a.insert(vtype::value_type(4, "four"));
            a.insert(vtype::value_type(13, "1three"));
            a.insert(vtype::value_type(12, "1two"));
            a.insert(vtype::value_type(15, "1five"));
            a.insert(vtype::value_type(11, "1one"));
            a.insert(vtype::value_type(14, "1four"));
            output << a.equal_range(4).first->first << a.equal_range(4).second->first
                   << a.equal_range(5).first->first << a.equal_range(5).second->first
                   << a.equal_range(10).first->first << a.equal_range(10).second->first
                   << a.equal_range(12).first->first << a.equal_range(12).second->first
                   << (a.equal_range(100).first == a.end() && a.equal_range(100).second == a.end());
        });
    map_test("count",
        {
            int x = 0;
            a.insert(vtype::value_type(3, "three"));
            a.insert(vtype::value_type(2, "two"));
            a.insert(vtype::value_type(5, "five"));
            a.insert(vtype::value_type(1, "one"));
            a.insert(vtype::value_type(4, "four"));
            a.insert(vtype::value_type(13, "1three"));
            a.insert(vtype::value_type(12, "1two"));
            a.insert(vtype::value_type(15, "1five"));
            a.insert(vtype::value_type(11, "1one"));
            a.insert(vtype::value_type(14, "1four"));
            output << a.count(++x);
            output << a.count(++x);
            output << a.count(++x);
            output << a.count(++x);
            output << a.count(++x);
            output << a.count(++x);
            output << a.count(++x);
            output << a.count(++x);
            output << a.count(++x);
            output << a.count(++x);
            output << a.count(++x);
            output << a.count(++x);
        });
    map_test("ctor test range",
        {
            vtype x;
            x.insert(vtype::value_type(3, "three"));
            x.insert(vtype::value_type(2, "two"));
            x.insert(vtype::value_type(5, "five"));
            x.insert(vtype::value_type(1, "one"));
            x.insert(vtype::value_type(4, "four"));
            x.insert(vtype::value_type(13, "1three"));
            x.insert(vtype::value_type(12, "1two"));
            x.insert(vtype::value_type(15, "1five"));
            x.insert(vtype::value_type(11, "1one"));
            x.insert(vtype::value_type(14, "1four"));
            a = vtype(++x.begin(), --x.end());
        });
}

void stack_test()
{
    ft::stack<int> x;

    if (!x.empty()) {
        throw std::runtime_error("should be empty");
    }
    x.push(10);
    x.push(20);
    x.push(30);
    x.push(40);
    x.pop();
    if (x.empty()) {
        throw std::runtime_error("should be filled");
    }
    if (x.size() != 3) {
        throw std::runtime_error("size should be 3");
    }
    if (x.top() != 30) {
        throw std::runtime_error("front should be 30");
    }
}

void queue_test()
{
    ft::queue<int> q;

    if (!q.empty()) {
        throw std::runtime_error("should be empty");
    }
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.pop();
    if (q.empty()) {
        throw std::runtime_error("should be filled");
    }
    if (q.size() != 3) {
        throw std::runtime_error("size should be 3");
    }
    if (q.front() != 20) {
        throw std::runtime_error("front should be 20");
    }
    if (q.back() != 40) {
        throw std::runtime_error("back should be 40");
    }
}

int main()
{
    std::cout << "Vector tests:\n";
    vector_tests();
    std::cout << "List tests:\n";
    list_tests();
    std::cout << "Map tests:\n";
    map_tests();
    std::cout << "stack test\n";
    stack_test();
    std::cout << "queue test\n";
    queue_test();
    return 0;
}
