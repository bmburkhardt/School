#!/usr/bin/env lua
-- lexit.lua
-- Bryan Burkhardt
-- 25 Feb 2017
-- CS 331 - Assignment 3
-- Module lexit.lua for lexit_test.lua

local lexit = {}

-- Lexeme Categories
lexit.KEY = 1
lexit.VARID = 2
lexit.SUBID = 3
lexit.NUMLIT = 4
lexit.STRLIT = 5
lexit.OP = 6
lexit.PUNCT = 7
lexit.MAL = 8

-- Lexeme category names
lexit.catnames = {
    "Keyword",
    "VariableIdentifier",
    "SubroutineIdentifier",
    "NumericLiteral",
    "StringLiteral",
    "Operator",
    "Punctuation",
    "Malformed"
}

local preferOpFlag = false

-- preferOp
function lexit.preferOp()
    preferOpFlag = true
end

-- Function isLetter
-- Passed a characer and returns true if character is a letter.
local function isLetter(c)
    if c:len() ~= 1 then
        return false
    elseif c >= "A" and c <= "Z" then
        return true
    elseif c >= "a" and c <= "z" then
        return true
    else
        return false
    end
end

-- Function isDigit
-- Passed a character and returns true if character is a digit.
-- A digit is defined as 0 <= digit <= 9
local function isDigit(c)
    if c:len() ~=1 then
        return false
    else
        return (c >= "0" and c <= "9")
    end
end

-- Function isWhiteSpace
-- Passed a character and returns true if character is whitespace.
-- Whitespace is considered to be a character that is blank, tab, 
--      vertical-tab, new-line, carriage-return, or form feed.
local function isWhitespace(c)
    if c:len() ~= 1 then
        return false
    end
    return (c == " " or c == "\t" or c == "\n" or c == "\r"
      or c == "\f" or c == "\v")
end

-- Function isIllegal
-- Passed a character and returns if it's illegal. If character is legal,
--      function returns true. 
local function isIllegal(c)
    if c:len() ~= 1 then
        return false
    elseif isWhitespace(c) then
        return false
    elseif c >= " " and c <= "~" then
        return false
    else
        return true
    end
end

function lexit.lex(program)
    local pos
    local state
    local ch
    local lexstr
    local category

    -- States of the lexer
    local START = 0
    local DONE = 1
    local KEYWORD = 2
    local IDENTIFIER = 3
    local NUMLIT = 4
    local OP = 5
    local STRLIT = 6
    local EXP = 7

    -- Table of keywords in the language
    local keywords = 
    {
        ["call"] = true,
        ["cr"] = true,
        ["else"] = true,
        ["elseif"] = true,
        ["end"] = true,
        ["false"] = true,
        ["if"] = true,
        ["input"] = true,
        ["print"] = true,
        ["set"] = true,
        ["sub"] = true,
        ["true"] = true,
        ["while"] = true
    }

    -- A table of the first character of operators in the language
    -- All the keys are NOT valid operators. "&,!,|" are invalid
    local operators =
    {
        ["&"] = true,
        ["|"] = true,
        ["!"] = true,
        ["="] = true,
        ["<"] = true,
        [">"] = true,
        ["+"] = true,
        ["-"] = true,
        ["*"] = true,
        ["/"] = true,
        ["%"] = true,
        ["["] = true,
        ["]"] = true,
        [":"] = true,
    }

    -- currentChar
    -- Returns the current character.
    local function currentChar()
        return program:sub(pos,pos)
    end

    -- nextChar
    -- Returns the next character.
    local function nextChar()
        return program:sub(pos+1,pos+1)
    end

    -- nextCharBy
    -- Returns the character that is n spaces away from our current position.
    local function nextCharBy(n)
        return program:sub(pos+n,pos+n)
    end

    -- drop1
    -- Move pos to the next character.
    local function drop1()
        pos = pos+1
    end

    -- add1
    -- Adds the current character to the lexeme, moving pos to the next character.
    local function add1()
        lexstr = lexstr .. currentChar()
        drop1()
    end

    -- skipWhitespace
    -- Ships whitespace and comments, moving pos to the beginning of the next
    -- lexeme.
    local function skipWhitespace()
        while true do
            while isWhitespace(currentChar()) do
                drop1()
            end

            if currentChar() == "#" then
                while currentChar() ~= "\n" and currentChar() ~= "" do
                    drop1()
                end
                if currentChar() == "" then
                    return
                end
                drop1()
            end

            if isWhitespace(currentChar()) == false and currentChar() ~= "#" then
                return
            end
        end
    end

    -- ***** State-Handler Functions *****
    -- A function with a name like handle_XYZ is the handler function for state XYZ.
    
    -- Handles string literals.
    local function handle_STRLIT()
        closing = ch
        add1()
        ch = currentChar()
        while ch ~= "" and ch ~= closing do
            add1()
            ch = currentChar()
        end
        state = DONE
        if ch == "" then
            category = lexit.MAL
        else
            category = lexit.STRLIT
            add1()
        end
    end

    -- Handles operators.
    local function handle_OP()
        if ch == "&" or ch == "|" or ch == "=" then
            if ch == nextChar() then
                add1()
            else
                add1()
                state = DONE
                category = lexit.PUNCT
                return
            end
        elseif ch == "!" or ch == "<" or ch == ">" then
            if nextChar() == "=" then
                add1()
            end
        end
        add1()
        state = DONE
        category = lexit.OP
    end

    -- Handles numeric literals that have exponents.
    local function handle_EXP()
        if isDigit(ch) then
            add1()
        else
            state = DONE
            category = lexit.NUMLIT
        end
    end

    -- Handles numeric literals.
    local function handle_NUMLIT()
        if isDigit(ch) then
            add1()
        elseif ch == "e" or ch == "E" then
            if isDigit(nextChar()) then
                add1()
                state = EXP
            elseif nextChar() == "+" and isDigit(nextCharBy(2)) == true then
                add1()
                add1()
                state = EXP
            else
                state = DONE
                category = lexit.NUMLIT
            end
        else
            state = DONE
            category = lexit.NUMLIT
        end
    end

    -- Handles identifies which are either variable or subroutine identifiers.
    local function handle_IDENTIFIER()
        if isLetter(ch) or isDigit(ch) or ch == "_" then
            add1()
        else
            state = DONE
        end
    end 

    -- Handles keywords.
    local function handle_KEYWORD()
        if isLetter(ch) then
            add1()
        else
            state = DONE
            if keywords[lexstr] == true then
                category = lexit.KEY
            else
                category = lexit.MAL
            end
        end
    end

    -- Handles the start of a lexeme.
    local function handle_START()
        -- Illegal
        if isIllegal(ch) then
            add1()
            state = DONE
            category = lexit.MAL
        -- Must be a keyword
        elseif isLetter(ch) then
            add1()
            state = KEYWORD
        -- Identifiers
        elseif ch == "%" or ch == "&" then
            if preferOpFlag == true then
                if (ch == "&" and nextChar() == "&") or ch == "%" then
                    state = OP
                    return
                end
            end
            if isLetter(nextChar()) or nextChar() == "_" then
                add1()
                state = IDENTIFIER
                if ch == "%" then
                    category = lexit.VARID
                else
                    category = lexit.SUBID
                end
            else
                state = OP
            end
        -- Numeric Literals
        elseif isDigit(ch) then
            add1()
            state = NUMLIT
        -- Operator or numeric literals
        elseif ch == "+" or ch == "-" then
            if isDigit(nextChar()) and preferOpFlag == false then
                state = NUMLIT
            else
                state = DONE
                category = lexit.OP
            end
            add1()
        -- Operators
        elseif operators[ch] == true then
            state = OP
        -- String literal
        elseif ch == "\'" or ch == "\"" then
            state = STRLIT
        -- Punctuation
        else
            add1()
            state = DONE
            category = lexit.PUNCT
        end
    end

    -- Table of Handler-Functions
    handle = 
    {
        [START] = handle_START,
        [KEYWORD] = handle_KEYWORD,
        [IDENTIFIER] = handle_IDENTIFIER,
        [NUMLIT] = handle_NUMLIT,
        [OP] = handle_OP,
        [STRLIT] = handle_STRLIT,
        [EXP] = handle_EXP,
    }

    -- getLexeme
    -- Called each time through the for-in loop.
    -- Returns next lexeme and category.
    local function getLexeme(dummy1, dummy2)
        if pos > program:len() then
            preferOpFlag = false
            return nil,nil
        end

        lexstr = ""
        state = START

        while state ~= DONE do
            ch = currentChar()
            handle[state]()
        end

        skipWhitespace()
        preferOpFlag = false
        return lexstr,category
    end

    pos = 1
    skipWhitespace()
    return getLexeme, nil, nil
end

return lexit