//
//  main.cpp
//  ASM_tasks
//
//  Created by MacBook Air M1 on 16.04.23.
//

#include <iostream>
using namespace std;
int SumOfNumbersLEThat10(int* a, int n){  // сумма чисел массива <= 10
 int sum = 0;
 __asm{
 mov eax, 0
 mov ebx, 10
 mov ecx, n
 mov esi, a
 for_label:
 cmp [esi], ebx
 jg label_1
 add eax, [esi]
 label_1:
 add esi, 4
 loop for_label
 mov sum, eax
   }
    return sum;
}
bool IsNumberPrime(int value){ // проверка числа на простоту
int result=1;
__asm{
mov ebx, value
mov ecx, 3
mov eax, ebx
mov edi, 2
cdq
idiv edi
cmp edx, 0
je not_prime
for_1:
mov eax, value
cmp ecx, eax
je end_for
cdq
idiv ecx
cmp edx, 0
je not_prime
add ecx, 1
jmp for_1
not_prime:
mov ecx, 0
mov result, ecx
end_for:
nop
}
return result;
}
bool IsNumberPerfect(int value){ // проверка числа на совершенство
    int sum=0;
    __asm{
    mov esi, 0
    mov ebx, value
    mov ecx, 1
    main_while:
    mov eax, ebx
    cmp ecx, ebx
    jge finish
    mov edx, 0
    idiv ecx
    add ecx, 1
    cmp edx, 0
    jne else_1
    add esi, ecx
    sub esi, 1
    else_1:
    jmp main_while
    finish:
    mov sum, esi
    }
    return sum==value;
}
char print_number[] = "%s\n";
void Print_number(int n){
    __asm{
    push n
    push offset print_number
    call printf
    pop ebx
    pop ebx
    }
}
void Reverse(int* a, int n){
    __asm{
    mov ecx, n
    mov edx, 0
    sub esi, a
    lea edi, [esi + 4*ecx]
    sub ecx, 1
    while_main:
    cmp esi, edi
    jge end_1
    mov eax, [esi]
    mov ebx, [edi]
    mov [esi], ebx
    mov [edi], eax
    add esi, 4
    sub edi, 4
    jmp while_main
    end_1:
    mov esi, a
    lea edi, [esi + 4*ecx]
    end_2:
    cmp esi, edi
    je end_3
    push [esi]
    call Print_number
    add esp, 4
    add esi, 4
    jmp end_2
    end_3:
    nop
    }

}
bool IsNumberPalindrome(int value){ // проверка числа на палиндром
    int result=0;
    int* a = new int[10];
    __asm{
     mov esi, a
     mov eax, value
     mov ecx, 0
     mov ebx, 0
     mov edi, 0 // elem
     reverse_for:
     cmp eax, 0
     je next_label
     cdq
     mov edi, 10
     idiv edi
     mov [esi + 4*ecx], edx
     add ecx, 1
     jmp reverse_for
     next_label:
     cmp ebx, ecx
     je end_label
     mov edi, 10
     imul edi
     add eax, [esi + 4*ebx]
     add ebx, 1
     jmp next_label
     end_label:
     mov result, eax
    }
    return result==value;
}
int main(int argc, const char * argv[]) {
    int n; cin >> n;
    int* a = new int[n];
    for(int i=0; i<n; ++i){
        cin >> a[i];
    }
    __asm{
    push a
    push n
    call Reverse
    add esp, 8
    }
   
    return 0;
}
