echo "=== Errors ==="
echo

bin/ltnc --src diagnostics/error/assign.ltn
bin/ltnc --src diagnostics/error/unary_neg.ltn
bin/ltnc --src diagnostics/error/binary_add.ltn

echo "=== Warnings ==="
echo "TODO"
