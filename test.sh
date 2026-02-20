#!/bin/bash

# Configuration
TEST_COUNT=25       # How many times to loop
STACK_SIZE=500      # How many numbers to sort
MAX_MOVES=5500      # Maximum allowed moves
CHECKER="./checker_linux" # Path to your checker binary

# Colors
GREEN="\033[32m"
RED="\033[31m"
RESET="\033[0m"

echo "========================================================"
echo "  PUSH_SWAP ULTIMATE TESTER                             "
echo "  Running $TEST_COUNT tests with $STACK_SIZE numbers    "
echo "  Max moves allowed: $MAX_MOVES                         "
echo "========================================================"

# Check if checker exists
if [ ! -f "$CHECKER" ]; then
    echo -e "${RED}Error: $CHECKER not found.${RESET}"
    exit 1
fi
chmod +x "$CHECKER"

echo "========================================================"
echo "  TESTING EDGE CASES                                    "
echo "========================================================"

# --- Edge Case 1: Already Sorted ---
echo -n "Test 0a (Already Sorted):       "
ARG_SORTED=$(seq 1 $STACK_SIZE | tr '\n' ' ')
MOVES_SORTED=$(./push_swap $ARG_SORTED | wc -l)
valgrind --leak-check=full --errors-for-leak-kinds=all --error-exitcode=42 ./push_swap $ARG_SORTED > /dev/null 2>&1
LEAK_SORTED=$?

if [ "$MOVES_SORTED" -ne 0 ]; then
    echo -e "${RED}KO (Moves: $MOVES_SORTED, expected 0)${RESET}"
    exit 1
elif [ $LEAK_SORTED -eq 42 ]; then
    echo -e "${RED}KO (Memory Leak Detected)${RESET}"
    exit 1
else
    echo -e "${GREEN}OK${RESET} (0 moves, no leaks)"
fi

# --- Edge Case 2: Duplicates ---
echo -n "Test 0b (Duplicates):           "
ARG_DUP="42 15 8 42 9"
# Capture standard error to check for the "Error" string
ERR_OUT=$(./push_swap $ARG_DUP 2>&1 >/dev/null)
valgrind --leak-check=full --errors-for-leak-kinds=all --error-exitcode=42 ./push_swap $ARG_DUP > /dev/null 2>&1
LEAK_DUP=$?

if [[ ! "$ERR_OUT" =~ "Error" ]]; then
    echo -e "${RED}KO (Did not print 'Error' to stderr)${RESET}"
    exit 1
elif [ $LEAK_DUP -eq 42 ]; then
    echo -e "${RED}KO (Memory Leak Detected during error handling)${RESET}"
    exit 1
else
    echo -e "${GREEN}OK${RESET} (Proper error handling, no leaks)"
fi

# --- Edge Case 3: Invalid Input (Letters/Symbols) ---
echo -n "Test 0c (Invalid Input):        "
ARG_INV="42 15 a 9"
# Capture standard error to check for the "Error" string
ERR_OUT_INV=$(./push_swap $ARG_INV 2>&1 >/dev/null)
valgrind --leak-check=full --errors-for-leak-kinds=all --error-exitcode=42 ./push_swap $ARG_INV > /dev/null 2>&1
LEAK_INV=$?

if [[ ! "$ERR_OUT_INV" =~ "Error" ]]; then
    echo -e "${RED}KO (Did not print 'Error' to stderr)${RESET}"
    exit 1
elif [ $LEAK_INV -eq 42 ]; then
    echo -e "${RED}KO (Memory Leak Detected during error handling)${RESET}"
    exit 1
else
    echo -e "${GREEN}OK${RESET} (Proper error handling, no leaks)"
fi

# --- Edge Case 4: Integer Overflow/Underflow ---
echo -n "Test 0d (INT Limits):           "
# 2147483648 is INT_MAX + 1, -2147483649 is INT_MIN - 1
ARG_OVER="42 2147483648 -2147483649 9"
# Capture standard error to check for the "Error" string
ERR_OUT_OVER=$(./push_swap $ARG_OVER 2>&1 >/dev/null)
valgrind --leak-check=full --errors-for-leak-kinds=all --error-exitcode=42 ./push_swap $ARG_OVER > /dev/null 2>&1
LEAK_OVER=$?

if [[ ! "$ERR_OUT_OVER" =~ "Error" ]]; then
    echo -e "${RED}KO (Did not print 'Error' to stderr)${RESET}"
    exit 1
elif [ $LEAK_OVER -eq 42 ]; then
    echo -e "${RED}KO (Memory Leak Detected during error handling)${RESET}"
    exit 1
else
    echo -e "${GREEN}OK${RESET} (Proper error handling, no leaks)"
fi

# --- Edge Case 5: Single Quoted String ---
echo -n "Test 0e (Single Quoted String): "
ARG_STR="42 15 8 9 21"
# We wrap $ARG_STR in double quotes in the command to pass it as a single argument
CHECKER_OUT_STR=$(./push_swap "$ARG_STR" | $CHECKER "$ARG_STR" 2>&1)
valgrind --leak-check=full --errors-for-leak-kinds=all --error-exitcode=42 ./push_swap "$ARG_STR" > /dev/null 2>&1
LEAK_STR=$?

if [ "$CHECKER_OUT_STR" != "OK" ]; then
    echo -e "${RED}KO (Did not sort correctly or checker failed)${RESET}"
    exit 1
elif [ $LEAK_STR -eq 42 ]; then
    echo -e "${RED}KO (Memory Leak Detected)${RESET}"
    exit 1
else
    echo -e "${GREEN}OK${RESET} (Parsed, sorted, no leaks)"
fi

# --- Edge Case 6: Empty String ---
echo -n "Test 0f (Empty String):         "
# Run normally to check for segfaults (exit codes > 128 usually mean a signal killed it)
./push_swap "" > /dev/null 2>&1
EXIT_CODE=$?
# Run in valgrind to check for leaks
valgrind --leak-check=full --errors-for-leak-kinds=all --error-exitcode=42 ./push_swap "" > /dev/null 2>&1
LEAK_EMPTY=$?

if [ $EXIT_CODE -gt 128 ]; then
    echo -e "${RED}KO (Crash/Segfault Detected)${RESET}"
    exit 1
elif [ $LEAK_EMPTY -eq 42 ]; then
    echo -e "${RED}KO (Memory Leak Detected)${RESET}"
    exit 1
else
    echo -e "${GREEN}OK${RESET} (Handled empty string, no leaks or crashes)"
fi

echo -n "Test 0g (Reverse Order):        "
# Generates numbers from STACK_SIZE down to 1
ARG_REV=$(seq $STACK_SIZE -1 1 | tr '\n' ' ')
CHECKER_OUT_REV=$(./push_swap $ARG_REV | $CHECKER $ARG_REV 2>&1)
MOVES_REV=$(./push_swap $ARG_REV | wc -l)
valgrind --leak-check=full --errors-for-leak-kinds=all --error-exitcode=42 ./push_swap $ARG_REV > /dev/null 2>&1
LEAK_REV=$?

if [ "$CHECKER_OUT_REV" != "OK" ]; then
    echo -e "${RED}KO (Not sorted correctly)${RESET}"
    exit 1
elif [ $LEAK_REV -eq 42 ]; then
    echo -e "${RED}KO (Memory Leak Detected)${RESET}"
    exit 1
elif [ "$MOVES_REV" -gt "$MAX_MOVES" ]; then
    echo -e "${RED}KO ($MOVES_REV moves exceeds $MAX_MOVES limit)${RESET}"
    exit 1
else
    echo -e "${GREEN}OK${RESET} ($MOVES_REV moves, sorted, no leaks)"
fi

# --- Edge Case 8: All Negative Numbers ---
echo -n "Test 0h (All Negative):         "
# Generates random negative numbers only
ARG_NEG=$(seq -10000 -1 | shuf -n $STACK_SIZE | tr '\n' ' ')
CHECKER_OUT_NEG=$(./push_swap $ARG_NEG | $CHECKER $ARG_NEG 2>&1)
MOVES_NEG=$(./push_swap $ARG_NEG | wc -l)
valgrind --leak-check=full --errors-for-leak-kinds=all --error-exitcode=42 ./push_swap $ARG_NEG > /dev/null 2>&1
LEAK_NEG=$?

if [ "$CHECKER_OUT_NEG" != "OK" ]; then
    echo -e "${RED}KO (Not sorted correctly)${RESET}"
    exit 1
elif [ $LEAK_NEG -eq 42 ]; then
    echo -e "${RED}KO (Memory Leak Detected)${RESET}"
    exit 1
elif [ "$MOVES_NEG" -gt "$MAX_MOVES" ]; then
    echo -e "${RED}KO ($MOVES_NEG moves exceeds $MAX_MOVES limit)${RESET}"
    exit 1
else
    echo -e "${GREEN}OK${RESET} ($MOVES_NEG moves, sorted, no leaks)"
fi

echo "========================================================"
echo "  STARTING RANDOM TESTS                                 "
echo "========================================================"

TOTAL_MOVES=0

for ((i=1; i<=TEST_COUNT; i++))
do
    # 1. Generate Random Numbers
    ARG=$(seq -10000 10000 | shuf -n $STACK_SIZE | tr '\n' ' ')

    # 2. Check Memory Leaks (Valgrind)
    valgrind --leak-check=full --errors-for-leak-kinds=all --error-exitcode=42 ./push_swap $ARG > /dev/null 2>&1
    if [ $? -eq 42 ]; then
        VALGRIND_RES="${RED}KO${RESET}"
        LEAK_FOUND=1
    else
        VALGRIND_RES="${GREEN}OK${RESET}"
        LEAK_FOUND=0
    fi

    # 3. Check Sorting Correctness (Checker)
    CHECKER_OUT=$(./push_swap $ARG | $CHECKER $ARG 2>&1)
    if [ "$CHECKER_OUT" == "OK" ]; then
        CHECKER_RES="${GREEN}OK${RESET}"
    else
        CHECKER_RES="${RED}KO${RESET}"
    fi

    # 4. Count Moves & Check Limits
    MOVES=$(./push_swap $ARG | wc -l)
    TOTAL_MOVES=$((TOTAL_MOVES + MOVES))
    
    if [ "$MOVES" -gt "$MAX_MOVES" ]; then
        MOVES_RES="${RED}$MOVES (Too High!)${RESET}"
        EXCEEDED_MOVES=1
    else
        MOVES_RES="${GREEN}$MOVES${RESET}"
        EXCEEDED_MOVES=0
    fi

    # 5. Print Result Line
    echo -e "Test $i: Valgrind=$VALGRIND_RES checker_linux=$CHECKER_RES | moves=$MOVES_RES"

    # 6. Stop immediately if something failed
    if [ $LEAK_FOUND -eq 1 ] || [ "$CHECKER_OUT" != "OK" ] || [ $EXCEEDED_MOVES -eq 1 ]; then
        echo "--------------------------------------------------------"
        echo -e "${RED}❌ TEST FAILED ON INPUT:${RESET}"
        if [ $EXCEEDED_MOVES -eq 1 ]; then
            echo -e "Reason: Exceeded maximum moves limit ($MAX_MOVES)"
        fi
        if [ $LEAK_FOUND -eq 1 ]; then
            echo -e "Reason: Memory leak detected"
        fi
        if [ "$CHECKER_OUT" != "OK" ]; then
            echo -e "Reason: Array not sorted correctly"
        fi
        echo "$ARG"
        exit 1
    fi
done

# Calculate Average
AVERAGE=$((TOTAL_MOVES / TEST_COUNT))

echo "========================================================"
echo -e "  🎉 ALL TESTS PASSED SUCCESSFULLY!                     "
echo -e "  📊 AVERAGE MOVES: ${GREEN}$AVERAGE${RESET} (for $STACK_SIZE elements)"
echo "========================================================"
