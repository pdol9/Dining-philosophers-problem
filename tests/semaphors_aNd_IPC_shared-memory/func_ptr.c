

/* 

// https://stackoverflow.com/questions/997821/how-to-make-a-function-return-a-pointer-to-a-function-c
// https://stackoverflow.com/questions/25671410/function-that-returns-a-function-pointer-syntax

https://stackoverflow.com/questions/3707096/spiral-rule-and-declaration-follows-usage-for-parsing-c-and-c-declarations
https://cdecl.org/
 */

int f1() {
    return 1;
}

int f2() {
    return 2;
}

typedef int (*fptr)();


fptr f( char c ) {
    if ( c == '1' ) {
        return f1;
    }
    else {
        return f2;
    }
}

int main() {
    char c = '1';
    fptr fp = f( c );
    cout << fp() << endl;
}
