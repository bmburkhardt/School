-- PA5.hs
-- Bryan Burkhardt
-- 29 Mar 2017
-- CS 331 - Assignment 5
-- PA5.hs program for excercise B. Testing program for PA5.hs
--		is pa5_test.hs

module PA5 where
import Data.List

-- ****** collatzCounts Problem ******

-- Function collatz
-- Takes a number n and repeats the steps of the collatz process.
collatz n
    | n == 0 = 0
    | mod n 2 == 0 = div n 2
    | otherwise = 3*n+1


-- Function collatzSequence
-- Runs collatz function until 1 is reached.
collatzSequence n
    | n == 1 = 0
    | collatz n == 1 = 1
    | otherwise = 1 + collatzSequence (collatz n)

-- collatzCounts is a list of how many steps is required for the given
--		number to reach 1. The list passed is from 1 to X.
collatzCounts = map collatzSequence [1..]



-- ****** findList Problem ******

-- Function findList
-- Returns the first index where a given string or value begins/exists.
findList :: Eq a => [a] -> [a] -> Maybe Int
findList a b = findIndex (isPrefixOf a) (tails b)



-- ****** Infix Operator ## Problem ******

-- Infix operator ##
-- Compares 2 lists and returns how many indexes contain equal values
--		between the 2 lists.
(##) :: Eq a => [a] -> [a] -> Int
a ## b = length $ filter (\(x,y) -> x == y) $ zip a b



-- ****** filterAB Problem ******

-- Function secondListValue
-- This function is used to get the value from the 2nd list for when 
--		filterAB is true.
secondListValue (_,list2) = list2

-- Function filterAB
-- This function takes a boolean test and 2 lists. Function returns
--		the value of the 2nd list for which the value of the 1st list
--		is true for the boolean case given.
filterAB :: (a -> Bool) -> [a] -> [b] -> [b]
filterAB test list1 list2 = returnList where
    trueList = (filter (test.fst) $ zip list1 list2)
    returnList = secondListValue (unzip trueList)