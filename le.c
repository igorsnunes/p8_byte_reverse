#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef INPUT32
  typedef int32_t base_type;
#else
  typedef int64_t base_type;
#endif

int main () {
  int SIZE = 10000000, i;
  base_type *in = (base_type*)malloc(sizeof(base_type)*SIZE);
  base_type *out = (base_type*)malloc(sizeof(base_type)*SIZE);

  for(i = 0; i < SIZE; i++) in[i] = i;

#ifdef INPUT32
#if  defined(AP1)
  asm volatile (
    "li  %[i],0\n\t"
    "li  15,8\n\t"
    "lvsl 1,0,15\n\t"
    "vspltisb 3,0xb\n\t"
    "vxor 1,1,3\n\t"
    "LOOP:\n\t"
    "lvx 0,%[i],%[in]\n\t"
    "vperm 0,0,0,1\n\t"
    "stvx 0,%[i],%[out]\n\t"
    "addi %[i],%[i],16\n\t"
    "cmpw %[i],%[SIZE]\n\t"
    "ble LOOP\n\t"
    :
    [i] "=&r" (i)
    :
    [in] "r" (in),
    [out] "r" (out),
    [SIZE] "r" (SIZE*4)
    :
    "memory","v0","r15","v1","v3"
    );
#elif defined(AP2)
  asm volatile (
    "li  %[i],0\n\t"
    "vspltisw 1,8\n\t"
    "vspltish 3,8\n\t"
    "vspltisw 4,1\n\t"
    "vsl 1,1,4\n\t"
    "LOOP:\n\t"
    "lvx 0,%[i],%[in]\n\t"
    "vrlh 0,0,3\n\t"
    "vrlw 0,0,1\n\t"
    "stvx 0,%[i],%[out]\n\t"
    "addi %[i],%[i],16\n\t"
    "cmpw %[i],%[SIZE]\n\t"
    "ble LOOP\n\t"
    :
    [i] "=&r" (i)
    :
    [in] "r" (in),
    [out] "r" (out),
    [SIZE] "r" (SIZE*4)
    :
    "memory","v0","v1","v3","v4"
    );
#else
  asm volatile (
    "li  %[i],0\n\t"
    "LOOP:\n\t"
    "lwbrx 6,%[i],%[in]\n\t"
    "stwx 6,%[i],%[out]\n\t"
    "addi %[i],%[i],4\n\t"
    "cmpw %[i],%[SIZE]\n\t"
    "ble LOOP\n\t"
    :
    [i] "=&r" (i)
    :
    [in] "r" (in),
    [out] "r" (out),
    [SIZE] "r" (SIZE*4)
    :
    "memory","r6"
    );
#endif
  for (i = 0; i < SIZE;i++)  printf("%d ",out[i]);
#else
#if defined(AP1)
  asm volatile (
    "li  15,8\n\t"
    "lvsl 1,0,15\n\t"
    "vspltisb 3,0xf\n\t"
    "vxor 1,1,3\n\t"
    "LOOP:\n\t"
    "lvx 0,%[i],%[in]\n\t"
    "vperm 0,0,0,1\n\t"
    "stvx 0,%[i],%[out]\n\t"
    "addi %[i],%[i],16\n\t"
    "cmpw %[i],%[SIZE]\n\t"
    "ble LOOP\n\t"
    :
    [i] "=&r" (i)
    :
    [in] "r" (in),
    [out] "r" (out),
    [SIZE] "r" (SIZE*8)
    :
    "memory","v0","r15","v1","v3"
    );
#elif defined(AP2)
  asm volatile (
    "li  %[i],0\n\t"
    "vspltisw 1,8\n\t"
    "vspltisw 3,1\n\t"
    "vsl 1,1,3\n\t"
    "vsl 4,1,3\n\t"
    "vspltish 5,8\n\t"
    "LOOP:\n\t"
    "lvx 0,%[i],%[in]\n\t"
    "vrlh 0,0,5\n\t"
    "vrlw 0,0,1\n\t"
    "vrld 0,0,4\n\t"
    "stvx 0,%[i],%[out]\n\t"
    "addi %[i],%[i],16\n\t"
    "cmpw %[i],%[SIZE]\n\t"
    "ble LOOP\n\t"
    :
    [i] "=&r" (i)
    :
    [in] "r" (in),
    [out] "r" (out),
    [SIZE] "r" (SIZE*8)
    :
    "memory","v0","v1","v3","v4","v5"
    );
#else
  asm volatile (
    "li  %[i],0\n\t"
    "LOOP:\n\t"
    "ldbrx 6,%[i],%[in]\n\t"
    "stdx 6,%[i],%[out]\n\t"
    "addi %[i],%[i],8\n\t"
    "cmpw %[i],%[SIZE]\n\t"
    "ble LOOP\n\t"
    :
    [i] "=&r" (i)
    :
    [in] "r" (in),
    [out] "r" (out),
    [SIZE] "r" (SIZE*8)
    :
    "memory","r6"
    );
#endif
  for (i = 0; i < SIZE;i++)  printf("%ld ",out[i]);
#endif
  return 0;
}
