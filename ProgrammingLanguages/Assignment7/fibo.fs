\ : collcount (n -- c)
\	cr
\ ;

\ fibo.fs
\ Glenn G. Chappell
\ 6 Mar 2017
\
\ For CS F331 / CSCE A331 Spring 2017
\ Compute Fibonacci Numbers


\ advance
\ Given pair of consecutive Fibonacci numbers (F[n], F[n+1]), returns
\ next such pair (F[n+1] F[n+2]).
\ Used by fibo.
: advance  ( a b -- b a+b )
  swap    \ Stack: b a
  over    \ Stack: b a b
  +       \ Stack: b a+b
;


\ fibo
\ Compute F[n]: the nth Fibonacci number.
\ F[0] = 0. F[1] = 1. For n >= 2, F[n] = F[n-2] + F[n-1].
\ Uses fast iterative algorithm.
\ Gives correct results:
\ - On 32-bit systems, for n = 0 .. 46
\ - On 64-bit systems, for n = 0 .. 92
: fibo  ( n -- F[n] )
  0 1     \ Stack: n 0 1
  rot     \ Stack: 0 1 n
  0 ?do   \ Counted loop: n times
    advance
  loop
          \ Stack: F[n] F[n+1]
  drop    \ Stack: F[n]
;


\ printfibos
\ Print i & Fibonacci number i in a nice format, for i = 0..k, each on a
\ separate line.
: printfibos  ( k -- )
  cr
  1 + 0 ?do   \ Counted loop: k+1 times
    ." F("
    i 1 .r  \ Output loop counter with no trailing blank
    ." ) = "
    i fibo .
    cr
  loop
;

