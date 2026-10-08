TARGET   = app.out
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -MMD -MP
LIBS     = -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

SRCS     = $(wildcard *.cpp)
OBJS     = $(SRCS:.cpp=.o)
DEPS     = $(SRCS:.cpp=.d)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -f *.o *.d $(TARGET)

.PHONY: clean
