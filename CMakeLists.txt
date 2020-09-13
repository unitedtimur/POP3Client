cmake_minimum_required (VERSION 3.15)

project (POP3Client)

#***************************************************************

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set (HEADERS 
	include/configuration.h
	include/client.h
	include/functionality.h
	include/socket.h
)

set (SOURCES 
	src/client.cpp
	src/main.cpp
	src/functionality.cpp
	src/socket.cpp
)

#***************************************************************

add_executable (${PROJECT_NAME} 
	${HEADERS}
	${SOURCES}
)