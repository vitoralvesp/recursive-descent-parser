#!/bin/bash

INPUT="./tests/test_cases.txt"
OUTPUT_TXT="./tests/outputs/output_tests.txt"
OUTPUT_PDF="./tests/outputs/output_tests_pdf.pdf"

> "$OUTPUT_TXT"

# Roda os testes e salva a saída
while read line; do
    echo "Expressao: $line" >> "$OUTPUT_TXT"
    echo "$line" | ./main >> "$OUTPUT_TXT"
    echo "" >> "$OUTPUT_TXT"
done < "$INPUT"


enscript "$OUTPUT_TXT" -o - | ps2pdf - "$OUTPUT_PDF"

echo "Resultados salvos em $OUTPUT_PDF"
