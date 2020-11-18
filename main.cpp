//#include "list.hpp"
#include "newerlist.hpp"
#include "vector.hpp"
#include <iostream>
#include <list>
#include <sstream>
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
            typedef std::list<int> vtype;              \
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
    evaluate_list(a, stream);
    evaluate_list(b, stream);
    evaluate_list(c, stream);
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

}

int main()
{
    vector_tests();
    list_tests();
    return 0;
}