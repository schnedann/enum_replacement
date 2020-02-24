#include <iostream>
#include <cstdint>
#include <string>

using namespace std;

using u8  = uint8_t;
using u16 = uint16_t;

struct thisisaenum_st{
  u8 A;
  u8 B;
  u8 C;
  u8 D;
  u8 E;
  u8 F;
  u8 G;
  u8 H;
} const thisisaenum = {2,3,5,7,11,13,17,19};

template<typename S, typename T> struct in_enum{
  constexpr static size_t elements = sizeof(S)/sizeof(T);
  static bool exists(T const* _p, T const _v){
    bool res = false;
    for(size_t ii=0; ii<elements; ++ii){
      if(_v==_p[ii]) res = true;
    }
    return res;
  }
};

int main(){

  cout << "-> " << u16(thisisaenum.A) << endl;
  cout << "-> " << u16(thisisaenum.B) << endl;
  cout << "-> " << u16(thisisaenum.C) << endl;
  cout << "-> " << u16(thisisaenum.D) << endl;
  cout << "-> " << u16(thisisaenum.E) << endl;
  cout << "-> " << u16(thisisaenum.F) << endl;
  cout << "-> " << u16(thisisaenum.G) << endl;
  cout << "-> " << u16(thisisaenum.H) << endl;

  for(u8 ii=0; ii<35; ++ii){
    bool res = in_enum<thisisaenum_st,u8>::exists(&thisisaenum.A,ii);
    string str = (res)?("+"):("-");
    cout << "[" << u16(ii) << "]: -> " << str << "\n";
  }

  return 0;
}
