#include <gmpxx.h>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

void solve()
{
    mpz_class p("134078079299425970995740249982058461274793658205923933777235614437217640300735469768018742981669034276"
                "90031858186486050853753882811946569946433649006084171");
    mpz_class g("117178298803662070095161175963353670885580849999989522055999794590639294997365837466705721764714603129"
                "28594829675428279466566527115212748467589894601965568");
    mpz_class h("323947510405045044356526437872806578864909752095244952783479245297198197614329255807385693795855318053"
                "2878928001494706097394108577585732452307673444020333");
    // B = sqrt(p) + 1 向上取整
    mpz_class B("1048576");
    mpz_class x0("0"), x1("0"), x("-1");
    unordered_map<string, int> hashMap;

    // x1 = 0, 1, 2...。将等式右边的结果 h * g^x1 存入哈希表，key = h * g^x1，value = x1
    mpz_class productRight = h;
    for(int i = 0; i < B; i++) {
        hashMap[productRight.get_str()] = i;
        productRight = productRight * g % p;
    }
    cout << "Hash map saved!" << endl;

    // 等式左边的底数 baseLeft = g^B
    mpz_class baseLeft = 1;
    for(int i = 0; i < B; i++) {
        baseLeft = baseLeft * g % p;
    }

    // x0 = 0, 1, 2...。判断等式左边的结果 (g^B)^x0 是否在哈希表中
    mpz_class productLeft("1");
    for(int i = 1; i <= B; i++) {
        productLeft = productLeft * baseLeft % p;
        if(hashMap.find(productLeft.get_str()) != hashMap.end()) {
            x0 = i;
            x1 = hashMap[productLeft.get_str()];
            break;
        }
    }

    x = B * x0 - x1;
    if(x == -1) {
        cout << "There is no solution!" << endl;
        return;
    }
    cout << "x0:\t" << x0 << endl;
    cout << "x1:\t" << x1 << endl;
    cout << "x:\t" << x << endl;
    return;
}

int main()
{
    solve();
    return 0;
}