#!/usr/bin/env bash
set -u
cd "$(dirname "$0")"

EXE="${1:-${EXE:-./g-v2}}"
if [[ ! -x "$EXE" ]]; then
    if [[ -x "./g-v2" ]]; then
        EXE="./g-v2"
    elif [[ -x "./g-v2.exe" ]]; then
        EXE="./g-v2.exe"
    else
        echo "ERRO: executavel g-v2 ou g-v2.exe nao encontrado. Rode make primeiro."
        exit 1
    fi
fi

shopt -s nullglob
TOTAL=0
FAIL=0

run_one() {
    local file="$1"
    local expected="$2"  # ok | erro
    local base asm out err status stderr_one_line stdout_one_line

    base="$(basename "$file")"
    asm="${file%.*}.asm"
    out="$(mktemp)"
    err="$(mktemp)"
    rm -f "$asm"

    "$EXE" "$file" >"$out" 2>"$err"
    status=$?

    stderr_one_line="$(tr '\n' ' ' < "$err" | sed 's/[[:space:]]\+$//')"
    stdout_one_line="$(tr '\n' ' ' < "$out" | sed 's/[[:space:]]\+$//')"

    TOTAL=$((TOTAL + 1))

    if [[ "$expected" == "ok" ]]; then
        if [[ $status -eq 0 && ! -s "$err" && -s "$asm" ]]; then
            echo "  OK: $base"
        else
            echo "  FALHOU: $base"
            echo "    status=$status"
            [[ -n "$stderr_one_line" ]] && echo "    stderr: $stderr_one_line"
            [[ -n "$stdout_one_line" ]] && echo "    stdout: $stdout_one_line"
            [[ ! -s "$asm" ]] && echo "    asm nao foi gerado: $asm"
            FAIL=$((FAIL + 1))
        fi
    else
        if [[ $status -ne 0 && -s "$err" && ! -e "$asm" ]]; then
            echo "  OK: $base => $stderr_one_line"
        else
            echo "  FALHOU: $base"
            echo "    status=$status"
            [[ -n "$stderr_one_line" ]] && echo "    stderr: $stderr_one_line"
            [[ -n "$stdout_one_line" ]] && echo "    stdout: $stdout_one_line"
            [[ -e "$asm" ]] && echo "    asm foi gerado indevidamente: $asm"
            FAIL=$((FAIL + 1))
        fi
    fi

    rm -f "$out" "$err"
}

run_group() {
    local title="$1"
    local dir="$2"
    local expected="$3"
    local files=("$dir"/*.txt)

    echo ""
    echo "=== $title ==="
    if [[ ${#files[@]} -eq 0 ]]; then
        echo "  AVISO: nenhum .g encontrado em $dir"
        return
    fi

    local f
    for f in "${files[@]}"; do
        run_one "$f" "$expected"
    done
}

run_group "Programas CORRETOS" "tests/corretos" "ok"
run_group "Programas LEXICOS ERRADOS" "tests/errados/lexico" "erro"
run_group "Programas SINTATICOS ERRADOS" "tests/errados/sintatico" "erro"
run_group "Programas SEMANTICOS ERRADOS" "tests/errados/semantico" "erro"

echo ""
echo "Resumo: $((TOTAL - FAIL))/$TOTAL passaram."

if [[ $FAIL -ne 0 ]]; then
    exit 1
fi
              