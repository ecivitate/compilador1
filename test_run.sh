#!/bin/bash
cd "$(dirname "$0")"

echo "=== Build ==="
make clean && make 2>&1 | grep -v "warning" | grep -v "^$" | grep -v "^\s*\^"
echo ""

echo "=== Programas CORRETOS (stderr deve estar vazio) ==="
for f in tests/corretos/*.g; do
    errors=$(./g-v1.exe "$f" 2>&1 >/dev/null)
    if [ -z "$errors" ]; then
        echo "  OK: $(basename $f)"
    else
        echo "  FALHOU: $(basename $f) => $errors"
    fi
done

echo ""
echo "=== Programas SINTATICOS ERRADOS (devem reportar erro no stderr) ==="
for f in tests/errados/sintatico/*.g; do
    errors=$(./g-v1.exe "$f" 2>&1 >/dev/null)
    if [ -n "$errors" ]; then
        echo "  OK: $(basename $f) => $errors"
    else
        echo "  FALHOU (erro nao detectado): $(basename $f)"
    fi
done

echo ""
echo "=== Programas SEMANTICOS ERRADOS (devem reportar erro no stderr) ==="
for f in tests/errados/semantico/*.g; do
    errors=$(./g-v1.exe "$f" 2>&1 >/dev/null)
    if [ -n "$errors" ]; then
        echo "  OK: $(basename $f) => $errors"
    else
        echo "  FALHOU (erro nao detectado): $(basename $f)"
    fi
done
