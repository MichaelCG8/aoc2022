    # Configure project
    cmake -S . -B build
    
    # Build
    cmake --build build

    # Run tests
    ctest --test-dir build --output-on-failure

    # Run puzzles
    build/day00
