CC = g++

CFLAGS = -Wall -g

SRCS = repl.cpp logger.cpp result.cpp tokenizer.cpp parser.cpp evaluator.cpp

OBJS = $(SRCS:.cpp=.o)

TARGET = calculator

all: $(TARGET)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJS) $(TARGET)
