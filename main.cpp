#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

const int BASE = 13;
const int SIZE = 13;

class Digit {
public:
    Digit() : digits({})
    {
        digits.reserve(SIZE);
    }

    void load(const string& data)
    {
        for (auto d : data) {
            char* err = nullptr;
            auto res = strtoul(&d, &err, BASE);
            if (res == 0 && (err - &d) == 0) {
                string text = "bad format "; text.push_back(d); text.append(" should be equal A,B or C");
                throw std::runtime_error( text );
            }
            digits.push_back(res);
        }
    }
    ~Digit()
    {
        digits.clear();
    }

    bool isNice() const
    {
        long rb = 0;
        long re = 0;
        for_each(digits.begin(), digits.begin() + 6, [&](const long& item) {
            rb += item;
        });
        for_each(digits.end() - 6, digits.end(), [&](const long& item) {
            re += item;
        });

        return (rb == re);
    }

private:
    vector<long> digits;
};

static vector<string> DATA = { "ABA98859978C0", "6789110551234", "0000007000000" };

int main()
{
    int count = 0;
    for( auto d : DATA){
        try{
            Digit digit;
            digit.load(d);
            bool isNice = digit.isNice();
            if (isNice) count++;
            cout << boolalpha << d << " " << isNice << endl;
        }
        catch (exception& err) {
            cout << "don't convert " << d << " " << " -> " << err.what() << endl;
        }
    }
    cout << "Count \"nice\" digits = " << count << endl;
    return 0;
}
