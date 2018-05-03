ifdef NDEBUG
	ndebug=-DNDEBUG
else
	ndebug=
endif

ZIP_NAME = archive

SOURCES=mock_trie.c trie_main.c
OBJECTS=$(addsuffix .o, $(basename $(SOURCES)))
ALLSOURCES=$(SOURCES) mock_trie.h README text_for_trie.txt Makefile
TARGET=trie_main

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS)

zip: $(ZIP_NAME).tar.gz

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

.c.o:
	$(CC) -c -o $@ $<

$(ZIP_NAME).tar.gz: $(ALLSOURCES)
	rm -rf $(ZIP_NAME)
	mkdir $(ZIP_NAME)
	cp $(ALLSOURCES) $(ZIP_NAME)
	tar cvzf $(ZIP_NAME).tar.gz $(ZIP_NAME)
	rm -rf $(ZIP_NAME)
