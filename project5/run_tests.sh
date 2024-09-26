#!/bin/bash

# Make sure the my_outputs directory exists
mkdir -p my_outputs

# Compile the program
make

run_test() {
    
    TEST_FILE=$1
    OUTPUT_FILE=my_outputs/$(basename $TEST_FILE .in).out

    if [ "$2" == "v" ]; then
        VALGRIND="valgrind --leak-check=full"
    else
        VALGRIND=""
    fi

    # Run the program or valgrind if specified
    $VALGRIND ./graph.out < $TEST_FILE > $OUTPUT_FILE

    # Check the exit status of the last command run
    if [ $? -eq 0 ]; then
        echo "Test $(basename $TEST_FILE) passed."
    else
        echo "Test $(basename $TEST_FILE) failed."
    fi
}

# Iterate over all .in files in test_inputs directory
for TEST_FILE in test_inputs/*.in
do
    if [ "$1" == "-v" ]; then
        run_test "$TEST_FILE" "v"
    else
        run_test "$TEST_FILE"
    fi
done

echo ""
echo "----------------"
echo "TESTING COMPLETED"



