#include <iostream>

using namespace std;
uint64_t rrsp, rrbp;

volatile int foo(void) {
  unsigned long val=0x1234567890abcdef;
  __asm__ volatile(
    "mov %0, (%%rbp)\n"
    "nop\n"
    ::"r" (val):
  );
  __asm__ volatile(
    "mov (%%rbp), %0\n"
    "nop\n"
    :"=r"(val)::
  );
  cout<<"val : " << hex << val << dec << endl;
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
    uint64_t a=foo();
    return 0;
}