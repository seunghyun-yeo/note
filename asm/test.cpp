#include <iostream>

using namespace std;
uint64_t rrsp, rrbp;
volatile int foo(void) {
  unsigned long val=0x1234567890abcdef;
  __asm__ volatile(
    "mov %%rsp, %0\n"
    "mov %%rbp, %1\n"
    "mov %2, (%%rbp)\n"
    "nop\n"
    :"=r"(rrsp), "=r" (rrbp):"r" (val):
  );
    // cout<< "rbp : " << hex << rrbp << dec << endl;
    // cout<< "rsp : " << hex << rrsp << dec << endl;
  __asm__ volatile(
    "mov (%%rbp), %0\n"
    "nop\n"
    :"=r"(val)::
  );
  // cout<<"val : " << hex << val << dec << endl;
  // cout<< "rbp : " << hex << rrbp << dec << endl;
  rrbp=rrbp+0x20;
  __asm__ volatile(
     "mov %0, (%%rbp)\n"
    ::"r" (rrbp):
  );
  return val;
}
int main(){
  __asm__ volatile(
    "mov %%rsp, %0\n"
    "mov %%rbp, %1\n"
    :"=r"(rrsp), "=r" (rrbp)::
  );
    cout<< "rbp : " << hex << rrbp << dec << endl;
    cout<< "rsp : " << hex << rrsp << dec << endl;
    uint64_t a=foo();
    return 0;
}