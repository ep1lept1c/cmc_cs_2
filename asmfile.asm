section .data
three dd 3
two dd 2
one dd 1
section .text
global func1
func1:
    push ebp
    mov ebp, esp
    finit
    fldz
    fld1
    fld1
    fld qword[ebp + 8]; st0 = x, st1 = 1, st3 = 0 для сравнения
    fcomi st0, st3
    jnc plus
    fxch st3
    fld1
    faddp
    fxch st3	
    fabs
    plus:
    L:
        fcomi st0, st1
        jc pow_below1
        fisub dword[one]
        fxch st2
        fimul dword[two]
        fxch st2
        jmp L
    pow_below1:
        f2xm1
        faddp
    fmulp
    fld1
    fcomi st0, st2
    jz wasminus
    faddp
    faddp
    jmp end
    wasminus:
    	fisub dword[one]
    	faddp
    	fdivp
    	fld1
    	faddp
    end:
    leave
    ret



global func2
func2:
push ebp
mov ebp, esp
finit
fld qword[ebp + 8]
fld qword[ebp + 8]
fld qword[ebp + 8]
fld qword[ebp + 8]
fld qword[ebp + 8]
fmulp
fmulp
fmulp
fmulp
leave
ret

global func3
func3:
push ebp
mov ebp, esp
finit
fld1
fld qword[ebp + 8]
fsubp
fidiv dword[three]
leave
ret
