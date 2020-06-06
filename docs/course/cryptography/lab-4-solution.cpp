#include <gmpxx.h>
#include <iostream>

using namespace std;

void solve1()
{
    mpz_class N(
        "17976931348623159077293051907890247336179769789423065727343008115773267580550562068698537944921298295958550138"
        "75371640157101398586478337786069255834975410851965916151280575759407526350074759352887108236499499407718956170"
        "54361149474865046711015101563940680527540071584560878577663743040086340742855278549092581");
    mpz_class p, q;
    mpz_class A, x;

    mpz_sqrt(A.get_mpz_t(), N.get_mpz_t());
    // 向上取整
    A++;
    mpz_class temp = A * A - N;
    mpz_sqrt(x.get_mpz_t(), temp.get_mpz_t());
    p = A - x;
    q = A + x;

    cout << "p: " << p << "\nq: " << q << endl;

    return;
}

void solve2()
{
    mpz_class N(
        "64845584280807166966282426534677227872634372070697626306043907037879730861808111646271401527606141756919558732"
        "18402545206554249067198924288448418393532819729885313105117386489659625828215025049902644521008852816733037111"
        "42296421027840289307657458645233683357077834689715838646088239640236866252211790085787877");
    mpz_class p, q;
    mpz_class A, x;

    for(int i = 1; i < 524288; i++) {
        mpz_sqrt(A.get_mpz_t(), N.get_mpz_t());
        A += i;
        mpz_class temp = A * A - N;
        mpz_sqrt(x.get_mpz_t(), temp.get_mpz_t());
        p = A - x;
        q = A + x;

        if(p * q == N) {
            cout << "p: " << p << "\nq: " << q << endl;
            break;
        }
    }

    return;
}

int main()
{
    cout << "Task 1:" << endl;
    solve1();
    cout << "\nTask 2:" << endl;
    solve2();
    return 0;
}