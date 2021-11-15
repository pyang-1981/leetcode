#include <algorithm>
#include <iostream>
#include <map>
#include <string>

using namespace std;

struct mult_entry {
    char res;
    char carry;
    mult_entry() = default;
    mult_entry(char res, char carry)
    {
        this->res = res;
        this->carry = carry;
    }
};

auto create_mult_table()
{
    map<string, mult_entry> m;
    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j <= 9; j++) {
            char res = ((i * j) % 10) + 48;
            char carry = (i * j) / 10 + 48;
            m.insert({to_string(i) + "*" + to_string(j), mult_entry(res, carry)});
        }
    }

    return m;
}

map<string, mult_entry> mult_table = create_mult_table();

struct add_entry {
    char res;
    char carry;
    add_entry() = default;
    add_entry(char res, char carry)
    {
        this->res = res;
        this->carry = carry;
    }
};

auto create_add_table()
{
    map<string, add_entry> m;
    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j <= 9; j++) {
            char res = ((i + j) % 10) + 48;
            char carry = (i + j) / 10 + 48;
            m.insert({to_string(i) + "+" + to_string(j), add_entry(res, carry)});
        }
    }

    return m;
}

map<string, add_entry> add_table = create_add_table();

const add_entry&
add_char_num(char n1, char n2)
{

    const string key = string(1, n1) + "+" + string(1, n2);
    const auto &entry = add_table[key];
    
    return entry;
}

auto add_str_num(const string &n1, const string &n2)
{
    const string *s, *l;
    if (n1.size() <= n2.size()) {
        s = &n1;
        l = &n2;
    } else {
        s = &n2;
        l = &n1;
    }

    string res;
    char carry = 48; //0
    for (int i = s->size() - 1, j = l->size() - 1; i >= 0 && j >= 0; i--, j--) {
        const auto &entry = add_char_num((*s)[i], (*l)[j]);
        const auto &res_entry = add_char_num(entry.res, carry);
        const auto &carry_entry = add_char_num(res_entry.carry, entry.carry);
        carry = carry_entry.res;
        res.push_back(res_entry.res);
    }

    if (l->size() == s->size() && carry != '0') {
        res.push_back(carry);
    } else {
        for (int i = l->size() - s->size() - 1; i >= 0; i--) {
            const auto &res_entry = add_char_num((*l)[i], carry);
            res.push_back(res_entry.res);
            carry = res_entry.carry;
        }
        if (carry != '0') {
            res.push_back(carry);
        }
    }

    reverse(res.begin(), res.end());

    return res;
}

const mult_entry&
mult_char_num(char n1, char n2)
{
    const string key = string(1, n1) + "*" + string(1, n2);
    return mult_table[key];
}

string
mult_schar_num(char n1, const string &n2)
{
    string res;
    char carry = '0';
    for (int i = n2.size() - 1; i >= 0; i--) {
        const auto &entry = mult_char_num(n1, n2[i]);
        const auto &res_entry = add_char_num(entry.res, carry);
        const auto &carry_entry = add_char_num(entry.carry, res_entry.carry);
        res.push_back(res_entry.res);
        carry = carry_entry.res;
    }
    if (carry != '0') {
        res.push_back(carry);
    }
    reverse(res.begin(), res.end());

    return res;
}

string
mult_string_num(const string &n1,const string &n2)
{
    string res;
    string sum = "0";

    for (int i = n1.size() - 1; i >= 0; i--) {
        string component = mult_schar_num(n1[i], n2);
        for (int j = 0; j < n1.size() - 1 - i; j++) {
            component.push_back('0');
        }
        sum = add_str_num(sum, component);
    }

    if (sum[0] == '0') {
        return "0";
    }
    return sum;
}

int main()
{
    string n1 = "0";
    string n2 = "273";

    cout << mult_string_num(n1, n2) << endl;
}
