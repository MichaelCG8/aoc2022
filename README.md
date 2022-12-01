    # Configure project
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    
    # Build
    cmake --build build

    # Run tests
    ctest --test-dir build --output-on-failure

    # Run puzzles
    build/day00

    # New day
    cookiecutter template
    # Enter number when prompted, e.g. 4
