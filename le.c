#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#ifdef INPUT32
  typedef int32_t base_type;
#else
  typedef int64_t base_type;
#endif

void swap_bytes(unsigned char *input, unsigned char *output, size_t size) {

  for (size_t i = 0; i < size; i++) {
    base_type *input_cast = (base_type*)input+i;
    base_type *output_cast = (base_type*)output+i;
    *output_cast =
#if defined(INPUT32)
      (*input_cast & 0xFF000000) >> 24 |
      (*input_cast & 0x00FF0000) >>  8 |
      (*input_cast & 0x0000FF00) <<  8 |
      (*input_cast & 0x000000FF) << 24;
#else
      (*input_cast & 0xFF00000000000000ULL) >> 56 |
      (*input_cast & 0x00FF000000000000ULL) >> 40 |
      (*input_cast & 0x0000FF0000000000ULL) >> 24 |
      (*input_cast & 0x000000FF00000000ULL) >>  8 |
      (*input_cast & 0x00000000FF000000ULL) <<  8 |
      (*input_cast & 0x0000000000FF0000ULL) << 24 |
      (*input_cast & 0x000000000000FF00ULL) << 40 |
      (*input_cast & 0x00000000000000FFULL) << 56;
#endif
  }
}

int main (int argc, char *argv) {
  int SIZE_IN =
#ifdef INPUT32
1015808
#else
516096
#endif
  , i;
  base_type  in[SIZE_IN] __attribute__ ((aligned (16)));
  base_type out[SIZE_IN] __attribute__ ((aligned (16))) ;

  for (i = 0; i < SIZE_IN; i++) in[i] = i;
  for (int SIZE = SIZE_IN/112; SIZE < SIZE_IN; SIZE = SIZE + SIZE_IN/112) {
    clock_t t;
    t = clock();
#ifdef INPUT32
#if  defined(VPERM)
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
#elif defined(ROTATE)
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
#elif defined(CVERSION)
  swap_bytes((unsigned char*)in, (unsigned char*)out, SIZE);
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
#else
#if defined(VPERM)
  asm volatile (
    "li  %[i],0\n\t"
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
#elif defined(ROTATE)
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
#elif defined(CVERSION)
  swap_bytes((unsigned char*)in, (unsigned char*)out, SIZE);

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
#endif
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("%d %f\n", SIZE, time_taken);
  }
  char filename[100];

  sprintf(filename, "out.txt.%d", getpid());
  FILE *file = fopen(filename,"w");
  for (i = 0; i < SIZE_IN;i++)
#if defined(INPUT32)
    fprintf(file, "%d ",out[i]);
#else
    fprintf(file, "%ld ",out[i]);
#endif
  fclose(file);
  return 0;
}
