#!/bin/sh
#https://learnbyexample.github.io/customizing-pandoc/
pandoc documentation.md -f gfm -V linkcolor:blue -V geometry:margin=2cm --toc --pdf-engine=xelatex -o documentation.pdf
