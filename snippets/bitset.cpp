    const int SIZE = 8; // Define bitset size
    bitset<SIZE> b;     // Initialize bitset with all bits set to 0
    cout << "Initial bitset: " << b << endl;
    // set(): Set a bit at a given index
    b.set(2);
    b.set(5);
    cout << "After set(2) and set(5): " << b << endl;
    // reset(): Reset a bit at a given index (set to 0)
    b.reset(2);
    cout << "After reset(2): " << b << endl;
    // flip(): Flip a bit at a given index
    b.flip(5);
    cout << "After flip(5): " << b << endl;
    // count(): Count number of set bits
    cout << "Count of set bits: " << b.count() << endl;
    // test(): Check if a bit is set at an index
    cout << "Is bit at index 3 set? " << (b.test(3) ? "Yes" : "No") << endl;
    // any(): Check if any bit is set
    cout << "Is any bit set? " << (b.any() ? "Yes" : "No") << endl;
    // none(): Check if no bit is set
    cout << "Are all bits 0? " << (b.none() ? "Yes" : "No") << endl;
    // all(): Check if all bits are set
    b.set(); // Setting all bits to 1
    cout << "After setting all bits: " << b << endl;
    cout << "Are all bits set? " << (b.all() ? "Yes" : "No") << endl;
    // size(): Get size of bitset
    cout << "Size of bitset: " << b.size() << endl;
    // to_string(): Convert bitset to string
    cout << "Bitset as string: " << b.to_string() << endl;
    // to_ulong(): Convert bitset to unsigned long
    cout << "Bitset as unsigned long: " << b.to_ulong() << endl;
    // to_ullong(): Convert bitset to unsigned long long
    cout << "Bitset as unsigned long long: " << b.to_ullong() << endl;
