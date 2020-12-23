# Source files

# Test files
target_sources(${PROJECT_NAME} PRIVATE
    "src/eSocket_test.cpp"
	"src/tests/program/ESocket_tests.h"
)

# Program files to test
target_sources(${PROJECT_NAME} PRIVATE
    "../../src/program/ESocket.h"
	"../../src/program/ESocket.cpp"
	"../../src/utils/Delay.h"
	"../../src/utils/Delay.cpp"
	"../../src/utils/Exception.h"
	"../../src/utils/Exception.cpp"
)