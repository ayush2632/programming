/** author : ayush sharma **/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<cstring>

#include<algorithm>
#include<string>
#include<sstream>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<stack>

#define FOR(i,a,b) for(int i=a; i<b; i++)
#define FORr(i,a,b) for(int i=a ; i>=b; i--)
#define pb push_back
#define mp make_pair
#define ub upper_bound
#define lb lower_bound
#define si1(n) scanf("%d",&n)
#define si2(n1, n2) scanf("%d%d",&n1,&n2)
#define si3(n1,n2,n3) scanf("%d%d%d",&n1, &n2, &n3)
#define si4(n1,n2,n3,n4) scanf("%d%d%d%d",&n1, &n2, &n3, &n4)
#define ff first
#define ss second
#define READ(x) freopen(x,"r",stdin)
#define WRITE(x) freopen(x,"w",stdout)
#define show1(a) cout<<a<<"\n"
#define show2(a, b) cout<<a<<"   "<<b<<"\n"
#define show3(a, b, c) cout<<a<<"   "<<b<<"    "<<c<<"\n"
#define show4(a, b, c,d) cout<<a<<"   "<<b<<"    "<<c<<"   "<<d<<"\n"

using namespace std;
typedef long long LL;
typedef pair <int,int> pii;
typedef pair <pii, int> piii;
typedef pair<string,int> psi;
typedef vector<int> vi;
typedef unsigned long long ull;

const int sz = 1000005;
const int limit = 100005;
int pr_cnt;
bool sieve[limit];
int primes[limit];
LL n;
int k = 0;
int pf[100], mul[100];


void atkins(){
    int insert = 2;
    int root = ceil(sqrt(limit));
    primes[0] = 2;
    primes[1] = 3;
    for (int z = 0; z < limit; z++) sieve[z] = false; //Not all compilers have false as the       default boolean value
    for (int x = 1; x <= root; x++){
        for (int y = 1; y <= root; y++){
             //Main part of Sieve of Atkin
             int n = (4*x*x)+(y*y);
             if (n <= limit && (n % 12 == 1 || n % 12 == 5)) sieve[n] ^= true;
             n = (3*x*x)+(y*y);
             if (n <= limit && n % 12 == 7) sieve[n] ^= true;
             n = (3*x*x)-(y*y);
             if (x > y && n <= limit && n % 12 == 11) sieve[n] ^= true;
        }
    }
        //Mark all multiples of squares as non-prime
    for (int r = 5; r <= root; r++) if (sieve[r]) for (int i = r*r; i < limit; i += r*r) sieve[i] = false;
    //Add into prime array
    for (int a = 5; a < limit; a++){
        if (sieve[a]){
            primes[insert] = a;
            insert++;
        }
    }
    pr_cnt = insert;
}

vector<LL> divisors;

void getDivisors(LL res, int i){
    if(i == k) {
        if(res<=1) return;
        divisors.pb(res);
        return ;
    }
    LL temp = res;
    getDivisors(temp,i+1);
    FOR(j,0,mul[i]){
        temp = temp*(LL)pf[i];
        getDivisors(temp,i+1);
    }
    return;
}

void splitIntoFactors(){
    LL temp = n;
    int i=0;
    k = 0;
    while(n>1){
        int count = 0;
        while(n>1 && n%primes[i] == 0){
            count++;
            n/=primes[i];
        }
        if(count > 0){
            pf[k] = primes[i];
            mul[k++] = count;
        }
        i++;
        if(i>=pr_cnt || primes[i]>= ceil(sqrt(temp))) break;
    }
    if(n > 1) pf[k] = n, mul[k++] = 1;

    FOR(i,0,k){
        show2(pf[i], mul[i]);
    }
    getDivisors(1,0);
    sort(divisors.begin(),divisors.end());
    show2("total divisors",divisors.size());
    FOR(i,0,divisors.size()){
        cout<<divisors[i]<<"\n";
    }
    cout<<endl;
}


int main(){
    atkins();
    cin>>n;
    splitIntoFactors();
    return 0;
}
