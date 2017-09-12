#!/usr/bin/env lua
-- pa2_test.lua
-- Glenn G. Chappell
-- 3 Feb 2017
--
-- For CS F331 / CSCE A331 Spring 2017
-- Test Program for Assignment 2 Functions
-- Used in Assignment 2, Exercise B

pa2 = require "pa2"  -- Import pa2 module

EXIT_ON_FIRST_FAILURE = true
-- If EXIT_ON_FIRST_FAILURE is true, then this program exits after the
-- first failing test. If it is false, then this program executes all
-- tests, reporting success/failure for each.


-- *********************************************************************
-- Testing Package
-- *********************************************************************


tester = {}
tester.countTests = 0
tester.countPasses = 0

function tester.test(self, success, testName)
    self.countTests = self.countTests+1
    io.write("    Test: " .. testName .. " - ")
    if success then
        self.countPasses = self.countPasses+1
        io.write("passed\n")
    else
        io.write("********** FAILED **********\n")
    end
end

function tester.allPassed(self)
    return self.countPasses == self.countTests
end


-- *********************************************************************
-- Utility Functions
-- *********************************************************************


function fail_exit()
    if EXIT_ON_FIRST_FAILURE then
        io.write("**************************************************\n")
        io.write("* This test program is configured to exit after  *\n")
        io.write("* the first failing test. To make it execute all *\n")
        io.write("* tests, reporting success/failure for each, set *\n")
        io.write("* variable                                       *\n")
        io.write("*                                                *\n")
        io.write("*   EXIT_ON_FIRST_FAILURE                        *\n")
        io.write("*                                                *\n")
        io.write("* to false, near the start of file pa2_test.lua. *\n")
        io.write("**************************************************\n")
        io.write("\n")
        os.exit(1)
    end
end


-- printTable
-- Given a table, prints it in (roughly) Lua literal notation. If
-- parameter is not a table, prints <not a table>.
function printTable(t)
    -- out
    -- Print parameter, surrounded by double quotes if it is a string,
    -- or simply an indication of its type, if it is not number, string,
    -- or boolean.
    local function out(p)
        if type(p) == "number" then
            io.write(p)
        elseif type(p) == "string" then
            io.write('"'..p..'"')
        elseif type(p) == "boolean" then
            if p then
                io.write("true")
            else
                io.write("false")
            end
        else
            io.write('<'..type(p)..'>')
        end
    end

    if type(t) ~= "table" then
        io.write("<not a table>")
    end

    io.write("{ ")
    local first = true  -- First iteration of loop?
    for k, v in pairs(t) do
        if first then
            first = false
        else
            io.write(", ")
        end
        io.write("[")
        out(k)
        io.write("]=")
        out(v)
    end
    io.write(" }")
end


-- printArray
-- Given a table, prints it in (roughly) Lua literal notation for an
-- array. If parameter is not a table, prints <not a table>.
function printArray(t)
    -- out
    -- Print parameter, surrounded by double quotes if it is a string.
    local function out(p)
        if type(p) == "string" then io.write('"') end
        io.write(p)
        if type(p) == "string" then io.write('"') end
    end

    if type(t) ~= "table" then
        io.write("<not a table>")
    end

    io.write("{ ")
    local first = true  -- First iteration of loop?
    for k, v in ipairs(t) do
        if first then
            first = false
        else
            io.write(", ")
        end
        out(v)
    end
    io.write(" }")
end


-- tableEq
-- Compare equality of two tables.
-- Uses "==" on table values. Returns false if either of t1 or t2 is not
-- a table.
function tableEq(t1, t2)
    -- Both params are tables?
    local type1, type2 = type(t1), type(t2)
    if type1 ~= "table" or type2 ~= "table" then
        return false
    end

    -- Get number of keys in t1 & check values in t1, t2 are equal
    local t1numkeys = 0
    for k, v in pairs(t1) do
        t1numkeys = t1numkeys + 1
        if t2[k] ~= v then
            return false
        end
    end

    -- Check number of keys in t1, t2 same
    local t2numkeys = 0
    for k, v in pairs(t2) do
        t2numkeys = t2numkeys + 1
    end
    return t1numkeys == t2numkeys
end


-- getCoroutineValues
-- Given coroutine f, returns array of all values yielded by f when
-- passed param as its parameter, in the order the values are yielded.
function getCoroutineValues(f, param)
    assert(type(f)=="function",
           "getCoroutineValues: f is not a function")
    local covals = {}  -- Array of values yielded by coroutine f
    local co = coroutine.create(f)
    local ok, value = coroutine.resume(co, param)
    while (coroutine.status(co) ~= "dead") do
        table.insert(covals, value)
        ok, value = coroutine.resume(co)
    end
    assert(ok, "Error in coroutine")
    return covals
end


-- *********************************************************************
-- Test Suite Functions
-- *********************************************************************


function test_filterArray(t)
    local function test(t, f, inv, expect, msg)
        local outv = pa2.filterArray(f, inv)
        local success = tableEq(outv, expect)
        t:test(success, msg)
        if not success then
            io.write("Expect: ")
            printTable(expect)
            io.write("\n")
            io.write("Actual: ")
            printTable(outv)
            io.write("\n")
            io.write("\n")
            fail_exit()
        end
    end

    io.write("Test Suite: filterArray\n")

    local inv, expect

    local function gt6(n)
        return n > 6
    end

    local function lt8(n)
        return n < 8
    end

    local function lengt3(s)
        return s:len() > 3
    end

    inv = { }
    expect = { }
    test(t, gt6, inv, expect, "empty array")

    inv = { 2 }
    expect = { }
    test(t, gt6, inv, expect, "singleton array #1")

    inv = { 9 }
    expect = { 9 }
    test(t, gt6, inv, expect, "singleton array #2")

    inv = { 1, 7, 9, 3, 10, 6, 2, 7, 0 }
    expect = { 7, 9, 10, 7 }
    test(t, gt6, inv, expect, "array of 8 numbers")

    inv = { 8, 7, 8, 6, 8, 5, 8, 4, 8, 3, 8, 2, 8, 1, 8, 0, 8, -1, 8, -2 }
    expect = { 7, 6, 5, 4, 3, 2, 1, 0, -1, -2 }
    test(t, lt8, inv, expect, "array of 20 numbers")

    inv = { }
    for i = 1,100 do inv[i]=9 end
    expect = { }
    test(t, lt8, inv, expect, "medium array, filters to nothing")

    inv = { }
    for i = 1,100 do inv[i]=2 end
    expect = inv
    test(t, lt8, inv, expect, "medium array, filters to itself")

    inv = { 1 }
    for i = 2,99 do inv[i]=9 end
    inv[100] = 2
    expect = { 1, 2 }
    test(t, lt8, inv, expect, "medium array, filters to small")

    inv = { }
    for i = 1,10000 do inv[i]=1 end
    expect = { }
    test(t, gt6, inv, expect, "large array, filters to nothing")

    inv = { }
    for i = 1,10000 do inv[i]=8 end
    expect = inv
    test(t, gt6, inv, expect, "large array, filters to itself")

    inv = { 8 }
    for i = 2,9999 do inv[i]=1 end
    inv[10000] = 9
    expect = { 8, 9 }
    test(t, gt6, inv, expect, "large array, filters to small")

    inv = { "xyz", "3457", "a", "simultaneous" }
    expect = { "3457", "simultaneous" }
    test(t, lengt3, inv, expect, "array of strings")

end


function test_concatMax(t)
    local function test(t, ins, lim, expect, msg)
        local outs = pa2.concatMax(ins, lim)
        local success = outs == expect
        t:test(success, msg)
        if not success then
            io.write("Expect: "..expect.."\n")
            io.write("Actual: "..outs.."\n")
            io.write("\n")
            fail_exit()
        end
    end

    io.write("Test Suite: concatMax\n")

    local ins, expect

    ins = "a"
    expect = "aa"
    test(t, ins, 2, expect, "string of length 1, #1")
    expect = "aaaaaaaa"
    test(t, ins, 8, expect, "string of length 1, #2")
    expect = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    test(t, ins, 40, expect, "string of length 1, #3")

    ins="abcdefghijklmnop"
    expect=""
    test(t, ins, 7, expect, "string of length 16, #1")
    test(t, ins, 15, expect, "string of length 16, #2")
    expect = ins
    test(t, ins, 16, expect, "string of length 16, #3")
    expect=ins..ins..ins..ins
    test(t, ins, 70, expect, "string of length 16, #4")
    test(t, ins, 79, expect, "string of length 16, #5")
    expect=ins..ins..ins..ins..ins
    test(t, ins, 80, expect, "string of length 16, #6")
end

function test_filterTable(t)
    local function test(t, f, inv, expect, msg)
        local outv = pa2.filterTable(f, inv)
        local success = tableEq(outv, expect)
        t:test(success, msg)
        if not success then
            io.write("Expect: ")
            printTable(expect)
            io.write("\n")
            io.write("Actual: ")
            printTable(outv)
            io.write("\n")
            io.write("\n")
        end
    end

    io.write("Test Suite: filterTable\n")

    local inv, expect

    local function isOddNumber(n)
        return type(n) == "number" and n % 2 == 1
    end

    local function isLongString(s)
        return type(s) == "string" and s:len() > 3
    end

    inv = {}
    expect = {}
    test(t, isOddNumber, inv, expect, "isOddNumber, empty table")

    inv = {-101}
    expect = {-101}
    test(t, isOddNumber, inv, expect, "isOddNumber, singleton array")

    inv = {2,6,17,-4,0,-27,"hello",50,-1,true,false}
    expect = {[1]=2,[3]=17,[5]=0,[7]="hello",[9]=-1,[11]=false}
    test(t, isOddNumber, inv, expect, "isOddNumber, longer array")

    inv = {
        ["abc"]=2, ["hello"]="dog", [30000]=4,
        ["nevertheless"]=17, ["boat"]="cat", ["x"]="y",
        [true]=true, [false]=false
        }
    expect = {
        ["hello"]="dog", ["nevertheless"]=17, ["boat"]="cat"
        }
    test(t, isLongString, inv, expect, "isLongString")

end


function test_collatz(t)
    local function test(t, inv, expect)
        local outv = getCoroutineValues(pa2.collatz, inv)
        local success = tableEq(outv, expect)
        t:test(success, "sequence starting at "..inv)
        if not success then
            io.write("Expect (yielded values): ")
            printArray(expect)
            io.write("\n")
            io.write("Actual (yielded values): ")
            printArray(outv)
            io.write("\n")
            io.write("\n")
            fail_exit()
        end
    end

    io.write("Test Suite: collatz\n")

    local inv, expect

    inv = 1
    expect = {1}
    test(t, inv, expect)

    inv = 2
    expect = {2,1}
    test(t, inv, expect)

    inv = 3
    expect = {3,10,5,16,8,4,2,1}
    test(t, inv, expect)

    inv = 4
    expect = {4,2,1}
    test(t, inv, expect)

    inv = 5
    expect = {5,16,8,4,2,1}
    test(t, inv, expect)

    inv = 9
    expect = {9,28,14,7,22,11,34,17,52,26,13,40,20,10,5,16,8,4,2,1}
    test(t, inv, expect)

    inv = 27
    expect = {27,82,41,124,62,31,94,47,142,71,214,107,322,161,484,242,
        121,364,182,91,274,137,412,206,103,310,155,466,233,700,350,175,
        526,263,790,395,1186,593,1780,890,445,1336,668,334,167,502,251,
        754,377,1132,566,283,850,425,1276,638,319,958,479,1438,719,2158,
        1079,3238,1619,4858,2429,7288,3644,1822,911,2734,1367,4102,2051,
        6154,3077,9232,4616,2308,1154,577,1732,866,433,1300,650,325,976,
        488,244,122,61,184,92,46,23,70,35,106,53,160,80,40,20,10,5,16,8,
        4,2,1}
    test(t, inv, expect)

    inv = 100
    expect = {100,50,25,76,38,19,58,29,88,44,22,11,34,17,52,26,13,40,20,
        10,5,16,8,4,2,1}
    test(t, inv, expect)
end

function test_pa2(t)
    io.write("TEST SUITES FOR CS F331 / CSCE A331 ASSIGNMENT 2\n")
    test_filterArray(t)
    test_concatMax(t)
    test_collatz(t)
end


-- *********************************************************************
-- Main Program
-- *********************************************************************


test_pa2(tester)
io.write("\n")
if tester:allPassed() then
    io.write("All tests successful\n")
else
    io.write("Tests ********** UNSUCCESSFUL **********\n")
    io.write("\n")
    io.write("**************************************************\n")
    io.write("* This test program is configured to execute all *\n")
    io.write("* tests, reporting success/failure for each. To  *\n")
    io.write("* make it exit after the first failing test, set *\n")
    io.write("* variable                                       *\n")
    io.write("*                                                *\n")
    io.write("*   EXIT_ON_FIRST_FAILURE                        *\n")
    io.write("*                                                *\n")
    io.write("* to true, near the start of file pa2_test.lua.  *\n")
    io.write("**************************************************\n")
end
io.write("\n")

