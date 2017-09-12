#lang scheme
; evenitems.scm
; Bryan Burkhardt
; 29 April 2017
; CS 331 - Assignment 7
; Excercise C - Basic Scheme

; evenitems take a list and returns the items in the even
;   indices
(define (evenitems list)
  (if (null? list) '()
      (if (not(null? (cdr list)))
                (cons (car list) (evenitems (cddr list))) 
      list)    
  )
)