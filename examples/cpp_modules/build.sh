#!/usr/bin/env bash
set -e

# ---------------------------------------------
# CONFIGURACIÓN
# ---------------------------------------------
PORT="/dev/ttyUSB0"
BAUD="460800"
FLASH_ADDR="0x00000"

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/build"
PROJECT_NAME="$(basename "$SCRIPT_DIR")"

TOOLCHAIN_FILE="$SCRIPT_DIR/../../toolchain-xtensa.cmake"

# ---------------------------------------------
# FUNCIONES
# ---------------------------------------------

do_clean() {
    echo "==> Limpiando build/"
    rm -rf "$BUILD_DIR"
}

do_build() {
    echo "=========================================="
    echo "  BUILD: $PROJECT_NAME"
    echo "=========================================="

    mkdir -p "$BUILD_DIR"

    echo "==> Configurando CMake (con Ninja)"
    cmake -G Ninja \
          -S "$SCRIPT_DIR" \
          -B "$BUILD_DIR" \
          -DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN_FILE"

    echo "==> Compilando con Ninja"
    cmake --build "$BUILD_DIR" --parallel --verbose

    echo "==> Build completado"
}

do_flash() {
    echo "=========================================="
    echo "  FLASH: $PROJECT_NAME"
    echo "=========================================="

    if [ ! -d "$BUILD_DIR" ]; then
        echo "ERROR: No existe build/. Ejecuta 'build' antes de 'flash'"
        exit 1
    fi

    ELF_FILE="$(find "$BUILD_DIR" -maxdepth 1 -type f \( -name '*.elf' -o -name "$PROJECT_NAME" \) | head -n 1)"

    if [ ! -f "$ELF_FILE" ]; then
        echo "ERROR: No se encontró ningún ELF en $BUILD_DIR"
        exit 1
    fi

    echo "Firmware ELF encontrado:"
    echo "  $ELF_FILE"

    BIN_FILE="$BUILD_DIR/firmware"

    echo "==> Generando BIN..."
    esptool --chip esp8266 elf2image "$ELF_FILE" --output "$BIN_FILE"

    echo "BIN generado:"
    echo "  ${BIN_FILE}0x00000.bin"

    echo "==> Flasheando"
    esptool \
        --chip esp8266 \
        --port "$PORT" \
        write-flash \
        "$FLASH_ADDR" "${BIN_FILE}0x00000.bin"

    echo "=========================================="
    echo "  FLASH COMPLETADO"
    echo "=========================================="
}

# ---------------------------------------------
# VALIDACIÓN DE ORDEN
# ---------------------------------------------

if [ $# -eq 0 ]; then
    echo "Uso:"
    echo "  ./build.sh clean"
    echo "  ./build.sh build"
    echo "  ./build.sh flash"
    echo "  ./build.sh clean build flash"
    exit 1
fi

ACTIONS=("$@")

WANT_CLEAN=false
WANT_BUILD=false
WANT_FLASH=false

for A in "${ACTIONS[@]}"; do
    case "$A" in
        clean) WANT_CLEAN=true ;;
        build) WANT_BUILD=true ;;
        flash) WANT_FLASH=true ;;
        *)
            echo "ERROR: Acción desconocida: $A"
            exit 1
            ;;
    esac
done

# Regla 1: clean sin build → NO permitido
if $WANT_CLEAN && ! $WANT_BUILD && $WANT_FLASH; then
    echo "ERROR: 'clean flash' NO es válido. Debe ser 'clean build flash'."
    exit 1
fi

# Regla 2: flash sin build previo → NO permitido
if $WANT_FLASH && ! $WANT_BUILD && [ ! -d "$BUILD_DIR" ]; then
    echo "ERROR: 'flash' requiere 'build' antes."
    exit 1
fi

# ---------------------------------------------
# EJECUCIÓN EN ORDEN FIJO
# ---------------------------------------------

if $WANT_CLEAN; then do_clean; fi
if $WANT_BUILD; then do_build; fi
if $WANT_FLASH; then do_flash; fi

