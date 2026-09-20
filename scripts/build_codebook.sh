#!/bin/sh
# Compile LaTeX codebook on demand
CODEBOOK_DIR="/home/shazid/latex/codebook"
MAIN_TEX="$CODEBOOK_DIR/main.tex"

if [ ! -f "$MAIN_TEX" ]; then
    echo "Error: $MAIN_TEX not found."
    exit 1
fi

echo "Compiling $MAIN_TEX..."
cd "$CODEBOOK_DIR" && pdflatex -interaction=nonstopmode main.tex > /dev/null 2>&1
echo "Done! Codebook PDF updated: $CODEBOOK_DIR/main.pdf"
