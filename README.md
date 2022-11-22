    # Configure project
    cmake -S . -B build
    
    # Build
    cmake --build build

    # Run tests
    ctest --test-dir build

    # Run puzzles
    build/day00
