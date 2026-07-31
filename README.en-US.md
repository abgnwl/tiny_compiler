

# A Simple Compiler
* Frontend of a simple compiler, implemented using a subset of basic C syntax and keywords.<br>
* The code is a bit ugly :D

## Lexical Analyzer
* Generates vector<tokens>
* Output is used for syntax analysis

## Syntax Analyzer
* Uses $ to indicate the end of input, which must be included in the [terminal] section of grammar.
* Uses @ to represent an empty string; the correctness of empty productions is **not verified**.

## Intermediate Code Generation
* During parsing, it generates quadruples to produce intermediate code. <br>
* The translation method is **non-standard**, and **does not use backpatching**.

<br>
2017.05.25
