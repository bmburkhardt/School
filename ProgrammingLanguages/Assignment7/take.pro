% take.pro
% Bryan Burkhardt
% 29 Apr 2017
% CS 331 - Assignment 7
% Excercise D - Basic Prolog

take(_, [], []).
take(0, _, []).

% Takes a number N and two lists. Returns true if
%		first N elements are identical in each list.
take(N, [X|Xs], [X|Es]):- M is N-1, take(M,Xs,Es).