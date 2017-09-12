-- median.hs
-- Bryan Burkhardt
-- 29 Mar 2017
-- CS 331 - Assignment 5
-- median.hs program that receives a list of integers from the user.
--      Once user decides to end input, program will sort the list and 
--      return the median value.
--
-- Preconditions / readme:
--      User must enter integer values (one per line) or a blank line. Any 
--      other input is not currently handled (ex: strings, doubles/floats, etc) 
--      and will crash the program.

import Data.List  -- for sort
import System.IO  -- for hFlush

-- Function getList
-- This function prompts the user for input and stores a list of
--      integer values until a blank line is sent as input.
getList :: IO [Int]
getList = getList' []
    where
        getList' x = do
        putStr "Enter number (blank line to end):"
        hFlush stdout
        num <- getLine
        if (num == [])
            then return x
            else getList' $ (read num :: Int):x

-- Function computeMedian
-- This function takes a list of integers given by the user. computeMedian
--      sorts the list, gets the length of the list, finds the middle of the list,
--      then returns the middle value of the sorted list.
--
--      If a list of even length if passed, the value to the right of the middle
--      is returned.
--
--      Function completes by printing the median.
computeMedian userList = do
    sortedList <- return (sort userList)
    lengthList <- return (length sortedList)
    middleList <- return (div lengthList 2)
    median <- return (sortedList !! middleList)
    putStr "Median: "
    print median
    putStrLn ""

-- Function computeAnother
-- Loop function that repeats the program until user prompts to quit.
computeAnother = do
    putStr "Compute another median? [y/n]"
    hFlush stdout
    restart <- getLine
    if restart == "y"
        then do
            putStrLn ""
            main
        else putStrLn "Bye!"

main = do
    putStrLn "Enter a list of integers, one on each line."
    putStrLn "I will compute the median of the list."
    putStrLn ""
    hFlush stdout
    input <- getList
    if (input == [])
        then putStrLn "Empty list - no median\n"
        else computeMedian input
    computeAnother
    