#!/usr/bin/env lua
-- parseit.lua
-- Bryan Burkhardt
-- 20 Mar 2017
-- CS 331 - Assignment 4
-- Module parseit.lua for parseit_test.lua
-- Parser module for Kanchil programming language

-- Grammar
-- Start symbol: program. Lines are numbered for later reference.
--
-- (1)     	program 	  →   	stmt_list
-- (2)     	stmt_list 	  →   	{ statement }
-- (3)     	statement 	  →   	“cr”
-- (4)     	  	|   	“print” ( STRLIT | expr )
-- (5)     	  	|   	“input” lvalue
-- (6)     	  	|   	“set” lvalue “:” expr
-- (7)     	  	|   	“sub” SUBID stmt_list “end”
-- (8)     	  	|   	“call” SUBID
-- (9)     	  	|   	“if” expr stmt_list { “elseif” expr stmt_list } [ “else” stmt_list ] “end”
-- (10)     	  	|   	“while” expr stmt_list “end”
-- (11)     	expr 	  →   	comp_expr { ( “&&” | “||” ) comp_expr }
-- (12)     	comp_expr 	  →   	“!” comp_expr
-- (13)     	  	|   	arith_expr { ( “==” | “!=” | “<” | “<=” | “>” | “>=” ) arith_expr }
-- (14)     	arith_expr 	  →   	term { ( “+” | “-” ) term }
-- (15)     	term 	  →   	factor { ( “*” | “/” | “%” ) factor }
-- (16)     	factor 	  →   	( “+” | “-” ) factor
-- (17)     	  	|   	“(” expr “)”
-- (18)     	  	|   	NUMLIT
-- (19)     	  	|   	( “true” | “false” )
-- (20)     	  	|   	lvalue
-- (21)     	lvalue 	  →   	VARID [ “[” expr “]” ]

-- The 13 binary operators are all left-associative: &&, ||, ==, !=, <, <=, >, >=, binary +, binary -, *, /, %.

local parseit = {} -- Our module

lexit = require "lexit"

-- Variables

-- For lexer iteration
local iter          -- Iterator returned by lexit.lex
local state         -- State for above iterator (maybe not used)
local lexer_out_s   -- Return value #1 from above iterator
local lexer_out_c   -- Return value #2 from above iterator

-- For current lexeme
local lexstr = ""   -- String form of current lexeme
local lexcat = 0    -- Category of current lexeme:
                    --  one of categories below, or 0 for past the end

-- Symbolic Constants for AST
STMT_LIST   = 1
CR_STMT     = 2
PRINT_STMT  = 3
INPUT_STMT  = 4
SET_STMT    = 5
SUB_STMT    = 6
CALL_STMT   = 7
IF_STMT     = 8
WHILE_STMT  = 9
BIN_OP      = 10
UN_OP       = 11
NUMLIT_VAL  = 12
STRLIT_VAL  = 13
BOOLLIT_VAL = 14
VARID_VAL   = 15
ARRAY_REF   = 16

-- Utility Functions

-- advance
-- Go to next lexeme and load it into lexstr, lexcat.
-- Should be called once before any parsing is done.
-- Function init must be called before this function is called.
local function advance()
    -- Advance the iterator
    lexer_out_s, lexer_out_c = iter(state, lexer_out_s)

    -- If we're not past the end, copy current lexeme into vars
    if lexer_out_s ~= nil then
        lexstr, lexcat = lexer_out_s, lexer_out_c
    else
        lexstr, lexcat = "", 0
    end

    if lexcat == lexit.VARID or lexcat == lexit.NUMLIT or lexstr == "]" 
      or lexstr == ")" or lexstr == "true" or lexstr == "false" then
		lexit.preferOp()
	end
end

-- init
-- Initial call. Sets input for parsing functions.
local function init(prog)
    iter, state, lexer_out_s = lexit.lex(prog)
    advance()
end

-- atEnd
-- Return true if pos has reached end of input.
-- Function init must be called before this function is called.
local function atEnd()
    return lexcat == 0
end

-- matchString
-- Given string, see if current lexeme string form is equal to it. If
-- so, then advance to next lexeme & return true. If not, then do not
-- advance, return false.
-- Function init must be called before this function is called.
local function matchString(s)
    if lexstr == s then
        advance()
        return true
    else
        return false
    end
end

-- matchCat
-- Given lexeme category (integer), see if current lexeme category is
-- equal to it. If so, then advance to next lexeme & return true. If
-- not, then do not advance, return false.
-- Function init must be called before this function is called.
local function matchCat(c)
    if lexcat == c then
        advance()
        return true
    else
        return false
    end
end

-- Primary Function for Client Code

-- parse
-- Given program, initialize parser and call parsing function for start
-- symbol. Returns pair of booleans & AST. First boolean indicates
-- successful parse or not. Second boolean indicates whether the parser
-- reached the end of the input or not. AST is only valid if first
-- boolean is true.
function parseit.parse(prog)
    -- Initialization
    init(prog)

    -- Get results from parsing
    local good, ast = parse_program()  -- Parse start symbol
    local done = atEnd()

    -- And return them
    return good, done, ast
end

-- Parsing Functions

-- Each of the following is a parsing function for a nonterminal in the
-- grammar. Each function parses the nonterminal in its name and returns
-- a pair: boolean, AST. On a successul parse, the boolean is true, the
-- AST is valid, and the current lexeme is just past the end of the
-- string the nonterminal expanded into. Otherwise, the boolean is
-- false, the AST is not valid, and no guarantees are made about the
-- current lexeme. See the AST Specification near the beginning of this
-- file for the format of the returned AST.

-- parse_program
-- Parsing function for nonterminal "program".
-- Function init must be called before this function is called.
function parse_program()
    local good, ast

    good, ast = parse_stmt_list()
    return good, ast
end


-- parse_stmt_list
-- Parsing function for nonterminal "stmt_list".
-- Function init must be called before this function is called.
function parse_stmt_list()
    local good, ast, newast
    ast = { STMT_LIST }

    while true do
        if lexstr ~= "cr"
          and lexstr ~= "print"
          and lexstr ~= "input"
          and lexstr ~= "set"
          and lexstr ~= "sub"
          and lexstr ~= "call"
          and lexstr ~= "if"
          and lexstr ~= "while" then
            return true, ast
        end

        good, newast = parse_statement()
        if not good then
            return false, nil
        end
        table.insert(ast, newast)
    end
end


-- parse_statement
-- Parsing function for nonterminal "statement".
-- Function init must be called before this function is called.
function parse_statement()
    local good, ast, new, old

    if matchString("cr") then
        return true, { CR_STMT }

    elseif matchString("print") then
        old = lexstr
        if matchCat(lexit.STRLIT) then
            return true, { PRINT_STMT, { STRLIT_VAL, old } }
        end

        good, ast = parse_expr()
        if not good then
            return false, nil
        end
        return true, { PRINT_STMT, ast }

    elseif matchString("input") then
        good, ast = parse_lvalue()
        if not good then
            return false, nil
        end
        return true, { INPUT_STMT, ast }

    elseif matchString("set") then
        good, ast = parse_lvalue()
        if not good then
            return false, nil
        end

        if not matchString(":") then
            return false, nil
        end

        good, new = parse_expr()
        if not good then
            return false, nil
        end
        return true, { SET_STMT, ast, new }

	elseif matchString("sub") then
		old = lexstr
		if not matchCat(lexit.SUBID) then
			return false, nil
		end
		good, ast = parse_stmt_list()
		if not good then
			return false, nil
		end
		if matchString("end") then
			return true, { SUB_STMT, old, ast }
		end
		return false, nil
		
	elseif matchString("call") then
		old = lexstr
		if not matchCat(lexit.SUBID) then
			return false, nil
		end
		return true, { CALL_STMT, old }	
	elseif matchString("if") then
		local newast = { IF_STMT }
		local moreElseSTMTs = true
		good, ast = parse_expr()
		if not good then
			return false, nil
		end
		table.insert(newast, ast)
		good, new = parse_stmt_list()
		if not good then
			return false, nil
		end
		table.insert(newast, new)
		while true do
			if matchString("elseif") and moreElseSTMTs then
				good, ast = parse_expr()
				if not good then
					return false, nil
				end
				table.insert(newast, ast)
				good, new = parse_stmt_list()
				if not good then
					return false, nil
				end
				table.insert(newast, new)
			elseif matchString("else") then
				good, ast = parse_stmt_list()
				if not good then
					return false, nil
				end
				table.insert(newast, ast)
				moreElseSTMTs = false
			elseif matchString("end") then
				break;
			else
				return false, nil
			end
		end
		return true, newast
	elseif matchString("while") then
		good, ast = parse_expr()
		if not good then
			return false, nil
		end
		good, new = parse_stmt_list()
		if not good then
			return false, nil
		end
		if matchString("end") then
			return true, { WHILE_STMT, ast, new }
		end
		return false, nil
	else
		return false, nil
	end
end


-- parse_expr
-- Parsing function for nonterminal "expr".
-- Function init must be called before this function is called.
function parse_expr()
    local good, ast, saveop, newast

    good, ast = parse_comp_expr()
    if not good then
        return false, nil
    end

    while true do
        saveop = lexstr
        if not matchString("&&") and not matchString("||") then
            break
        end

        good, newast = parse_comp_expr()
        if not good then
            return false, nil
        end

        ast = { { BIN_OP, saveop }, ast, newast }
    end

    return true, ast
end

-- parse_term
-- Parsing function for nonterminal "term".
-- Function init must be called before this function is called.
function parse_term()
    local good, ast, saveop, newast

    good, ast = parse_factor()
    if not good then
        return false, nil
    end

    while true do
        saveop = lexstr
        if not matchString("*") and not matchString("/") and not matchString("%") then
            break
        end

        good, newast = parse_factor()
        if not good then
            return false, nil
        end

        ast = { { BIN_OP, saveop }, ast, newast }
    end

    return true, ast
end

-- parse_factor
-- Parsing function for nonterminal "factor".
-- Function init must be called before this function is called.
function parse_factor()
    local old, good, ast

    old = lexstr
	if matchCat(lexit.NUMLIT) then
		return true, { NUMLIT_VAL, old }
	elseif matchString("+") or matchString("-") then
		good, ast = parse_factor()
		if not good then
			return false, nil
		end
		return true, {{UN_OP, old}, ast}
    elseif matchString("(") then
        good, ast = parse_expr()
        if not good then
            return false, nil
        end

        if not matchString(")") then
            return false, nil
        end

        return true, ast
	elseif matchString("true") or matchString("false") then
		return true, { BOOLLIT_VAL, old }
    else
		good, ast = parse_lvalue()
		if not good then
			return false, nil
		end
        return true, ast
    end
end

-- parse_lvalue
-- Parsing function for nonterminal "lvalue".
-- Function init must be called before this function is called.
function parse_lvalue()
    local old, good, ast, new

    old = lexstr
    if matchCat(lexit.VARID) then
		ast = {VARID_VAL, old}
		if not matchString("[") then
			return true, ast
		end
		good, new = parse_expr()
		if not good then
			return false, nil
		end
		if not matchString("]") then
			return false, nil
		end
		return true, {ARRAY_REF, ast, new}
    end
	return false, nil
end

-- parse_comp_expr
-- Parsing function for nonterminal "comp_expr".
-- Function init must be called before this function is called.
function parse_comp_expr()
    local good, ast, saveop, newast
	
	if matchString("!") then
		good, ast = parse_comp_expr()
		if not good then
			return false, nil
		end
		return true, { {UN_OP, "!"}, ast }
	end
    good, ast = parse_arith_expr()
    if not good then
        return false, nil
    end

    while true do
        saveop = lexstr
        if not matchString("==") and not matchString("!=") and not matchString("<")
		  and not matchString("<=") and not matchString(">") and not matchString(">=") then
            break
        end

        good, newast = parse_arith_expr()
        if not good then
            return false, nil
        end

        ast = { { BIN_OP, saveop }, ast, newast }
    end

    return true, ast
end

-- parse_arith_expr
-- Parsing function for nonterminal "arith_expr".
-- Function init must be called before this function is called.
function parse_arith_expr()
    local good, ast, saveop, newast

    good, ast = parse_term()
    if not good then
        return false, nil
    end

    while true do
        saveop = lexstr
        if not matchString("+") and not matchString("-") then
            break
        end

        good, newast = parse_term()
        if not good then
            return false, nil
        end

        ast = { { BIN_OP, saveop }, ast, newast }
    end

    return true, ast
end

-- Module Export

return parseit