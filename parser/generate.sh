#!/bin/sh

antlr4 -o ../generated_parser -Dlanguage=Go -no-visitor -package parser *.g4
