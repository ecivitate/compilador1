#!/bin/bash
cd "$(dirname "$0")"

if [ -x "./g-v1" ]; then
    EXE="./g-v1"
elif [ -x "./g-v1.exe" ]; then
    EXE="./g-v1.exe"
else
    echo "ERRO: executavel g-v1 ou g-v1.exe nao encontrado. Rode make primeiro."
    exit 1
fi

echo "=== Programas CORRETOS (stderr deve estar vazio) ==="
for f in tests/corretos/*.g; do
    errors=$($EXE "$f" 2>&1 >/dev/null)
    if [ -z "$errors" ]; then
        echo "  OK: $(basename $f)"
    else
        echo "  FALHOU: $(basename $f) => $errors"
    fi
done

echo ""
echo "=== Programas SINTATICOS ERRADOS (devem reportar erro no stderr) ==="
for f in tests/errados/sintatico/*.g; do
    errors=$($EXE "$f" 2>&1 >/dev/null)
    if [ -n "$errors" ]; then
        echo "  OK: $(basename $f) => $errors"
    else
        echo "  FALHOU (erro nao detectado): $(basename $f)"
    fi
done

echo ""
echo "=== Programas SEMANTICOS ERRADOS (devem reportar erro no stderr) ==="
for f in tests/errados/semantico/*.g; do
    errors=$($EXE "$f" 2>&1 >/dev/null)
    if [ -n "$errors" ]; then
        echo "  OK: $(basename $f) => $errors"
    else
        echo "  FALHOU (erro nao detectado): $(basename $f)"
    fi
done
