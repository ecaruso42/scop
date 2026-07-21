NAME = scop

CXX = g++
CC = gcc

CXXFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iinclude

SRC_CPP = src/main.cpp		\
		  src/Input.cpp		\
		  src/Shader.cpp 	\
		  src/Window.cpp	\
		  src/Mesh.cpp		\
		  src/Renderer.cpp	\
		  src/Math/Matrix4.cpp	\
		  src/Math/Vector3.cpp	\
		  src/Math/Vector2.cpp	\
		  src/ObjLoader.cpp	\

SRC_C = src/glad.c

OBJ_CPP = $(SRC_CPP:.cpp=.o)
OBJ_C = $(SRC_C:.c=.o)

OBJ = $(OBJ_CPP) $(OBJ_C)

LIBS = -lglfw -ldl -lGL

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) $(LIBS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.c
	$(CC) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re