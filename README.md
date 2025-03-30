# Porównanie implamentacji algorytmów Dijkstry

### OPIS

    Projekt porównuje trzy implementacje algorytmu Dijkstry
    
        - z wykorzystaniem kolejki priorytetowej na bazie kopca d-arnego

        - z wykorzystaniem kobułeków (algorytm Diala)
        
        - z wykorzystaniem struktury Radix Heap
    
    Wszelkie struktury i algorytmy zostały napisane na potrzeby projektu (nie są wykorzystywane żadne gotowe elementy z bibliotek)

### STRUKTURA PLIKÓW

    - README.md: ten plik

    - Makefile: plik do zautomatyzowanego kompilowania programu

    - AOD3.pdf: omówienie algorytmów oraz dane z przeprowadzonych testów

    - src: folder z plikami źródłowymi

    - include: folder z plikami nagłówkowymi

    - build: folder z plikami obiektowymi (zostaje utworzony po użyciu polecenia 'make')
    
    - bin: folder z plikami wykonywalnymi (zostaje utworzony po użyciu polecenia 'make')

### TECHNOLOGIE

    JĘZYK PROGRAMOWANIA

    Program został napisany w języku c++ (standard C++14)
    Testowany pod systemem Ubuntu
    Kompilowany kompilatorem g++ w wersji 9.4.0

    BIBLIOTEKI

    Program wykorzystuje jedynie standardowe biblioteki
    tj. iostream, fstream, limits, string, chrono

### KOMPILACJA

    Polecenie 'make' kompiluje program tworząc finalnie trzy plik wykonywalne
    ./bin/dijkstra ./bin/dial ./bin/radixheap

    Można wykorzystać 'make dijkstra', 'make dial' lub 'make radixheap', aby
    otrzymać tylko jeden odpowiedni plik wykonywalny

    Polecenie 'make clean' usuwa wszystkie pliki/foldery stworzone poleceniem 'make'

    W celu wykorzystania innego kompilatora niż g++, należy do polecenia 'make'
    dopisać 'CC=<komenda_kompiltora>', np. 'CC=clang++'
