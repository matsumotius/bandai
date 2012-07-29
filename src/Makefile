all:
	g++ -funwind-tables -o ../bandai image/parser.cpp logic/bhattacharyya.cpp serializer/writer.cpp serializer/reader.cpp service/store.cpp service/searcher.cpp main.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv`
